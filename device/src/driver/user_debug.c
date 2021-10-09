/*
 * debug.c
 *
 *  Created on: 2016年2月4日
 *      Author: jk
 */
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "utils.h"
#include "user_at.h"
#include "hardware.h"
#include "user_debug.h"
#include "audio_driver.h"
#include "device.h"
#include "da14580.h"
#include "version.h"
#include "user_fs.h"
#include "userMsg.h"
#include "request.h"
#include "setting.h"
#include "response.h"
#include "sms.h"
#include "http.h"
#include "bioMsg.h"
#include "socket.h"
#include "data.h"
#include "audio.h"
#include "gps_parse.h"
#include "user_timer.h"
#include "agps.h"
#include "types.h"
#include "ublox.h"

#define MAX_CMD_LENGTH (32)
#define MAX_CMD_NUMBER (64)

typedef struct
{
    unsigned char cmd[MAX_CMD_LENGTH + 1];
    CMD_ACTION  action;
} CMD_MAP;

static CMD_MAP cmd_map[MAX_CMD_NUMBER] =
{

};

static int cmd_play(const unsigned char *cmdString, unsigned short length)
{
    int ret = 0;
    const char *p = (const char *)string_bypass((const char *)cmdString, "play");

    p = (const char *)string_trimLeft((const unsigned char *)p);
    string_trimRight((unsigned char *)p);
    int count = sscanf(p, "%d", &ret);
    if(count == 1)
    {
        audio_play(ret);
    }
    return 0;
}

static int cmd_debug(const unsigned char *cmdString, unsigned short length)
{
    int i = 0;
    DBG_OUT("support cmd:");
    for (i = 0; i < MAX_CMD_NUMBER && cmd_map[i].action; i++)
    {
        DBG_OUT("\t%s\t%p", cmd_map[i].cmd, cmd_map[i].action);
    }
    return 0;
}

static int cmd_imei(const unsigned char *cmdString, unsigned short length)
{
    unsigned char imei[17] = {0};
    fibo_get_imei(imei, CFW_SIM_0);
    DBG_OUT("IMEI = %s", imei);
    return 0;
}

static int cmd_imsi(const unsigned char* cmdString, unsigned short length)
{
    uint8_t imsi[32] = {0};
    fibo_get_imsi(imsi);
    DBG_OUT("IMSI = %s", imsi);
    return 0;
}

static int cmd_ccid(const unsigned char *cmdString, unsigned short length)
{
    uint8_t ccid[32] = {0};
    fibo_get_ccid(ccid);
    DBG_OUT("CCID = %s", ccid);
    return 0;
}

static int cmd_AT(const unsigned char *cmdString, unsigned short length)
{
    uint8_t cmd[MODEM_AT_MAX_LEN] = {0};
    string_trimRight((unsigned char *)cmdString);
    snprintf((char *)cmd, MODEM_AT_MAX_LEN, "%s\r", cmdString);
    at_run((const char *)cmd, at_default_cb);
    return 0;
}

static int cmd_reboot(const unsigned char *cmdString, unsigned short length)
{
    fibo_softReset();
    return 0;
}

static int cmd_shutdown(const unsigned char *cmdString, unsigned short length)
{
    fibo_softPowerOff();
    return 0;
}

static int cmd_rtc(const unsigned char *cmdString, unsigned short length)
{
    const int RTC_BASE = 2000;
    hal_rtc_time_t rtc = {0};

    rtc_getLocaltime(&rtc);
    LOG_DEBUG("Local RTC:%d-%02d-%02d %02d:%02d:%02d,UTC timestamp:%d", rtc.year + RTC_BASE, rtc.month, rtc.day, rtc.hour, rtc.min, rtc.sec, (u32) rtc_getTimestamp());
    return 0;
}

int regist_cmd(const unsigned char *cmd, CMD_ACTION action)
{
    int i = 0;

    //寻找第一个空位命令 或者命令字相同的命令
    while(i < MAX_CMD_NUMBER && cmd_map[i].action && (0 != memcmp(cmd_map[i].cmd, cmd, strlen((const char *)cmd))))
    {
        i++;
    }

    if(i >= MAX_CMD_NUMBER)
    {
        LOG_ERROR("exceed MAX command number: %d", MAX_CMD_NUMBER);
        return -1;
    }

    strncpy((char *)cmd_map[i].cmd, (const char *)cmd, MAX_CMD_LENGTH);
    cmd_map[i].action = action;

    LOG_DEBUG("register cmd %s(%p) at position %d success", cmd, action, i);
    return 0;
}

static int debug_proc(unsigned char *cmdString, unsigned short length)
{
    int i = 0;

    const unsigned char *cmd = string_trimLeft(cmdString);
    LOG_INFO(">DEBUG CMD: %s\n", cmdString);
    for (i = 0; i < MAX_CMD_NUMBER && cmd_map[i].action; i++)
    {
        if (strncmp((const char *)cmd, (const char *)cmd_map[i].cmd, strlen((const char *)cmd_map[i].cmd)) == 0)
        {
            return cmd_map[i].action(cmdString, length);
        }
    }

    LOG_INFO("CMD not processed\n");
    return -1;
}

static void _printIOExample(void)
{
    LOG_DEBUG("io control example:\r\n");
    LOG_DEBUG("io:init <pin> <in/out> <low/high>\r\n");
    LOG_DEBUG("io:read <pin>\r\n");
    LOG_DEBUG("io:write <pin> <low/high>\r\n");
}

__attribute__((unused)) static int cmd_ctrlIO(const unsigned char *cmdString, unsigned short length)
{
    uint8_t tempData[MAX_CMD_LENGTH] = {0};
    uint8_t *p = NULL;
    unsigned int ioPort = 0;
    unsigned int ioState = 0;
    unsigned int ioCtrl = 0;
    int count = 0;

    memcpy(tempData, cmdString, length);

    p = (uint8_t *)string_bypass((const char *)tempData, "io");
    if(p[0] != ':')
    {
        _printIOExample();
        return -1;
    }

    p++;
    p = (uint8_t *)string_trimLeft(p);

    if(strstr((const char *)p, "init"))
    {
        p = (uint8_t *)string_bypass((const char *)p, "init");
        p = (uint8_t *)string_trimLeft(p);

        count = sscanf((const char *)p, "%u %u %u", &ioPort, &ioCtrl, &ioState);//端口,输入输出,默认电平
        if(count == 3)
        {
            LOG_DEBUG("io-> set io(%d) in/out(%d) state(%d) successful!\r\n", ioPort, ioCtrl, ioState);
//            eat_gpio_setup((EatPinName_enum)ioPort, (EatGpioDir_enum)ioCtrl, (EatGpioLevel_enum)ioState);
            return 0;
        }
        _printIOExample();
        return -1;
    }

    if(strstr((const char *)p, "read"))
    {
        p = (uint8_t *)string_bypass((const char *)p, "read");
        p = (uint8_t *)string_trimLeft(p);

        count = sscanf((const char *)p, "%u", &ioPort);
        if(count == 1)
        {
            uint8_t state = 0;
            fibo_gpio_get(ioPort, &state);
            ioState = state;
            LOG_DEBUG("io-> succeed to read io(%d) %d \r\n",ioPort,ioState);
            return 0;
        }
        _printIOExample();
        return -1;
    }

    if(strstr((const char *)p, "write"))
    {
        p = (uint8_t *)string_bypass((const char *)p, "write");
        p = (uint8_t *)string_trimLeft(p);

        count = sscanf((const char *)p, "%u %u", &ioPort, &ioState);
        if(count == 2)
        {
            fibo_gpio_set(ioPort, ioState);
            LOG_DEBUG("io-> succeed to write io(%d) %d\r\n",ioPort,ioState);
            return 0;
        }
        _printIOExample();
        return -1;
    }

    _printIOExample();
    return -1;
}

static int cmd_log(const unsigned char *cmdString, unsigned short length)
{
    char *p = (char *)string_bypass((const char *)cmdString, "log");
    p = (char *)string_trimLeft((const unsigned char *)p);
    string_trimRight((unsigned char *)p);
    if(p)
    {
        if(strstr(p, "null") != NULL)
        {
            setting.settingConf.loglevel = LOG_LEVEL_NULL;
        }
        else if(strstr(p, "fatal") != NULL)
        {
            setting.settingConf.loglevel = LOG_LEVEL_FATAL;
        }
        else if(strstr(p, "error") != NULL)
        {
            setting.settingConf.loglevel = LOG_LEVEL_ERROR;
        }
        else if(strstr(p, "warning") != NULL)
        {
            setting.settingConf.loglevel = LOG_LEVEL_WARNING;
        }
        else if(strstr(p, "info") != NULL)
        {
            setting.settingConf.loglevel = LOG_LEVEL_INFO;
        }
        else if(strstr(p, "debug") != NULL)
        {
            setting.settingConf.loglevel = LOG_LEVEL_DEBUG;
        }
        else if(strstr(p, "main") != NULL)
        {
            setting.settingConf.loglevel = LOG_LEVEL_MAINTENANCE;
        }
        settingConf_save();
    }
    return 0;
}

static int cmd_server(const unsigned char *cmdString, unsigned short length)
{
    if(strstr((const char *)cmdString, "server?") != NULL)
    {
        if(setting.serverConf.addr_type == ADDR_TYPE_IP)
        {
            LOG_DEBUG("server %d.%d.%d.%d:%d", 
                setting.serverConf.ipaddr[0], setting.serverConf.ipaddr[1], setting.serverConf.ipaddr[2], setting.serverConf.ipaddr[3], setting.serverConf.port);
        }
        else if(setting.serverConf.addr_type == ADDR_TYPE_DOMAIN)
        {
            LOG_DEBUG("server \"%s\":%d", setting.serverConf.domain, setting.serverConf.port);
        }
    }
    else
    {
        int rc = 0;
        u32 port = 0;
        u32 addr[4] = {0};
        char domain[MAX_DOMAIN_NAME_LEN] = {0};
        
        if(5 == sscanf((const char *)cmdString, "server %u.%u.%u.%u:%u", &addr[0], &addr[1], &addr[2], &addr[3], &port))
        {
            if(check_ip(addr[0], addr[1], addr[2], addr[3]))
            {
                LOG_DEBUG("Ip cannot be %u.%u.%u.%u.", addr[0], addr[1], addr[2], addr[3]);
                return -1;
            }
            if(check_port(port))
            {
                LOG_DEBUG("Port cannot be %d.", port);
                return -1;
            }

            setting.serverConf.addr_type = ADDR_TYPE_IP;
            setting.serverConf.ipaddr[0] = (u8)addr[0];
            setting.serverConf.ipaddr[1] = (u8)addr[1];
            setting.serverConf.ipaddr[2] = (u8)addr[2];
            setting.serverConf.ipaddr[3] = (u8)addr[3];
            setting.serverConf.port = (u16)port;
            rc = serverConf_save();
            
            LOG_DEBUG("change server to [%d.%d.%d.%d:%d], ret = %d", 
                            addr[0], addr[1], addr[2], addr[3], port, rc);
            socket_initial();
            return 0;
        }

        if(2 == sscanf((const char *)cmdString + strlen("server "), "%[^:]:%u", domain, &port))
        {
            if(check_port(port))
            {
                LOG_DEBUG("Port cannot be %d.", port);
                return -1;
            }

            setting.serverConf.addr_type = ADDR_TYPE_DOMAIN;
            strncpy(setting.serverConf.domain, domain, MAX_DOMAIN_NAME_LEN);
            setting.serverConf.port = (u16)port; 
            rc = serverConf_save();
            
            LOG_DEBUG("change server to [%s:%d], ret = %d", domain, port, rc);
            socket_initial();
            return 0;
        }
    }
    return 0;
}

static int cmd_awake(const unsigned char *cmdString, unsigned short length)
{
    LOG_DEBUG("awake env");
    setting.settingConf.isSleepEnable = L_FALSE;
    data_setAwakeTime(SLEEP_DEFAULT_TIME);
    return 0;
}

static int cmd_version(const unsigned char *cmdString, unsigned short length)
{
    char version_str[12] = {0};
    snprintf(version_str, 12, "%d.%d.%d", (setting.defaultConf.version >> 16) & 0xFF,
                (setting.defaultConf.version >> 8) & 0xFF,
                (setting.defaultConf.version >> 0) & 0xFF);

    LOG_DEBUG("V%s (build:%s %s)", version_str, __DATE__, __TIME__);
    return 0;
}

static int cmd_sendms(const unsigned char *cmdString, unsigned short length)
{
    sms_writeMessage("HELLO", "1440465442615");
    LOG_DEBUG("sms write test");
    return 0;
}

static int cmd_bleHeartbeat(const unsigned char *cmdString, unsigned short length)
{
    static s8 sta = 0;

    da14580_sendDATA(BIO_ADDRESS, CMD_BIO_SET_BEATHEART, (uint8_t *)&sta, 1);
    if(sta == 0)
    {
        LOG_DEBUG("[Debug] open ble heartbeat");
        sta = 1;
    }
    else if (sta == 1)
    {
        LOG_DEBUG("[Debug] close ble heartbeat");
        sta = 0;
    }
    return 0;
}

static int cmd_rsaudio(const unsigned char *cmdString, unsigned short length)
{
#if defined(APP_RELEASE)
    LOG_DEBUG("[Debug] Release version ! restore failed");
#else
    audio_RstoreDefaultAudios();
    LOG_DEBUG("[Debug] Restore default voice");
#endif
    return 0;
}

static int cmd_rmdtaudio(const unsigned char *cmdString, unsigned short length)
{
    for(int i = 0; i < AUDIO_MAX_NUMBER; i ++)
    {
        audio_deleteCustomAudio(i);
        audio_deleteBakAudio(i);
    }
    LOG_DEBUG("[Debug] Remove all custom voice");
    return 0;
}

static int cmd_rssetting(const unsigned char *cmdString, unsigned short length)
{
    if(fs_isFileExists(FILE_DEFAULT_CONF) == L_TRUE)
    {
        fs_deleteFile(FILE_DEFAULT_CONF);
    }

    if(fs_isFileExists(FILE_SETTING_CONF) == L_TRUE)
    {
        fs_deleteFile(FILE_SETTING_CONF);
    }

    if(fs_isFileExists(FILE_STATUS_CONF) == L_TRUE)
    {
        fs_deleteFile(FILE_STATUS_CONF);
    }

    sysConf_initial();

    LOG_INFO("[Debug] Restore Default Setting");
    return 0;
}

static int cmd_rsserver(const unsigned char *cmdString, unsigned short length)
{
    if(fs_isFileExists(FILE_SERVER_CONF) == L_TRUE)
    {
        fs_deleteFile(FILE_SERVER_CONF);
    }

    setting.serverConf.port = 9880;
    setting.serverConf.ipaddr[0] = 112;
    setting.serverConf.ipaddr[1] = 74;
    setting.serverConf.ipaddr[2] = 77;
    setting.serverConf.ipaddr[3] = 182;
    setting.serverConf.addr_type = ADDR_TYPE_IP;

    serverConf_save();

    LOG_INFO("[Debug] Restore Default server");
    socket_initial();
    return 0;
}

static int cmd_csq(const unsigned char *cmdString, unsigned short length)
{
    INT32 csq;
    INT32 ber;
    u8 ret = fibo_get_csq(&csq, &ber);
    LOG_DEBUG("[CMD] CSQ=%d Ber=%d ret=%d",csq,ber,ret);
    return 0;
}

static int cmd_openlog(const unsigned char *cmdString, unsigned short length)
{
    setting.settingConf.loglevel = LOG_LEVEL_DEBUG;
    settingConf_save();
    return 0;
}

static int cmd_closelog(const unsigned char *cmdString, unsigned short length)
{
    setting.settingConf.loglevel = LOG_LEVEL_NULL;
    settingConf_save();
    return 0;
}

static int cmd_displaylog(const unsigned char *cmdString, unsigned short length)
{
    setting.settingConf.displaylog = 1;
    return 0;
}

static int getclbs_cb(void)
{
    gps_getCLBS(gps_getCLBS_proc);
    return 0;
}
static int cmd_clbs(const unsigned char *cmdString, unsigned short length)
{
    static u8 flag = 0;
    if(flag == 0)
    {
        flag = 1;
        timer_startRepeat(TIMER_PIRVTEST, TIMER_S, 5, getclbs_cb);
    }
    else
    {
        flag = 0;
        timer_stop(TIMER_PIRVTEST);
    }
    return 0;
}

static int cmd_bledebug(const unsigned char *cmdString, unsigned short length)
{
    if(!data_getData()->ble_workMode)
    {
        data_getData()->ble_workMode = 1;
    }
    else
    {
        data_getData()->ble_workMode = 0;
    }
    LOG_DEBUG("[cmd] ble_workMode %d",data_getData()->ble_workMode);
    return 0;
}

static int cmd_setRTC(const unsigned char *cmdString, unsigned short length)
{
    const u8 *seq = (const u8 *)strstr((const char *)cmdString, "setRTC") + strlen("setRTC");
    u32 time = 0;
    const int RTC_BASE = 2000;
    hal_rtc_time_t rtc = {0};
    int rc = sscanf((const char *)seq, "%d", &time);

    if(rc == 1)
    {
        LOG_DEBUG("setRTC: %d", time);
        rtc_setNoUpdate(L_FALSE);
        rtc_updateTimestamp(time);
        rtc_setNoUpdate(L_TRUE);
    }

    rtc_getLocaltime(&rtc);
    LOG_DEBUG("Local RTC:%d-%02d-%02d %02d:%02d:%02d,UTC timestamp:%d", rtc.year + RTC_BASE, rtc.month, rtc.day, rtc.hour, rtc.min, rtc.sec, (u32)rtc_getTimestamp());
    return 0;
}

static int cmd_setNmea(const unsigned char *cmdString, unsigned short length)
{
    const u8 *nmea = (const u8 *)strstr((const char *)cmdString, "nmea") + strlen("nmea");
    LOG_DEBUG("cmd_setNmea: %s", nmea);
    gps_setNmeaStr(nmea, strlen(nmea));
    gps_parse(); //触发解析
    return 0;
}

static int cmd_setVersion(const unsigned char *cmdString, unsigned short length)
{
    const u8 *version = (const u8 *)strstr((const char *)cmdString, "setVersion") + strlen("setVersion");

    u8 *temp0, *temp1, *temp2;
    temp0 = string_bypassByNum(version, ".", 0);
    temp1 = string_bypassByNum(version, ".", 1);
    temp2 = string_bypassByNum(version, ".", 2);
    
    setting.defaultConf.version = (_atoi(temp0) << 16) | (_atoi(temp1) << 8) | _atoi(temp2);

    LOG_DEBUG("set version:%d.%d.%d",(setting.defaultConf.version >> 16) & 0xFF, (setting.defaultConf.version >> 8) & 0xFF, (setting.defaultConf.version) & 0xFF);
    defaultConf_save();
    fibo_taskSleep(100);
    fibo_softReset();
    return 0;
}

static int cmd_ublox(const unsigned char *cmdString, unsigned short length)
{
    const u8 *str = (const u8 *)strstr((const char *)cmdString, "ublox") + strlen("ublox");
    int cmd = 0;
    int rc = sscanf((const char *)str, "%d", &cmd);

    DBG_OUT("ublox cmd: %d", cmd);
    if(cmd == 1) //get version
    {
        Ublox_getVersion();
    }
    else if(cmd == 2)
    {
        Ublox_setModel(UBLOX_DYNAMIC_MODLE_STATIONNARY);
    }
    else if(cmd == 3)
    {
    }
    else if(cmd == 4)
    {
        Ublox_setModel(UBLOX_DYNAMIC_MODLE_AUTOMOTIVE);
    }

    return 0;
}

static int cmd_nmea(const unsigned char *cmdString, unsigned short length)
{
    int en = 0;
    if(1 == sscanf(cmdString, "nmea %d", &en) )
    {
        DBG_OUT("set nmea out en(%d)", en);
        if(en == L_TRUE || en == L_FALSE)
        {
            setting.settingConf.isNmeaOut = en;
            settingConf_save();
        }
        
        return 0;
    }

    return 0;
}

static int cmd_apn(const unsigned char *cmdString, unsigned short length)
{
    char apnname[64] = {0};
    char username[64] = {0};
    char password[64] = {0};
    if(sscanf(cmdString, "apn %[^,],%[^,],%[^,]", apnname, username, password) >= 1)
    {
        DBG_OUT("set apn apnname=%s, username=%s, password=%s", apnname, username, password);
        strncpy(setting.settingConf.apnname, apnname, 64);
        strncpy(setting.settingConf.username, username, 64);
        strncpy(setting.settingConf.password, password, 64);
        settingConf_save(); //将apn存储到setting
        
        setting_setRebootType(REBOOT_COMAND);
        fibo_taskSleep(500);
        fibo_softReset();
        return 0;
    }
    else
    {
        DBG_OUT("get apn apnname=%s, username=%s, password=%s", setting.settingConf.apnname, setting.settingConf.username, setting.settingConf.password);
    }

    return 0;
}

void debug_RegistUserCmd(void)
{
    regist_cmd((const unsigned char *)CMD_STRING_LS,  fs_ls);
    regist_cmd((const unsigned char *)CMD_STRING_RM,  fs_rm);
    regist_cmd((const unsigned char *)CMD_STRING_CAT, fs_cat);
    regist_cmd((const unsigned char *)"version", cmd_version);
    regist_cmd((const unsigned char *)"awake", cmd_awake);
    regist_cmd((const unsigned char *)"sendms", cmd_sendms);
    regist_cmd((const unsigned char *)"bleheart", cmd_bleHeartbeat);
    regist_cmd((const unsigned char *)"csq", cmd_csq);
    regist_cmd((const unsigned char *)"init audio", cmd_rsaudio);
    regist_cmd((const unsigned char *)"init custom audio", cmd_rmdtaudio);
    regist_cmd((const unsigned char *)"init setting", cmd_rssetting);
    regist_cmd((const unsigned char *)"init server", cmd_rsserver);
    regist_cmd((const unsigned char *)"openlog", cmd_openlog);
    regist_cmd((const unsigned char *)"closelog", cmd_closelog);
    regist_cmd((const unsigned char *)"clbs", cmd_clbs);
    regist_cmd((const unsigned char *)"bledebug", cmd_bledebug);
    regist_cmd((const unsigned char *)"displaylog", cmd_displaylog);
    regist_cmd((const unsigned char *)"setRTC", cmd_setRTC);
    regist_cmd((const unsigned char *)"nmea", cmd_setNmea);
    regist_cmd((const unsigned char *)"setVersion", cmd_setVersion);
    regist_cmd((const unsigned char *)"ublox", cmd_ublox);
    regist_cmd((const unsigned char *)"nmea", cmd_nmea);
    regist_cmd((const unsigned char *)"apn", cmd_apn);
}

int debug_initial(void)
{
    regist_cmd((const unsigned char *)DEBUG_CMD_PLAY,  cmd_play);
    regist_cmd((const unsigned char *)DEBUG_CMD_DEBUG, cmd_debug);
    regist_cmd((const unsigned char *)DEBUG_CMD_IMEI,  cmd_imei);
    regist_cmd((const unsigned char *)DEBUG_CMD_IMSI,  cmd_imsi);
    regist_cmd((const unsigned char *)DEBUG_CMD_CCID,  cmd_ccid);
    regist_cmd((const unsigned char *)DEBUG_CMD_AT,    cmd_AT);
    regist_cmd((const unsigned char *)DEBUG_CMD_at,    cmd_AT);
    regist_cmd((const unsigned char *)DEBUG_CMD_REBOOT,cmd_reboot);
    regist_cmd((const unsigned char *)DEBUG_CMD_SHUTDOWN,cmd_shutdown);
    regist_cmd((const unsigned char *)DEBUG_CMD_RTC,   cmd_rtc);
    regist_cmd((const unsigned char *)DEBUG_CMD_LOG,	cmd_log);
    regist_cmd((const unsigned char *)"server",	    cmd_server);

    return uart_registerHandler(UART_DEBUG, debug_proc);
}

