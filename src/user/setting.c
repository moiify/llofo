/*
 * setting.c
 *
 *  Created on: 2020/04/09
 *      Author: lc
 */
#include <string.h>
#include <stdio.h>

#include "cJSON/cJSON.h"
#include "config/default_config.txt"

#include "log.h"
#include "car.h"
#include "tlv.h"
#include "msg.h"
#include "data.h"
#include "types.h"
#include "flash.h"
#include "socket.h"
#include "version.h"
#include "user_fs.h"
#include "user_at.h"
#include "setting.h"
#include "user_timer.h"
#include "request.h"
#include "userMsg.h"
#include "rtc.h"
#include "utils.h"
#include "audio_driver.h"
#include "http.h"

#define TAG_LOGLEVEL            "loglevel"
//for server tag
#define TAG_SERVER              "SERVER"
#define TAG_ADDR_TYPE           "ADDR_TYPE"
#define TAG_ADDR                "ADDR"
#define TAG_PORT                "PORT"


//for setting tag
#define TAG_FVERSION            "firmwareVer"
#define TAG_TYPENAME            "typename"
#define TAG_TYPEINDEX           "typeindex"

#define TAG_DEFENDVA            "defendVa"
#define TAG_STATUSVA            "statusVa"
#define TAG_ACC                 "isAcc"
#define TAG_DEFEND              "isDefend"
#define TAG_FENCE_SWITCH        "fenceSW"
#define TAG_FENCE_IGNORE        "fenceIgnore"
#define TAG_FENCE_IGNOREONCE    "fenceIgnoreOnce"
#define TAG_AUTOLOCKPERIOD      "autolockPeriod"
#define TAG_FREQ_NORM           "freq_norm"
#define TAG_FREQ_MOVE           "freq_move"
#define TAG_ISSAGPS             "isAgpsEnable"
#define TAG_ISSLEEPENABLE       "isSleepEnable"
#define TAG_LOCKCARFORCE        "forceLock"
#define TAG_ISLOCKINGSADDLE     "isLockingSaddle"
#define TAG_PERIOD_TURNAUDIO    "periodTurnAudio"
#define TAG_TURNANGLE           "turnAngle"
#define TAG_PROTECT_VOLTAGE     "protectVoltage"
#define TAG_RESTORE_VOLTAGE     "restoreVoltage"
#define TAG_AUDIOTYPE           "audioType"
#define TAG_ETCSOC              "isEtcSOC"
#define TAG_ACTIVEFREQSOC       "activeFreqSOC"
#define TAG_TOKEN               "token"
#define TAG_BLENAME             "bleName"
#define TAG_TBEACONRSSI         "beaconRssi"
#define TAG_ISMX5EEAUDIO1K      "isMX5EEAudio1K"

#define TAG_ETC_ISSLOWSTART     "etcIsSlowStart"
#define TAG_ETC_LIMITCURRENT    "etcLimitCurrent"
#define TAG_ETC_PROTECTVOLTAGE  "etcProtectVoltage"
#define TAG_ETC_FUNCSWICTH      "etcFuncSwitch"
#define TAG_ETC_UPGRADE_FLAG         "etcUpgradeFlag"
#define TAG_ETC_VERSION              "etcVersion"
#define TAG_ETC_UPGRADE_VERSION      "etcUpgradeVersion"
#define TAG_ETC_FW_CRC               "etcFirmwareCRC"
#define TAG_IS_TERMINATE_ETC_UPGRADE "isTerminateETCUpgrade"
#define TAG_ISTRANSFORMMODE         "isTransformMode"
#define TAG_BMS_UPGRADE_FLAG         "bmsUpgradeFlag"
#define TAG_BMS_VERSION              "bmsVersion"
#define TAG_BMS_UPGRADE_VERSION      "bmsUpgradeVersion"
#define TAG_BMS_FW_CRC               "bmsFirmwareCRC"
#define TAG_BMS_SOC                  "bmsSoc"
#define TAG_BMS_PERIOD               "bmsSendPeriod"
#define TAG_IS_TERMINATE_BMS_UPGRADE "isTerminateBMSUpgrade"
#define TAG_OVERSPEEDPERIOD      "checkoverSpeedPeriod"
#define TAG_OVERSPEEDVOLUME      "overSpeedVolume"
#define TAG_OVERSPEEDURL         "overSpeedUrl"
#define TAG_OVERSPEEDCRC         "overSpeedCrc"
#define TAG_MOVETHRESHOLD        "moveThreshold"
#define TAG_DEV_INSTALLMODE      "devInstallMode"
#define TAG_COREUPCOUNT          "coreUpdateCount"
#define TAG_GPSBAUDUPDATE_FLAG   "gpsBaudrateUpdateFlag"
#define TAG_IS_ETC_ACC_PROTECT      "isEtcAccProtect"
#define TAG_IS_ETC_DEFEND_PROTECT   "isEtcDefendProtect"
#define TAG_RFID_ENABLE          "isRFIDEnable"
#define TAG_IS_DEFAULT_SPEED     "isDefaultSpeed"
#define TAG_IS_NMEA_OUT          "isNmeaOut"
#define TAG_HELMET_TARGET_STATUS "helmetTargetStatus"
#define TAG_APNNAME              "apnname"
#define TAG_USERNAME             "username"
#define TAG_PASSWORD             "password"

#define TAG_RGBISREPEAT            "rgbLedIsRepeat"
#define TAG_RGBLEDISTRIGGER        "rgbLedIsTrigger"
#define TAG_RGBLEDREPEATISON       "rgbLedIsOn"
#define TAG_RGBLEDREPEATTYPE       "rgbLedRepeatType"
#define TAG_RGBLEDMODE             "rgbLedRepeatMode"
#define TAG_RGBLEDDURATION         "rgbLedDuration"

#define TAG_RGBLEDTRIGGERTYPE       "rgbLedTriggerType"
#define TAG_RGBLEDTRIGGERMODE       "rgbLedTriggerMode"
#define TAG_RGBLEDREMAINTIME        "rgbLedRemainTime"

#define TAG_RGBLEDSTART            "rgbLedRepeatStart"
#define TAG_RGBLEDEND              "rgbLedRepeatEnd"

//for default
#define TAG_CCUTYPE              "ccutype"
#define TAG_BMSTYPE              "bmstype"
#define TAG_SADDLETYPE           "saddletype"
#define TAG_BACKWHEELTYPE        "backwheeltype"
#define TAG_HELMETTYPE           "helmettype"
#define TAG_LIGHTTYPE            "lighttype"
#define TAG_BATTVTYPE            "batterytype"
#define TAG_ISOVERSPEEDON        "isOverSpeedOn"
#define TAG_ISMOVEALARMON        "isMoveAlarmOn"
#define TAG_AUDIORATIO           "audioRatio"
#define TAG_ISNIGHTVOICEON       "isNightVoiceOn"
#define TAG_ISSHARKALON          "isShakeAlarmOn"
#define TAG_ISAUTOLOCKON         "isAutolockOn"
#define TAG_ETC_SPEED            "etcSpeed"
#define TAG_ISTURNENABLE         "isTurnEnable"
#define TAG_ETC_SPEED_SOURCE     "etcSpeedSource"
#define TAG_ETC_SPEED_RATIO      "etcSpeedRatio"
#define TAG_ETC_HALL_RATIO       "etcHallRatio"
#define TAG_IS_ETC_OVERSPEED_BIT "isEtcOverspeedBit"
#define TAG_OVERSPEED_THRESHOLD  "overspeedThreshold"

#define TAG_REBOOT_TYPE         "RebootType"
#define TAG_ISTBEACONABLE       "tbeaconEnAble"

#define TAG_TOTALMILES          "totalMiles"
#define TAG_LASTLAT             "lastMileLat"
#define TAG_LASTLON             "lastMileLon"

//for record tag
#define TAG_ACCON_COUNT         "accOnN"
#define TAG_PWRCUT_COUNT        "pwrCutN"
#define TAG_REBOOT_COUNT        "rebootN"
#define CMD_STRING_SERVER       "server"

#define TLV_TAG_CONVERSION    0xF0
#define TLV_TAG_PRONAME       0xF1
#define TLV_TAG_PROTYPE       0xF2

#pragma pack(push, 1)

typedef struct
{
    short head_sign;
    u8*   tlvpayload;
    u8    tail_sign;
} jasonConf_t;

typedef struct
{
    u8  tag;
    u8  len;
    u8 payload;
} tLvType_t;


typedef enum
{
    TYPE_UNSIGNED,
    TYPE_SIGNED
} USER_NUMBER_TYPE;

#pragma pack(pop)

SETTING setting;

//for debug purpose: to change the server configuration via UART

__attribute__((unused)) static int setting_changeServer(const unsigned char* cmdString, unsigned short length)
{
    char address[MAX_DOMAIN_NAME_LEN] = {0};
    int ip[4] = {0};
    int port = 0;
    int count = 0;
    u8 rc = L_FALSE;

    const char *serverString = string_bypass((const char *)cmdString, CMD_STRING_SERVER);
    serverString = (const char *)string_trimLeft((const u8*)serverString);

    count = sscanf(serverString, "%[^:]:%d", address, &port);
    if (count != 2)
    {
        LOG_DEBUG("format not correct, should be like 'server 10.11.12.23:9876' or 'server server.xiaoan.com:9876'");
        return -1;
    }

    count = sscanf(address, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
    if (4 == count)   // ip
    {
        if (ip[0] <= 255 && ip[1] <= 255 && ip[2] <= 255 && ip[3] <= 255)//validity check
        {
            setting.serverConf.addr_type = ADDR_TYPE_IP;
            setting.serverConf.ipaddr[0] = (u8) ip[0];
            setting.serverConf.ipaddr[1] = (u8) ip[1];
            setting.serverConf.ipaddr[2] = (u8) ip[2];
            setting.serverConf.ipaddr[3] = (u8) ip[3];
            setting.serverConf.port = (u16) port;

            rc = serverConf_save();
            if(rc == L_FALSE)
            {
                LOG_ERROR("change server fail");
                return -1;
            }
        }
        else
        {
            LOG_DEBUG("ip addrss format not correct!");
            return -1;
        }
    }
    else            // domain
    {
        setting.serverConf.addr_type = ADDR_TYPE_DOMAIN;
        strncpy(setting.serverConf.domain, address, MAX_DOMAIN_NAME_LEN);
        setting.serverConf.port = (u16) port;

        rc = serverConf_save();
        if(rc == L_FALSE)
        {
            LOG_ERROR("change server fail");
            return -1;
        }
    }
    setting_serverReinit();
    return 0;
}

int setting_setServerTimeout(void)
{
    /* 检查备份服务器合法性 */
    int isSrvBakOK = L_TRUE;
    if(setting.srvBakConf.addr_type == ADDR_TYPE_IP)
    {
        if(check_ip(setting.srvBakConf.ipaddr[0], setting.srvBakConf.ipaddr[1], setting.srvBakConf.ipaddr[2], setting.srvBakConf.ipaddr[3]))
        {
            isSrvBakOK = L_FALSE;
        }
        if(check_port(setting.srvBakConf.port))
        {
            isSrvBakOK = L_FALSE;
        }
    }
    else if(setting.srvBakConf.addr_type == ADDR_TYPE_DOMAIN)
    {
        if(check_port(setting.srvBakConf.port))
        {
            isSrvBakOK = L_FALSE;
        }
    }

    if(isSrvBakOK == L_TRUE)
    {
        /* 备份服务器合法，则切回备份服务器 */
        memcpy(&setting.serverConf, &setting.srvBakConf, sizeof(SERVER_CONF));
    }
    else if(isSrvBakOK == L_FALSE)
    {
        /* 备份服务器不合法，则设置为默认服务器 */
        setting.serverConf.port = 9880;
        setting.serverConf.ipaddr[0] = 112;
        setting.serverConf.ipaddr[1] = 74;
        setting.serverConf.ipaddr[2] = 77;
        setting.serverConf.ipaddr[3] = 182;
        setting.serverConf.addr_type = ADDR_TYPE_IP;

        setting.srvBakConf.port = 9880;
        setting.srvBakConf.ipaddr[0] = 112;
        setting.srvBakConf.ipaddr[1] = 74;
        setting.srvBakConf.ipaddr[2] = 77;
        setting.srvBakConf.ipaddr[3] = 182;
        setting.srvBakConf.addr_type = ADDR_TYPE_IP;
    }

    serverConf_save(); //超时则恢复原来服务器
    LOG_INFO("device_setServerTimeout");
    setting_serverReinit();
    return 0;
}

s64 setting_getNumber(ST_FLASH_DATA *data, USER_NUMBER_TYPE type)
{
    s64 number = 0;
    switch(data->len)
    {
        case 1:
        {
            if(type == TYPE_UNSIGNED)
            {
                MSG_U8_VALUE *u8_value = (MSG_U8_VALUE *)data->value;
                number = u8_value->val;
            }
            else
            {
                MSG_S8_VALUE *u8_value = (MSG_S8_VALUE *)data->value;
                number = u8_value->val;
            }
        }
        break;

        case 2:
        {
            if(type == TYPE_UNSIGNED)
            {
                MSG_U16_VALUE *u16_value = (MSG_U16_VALUE *)data->value;
                number = u16_value->val;
            }
            else
            {
                MSG_S16_VALUE *u16_value = (MSG_S16_VALUE *)data->value;
                number = u16_value->val;
            }
        }
        break;

        case 4:
        {
            if(type == TYPE_UNSIGNED)
            {
                MSG_U32_VALUE *u32_value = (MSG_U32_VALUE *)data->value;
                number = u32_value->val;
            }
            else
            {
                MSG_S32_VALUE *u32_value = (MSG_S32_VALUE *)data->value;
                number = u32_value->val;
            }
        }
        break;

    }

    return number;
}

int setting_serverReinit(void)
{
    LOG_INFO("setting_serverReinit");
    socket_initial();
    return 0;
}

u8 setting_isDefendOn(void)
{
    return setting.statusConf.isDefend != L_FALSE ? L_TRUE : L_FALSE;
}

SETTING_RESULT setting_setDefend(u8 defendState)
{
    SETTING_RESULT result = SETTING_SUCCESS;

    if(defendState)
    {
        //未设防状态或者电门打开状态下 执行设防 + 关闭电门操作
        if(!setting_isDefendOn() || setting_isAccOn())
        {
            if(data_getData()->isWheelSpinning)
            {
                result = SETTING_NOTSTOP;
            }
            else
            {
                setting.statusConf.acc = L_FALSE;
                setting.statusConf.isDefend = L_TRUE;
                car_accOff();
                car_lockElectricalBrake();
                if(!car_isBackWheelLocked())
                {
                    car_lockBackWheel();
                }
                car_lightOperate(L_FALSE);

                result = SETTING_SUCCESS;
                event_checkActiveFreqSOC(); //从撤防到设防则重启主动获取SOC定时器
            }
        }
        else
        {
            car_accAction();
            result = SETTING_ALREADY;
        }
    }
    else
    {
        if(setting_isDefendOn() || setting_isAccOn())
        {
            //之前不处于当前状态 执行操作 并上报告警
            setting.statusConf.acc = L_FALSE;
            setting.statusConf.isDefend = L_FALSE;

            car_accOff();
            car_unlockElectricalBrake();
            if(car_isBackWheelLocked())
            {
                car_unlockBackWheel();
            }
            car_lightOperate(L_FALSE);

            result = SETTING_SUCCESS;
            event_checkActiveFreqSOC(); //从设防到撤防则关闭获取SOC定时器
        }
        else
        {
            car_accAction();
            result = SETTING_ALREADY;
        }
    }

    if(result == SETTING_SUCCESS || result == SETTING_ALREADY)
    {
        if(setting.settingConf.isIgnoreFenceOnce) //首次操作跳过电子围栏
        {
            setting.settingConf.isIgnoreFenceOnce = L_FALSE;
        }
        else //不是首次操作 不忽略电子围栏
        {
            setting.settingConf.isIgnoreFence = L_FALSE;
        }
    }

    if(setting.statusConf.Cnt_autoLockTime != 0)
    {
        setting.statusConf.Cnt_autoLockTime = 0;
    }
    data_resetVibrationTime();

    if(result == SETTING_SUCCESS)
    {
        result = statusConf_save();
    }
    return result;
}

SETTING_RESULT setting_setAcc(u8 accState)
{
    SETTING_RESULT result = SETTING_SUCCESS;
    data_getData()->faultRecord.isDelayCheckAccState = TRUE; //开关电门时，延迟ACC故障检测，避免误判

    if(accState) //启动操作
    {
        if(setting.settingConf.isFenceEnable && data_getData()->fenceAreaType == OUTSERVICE_AREA)
        {
            return SETTING_OUTSERVICE; //电子围栏外，无法操作开电门
        }

        //非撤防或者电门关闭状态下 执行撤防 + 打开电门操作
        if(setting_isDefendOn() || !setting_isAccOn())
        {
            //之前不处于当前状态 执行操作
            car_accOn();
            car_unlockElectricalBrake();
            if(car_isBackWheelLocked()) //开电门情况下,再次开电门，如果检测到后轮锁到位则解锁
            {
                car_unlockBackWheel();
            }
            car_lightOperate(L_TRUE);

            setting.statusConf.accOnCount++;
            setting.statusConf.acc = L_TRUE;
            setting.statusConf.isDefend = L_FALSE;
            result = SETTING_SUCCESS;
        }
        else
        {
            car_accAction();
            result = SETTING_ALREADY;
        }
    }
    else//熄火操作
    {
        // 非撤防或者电门打开状态下 执行撤防 + 关闭电门操作
        if(setting_isDefendOn() || setting_isAccOn())
        {
            // 之前不处于当前状态 执行操作 并上报告警
            car_accOff();
            car_unlockElectricalBrake();
            car_lightOperate(L_FALSE);

            setting.statusConf.acc = L_FALSE;
            result = SETTING_SUCCESS;
        }
        else
        {
            car_accAction();
            result = SETTING_ALREADY;
        }
    }

    if(result == SETTING_SUCCESS || result == SETTING_ALREADY)
    {
        if(setting.settingConf.isIgnoreFenceOnce) //首次操作跳过电子围栏
        {
            setting.settingConf.isIgnoreFenceOnce = L_FALSE;
        }
        else //不是首次操作 不忽略电子围栏
        {
            setting.settingConf.isIgnoreFence = L_FALSE;
        }
    }

    if(setting.statusConf.Cnt_autoLockTime != 0)
    {
        setting.statusConf.Cnt_autoLockTime = 0;
    }
    data_resetVibrationTime();

    if(result == SETTING_SUCCESS)
    {
        result = statusConf_save();
    }
    return result;
}

u8 setting_isAccOn(void)
{
    return setting.statusConf.acc;
}

u8 *setting_getIMEI(void)
{
    static unsigned char imei[MAX_IMEI_LENGTH + 2] = {0};

    if(strlen((const char *)imei) == 15)
    {
        return imei;
    }
    int ret = fibo_get_imei(imei, CFW_SIM_0);
    if(ret < 0)
    {
        memset(imei, 0, MAX_IMEI_LENGTH + 2);
        return NULL;
    }
    return imei;
}

u8 *setting_getIMSI(void)
{
    if(strlen(setting.settingConf.imsi) == MAX_IMSI_LENGTH)
    {
        return setting.settingConf.imsi;
    }
    //等待setting_obtainIMSI_cb回调触发后异步写入setting.settingConf.imsi
    //为避免异步不返回，和老版本无异步接口，则直接用同步接口作为兜底
    u8 imsi[MAX_IMSI_LENGTH + 1] = {0};
    int ret = fibo_get_imsi(imsi);
    if(ret < 0)
    {
        memset(imsi, 0, MAX_IMSI_LENGTH + 1);
    }
    if(strlen(imsi) == MAX_IMSI_LENGTH && strcmp(imsi, "000000123456789") != 0) //imsi同步接口可能返回固定串
    {
        memset(setting.settingConf.imsi, 0, MAX_IMSI_LENGTH + 1);
        memcpy(setting.settingConf.imsi, imsi, MAX_IMSI_LENGTH);
        return setting.settingConf.imsi;
    }
    memset(setting.settingConf.imsi, 0, MAX_IMSI_LENGTH + 1);
    return setting.settingConf.imsi;
}

u8 *setting_getCCID(void)
{
    if(strlen(setting.settingConf.ccid) == MAX_CCID_LENGTH)
    {
        return setting.settingConf.ccid;
    }

    u8 ccid[MAX_CCID_LENGTH + 1] = {0};
    int ret = fibo_get_ccid(ccid);
    if(ret < 0)
    {
        memset(ccid, 0, MAX_CCID_LENGTH + 1);
    }
    if(strlen(ccid) == MAX_CCID_LENGTH)
    {
        memset(setting.settingConf.ccid, 0, MAX_CCID_LENGTH + 1);
        memcpy(setting.settingConf.ccid, ccid, MAX_CCID_LENGTH);
        return setting.settingConf.ccid;
    }
    memset(setting.settingConf.ccid, 0, MAX_CCID_LENGTH + 1);
    return setting.settingConf.ccid;
}

void *setting_obtainIMSI_cb(u8 *imsi)
{
#if defined(COREVERSION23) || defined(COREVERSION06)
    if(strlen((char *)imsi) == 0 || strlen((char *)imsi) != MAX_IMSI_LENGTH
    || memcmp(imsi, "000000123456789", MAX_IMSI_LENGTH) == 0)
    {
        LOG_ERROR("> getIMSI Error ");
        fibo_get_imsi_asyn(setting_obtainIMSI_cb); //获取失败则重复获取
        return NULL;
    }

    memset(setting.settingConf.imsi, 0, MAX_IMSI_LENGTH + 1);
    memcpy(setting.settingConf.imsi, imsi, MAX_IMSI_LENGTH);
    LOG_DEBUG("getIMSI Success imsi: %s", imsi);
#endif
    return NULL;
}

static void setting_checkGpsSendTimer(void)
{
    static FREQ_TYPE g_type = FREQ_NULL;

    DATA *pData = data_getData();

    FREQ_TYPE type = FREQ_MOVE;
    do
    {
        if(((!setting_isDefendOn() || car_isAccOn()) || (setting_isDefendOn() && data_getData()->isMoving)) && !data_isSleeping())//开电门+非法移动
        {
            type = FREQ_MOVE;
            break;
        }
        else //setting_isDefendOn && !car_isAccOn
        {
            type = FREQ_NORM;
            break;
        }
    }
    while(L_FALSE);

    if(type != g_type)
    {
        switch(type)
        {
            case FREQ_MOVE:
                pData->gpsSendPeriod_ms = setting.settingConf.freq_move * 1000;
                break;

            case FREQ_NORM:
                pData->gpsSendPeriod_ms = setting.settingConf.freq_norm * 1000;
                break;

            default:
                break;
        }
        LOG_DEBUG("FREQ_TYPE %d -> %d", g_type, type);
        g_type = type;
        timer_start(TIMER_SEND_GPS, TIMER_MS, 1000, cmd_statusMatchPeriod);//切换状态时发送一次报文,通知服务器状态
    }
}

int setting_listnerHandler(void)
{
    setting_checkGpsSendTimer();
    return 0;
}

static void defaultConf_ObtainJSON(void) //优先级顺序: 文件系统 > Json > 系统初始化设置
{
    jasonConf_t * confFile = (jasonConf_t *) tlv_config;
    u8 *pbuf = (u8 *)tlv_config;
    tLvType_t * temptlv = NULL;
    u16 filesize = sizeof(tlv_config);
    u8 tag, len;
    u8 *payload = NULL;
    s16 leftlen = 0;
    if(confFile->head_sign !=  _htons(START_FLAG)) //如果配置数组头不对 认为数据错误 直接返回不解析
    {
        LOG_ERROR("[Setting]  Config File Head Error");
        return;
    }

    LOG_INFO("[Setting] Find Json Config Array");
    leftlen = filesize - sizeof(confFile->head_sign);
    pbuf += sizeof(confFile->head_sign);  //pbuf偏移到tlv头
    while(leftlen > sizeof(confFile->tail_sign))//TLV解析
    {
        temptlv = (tLvType_t *)pbuf;
        tag = temptlv->tag;
        len = temptlv->len;
        payload = (u8 *)&temptlv->payload;
        //LOG_DEBUG("[Setting] tag:0x%0X len%d  payload:0x%X",temptlv->tag,temptlv->len,payload[0]);
        switch (tag)
        {
            case TLV_TAG_CONVERSION:  // "xxx.xxx.xxx" 最多11个字节
            {
                if(len && len < 12)
                {
                    u8 *pMAJOR, *pMINOR, *pMICRO = NULL;
                    u8 tempVersion [12];
                    u32 ver_MINOR = 0;
                    u32 ver_MAJOR = 0;
                    memset(tempVersion, 0, 12);
                    memcpy(tempVersion, payload, len);
                    LOG_INFO("[Setting] version:%s", tempVersion);
                    pMAJOR = tempVersion;
                    pMINOR = (u8 *)string_bypassByNum((const char *)tempVersion, ".", 1);
                    pMICRO = (u8 *)string_bypassByNum((const char *)tempVersion, ".", 2);
                    if(pMAJOR && pMINOR && pMICRO)
                    {
                        ver_MAJOR = _atoi((const char *)pMAJOR);
                        ver_MINOR = _atoi((const char *)pMINOR);
                        setting.defaultConf.version = (VERSION_MAJOR << 16) | (ver_MINOR << 8) | VERSION_MICRO;
                        LOG_INFO("[Setting] pMAJOR:%d, pMINOR:%d, pMICRO:%d", ver_MAJOR, ver_MINOR, VERSION_MICRO);
                    }
                    else
                    {
                        LOG_ERROR("[Setting] ConfigVersion Error ");
                    }
                }
            }
            break;
            case TLV_TAG_PRONAME:
            {
                if(len <= PRODUCT_NAME_LEN)
                {
                    memset(setting.defaultConf.name, 0, sizeof(setting.defaultConf.name));
                    memcpy(setting.defaultConf.name, payload, len);
                    
                    if(VERSION_MAJOR == 22) //-EE版本处理name
                    {
                        char *pStr = strstr(setting.defaultConf.name, "-BB");
                        if(!pStr)
                        {
                            pStr = strstr(setting.defaultConf.name, "-CC");
                            if(!pStr)
                            {
                                pStr = strstr(setting.defaultConf.name, "-DD");
                            }
                        }
                        if(pStr)
                        {
                            memcpy(pStr, "-EE", 3); //-BB、-CC、-DD直接转为-EE
                        }

                        pStr = strstr(setting.defaultConf.name, "-RF");
                        if(pStr)
                        {
                            char *pCheck = strstr(setting.defaultConf.name, "-RF-EE");
                            if(!pCheck)
                            {
                                memcpy(pStr, "-RF-EE", 6); //有-RF却不为-RF-EE，则修改为-RF-EE
                            }
                        }
                    }
                    LOG_INFO("[Setting] ProductName:%s", setting.defaultConf.name);
                }
            }
            break;
            case TLV_TAG_PROTYPE:
            {
                if(len == 1)
                {
                    setting.defaultConf.productType = *payload;
                    LOG_INFO("[Setting] ProductType:%d", *payload);
                }
            }
            break;
            case TYPE_ISOVERSPEEDON:
            {
                if(len == 1)
                {
                    setting.defaultConf.isOverSpeedOn = *payload;
                    LOG_INFO("[Setting] OverSpeedOn:%d", *payload);
                }
            }
            break;
            case TYPE_ISMOVEALARMON:
            {
                if(len == 1)
                {
                    setting.defaultConf.isMoveAlarmOn = *payload;
                    LOG_INFO("[Setting] MoveAlarmOn:%d", *payload);
                }
            }
            break;
            case TYPE_AUDIORATIO:
            {
                float tempfloat = *payload;
                if(len == 1)
                {
                    setting.defaultConf.audioRatio = (tempfloat / 100);
                    LOG_INFO("[Setting] audioRatio:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_ISNIGHTVOICEON:
            {
                if(len ==1 )
                {
                    setting.defaultConf.isNightVoiceOn = *payload;
                    LOG_INFO("[Setting] isNightVoiceOn:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_SADDLE:
            {
                if(len == 1)
                {
                    setting.defaultConf.saddleType = *payload;
                    LOG_INFO("[Setting] saddleType:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_BACKWHEEL:
            {
                if(len == 1)
                {
                    setting.defaultConf.backWheelType = *payload;
                    LOG_INFO("[Setting] backWheelType:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_ISSHAKEALARMON:
            {
                if(len == 1)
                {
                    setting.defaultConf.isShakeAlarmOn = *payload;
                    LOG_INFO("[Setting] isShakeAlarmOn:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_CONTROLLIGHT:
            {
                if(len == 1)
                {
                    setting.defaultConf.lightCtrlType = *payload;
                    LOG_INFO("[Setting] lightCtrlType:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_CCU:
            {
                if(len == 1)
                {
                    setting.defaultConf.ccuType = *payload;
                    LOG_INFO("[Setting] ccuType:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_BMS:
            {
                if(len == 1)
                {
                    setting.defaultConf.bmsType = *payload;
                    LOG_INFO("[Setting] bmsType:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_BATTERY:
            {
                if(len == 1)
                {
                    setting.defaultConf.batteryType = *payload;
                    LOG_INFO("[Setting] batteryType:%d", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_HELMET:
            {
                if(len == 1)
                {
                    setting.defaultConf.helmetType = *payload;
                    LOG_INFO("[Setting] helmetType:%d ",setting.defaultConf.helmetType);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_ISAUTOLOCKON:
            {
                if(len == 1)
                {
                    setting.defaultConf.isAutoLockOn = *payload;
                    LOG_INFO("[Setting] isAutoLockOn:%d ", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_ETC_SPEED:
            {
                if(len == 1)
                {
                    setting.defaultConf.etcSpeed = *payload;
                    LOG_INFO("[Setting] etcSpeed:%d ", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            case TYPE_ISTURNOVERON:
            {
                if(len == 1)
                {
                    setting.defaultConf.isTurnOverEnable = *payload;
                    LOG_INFO("[Setting] isTurnOverEnable:%d ", *payload);
                }
                else
                {
                    LOG_ERROR("[Setting] JsonFile ParaInVaild! Tag:%d", tag);
                }
            }
            break;
            default:
                break;
        }
        pbuf +=  temptlv->len + sizeof(temptlv->tag) + sizeof(temptlv->len);
        leftlen = leftlen - temptlv->len - sizeof(temptlv->tag) - sizeof(temptlv->len);
        //LOG_DEBUG("[Setting] *****pbuf 0x%x leftlen%d *****",pbuf[0],leftlen);
    }
    if(*pbuf == 0xA5)
    {
        LOG_INFO("[Setting] ***** JsonConfig Apply to system *****");
    }
}

L_BOOL defaultConf_save(void)
{
    cJSON *root = cJSON_CreateObject();
    if(!root)
    {
        return L_FALSE;
    }
    cJSON *userconfig = cJSON_CreateObject();
    if(!userconfig)
    {
        cJSON_Delete(root);
        return L_FALSE;
    }
    //default 文件
    cJSON_AddNumberToObject(userconfig, TAG_FVERSION, setting.defaultConf.version);
    cJSON_AddStringToObject(userconfig, TAG_TYPENAME, (const char *)setting.defaultConf.name);
    cJSON_AddNumberToObject(userconfig, TAG_TYPEINDEX, setting.defaultConf.productType);
    cJSON_AddNumberToObject(userconfig, TAG_BMSTYPE, setting.defaultConf.bmsType);
    cJSON_AddNumberToObject(userconfig, TAG_CCUTYPE, setting.defaultConf.ccuType);
    cJSON_AddNumberToObject(userconfig, TAG_HELMETTYPE, setting.defaultConf.helmetType);
    cJSON_AddNumberToObject(userconfig, TAG_SADDLETYPE, setting.defaultConf.saddleType);
    cJSON_AddNumberToObject(userconfig, TAG_BACKWHEELTYPE, setting.defaultConf.backWheelType);
    cJSON_AddNumberToObject(userconfig, TAG_LIGHTTYPE, setting.defaultConf.lightCtrlType);
    cJSON_AddNumberToObject(userconfig, TAG_BATTVTYPE, setting.defaultConf.batteryType);
    cJSON_AddNumberToObject(userconfig, TAG_ISOVERSPEEDON, setting.defaultConf.isOverSpeedOn);
    cJSON_AddNumberToObject(userconfig, TAG_ISMOVEALARMON, setting.defaultConf.isMoveAlarmOn);
    cJSON_AddNumberToObject(userconfig, TAG_AUDIORATIO, setting.defaultConf.audioRatio);
    cJSON_AddNumberToObject(userconfig, TAG_ISNIGHTVOICEON, setting.defaultConf.isNightVoiceOn);
    cJSON_AddNumberToObject(userconfig, TAG_ISSHARKALON, setting.defaultConf.isShakeAlarmOn);
    cJSON_AddNumberToObject(userconfig, TAG_ISAUTOLOCKON, setting.defaultConf.isAutoLockOn);
    cJSON_AddNumberToObject(userconfig, TAG_ETC_SPEED, setting.defaultConf.etcSpeed);
    cJSON_AddNumberToObject(userconfig, TAG_ISTURNENABLE, setting.defaultConf.isTurnOverEnable);
    cJSON_AddItemToObject(root, "userconfig", userconfig);

    char *content = cJSON_PrintUnformatted(root); //PrintUnformatted use space less
    if(!content)
    {
        LOG_ERROR("device inner error.");
        cJSON_Delete(root);
        return L_FALSE;
    }
    cJSON_Delete(root);
    
    cmd_status_UDP(); //设备配置改变保存后上报一次
    
    int ret = fs_saveFileData(FILE_DEFAULT_CONF, content, strlen(content));
    Free(content);
    return ret == 0 ? L_TRUE : L_FALSE;
}

static u8 defaultConf_restore(void)
{
    cJSON *conf = NULL;
    cJSON *tmp = NULL;

    LOG_INFO("restore default.conf from filesystem");

    //malloc memory to read the file
    int filesize = fs_getFileSize(FILE_DEFAULT_CONF);
    if(filesize < 0)
    {
        LOG_WARNING("restore default.conf size failed");
        return L_FALSE;
    }
    char *buf = (char *)Malloc(filesize + 1);
    if (!buf)
    {
        LOG_ERROR("malloc default.conf  buffer failed");
        return L_FALSE;
    }
    memset(buf, 0, filesize + 1);
    if(fs_getFileData(FILE_DEFAULT_CONF, buf, filesize + 1) < 0)
    {
        LOG_ERROR("restore default.conf data failed");
        return L_FALSE;
    }

    //parse the JSON data
    conf = cJSON_Parse(buf);
    if (!conf)
    {
        LOG_ERROR("default.conf file format error!");
        Free(buf);
        cJSON_Delete(conf);
        return L_FALSE;
    }
    Free(buf);

    cJSON *userconfig = cJSON_GetObjectItem(conf, "userconfig");
    if(userconfig)
    {
        tmp = cJSON_GetObjectItem(userconfig, TAG_TYPENAME);
        if(tmp)
        {
            u8 *name = (u8 *)tmp->valuestring;
            strncpy((char *)setting.defaultConf.name, (const char *)name, PRODUCT_NAME_LEN);
        }
        else
        {
            return L_FALSE;
        }
        LOG_INFO("[setting] product name :%s", setting.defaultConf.name);

        tmp = cJSON_GetObjectItem(userconfig, TAG_FVERSION);
        if(tmp)
        {
            setting.defaultConf.version = ((VERSION_MAJOR << 16) | (tmp->valueint & 0xFF00) | VERSION_MICRO);
        }
        else
        {
            return L_FALSE;
        }
        LOG_INFO("[setting] version: %d.%d.%d",(setting.defaultConf.version >> 16) & 0xFF,(setting.defaultConf.version >> 8) & 0xFF, (setting.defaultConf.version) & 0xFF);

        tmp = cJSON_GetObjectItem(userconfig, TAG_TYPEINDEX);
        if(tmp)
        {
            setting.defaultConf.productType = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        LOG_INFO("[setting] productType: %d",setting.defaultConf.productType);

        tmp = cJSON_GetObjectItem(userconfig, TAG_BMSTYPE);
        if(tmp)
        {
            setting.defaultConf.bmsType = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_CCUTYPE);
        if(tmp)
        {
            setting.defaultConf.ccuType = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_SADDLETYPE);
        if(tmp)
        {
            setting.defaultConf.saddleType = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_HELMETTYPE);
        if(tmp)
        {
            setting.defaultConf.helmetType = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_BACKWHEELTYPE);
        if(tmp)
        {
            setting.defaultConf.backWheelType = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_LIGHTTYPE);
        if(tmp)
        {
            setting.defaultConf.lightCtrlType = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_BATTVTYPE);
        if(tmp)
        {
            setting.defaultConf.batteryType = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_ISOVERSPEEDON);
        if(tmp)
        {
            setting.defaultConf.isOverSpeedOn = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_ISMOVEALARMON);
        if(tmp)
        {
            setting.defaultConf.isMoveAlarmOn = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_AUDIORATIO);
        if(tmp)
        {
            setting.defaultConf.audioRatio = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_ISNIGHTVOICEON);
        if(tmp)
        {
            setting.defaultConf.isNightVoiceOn = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_ISSHARKALON);
        if(tmp)
        {
            setting.defaultConf.isShakeAlarmOn = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_ISAUTOLOCKON);
        if(tmp)
        {
            setting.defaultConf.isAutoLockOn = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_ETC_SPEED);
        if(tmp)
        {
            setting.defaultConf.etcSpeed = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_ISTURNENABLE);
        if(tmp)
        {
            setting.defaultConf.isTurnOverEnable = tmp->valueint;
        }
        else
        {
            return L_FALSE;
        }
    }

    cJSON_Delete(conf);
    return L_TRUE;
}

u8 serverConf_save(void)
{
    cJSON *root = cJSON_CreateObject();
    if(!root)
    {
        return L_FALSE;
    }
    cJSON *address = cJSON_CreateObject();
    if(!address)
    {
        cJSON_Delete(root);
        return L_FALSE;
    }

    cJSON_AddNumberToObject(address, TAG_ADDR_TYPE, setting.serverConf.addr_type);
    if (setting.serverConf.addr_type == ADDR_TYPE_DOMAIN)
    {
        cJSON_AddStringToObject(address, "ADDR", setting.serverConf.domain);
    }
    else
    {
        char server_array[MAX_DOMAIN_NAME_LEN] = {0};
        snprintf(server_array, MAX_DOMAIN_NAME_LEN, "%d.%d.%d.%d", setting.serverConf.ipaddr[0], setting.serverConf.ipaddr[1], setting.serverConf.ipaddr[2], setting.serverConf.ipaddr[3]);
        cJSON_AddStringToObject(address, TAG_ADDR, server_array);
    }
    cJSON_AddNumberToObject(address, TAG_PORT, setting.serverConf.port);
    cJSON_AddItemToObject(root, TAG_SERVER, address);

    char *content = cJSON_PrintUnformatted(root);
    if(!content)
    {
        cJSON_Delete(root);
        return L_FALSE;
    }
    cJSON_Delete(root);

    int ret = fs_saveFileData(FILE_SERVER_CONF, content, strlen(content));
    Free(content);
    return ret == 0 ? L_TRUE : L_FALSE;
}

u8 serverConf_restore(void)
{
    cJSON *conf = 0;
    cJSON *server = 0;
    cJSON *addr = 0;
    cJSON *addrtype = 0;
    cJSON *port = 0;

    LOG_DEBUG("restore server from file");

    //malloc memory to read the file
    int filesize = fs_getFileSize(FILE_SERVER_CONF);
    if(filesize < 0)
    {
        return L_FALSE;
    }
    char *buf = (char *)Malloc(filesize + 1);
    if (!buf)
    {
        LOG_ERROR("malloc file content buffer failed");
        return L_FALSE;
    }
    memset(buf, 0, filesize + 1);
    fs_getFileData(FILE_SERVER_CONF, buf, filesize + 1);

    //parse the JSON data
    conf = cJSON_Parse(buf);
    if (!conf)
    {
        Free(buf);
        cJSON_Delete(conf);
        return L_FALSE;
    }
    Free(buf);

    server = cJSON_GetObjectItem(conf, TAG_SERVER);
    if (server)
    {
        addrtype = cJSON_GetObjectItem(server, TAG_ADDR_TYPE);
        if(!addrtype)
        {
            cJSON_Delete(conf);
            Free(buf);
            return L_FALSE;
        }
        setting.serverConf.addr_type = addrtype->valueint;
        if (setting.serverConf.addr_type == ADDR_TYPE_DOMAIN)
        {
            addr = cJSON_GetObjectItem(server, TAG_ADDR);
            if(addr)
            {
                char *domain = addr->valuestring;
                strncpy(setting.serverConf.domain, domain, MAX_DOMAIN_NAME_LEN);
                LOG_DEBUG("restore domain: %s", setting.serverConf.domain);
            }
        }
        else
        {
            addr = cJSON_GetObjectItem(server, TAG_ADDR);
            if(addr)
            {
                int ip[4] = {0,0,0,0};
                char *ipaddr = addr->valuestring;
                if(ipaddr)
                {
                    int count = sscanf(ipaddr, "%d.%d.%d.%d", ip, ip + 1, ip + 2, ip + 3);
                    if(count != 4) //4 means got four number of ip
                    {
                        cJSON_Delete(conf);
                        Free(buf);
                        return L_FALSE;
                    }
                    LOG_DEBUG("restore ip address");
                    if(ip[0] < 256 && ip[1] < 256 && ip[2] < 256 && ip[3] < 256)
                    {
                        setting.serverConf.ipaddr[0] = (u8)ip[0];
                        setting.serverConf.ipaddr[1] = (u8)ip[1];
                        setting.serverConf.ipaddr[2] = (u8)ip[2];
                        setting.serverConf.ipaddr[3] = (u8)ip[3];
                    }
                    else
                    {
                        cJSON_Delete(conf);
                        Free(buf);
                        return L_FALSE;
                    }
                }
                else
                {
                    LOG_ERROR("[server] ip string empty ***********");
                    cJSON_Delete(conf);
                    Free(buf);
                    return L_FALSE;
                }
            }
        }

        port = cJSON_GetObjectItem(server, TAG_PORT);
        if(port)
        {
            setting.serverConf.port = (u16)port->valueint;
            LOG_DEBUG("restore port: %d", setting.serverConf.port);
        }
    }

    cJSON_Delete(conf);
    return L_TRUE;
}

u8 statusConf_save(void)
{
    cJSON *root = cJSON_CreateObject();
    if(!root)
    {
        return L_FALSE;
    }

    cJSON *status = cJSON_CreateObject();
    if(!status)
    {
        cJSON_Delete(root);
        return L_FALSE;
    }

    //status
    cJSON_AddNumberToObject(status, TAG_ACC, setting.statusConf.acc);
    cJSON_AddNumberToObject(status, TAG_DEFEND, setting.statusConf.isDefend);

    cJSON_AddNumberToObject(status, TAG_REBOOT_TYPE, setting.statusConf.rebootType);
    cJSON_AddNumberToObject(status, TAG_ACCON_COUNT, setting.statusConf.accOnCount);
    cJSON_AddNumberToObject(status, TAG_PWRCUT_COUNT, setting.statusConf.pwrCutCount);

    cJSON_AddNumberToObject(status, TAG_TOTALMILES, setting.statusConf.totalMiles);
    cJSON_AddNumberToObject(status, TAG_LASTLAT, setting.statusConf.lastMileLat);
    cJSON_AddNumberToObject(status, TAG_LASTLON, setting.statusConf.lastMileLon);

    cJSON_AddNumberToObject(status, TAG_ISLOCKINGSADDLE, setting.statusConf.OperatingSaddlelock);

    cJSON_AddNumberToObject(status, TAG_ETC_UPGRADE_FLAG, setting.statusConf.etcUpgradeFlag);
    cJSON_AddNumberToObject(status, TAG_ETC_VERSION, setting.statusConf.etcVersion);
    cJSON_AddNumberToObject(status, TAG_ETC_UPGRADE_VERSION, setting.statusConf.etcUpgradeVersion);
    cJSON_AddNumberToObject(status, TAG_ETC_FW_CRC, setting.statusConf.etcFirmwareCRC);
    cJSON_AddNumberToObject(status, TAG_IS_TERMINATE_ETC_UPGRADE, setting.statusConf.isTerminateETCUpgrade);

    cJSON_AddNumberToObject(status, TAG_BMS_UPGRADE_FLAG, setting.statusConf.bmsUpgradeFlag);
    cJSON_AddNumberToObject(status, TAG_GPSBAUDUPDATE_FLAG, setting.statusConf.gpsBaudrateUpdateFlag);
    cJSON_AddNumberToObject(status, TAG_BMS_VERSION, setting.statusConf.bmsVersion);
    cJSON_AddNumberToObject(status, TAG_BMS_UPGRADE_VERSION, setting.statusConf.bmsUpgradeVersion);
    cJSON_AddNumberToObject(status, TAG_BMS_FW_CRC, setting.statusConf.bmsFirmwareCRC);
    cJSON_AddNumberToObject(status, TAG_BMS_SOC, setting.statusConf.bmsSoc);
    cJSON_AddNumberToObject(status, TAG_BMS_PERIOD, setting.statusConf.bmsSendPeriod);
    cJSON_AddNumberToObject(status, TAG_IS_TERMINATE_BMS_UPGRADE, setting.statusConf.isTerminateBMSUpgrade);
    cJSON_AddNumberToObject(status, TAG_HELMET_TARGET_STATUS, setting.statusConf.helmetTargetStatus);

    cJSON_AddItemToObject(root, TAG_STATUSVA, status);
    char *content = cJSON_PrintUnformatted(root);// PrintUnformatted use space less
    if(!content)
    {
        LOG_ERROR("device inner error.");
        cJSON_Delete(root);
        return L_FALSE;
    }
    cJSON_Delete(root);

    int ret = fs_saveFileData(FILE_STATUS_CONF, content, strlen(content));
    Free(content);
    return ret == 0 ? L_TRUE : L_FALSE;
}

u8 statusConf_restore(void)
{
    cJSON *conf = NULL;
    cJSON *tmp = NULL;

    //malloc memory to read the file
    int filesize = fs_getFileSize(FILE_STATUS_CONF);
    if(filesize < 0)
    {
        LOG_WARNING("restore status file size failed");
        return L_FALSE;
    }
    char *buf = (char *)Malloc(filesize + 1);
    if (!buf)
    {
        LOG_ERROR("malloc status file content buffer failed");
        return L_FALSE;
    }
    memset(buf, 0, filesize + 1);
    if(fs_getFileData(FILE_STATUS_CONF, buf, filesize + 1) < 0)
    {
        LOG_WARNING("restore status data failed");
        return L_FALSE;
    }

    //parse the JSON data
    conf = cJSON_Parse(buf);
    if (!conf)
    {
        LOG_ERROR("setting config file format error!");
        Free(buf);
        cJSON_Delete(conf);
        return L_FALSE;
    }
    Free(buf);

    cJSON *status = cJSON_GetObjectItem(conf, TAG_STATUSVA);
    if(status)
    {
        LOG_DEBUG("restore status conf");
        tmp = cJSON_GetObjectItem(status, TAG_DEFEND);
        if(tmp)
        {
            setting.statusConf.isDefend = tmp->valueint ? L_TRUE : L_FALSE;
            LOG_DEBUG("isDefend:%d", setting.statusConf.isDefend);
        }
        tmp = cJSON_GetObjectItem(status, TAG_ACC);
        if(tmp)
        {
            setting.statusConf.acc = tmp->valueint?L_TRUE:L_FALSE;
            LOG_DEBUG("acc:%d", setting.statusConf.acc);
        }
        tmp = cJSON_GetObjectItem(status, TAG_TOTALMILES);
        if(tmp)
        {
            setting.statusConf.totalMiles = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(status, TAG_LASTLAT);
        if(tmp)
        {
            setting.statusConf.lastMileLat = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(status, TAG_LASTLON);
        if(tmp)
        {
            setting.statusConf.lastMileLon = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(status, TAG_REBOOT_TYPE);
        if(tmp)
        {
            setting.statusConf.rebootType = tmp->valueint;
            if(setting.statusConf.rebootType == REBOOT_NULL)
            {
                setting.statusConf.rebootType = REBOOT_ERROR;
            }
            setting.statusConf.lastreboot = setting.statusConf.rebootType;
        }
        tmp = cJSON_GetObjectItem(status, TAG_ISLOCKINGSADDLE);
        if(tmp)
        {
            setting.statusConf.OperatingSaddlelock = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(status, TAG_ACCON_COUNT);
        if(tmp)
        {
            setting.statusConf.accOnCount = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(status, TAG_PWRCUT_COUNT);
        if(tmp)
        {
            setting.statusConf.pwrCutCount = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(status, TAG_ETC_UPGRADE_FLAG);
        if(tmp)
        {
            setting.statusConf.etcUpgradeFlag = (bool)tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(status, TAG_ETC_VERSION);
        if(tmp)
        {
            setting.statusConf.etcVersion = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_ETC_UPGRADE_VERSION);
        if(tmp)
        {
            setting.statusConf.etcUpgradeVersion = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_ETC_FW_CRC);
        if(tmp)
        {
            setting.statusConf.etcFirmwareCRC = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_IS_TERMINATE_ETC_UPGRADE);
        if(tmp)
        {
            setting.statusConf.isTerminateETCUpgrade = (bool)tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_BMS_UPGRADE_FLAG);
        if(tmp)
        {
            setting.statusConf.bmsUpgradeFlag = (bool)tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_BMS_VERSION);
        if(tmp)
        {
            setting.statusConf.bmsVersion = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_BMS_UPGRADE_VERSION);
        if(tmp)
        {
            setting.statusConf.bmsUpgradeVersion = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_BMS_FW_CRC);
        if(tmp)
        {
            setting.statusConf.bmsFirmwareCRC = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_BMS_SOC);
        if(tmp)
        {
            setting.statusConf.bmsSoc = tmp->valueint;
        }
        
        tmp = cJSON_GetObjectItem(status, TAG_BMS_PERIOD);
        if(tmp)
        {
            setting.statusConf.bmsSendPeriod = tmp->valueint;
        }
        
        tmp = cJSON_GetObjectItem(status, TAG_IS_TERMINATE_BMS_UPGRADE);
        if(tmp)
        {
            setting.statusConf.isTerminateBMSUpgrade = (bool)tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_COREUPCOUNT);
        if(tmp)
        {
            setting.statusConf.coreUpdateCount = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(status, TAG_GPSBAUDUPDATE_FLAG);
        if(tmp)
        {
            setting.statusConf.gpsBaudrateUpdateFlag = (bool)tmp->valueint;
        }
        
        tmp = cJSON_GetObjectItem(status, TAG_HELMET_TARGET_STATUS);
        if(tmp)
        {
            setting.statusConf.helmetTargetStatus = tmp->valueint;
        }
    }

    cJSON_Delete(conf);
    return L_TRUE;
}

u8 settingConf_save(void)
{
    cJSON *root = cJSON_CreateObject();
    if(!root)
    {
        return L_FALSE;
    }

    cJSON *innerparam = cJSON_CreateObject();
    if(!innerparam)
    {
        cJSON_Delete(root);
        return L_FALSE;
    }

    cJSON *userconfig = cJSON_CreateObject();
    if(!userconfig)
    {
        cJSON_Delete(root);
        cJSON_Delete(innerparam);
        return L_FALSE;
    }

    //默认配置
    cJSON_AddNumberToObject(userconfig, TAG_BMSTYPE, setting.defaultConf.bmsType);
    cJSON_AddNumberToObject(userconfig, TAG_CCUTYPE, setting.defaultConf.ccuType);
    cJSON_AddNumberToObject(userconfig, TAG_HELMETTYPE, setting.defaultConf.helmetType);
    cJSON_AddNumberToObject(userconfig, TAG_SADDLETYPE, setting.defaultConf.saddleType);
    cJSON_AddNumberToObject(userconfig, TAG_BACKWHEELTYPE, setting.defaultConf.backWheelType);
    cJSON_AddNumberToObject(userconfig, TAG_LIGHTTYPE, setting.defaultConf.lightCtrlType);
    cJSON_AddNumberToObject(userconfig, TAG_BATTVTYPE, setting.defaultConf.batteryType);
    cJSON_AddItemToObject(root, "userconfig", userconfig);

    cJSON_AddNumberToObject(innerparam, TAG_ISAUTOLOCKON, setting.defaultConf.isAutoLockOn);
    cJSON_AddNumberToObject(innerparam, TAG_ISMOVEALARMON, setting.defaultConf.isMoveAlarmOn);
    cJSON_AddNumberToObject(innerparam, TAG_ISOVERSPEEDON, setting.defaultConf.isOverSpeedOn);
    cJSON_AddNumberToObject(innerparam, TAG_AUDIORATIO, setting.defaultConf.audioRatio);
    cJSON_AddNumberToObject(innerparam, TAG_ISNIGHTVOICEON, setting.defaultConf.isNightVoiceOn);
    cJSON_AddNumberToObject(innerparam, TAG_ISSHARKALON, setting.defaultConf.isShakeAlarmOn);
    cJSON_AddNumberToObject(innerparam, TAG_ISTURNENABLE, setting.defaultConf.isTurnOverEnable);
    cJSON_AddNumberToObject(innerparam, TAG_ETC_SPEED, setting.defaultConf.etcSpeed);

    cJSON_AddNumberToObject(innerparam, TAG_FENCE_IGNORE, setting.settingConf.isIgnoreFence);
    cJSON_AddNumberToObject(innerparam, TAG_FENCE_IGNOREONCE, setting.settingConf.isIgnoreFenceOnce);

    if(setting.settingConf.freq_move != SETTING_DFT_MOVEPERIOD)
        cJSON_AddNumberToObject(innerparam, TAG_FREQ_MOVE, setting.settingConf.freq_move);
    if(setting.settingConf.freq_norm != SETTING_DFT_NORMPERIOD)
        cJSON_AddNumberToObject(innerparam, TAG_FREQ_NORM, setting.settingConf.freq_norm);

    if(setting.settingConf.audioType != 0)
        cJSON_AddNumberToObject(innerparam, TAG_AUDIOTYPE, setting.settingConf.audioType);

    if(setting.settingConf.isSleepEnable != SETTING_DFT_SLEEP)
        cJSON_AddNumberToObject(innerparam, TAG_ISSLEEPENABLE, setting.settingConf.isSleepEnable);
    if(setting.settingConf.isFenceEnable != SETTING_DFT_FENCE)
        cJSON_AddNumberToObject(innerparam, TAG_FENCE_SWITCH, setting.settingConf.isFenceEnable);

    if(setting.settingConf.isTBeaconEnable != SETTING_DFT_BEACON)
        cJSON_AddNumberToObject(innerparam, TAG_ISTBEACONABLE, setting.settingConf.isTBeaconEnable);
    if(setting.settingConf.isMX5EEAudio1K != L_FALSE)
        cJSON_AddNumberToObject(innerparam, TAG_ISMX5EEAUDIO1K, setting.settingConf.isMX5EEAudio1K);

    if(setting.settingConf.isAgpsEnable != SETTING_DFT_AGPS)
        cJSON_AddNumberToObject(innerparam, TAG_ISSAGPS, setting.settingConf.isAgpsEnable);
    if(setting.settingConf.forceLock != L_FALSE)
        cJSON_AddNumberToObject(innerparam, TAG_LOCKCARFORCE, setting.settingConf.forceLock);
    if(setting.settingConf.autoLockPeriod != SETTING_DFT_AUTOLOCKPERIOD)
        cJSON_AddNumberToObject(innerparam, TAG_AUTOLOCKPERIOD, setting.settingConf.autoLockPeriod);

    if(setting.settingConf.diffAngle != SETTING_DFT_TURNANGLE)
        cJSON_AddNumberToObject(innerparam, TAG_TURNANGLE, setting.settingConf.diffAngle);
    if(setting.settingConf.periodDiffAngleAudio != SETTING_DFT_TURNAUDIO)
        cJSON_AddNumberToObject(innerparam, TAG_PERIOD_TURNAUDIO, setting.settingConf.periodDiffAngleAudio);

    if(setting.settingConf.token != BLE_DFT_TOKEN)
        cJSON_AddNumberToObject(innerparam, TAG_TOKEN, setting.settingConf.token);
    if(0 != memcmp(setting.settingConf.ble_name, BLE_DFT_NAME, strlen(BLE_DFT_NAME)))
        cJSON_AddStringToObject(innerparam, TAG_BLENAME, (const char *)setting.settingConf.ble_name);

    if(setting.settingConf.etcFuncSwitch != ETC_DEFAULT_FUNCSWITCH)
        cJSON_AddNumberToObject(innerparam, TAG_ETC_FUNCSWICTH, setting.settingConf.etcFuncSwitch);
    if(setting.settingConf.etcIsSlowStart != ETC_DEFAULT_ISSLOWSTART)
        cJSON_AddNumberToObject(innerparam, TAG_ETC_ISSLOWSTART, setting.settingConf.etcIsSlowStart);
    if(setting.settingConf.etcLimitCurrent_100mA != ETC_DEFAULT_LIMITCURRENT)
        cJSON_AddNumberToObject(innerparam, TAG_ETC_LIMITCURRENT, setting.settingConf.etcLimitCurrent_100mA);
    if(setting.settingConf.etcProtectVoltage_100mV != ETC_DEFAUTL_PROTECTVOLTAGE)
        cJSON_AddNumberToObject(innerparam, TAG_ETC_PROTECTVOLTAGE, setting.settingConf.etcProtectVoltage_100mV);

    if((setting_getVerisonType() == VERSION_TYPE_MX5D2) || (setting_getVerisonType() == VERSION_TYPE_MX5D4))
    {
        cJSON_AddNumberToObject(innerparam, TAG_RGBISREPEAT, setting.settingConf.ledConfig.isRepeat);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDISTRIGGER, setting.settingConf.ledConfig.isTrigger);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDREPEATISON, setting.settingConf.ledConfig.isOn);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDREPEATTYPE, setting.settingConf.ledConfig.repeatLedType);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDMODE, setting.settingConf.ledConfig.repeatMode);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDDURATION, setting.settingConf.ledConfig.durationTime);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDREMAINTIME, setting.settingConf.ledConfig.remainTime);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDTRIGGERTYPE, setting.settingConf.ledConfig.triggerLedType);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDTRIGGERMODE, setting.settingConf.ledConfig.triggerMode);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDSTART, setting.settingConf.ledConfig.startTime);
        cJSON_AddNumberToObject(innerparam, TAG_RGBLEDEND, setting.settingConf.ledConfig.endTime);
    }

    if(setting.settingConf.isEtcSOC != L_FALSE)
    {
        cJSON_AddNumberToObject(innerparam, TAG_ETCSOC, setting.settingConf.isEtcSOC);
    }
    if(setting.settingConf.activeFreqSOC != 0)
    {
        cJSON_AddNumberToObject(innerparam, TAG_ACTIVEFREQSOC, setting.settingConf.activeFreqSOC);
    }
    cJSON_AddNumberToObject(innerparam, TAG_TBEACONRSSI, setting.settingConf.beaconRssi);
    cJSON_AddNumberToObject(innerparam, TAG_OVERSPEEDPERIOD, setting.settingConf.checkOverSpeedTime);
    cJSON_AddNumberToObject(innerparam, TAG_OVERSPEEDVOLUME, setting.settingConf.overSpeedVolume);
    cJSON_AddStringToObject(innerparam, TAG_OVERSPEEDURL, (const char *)setting.settingConf.overSpeedUrl);
    cJSON_AddNumberToObject(innerparam, TAG_OVERSPEEDCRC, setting.settingConf.overSpeedCrc);
    cJSON_AddNumberToObject(innerparam, TAG_LOGLEVEL, setting.settingConf.loglevel);
    if(setting.settingConf.protectVoltage != SETTING_DFT_PROTECTVOLATGE)
        cJSON_AddNumberToObject(innerparam, TAG_PROTECT_VOLTAGE, setting.settingConf.protectVoltage);
    if(setting.settingConf.restoreVoltage != SETTING_DFT_RESTOREVOLATGE)
        cJSON_AddNumberToObject(innerparam, TAG_RESTORE_VOLTAGE, setting.settingConf.restoreVoltage);
    cJSON_AddNumberToObject(innerparam, TAG_DEV_INSTALLMODE, setting.settingConf.devInstallMode);
    cJSON_AddNumberToObject(innerparam, TAG_MOVETHRESHOLD, setting.settingConf.move_threshold);
    cJSON_AddNumberToObject(innerparam, TAG_IS_ETC_ACC_PROTECT, setting.settingConf.isEtcAccProtect);
    cJSON_AddNumberToObject(innerparam, TAG_IS_ETC_DEFEND_PROTECT, setting.settingConf.isEtcDefendProtect);
    cJSON_AddNumberToObject(innerparam, TAG_RFID_ENABLE, setting.settingConf.isRFIDEnable);
    cJSON_AddNumberToObject(innerparam, TAG_IS_DEFAULT_SPEED, setting.settingConf.isDefaultSpeed);
    cJSON_AddNumberToObject(innerparam, TAG_IS_NMEA_OUT, setting.settingConf.isNmeaOut);
    cJSON_AddNumberToObject(innerparam, TAG_ETC_SPEED_SOURCE, setting.settingConf.etcSpeedSource);
    cJSON_AddNumberToObject(innerparam, TAG_ETC_SPEED_RATIO, setting.settingConf.etcSpeedRatio);
    cJSON_AddNumberToObject(innerparam, TAG_ETC_HALL_RATIO, setting.settingConf.etcHallRatio);
    cJSON_AddStringToObject(innerparam, TAG_APNNAME, (const char *)setting.settingConf.apnname);
    cJSON_AddStringToObject(innerparam, TAG_USERNAME, (const char *)setting.settingConf.username);
    cJSON_AddStringToObject(innerparam, TAG_PASSWORD, (const char *)setting.settingConf.password);
    cJSON_AddNumberToObject(innerparam, TAG_IS_ETC_OVERSPEED_BIT, setting.settingConf.isEtcOverspeedBit);
    cJSON_AddNumberToObject(innerparam, TAG_OVERSPEED_THRESHOLD, setting.settingConf.overspeedThreshold);

    cJSON_AddItemToObject(root, "innerparam", innerparam);

    char *content = cJSON_PrintUnformatted(root);// PrintUnformatted use space less
    if(!content)
    {
        LOG_ERROR("device inner error.");
        cJSON_Delete(root);
        return L_FALSE;
    }
    cJSON_Delete(root);

    int ret = fs_saveFileData(FILE_SETTING_CONF, content, strlen(content));
    Free(content);
    return ret == 0 ? L_TRUE : L_FALSE;
}

u8 settingConf_restore(void)
{
    cJSON *conf = NULL;
    cJSON *tmp = NULL;

    LOG_INFO("restore setting from file");

    //malloc memory to read the file
    int filesize = fs_getFileSize(FILE_SETTING_CONF);
    if(filesize < 0)
    {
        LOG_WARNING("restore setting size failed");
        return L_FALSE;
    }
    char *buf = (char *)Malloc(filesize + 1);
    if (!buf)
    {
        LOG_ERROR("malloc file content buffer failed");
        return L_FALSE;
    }
    memset(buf, 0, filesize + 1);
    if(fs_getFileData(FILE_SETTING_CONF, buf, filesize + 1) < 0)
    {
        LOG_WARNING("restore setting data failed");
        return L_FALSE;
    }

    //parse the JSON data
    conf = cJSON_Parse(buf);
    if (!conf)
    {
        LOG_ERROR("setting config file format error!");
        Free(buf);
        cJSON_Delete(conf);
        return L_FALSE;
    }
    Free(buf);

    cJSON *defend_state = cJSON_GetObjectItem(conf, TAG_DEFENDVA);
    if(defend_state)
    {
        LOG_DEBUG("restore defend_state conf");
        tmp = cJSON_GetObjectItem(defend_state, TAG_DEFEND);
        if(tmp)
        {
            setting.statusConf.isDefend = tmp->valueint ? L_TRUE : L_FALSE;
        }
        tmp = cJSON_GetObjectItem(defend_state, TAG_ACC);
        if(tmp)
        {
            setting.statusConf.acc = tmp->valueint?L_TRUE:L_FALSE;
        }
    }

    cJSON *innerparam = cJSON_GetObjectItem(conf, "innerparam");
    if(innerparam)
    {
        tmp = cJSON_GetObjectItem(innerparam, TAG_TYPENAME);  //兼容
        if(tmp)
        {
            u8 *name = (u8 *)tmp->valuestring;
            strncpy((char *)setting.defaultConf.name, (const char *)name, PRODUCT_NAME_LEN);
            LOG_INFO("[setting] patch product name :%s", setting.defaultConf.name);
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_FVERSION);  //兼容
        if(tmp)
        {
            setting.defaultConf.version = ((VERSION_MAJOR << 16) | (tmp->valueint & 0xFF00) | VERSION_MICRO);
            LOG_INFO("[setting] patch version: %d.%d.%d",(setting.defaultConf.version >> 16) & 0xFF,(setting.defaultConf.version >> 8) & 0xFF, (setting.defaultConf.version) & 0xFF);
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_TYPEINDEX);  //兼容
        if(tmp)
        {
            setting.defaultConf.productType = tmp->valueint;
            LOG_INFO("[setting] patch productType: %d",setting.defaultConf.productType);
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_LOGLEVEL);
        if(tmp)
        {
            setting.settingConf.loglevel = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_FREQ_NORM);
        if(tmp)
        {
            setting.settingConf.freq_norm = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_FREQ_MOVE);
        if(tmp)
        {
            setting.settingConf.freq_move = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISOVERSPEEDON);
        if(tmp)
        {
            setting.defaultConf.isOverSpeedOn = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_FENCE_SWITCH);
        if(tmp)
        {
            setting.settingConf.isFenceEnable = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_FENCE_IGNORE);
        if(tmp)
        {
            setting.settingConf.isIgnoreFence = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_FENCE_IGNOREONCE);
        if(tmp)
        {
            setting.settingConf.isIgnoreFenceOnce = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISMOVEALARMON);
        if(tmp)
        {
            setting.defaultConf.isMoveAlarmOn = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_AUDIORATIO);
        if(tmp)
        {
            setting.defaultConf.audioRatio = (float)tmp->valuedouble;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISNIGHTVOICEON);
        if(tmp)
        {
            setting.defaultConf.isNightVoiceOn = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISSLEEPENABLE);
        if(tmp)
        {
            setting.settingConf.isSleepEnable = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISSHARKALON);
        if(tmp)
        {
            setting.defaultConf.isShakeAlarmOn = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISSAGPS);
        if(tmp)
        {
            setting.settingConf.isAgpsEnable = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISMX5EEAUDIO1K);
        if(tmp)
        {
            setting.settingConf.isMX5EEAudio1K = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_TOKEN);
        if(tmp)
        {
            u32 token = (u32)tmp->valueint;
            setting.settingConf.token = token;
            LOG_DEBUG("%#x", setting.settingConf.token);
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_REBOOT_TYPE);
        if(tmp)
        {
            setting.statusConf.rebootType = tmp->valueint;
            // 如果上次记录的值为正常无重启，则本次开机认为是异常重启
            if(setting.statusConf.rebootType == REBOOT_NULL)
            {
                setting.statusConf.rebootType = REBOOT_ERROR;
            }
            setting.statusConf.lastreboot = setting.statusConf.rebootType;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_BLENAME);
        if(tmp)
        {
            u8 *name = (u8 *)tmp->valuestring;
            strncpy((char *)setting.settingConf.ble_name, (const char *)name, MAX_BLE_NAME_LEN);
            LOG_DEBUG("%s", setting.settingConf.ble_name);
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISLOCKINGSADDLE);
        if(tmp)
        {
            setting.statusConf.OperatingSaddlelock = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ACCON_COUNT);
        if(tmp)
        {
            setting.statusConf.accOnCount = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_PWRCUT_COUNT);
        if(tmp)
        {
            setting.statusConf.pwrCutCount = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_FUNCSWICTH);
        if(tmp)
        {
            setting.settingConf.etcFuncSwitch = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISAUTOLOCKON);
        if(tmp)
        {
            setting.defaultConf.isAutoLockOn = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_AUTOLOCKPERIOD);
        if(tmp)
        {
            setting.settingConf.autoLockPeriod = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_ISSLOWSTART);
        if(tmp)
        {
            setting.settingConf.etcIsSlowStart = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_LIMITCURRENT);
        if(tmp)
        {
            setting.settingConf.etcLimitCurrent_100mA = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_PROTECTVOLTAGE);
        if(tmp)
        {
            setting.settingConf.etcProtectVoltage_100mV = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_SPEED);
        if(tmp)
        {
            setting.defaultConf.etcSpeed = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_UPGRADE_FLAG);
        if(tmp)
        {
            setting.statusConf.etcUpgradeFlag = (bool)tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_VERSION);
        if(tmp)
        {
            setting.statusConf.etcVersion = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_UPGRADE_VERSION);
        if(tmp)
        {
            setting.statusConf.etcUpgradeVersion = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_FW_CRC);
        if(tmp)
        {
            setting.statusConf.etcFirmwareCRC = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_IS_TERMINATE_ETC_UPGRADE);
        if(tmp)
        {
            setting.statusConf.isTerminateETCUpgrade = (bool)tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_BMS_UPGRADE_FLAG);
        if(tmp)
        {
            setting.statusConf.bmsUpgradeFlag = (bool)tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_BMS_VERSION);
        if(tmp)
        {
            setting.statusConf.bmsVersion = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_BMS_UPGRADE_VERSION);
        if(tmp)
        {
            setting.statusConf.bmsUpgradeVersion = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_BMS_FW_CRC);
        if(tmp)
        {
            setting.statusConf.bmsFirmwareCRC = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_BMS_SOC);
        if(tmp)
        {
            setting.statusConf.bmsSoc = tmp->valueint;
        }
        
        tmp = cJSON_GetObjectItem(innerparam, TAG_IS_TERMINATE_BMS_UPGRADE);
        if(tmp)
        {
            setting.statusConf.isTerminateBMSUpgrade = (bool)tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_AUDIOTYPE);
        if(tmp)
        {
            setting.settingConf.audioType = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_PROTECT_VOLTAGE);
        if(tmp)
        {
            setting.settingConf.protectVoltage = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_RESTORE_VOLTAGE);
        if(tmp)
        {
            setting.settingConf.restoreVoltage = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_LOCKCARFORCE);
        if(tmp)
        {
            setting.settingConf.forceLock = tmp->valueint ? L_TRUE : L_FALSE;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ISTURNENABLE);
        if(tmp)
        {
            setting.defaultConf.isTurnOverEnable = tmp->valueint ? L_TRUE : L_FALSE;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_PERIOD_TURNAUDIO);
        if(tmp)
        {
            setting.settingConf.periodDiffAngleAudio = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_TURNANGLE);
        if(tmp)
        {
            setting.settingConf.diffAngle = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_OVERSPEEDPERIOD);
        if(tmp)
        {
            setting.settingConf.checkOverSpeedTime = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_OVERSPEEDVOLUME);
        if(tmp)
        {
            setting.settingConf.overSpeedVolume = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_OVERSPEEDURL);
        if(tmp)
        {
            strncpy((char *)setting.settingConf.overSpeedUrl, tmp->valuestring, MAX_URL_LEN);
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_OVERSPEEDCRC);
        if(tmp)
        {
            setting.settingConf.overSpeedCrc = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_MOVETHRESHOLD);
        if(tmp)
        {
            setting.settingConf.move_threshold = tmp->valueint;
        }

        if((setting_getVerisonType() == VERSION_TYPE_MX5D2) || (setting_getVerisonType() == VERSION_TYPE_MX5D4))
        {
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBISREPEAT);
            if(tmp)
            {
                setting.settingConf.ledConfig.isRepeat = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDISTRIGGER);
            if(tmp)
            {
                setting.settingConf.ledConfig.isTrigger = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDREPEATISON);
            if(tmp)
            {
                setting.settingConf.ledConfig.isOn= tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDREPEATTYPE);
            if(tmp)
            {
                setting.settingConf.ledConfig.repeatLedType = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDMODE);
            if(tmp)
            {
                setting.settingConf.ledConfig.repeatMode = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDDURATION);
            if(tmp)
            {
                setting.settingConf.ledConfig.durationTime = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDREMAINTIME);
            if(tmp)
            {
                setting.settingConf.ledConfig.remainTime = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDTRIGGERTYPE);
            if(tmp)
            {
                setting.settingConf.ledConfig.triggerLedType = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDTRIGGERMODE);
            if(tmp)
            {
                setting.settingConf.ledConfig.triggerMode = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDSTART);
            if(tmp)
            {
                setting.settingConf.ledConfig.startTime = tmp->valueint;
            }
            tmp = cJSON_GetObjectItem(innerparam, TAG_RGBLEDEND);
            if(tmp)
            {
                setting.settingConf.ledConfig.endTime = tmp->valueint;
            }
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_DEV_INSTALLMODE);
        if(tmp)
        {
            setting.settingConf.devInstallMode = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_ETCSOC);
        if(tmp)
        {
            setting.settingConf.isEtcSOC = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_ACTIVEFREQSOC);
        if(tmp)
        {
            setting.settingConf.activeFreqSOC = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_TBEACONRSSI);
        if(tmp)
        {
            setting.settingConf.beaconRssi = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_IS_ETC_ACC_PROTECT);
        if(tmp)
        {
            setting.settingConf.isEtcAccProtect = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_IS_ETC_DEFEND_PROTECT);
        if(tmp)
        {
            setting.settingConf.isEtcDefendProtect = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_RFID_ENABLE);
        if(tmp)
        {
            setting.settingConf.isRFIDEnable = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_IS_DEFAULT_SPEED);
        if(tmp)
        {
            setting.settingConf.isDefaultSpeed = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_IS_NMEA_OUT);
        if(tmp)
        {
            setting.settingConf.isNmeaOut = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_SPEED_SOURCE);
        if (tmp)
        {
            setting.settingConf.etcSpeedSource = tmp->valueint;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_SPEED_RATIO);
        if (tmp)
        {
            setting.settingConf.etcSpeedRatio = tmp->valuedouble;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_ETC_HALL_RATIO);
        if (tmp)
        {
            setting.settingConf.etcHallRatio = tmp->valuedouble;
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_APNNAME);
        if(tmp)
        {
            strncpy((char *)setting.settingConf.apnname, (const char *)tmp->valuestring, 64);
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_USERNAME);
        if(tmp)
        {
            strncpy((char *)setting.settingConf.username, (const char *)tmp->valuestring, 64);
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_PASSWORD);
        if(tmp)
        {
            strncpy((char *)setting.settingConf.password, (const char *)tmp->valuestring, 64);
        }

        tmp = cJSON_GetObjectItem(innerparam, TAG_IS_ETC_OVERSPEED_BIT);
        if (tmp)
        {
            setting.settingConf.isEtcOverspeedBit = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(innerparam, TAG_OVERSPEED_THRESHOLD);
        if (tmp)
        {
            setting.settingConf.overspeedThreshold = tmp->valueint;
        }
    }

    cJSON *userconfig = cJSON_GetObjectItem(conf, "userconfig");  //兼容新版本的tag 下同
    if(userconfig)
    {
        tmp = cJSON_GetObjectItem(userconfig, TAG_BMSTYPE);
        if(tmp)
        {
            setting.defaultConf.bmsType = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_CCUTYPE);
        if(tmp)
        {
            setting.defaultConf.ccuType = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_SADDLETYPE);
        if(tmp)
        {
            setting.defaultConf.saddleType = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_HELMETTYPE);
        if(tmp)
        {
            setting.defaultConf.helmetType = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_BACKWHEELTYPE);
        if(tmp)
        {
            setting.defaultConf.backWheelType = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_LIGHTTYPE);
        if(tmp)
        {
            setting.defaultConf.lightCtrlType = tmp->valueint;
        }
        tmp = cJSON_GetObjectItem(userconfig, TAG_BATTVTYPE);
        if(tmp)
        {
            setting.defaultConf.batteryType = tmp->valueint;
        }
    }

    cJSON_Delete(conf);
    return L_TRUE;
}

static void setting_addFlashData(ST_FLASH_DATA_HEADER *flashData, USER_FLASH_TYPE type, void *data, u16 len)
{
    //计算要写的数据的位置
    u16 i = 0;
    u8 *pos = flashData->payload + flashData->payloadLen;

    //更新数据
    flashData->payloadLen = flashData->payloadLen + len + 2;
    pos[0] = type;
    pos[1] = len;
    memcpy(pos + 2, data, len);

    //计算checksum
    pos = (u8 *)flashData;
    flashData->payload[flashData->payloadLen] = 0;
    for(; i < flashData->payloadLen + 3; i++)
    {
        flashData->payload[flashData->payloadLen] += pos[i];
    }
}

u8 setting_saveFlash(void)
{
    u8 rc = L_FALSE;

    LOG_DEBUG("[Flash] Save");
    ST_FLASH_DATA_HEADER *flashData = (ST_FLASH_DATA_HEADER *)Malloc(SETTING_DATA_SIZE * 2);
    if(!flashData)
    {
        Free(flashData);
        return L_FALSE;
    }
    //add signature
    flashData->signature = 0xAA;

    setting_addFlashData(flashData, TYPE_BUILDTIME_S, __TIME__, strlen(__TIME__));

    rc = flash_save2Block((const ST_FLASH_DATA_HEADER *)flashData, flashData->payloadLen + 4);

    //Free flash Data
    Free(flashData);
    return rc;
}

static void setting_reMoveCfgFile(void)
{
    if(fs_isFileExists(FILE_DEFAULT_CONF) == L_TRUE)
    {
        fs_deleteFile(FILE_DEFAULT_CONF);
        LOG_DEBUG("[setting] remove %s",FILE_DEFAULT_CONF);
    }

    if(fs_isFileExists(FILE_SERVER_CONF) == L_TRUE)
    {
        fs_deleteFile(FILE_SERVER_CONF);
        LOG_DEBUG("[setting] remove %s",FILE_SERVER_CONF);
    }
    if(fs_isFileExists(FILE_SETTING_CONF) == L_TRUE)
    {
        fs_deleteFile(FILE_SETTING_CONF);
        LOG_DEBUG("[setting] remove %s",FILE_SETTING_CONF);
    }
    if(fs_isFileExists(FILE_FENCE_CONF) == L_TRUE)
    {
        fs_deleteFile(FILE_FENCE_CONF);
        LOG_DEBUG("[setting] remove %s",FILE_FENCE_CONF);
    }
    if(fs_isFileExists(UPGRADE_ETC_FILE_NAME) == L_TRUE)
    {
        fs_deleteFile(UPGRADE_ETC_FILE_NAME);
        LOG_DEBUG("[setting] remove %s",UPGRADE_ETC_FILE_NAME);
    }
    if(fs_isFileExists(UPGRADE_BMS_FILE_NAME) == L_TRUE)
    {
        fs_deleteFile(UPGRADE_BMS_FILE_NAME);
        LOG_DEBUG("[setting] remove %s",UPGRADE_BMS_FILE_NAME);
    }

    return;
}
u8 setting_restoreFlash(void)
{
    s16 leftLen = 0;
    ST_FLASH_DATA *pValue = NULL;
    ST_FLASH_DATA_HEADER *flashData = (ST_FLASH_DATA_HEADER *)flash_getBlockData();
    if(!flashData)
    {
        setting_saveFlash(); //新板子先保存一遍
        Free(flashData);
        return L_FALSE;
    }
    LOG_INFO("[Flash] Get Block Data Success!");
    leftLen = flashData->payloadLen;
    pValue = (ST_FLASH_DATA *)flashData->payload;
    do
    {
        switch(pValue->type)
        {
            case TYPE_TOTALMILES: //兼容老版本
            {
                setting.statusConf.totalMiles = setting_getNumber(pValue, TYPE_UNSIGNED);
                LOG_INFO("[Flash] totalMiles:%d\r\n", setting.statusConf.totalMiles);
            }
            break;

            case TYPE_LASTMILELAT:
            {
                setting.statusConf.lastMileLat = setting_getNumber(pValue, TYPE_SIGNED);
                LOG_INFO("[Flash] Mileinfo Last Latitude:%d\r\n", setting.statusConf.lastMileLat);
            }
            break;

            case TYPE_LASTMILELON:
            {
                setting.statusConf.lastMileLon = setting_getNumber(pValue, TYPE_SIGNED);
                LOG_INFO("[Flash] Mileinfo Last Longitude:%d\r\n", setting.statusConf.lastMileLon);
            }
            break;
            case TYPE_BUILDTIME_S:
            {
                char buildStamp[10];
                memset(buildStamp, 0, 10);
                if(pValue->len < 10)
                {
                    memcpy(buildStamp, pValue->value, pValue->len);
                    buildStamp[pValue->len] = 0;
                }
                if(strcmp(buildStamp, __TIME__) != 0) //烧录了新固件
                {
                    LOG_INFO("[Flash] New FirmWare!");
                    setting_saveFlash();
                }
                else
                {
                    LOG_INFO("[Flash] FirmWare Check OK , Continue... ");
                }
            }
            break;
            default:
            {
                LOG_INFO("[Flash] Unknow type:%d", pValue->type);
            }
            break;
        }
        leftLen -= (pValue->len + 2);
        pValue = (ST_FLASH_DATA *)((u8 *)flashData->payload + flashData->payloadLen - leftLen);
    }while(leftLen > 2); // type len
    Free(flashData);
    return L_TRUE;
}

void setting_ApplyConf(void)
{
    if(setting_restoreFlash())
    {
        if(!defaultConf_restore())   //获取默认配置失败
        {
            defaultConf_ObtainJSON();
            if(!settingConf_restore())  //如果从老版本升上来,除了设备名字,版本号,产品号,其他都可被原有的setting文件覆盖.
            {
                //todo 上报获取配置错误
            }
            defaultConf_save();
        }
        else
        {
            settingConf_restore();
        }
    }
    else
    {
        //新板子flash没有数据
        audio_factoryAll();
        setting_reMoveCfgFile();//清空所有文件
        defaultConf_ObtainJSON();
        defaultConf_save();
        LOG_INFO("[Flash] Init New Borad");
    }
}

void setting_fixHardware(void)
{
    if(setting_getVerisonType() == VERSION_TYPE_MX5K6)
    {
        setting.settingConf.gpsType = GPS_UBLOX_M8U;
        setting.settingConf.accleType = ACCLE_LIS3DH;
    }
    else if(setting_getVerisonType() == VERSION_TYPE_MX5K6_DD ||
            setting_getVerisonType() == VERSION_TYPE_MX5F6_DD ||
            setting_getVerisonType() == VERSION_TYPE_MX5Y6_DD ||
            setting_getVerisonType() == VERSION_TYPE_MX5H6_DD ||
            setting_getVerisonType() == VERSION_TYPE_MX5H7_DD ||
            setting_getVerisonType() == VERSION_TYPE_MX5F7_DD ||
            setting_getVerisonType() == VERSION_TYPE_MX5K7_DD ||
            setting_getVerisonType() == VERSION_TYPE_MX5K8_RF ||
            setting_getVerisonType() == VERSION_TYPE_MX5Y6_RF ||
            setting_getVerisonType() == VERSION_TYPE_MX5F6_RF ||
            setting_getVerisonType() == VERSION_TYPE_MX5F7_RF ||
            setting_getVerisonType() == VERSION_TYPE_MX5H7_RF ||
            setting_getVerisonType() == VERSION_TYPE_MX5K6_RF
            )
    {
        setting.settingConf.gpsType = GPS_UBLOX_8130;
        setting.settingConf.accleType = ACCLE_MPU6500;
    }
    else if(setting_getVerisonType() == VERSION_TYPE_MX5K6_LS)
    {
        setting.settingConf.gpsType = GPS_UBLOX_M8U;
        setting.settingConf.accleType = ACCLE_MPU6500;
    }
    
    if(setting_getVerisonType() == VERSION_TYPE_MX5D3_RF || setting_getVerisonType() == VERSION_TYPE_MX5K8_RF 
    || setting_getVerisonType() == VERSION_TYPE_MX5Y6_RF || setting_getVerisonType() == VERSION_TYPE_MX5F7_RF
    || setting_getVerisonType() == VERSION_TYPE_MX5F6_RF || setting_getVerisonType() == VERSION_TYPE_MX5H7_RF
    || setting_getVerisonType() == VERSION_TYPE_MX5K6_RF || setting_getVerisonType() == VERSION_TYPE_MX5K4_RF
    || setting_getVerisonType() == VERSION_TYPE_MX5K7_RF)
    {
        setting.settingConf.isRFIDEnable = L_TRUE;
    }
    
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JC)
    {
        setting.settingConf.isKickStandEnable = L_TRUE;
    }
}

int setting_getVersion_cb(int result, uint8_t *data, int data_len)
{
    if(result == 0 && data)
    {
        cJSON *json_root = NULL;

        /* 首先恢复初始设置 */
        setting.defaultConf.version =  (255 << 16) | (255 << 8) | 255;
        setting.defaultConf.productType = DEVICE_TYPE;
        setting.defaultConf.bmsType = TYPE_NOBMS;
        setting.defaultConf.ccuType = TYPE_XIAOANCCU;
        setting.defaultConf.helmetType = TYPE_NOHELMET;
        setting.defaultConf.saddleType = TYPE_BUCKLESADDLE;
        setting.defaultConf.backWheelType = TYPE_NOBACKWHEEL;
        setting.defaultConf.lightCtrlType = TYPE_CCUHEADLIGHT;
        setting.defaultConf.batteryType = TYPE_BATTERY48V;
        setting.defaultConf.isOverSpeedOn = SETTING_DFT_OVERSPEED;
        setting.defaultConf.isMoveAlarmOn = SETTING_DFT_MOVEALARM;
        setting.defaultConf.isNightVoiceOn = SETTING_DFT_NIGHTVO;
        setting.defaultConf.isShakeAlarmOn = SETTING_DFT_SHARKAL;
        setting.defaultConf.isTurnOverEnable = SETTING_DFT_TURNOVER;
        setting.defaultConf.isAutoLockOn = SETTING_DFT_AUTOLOCK;
        setting.defaultConf.audioRatio = 1.0f;
        setting.defaultConf.etcSpeed = ETC_DEFAULT_SPEED;

        /* 从服务器文件中恢复标品配置 */
        json_root = cJSON_Parse(data);
        if(json_root)
        {
            cJSON *temp = NULL;
            temp = cJSON_GetObjectItem(json_root, "confVersion");
            if(temp)
            {
                u8 *p = string_bypassByNum(temp->valuestring, ".", 1);
                setting.defaultConf.version = (VERSION_MAJOR << 16) | (_atoi(p) << 8) | VERSION_MICRO;
            }
            temp = cJSON_GetObjectItem(json_root, "productType");
            if(temp)
            {
                setting.defaultConf.productType = temp->valueint;
            }
            temp = cJSON_GetObjectItem(json_root, "productName");
            if(temp)
            {
                strncpy((char *)setting.defaultConf.name, (const char *)temp->valuestring, PRODUCT_NAME_LEN);
            }
            temp = cJSON_GetObjectItem(json_root, "setting");
            if(NULL != temp)
            {
                cJSON *setting_list = temp->child;
                while(setting_list != NULL)
                {
                    u8 type = cJSON_GetObjectItem(setting_list, "type")->valueint;
                    switch (type)
                    {
                        case TYPE_ISOVERSPEEDON:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.isOverSpeedOn = jvalue;
                            LOG_INFO("[patch] OverSpeedOn:%d", jvalue);
                        }
                        break;
                        case TYPE_ISMOVEALARMON:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.isMoveAlarmOn = jvalue;
                            LOG_INFO("[patch] MoveAlarmOn:%d", jvalue);
                        }
                        break;
                        case TYPE_AUDIORATIO:
                        {
                            float jvalue = cJSON_GetObjectItem(setting_list, "value")->valuedouble ;
                            setting.defaultConf.audioRatio = (jvalue / 100);
                            LOG_INFO("[patch] audioRatio:%f", setting.defaultConf.audioRatio);
                        }
                        break;
                        case TYPE_ISNIGHTVOICEON:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.isNightVoiceOn = jvalue;
                            LOG_INFO("[patch] isNightVoiceOn:%d", jvalue);
                        }
                        break;
                        case TYPE_SADDLE:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.saddleType = jvalue;
                            LOG_INFO("[patch] saddleType:%d", jvalue);
                        }
                        break;
                        case TYPE_BACKWHEEL:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.backWheelType = jvalue;
                            LOG_INFO("[patch] backWheelType:%d",jvalue);
                        }
                        break;
                        case TYPE_ISSHAKEALARMON:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.isShakeAlarmOn = jvalue;
                            LOG_INFO("[patch] isShakeAlarmOn:%d", jvalue);
                        }
                        break;
                        case TYPE_CONTROLLIGHT:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.lightCtrlType = jvalue;
                            LOG_INFO("[patch] lightCtrlType:%d", jvalue);
                        }
                        break;
                        case TYPE_CCU:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.ccuType = jvalue;
                            LOG_INFO("[patch] ccuType:%d", jvalue);
                        }
                        break;
                        case TYPE_BMS:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.bmsType = jvalue;
                            LOG_INFO("[patch] bmsType:%d", jvalue);
                        }
                        break;
                        case TYPE_BATTERY:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.batteryType = jvalue;
                            LOG_INFO("[patch] batteryType:%d", jvalue);
                        }
                        break;
                        case TYPE_HELMET:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.helmetType = jvalue;
                            LOG_INFO("[patch] helmetType:%d", jvalue);
                        }
                        break;
                        case TYPE_ISAUTOLOCKON:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.isAutoLockOn = jvalue;
                            LOG_INFO("[patch] isAutoLockOn:%d", jvalue);
                        }
                        break;
                        case TYPE_ETC_SPEED:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.etcSpeed = jvalue;
                            LOG_INFO("[patch] etcSpeed:%d", jvalue);
                        }
                        break;
                        case TYPE_ISTURNOVERON:
                        {
                            u8 jvalue = cJSON_GetObjectItem(setting_list, "value")->valueint;
                            setting.defaultConf.isTurnOverEnable = jvalue;
                            LOG_INFO("[patch] isTurnOverEnable:%d", jvalue);
                        }
                        break;
                        default:
                            break;
                    }
                    setting_list = setting_list->next ;
                }
            }
            defaultConf_save(); //保存标品默认配置文件
            settingConf_save(); //恢复出厂配置文件
            cJSON_Delete(json_root);
            return 0;
        }
        cJSON_Delete(json_root);
    }
    return -1;
}

static void setting_versionPatch_cb(void *pstHttpParam, INT8 *data, INT32 len)
{
    LOG_DEBUG("getVersion RSP");
    LOG_HEX(data, len);
    cJSON *jdata = NULL;
    cJSON *json_root = NULL;
    json_root = cJSON_Parse(data);

    jdata = cJSON_GetObjectItem(json_root, "data");
    if(jdata)
    {
        cJSON *ver = NULL;
        ver = cJSON_GetObjectItem(jdata, "version");
        if(ver)
        {
            u32 tempVer = ver->valueint;
            u8 url[256] = {0};
            u8 vMAR = (setting.defaultConf.version >> 16) & 0xFF; //首位版本号
            u8 vMIN = (setting.defaultConf.version >> 8) & 0xFF; //中间版本号
            LOG_DEBUG("version%d, version MIN%d", tempVer, tempVer >> 8 & 0xff);
            if(vMAR == VERSION_MAJOR && vMIN == 0) //如果没有变成0.0.0而且是MX5F(15.0.x)则不恢复
            {
                cJSON_Delete(json_root);
                return;
            }
            switch(tempVer >> 8 & 0xff)
            {
                case VERSION_TYPE_MX5F:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5F.json");
                }
                break;
                case VERSION_TYPE_MX5K4:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5K4.json");
                }
                break;
                case VERSION_TYPE_MX5F3:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5F3.json");
                }
                break;
                case VERSION_TYPE_MX5H3:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5H3.json");
                }
                break;
                case VERSION_TYPE_MX5K3:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5K3.json");
                }
                break;
                case VERSION_TYPE_MX5Z3:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5Z3.json");
                }
                break;
                case VERSION_TYPE_MX5Z:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5Z.json");
                }
                break;
                case VERSION_TYPE_MX5D:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5D.json");
                }
                break;
                case VERSION_TYPE_MX5H:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5H.json");
                }
                break;
                case VERSION_TYPE_MX5F_JDY:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5F_JDY.json");
                }
                break;
                case VERSION_TYPE_MX5Z5:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5Z5.json");
                }
                break;
                case VERSION_TYPE_MX5D2:
                {
                    sprintf(url, "http://xc-res.oss-cn-shenzhen.aliyuncs.com/mx5BkConfig/config_MX5D2.json");
                }
                break;
                default:
                {
                    cJSON_Delete(json_root);
                    return;
                }
            }
            http_get(url, setting_getVersion_cb);
        }
    }
    cJSON_Delete(json_root);
}
void setting_versionPatch(void)
{
    u8 vMAR = (setting.defaultConf.version >> 16) & 0xFF ;
    u8 vMIN = (setting.defaultConf.version >> 8) & 0xFF;

    if(vMAR != VERSION_MAJOR || vMIN == 0 || vMIN == 255)
    {
        //检查恢复
        oc_http_param_t *HttpParam = NULL;
        u8 url[256] = {0};
        u8 header[256] = {0};
        char imei[MAX_IMEI_LENGTH + 1] = {0};
        INT32 ret;
        fibo_get_imei((UINT8 *)imei, CFW_SIM_0);
        HttpParam = fibo_http_new();

        HttpParam->timeout = 10;
        HttpParam->cbReadBody = setting_versionPatch_cb;
        HttpParam->respCode = 500;
        HttpParam->enHttpReadMethod = OC_USER_CALLBACK;
        //memset(HttpParam->url, 0, OC_HTTP_URL_LEN + 1);
        sprintf(url, "http://api.xiaoantech.com/ebike/v1/deviceInfo?agentId=1&imei=%s", imei);
        strncpy((char *)HttpParam->url, url, strlen((const char *)url));
        snprintf((char *)header, 256, "GET %s HTTP/1.1\r\nHost: api.xiaoantech.com\r\nUser-Agent: curl/7.47.0\r\nAccept: */*\r\nContent-Type: application/json\r\nxc-access-token: D23E73CDEB885B7774E4878B310F0CBB\r\n\r\n",
                 url);
        LOG_DEBUG("header: %s", header);
        ret = fibo_http_get(HttpParam, (u8 *)header);
        LOG_DEBUG("get ret : %d code:%d", ret, HttpParam->respCode);
        fibo_http_delete(HttpParam);
    }
}

void sysConf_initial(void)
{
    /* default.conf */
    setting.defaultConf.version =  (255 << 16) | (255 << 8) | 255;
    setting.defaultConf.productType = DEVICE_TYPE;
    setting.defaultConf.bmsType = TYPE_NOBMS;
    setting.defaultConf.ccuType = TYPE_XIAOANCCU;
    setting.defaultConf.helmetType = TYPE_NOHELMET;
    setting.defaultConf.saddleType = TYPE_BUCKLESADDLE;
    setting.defaultConf.backWheelType = TYPE_NOBACKWHEEL;
    setting.defaultConf.lightCtrlType = TYPE_CCUHEADLIGHT;
    setting.defaultConf.batteryType = TYPE_BATTERY48V;
    setting.defaultConf.isOverSpeedOn = SETTING_DFT_OVERSPEED;
    setting.defaultConf.isMoveAlarmOn = SETTING_DFT_MOVEALARM;
    setting.defaultConf.isNightVoiceOn = SETTING_DFT_NIGHTVO;
    setting.defaultConf.isShakeAlarmOn = SETTING_DFT_SHARKAL;
    setting.defaultConf.isTurnOverEnable = SETTING_DFT_TURNOVER;
    setting.defaultConf.isAutoLockOn = SETTING_DFT_AUTOLOCK;
    setting.defaultConf.audioRatio = 1.0f;
    setting.defaultConf.etcSpeed = ETC_DEFAULT_SPEED;

    /* setting.conf */
    setting.settingConf.loglevel = LOG_LEVEL_INFO;
    setting.settingConf.isFenceEnable = SETTING_DFT_FENCE;
    setting.settingConf.isRFIDEnable = SETTING_DFT_RFID; //默认不打开RFID定点功能
    setting.settingConf.isIgnoreFence = SETTING_DFT_IGNORE;
    setting.settingConf.isIgnoreFenceOnce = SETTING_DFT_IGNORE_ONEC;
    setting.settingConf.isSleepEnable = SETTING_DFT_SLEEP;
    setting.settingConf.isTBeaconEnable = SETTING_DFT_BEACON;
    setting.settingConf.isAgpsEnable = SETTING_DFT_AGPS;
    setting.settingConf.freq_move = SETTING_DFT_MOVEPERIOD;
    setting.settingConf.freq_norm = SETTING_DFT_NORMPERIOD;
    setting.settingConf.autoLockPeriod = SETTING_DFT_AUTOLOCKPERIOD;
    setting.settingConf.diffAngle = SETTING_DFT_TURNANGLE;
    setting.settingConf.periodDiffAngleAudio = SETTING_DFT_TURNAUDIO;
    setting.settingConf.isMX5EEAudio1K = L_FALSE; //只有最先生产的5200台语音放大电阻1K的设备才打开

    setting.settingConf.forceLock = L_FALSE;
    setting.settingConf.audioType = SETTING_DEF_AUTYPE;
    memset((char *)setting.settingConf.overSpeedUrl, 0, MAX_URL_LEN);
    setting.settingConf.overSpeedVolume = OVERSPEED_VOLUME_DEFAULT;
    setting.settingConf.checkOverSpeedTime = 3;
    setting.settingConf.overSpeedCrc = 0;
    setting.settingConf.move_threshold = SETTING_MOVE_THRESHOLD;

    setting.settingConf.devInstallMode = 0; //默认中控安装方式为：纵向安装，线朝车尾
    setting.settingConf.token = BLE_DFT_TOKEN;
    memcpy(setting.settingConf.ble_name, BLE_DFT_NAME, strlen(BLE_DFT_NAME));
    setting.settingConf.etcFuncSwitch = ETC_DEFAULT_FUNCSWITCH;
    setting.settingConf.etcIsSlowStart = ETC_DEFAULT_ISSLOWSTART;
    setting.settingConf.etcLimitCurrent_100mA = ETC_DEFAULT_LIMITCURRENT;
    setting.settingConf.etcProtectVoltage_100mV = ETC_DEFAUTL_PROTECTVOLTAGE;
    setting.settingConf.protectVoltage = SETTING_DFT_PROTECTVOLATGE;
    setting.settingConf.restoreVoltage = SETTING_DFT_RESTOREVOLATGE;
    setting.settingConf.mpuAvoidanceRatio = SETTING_MPU_AVOIDANCE_RATIO;
    setting.settingConf.fenceVersion = 0; //unuse
    setting.settingConf.displaylog = L_FALSE;
    setting.settingConf.isEtcSOC = L_FALSE;
    setting.settingConf.activeFreqSOC = 0; //默认主动获取一线通SOC频率为0分钟
    setting.settingConf.beaconRssi = SETTING_DFT_BEACONRSSI; //默认道钉阈值为70
    setting.settingConf.gpsType = GPS_UBLOX_8130;
    setting.settingConf.accleType = ACCLE_LIS3DH;
    setting.settingConf.isEtcAccProtect = L_TRUE; //默认每秒控制器开电门保护
    setting.settingConf.isEtcDefendProtect = L_FALSE; //默认每秒控制器撤防不做保护
    setting.settingConf.isDefaultSpeed = L_TRUE;
    setting.settingConf.isNmeaOut = L_FALSE;
    memset(setting.settingConf.imsi, 0, MAX_IMSI_LENGTH + 1);
    memset(setting.settingConf.ccid, 0, MAX_CCID_LENGTH + 1);
    setting.settingConf.etcSpeedSource = ETC_FIRST_USE_SPEED;
    setting.settingConf.etcSpeedRatio = 1.0;
    setting.settingConf.etcHallRatio = 0.067029; //(pulse * 7200 * 14 * 2.54 * PI / (100000 * 6 * 20))
    if(memcmp(setting.defaultConf.name, "AT-MX5Z5", strlen("AT-MX5Z5")) == 0)
    {
        setting.settingConf.etcHallRatio = 0.058811; //(pulse * 3600 * 0.39 * PI / (1000 * 25 * 3))
    }
    setting.settingConf.isEtcOverspeedBit = L_TRUE; //默认使用控制器超速故障位
    setting.settingConf.overspeedThreshold = 15; //默认超速报警阈值为15km/h

    /* status.conf 重启后不丢失的易修改状态*/
    setting.statusConf.acc = L_FALSE;
    setting.statusConf.isDefend = L_FALSE;
    setting.statusConf.OperatingSaddlelock = L_FALSE;
    setting.statusConf.rebootType = REBOOT_NORMAL;  // 初始化为正常开机
    setting.statusConf.isTerminateETCUpgrade = 0;
    setting.statusConf.etcUpgradeFlag = 0;
    setting.statusConf.etcVersion = 0;
    setting.statusConf.etcUpgradeVersion = 0;
    setting.statusConf.etcFirmwareCRC = 0;
    setting.statusConf.isTerminateBMSUpgrade = 0;
    setting.statusConf.bmsUpgradeFlag = 0;
    setting.statusConf.bmsVersion = 0;
    setting.statusConf.bmsUpgradeVersion = 0;
    setting.statusConf.bmsFirmwareCRC = 0;
    setting.statusConf.coreUpdateCount = 0;
    setting.statusConf.bmsSoc = 0;
    setting.statusConf.bmsSendPeriod = SETTING_DFT_BMSPERIOD;
    setting.statusConf.gpsBaudrateUpdateFlag = 0;
    setting.statusConf.helmetTargetStatus = HELMET_NULL;
    
    /* server.conf 非默认服务器信息*/
    setting.serverConf.port = 9880;
    setting.serverConf.ipaddr[0] = 112;
    setting.serverConf.ipaddr[1] = 74;
    setting.serverConf.ipaddr[2] = 77;
    setting.serverConf.ipaddr[3] = 182;
    setting.serverConf.addr_type = ADDR_TYPE_IP;

    /* 备份服务器信息，不做固化 */
    setting.srvBakConf.port = 9880;
    setting.srvBakConf.ipaddr[0] = 112;
    setting.srvBakConf.ipaddr[1] = 74;
    setting.srvBakConf.ipaddr[2] = 77;
    setting.srvBakConf.ipaddr[3] = 182;
    setting.srvBakConf.addr_type = ADDR_TYPE_IP;

    setting.coreVersion = 0x55AA55;

    setting_ApplyConf(); //检查default + 应用setting.conf
    statusConf_restore();
    serverConf_restore();
    fence_getFenceFromFile(&data_getData()->fence);//更新围栏数据
    statusConf_save();    //兼容代码,防止数据丢失立刻保存一份

    if((setting_getVerisonType() == VERSION_TYPE_MX5D2) || (setting_getVerisonType() == VERSION_TYPE_MX5D4))
    {
        if(!setting.settingConf.ledConfig.repeatLedType && !setting.settingConf.ledConfig.startTime && !setting.settingConf.ledConfig.endTime)//没有设置过
        {
            setting.settingConf.ledConfig.isOn = 1;
            setting.settingConf.ledConfig.repeatLedType = CAR_REDLED;
            setting.settingConf.ledConfig.startTime = 20*3600;//晚上8点
            setting.settingConf.ledConfig.endTime = 23*3600;
            setting.settingConf.ledConfig.repeatMode = CAR_BLINKSLOW;
            setting.settingConf.ledConfig.isRepeat = 1;
        }
    }

    car_accAction();
    setting_fixHardware(); //利用产品型号定位硬件模块类型
    timer_startRepeat(TIMER_SETTING_LISTEN, TIMER_S, 1, setting_listnerHandler);
    return ;
}

int setting_setRebootType(u16 rebootType)
{
    if(rebootType >= REBOOT_TYPEMAX)
    {
        LOG_DEBUG("save reboot_type err %d", rebootType);
        return -1;
    }
    if(rebootType != setting.statusConf.rebootType)
    {
        setting.statusConf.rebootType = rebootType;
        return statusConf_save();
    }
    return 0;
}

u8 setting_getVerisonType(void)
{
    return (setting.defaultConf.version >> 8) & 0xFF;
}

#define AUTOCHECKCORE_MAX 5
static char coreURL[MAX_URL_LEN] = {0};
static void setting_UpgradeFirmware(int result, uint8_t *data, int data_len)
{
    if(result == 0 && data)
    {
        setting_setRebootType(REBOOT_UPGRADE);
        int ret = fibo_firmware_handle((char *)data, data_len);
        if(0 < ret)
        {
            LOG_ERROR("[setting] fibo_firmware_handle failed");
            return;
        }
        LOG_INFO("[setting] Firmware upgrade success");
    }
}

L_BOOL setting_isCoreUnmatch(void)
{
    if((setting.coreVersion & 0xff) == 14)
    {
#if defined(COREVERSION23)
        if(strlen(COREURL_14_23) < MAX_URL_LEN) //如果当前获取的内核是14,但是SDK是23
        {
            strcpy(coreURL, COREURL_14_23); //赋值相匹配的URL
            return L_TRUE;
        }
#endif
    }
    return L_FALSE;
}

int setting_checkCore(void)
{
    if(setting_isCoreUnmatch() == L_TRUE)
    {
        LOG_DEBUG("[system] core conflict%d", setting.statusConf.coreUpdateCount);
        if(setting.statusConf.coreUpdateCount++ < AUTOCHECKCORE_MAX)
        {
            http_get(coreURL, setting_UpgradeFirmware);
            settingConf_save();
        }
        else
        {
            LOG_WARNING("[system] update core protect");
        }
        return 0;
    }
    setting.statusConf.coreUpdateCount = 0;
    statusConf_save();
    LOG_DEBUG("[system] core match");
    return 0;
}

void *setting_allocConfig(int *pSize)
{
    char *pRet = NULL;
    u32 version = _htonl(setting.defaultConf.version);
    u16 productType = _htons(setting.defaultConf.productType);
    u8 audioRatio = (u8)(setting.defaultConf.audioRatio * 100);

    TLV_DATA_HEADER *tlv_header = tlv_createHeader();
    if(!tlv_header)
    {
        return -1;
    }

    tlv_addData(&tlv_header, TLV_TAG_CONVERSION, &version, sizeof(version));
    tlv_addData(&tlv_header, TLV_TAG_PRONAME, &setting.defaultConf.name, strlen(setting.defaultConf.name));
    tlv_addData(&tlv_header, TLV_TAG_PROTYPE, &productType, sizeof(productType));
    tlv_addData(&tlv_header, TYPE_ISOVERSPEEDON, &setting.defaultConf.isOverSpeedOn, sizeof(setting.defaultConf.isOverSpeedOn));
    tlv_addData(&tlv_header, TYPE_ISMOVEALARMON, &setting.defaultConf.isMoveAlarmOn, sizeof(setting.defaultConf.isMoveAlarmOn));
    tlv_addData(&tlv_header, TYPE_AUDIORATIO, &audioRatio, sizeof(audioRatio));
    tlv_addData(&tlv_header, TYPE_ISNIGHTVOICEON, &setting.defaultConf.isNightVoiceOn, sizeof(setting.defaultConf.isNightVoiceOn));
    tlv_addData(&tlv_header, TYPE_SADDLE, &setting.defaultConf.saddleType, sizeof(setting.defaultConf.saddleType));
    tlv_addData(&tlv_header, TYPE_BACKWHEEL, &setting.defaultConf.backWheelType, sizeof(setting.defaultConf.backWheelType));
    tlv_addData(&tlv_header, TYPE_ISSHAKEALARMON, &setting.defaultConf.isShakeAlarmOn, sizeof(setting.defaultConf.isShakeAlarmOn));
    tlv_addData(&tlv_header, TYPE_CONTROLLIGHT, &setting.defaultConf.lightCtrlType, sizeof(setting.defaultConf.lightCtrlType));
    tlv_addData(&tlv_header, TYPE_CCU, &setting.defaultConf.ccuType, sizeof(setting.defaultConf.ccuType));
    tlv_addData(&tlv_header, TYPE_BMS, &setting.defaultConf.bmsType, sizeof(setting.defaultConf.bmsType));
    tlv_addData(&tlv_header, TYPE_BATTERY, &setting.defaultConf.batteryType, sizeof(setting.defaultConf.batteryType));
    tlv_addData(&tlv_header, TYPE_HELMET, &setting.defaultConf.helmetType, sizeof(setting.defaultConf.helmetType));
    tlv_addData(&tlv_header, TYPE_ISAUTOLOCKON, &setting.defaultConf.isAutoLockOn, sizeof(setting.defaultConf.isAutoLockOn));
    tlv_addData(&tlv_header, TYPE_ETC_SPEED, &setting.defaultConf.etcSpeed, sizeof(setting.defaultConf.etcSpeed));
    tlv_addData(&tlv_header, TYPE_ISTURNOVERON, &setting.defaultConf.isTurnOverEnable, sizeof(setting.defaultConf.isTurnOverEnable));

    pRet = Malloc(tlv_header->payloadLen);
    memcpy(pRet, tlv_header->payload, tlv_header->payloadLen);
    *pSize = tlv_header->payloadLen;
    tlv_deleteHeader(tlv_header);
    return pRet;
}
