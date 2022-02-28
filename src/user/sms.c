/*
 * sms.c
 *
 *  Created on: 2019/4/16
 *      Author: lc
 */

#include "fibo_opencpu.h"
#include "nmea/gmath.h"

#include "cJSON/cJSON.h"

#include "log.h"
#include "sms.h"
#include "msg.h"
#include "types.h"
#include "utils.h"
#include "setting.h"
#include "user_at.h"
#include "protocol.h"
#include "gps_parse.h"
#include "car.h"
#include "user_timer.h"
#include "data.h"
#include "version.h"
#include "user_fs.h"
#include "audio_driver.h"

static uint8_t w_buf[128];

enum
{
    SMS_CMD_FACTORY = 0,
    SMS_CMD_VERSION = 1,
    SMS_CMD_REBOOT  = 2,
    SMS_CMD_SERVER  = 3,
    SMS_CMD_DEFEND  = 4,
    SMS_CMD_ACC     = 5,
    SMS_CMD_SADDLE  = 6,
    SMS_CMD_STATISTICS = 7,
    SMS_CMD_LOCATION = 8,
    SMS_CMD_PLAYAUDIO = 9,
    SMS_CMD_SET_INNERPARAM = 10,
    SMS_CMD_GET_INNERPARAM = 11,
    SMS_CMD_GET_DEVICE_STATE = 14,
    SMS_CMD_SET_BACKWHEEL = 15,
    SMS_CMD_SET_HELMET    = 16,
};

typedef void (*SMS_PROC)(cJSON *, u8 *);
typedef struct
{
    char cmd;
    SMS_PROC pfn;
}SMS_MSG_PROC;

static ATResult_enum sms_writeMessageCb(uint8_t isTimeout, char *buf, uint16_t len)
{
    static unsigned char *cmd = NULL;
    if(!cmd)
    {
        cmd = Malloc(256);
    }
    if(isTimeout || strstr((const char *)buf, ">")) 
    {
        snprintf((char *)cmd, 256, "%s\x1a\r", w_buf);
        LOG_DEBUG("[SMS] writeMessageCb:%s", w_buf);
        at_run((const char *)cmd, at_default_cb);
        return AT_RES_FINISHED;
    }
    return AT_RES_CONTRINUE; // need ERROR or OK
}

void sms_writeMessage(char *p, char *number)
{
    static unsigned char *cmd = NULL;
    if(!cmd)
    {
        cmd = Malloc(64);
    }
    snprintf((char *)cmd, 64, "AT+CMGW=\"%s\"\r", number);
    memset(w_buf, 0, sizeof(w_buf));
    strcpy((char *)w_buf, p);
    at_runwithTimeout((const char *)cmd, sms_writeMessageCb, 3);//这个命令没有回显,设置3秒超时
    return;
}

__attribute__((unused)) static void sms_poweroff(const u8 *param, u8 *number)
{
    setting_setRebootType(REBOOT_NORMAL);
    fibo_taskSleep(500);
    fibo_softPowerOff();
    return;
}

static void sms_server(cJSON *param, u8 *number)
{
    cJSON *json_server = NULL;
    char *buffer = NULL;
    int count = 0;
    u32 port = 0;
    u32 ip[4] = {0};
    char domain[MAX_DOMAIN_NAME_LEN] = {0};
    L_BOOL rc = L_FALSE;

    audio_play(AUDIO_STARTUP);

    if(param)
    {
        json_server = cJSON_GetObjectItem(param, "server");
    }

    if(!param || !json_server)
    {
        if(setting.serverConf.addr_type == ADDR_TYPE_DOMAIN)
        {
            snprintf(domain, MAX_DOMAIN_NAME_LEN + 6, "%s:%d", setting.serverConf.domain, setting.serverConf.port);
        }
        else if(setting.serverConf.addr_type == ADDR_TYPE_IP)
        {
            snprintf(domain, MAX_IP_PORT_LEN, "%u.%u.%u.%u:%d", setting.serverConf.ipaddr[0], setting.serverConf.ipaddr[1], setting.serverConf.ipaddr[2], setting.serverConf.ipaddr[3], setting.serverConf.port);
        }
        
        buffer = myTestMalloc(128);
        memset(buffer, 0, 128);
        snprintf(buffer, 128, "{\"server\":\"%s\"}", domain);
        sms_writeMessage((char *)buffer, (char *)number);
        Free(buffer);
        return;
    }

    do
    {
        count = sscanf(json_server->valuestring, "%u.%u.%u.%u:%u", &ip[0], &ip[1], &ip[2], &ip[3], &port);
        if(5 == count)
        {
            if(check_ip(ip[0], ip[1], ip[2], ip[3]))
            {
                LOG_DEBUG("Ip cannot be %u.%u.%u.%u.", ip[0], ip[1], ip[2], ip[3]);

                buffer = Malloc(128);
                memset(buffer, 0, 128);
                snprintf(buffer, 128, "server cannot be \"%s\"", json_server->valuestring);
                sms_writeMessage((char *)buffer, (char *)number);
                return;
            }
            if(check_port(port))
            {
                LOG_DEBUG("Port cannot be %d.", port);

                buffer = Malloc(128);
                memset(buffer, 0, 128);
                snprintf(buffer, 128, "server cannot be \"%s\"", json_server->valuestring);
                sms_writeMessage((char *)buffer, (char *)number);
                return;
            }

            if(data_isLogined())
            {
                memcpy(&setting.srvBakConf, &setting.serverConf, sizeof(SERVER_CONF)); //保存备份服务器信息
            }

            setting.serverConf.addr_type = ADDR_TYPE_IP;
            setting.serverConf.ipaddr[0] = (u8)ip[0];
            setting.serverConf.ipaddr[1] = (u8)ip[1];
            setting.serverConf.ipaddr[2] = (u8)ip[2];
            setting.serverConf.ipaddr[3] = (u8)ip[3];
            setting.serverConf.port = (u16)port;
            rc = L_TRUE;
            break;
        }

        count = sscanf(json_server->valuestring, "%[^:]:%u", domain, &port);
        if(2 == count)
        {
            if(check_port(port))
            {
                LOG_DEBUG("Port cannot be %d.", port);

                buffer = Malloc(128);
                memset(buffer, 0, 128);
                snprintf(buffer, 128, "server cannot be \"%s\"", json_server->valuestring);
                sms_writeMessage((char *)buffer, (char *)number);
                return;
            }

            if(data_isLogined())
            {
                memcpy(&setting.srvBakConf, &setting.serverConf, sizeof(SERVER_CONF)); //保存备份服务器信息
            }

            setting.serverConf.addr_type = ADDR_TYPE_DOMAIN;
            strncpy(setting.serverConf.domain, domain, MAX_DOMAIN_NAME_LEN);
            setting.serverConf.port = (u16)port;
            rc = L_TRUE;
            break;
        }
    } 
    while (L_FALSE);

    if(rc == L_TRUE)
    {
        //登陆响应后再保存，否则超时切回原服务器
        setting_serverReinit();
        timer_start(TIMER_CHANGESERVER_TIMEOUT, TIMER_S, 60, setting_setServerTimeout);
    }
    else
    {
        LOG_DEBUG("param format error.");
    }
}

static void sms_factory(cJSON *param, u8 *number)
{	
    audio_play(AUDIO_STARTUP);
    fibo_file_delete(FILE_FENCE_CONF);
    fibo_file_delete(FILE_SERVER_CONF);
    fibo_file_delete(FILE_SETTING_CONF);
    fibo_softReset();
}

static void sms_version(cJSON *param, u8 *number)
{
    cJSON *result = NULL;
    char *buffer = NULL;
    char version[12] = {0};
    
    audio_play(AUDIO_STARTUP);

    result = cJSON_CreateObject();
    if(!result)
    {
        return;
    }

    snprintf(version, 12, "%d.%d.%d", (setting.defaultConf.version >> 16) & 0xFF,
                                        (setting.defaultConf.version >> 8) & 0xFF,
                                        (setting.defaultConf.version >> 0) & 0xFF);

    cJSON_AddStringToObject(result, "app", version);
    
    snprintf((char *)version, 16, "%d.%d.%d", (setting.coreVersion >> 16) & 0xFF,
                        (setting.coreVersion >> 8) & 0xFF,
                        (setting.coreVersion >> 0) & 0xFF);
    cJSON_AddStringToObject(result, "core", version);

    buffer = cJSON_PrintUnformatted(result);
    if(!buffer)
    {
        cJSON_Delete(result);
        return;
    }

    cJSON_Delete(result);
    sms_writeMessage((char *)buffer, (char *)number);

    Free(buffer);
}

static void sms_reboot(cJSON *param, u8 *number)
{
    audio_play(AUDIO_STARTUP);
    fibo_taskSleep(500);
    fibo_softReset();
}

static void sms_defend(cJSON *param, u8 *number)
{
    cJSON *defend = NULL;

    if(!param)
    {
        return;
    }

    defend = cJSON_GetObjectItem(param, "defend");
    if(!defend)
    {
        return;
    }
    
    car_accOff();
    if(defend->valueint)
    {
        setting_setDefend(L_TRUE);
        audio_play(AUDIO_DEFEND_ON);
    }
    else
    {
        if(setting.settingConf.forceLock)
        {
            return;
        }
        audio_play(AUDIO_DEFEND_OFF);
        setting_setDefend(L_FALSE);
    }    
}

static void sms_acc(cJSON *param, u8 *number)
{
    cJSON *acc = NULL;
    if(!param)
    {
        return;
    }

    acc = cJSON_GetObjectItem(param, "acc");
    if(!acc)
    {
        return;
    }
    
    if(acc->valueint == 1)
    {
        if(setting.settingConf.forceLock)
        {
            return;
        }
        //启动电门,并撤防
        if(SETTING_OUTSERVICE == setting_setAcc(L_TRUE))
        {
            audio_play(AUDIO_BEEP);
            return;
        }

        audio_play(AUDIO_ACC_ON);
        timer_stop(TIMER_RELEASE_ELOCK);
    }
    else if(acc->valueint == 0)
    {
        setting_setAcc(L_FALSE);
        
        audio_play(AUDIO_ACC_OFF);
    }
}

static void sms_saddle(cJSON *param, u8 *number)
{
    audio_play(AUDIO_STARTUP);
    car_unlockSaddle();
}

static void sms_statistics(cJSON *param, u8 *number)
{
    cJSON *result = NULL;

    char *buffer = NULL;
    
    audio_play(AUDIO_STARTUP);

    result = cJSON_CreateObject();
    if(!result)
    {
        return;
    }

    cJSON_AddNumberToObject(result, "pkts_sent", data_getData()->socstate.pkts_sent);
    cJSON_AddNumberToObject(result, "bytes_sent", data_getData()->socstate.bytes_sent);
    cJSON_AddNumberToObject(result, "pkts_acked", data_getData()->socstate.pkts_acked);
    cJSON_AddNumberToObject(result, "bytes_acked", data_getData()->socstate.bytes_acked);
    cJSON_AddNumberToObject(result, "conn_success", data_getData()->socstate.conn_success);
    cJSON_AddNumberToObject(result, "conn_fail", data_getData()->socstate.conn_fail);
    cJSON_AddNumberToObject(result, "conn_close", data_getData()->socstate.conn_close);

    buffer = cJSON_PrintUnformatted(result);
    if(!buffer)
    {
        cJSON_Delete(result);
        return;
    }

    cJSON_Delete(result);
    
    sms_writeMessage((char *)buffer, (char *)number);

    Free(buffer);
    return;
}

static void sms_location(cJSON *param, u8 *number)
{
    DATA *pData = data_getData();
    cJSON *result = NULL;

    char *buffer = NULL;
    
    audio_play(AUDIO_STARTUP);

    result = cJSON_CreateObject();
    if(!result)
    {
        return;
    }
    
    cJSON_AddNumberToObject(result, "CarVoltageMv", pData->vehicleBattery_mV);
    cJSON_AddNumberToObject(result, "BatVoltageMv", pData->smallBattery_mV);
    
    if(pData->lastPosition.isGPS)
    {
        cJSON_AddNumberToObject(result, "timestamp", pData->lastPosition.timestamp);
        cJSON_AddNumberToObject(result, "lat", gps_getGPSValue(pData->lastPosition.nmeaInfo.lat));
        cJSON_AddNumberToObject(result, "lng", gps_getGPSValue(pData->lastPosition.nmeaInfo.lon));
        cJSON_AddNumberToObject(result, "speed", (u8)(pData->lastPosition.nmeaInfo.speed + 0.5));
        cJSON_AddNumberToObject(result, "course",(u16)(pData->lastPosition.nmeaInfo.direction + 0.5));
    }
    
    buffer = cJSON_PrintUnformatted(result);
    if(!buffer)
    {
        cJSON_Delete(result);
        return;
    }

    cJSON_Delete(result);
    
    sms_writeMessage((char *)buffer, (char *)number);

    Free(buffer);
}

static void sms_setInnerParam(cJSON *param, u8 *number)
{
    cJSON *item = NULL;

    //先保存原始配置值,如果所有参数校验通过，则一次性更新；否则，全部不更新
    u16 freq_norm = setting.settingConf.freq_norm;
    u16 freq_move = setting.settingConf.freq_move;

    if(!param)
    {
        return;
    }
    
    item = cJSON_GetObjectItem(param, "freq");
    if(item)
    {
        freq_norm = item->valueint;
    }
    
    item = cJSON_GetObjectItem(param, "freq_move");
    if(item)
    {
        freq_move = item->valueint;
    }

    setting.settingConf.freq_norm = freq_norm;
    setting.settingConf.freq_move = freq_move;

    settingConf_save();
}

static void sms_playaudio(cJSON *param, u8 *number)
{
    cJSON *audio_idx = NULL;
    if (!param)
    {
        return;
    }

    audio_idx = cJSON_GetObjectItem(param, "idx");

    audio_play(audio_idx->valueint);
    return;
}

static void sms_getInnerParam(cJSON *param, u8 *number)
{
    char *buffer = NULL;
    cJSON *result = NULL;

    result = cJSON_CreateObject();
    if(!result)
    {
        return;
    }

    cJSON_AddNumberToObject(result, "mode", data_getData()->mode);
    cJSON_AddNumberToObject(result, "freq", setting.settingConf.freq_norm);
    cJSON_AddNumberToObject(result, "freq_move", setting.settingConf.freq_move);

    buffer = cJSON_PrintUnformatted(result);
    if(!buffer)
    {
        cJSON_Delete(result);
        return;
    }
    cJSON_Delete(result);
    
    sms_writeMessage((char *)buffer, (char *)number);

    Free(buffer);
}

static void sms_getDeviceState(cJSON *param, u8 *number)
{
    char *buffer = NULL;
    cJSON *result = NULL;

    result = cJSON_CreateObject();
    if(!result)
    {
        return;
    }

    cJSON_AddNumberToObject(result, "reboot", setting.statusConf.rebootType);
    cJSON_AddNumberToObject(result, "isLogined", data_isLogined());

    buffer = cJSON_PrintUnformatted(result);
    if(!buffer)
    {
        cJSON_Delete(result);
        return;
    }
    cJSON_Delete(result);
    
    sms_writeMessage((char *)buffer, (char *)number);

    Free(buffer);
}

static void sms_setBackwheel(cJSON *param, u8 *number)
{
    cJSON *sw = NULL;
    
    if(!param)
    {
        return;
    }

    sw = cJSON_GetObjectItem(param, "sw");
    if (!sw)
    {
        return;
    }

    if(sw->valueint == 0)
    {
        car_unlockBackWheel();
    }
    else
    {
        car_lockBackWheel();
    }
}

static void sms_setHelmet(cJSON *param, u8 *number)
{
    cJSON *sw = NULL;
    
    if(!param)
    {
        return;
    }

    sw = cJSON_GetObjectItem(param, "sw");
    if (!sw)
    {
        return;
    }

    if(sw->valueint == 0)
    {
        car_unlockHelmet();
    }
    else
    {
        car_lockHelmet();
    }
}

static SMS_MSG_PROC smsProcs[] =
{
    {SMS_CMD_FACTORY,   sms_factory},
    {SMS_CMD_VERSION,   sms_version},
    {SMS_CMD_REBOOT,    sms_reboot},
    {SMS_CMD_SERVER,    sms_server},
    {SMS_CMD_DEFEND,    sms_defend},
    {SMS_CMD_ACC,       sms_acc},
    {SMS_CMD_SADDLE,    sms_saddle},
    {SMS_CMD_STATISTICS,sms_statistics},
    {SMS_CMD_LOCATION,  sms_location},
    {SMS_CMD_PLAYAUDIO, sms_playaudio},
    {SMS_CMD_SET_INNERPARAM, sms_setInnerParam},
    {SMS_CMD_GET_INNERPARAM, sms_getInnerParam},
    {SMS_CMD_GET_DEVICE_STATE, sms_getDeviceState},
    {SMS_CMD_SET_BACKWHEEL,    sms_setBackwheel},
    {SMS_CMD_SET_HELMET,       sms_setHelmet},
};

void sms_proc(const u8 *p, u8 *number)
{
    int i =0;
    char cmd = 0;
    cJSON *json_cmd = NULL;
    cJSON *json_root = NULL;
    cJSON *json_param = NULL;

    data_setAwakeTime(SLEEP_SMS_WAKE);

    json_root = cJSON_Parse((const char *)p);
    if(!json_root)
    {
        LOG_ERROR("content is not json type");
        return;
    }

    json_cmd = cJSON_GetObjectItem(json_root, "c");
    if(!json_cmd)
    {
        cJSON_Delete(json_root);
        LOG_ERROR("no cmd in content");
        return;
    }
    cmd = json_cmd->valueint;

    json_param = cJSON_GetObjectItem(json_root, "p");

    for (i = 0; i < sizeof(smsProcs) / sizeof(smsProcs[0]); i++)
    {
        if (smsProcs[i].cmd == json_cmd->valueint)
        {
            SMS_PROC pfn = smsProcs[i].pfn;
            if (pfn)
            {
                pfn(json_param, number);
                cJSON_Delete(json_root);
                return;
            }
            else
            {
                LOG_ERROR("cmd %d not processed!", cmd);
                cJSON_Delete(json_root);
                return;
            }
        }
    }

    LOG_ERROR("unsupported cmd %d!", cmd);
    cJSON_Delete(json_root);
}

ATResult_enum sms_listMessage(uint8_t isTimeout, char *buf, uint16_t len)
{
    if(isTimeout || strstr((const char *)buf, "ERROR") || strstr((const char *)buf, "OK")) 
    {
        if(strstr((const char *)buf, "OK"))
        {
            //已经读取了短信了, 在这里先删除, 避免删除了回复短信
            at_run("AT+CMGD=0,4\r", at_default_cb);
            
            char *p = string_bypass((const char *)buf, "REC UNREAD"); //直接找未读短信
            if(p)
            {
                char *phoneNumber = string_bypassByNum(p, ",", 1);
                char *content = string_bypassByNum(p, "\"", 5);
                if(phoneNumber && content)
                {
                    int index = 0;
                    u8 number[15] = {0};
                    for(int i = 1; i < 15; i++)
                    {
                        if(phoneNumber[i] >= '0' && phoneNumber[i] <= '9')
                        {
                            number[index++] = phoneNumber[i];
                        }
                        else
                        {
                            break;
                        }
                    }
                    sms_proc((const u8 *)content + 2, number);// +2:\r\n
                }
            }
        }
        return AT_RES_FINISHED;
    }
    return AT_RES_CONTRINUE; // need ERROR or OK
}

void sms_sendMessage_end(uint8_t *buf, uint16_t len)
{
    //已经发送了短信了, 删除全部短信
    at_run("AT+CMGD=0,4\r", at_default_cb);
}

void sms_sendMessage(uint8_t *buf, uint16_t len)
{
    char *p = string_bypass((const char *)buf, "+CMGW: ");
    if(p)
    {
        char cmd[32] = {0};
        snprintf(cmd, 32, "AT+CMSS=%d\r", _atoi(p));
        //存了什么短信,就发什么短信
        at_run(cmd, at_default_cb);
    }
}

void sms_recvMessage(uint8_t *buf, uint16_t len)
{
    //收到了短信,进行遍历短信
    at_run("AT+CMGL=\"ALL\"\r", sms_listMessage);
}

