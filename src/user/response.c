/*
 * response.c
 *
 *  Created on: 2020/04/09
 *      Author: lc
 */
#include <string.h>
#include <stdint.h>

#include "msg.h"
#include "rtc.h"
#include "log.h"
#include "data.h"
#include "types.h"
#include "client.h"
#include "request.h"
#include "response.h"
#include "protocol.h"
#include "device_msg.h"
#include "user_timer.h"
#include "agps.h"
#include "device.h"
#include "setting.h"

int cmd_Login_rsp(const void* msg)
{
    MSG_LOGIN_REQ_NEW_RSP *rsp= (MSG_LOGIN_REQ_NEW_RSP *)msg;

    /* 服务器时间戳同步 */
    rtc_updateTimestamp(_htonl(rsp->timestamp));
    LOG_DEBUG("[cmd] TimeStamp rsp >>>> set %d  get %d ",_htonl(rsp->timestamp), (u32)rtc_getTimestamp());

    data_getData()->isLogined = L_TRUE;
	data_getData()->socstate.conn_success++;
	
    /* 登陆后1s上报一次GPS供服务器判断设备状态模式 */
    timer_start(TIMER_SEND_GPS, TIMER_MS, 1000, cmd_statusMatchPeriod);

	timer_start(TIMER_AGPS_ONCE, TIMER_MS, 100, agps_NeedAGPS); //登录后立马进行一次AGPS
	
	timer_start(TIMER_GETVERSION, TIMER_S, 5, setting_versionPatch);
    if(timer_isTimerStart(TIMER_CHANGESERVER_TIMEOUT))
    {
        serverConf_save();//切服务器成功后保存
        timer_stop(TIMER_CHANGESERVER_TIMEOUT);
    }
    LOG_DEBUG("[Device CMD] get login new respond.");

    return 0;
}

int cmd_Ping_rsp(const void* msg)
{
    DATA *pData = data_getData();
    
    LOG_DEBUG("[Device CMD] get ping respond.");
    pData->heartBeatLostTimes = 0;

    return 0;
}

int cmd_Alarm_rsp(const void* msg)
{
    LOG_DEBUG("[Device CMD] get alarm respond");
    return 0;
}

static MC_MSG_PROC msgProcs[] =
{
    {CMD_ALARM,         cmd_Alarm_rsp},
    {CMD_LOGIN_NEW,     cmd_Login_rsp},
    {CMD_PING,          cmd_Ping_rsp},
    {CMD_WILD,          device_msg_handler},
    {CMD_DEVICE,        device_msg_handler},
};

static MC_MSG_PROC msgUdpProcs[] =
{
    {CMD_WILD,      device_msg_handler},
    {CMD_DEVICE,    device_msg_handler},
    {CMD_WILD_NEW,  device_new_handler},
};

void response_initial(void)
{
    device_initail();
    client_initail((void *)msgProcs, sizeof(msgProcs) / sizeof(msgProcs[0]));
    client_initailUDP((void *)msgUdpProcs, sizeof(msgUdpProcs) / sizeof(msgUdpProcs[0]));
}

