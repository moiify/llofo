#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "log.h"
#include "car.h"
#include "data.h"
#include "park.h"
#include "types.h"
#include "setting.h"
#include "gps_parse.h"
#include "user_timer.h"
#include "mpu_dmp_api.h"

#define GPS_VALID_SPEED (10)        // 10 km/h

#define YAW_VALID_VARIANCE (1.5)
#define SAMPLE_LEN (20)
#define FAULT_TIME (2)
#define CALDIRRECT_LOOP (100)
#define LIMIT_TIME (300)

static u8 g_isDirFixed = 0;
static L_BOOL g_isETCSpeedValid = L_TRUE;

typedef struct 
{
	double lon ;
	double lat ;
}POINT;

void park_setIsDirFixed(u8 isDirFixed)
{
    g_isDirFixed = isDirFixed;
}

u8 park_isDirFixed(void)
{
    return g_isDirFixed;
}

// 计算样本方差
static double cal_variance(double *data ,u8 len)
{
    u8 i = 0;
    double variance = 0, average = 0;
    double sum = 0.0, suqare = 0.0;
    if(len < 1)
    {
        return -1;
    }

    for(i=0; i < len; i++)
    {
        sum += data[i];
    }
    average = sum / len;
    for(i=0; i < len; i++)
    {
        suqare += pow((data[i] - average), 2);
    }

    variance = suqare / (len - 1);

    return  variance;
}

// 数据队列 gps方向角和偏航角， 求方差
static double get_dirVariance(double data, u8 len)
{
	static double gps_dir_buff[SAMPLE_LEN] = {0};
	double dir_variance;
	int i=0;
    
	for(i=0;i<len-1;i++)
	{
		gps_dir_buff[i] = gps_dir_buff[i+1];
	}
	gps_dir_buff[len-1] = data;
    
	dir_variance = cal_variance(gps_dir_buff, len);

	return dir_variance;
}

static L_BOOL park_isSpeedValidBeforeFixed(void)
{
    //当控制器速度恢复正常或者电门关闭时对控制器速度状态量进行复位
    if(data_getRealEtcSpeed() > 0 || car_isAccOn() == L_FALSE)
    {
        g_isETCSpeedValid = L_TRUE;
    }

    if(gps_getPosition()->nmeaInfo.speed > GPS_VALID_SPEED 
    && data_getRealEtcSpeed() == 0 && data_getData()->isWheelSpinning)
    {
        g_isETCSpeedValid = L_FALSE;
    }
    
    //在进入校准前，判断控制器速度是否达到要求，若控制器速度异常但是有轮动，则认为速度也有效，降低校准标准
    if(gps_getPosition()->nmeaInfo.speed > GPS_VALID_SPEED
    && (data_getRealEtcSpeed() > GPS_VALID_SPEED 
    ||  (data_getRealEtcSpeed() == 0 && data_getData()->isWheelSpinning)))
    {
        return L_TRUE;
    }
    return L_FALSE;
}

static L_BOOL park_isSpeedValidAfterFixed(void)
{
        //当控制器速度恢复正常或者电门关闭时对控制器速度状态量进行复位
    if(data_getRealEtcSpeed() > 0 || car_isAccOn() == L_FALSE)
    {
        g_isETCSpeedValid = L_TRUE;
    }

    if(gps_getPosition()->nmeaInfo.speed > GPS_VALID_SPEED 
    && data_getRealEtcSpeed() == 0 && data_getData()->isWheelSpinning)
    {
        g_isETCSpeedValid = L_FALSE;
    }

    //在已经进入校准的情况下，判断控制器速度是否达到要求
    if(gps_getPosition()->nmeaInfo.speed > GPS_VALID_SPEED
    && data_getRealEtcSpeed() > GPS_VALID_SPEED)
    {
        return L_TRUE;
    }
    return L_FALSE;
}

static double get_yawVariance(double data, u8 len)
{
	static double yaw_buff[SAMPLE_LEN] = {0};

    int i = 0;
    
    for(i = 0; i < len - 1; i++)
	{
		yaw_buff[i] = yaw_buff[i+1];
	}
    yaw_buff[len - 1] = data;
    
	return cal_variance(yaw_buff, len);
}

static L_BOOL is_gpsDirValid(double *dir_variance, double *yaw_variance)
{
    if(NULL == yaw_variance)
    {
        return L_FALSE;
    }
    
    // 检查gps是否可用，GPS已定位并且HDOP还可以
    if(!gps_getPosition()->isGPS)
    {
        return L_FALSE;
    }

    if(data_getData()->isAccelerateInitFault)return L_FALSE;
    
    //*dir_variance = get_dirVariance(gps_getPosition()->nmeaInfo.direction, SAMPLE_LEN);
    *yaw_variance = get_yawVariance(yaw_cal, SAMPLE_LEN); 
	if(*yaw_variance > 1000)
	{
		*yaw_variance = 1000;
	}

    //方差和速度都满足的情况下 可以校准
    //加速度计的方差要满足条件 2秒方差小于YAW_VALID_VARIANCE
    if(*yaw_variance < YAW_VALID_VARIANCE && park_isSpeedValidBeforeFixed() == L_TRUE)
    {
        return L_TRUE;
    }
    
    return L_FALSE;
}

static void park_calcDirect(void) //100ms
{    
    static u8 gFaultTime = 0;
    static u32 incorrectTime = 0;
    static float g_yaw_last = 0;
    static float g_staticOffset = 0;
	static double yaw_bak = 0, dir_bak = 0;

	double diff = 0, correct_Dir = 0, yaw_variance = 0;
    u8 isRevGpsMsg = gps_isRevGPSMsg();
    u8 isGpsDirValid = is_gpsDirValid(NULL, &yaw_variance); //是否经历了2秒的直线行驶
    
    gps_setRevGpsMsg(L_FALSE);
    do
    {
        //开始获取当前的陀螺仪地理方向, 这里是拿着之前校准后的方向进行比较
        //第一步 根据当前陀螺仪方向,计算实时diff
        if(yaw_cal - g_staticOffset < 0)
        {
            diff = (yaw_cal - g_staticOffset + 360) - yaw_bak;
        }
        else if(yaw_cal - g_staticOffset > 360)
        {
            diff = (yaw_cal - g_staticOffset - 360) - yaw_bak;//求当前相对于校准时的角度偏差 循环体不需要判断
        }
        else
        {
            diff = (yaw_cal - g_staticOffset) - yaw_bak;
        }

        //第二步 约束diff在0->360
        if(diff < 0)
        {
            diff = diff + 360;//如果需要翻转 翻转一下
        }
        else if(diff >= 360)
        {
            diff = diff - 360;//如果需要翻转 翻转一下
        }

        //第三步 计算陀螺仪地理方向
        correct_Dir = dir_bak + diff;
        if(correct_Dir < 0)
        {
            correct_Dir = correct_Dir + 360;//如果需要翻转 翻转一下
        }
        else if(correct_Dir >= 360)
        {
            correct_Dir = correct_Dir - 360;//如果需要翻转 翻转一下
        }
        //拿到当前的陀螺仪地理方向 correct_Dir
        if(isRevGpsMsg)
        {            
            double iDiff = abs(gps_getPosition()->nmeaInfo.direction - correct_Dir);
            if(iDiff > 180)
            {
                iDiff = 360 - iDiff;
            }
            if(iDiff > 5)
            {
                //GPS速度和控制器速度满足要求
                if(park_isSpeedValidAfterFixed() == L_TRUE)
                {
                    gFaultTime++;
                    //在任意行驶情况下,如果GPS方向持续2秒和陀螺仪方向误差较大,那么认为方向不准确，设置未校准状态
                    if(gFaultTime > FAULT_TIME * (1000 / CALDIRRECT_LOOP))
                    {
                        park_setIsDirFixed(DIR_NOT_FIX); //设置未校准状态
                    }
                }
            }
            else
            {
                gFaultTime = 0;
            }
        }

        //如果经历了2秒的直线行驶, 并且GPS精度还不错那么校准之
        if(isRevGpsMsg && isGpsDirValid && gps_getPosition()->nmeaInfo.HDOP < 2 && !data_getData()->isAccelerateInitFault)
        {
            if(!(gps_getPosition()->nmeaInfo.direction < 0.00001 && gps_getPosition()->nmeaInfo.direction > -0.00001))
            {
                yaw_bak = yaw_cal;//记录MPU校准角度
                incorrectTime = 0;//重置校准时间
                g_staticOffset = 0;//校准的时候清除掉之前的静飘偏差
                
                if(g_isETCSpeedValid)
                {
                    park_setIsDirFixed(DIR_DYNAMIC_FIXED); //设置校准状态（带控制器速度的校准状态）
                }
                else
                {
                    park_setIsDirFixed(DIR_STATIC_FIXED); //设置校准状态（静止状态或不带控制器速度的校准）
                }
                dir_bak = gps_getPosition()->nmeaInfo.direction;//记录GPS校准角度
                correct_Dir = gps_getPosition()->nmeaInfo.direction;//记录GPS校准角度
                break;
            }
        }

        //如果经历了2秒的直线行驶,并且还在校准状态
        //但陀螺仪方向和GPS方向误差较大,可以降低精度要求校准之
        if(isRevGpsMsg && isGpsDirValid && park_isDirFixed())
        {
            double iDiff = abs(gps_getPosition()->nmeaInfo.direction - correct_Dir);
            if(iDiff > 180)
            {
                iDiff = 360 - iDiff;
            }
            if(iDiff > 5)
            {
                if(gps_getPosition()->nmeaInfo.HDOP < 4 && !data_getData()->isAccelerateInitFault)
                {
                    //如果判定可以校准并且刚刚收到GPS信息(100ms以内) 那么校准之
                    yaw_bak = yaw_cal;//记录MPU校准角度
                    incorrectTime = 0;//重置校准时间
                    g_staticOffset = 0;//校准的时候清除掉 之前的静飘偏差
                    
                    if(g_isETCSpeedValid)
                    {
                        park_setIsDirFixed(DIR_DYNAMIC_FIXED); //设置校准状态（带控制器速度的校准状态）
                    }
                    else
                    {
                        park_setIsDirFixed(DIR_STATIC_FIXED); //设置校准状态（静止状态或不带控制器速度的校准）
                    }
                    dir_bak = gps_getPosition()->nmeaInfo.direction;//记录GPS校准角度
                    correct_Dir = gps_getPosition()->nmeaInfo.direction;//记录GPS校准角度
                    break;
                }
            }
        }
        
        //处理静飘 在电门关闭并且没有震动的情况下 小的漂移直接通过staticOffset抵掉
        if(!car_isAccOn() && !data_getData()->isShaking && setting_isDefendOn())
        {
            if(abs(yaw_cal - g_yaw_last) < 0.2f)
            {
                g_staticOffset += yaw_cal - g_yaw_last;
                //当静飘大于360时，表示静飘超过一周，做取余处理
                if(g_staticOffset >= 360)
                {
                    g_staticOffset -= 360;
                }
            }
        }
        g_yaw_last = yaw_cal;
    }while(L_FALSE);
    
    //开始获取当前的陀螺仪地理方向, 这里是将更新的地理方向记录下来
    //第一步 根据当前陀螺仪方向,计算实时diff
    if(yaw_cal - g_staticOffset < 0)
    {
        diff = (yaw_cal - g_staticOffset + 360) - yaw_bak;
    }
    else if(yaw_cal - g_staticOffset > 360)
    {
        diff = (yaw_cal - g_staticOffset - 360) - yaw_bak;//求当前相对于校准时的角度偏差 循环体不需要判断
    }
    else
    {
        diff = (yaw_cal - g_staticOffset) - yaw_bak;
    }
    
    //第二步 约束diff在0->360
    if(diff < 0)
    {
        diff = diff + 360;//如果需要翻转 翻转一下
    }
    else if(diff >= 360)
    {
        diff = diff - 360;//如果需要翻转 翻转一下
    }
    
    //第三步 计算陀螺仪地理方向
    correct_Dir = dir_bak + diff;
    if(correct_Dir < 0)
    {
        correct_Dir = correct_Dir + 360;//如果需要翻转 翻转一下
    }
    else if(correct_Dir >= 360)
    {
        correct_Dir = correct_Dir - 360;//如果需要翻转 翻转一下
    }
    //拿到更新后的陀螺仪地理方向 correct_Dir
    
	data_getData()->headingAngle = correct_Dir;//记录实时方向
    
    //如果GPS方向持续5min无效，则认为方向不准确
    if(incorrectTime++ >= LIMIT_TIME * (1000 / CALDIRRECT_LOOP))
    {
        park_setIsDirFixed(DIR_NOT_FIX); //设置未校准状态
    }
}

int park_dirFix_timerHandler(void)//100ms
{      
    park_calcDirect(); //计算方向角
    data_getData()->fixtype = park_isDirFixed();
	return 0;
}

static int park_getYaw_timerHandler(void)
{
	static u32 cnt = 0;
	
	mpu_dmp_getData();
	if(cnt++ % 10 == 0) //100ms
	{
		park_dirFix_timerHandler();
        if(cnt >= 4294967295uL)cnt = 0;
	}
    return 0;
}

void park_initial(void)
{
    timer_startRepeat(TIEMR_PARK_DIR, TIMER_MS, CALC_DIR_TIME, park_getYaw_timerHandler);
}
