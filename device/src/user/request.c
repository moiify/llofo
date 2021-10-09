/*
 * request.c
 *
 *  Created on: 2020/04/09
 *      Author: lc
 */
#include "nmea/gmath.h"
#include "cJSON/cJSON.h"
#include <string.h>

#include "msg.h"
#include "log.h"
#include "tlv.h"
#include "car.h"
#include "data.h"
#include "socket.h"
#include "device.h"
#include "setting.h"
#include "userMsg.h"
#include "request.h"
#include "version.h"
#include "response.h"
#include "protocol.h"
#include "gps_parse.h"
#include "user_timer.h"
#include "flash.h"

#define DESC_DEF(x) case x:\
                        return #x  //#直接返回宏定义对应的字符串

static char* getAlarmDescription(int type)
{
    switch (type)
    {
#ifdef APP_DEBUG
            DESC_DEF(ALARM_FENCE_OUT);
            DESC_DEF(ALARM_FENCE_IN);
            DESC_DEF(ALARM_VIBRATE);
            DESC_DEF(ALARM_BATTERY50);
            DESC_DEF(ALARM_BATTERY30);
            DESC_DEF(ALARM_POWER_CUT);
            DESC_DEF(ALARM_SWITCH_OPEN);
            DESC_DEF(ALARM_SWITCH_CLOSE);
            DESC_DEF(ALARM_BACKSEAT_OPEN);
            DESC_DEF(ALARM_BACKSEAT_SHUT);
            DESC_DEF(ALARM_POWER_RESTORE);
            DESC_DEF(ALARM_SHAKE);
            DESC_DEF(ALARM_AUTOLOCK_DEFEND);
            DESC_DEF(ALARM_AUTOLOCK_WARNING);
            DESC_DEF(ALARM_DEFENDON);
            DESC_DEF(ALARM_DEFENDOFF);
            DESC_DEF(ALARM_DEFENDON_BLE);
            DESC_DEF(ALARM_DEFENDOFF_BLE);
            DESC_DEF(ALARM_ACCON_BLE);
            DESC_DEF(ALARM_LOCK_CAR);
            DESC_DEF(ALARM_ACCON);
            DESC_DEF(ALARM_ACCON_PKE);
            DESC_DEF(ALARM_CONSTANTLYSHAKE);
            DESC_DEF(ALARM_UNLOCKSADDLE_BLE);
            DESC_DEF(ALARM_OVERTURN);
            DESC_DEF(ALARM_OVERTURN_RESTORE);
#endif
        default:
        {
            static char alarm_type[10] = {0};
            snprintf(alarm_type, 10, "%d", type);
            return alarm_type;
        }
    }
}
int cmd_alarm(char alarm_type)
{
    MSG_ALARM_REQ* socket_msg = alloc_msg(CMD_ALARM, sizeof(MSG_ALARM_REQ));
    if (!socket_msg)
    {
        LOG_ERROR("[Alarm CMD] alloc message failed!");
        return -1;
    }

    LOG_DEBUG("[Alarm CMD] sending alarm %s", getAlarmDescription(alarm_type));
    socket_msg->alarmType = alarm_type;

    socket_sendDataDirectly(socket_msg, sizeof(MSG_ALARM_REQ));
    return 0;
}

int cmd_faultRecord(void)
{
    MSG_FAULT_INFO* socket_msg = alloc_msg(CMD_FAULTINFO, sizeof(MSG_FAULT_INFO));
    DATA *pData = data_getData();
    if (!socket_msg)
    {
        LOG_ERROR("alloc message failed!");
        return -1;
    }

    socket_msg->etcFault = _htons(pData->etc.fault);
    socket_msg->bmsFault = _htons(pData->bms.fault);//目前只有小安协议有fault位
    socket_msg->ecuFault = _htons(pData->ecuFault);
    
    socket_sendDataDirectly(socket_msg, sizeof(MSG_FAULT_INFO));
    return 0;
}

static int cmd_sendStatus_cb(void)
{
    userMsg_setEvent(EVENT_SENDSTATUS, 0);
    return 0;
}
int cmd_statusMatchPeriod(void)
{
    userMsg_setEvent(EVENT_SENDSTATUS, 0);
    return timer_startRepeat(TIMER_SEND_GPS, TIMER_MS, data_getData()->gpsSendPeriod_ms, cmd_sendStatus_cb);
}

int cmd_Login(void)
{
    MSG_LOGIN_REQ_NEW* msg = alloc_msg(CMD_LOGIN_NEW, sizeof(MSG_LOGIN_REQ_NEW));
    if (!msg)
    {
        LOG_ERROR("[cmd] alloc login new message failed!");
        return -1;
    }

    msg->version = _htonl(setting.defaultConf.version);
    msg->deviceType = setting.defaultConf.productType;

    memcpy(msg->IMEI, setting_getIMEI(), MAX_IMEI_LENGTH);
    memcpy(msg->IMSI, setting_getIMSI(), MAX_IMSI_LENGTH);

    LOG_DEBUG("[cmd] send login new message.");
    socket_sendDataDirectly(msg, sizeof(MSG_LOGIN_REQ_NEW));
    setting_setRebootType(REBOOT_NULL);
    return 0;
}

int cmd_Heartbeat(void)
{
    DATA *pData = data_getData();
    int32_t msgLen = sizeof(MSG_HEADER) + sizeof(short);
    MSG_PING_REQ *msg = alloc_msg(CMD_PING, msgLen);

    int rssi = 0, ber = 0;
    fibo_get_csq(&rssi, &ber);
    LOG_DEBUG("%d %d", rssi, ber);
    msg->gsm = rssi;

    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && pData->staticBikeBat_mV != 0)
    {
        msg->voltage = (u8)(pData->staticBikeBat_mV / 1000.f + 0.5);
    }
    else
    {
        msg->voltage = (u8)(pData->vehicleBattery_mV / 1000.f + 0.5);
    }

    int32_t rc = socket_sendDataDirectly(msg, msgLen);

    /*发送成功则记录一次*/
    if(rc >= 0)
    {
        pData->heartBeatLostTimes++;
    }

    /*发送出去2条都没有收到回复, 认为socket异常了*/
    if(pData->heartBeatLostTimes >= (2 + 1))
    {
        LOG_ERROR("heartbeat lost times error.");
        socket_initial();
        pData->heartBeatLostTimes = 0;
    }
    return rc;
}

int cmd_status_v4(void)
{
    uint16_t result = 0;
    float Templongitude;
    float Templatitude;
    DATA *pData = data_getData();
    uint8_t msgLen = sizeof(MSG_GPS_V4) ;
    MSG_GPS_V4* msg = (MSG_GPS_V4*)alloc_msg(CMD_GPS_V4, msgLen);
    uint16_t course = (uint16_t)(pData->lastPosition.nmeaInfo.direction + 0.5);
    if(!msg)
    {
        Free(msg);
        LOG_ERROR("malloc msg error");
        return -1;
    }

    result |= setting.statusConf.isDefend ? SW_MASK_DEFEND : 0;
    result |= (car_isAccOn() || setting.statusConf.acc) ? SW_MASK_ACC : 0;
    result |= car_isBackWheelLocked() ? SW_MASK_WHEEL : 0;
    result |= car_isSaddleLocked() ? SW_MASK_SEAT : 0;
    result |= car_isPowerExistence() ? SW_MASK_POWER : 0;
    result |= (pData->gpsSendPeriod_ms == setting.settingConf.freq_move * 1000) ? ST_MASK_FREQ : 0;
    result |= pData->isMoving ? ST_MASK_MOVE : 0;
    result |= pData->isWheelSpinning ? ST_MASK_WHEEL : 0;
    result |= car_isHelmetLocked() ? 0 : ST_MASK_UNHELMET;
    result |= pData->mode == MODE_SLEEP ? ST_MASK_SLEEP : 0;
    result |= setting.defaultConf.isMoveAlarmOn ? ST_MASK_DISTURB : 0;
    result |= setting.defaultConf.isOverSpeedOn ? ST_MASK_ISOVERSPEED : 0;
    result |= gps_getPosition()->isGPS ? 0 : ST_MASK_ISGPSUNFIXED;
    result |= setting.settingConf.isFenceEnable ? ST_MASK_ISFENCEENABLE : 0;
    result |= pData->isOutOfPoly ? ST_MASK_ISOUTOFSERVAERA : 0;

    msg->sw = _htons(result);
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && pData->staticBikeBat_mV != 0)
    {
        msg->voltage = _htonl(pData->staticBikeBat_mV);
    }
    else
    {
        msg->voltage = _htonl(pData->vehicleBattery_mV);
    }
    int rssi = 0, ber = 0;
    fibo_get_csq(&rssi, &ber);
    msg->gsm = rssi;

    if(pData->lastPosition.isGPS) //有GPS定位优先发
    {
        Templongitude = (float)nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lon);
        Templatitude = (float)nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lat);

        //patch 调试定位精度异常漂移的问题
        if(Templongitude < 70.0 || Templongitude > 140.0
        || Templatitude < 0.0 || Templatitude > 60.0)
        {
            LOG_ERROR("[CMD] NEMA Filtered");
            LOG_INFO("[CMD] lat(%lf) lon(%lf)", Templatitude, Templongitude);
            cmd_nmea_UDP();
            data_getData()->gps_statusFilter++;
            memset(&msg->timestamp, 0, 20);
        }
        else
        {
            msg->timestamp = _htonl(pData->lastPosition.timestamp);
            msg->speed = (uint8_t)(pData->lastPosition.nmeaInfo.speed + 0.5);
            msg->course = _htons(course);
            msg->hdop = pData->lastPosition.nmeaInfo.HDOP;
            msg->satellite = (uint8_t)(pData->lastPosition.nmeaInfo.satinfo.inuse);
            msg->longitude = Templongitude;
            msg->latitude = Templatitude;
        }

    }
    pData->isNewGPS = L_TRUE;
    return socket_sendDataDirectly(msg, msgLen);
}

static int cmd_status_v6(void)
{
    u32 result = 0;
    DATA *pData = data_getData();
    u8 msgLen = sizeof(MSG_GPS_V6);
    u8 tmp = (3 + 4); //电池电压+控制器速度上报
    u8 offset = 0;

    if(setting.settingConf.gpsType == GPS_UBLOX_M8U || setting.settingConf.accleType == ACCLE_MPU6500) //定向停车方案产品
    {
        tmp += 4;
    }

    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
    {
        if(16 == data_getData()->cardIDlen) //上报RFID卡号时，cardIDlen为16个字节
        {
            tmp += data_getData()->cardIDlen + 2;
        }
        else if(2 == data_getData()->cardIDlen)//上报RFID错误码时，cardIDlen为2个字节
        {
            tmp += data_getData()->cardIDlen + 2;
        }
        else //不上报RFID信息
        {
            tmp += 0;
        }
    }

	if(setting.defaultConf.helmetType != TYPE_NOHELMET) //有头盔锁的产品
	{
        tmp += 3;
    }

    MSG_GPS_V6 *msg = (MSG_GPS_V6 *)alloc_msg(CMD_GPS_V6, msgLen + tmp);

    if(!msg)
    {
        LOG_ERROR("malloc msg error");
        return -1;
    }

    result |= setting.statusConf.isDefend ? SW_MASK_DEFEND : 0;
    result |= (car_isAccOn() || setting.statusConf.acc) ? SW_MASK_ACC : 0;
    result |= car_isBackWheelLocked() ? SW_MASK_WHEEL : 0;
    result |= car_isSaddleLocked() ? SW_MASK_SEAT : 0;
    result |= car_isPowerExistence() ? SW_MASK_POWER : 0;
    result |= (pData->gpsSendPeriod_ms == setting.settingConf.freq_move * 1000) ? ST_MASK_FREQ : 0;
    result |= pData->isMoving ? ST_MASK_MOVE : 0;
    result |= pData->isWheelSpinning ? ST_MASK_WHEEL : 0;
    result |= car_isHelmetLocked() ? 0 : ST_MASK_UNHELMET;
    result |= pData->mode == MODE_SLEEP ? ST_MASK_SLEEP : 0;
    result |= setting.defaultConf.isMoveAlarmOn ? ST_MASK_DISTURB : 0;
    result |= setting.defaultConf.isOverSpeedOn ? ST_MASK_ISOVERSPEED : 0;
    result |= gps_getPosition()->isGPS ? 0 : ST_MASK_ISGPSUNFIXED;
    result |= setting.settingConf.isFenceEnable ? ST_MASK_ISFENCEENABLE : 0;
    result |= pData->isOutOfPoly ? ST_MASK_ISOUTOFSERVAERA : 0;

    msg->sw = _htonl(result);

    int rssi = 0, ber = 0;
    fibo_get_csq(&rssi, &ber);
    msg->gsm = (u8)rssi;

    msg->voltage = _htonl(pData->vehicleBattery_mV);
    msg->timestamp = _htonl(pData->lastPosition.timestamp);
    msg->longitude = _htonl(gps_getGPSU32(pData->lastPosition.nmeaInfo.lon));
    msg->latitude = _htonl(gps_getGPSU32(pData->lastPosition.nmeaInfo.lat));
    msg->speed = _htons((u16)(pData->lastPosition.nmeaInfo.speed + 0.5));
    msg->course = _htons((u16)(pData->lastPosition.nmeaInfo.direction + 0.5));
    msg->hdop = _htons((u16)(pData->lastPosition.nmeaInfo.HDOP * 100 + 0.5));
    msg->satellite = (u8)(pData->lastPosition.nmeaInfo.satinfo.inuse);
    msg->totalMiles = _htonl(setting.statusConf.totalMiles);
    msg->fenceVersion = _htonl(setting.settingConf.fenceVersion);

    u16 etcSpeed = data_getRealEtcSpeed();
    msg->reserve[offset++] = 3; //type 控制器速度
    msg->reserve[offset++] = 2; //len
    msg->reserve[offset++] = (u8)(etcSpeed >> 8 & 0xFF);
    msg->reserve[offset++] = (u8)(etcSpeed & 0xFF);

    if(setting.settingConf.gpsType == GPS_UBLOX_M8U || setting.settingConf.accleType == ACCLE_MPU6500) //需要上报方向角的产品
    {
        s16 orientation = data_getHeadingAngle(); //将方向角转换为保留1位小数的整数形式
        msg->reserve[offset++] = 9; //type
        msg->reserve[offset++] = 2; //len
        msg->reserve[offset++] = (u8)(orientation >> 8 & 0xFF);
        msg->reserve[offset++] = (u8)(orientation & 0xFF);
    }

    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
    {
        if(data_getData()->cardIDlen > 0) //设防或者断大电时不上报RFID信息
        {
            msg->reserve[offset++] = 5; //type
            msg->reserve[offset++] = data_getData()->cardIDlen; //len
            
            if(16 == data_getData()->cardIDlen)
            {
                for(int i = 0; i < data_getData()->cardIDlen; i++)
                {
                    msg->reserve[offset++] = data_getData()->cardID[i];
                }
            }
            else if(2 == data_getData()->cardIDlen)
            {
                msg->reserve[offset++] = (u8)(pData->RFID_ErrorCode >> 8 & 0xFF); //RFID错误码
                msg->reserve[offset++] = (u8)(pData->RFID_ErrorCode & 0xFF);
            }
        }
    }
    msg->reserve[offset++] = 10; //type
    msg->reserve[offset++] = 1; //len
    msg->reserve[offset++] = pData->voltageState; //电池电压ADC准否

	if(setting.defaultConf.helmetType != TYPE_NOHELMET) //有头盔锁的产品
    {
        u8 helmetLockState = 0;
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            helmetLockState |= ST_HELMET_TYPE;
            helmetLockState |= car_isHelmetClose() ? ST_HELMET_LOCKDETECT : 0;
            helmetLockState |= car_isHelmetAtPos() ? ST_HELMET_PINDETECT : 0;
        }
        else
        {
            helmetLockState |= car_isHelmetLocked() ? ST_HELMET_PINDETECT : 0;
        }
        helmetLockState |= car_isHelmetConnected() ? ST_HELMET_CONNECTDETECT_SW : 0;
        msg->reserve[offset++] = 11; //type
        msg->reserve[offset++] = 1; //len
        msg->reserve[offset++] = helmetLockState; //len
    }

    msgLen += tmp;
    pData->isNewGPS = L_TRUE;
    pData->lastPosition.tagTimestamp = 0; //发送后清空最佳定位以便下个周期记录新的定位
    memset(&pData->lastPosition.tagNmeaInfo, 0, sizeof(nmeaINFO));

    return socket_sendDataDirectly(msg, msgLen);
}

int cmd_status(void)
{
    if(!socket_isLogined())
    {
        LOG_ERROR("socket has not login.");
        return -1;
    }

    if(setting_getVerisonType() == VERSION_TYPE_MX5K6   || setting_getVerisonType() == VERSION_TYPE_MX5K6_DD
    || setting_getVerisonType() == VERSION_TYPE_MX5F6_DD || setting_getVerisonType() == VERSION_TYPE_MX5K6_LS
    || setting_getVerisonType() == VERSION_TYPE_MX5D3_RF || setting_getVerisonType() == VERSION_TYPE_MX5Y6_DD
    || setting_getVerisonType() == VERSION_TYPE_MX5H6_DD || setting_getVerisonType() == VERSION_TYPE_MX5H7_DD
    || setting_getVerisonType() == VERSION_TYPE_MX5F7_DD || setting_getVerisonType() == VERSION_TYPE_MX5K7_DD
    || setting_getVerisonType() == VERSION_TYPE_MX5K8_RF || setting_getVerisonType() == VERSION_TYPE_MX5Y6_RF
    || setting_getVerisonType() == VERSION_TYPE_MX5F6_RF || setting_getVerisonType() == VERSION_TYPE_MX5F7_RF
    || setting_getVerisonType() == VERSION_TYPE_MX5H7_RF || setting_getVerisonType() == VERSION_TYPE_MX5K6_RF
    || setting_getVerisonType() == VERSION_TYPE_MX5Y3_XL_CC || setting_getVerisonType() == VERSION_TYPE_MX5X5
    || setting_getVerisonType() == VERSION_TYPE_MX5F5 || setting_getVerisonType() == VERSION_TYPE_MX5F8
    || setting_getVerisonType() == VERSION_TYPE_MX5K4_RF || setting_getVerisonType() == VERSION_TYPE_MX5K7_RF)
    {
        return cmd_status_v6(); //走V6逻辑
    }
    else
    {
        return cmd_status_v4();
    }
}

int cmd_notify(u8 notifyType, u8 notifyValue)
{
    MSG_NOTIFY_REQ *socket_msg = alloc_msg(CMD_NOTIFY, sizeof(MSG_NOTIFY_REQ));
    if(!socket_msg)
    {
        LOG_ERROR("alloc message failed!");
        return -1;
    }

    socket_msg->notifyType = notifyType;
    socket_msg->notifyValue = notifyValue;

    socket_sendDataDirectly(socket_msg, sizeof(MSG_NOTIFY_REQ));
    return 0;
}

int cmd_notify_V2(u16 notifyType, u16 payload, u32 reserved)
{
    MSG_NOTIFY_V2_REQ* socket_msg = alloc_msg(CMD_NOTIFY_V2, sizeof(MSG_NOTIFY_V2_REQ));
    if (!socket_msg)
    {
        LOG_ERROR("alloc message failed!");
        return -1;
    }

    socket_msg->notifyType = notifyType;
    socket_msg->payload = payload;
    socket_msg->reserved = reserved;

    socket_sendDataDirectly(socket_msg, sizeof(MSG_NOTIFY_V2_REQ));
    return 0;
}

int cmd_submitBMSInfo(void) //上报BMS信息
{
    DATA *pData = data_getData();
    u8 msgLen = sizeof(MSG_BMS_INFO_CMD);
    MSG_BMS_INFO_CMD *msg = NULL;

    //如果不通过ETC获取SOC且bms信息为空，或通过ETC获取SOC且soc信息为空则不上报
    if((!setting.settingConf.isEtcSOC && 0 == memcmp("\x00\x00\x00\x00\x00\x00", pData->bms.SN, 6))
    || (setting.settingConf.isEtcSOC && 0 == setting.statusConf.bmsSoc))
    {
        LOG_DEBUG("[CMD] noBMSInfo ");
        return -1;
    }

    msg = alloc_msg(CMD_BMS_INFO, msgLen);
    if(!msg)
    {
        LOG_ERROR("[CMD] bms malloc msg error");
        return -1;
    }

    if(setting.defaultConf.bmsType == TYPE_XINGHENGBMS)
    {
        memcpy(msg->sn, pData->bms.SN, sizeof(msg->sn));
        msg->hardVersion = _htons(pData->bms.hardwareVer);
        msg->softVersion = _htons(pData->bms.softwareVer);
        msg->MOSTemp = _htons(pData->bms.temperature);
        msg->MOSState = 0x00;
        msg->maxVoltage = 0x00;
        msg->minVoltage = 0x00;
        msg->healthState = pData->bms.health;
        msg->fault = 0x00;
        msg->capacity = _htons(pData->bms.capacity);
        msg->remainCapacity = _htons(pData->bms.remainCapacity);
        msg->SOC = setting.statusConf.bmsSoc;
        msg->cycle = _htons(pData->bms.cycleCount);
        msg->voltage = _htons(pData->bms.voltage);
        msg->current = _htons(pData->bms.current * 100);
        msg->timestamp = _ntohl((u32)rtc_getTimestamp());
    }
    else if(setting.defaultConf.bmsType == TYPE_XIAOANBMS)
    {
        memcpy(msg->sn, pData->bms.SN, sizeof(msg->sn));
        msg->hardVersion = _htons(pData->bms.hardwareVer);
        msg->softVersion = _htons(pData->bms.softwareVer);
        msg->MOSTemp = _htons(pData->bms.MOSTemperature);
        msg->MOSState = pData->bms.mosfetState;
        msg->maxVoltage = pData->bms.cellVoltageMax / 100;
        msg->minVoltage = pData->bms.cellVoltageMin / 100;
        msg->healthState = 100; //暂无电池健康状态，默认100
        msg->fault = _htons(pData->bms.fault);
        msg->capacity = _htons(pData->bms.capacity);
        msg->remainCapacity = _htons(pData->bms.remainCapacity);
        msg->SOC = setting.statusConf.bmsSoc;
        msg->cycle = _htons(pData->bms.cycleCount);
        msg->voltage = _htons(pData->bms.voltage);
        msg->current = _htons(pData->bms.current);
        msg->timestamp = _ntohl(pData->bms.timestamp);
    }

    if(setting.settingConf.isEtcSOC)
    {
        if(0 == memcmp("\x00\x00\x00\x00\x00\x00", pData->bms.SN, 6)) //如果不通过ETC读取BMS信息为空，则上报一线通SOC值
        {
            msg->SOC = setting.statusConf.bmsSoc;
            msg->timestamp = _ntohl((u32)rtc_getTimestamp());
        }
    }

    socket_sendDataDirectly(msg, msgLen);
    LOG_DEBUG("[CMD] submitBMSInfo ");
    return 0;
}

static u8 g_isFirstUdp = L_TRUE;

int cmd_status_UDP(void)
{
    if(!socket_isPDPActived())
    {
        return -1;
    }
    
    LOG_DEBUG("[CMD] ************************************************* UDP status");
    if(g_isFirstUdp) //启动后第一次发送登录包 附带IMSI信息
    {
        s32 rc = 0;
        u16 msgLen = 0;
        MSG_UDP_STATUS *msg = NULL;
        MSG_U32_VALUE versionNum;
        TLV_DATA_HEADER *tlv_header = tlv_createHeader();
        if(!tlv_header)
        {
            return -1;
        }

        tlv_addData(&tlv_header, TLV_UDP_IMSI, setting_getIMSI(), MAX_IMSI_LENGTH);

        tlv_addData(&tlv_header, TLV_UDP_CCID, setting_getCCID(), MAX_CCID_LENGTH);

        versionNum.val = _htonl(setting.defaultConf.version);
        tlv_addData(&tlv_header, TLV_UDP_VERSION, &versionNum, sizeof(MSG_U32_VALUE));

        int iCfgSize = 0;
        char *pCfgTlv = (char *)setting_allocConfig(&iCfgSize);
        tlv_addData(&tlv_header, TLV_UDP_CONFIG, pCfgTlv, iCfgSize);
        free(pCfgTlv);

        msgLen = sizeof(MSG_UDP_STATUS) + tlv_header->payloadLen;
        msg = (MSG_UDP_STATUS *)Malloc(msgLen);
        if(!msg)
        {
            tlv_deleteHeader(tlv_header);
            return -1;
        }

        msg->header.signature = _htons(START_FLAG_UDP);
        msg->header.cmd = CMD_UDP_TLV;

        memcpy(msg->header.imei, setting_getIMEI(), MAX_IMEI_LENGTH);
        msg->header.length = _htons(msgLen - MSG_UDP_HEADER_LEN);
        memcpy(msg->tlv, tlv_header->payload, tlv_header->payloadLen);
        rc = socket_sendDatawithUDP(msg, msgLen);
        if(rc >= 0)
        {
            g_isFirstUdp = L_FALSE;
        }

        tlv_deleteHeader(tlv_header);
    }
    else //登录包之后发送信息状态包
    {
        u16 msgLen = 0;
        MSG_UDP_STATUS *msg = NULL;
        DATA *pData = data_getData();

        TLV_DATA_HEADER *tlv_header = tlv_createHeader();
        if(!tlv_header)
        {
            return -1;
        }

        {
            u8 deviceFault = 0;
            if(setting.statusConf.acc && !car_isAccOn())
            {
                deviceFault |= FAULT_ACC_SWICTH;
            }
            tlv_addData(&tlv_header, TLV_UDP_DEVICEFAULT, &deviceFault, sizeof(u8));
        }

        if(pData->lastPosition.isGPS)//有GPS的时候发送GPS
        {
            GPS gps = {0};
            MSG_U16_VALUE course;
            course.val = (u16)(pData->lastPosition.nmeaInfo.direction + 0.5);
            gps.timestamp = _htonl(pData->lastPosition.timestamp);
            gps.latitude = gps_getGPSValue(pData->lastPosition.nmeaInfo.lat);
            gps.longitude = gps_getGPSValue(pData->lastPosition.nmeaInfo.lon);
            gps.course = _htons(course.val);
            gps.speed = (u8)(pData->lastPosition.nmeaInfo.speed);
            tlv_addData(&tlv_header, TLV_UDP_GPS, &gps, sizeof(GPS));
        }
        {

            MSG_U16_VALUE volt;
            volt.val = pData->smallBattery_mV;
            volt.val = _htons(volt.val);

            tlv_addData(&tlv_header, TLV_UDP_VBATTERY, &volt, sizeof(u16));
        }
        {
            MSG_U32_VALUE volatge_mV;
            volatge_mV.val = pData->vehicleBattery_mV;
            volatge_mV.val = _htonl(volatge_mV.val);

            tlv_addData(&tlv_header, TLV_UDP_VCAR, &volatge_mV, sizeof(u32));
        }
        {
            int rssi = 0, beri = 0;
            fibo_get_csq(&rssi, &beri);
            u8 gsm = rssi;
            u8 ber = beri;
            tlv_addData(&tlv_header, TLV_UDP_GSM, &gsm, sizeof(u8));
            tlv_addData(&tlv_header, TLV_UDP_BER, &ber, sizeof(u8));
        }

        int iCfgSize = 0;
        char *pCfgTlv = (char *)setting_allocConfig(&iCfgSize);
        tlv_addData(&tlv_header, TLV_UDP_CONFIG, pCfgTlv, iCfgSize);
        free(pCfgTlv);

        msgLen = sizeof(MSG_UDP_STATUS) + tlv_header->payloadLen;
        msg = (MSG_UDP_STATUS *)Malloc(msgLen);
        if(!msg)
        {
            tlv_deleteHeader(tlv_header);
            return -1;
        }

        msg->header.signature = _htons(START_FLAG_UDP);
        msg->header.cmd = CMD_UDP_TLV;
        memcpy(msg->header.imei, setting_getIMEI(), MAX_IMEI_LENGTH);
        msg->header.length = _htons(msgLen - MSG_UDP_HEADER_LEN);
        memcpy(msg->tlv, tlv_header->payload, tlv_header->payloadLen);
        socket_sendDatawithUDP(msg, msgLen);
        tlv_deleteHeader(tlv_header);
    }
    return 0;
}


/*
 * print message via UDP
 *
 * Note:
 *      the message length is limited to 1023 bytes
 */
int cmd_printUDP(const char *fmt, ...)
{
    static unsigned char *buf = NULL;

    if(!buf)
    {
        buf = Malloc(1024);
    }

    if(buf)
    {
        int msgLen = 0;
        int payLoadLen = 0;
        MSG_UDP_STATUS *msg = NULL;
        
        memset(buf, 0, 1024);

        va_list arg;
        va_start (arg, fmt);
        vsnprintf((char *)buf, 1023, fmt, arg);

        //拿到payload和payloadLen
        payLoadLen = strlen((const char *)buf);
        payLoadLen = payLoadLen > 1023 ? 1023 : payLoadLen;
        if(buf[payLoadLen - 1] != '\n')buf[payLoadLen - 1] = '\n';


        //打包数据
        msgLen = sizeof(MSG_UDP_STATUS) + payLoadLen;
        msg = (MSG_UDP_STATUS *)Malloc(msgLen);
        if(!msg)
        {
            return -1;
        }
        msg->header.signature = _htons(START_FLAG_UDP);
        msg->header.cmd = CMD_UDP_LOG_NEW;
        memcpy(msg->header.imei, setting_getIMEI(), MAX_IMEI_LENGTH);
        msg->header.length = _htons(msgLen - MSG_UDP_HEADER_LEN);
        memcpy(msg->tlv, buf, payLoadLen);

        //发送数据
        socket_sendDatawithUDP(msg, msgLen);
        
        va_end(arg);
    }
    return 0;
}


int cmd_nmea_UDP(void)
{
    cJSON *result = NULL;
    cJSON *json_root = NULL;

    result = cJSON_CreateObject();
    if(!result)
    {
        return L_FALSE;
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        return L_FALSE;
    }

    cJSON_AddNumberToObject(json_root, "code", 0);
    cJSON_AddStringToObject(result, "nmea", (const char *)gps_getLastNMEA_str());
    cJSON_AddItemToObject(json_root, "result", result);

    char *buffer = cJSON_PrintUnformatted(json_root);
    if(!buffer)
    {
        cJSON_Delete(json_root);
        return L_FALSE;
    }
    cJSON_Delete(json_root);

    int length = sizeof(MSG_DEVICE_RSP) + strlen(buffer);
    MSG_DEVICE_RSP *msg = myTestMalloc(length);
    if(msg)
    {
        memset(msg, 0, length);
        msg->header.signature = 0xA5A5;
        msg->header.cmd = 0;
        msg->header.seq = 0;
        msg->header.length = _htons(length - MSG_HEADER_LEN);
    }
    strncpy(msg->data, buffer, strlen(buffer));
    socket_sendDatawithUDP(msg, length);

    Free(buffer);
    return L_TRUE;
}

static int request_timer_cb(void)
{
    cmd_status_UDP();
    return timer_startRepeat(TIMER_SEND_UDP, TIMER_M, 60, cmd_status_UDP); //1h
}

int request_initail(void)
{
    device_initail(); //下行命令初始化
    timer_start(TIMER_SEND_UDP, TIMER_S, 30, request_timer_cb);
    return 0;
}

