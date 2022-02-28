/*
 * data.c
 *
 *  Created on: 2020/04/09
 *      Author: lc
 */

#include "data.h"
#include "log.h"
#include "setting.h"

static DATA data;

DATA *data_getData(void)
{
    return &data;
}

/*
*get the last gps info
*/
POSITION *data_getPosition(void)
{
    return &data.lastPosition;
}

/*
*save the last position info
*/
void data_savePosition(POSITION *pos)
{
    data.lastPosition.isGPS = pos->isGPS;
    data.lastPosition.nmeaInfo = pos->nmeaInfo;
    data.lastPosition.timestamp = pos->timestamp;
    data.lastPosition.tagNmeaInfo = pos->tagNmeaInfo;
    data.lastPosition.tagTimestamp = pos->tagTimestamp;

    data.lastPosition.lbsInfo = pos->lbsInfo;
    data.lastPosition.isCLBS = pos->isCLBS;
    data.lastPosition.lbsTimestamp = pos->lbsTimestamp;

    data.lastPosition.cellInfo = pos->cellInfo;
}

L_BOOL data_isTime2Sleep(void)
{
    if (!data.awakeTime)
    {
        return L_TRUE;
    }
    return L_FALSE;
}

void data_minusAwakeTime(void)
{
    if (data.awakeTime)
    {
        data.awakeTime--;
        LOG_DEBUG("the left time to sleep .....is %d", data.awakeTime);
    }
}

void data_setAwakeTime(u32 time_s)
{
    if (time_s > data.awakeTime)
    {
        data.awakeTime = time_s;
    }
}

u32 data_getAwakeTime(void)
{
    return data.awakeTime;
}

u8 data_isSleeping(void)
{
    return data.isSleeping;
}

void data_setSleepState(u8 state)
{
    data.isSleeping = state;
}
void data_addVivrationTime(void)
{
    data.vibrationTime++;
}

void data_resetVibrationTime(void)
{
    data.vibrationTime = 0;
}

u32 data_getVibrationTime(void)
{
    return data.vibrationTime;
}

u8 data_getBMSSOC(void)
{
    return (data.bms.SOH);
}

u8 data_isLogined(void)
{
    return data.isLogined;
}

void data_setAccelerometerFault(L_BOOL sw)
{
    data.isAccelerometerFault = sw;
}

L_BOOL data_getAccelerometerFault(void)
{
    return data.isAccelerometerFault;
}
/*
*data of isMove
*/
void data_setMovedState(u8 state)
{
    data.isMoving = state;
}

u8 data_GetMoveState(void)
{
    return data.isMoving;
}

#define PI 3.141592653
float HALL2SPEED(u32 pulse)
{
    if (memcmp(setting.defaultConf.name, "AT-MX5Z5", strlen("AT-MX5Z5")) == 0)
    {
        return (pulse * 3600 * 0.39 * PI / (1000 * 25 * 3)); //当肯松果6.5车型 系数0.058811
    }
    return (pulse * 7200 * 14 * 2.54 * PI / (100000 * 6 * 20)); //Q1车型 系数 系数0.067029
}

u8 data_getRealEtcSpeed(void)
{
    u8 realSpeed = 0;
    if (setting.settingConf.etcSpeedSource == ETC_NO_SPEED_OR_HALL)
    {
        return 0;
    }
    else if (setting.settingConf.etcSpeedSource == ETC_FIRST_USE_SPEED)
    {
        if (data_getData()->etc.speed != 0 && data_getData()->etc.speed < 50) //避免某些控制器速度不变异常为100
        {
            realSpeed = data_getData()->etc.speed * setting.settingConf.etcSpeedRatio;
            return realSpeed;
        }
        if (data_getData()->etc.pulse != 0)
        {
            realSpeed = data_getData()->etc.pulse * setting.settingConf.etcHallRatio; //HALL2SPEED()
            return realSpeed;
        }
    }
    else if (setting.settingConf.etcSpeedSource == ETC_ONLT_USE_SPEED)
    {
        if (data_getData()->etc.speed != 0)
        {
            realSpeed = data_getData()->etc.speed * setting.settingConf.etcSpeedRatio;
            if(realSpeed > 50) //避免某些控制器速度不变异常为100
            {
                return 0;
            }
            return realSpeed;
        }
    }
    else if (setting.settingConf.etcSpeedSource == ETC_ONLT_USE_HALL)
    {
        if (data_getData()->etc.pulse != 0)
        {
            realSpeed = data_getData()->etc.pulse * setting.settingConf.etcHallRatio; //HALL2SPEED()
            return realSpeed;
        }
    }
    return 0;
}

u8 data_isHeadingAngleFixed(void) //检查设备是否进入惯导状态
{
    u8 isFixed = L_FALSE;
    
    if (setting.settingConf.gpsType == GPS_UBLOX_M8U && setting.settingConf.accleType == ACCLE_LIS3DH) //M8U定向停车方案
    {
        if (DIR_INS_STATUS == data_getData()->fixtype || DIR_DR_STATUS == data_getData()->fixtype)
        {
            isFixed = L_TRUE;
        }
        else
        {
            isFixed = L_FALSE;
        }
    }
    else if (setting.settingConf.accleType == ACCLE_MPU6500) //MPU6500定向停车方案
    {
        if (DIR_STATIC_FIXED == data_getData()->fixtype || DIR_DYNAMIC_FIXED == data_getData()->fixtype)
        {
            isFixed = L_TRUE;
        }
        else
        {
            isFixed = L_FALSE;
        }
    }
    return isFixed;
}

s16 data_getHeadingAngle(void) //获取方向角整数形式（保留小数点后一位）
{
    s16 pa = 0;
    u8 isFixed = data_isHeadingAngleFixed();

    if (isFixed)
    {
        //转换成一个小数点
        pa = (int)(10 * data_getData()->headingAngle + 10 * 0.05);
    }
    else
    {
        //转换成一个小数点
        pa = (int)(10 * data_getData()->headingAngle + 10 * 0.05);
        pa = -1 * pa;
        if (pa == 0) //pa的值为0 改写成 -0.1
        {
            pa = -1;
        }
    }
    return pa;
}

//获取几秒内最好的道钉信息
beaconInfo_t *data_getTBeaconInfo(int limitTime)
{
    int pos = -1;
    int min_dbm = 128;

    if (limitTime > 5)
    {
        limitTime = 5;
    }
    if (limitTime < 2)
    {
        limitTime = 2;
    }
    for (int i = 0; i < limitTime; i++)
    {
        if (data.tBeaconStatus.highestInfoNSecondsAgo[i].dbm != 0)
        {
            if (data.tBeaconStatus.highestInfoNSecondsAgo[i].dbm < min_dbm)
            {
                pos = i;
                min_dbm = data.tBeaconStatus.highestInfoNSecondsAgo[i].dbm;
            }
        }
    }
    if (pos >= 0 && pos < limitTime)
    {
        return &data.tBeaconStatus.highestInfoNSecondsAgo[pos];
    }
    return NULL;
}

L_BOOL data_isInNight(u8 night, u8 day) //night:晚上N点  day:早上N点
{
    if (night < 0 || night > 23 || day < 0 || day > 23)
    {
        return L_FALSE;
    }
    u32 timestamp = (u32)rtc_getTimestamp();
    u32 realTime = (timestamp + 28800) % 86400;
    if (timestamp > 1546272000 && ((realTime >= (night * 3600) && realTime < 86400) || (realTime > 0 && realTime <= (day * 3600))))
    {
        return L_TRUE;
    }
    return L_FALSE;
}
