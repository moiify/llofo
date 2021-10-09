/*
 * bleMsg.c
 *
 *  Created on: 2018.08.21
 *      Author: lc
 */
#include <unistd.h>
#include <string.h>

#include "fibo_opencpu.h"

#include "car.h"
#include "msg.h"
#include "log.h"
#include "data.h"
#include "audio.h"
#include "audio_driver.h"
#include "utils.h"
#include "socket.h"
#include "bioMsg.h"
#include "bleMsg.h"
#include "userMsg.h"
#include "version.h"
#include "setting.h"
#include "da14580.h"
#include "hardware.h"
#include "protocol.h"
#include "user_timer.h"
#include "gps_parse.h"
#include "nmea/gmath.h"
#include "RFID.h"
#include "flash.h"

static int tempBleIdx = -1;
static int tempBleVolume = -1;
static uint8_t g_isSetDefending = L_FALSE;

uint8_t bleMsg_isSetDefending(void)
{
    return g_isSetDefending;
}

int da14580_sendBleMsg(uint8_t cmd, uint8_t *data, uint8_t len)
{
    uint8_t *send_data = (uint8_t *)da14580_allocMsg(BLE_ADDRESS, cmd, data, len);
    if(send_data)
    {
        da14580_sendUartData(send_data, MSG_HEADER_XA_LEN + len + 1); //+1+1: code + checksum
        free_msg(send_data);
        return 0;
    }
    return -1;
}

static int bleMsg_sendBleResponse(uint8_t cmd, uint8_t code)
{
    return da14580_sendBleMsg(cmd, &code, 1);
}

static int bleMsg_sendBleResponseWithType(uint8_t cmd, BLE_RESPONSE_WITHTYPE *code,uint8_t len)
{
    return da14580_sendBleMsg(cmd, code, len);
}

__attribute__((unused)) static bool da14580_isTestCheckPass(uint8_t *data)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)data;
    uint8_t i = 0;
    uint8_t checksum = msg->cmd + msg->length;
    for(i = 0; i < msg->length; i++)
    {
        checksum += msg->data[i];
    }

    if(checksum == msg->data[msg->length])
    {
        return L_TRUE;
    }
    return L_FALSE;
}

__attribute__((unused)) static bool bleMsg_isTokenPass(uint32_t token)
{
    return setting.settingConf.token == token ? L_TRUE : L_FALSE;
}

static int bleMsg_setDefend(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    uint8_t sw = bleMsg->data[0];

    int idx = 0;
    int volume = -1;
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(msg->length > sizeof(uint32_t) + 1)
    {
        idx = bleMsg->data[1];
        if(msg->length > sizeof(uint32_t) + 2)
        {
            volume = bleMsg->data[2];
        }
    }

    if(sw == 1)
    {
        if(SETTING_NOTSTOP == setting_setDefend(L_TRUE))
        {
            bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_NOTSTOP);
        }
        else
        {
            bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);

            if(idx > 0 && idx < AUDIO_MAX_NUMBER)
            {
                if(volume >= 0 && volume <= 100)
                {
                    audio_playWithVolume(idx, volume);
                }
                else
                {
                    audio_play(idx);
                }
            }
            else
            {
                if(volume >= 0 && volume <= 100)
                {
                    audio_playWithVolume(AUDIO_DEFEND_ON, volume);
                }
                else
                {
                    audio_play(AUDIO_DEFEND_ON);
                }
            }
        }
        return 0;
    }
    else if(sw == 0)
    {    
        if(setting.settingConf.forceLock)
        {
            bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_ACCESSDENY);
            return 0;
        }

        if(SETTING_OUTSERVICE == setting_setAcc(L_TRUE))
        {
            bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_ACCESSDENY);
            return 0;
        }

        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);

        data_getData()->tBeaconInfo.event = EVENT_NOTBEACON;//标志道钉数据不可用
        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_ACC_ON, volume);
            }
            else
            {
                audio_play(AUDIO_ACC_ON);
            }
        }
        return 0;
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
    return -1;
}

static int bleMsg_getStatus(void *m)
{
    uint8_t result = 0;
    BLE_STATUS_MSG data = {0};
    DATA *pData = data_getData();
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    INT32 csq;
    INT32 ber;

    fibo_get_csq(&csq, &ber);
    result |= setting.statusConf.isDefend ? SW_MASK_DEFEND : 0;
    result |= (car_isAccOn() || setting.statusConf.acc) ? SW_MASK_ACC : 0;
    result |= car_isBackWheelLocked() ? SW_MASK_WHEEL : 0;
    result |= car_isSaddleLocked() ? SW_MASK_SEAT : 0;
    result |= car_isPowerExistence() ? SW_MASK_POWER : 0;
    result |= car_isHelmetLocked() ? 0 : BLE_SW_HELMETUNLOCK;
    result |= pData->isMoving ? ST_MASK_MOVE : 0;
    result |= pData->isWheelSpinning ? ST_MASK_WHEEL : 0;

    data.sw = result;
    data.gsm = csq;

    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && pData->staticBikeBat_mV != 0)
    {
        data.volatge_mV = _htonl(pData->staticBikeBat_mV);
    }
    else
    {
        data.volatge_mV = _htonl(pData->vehicleBattery_mV);
    }

    da14580_sendDATA(BLE_ADDRESS, msg->cmd, (uint8_t *)&data, sizeof(BLE_STATUS_MSG));
    return 0;
}

static int bleMsg_setServer(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    char buf[64] = {0};
    bool rc = L_FALSE;
    DATA *pData = data_getData();
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;

    int dataLen = msg->length - sizeof(BLE_MSG_DATA);
    if(dataLen == 0) //如果消息为空则视为获取
    {
        char server[MAX_DOMAIN_NAME_LEN] = {0};
        if(setting.serverConf.addr_type == ADDR_TYPE_DOMAIN)
        {
            snprintf(server, MAX_DOMAIN_NAME_LEN + 6, "%s:%d", setting.serverConf.domain, setting.serverConf.port);
        }
        else if(setting.serverConf.addr_type == ADDR_TYPE_IP)
        {
            snprintf(server, MAX_IP_PORT_LEN, "%u.%u.%u.%u:%d", setting.serverConf.ipaddr[0], setting.serverConf.ipaddr[1], setting.serverConf.ipaddr[2], setting.serverConf.ipaddr[3], setting.serverConf.port);
        }
        return da14580_sendBleMsg(msg->cmd, (uint8_t *)server, strlen(server));
    }

    memcpy(buf, bleMsg->data, msg->length - 2);
    do
    {
        int count = 0;
        u32 port = 0;
        u32 ip[4] = {0};
        char domain[MAX_DOMAIN_NAME_LEN] = {0};

        count = sscanf(buf, "%u.%u.%u.%u:%u", &ip[0], &ip[1], &ip[2], &ip[3], &port);
        if(5 == count)
        {
            if(check_ip(ip[0], ip[1], ip[2], ip[3]))
            {
                LOG_DEBUG("Ip cannot be %u.%u.%u.%u.", ip[0], ip[1], ip[2], ip[3]);
                bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
                return -1;
            }
            if(check_port(port))
            {
                LOG_DEBUG("Port cannot be %d.", port);
                bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
                return -1;
            }

            if(data_isLogined())
            {
                memcpy(&setting.srvBakConf, &setting.serverConf, sizeof(SERVER_CONF)); //保存备份服务器信息
            }

            setting.serverConf.addr_type = ADDR_TYPE_IP;
            setting.serverConf.ipaddr[0] = (uint8_t)ip[0];
            setting.serverConf.ipaddr[1] = (uint8_t)ip[1];
            setting.serverConf.ipaddr[2] = (uint8_t)ip[2];
            setting.serverConf.ipaddr[3] = (uint8_t)ip[3];
            setting.serverConf.port = (uint16_t)port;
            rc = L_TRUE;
            break;
        }

        count = sscanf(buf, "%[^:]:%u", domain, &port);
        if(2 == count)
        {
            if(check_port(port))
            {
                LOG_DEBUG("Port cannot be %d.", port);
                bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
                return -1;
            }

            if(data_isLogined())
            {
                memcpy(&setting.srvBakConf, &setting.serverConf, sizeof(SERVER_CONF)); //保存备份服务器信息
            }

            setting.serverConf.addr_type = ADDR_TYPE_DOMAIN;
            strncpy(setting.serverConf.domain, domain, MAX_DOMAIN_NAME_LEN);
            setting.serverConf.port = (uint16_t)port;
            rc = L_TRUE;
            break;
        }
    }
    while (L_FALSE);

    if(rc == L_TRUE)
    {
        //登陆响应后再保存，否则超时切回原服务器
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
        setting_serverReinit();
        timer_start(TIMER_CHANGESERVER_TIMEOUT, TIMER_S, 60, setting_setServerTimeout);
    }
    else
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
    }

    return 0;
}

static int bleMsg_reboot(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    setting_setRebootType(REBOOT_COMAND);
    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    fibo_taskSleep(500);
    fibo_softReset();
    return 0;
}

static int bleMsg_setAcc(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    uint8_t sw = bleMsg->data[0];
    int idx = 0;
    int volume = -1;
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(msg->length > sizeof(uint32_t) + 1)
    {
        idx = bleMsg->data[1];
        if(msg->length > sizeof(uint32_t) + 2)
        {
            volume = bleMsg->data[2];
        }
    }

    if(1 == sw)
    {    
        if(setting.settingConf.forceLock)
        {
            bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_ACCESSDENY);
            return 0;
        }

        if(SETTING_OUTSERVICE == setting_setAcc(L_TRUE))
        {
            bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_ACCESSDENY);
            return 0;
        }

        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);

        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_ACC_ON, volume);
            }
            else
            {
                audio_play(AUDIO_ACC_ON);
            }
        }
        return 0;
    }
    else if(0 == sw)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);

        setting_setAcc(L_FALSE);
        setting_setDefend(L_FALSE); //蓝牙熄火时撤防
        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_ACC_OFF, volume);
            }
            else
            {
                audio_play(AUDIO_ACC_OFF);
            }
        }
        return 0;
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
    return -1;
}

static int bleMsg_playAudio(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    u8 idx = bleMsg->data[0];
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    audio_play(idx);

    if(idx == AUDIO_SEEK || idx == AUDIO_WHO_AM_I)
    {
        car_blinkLight();
    }
    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);

    return 0;
}

static int bleMsg_shutDown(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    if(car_isPowerExistence() || data_getData()->vehicleBattery_mV > setting.settingConf.restoreVoltage)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return 0;
    }
    setting_setRebootType(REBOOT_NORMAL);
    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    fibo_taskSleep(500);
    fibo_softPowerOff();
    return 0;
}

static int bleMsg_changeServer(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    uint8_t sw = bleMsg->data[0];
    if(sw == 0)
    {
        /* 切服务回小安 */
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
        setting.serverConf.addr_type = ADDR_TYPE_IP;
        setting.serverConf.ipaddr[0] = 112;
        setting.serverConf.ipaddr[1] = 74;
        setting.serverConf.ipaddr[2] = 77;
        setting.serverConf.ipaddr[3] = 182;
        setting.serverConf.port = 9880;
        serverConf_save();
        timer_start(TIMER_SOCKET_CLOSE, TIMER_MS, 500, setting_serverReinit);
    }
    else if(sw == 1)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_UNSUPPORT);
    }
    return 0;
}

static int bleMsg_setSaddle(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    uint8_t sw = bleMsg->data[0];
    int idx = 0;
    int volume = -1;
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(msg->length > sizeof(uint32_t) + 1)
    {
        idx = bleMsg->data[1];
        if(msg->length > sizeof(uint32_t) + 2)
        {
            volume = bleMsg->data[2];
        }
    }

    if(1 == sw)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
        car_lockSaddle();

        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_BEEP, volume);
            }
            else
            {
                audio_play(AUDIO_BEEP);
            }
        }
        return 0;
    }
    else if(0 == sw)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
        car_unlockSaddle();

        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_BEEP, volume);
            }
            else
            {
                audio_play(AUDIO_BEEP);
            }
        }
        return 0;
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
    return -1;
}

static int bleMsg_setBackwheel(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    uint8_t sw = bleMsg->data[0];
    int idx = 0;
    int volume = -1;
    if(msg->length > sizeof(uint32_t) + 1)
    {
        idx = bleMsg->data[1];
        if(msg->length > sizeof(uint32_t) + 2)
        {
            volume = bleMsg->data[2];
        }
    }

    if(1 == sw)
    {
        if(data_getData()->isWheelSpinning || data_getData()->isMoving)
        {
            bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_NOTSTOP);
            return -1;
        }
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
        car_lockBackWheel();

        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_BEEP, volume);
            }
            else
            {
                audio_play(AUDIO_BEEP);
            }
        }
        return 0;
    }
    else if(0 == sw)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
        car_unlockBackWheel();

        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_BEEP, volume);
            }
            else
            {
                audio_play(AUDIO_BEEP);
            }
        }
        return 0;
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
    return -1;
}

static int bleMsg_getCCID(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    uint8_t ccid[32] = {0};
    uint8_t ccid_bcd[10] = {0};
    fibo_get_ccid(ccid);
    StringToHex(ccid, ccid_bcd, 20);
    LOG_BIN((const char *)ccid_bcd, 10);
    LOG_DEBUG("send ccid to ble: %s", ccid);
    da14580_sendDATA(BLE_ADDRESS, msg->cmd, ccid_bcd, sizeof(ccid_bcd));
    return 0;
}

static int bleMsg_getGPS(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    DA14580_GPS_MSG gps = {0};
    DATA *pData = data_getData();
    uint16_t course = (uint16_t)(pData->lastPosition.nmeaInfo.direction + 0.5);

    if(pData->lastPosition.isGPS)
    {
        gps.gps.timestamp = _htonl(pData->lastPosition.timestamp);
        gps.gps.longitude = nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lon);
        gps.gps.latitude = nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lat);
        gps.gps.course = _htons(course);
        gps.gps.speed = (uint8_t)(pData->lastPosition.nmeaInfo.speed + 0.5);
    }

    da14580_sendDATA(msg->address, msg->cmd, (uint8_t *)&gps, sizeof(DA14580_GPS_MSG));
    return 0;
}

static int bleMsg_getSimInfo(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    uint8_t imsi[32] = {0};
    fibo_get_imsi(imsi);   
    da14580_sendDATA(msg->address, msg->cmd, imsi, MAX_IMSI_LENGTH);
    return 0;
}

static int bleMsg_setDefendOn(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    int idx = 0;
    int volume = -1;
    if(msg->length > sizeof(uint32_t))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(uint32_t) + 1)
        {
            volume = bleMsg->data[1];
        }
    }

    if(SETTING_NOTSTOP == setting_setDefend(L_TRUE))
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_NOTSTOP);
    }
    else
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);

        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_DEFEND_ON, volume);
            }
            else
            {
                audio_play(AUDIO_DEFEND_ON);
            }
        }
    }
    return 0;
}

static int bleMsg_setAccOn(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    int idx = 0;
    int volume = -1;
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(msg->length > sizeof(uint32_t))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(uint32_t) + 1)
        {
            volume = bleMsg->data[1];
        }
    }
    
    if(setting.settingConf.forceLock)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_ACCESSDENY);
        return 0;
    }

    if(SETTING_OUTSERVICE == setting_setAcc(L_TRUE))
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_ACCESSDENY);
        return 0;
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);

    if(idx > 0 && idx < AUDIO_MAX_NUMBER)
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(idx, volume);
        }
        else
        {
            audio_play(idx);
        }
    }
    else
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(AUDIO_ACC_ON, volume);
        }
        else
        {
            audio_play(AUDIO_ACC_ON);
        }
    }
    timer_stop(TIMER_RELEASE_ELOCK);
    return 0;
}

static int bleMsg_setAccOff(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    int idx = 0;
    int volume = -1;
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(msg->length > sizeof(uint32_t))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(uint32_t) + 1)
        {
            volume = bleMsg->data[1];
        }
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    setting_setAcc(L_FALSE);
    setting_setDefend(L_FALSE);
    data_getData()->tBeaconInfo.event = EVENT_NOTBEACON;//标志道钉数据不可用

    if(idx > 0 && idx < AUDIO_MAX_NUMBER)
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(idx, volume);
        }
        else
        {
            audio_play(idx);
        }
    }
    else
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(AUDIO_ACC_OFF, volume);
        }
        else
        {
            audio_play(AUDIO_ACC_OFF);
        }
    }
    return 0;
}

static int bleMsg_unlockWheel(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    int idx = 0;
    int volume = -1;
    if(msg->length > sizeof(uint32_t))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(uint32_t) + 1)
        {
            volume = bleMsg->data[1];
        }
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    car_unlockBackWheel();

    if(idx > 0 && idx < AUDIO_MAX_NUMBER)
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(idx, volume);
        }
        else
        {
            audio_play(idx);
        }
    }
    else
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(AUDIO_BEEP, volume);
        }
        else
        {
            audio_play(AUDIO_BEEP);
        }
    }
    return 0;
}

static int bleMsg_lockWheel(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    int idx = 0;
    int volume = -1;
    if(msg->length > sizeof(uint32_t))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(uint32_t) + 1)
        {
            volume = bleMsg->data[1];
        }
    }

    if(data_getData()->isWheelSpinning || data_getData()->isMoving)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_NOTSTOP);
        return -1;
    }
    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    car_lockBackWheel();

    if(idx > 0 && idx < AUDIO_MAX_NUMBER)
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(idx, volume);
        }
        else
        {
            audio_play(idx);
        }
    }
    else
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(AUDIO_BEEP, volume);
        }
        else
        {
            audio_play(AUDIO_BEEP);
        }
    }
    return 0;
}

static int bleMsg_unlockSaddle(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    __attribute__((unused)) int idx = 0;
    __attribute__((unused)) int volume = -1;
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && !setting_isDefendOn())  //只在设防下能开电池仓锁
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(msg->length > sizeof(uint32_t))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(uint32_t) + 1)
        {
            volume = bleMsg->data[1];
        }
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    car_unlockSaddle();
    return 0;
}

static int bleMsg_lockSaddle(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    int idx = 0;
    int volume = -1;
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(msg->length > sizeof(uint32_t))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(uint32_t) + 1)
        {
            volume = bleMsg->data[1];
        }
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    car_lockSaddle();

    if(idx > 0 && idx < AUDIO_MAX_NUMBER)
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(idx, volume);
        }
        else
        {
            audio_play(idx);
        }
    }
    else
    {
        if(volume >= 0 && volume <= 100)
        {
            audio_playWithVolume(AUDIO_BEEP, volume);
        }
        else
        {
            audio_play(AUDIO_BEEP);
        }
    }
    return 0;
}

static int bleMsg_getStatus_V2(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    DATA *pData = data_getData();
    DA14580_STATUS_V2_MSG status = {0};
    uint16_t result = 0;
    uint32_t voltage = 0;
    INT32 csq;
    INT32 ber;

    fibo_get_csq(&csq, &ber);
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && pData->staticBikeBat_mV != 0)
    {
        voltage = pData->staticBikeBat_mV;
    }
    else
    {
        voltage = pData->vehicleBattery_mV;
    }

    result |= setting_isDefendOn() ? BLE_SW_MASK_DEFEND : 0;
    result |= (car_isAccOn() || setting.statusConf.acc) ? BLE_SW_MASK_ACC : 0;
    result |= car_isBackWheelLocked() ? BLE_SW_MASK_WHEEL : 0;
    result |= car_isSaddleLocked() ? BLE_SW_MASK_SEAT : 0;
    result |= car_isPowerExistence() ? BLE_SW_MASK_POWER : 0;
    result |= pData->isLogined ? BLE_SW_MASK_LOGIN : 0;
    result |= setting.defaultConf.isAutoLockOn ? BLE_SW_MASK_AUTOLOCKON : 0;
    result |= setting.defaultConf.isOverSpeedOn ? BLE_SW_MASK_OVERSPEEDON : 0;

    if(setting.defaultConf.helmetType != TYPE_NOHELMET)
    {
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            result |= car_isHelmetClose() ? 0 : BLE_SW_MASK_HELMETREACT_V2; //0表示头盔锁在位
            result |= car_isHelmetAtPos() ? BLE_SW_MASK_HELMETLOCKED_V2 : 0; //1表示头盔锁已锁
        }
        else
        {
            result |= car_isHelmetLocked() ?  0 : BLE_SW_MASK_HELMETREACT_V2;
        }
    }
    
    status.event = 0;
    status.sw = _htons(result);
    status.gsm = csq;

    status.voltage[0] = (voltage >> 16) & 0xFF;
    status.voltage[1] = (voltage >> 8) & 0xFF;
    status.voltage[2] = (voltage) & 0xFF;
    
    status.version[0] = (setting.defaultConf.version >> 16) & 0xFF;
    status.version[1] = (setting.defaultConf.version >> 8) & 0xFF;
    status.version[2] = (setting.defaultConf.version >> 0) & 0xFF;

    status.bleVersion[0] = (pData->ble_state.version >> 16) & 0xFF;
    status.bleVersion[1] = (pData->ble_state.version >> 8) & 0xFF;
    status.bleVersion[2] = pData->ble_state.version & 0xFF;

    da14580_sendDATA(msg->address, msg->cmd, (uint8_t *)&status, sizeof(DA14580_STATUS_V2_MSG));
    return 0;
}

static int bleMsg_setAPN(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    char *apnData = bleMsg->data;
    int apnDataLen = msg->length - sizeof(BLE_MSG_DATA);
    
    if(apnDataLen == 0) //如果apn消息为空则视为获取当前apn
    {
        char str[512] = {0};
        strcat(str, setting.settingConf.apnname);
        strcat(str, ",");
        strcat(str, setting.settingConf.username);
        strcat(str, ",");
        strcat(str, setting.settingConf.password);
        return da14580_sendBleMsg(msg->cmd, str, strlen(str));
    }

    char *apnStr = (char *)malloc(apnDataLen + 1);
    char apnname[64] = {0};
    char username[64] = {0};
    char password[64] = {0};
    memcpy(apnStr, apnData, apnDataLen);
    apnStr[apnDataLen] = '\0';
    LOG_DEBUG("set apnStr: %s", apnStr);

    int cnt = sscanf(apnStr, "%[^,],%[^,],%[^,]", apnname, username, password);
    free_msg(apnStr);
    if(cnt < 1 || !strlen(apnname))
    {
        LOG_ERROR("set apn no apn.apn_name error!");
        return bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
    }
    
    LOG_DEBUG("set apn: name=%s, userName=%s, passwd=%s", apnname, username, password);
    strncpy(setting.settingConf.apnname, apnname, 64);
    strncpy(setting.settingConf.username, username, 64);
    strncpy(setting.settingConf.password, password, 64);
    settingConf_save(); //将apn存储到setting

    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    setting_setRebootType(REBOOT_COMAND);
    fibo_taskSleep(500);
    fibo_softReset();
    return 0;
}

static int bleMsg_getNetState(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_NET_STATE_MSG msgNetState = {0};

    uint8_t state = 0;
    uint32_t cnt = 0;
//    fsm_getNetState(&state, &cnt);

    msgNetState.state = state;
    msgNetState.cnt = _htonl(cnt);
    da14580_sendDATA(BLE_ADDRESS, msg->cmd, (uint8_t *)&msgNetState, sizeof(msgNetState));
    return 0;
}

static int bleMsg_getStatus_V3(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    DATA *pData = data_getData();
    DA14580_STATUS_V3_MSG status = {0};

    uint32_t result = 0;
    uint16_t voltage = 0;
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && pData->staticBikeBat_mV != 0)
    {
        voltage = pData->staticBikeBat_mV / 10;
    }
    else
    {
        voltage = pData->vehicleBattery_mV / 10;
    }
    int32_t lat = (int32_t)(nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lat) * (int64_t)1000000.f + 0.5);
    int32_t lon = (int32_t)(nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lon) * (int64_t)1000000.f + 0.5);
    uint16_t course = pData->lastPosition.nmeaInfo.direction;
    uint16_t hdop = pData->lastPosition.nmeaInfo.HDOP * 100;
    uint32_t totalMiles = setting.statusConf.totalMiles + pData->iMiles;
    INT32 csq;
    INT32 ber;

    fibo_get_csq(&csq, &ber);
    result |= setting.statusConf.isDefend ? SW_MASK_DEFEND : 0;
    result |= (car_isAccOn() || setting.statusConf.acc) ? SW_MASK_ACC : 0;
    result |= car_isBackWheelLocked() ? SW_MASK_WHEEL : 0;
    result |= car_isSaddleLocked() ? SW_MASK_SEAT : 0;
    result |= car_isPowerExistence() ? SW_MASK_POWER : 0;
    result |= pData->isWheelSpinning ? ST_MASK_WHEEL : 0;
    result |= pData->isMoving ? ST_MASK_MOVE : 0;
    result |= (pData->gpsSendPeriod_ms == setting.settingConf.freq_move * 1000) ? ST_MASK_FREQ : 0;
    result |= pData->mode == MODE_SLEEP ? ST_MASK_SLEEP : 0;
//    result |= setting.defaultConf.isMoveAlarmOn ? ST_MASK_ISMOVEALARM : 0;
    result |= setting.defaultConf.isOverSpeedOn ? ST_MASK_ISOVERSPEED : 0;
    result |= gps_getPosition()->isGPS ? 0 : ST_MASK_ISGPSUNFIXED;
    result |= setting.settingConf.isFenceEnable ? ST_MASK_ISFENCEENABLE : 0;
    result |= pData->isOutOfPoly ? ST_MASK_ISOUTOFSERVAERA : 0;
    // result |= car_isGSSLocked() ? BLE_SW_GSSLOCKED_V3 : 0;

    if(setting.defaultConf.helmetType != TYPE_NOHELMET)
    {
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            result |= car_isHelmetAtPos() ? BLE_SW_HELMETREACT_6 : 0; //6芯头盔锁的头盔在位信号
            result |= car_isHelmetClose() ? BLE_SW_HELMELOCK_6 : 0; //6芯头盔锁的锁到位信号
        }
        else
        {
            result |= car_isHelmetLocked() ?  BLE_SW_HELMETLOCKED_4 : 0;//4芯头盔锁的锁到位信号
        }
    }

    status.event = 0;
    status.sw = _htonl(result);
    status.gsm = csq;

    status.voltage = _htons(voltage);

    status.version[0] = (setting.defaultConf.version >> 16) & 0xFF;
    status.version[1] = (setting.defaultConf.version >> 8) & 0xFF;
    status.version[2] = (setting.defaultConf.version >> 0) & 0xFF;

    status.bleVersion[0] = (pData->ble_state.version >> 16) & 0xFF;
    status.bleVersion[1] = (pData->ble_state.version >> 8) & 0xFF;
    status.bleVersion[2] = pData->ble_state.version & 0xFF;

    status.timstamp = _htonl(pData->lastPosition.timestamp);
    status.lat = _htonl(lat);
    status.lon = _htonl(lon);
    status.speed = pData->lastPosition.nmeaInfo.speed;
    status.course = _htons(course);
    status.hdop = _htons(hdop);
    status.satelites = pData->lastPosition.nmeaInfo.satinfo.inuse;
    status.totalMiles = _htonl(totalMiles);

    da14580_sendDATA(msg->address, msg->cmd, (uint8_t *)&status, sizeof(DA14580_STATUS_V3_MSG));
    return 0;
}

static int bleMsg_getTBeaconInfo(void *data)
{
    DATA *pData = data_getData();
    DA14580_TBEACON_INFO_MSG tBeaconInfo = {0};
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)data;

    beaconInfo_t *pBeaconInfo = data_getTBeaconInfo(5);
    if(pBeaconInfo)
    {
        s32 lat = (s32)(gps_getGPSValue(pData->lastPosition.nmeaInfo.lat) * (s64)1000000.f + 0.5);
        s32 lon = (s32)(gps_getGPSValue(pData->lastPosition.nmeaInfo.lon) * (s64)1000000.f + 0.5);

        tBeaconInfo.event = 0;
        memcpy(tBeaconInfo.tBeaconAddr, pBeaconInfo->mac, 6);
        memcpy(tBeaconInfo.tBeaconId, pBeaconInfo->tBeaconID, 12);
        tBeaconInfo.tBeaconSOC = pBeaconInfo->tBeaconSOC;
        memcpy((u8 *)(&tBeaconInfo.tBeaconVsn), pBeaconInfo->tBeaconVersion, 2);
        tBeaconInfo.lat = _ntohl(lat);
        tBeaconInfo.lon = _ntohl(lon);
        tBeaconInfo.timestamp = _ntohl(rtc_getTimestamp());
    }
    else
    {
        memset((void *)(&tBeaconInfo), 0, sizeof(DA14580_TBEACON_INFO_MSG));
    }

    da14580_sendDATA(msg->address, msg->cmd, (u8 *)&tBeaconInfo, sizeof(DA14580_TBEACON_INFO_MSG));
    return 0;
}

static int bleMsg_SetDeffendOnWithTBeacon_successful(void)
{
    LOG_INFO("scan daoding successful");
    data_getData()->isWaitingTBeaconResult = L_FALSE;
    if(SETTING_NOTSTOP == setting_setDefend(L_TRUE))
    {
        return -1;
    }
    if(tempBleIdx >= 0 && tempBleIdx < ALARM_MAX_NUMBER)
    {
        if(tempBleVolume >= 0)
        {
            audio_playWithVolume(tempBleIdx, tempBleVolume);
        }
        else
        {
            audio_play(tempBleIdx);
        }
    }
    else
    {
        if(tempBleVolume >= 0)
        {
            audio_playWithVolume(AUDIO_DEFEND_ON, tempBleVolume);
        }
        else
        {
            audio_play(AUDIO_DEFEND_ON);
        }
    }
    return 0;
}

static int bleMsg_SetDeffendOnWithTBeacon_fail(void)
{
    LOG_INFO("scan daoding fail");
    data_getData()->isWaitingTBeaconResult = L_FALSE;
    if(tempBleVolume >= 0)
    {
        audio_playWithVolume(AUDIO_CAOZUOSHIBAI, tempBleVolume);
    }
    else
    {
        audio_play(AUDIO_CAOZUOSHIBAI);
    }
    return 0;
}

//带道钉设防
static int bleMsg_setDefendTBeacon(void *data)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)data;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    int idx = 0;
    int volume = -1;
    if(msg->length > sizeof(u32))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(u32) + 1)
        {
            volume = bleMsg->data[1];
        }
    }
    if(setting.settingConf.isTBeaconEnable)
    {
        LOG_INFO("start scan DaoDing for defend on");
        if(idx > 0 && idx < ALARM_MAX_NUMBER )
        {
            tempBleIdx = idx;
            if(volume > 0)
            {
                tempBleVolume = volume;
            }
            else
            {
                tempBleVolume = -1;
            }
        }
        else
        {
            tempBleIdx = -1;
            if(volume > 0)
            {
                tempBleVolume = volume;
            }
            else
            {
                tempBleVolume = -1;
            }
        }
        data_getData()->tBeaconInfo.event = EVENT_DEFENDONTBEACON;                    
        beaconInfo_t* info = data_getTBeaconInfo(3);
        if(!info)
        {
            LOG_ERROR("no beacon info");
            return bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        }
        if(info && info->dbm <= setting.settingConf.beaconRssi)
        {
            bleMsg_SetDeffendOnWithTBeacon_successful();
        }
        else
        {
            bleMsg_SetDeffendOnWithTBeacon_fail();
        }
        return 0;
    }
    bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
    return -1;
}

static int bleMsg_SetAccOnWithTBeacon_successful(u8 cmd)
{
    LOG_INFO("scan daoding successful");
    data_getData()->isWaitingTBeaconResult = L_FALSE;
    
    if(SETTING_OUTSERVICE == setting_setAcc(L_TRUE))
    {
        bleMsg_sendBleResponse(cmd, CODE_ERROR_ACCESSDENY);
        return 0;
    }

    if(tempBleIdx >= 0 && tempBleIdx < ALARM_MAX_NUMBER)
    {
        if(tempBleVolume >= 0)
        {
            audio_playWithVolume(tempBleIdx, tempBleVolume);
        }
        else
        {
            audio_play(tempBleIdx);
        }
    }
    else
    {
        if(tempBleVolume >= 0)
        {
            audio_playWithVolume(AUDIO_ACC_ON, tempBleVolume);
        }
        else
        {
            audio_play(AUDIO_ACC_ON);
        }
    }
    return 0;
}

static int bleMsg_SetAccOnWithTBeacon_fail(void)
{
    LOG_INFO("[BLE] scan TBeacon fail");
    data_getData()->isWaitingTBeaconResult = L_FALSE;
    if(tempBleVolume >= 0)
    {
        audio_playWithVolume(AUDIO_BEEP, tempBleVolume);
    }
    else
    {
        audio_play(AUDIO_BEEP);
    }
    return 0;
}

//带道钉撤防
static int bleMsg_setAccOnTBeacon(void *data)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)data;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    int volume = -1;
    int idx = 0;
    if(msg->length > sizeof(u32))
    {
        idx = bleMsg->data[0];
        if(msg->length > sizeof(u32) + 1)
        {
            volume = bleMsg->data[1];
        }
    }
    
    if(setting.settingConf.forceLock)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_ACCESSDENY);
        return 0;
    }
    
    if(setting.settingConf.isTBeaconEnable)
    {
        LOG_INFO("start scan DaoDing for blue acc on");
        if(idx > 0 && idx < ALARM_MAX_NUMBER)
        {
            tempBleIdx = idx;
            if(volume >= 0)
            {
                tempBleVolume = volume;
            }
            else
            {
                tempBleVolume = -1;
            }
        }
        else
        {
            tempBleIdx = -1;
            if(volume >= 0)
            {
                tempBleVolume = volume;
            }
            else
            {
                tempBleVolume = -1;
            }
        }
        data_getData()->tBeaconInfo.event = EVENT_ACCONTBEACON;
        beaconInfo_t* info = data_getTBeaconInfo(3);
        if(!info)
        {
            LOG_ERROR("no beacon info");
            return bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        }
        if(info && info->dbm <= setting.settingConf.beaconRssi)
        {
            bleMsg_SetAccOnWithTBeacon_successful(msg->cmd);
        }
        else
        {
            bleMsg_SetAccOnWithTBeacon_fail();
        }
        return 0;
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
    return -1;
}

static int bleMsg_setHelmet(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    uint8_t sw = bleMsg->data[0];
    int idx = 0;
    int volume = -1;
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_OPREATION);
        return -1;
    }
    if(msg->length > sizeof(uint32_t) + 1)
    {
        idx = bleMsg->data[1];
        if(msg->length > sizeof(uint32_t) + 2)
        {
            volume = bleMsg->data[2];
        }
    }

    if(1 == sw)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
        
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            car_lockHelmet_sync(L_FALSE); //同步阻塞接口，以便操作完成后返回锁状态
        }
        else
        {
            car_lockHelmet();
        }

        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_BEEP, volume);
            }
            else
            {
                audio_play(AUDIO_BEEP);
            }
        }
        return 0;
    }
    else if(0 == sw)
    {
        bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
                
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            car_unlockHelmet_sync(L_TRUE); //同步阻塞接口，以便操作完成后返回锁状态
        }
        else
        {
            setting.statusConf.helmetTargetStatus = HELMET_UNLOCK_WITH_AUTOLOCK;
            statusConf_save();
            car_unlockHelmet();
        }
        
        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_BEEP, volume);
            }
            else
            {
                audio_play(AUDIO_BEEP);
            }
        }
        return 0;
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_CONTENT);
    return -1;
}

static int bleMsg_getdebug(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    uint8_t sw = bleMsg->data[0];
    data_getData()->ble_workMode = sw;
    setting.settingConf.loglevel = LOG_LEVEL_DEBUG;
    bleMsg_sendBleResponse(msg->cmd, CODE_SUCCESS);
    LOG_DEBUG("[cmd] ble_workMode %d",data_getData()->ble_workMode);
    return 0;
}

static MSG_HEADER_XA *g_setDefend_msg = NULL;
static BLE_RESPONSE_WITHTYPE *g_setDefend_res = NULL;
static int bleMsg_SetDeffendOnWithRFID_cb(void)
{
    if((((data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) || !data_getData()->isRFIDConnect) &&
        !setting_isDefendOn()) || !car_isPowerExistence()) //未连接RFID模块、未读到标签信息或大电不在时，返回操作失败
    {
        g_setDefend_res->errCode = CODE_ERROR_OPREATION;
        g_setDefend_res->type = 2;
    }
    else
    {
        g_setDefend_res->errCode = CODE_SUCCESS;
        g_setDefend_res->type = 2;
    }

    if(!setting_isDefendOn() && car_isPowerExistence())
    {
        if(data_getData()->isRFIDConnect && data_getData()->isCardIdLegal)
        {
            memcpy(g_setDefend_res->payload,data_getData()->cardID,16); //保存RFID卡号到payload
            bleMsg_sendBleResponseWithType(g_setDefend_msg->cmd, g_setDefend_res,BLE_RESPONSE_LEN + 16);
            
            if(audio_isRFIDAudioDone())
            {
                fibo_taskSleep(400); //避免RFID提示音和还车语音同时播放
            }
            audio_play(AUDIO_DEFEND_ON);
            car_lockBackWheel();
            setting_setDefend(L_TRUE);
            g_isSetDefending = L_FALSE;
            return 0;
        }
    }
    bleMsg_sendBleResponseWithType(g_setDefend_msg->cmd, g_setDefend_res,BLE_RESPONSE_LEN + 16);
    Free(g_setDefend_res);
    g_setDefend_res = NULL;
    g_isSetDefending = L_FALSE;
    return 0;
}

//带RFID还车的响应
static void bleMsg_SetDeffendOnWithRFID(void)
{
    if(!setting_isDefendOn() && !car_isAccOn() && car_isPowerExistence()) //撤防状态，电门关的情况下，先打开RFID的5v供电
    {
        car_openRFIDPower_SetDeffend();//打开RFID的5V供电，5秒后再关闭
        timer_start(TIMER_RFID_DELAY, TIMER_MS, 3500, bleMsg_SetDeffendOnWithRFID_cb);//延时是为了保证检测RFID标签状态正确
        return 0;
    }
    bleMsg_SetDeffendOnWithRFID_cb();
}

static int bleMsg_setDefendOnType(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;
    u8 idx = 0;
    u8 volume = -1;
    u8 type = 0;
    
    if(msg->length > sizeof(uint32_t))
    {        
        type = bleMsg->data[0];
        if(msg->length > sizeof(uint32_t) + 5) //reserved预留位占4个字节
        {
            idx = bleMsg->data[5];
        }
        if(msg->length > sizeof(uint32_t) + 6)
        {
            volume = bleMsg->data[6];
        }
   }
    g_setDefend_msg = msg;
    g_isSetDefending = L_TRUE;

    if(2 == type) //考虑RFID类型的设防
    {
        g_setDefend_res = (BLE_RESPONSE_WITHTYPE*)Malloc(BLE_RESPONSE_LEN + 16); //带上16个字节RFID卡号上报
        bleMsg_SetDeffendOnWithRFID();
        return 0;
    }
    else
    {
        g_setDefend_res = (BLE_RESPONSE_WITHTYPE*)Malloc(BLE_RESPONSE_LEN);
    }

    if(1 == type) //考虑脚撑类型的设防，暂时占位
    {
        g_setDefend_res->errCode = CODE_SUCCESS;
        g_setDefend_res->type = 1;
        bleMsg_sendBleResponseWithType(msg->cmd, g_setDefend_res,BLE_RESPONSE_LEN);
        Free(g_setDefend_res);
        g_setDefend_res = NULL;
        g_isSetDefending = L_FALSE;
        return 0;
    }
    
    if(SETTING_NOTSTOP == setting_setDefend(L_TRUE)) //常规设防
    {
        g_setDefend_res->errCode = CODE_ERROR_NOTSTOP;
        g_setDefend_res->type = 0;
        bleMsg_sendBleResponseWithType(msg->cmd, g_setDefend_res,BLE_RESPONSE_LEN);
    }
    else
    {
        g_setDefend_res->errCode = CODE_SUCCESS;
        g_setDefend_res->type = 0;
        bleMsg_sendBleResponseWithType(msg->cmd, g_setDefend_res,BLE_RESPONSE_LEN);
        
        if(idx > 0 && idx < AUDIO_MAX_NUMBER)
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(idx, volume);
            }
            else
            {
                audio_play(idx);
            }
        }
        else
        {
            if(volume >= 0 && volume <= 100)
            {
                audio_playWithVolume(AUDIO_DEFEND_ON, volume);
            }
            else
            {
                audio_play(AUDIO_DEFEND_ON);
            }
        }
    }
    Free(g_setDefend_res);
    g_setDefend_res = NULL;
    g_isSetDefending = L_FALSE;
    return 0;
}

static int bleMsg_getRFIDInfo(void *m)
{
    DATA *pData = data_getData();
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BLE_RFID_STATE_MSG msgRFIDState = {0};
    
    u8 tmp_event = RFID_SCAN_NONE;
    if(data_getData()->isRFIDConnect && data_getData()->isCardIdLegal) //RFID连接并扫描到标签
    {
        tmp_event = RFID_SCAN_SUCCESS;
        strncpy(msgRFIDState.cardID, data_getData()->cardID, 16);
    }
    else if(data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID连接未扫描到标签
    {
        tmp_event = RFID_SCAN_NONE;
    }   
    else if(!data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID未连接
    {
        tmp_event = RFID_DISCONNECT;
    }
    msgRFIDState.result = tmp_event;
    if(msgRFIDState.result == RFID_SCAN_SUCCESS || msgRFIDState.result == RFID_SCAN_NONE)
    {
        int count = sscanf(data_getData()->RFIDVersion, "%d.%d.%d", &msgRFIDState.version[0], &msgRFIDState.version[1], &msgRFIDState.version[2]);
        if(count != 3)
        {
            return 0;
        }
    }
    
    da14580_sendDATA(msg->address, msg->cmd, (uint8_t *)&msgRFIDState, sizeof(BLE_RFID_STATE_MSG));
    return 0;
}

PROC_MAP ble_msg_procs[] = 
{
    {CMD_BLE_SET_DEFEND,        bleMsg_setDefend},
    {CMD_BLE_GET_STATUS,        bleMsg_getStatus},
    {CMD_BLE_SET_SERVER,        bleMsg_setServer},
    {CMD_BLE_REBOOT,            bleMsg_reboot},
    {CMD_BLE_SET_ACC,           bleMsg_setAcc},
    {CMD_BLE_AUDIO,             bleMsg_playAudio},
    {CMD_BLE_SHUTDOWN,          bleMsg_shutDown},
    {CMD_BLE_CHNAGE_SERVER,     bleMsg_changeServer},
    {CMD_BLE_SET_SADDLE,        bleMsg_setSaddle},
    {CMD_BLE_SET_BACKWHEEL,     bleMsg_setBackwheel},
    {CMD_BLE_GET_CCID,          bleMsg_getCCID},

    {CMD_BLE_GET_GPS,           bleMsg_getGPS},
    {CMD_BLE_GET_CARD_INFO,     bleMsg_getSimInfo},
    {CMD_BLE_SET_DEFENDON,      bleMsg_setDefendOn},
    {CMD_BLE_SET_ACCON,         bleMsg_setAccOn},
    {CMD_BLE_SET_ACCOFF,        bleMsg_setAccOff},
    {CMD_BLE_UNLOCK_WHEEL,      bleMsg_unlockWheel},
    {CMD_BLE_LOCK_WHEEL,        bleMsg_lockWheel},
    {CMD_BLE_UNLOCK_SADDLE,     bleMsg_unlockSaddle},
    {CMD_BLE_LOCK_SADDLE,       bleMsg_lockSaddle},
    {CMD_BLE_GET_STATUS_V2,     bleMsg_getStatus_V2},
    {CMD_BLE_GET_STATUS_V3,     bleMsg_getStatus_V3},
    {CMD_BLE_SET_APN,           bleMsg_setAPN},

    {CMD_BLE_GET_NET_STATE,         bleMsg_getNetState},
    {CMD_BLE_GET_TBEACON_INFO,      bleMsg_getTBeaconInfo},
    {CMD_BLE_SET_DEFEND_TBEACON,    bleMsg_setDefendTBeacon},
    {CMD_BLE_SET_ACC_TBEACON,       bleMsg_setAccOnTBeacon},
    {CMD_BLE_SET_HELMET,            bleMsg_setHelmet},
    {CMD_BLE_SET_WORKMODE,          bleMsg_getdebug},
    {CMD_BLE_SET_DEFENDON_TYPE,     bleMsg_setDefendOnType},
    {CMD_BLE_GET_RFID_INFO,         bleMsg_getRFIDInfo},
//    {CMD_BLE_SET_DEEP_SLEEP,    bleMsg_setDeepSleep},
//    {CMD_BLE_GET_DIAGNOSIS,     bleMsg_getDiagnosis},
};

static bool da14580_isTokenPass(uint32_t token)
{
    return setting.settingConf.token == token ? L_TRUE : L_FALSE;
}

static int bleMsg_connect_cb(void)
{
    if(!data_getData()->ble_workMode) //如果不是LOG透传模式
    {
        LOG_DEBUG("[bleMsg] connect protect");
        return da14580_sendDATA(BIO_ADDRESS, CMD_BIO_DISCONNECT_REQ, NULL, 0);
    }
    return 0;
}

int bleMsg_msgProc(uint8_t *data, uint16_t dataLen)
{
    uint8_t i = 0;
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)data;
    BLE_MSG_DATA *bleMsg = (BLE_MSG_DATA *)msg->data;

    if(!da14580_isTokenPass(_ntohl(bleMsg->token)))
    {
        //切回服务器命令兼容默认token
        LOG_DEBUG("TokenPass error cmd:%d", msg->cmd);
        if(_ntohl(bleMsg->token) == BLE_DFT_TOKEN && msg->cmd == CMD_BLE_CHNAGE_SERVER)
        {
            bleMsg_changeServer(msg);
            return 0;
        }
        else
        {
            bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_TOKEN);
            return -1;
        }
    }
    timer_start(TIMER_BLE_CONN_PROTECT, TIMER_S, 60, bleMsg_connect_cb);
    data_setAwakeTime(SLEEP_BLE_WAKE);
    for(i = 0; i < sizeof(ble_msg_procs) / sizeof(ble_msg_procs[0]); i++)
    {
        if(ble_msg_procs[i].cmd == msg->cmd)
        {
            if(ble_msg_procs[i].action)
            {
                LOG_INFO(">>>CALL cmd = %d\n", msg->cmd);
                ble_msg_procs[i].action((void *)msg);
            }
            return 0;
        }
    }

    bleMsg_sendBleResponse(msg->cmd, CODE_ERROR_UNSUPPORT);
    return 0;
}

