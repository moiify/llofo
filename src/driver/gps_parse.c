
#include <stdio.h>
#include <string.h>

#include "nmea/gmath.h"
#include "nmea/units.h"
#include "nmea/sentence.h"
#include "nmea/parser.h"

#include "log.h"
#include "car.h"
#include "msg.h"
#include "agps.h"
#include "data.h"
#include "uart.h"
#include "ublox.h"
#include "utils.h"
#include "fence.h"
#include "userMsg.h"
#include "setting.h"
#include "request.h"
#include "hardware.h"
#include "user_at.h"
#include "diagnosis.h"
#include "gps_parse.h"
#include "user_timer.h"
#include "gps_filter.h"
#include "utc_time.h"
#include "display_log.h"
#include "ublox.h"
#include "audio_driver.h"

static uint32_t g_missNMEACount = 0;
static POSITION g_position;
static uint8_t *g_nmea_raw_str = NULL;
static int16_t  g_nmea_raw_len = 0;

#define MAX_BUFFER_SIZE (1576)
#define AUDIO_PLAY_PERIOD 15

static uint8_t *g_nmea_str = NULL;

POSITION *gps_getPosition(void)
{
    return &g_position;
}

uint8_t *gps_getLastNMEA_str(void)
{
    if(g_nmea_str)return g_nmea_str;
    return (uint8_t *)"";
}

#define NMEA_LIMIT_LEN 900
uint8_t *gps_getLastNMEA_strLimit(void)
{
    if(!g_nmea_str)
    {
        return (uint8_t *)"";
    }

    static char *nmeaLimitStr = NULL;
    if(!nmeaLimitStr)
    {
        nmeaLimitStr = Malloc(NMEA_LIMIT_LEN + 1); //为满足socket 1024的限长，需要对nmea做更小的限长
    }
    memset(nmeaLimitStr, 0, NMEA_LIMIT_LEN + 1);
    LOG_HEX(g_nmea_str, strlen((const char *)g_nmea_str));

    char *all = (char *)g_nmea_str;
    char *begin = NULL;
    char *end = NULL;
    int subLen = 0, strLen = 0;
    while(begin = strstr(all, "$G"))
    {
        begin += 3; //跳过"$GN"
        if(strncmp(begin, "RMC", 3) == 0
        || strncmp(begin, "GGA", 3) == 0
        || strncmp(begin, "GSV", 3) == 0
        || strncmp(begin, "GSA", 3) == 0)
        {
            end = strstr(begin, "\r\n"); //找到下个回车
            if(!end)
            {
                break; //未找到结束则退出
            }
            subLen = end - begin + 3 + 2; //"$GN"和"\r\n"
            if(strLen + subLen > NMEA_LIMIT_LEN)
            {
                break; //长度加当前子串超限则退出
            }

            memcpy(nmeaLimitStr + strLen, begin - 3, subLen); //拷贝"$GN"到"\r\n"之间的字符串
            strLen += subLen; //长度后移子串长度
        }
        all = begin; //从子串后开始新一轮匹配
    }

    LOG_HEX(nmeaLimitStr, strlen((const char *)nmeaLimitStr));
    return (uint8_t *)nmeaLimitStr;
}

void gps_nmeaOutputEnable(uint8_t isEnable)
{
    if(isEnable)
    {
        if(setting.settingConf.gpsType == GPS_ALLYSTAR_8040)
        {
            gps_moudleReset();
        }
        else if(setting.settingConf.gpsType == GPS_UBLOX_8130 || setting.settingConf.gpsType == GPS_UBLOX_M8U
                || setting.settingConf.gpsType == GPS_UBLOX_7020)
        {
            Ublox_gotoAwake();
        }
    }
    else
    {
        if(setting.settingConf.gpsType == GPS_ALLYSTAR_8040)
        {
            //allystar_sleep();
        }
        else if(setting.settingConf.gpsType == GPS_UBLOX_8130 || setting.settingConf.gpsType == GPS_UBLOX_M8U
                || setting.settingConf.gpsType == GPS_UBLOX_7020)
        {
            Ublox_gotoSleep();
        }
    }
}

/*
*在省电模式，每一个小时打开GPS一分钟
*/
static int gps_powerManagerByModeHandler(void)
{
    if(g_missNMEACount == (60)) // 持续一分钟没有nmea数据
    {
        Ublox_hotRestart();
    }
    else if (g_missNMEACount == 120) // 持续两分钟没有nmea数据
    {
        Ublox_coldRestart();
    }

    if(g_missNMEACount++ >= (300))//如果持续五分钟没有nmea数据 重启设备
    {
        g_missNMEACount = 0;
        fibo_softReset();
    }
    return 0;
}

static int gps_parseNMEA_GNGGA(uint8_t *nmea_str, uint32_t length, nmeaINFO *nmeaInfo)
{
    char *p = string_bypass((const char *)nmea_str, "GGA,");
    if(p)
    {
        char *pGpsState = string_bypassByNum((const char *)p, ",", 5);
        if(pGpsState)
        {
            int inuse = 0;
            int gpsState = 0;
            int count = sscanf(pGpsState, "%d,%d%*s", &gpsState, &inuse);
            if(2 == count)
            {
                nmeaInfo->gpsState = gpsState;
                nmeaInfo->satinfo.inuse = inuse;
            }
        }
        return 1;
    }
    return 0;
}

static int gps_parseNMEA_GPGSA(uint8_t *nmea_str, uint32_t length, nmeaINFO *nmeaInfo)
{
    char *p = string_bypass((const char *)nmea_str, "GSA,");
    if(p)
    {
        char *pFix = string_bypassByNum((const char *)p, ",", 1);
        char *pPDOP = string_bypassByNum((const char *)p, ",", 14);

        if(pFix)
        {
            int fix = 0;
            int count = sscanf(pFix, "%d", &fix);
            if(1 == count)
            {
                nmeaInfo->fix = fix;
            }
        }

        if(pPDOP)
        {
            double PDOP = 0.0, HDOP = 0.0, VDOP = 0.0;
            int count = sscanf(pPDOP, "%lf,%lf,%lf%*s", &PDOP, &HDOP, &VDOP);
            if(3 == count)
            {
                nmeaInfo->HDOP = HDOP;
                nmeaInfo->PDOP = PDOP;
                nmeaInfo->VDOP = VDOP;
            }
        }

        if(setting.settingConf.gpsType == GPS_UBLOX_M8U && setting.settingConf.accleType == ACCLE_LIS3DH) //M8U定向停车方案产品
        {
            u8 i = 0;
            char *pUse = string_bypassByNum((const char *)p, ",",2);
            if(pUse) //解析所有GSA数据
            {
                for(i = 0; i < 12; i++)
                {
                    int prn = 0;
                    int count = sscanf(pUse, "%d%*s", &prn);
                    if(count != 1) //如果第i个卫星没有则停止
                    {
                        break;
                    }
                    data_getData()->gpsPrns[i] = prn;
                    pUse = string_bypass((const char *)pUse, ",");
                }
            }
        }
        return 1;
    }
    return 0;
}

static int gps_parseNMEA_GPGSV(uint8_t *nmea_str, uint32_t length, nmeaINFO *nmeaInfo)
{
    char *p = string_bypass((const char *)nmea_str, "GSV,");

    if(p)
    {
        if(setting.settingConf.gpsType == GPS_UBLOX_M8U && setting.settingConf.accleType == ACCLE_LIS3DH) //M8U定向停车方案产品
        {
            while(p) //解析所有GSV数据
            {
                char *pInview = string_bypassByNum((const char *)p, ",", 2);
                if(pInview)
                {
                    int inview = 0;
                    int i = 0, j = 0;
                    int prn[4] = {0};
                    int sig[4] = {0};
                    sscanf(pInview, "%d,%d,%*d,%*d,%d,%d,%*d,%*d,%d,%d,%*d,%*d,%d,%d,%*d,%*d,%d"
                            , &inview, prn, sig, prn + 1, sig + 1, prn + 2, sig + 2, prn + 3, sig + 3);

                    nmeaInfo->satinfo.inview = inview;
                    for(i = 0; i < sizeof(data_getData()->gpsPrns); i++)
                    {
                        for(j = 0; j < 4; j++)
                        {
                            if(data_getData()->gpsPrns[i] == prn[j])
                            {
                                data_getData()->gpsSigs[i] = sig[j];
                            }
                        }
                    }
                    p = string_bypass((const char *)p, "GSV,");
                }
            }
        }
        else
        {
            char *pInview = string_bypassByNum((const char *)p, ",", 2);
            if(pInview)
            {
                int inview = 0;
                int count = sscanf(pInview, "%d%*s", &inview);
                if(1 == count)
                {
                    nmeaInfo->satinfo.inview = inview;
                }
            }
        }
        return 1;
    }
    return 0;
}

static int gps_parseNMEA_GNRMC(uint8_t *nmea_str, uint32_t length, nmeaINFO *nmeaInfo)
{
    char *p = string_bypass((const char *)nmea_str, "RMC,");
    if(p)
    {
        char *pTime = string_bypassByNum((const char *)p, ",", 0);
        char *pAvalid = string_bypassByNum((const char *)p, ",", 1);
        char *pGPS = string_bypassByNum((const char *)p, ",", 2);
        char *pSpeed = string_bypassByNum((const char *)p, ",", 6);
        char *pCourse = string_bypassByNum((const char *)p, ",", 7);
        char *pDate = string_bypassByNum((const char *)p, ",", 8);

        if(pTime)
        {
            double time = 0.0;
            int count = sscanf(pTime, "%lf%*s", &time);
            if(1 == count)
            {
                nmeaInfo->utc.hour = (int)(time / 10000);
                nmeaInfo->utc.min = (int)((time - nmeaInfo->utc.hour * 10000) / 100);
                nmeaInfo->utc.sec = (int)(time - nmeaInfo->utc.hour * 10000 - nmeaInfo->utc.min * 100);
            }
        }

        if(pAvalid)
        {
            char c_Avalid;
            int count = sscanf(pAvalid, "%c%*s", &c_Avalid);
            if(1 == count)
            {
                if(c_Avalid == 'A')
                {
                    nmeaInfo->sig = NMEA_SIG_MID;
                }
                else if(c_Avalid == 'V')
                {
                    nmeaInfo->sig = NMEA_SIG_BAD;
                }
            }
        }

        if(pGPS)
        {
            char isEast, isNorth;
            double lat = 0.0, lon = 0.0;
            int count = sscanf(pGPS, "%lf,%c,%lf,%c%*s", &lat, &isNorth, &lon, &isEast);
            if(4 == count)
            {
                if(isNorth == 'N')
                {
                    nmeaInfo->lat = lat;
                }
                else
                {
                    nmeaInfo->lat = -lat;
                }

                if(isEast == 'E')
                {
                    nmeaInfo->lon = lon;
                }
                else
                {
                    nmeaInfo->lon = -lon;
                }
            }
        }

        if(pSpeed)
        {
            double speed = 0.0;
            int count = sscanf(pSpeed, "%lf%*s", &speed);
            if(1 == count)
            {
                nmeaInfo->speed = speed * NMEA_TUD_KNOTS;
            }
        }

        if(pCourse)
        {
            double course = 0.0;
            int count = sscanf(pCourse, "%lf%*s", &course);
            if(1 == count)
            {
                nmeaInfo->direction = course;
            }
        }

        if(pDate)
        {
            int year = 0, mon = 0, day = 0;
            int count = sscanf(pDate, "%2d%2d%2d%*s", &day, &mon, &year);
            if(3 == count)
            {
                nmeaInfo->utc.year = year;
                nmeaInfo->utc.mon = mon;
                nmeaInfo->utc.day = day;

                if(nmeaInfo->utc.year < 80)
                    nmeaInfo->utc.year += 100;
                nmeaInfo->utc.mon -= 1;
            }
        }
        return 1;
    }
    return 0;
}

static int gps_nmea_parse(uint8_t *nmea_str, uint32_t length, nmeaINFO *nmeaInfo)
{
    int sentence = 0;
    int parse_num = 0;

    g_position.isGPS = L_FALSE;
    memset(&g_position.nmeaInfo, 0, sizeof g_position.nmeaInfo);

    if(gps_parseNMEA_GNRMC(nmea_str, length, nmeaInfo))
    {
        parse_num++;
        sentence |= GPRMC;
    }

    if(gps_parseNMEA_GNGGA(nmea_str, length, nmeaInfo))
    {
        parse_num++;
        sentence |= GPGGA;
    }

    if(gps_parseNMEA_GPGSA(nmea_str, length, nmeaInfo))
    {
        parse_num++;
        sentence |= GPGSA;
    }
    if(gps_parseNMEA_GPGSV(nmea_str, length, nmeaInfo))
    {
        parse_num++;
        sentence |= GPGSV;
    }

    return parse_num;
}

#define MAX_IGPSMILES (20)
static uint8_t gps_isNMEAMessage(uint8_t *nmea_str, uint16_t length)
{
    if(string_bypass((const char *)nmea_str, "RMC,"))
    {
        return L_TRUE;
    }
    if(string_bypass((const char *)nmea_str, "GGA,"))
    {
        return L_TRUE;
    }
    if(string_bypass((const char *)nmea_str, "GSA,"))
    {
        return L_TRUE;
    }
    if(string_bypass((const char *)nmea_str, "GSV,"))
    {
        return L_TRUE;
    }
    return L_FALSE;
}

static L_BOOL gps_isPollACK(uint8_t *nmea_str, uint16_t length)
{
    u16 offect = 0;
    if(nmea_str && length)
    {
        while(offect < length)
        {
            if(nmea_str[offect] == 0xB5 && nmea_str[offect + 1] == 0x62)
            {
                if(nmea_str[offect + 8] == Ublox_getExpectMode())
                {
                    data_getData()->ublox_setModeACK = L_TRUE;
                    LOG_DEBUG("[gps] get Mode Poll ACK %d", nmea_str[offect + 8]);
                }
                return L_TRUE;
            }
            offect++;
        }
    }
    return L_FALSE;
}

//1s调用
static int gps_DynStafilter(void)
{
    static double lastLat = 0.001;
    static double lastLon = 0.001;
    static u32 lastTime = 0;
    double lat = nmea_ndeg2degree(g_position.nmeaInfo.lat);
    double lon = nmea_ndeg2degree(g_position.nmeaInfo.lon);

    if(lastLat < 0.1 || lastLon < 0.1 || (g_position.timestamp - lastTime > 2)) //无定位或定位无时效
    {
        lastLat = lat;
        lastLon = lon;
        lastTime = g_position.timestamp;
        return L_FALSE;
    }

    if(setting_isDefendOn()) //如果车辆处于设防状态且未移动，经纬度变化超过0.0001，触发静态过滤
    {
        if(!data_getData()->isWheelSpinning && !data_getData()->isMoving
        && ((lastLat - lat > 0.0001) || (lat - lastLat > 0.0001)
            || (lastLon - lon > 0.0001) || (lon - lastLon > 0.0001)) //约10m
        )
        {
            return L_TRUE;
        }
    }

    if(setting_isAccOn()) //如果处于电门开启状态且有轮动，GPS速度超过两倍控制器速度或经纬度变化超过0.001，触发动态过滤
    {
        if(data_getData()->isWheelSpinning
        && ((data_getRealEtcSpeed() && (g_position.nmeaInfo.speed >= 2 * data_getRealEtcSpeed()))
            || ((lastLat - lat > 0.001) || (lat - lastLat > 0.001)
                || (lastLon - lon > 0.001) || (lon - lastLon > 0.001))) //约100m
        )
        {
            return L_TRUE;
        }
    }

    if(g_position.nmeaInfo.speed > 150.0f)  //过滤夸张静飘
    {
        return L_TRUE;
    }

    lastLat = lat;
    lastLon = lon;
    lastTime = g_position.timestamp;
    return L_FALSE;
}

#define DEBUG_DISPLAY 0

#if DEBUG_DISPLAY //在这里配置显示屏显示信息，方便调试
static void debug_display(void)
{
    DATA* pData = data_getData();
    char str[50],str2[50],str3[50],str4[50],str5[50],str6[50];

    memset(str,0,50);
    memset(str2,0,50);
    memset(str3,0,50);
    memset(str4,0,50);
    memset(str5,0,50);
    memset(str6,0,50);

    sprintf(str,"fixtype: %d",pData->fixtype);
    display_log(str,0); //在显示屏第0行显示出来，方便调试
    sprintf(str2,"heading: %5.2f",pData->headingAngle);
    display_log(str2,1); //在显示屏第1行显示出来，方便调试
    sprintf(str3,"accheading: %d",pData->accHeading);
    display_log(str3,2); //在显示屏第2行显示出来，方便调试
    sprintf(str4,"lat: %f",g_position.nmeaInfo.lat);
    display_log(str4,3); //在显示屏第3行显示出来，方便调试
    sprintf(str5,"lon: %f",g_position.nmeaInfo.lon);
    display_log(str5,4); //在显示屏第4行显示出来，方便调试
    sprintf(str6,"%d-%d %d:%d:%d",g_position.nmeaInfo.utc.mon + 1,g_position.nmeaInfo.utc.day,
            g_position.nmeaInfo.utc.hour + 8,g_position.nmeaInfo.utc.min,(g_position.nmeaInfo.utc.sec % 60));
    display_log(str6,5); //在显示屏第5行显示出来，方便调试
}
#endif

ALARM_TYPE_RETURN judgeWarningType(char lastIsInServiceArea, char fenceAreaType)
{
    if(lastIsInServiceArea == RIDING_AREA && fenceAreaType == ALARM_AREA)
    {
        return TYPE_OUT_WARNING_FENCE;
    }
    else if(lastIsInServiceArea == ALARM_AREA && fenceAreaType == OUTSERVICE_AREA)
    {
        return TYPE_OUT_SERVER_FENCE;
    }
    else if(lastIsInServiceArea == OUTSERVICE_AREA && fenceAreaType == ALARM_AREA)
    {
        return TYPE_IN_SERVER_FENCE;
    }
    else if(lastIsInServiceArea == ALARM_AREA && fenceAreaType == RIDING_AREA)
    {
        return TYPE_IN_WARNING_FENCE;
    }
}

int gps_parse(void)
{
    static char lastIsInServiceArea = -1;//上一次区域状态
    static uint8_t isFirstMilesPoint = 1;
    static int outrageousCount = 0;//连续出现离谱的GPS距离次数
    int num = 0;
    static int count = 0;
    static char playCount = 0;
    u16 nmea_len = g_nmea_raw_len;
    u8 *nmea_str = g_nmea_raw_str;
    static u8 isfirst = 1;

    if(setting.settingConf.gpsType == GPS_UBLOX_M8U && setting.settingConf.accleType == ACCLE_LIS3DH) //M8U定向停车方案产品
    {
        if(nmea_len < sizeof(UBLOX_HEAD_DATA))
        {
            return -1; //6个字节，比nmea数据小，直接过滤
        }
        Ublox_M8U_procUbloxMsg(nmea_str, nmea_len); //对M8U模块数据进行解析

        int pos = 0;
        for(; pos < nmea_len - 1; pos++)
        {
            if(0 == memcmp(nmea_str + pos, "$G", 2)) //获取nmea数据位置
            {
                nmea_str = nmea_str + pos;
                nmea_len = nmea_len - pos;
                break;
            }
        }
        while((nmea_str[nmea_len-1] != '\n' || nmea_str[nmea_len-2] != '\r') && (nmea_len > 2))//过滤掉nmea数据包末尾垃圾数据
        {
            nmea_len--;
        }
    }
    else if(setting.settingConf.gpsType == GPS_ALLYSTAR_8040)
    {
        LOG_DEBUG("ALLYSTAR NEMA PHASE");
    }
    else if(setting.settingConf.gpsType == GPS_UBLOX_8130 || setting.settingConf.gpsType == GPS_UBLOX_M8U
        || setting.settingConf.gpsType == GPS_UBLOX_7020)
    {
        if(data_getData()->isReadyToSleep) //若即将进入休眠，则不解析数据，避免再次发送数据到ublox，导致模块未完全休眠
        {
            return 0;
        }

        //配置为GNGSV, 如果遇到GPGSV 重新配置一下UBLOX
        if(strstr((const char *)nmea_str, "GPGSV"))
        {
            Ublox_checkVersion_cb();
        }
    }

    if(!gps_isNMEAMessage(nmea_str, nmea_len))
    {
        return -1; //屏蔽掉不是nmea数据的数据
    }

    if(setting.settingConf.isNmeaOut)
    {
        LOG_INFO("nmea recv(%d):\r\n%s\r\n", nmea_len, nmea_str);
    }

    if(setting_getVerisonType() == VERSION_TYPE_MX5K6_LS && !setting.statusConf.gpsBaudrateUpdateFlag)
    {
        setting.statusConf.gpsBaudrateUpdateFlag = 1;
        statusConf_save();
    }

    if(isfirst) //只需要自检一次
    {
        diag_GPSCheckSuccess();//收到NMEA数据表示GPS模块自检通过
        isfirst = 0;
    }

    //总里程计算逻辑 如果是设防状态 清空之前的历史里程记录点
    if(setting_isDefendOn())
    {
        outrageousCount = 0;
        if(setting.statusConf.lastMileLat != 0 || setting.statusConf.lastMileLon != 0)
        {
            setting.statusConf.lastMileLat = 0;
            setting.statusConf.lastMileLon = 0;
            statusConf_save();
        }
    }

    g_position.isGPS = L_FALSE;
    nmea_zero_INFO(&g_position.nmeaInfo);
    num = gps_nmea_parse(nmea_str, nmea_len, &g_position.nmeaInfo);
    if(num > 0)
    {
        g_missNMEACount = 0;
    }

#if DEBUG_DISPLAY //在这里配置显示屏显示信息，方便调试
    debug_display();
#endif

    if(g_nmea_str)
    {
        if(nmea_len > MAX_BUFFER_SIZE)
        {
            nmea_len = MAX_BUFFER_SIZE;
        }

        memset(g_nmea_str, 0, MAX_BUFFER_SIZE);
        memcpy(g_nmea_str, nmea_str, nmea_len);
    }

    LOG_INFO("fix(%d) HDOP(%lf) sig(%d) inUse(%d) inView(%d) lat(%lf) lon(%lf) time(%04d-%02d-%02d %02d:%02d:%02d)",
                g_position.nmeaInfo.fix,
                g_position.nmeaInfo.HDOP,
                g_position.nmeaInfo.sig,
                g_position.nmeaInfo.satinfo.inuse,
                g_position.nmeaInfo.satinfo.inview,
                g_position.nmeaInfo.lat,
                g_position.nmeaInfo.lon,
                g_position.nmeaInfo.utc.year + 1900,
                g_position.nmeaInfo.utc.mon + 1,
                g_position.nmeaInfo.utc.day,
                g_position.nmeaInfo.utc.hour,
                g_position.nmeaInfo.utc.min,
                g_position.nmeaInfo.utc.sec
            );

//    LOG_DEBUG("%d nmea numbers has been caculated.", num);
    if((u32)rtc_getTimestamp() < 1546272000 && g_position.nmeaInfo.utc.year != 0) //2019-01-01 00:00:00
    {
        rtc_updateUTC(g_position.nmeaInfo.utc.year + 1900,
                        g_position.nmeaInfo.utc.mon + 1,
                        g_position.nmeaInfo.utc.day,
                        g_position.nmeaInfo.utc.hour,
                        g_position.nmeaInfo.utc.min,
                        g_position.nmeaInfo.utc.sec);
        LOG_DEBUG("[GPS] Calibration time C1");
        data_getData()->lastSyncTimestamp = (u32)rtc_getTimestamp();
    }

    if(g_position.nmeaInfo.fix <= NMEA_FIX_BAD
    || g_position.nmeaInfo.satinfo.inuse < 3
    || (g_position.nmeaInfo.lat < 0.0001 && g_position.nmeaInfo.lat > -0.0001)
    || (g_position.nmeaInfo.lon < 0.0001 && g_position.nmeaInfo.lon > -0.0001))
    {
        //如果当前没有定位认为在围栏范围内
        data_getData()->isOutOfPoly = L_FALSE;
        if(setting.settingConf.isFenceEnable && !setting.settingConf.isIgnoreFence)
        {
            if(setting.statusConf.acc)
            {
                if(!car_isAccOn() && car_isPowerExistence())
                {
                    car_accOn();
                    car_unlockBackWheel();  //后轮锁打开
                }
            }
        }
        diag_GNSSState(L_FALSE);
        LOG_DEBUG("GPS is not fix now.");
    }
    else
    {
        /* 临时变量 用来存储更优的GPS数据 */
        static int inuse_tmp = 0;
        static double HDOP_tmp = 99;
        static struct utc_time_t ltm = {0};
        u32 rtcTime = (u32)rtc_getTimestamp();
        static uint32_t time = 0;

        DATA *pData = data_getData();

        u32 gpsTime = 0;
        static u32 lastRtcTime = 0, lastGpsTime = 0;

        /* 如果上次上传了GPS 那么刷新GPS筛选条件 */
        if(data_getData()->isNewGPS)
        {
            inuse_tmp = 0;
            HDOP_tmp = 99;
            data_getData()->isNewGPS = L_FALSE;
        }

        if(time++ % 60 == 0)
        {
            ltm.year = g_position.nmeaInfo.utc.year + 1900;
            ltm.month = g_position.nmeaInfo.utc.mon ;  //解析里已经减过1了
            ltm.day = g_position.nmeaInfo.utc.day - 1;
            ltm.hour = g_position.nmeaInfo.utc.hour;
            ltm.minutes = g_position.nmeaInfo.utc.min;
            ltm.seconds = g_position.nmeaInfo.utc.sec;
            gpsTime = (u32)convert_utc_secs(&ltm);

            //如果没有记录上次时间且与上次网络授时间隔小于2，或者认为gps时间没问题（gps时间间隔与rtc时间间隔相差小于2），则利用gps时间来更新rtc
            if(((lastRtcTime == 0 && abs(rtcTime - gpsTime) < 2) || abs((rtcTime - lastRtcTime) - (gpsTime - lastGpsTime)) < 2))
            {
                rtc_updateTimestamp(gpsTime);
                data_getData()->lastSyncTimestamp = rtcTime;
                LOG_DEBUG("[GPS] Calibration time C2");
            }
            lastRtcTime = rtcTime;
            lastGpsTime = gpsTime;
        }
        g_position.timestamp = (u32)rtc_getTimestamp(); //更新授时后，更新定位时间戳

        g_position.isGPS = L_TRUE;
        diag_GNSSState(L_TRUE);

        /* 动飘静飘过滤 */
        if(gps_DynStafilter() == L_TRUE) //需要用实时g_position.timestamp
        {
            data_getData()->gps_parseFilter++;
            LOG_ERROR("[GPS] NEMA Filtered");
            return -1;
        }

        /* 如果定位卫星数量多选择多的 如果卫星数量一致 选择HDOP更低的 */
        if(setting.settingConf.gpsType == GPS_UBLOX_M8U //M8U产品暂时不用此过滤逻辑
        || g_position.nmeaInfo.HDOP < 1.5 
        || g_position.nmeaInfo.satinfo.inuse > inuse_tmp 
        || (g_position.nmeaInfo.satinfo.inuse == inuse_tmp && g_position.nmeaInfo.HDOP < HDOP_tmp))
        {
            ST_GPS_POINTS_FIX temp_position = {0};
            HDOP_tmp = g_position.nmeaInfo.HDOP;
            inuse_tmp = g_position.nmeaInfo.satinfo.inuse;
            temp_position.lat = g_position.nmeaInfo.lat;
            temp_position.lng = g_position.nmeaInfo.lon;
            temp_position.timeStamp = g_position.timestamp;
            gps_filterProc(!setting.statusConf.isDefend, &temp_position);
            g_position.nmeaInfo.lat = temp_position.lat;
            g_position.nmeaInfo.lon = temp_position.lng;
            g_position.timestamp = rtcTime;//恢复实时时间戳

            //更新周期内最好的定位，以便cmd_status_v6上报
            if(g_position.tagTimestamp == 0 || data_getData()->lastPosition.tagTimestamp == 0
            || g_position.nmeaInfo.satinfo.inuse > g_position.tagNmeaInfo.satinfo.inuse
            || (g_position.nmeaInfo.satinfo.inuse == g_position.tagNmeaInfo.satinfo.inuse
                &&  g_position.nmeaInfo.HDOP < g_position.tagNmeaInfo.HDOP))
            {
                g_position.tagTimestamp = g_position.timestamp;
                memcpy(&g_position.tagNmeaInfo, &g_position.nmeaInfo, sizeof(nmeaINFO));
            }
            data_savePosition(&g_position);
            gps_setRevGpsMsg(L_TRUE);
            //总里程计算逻辑 如果是非设防状态 计算总里程
            if(!setting_isDefendOn())
            {
                LOG_DEBUG("lastMileLat = %d, lastMileLon = %d\n", setting.statusConf.lastMileLat, setting.statusConf.lastMileLon);
                if((setting.statusConf.lastMileLat == 0 && setting.statusConf.lastMileLon == 0 ))
                {
                    //如果上次没有位置 记录这次位置
                    setting.statusConf.lastMileLat = (int32_t)(nmea_ndeg2degree(g_position.nmeaInfo.lat) * 1000000.f + 0.5);
                    setting.statusConf.lastMileLon = (int32_t)(nmea_ndeg2degree(g_position.nmeaInfo.lon) * 1000000.f + 0.5);
                    statusConf_save();
                }
                else
                {
                    pData->iMiles = (uint32_t)(0.5 + getdistance(nmea_ndeg2degree(g_position.nmeaInfo.lat),
                                                nmea_ndeg2degree(g_position.nmeaInfo.lon),
                                                setting.statusConf.lastMileLat / 1000000.f,
                                                setting.statusConf.lastMileLon / 1000000.f));

                    //如果是刚重启的 并且距离差距不是很大(22公里/小时 1分钟的距离) 判定是正常轨迹 记录里程
                    //如果上次位置和当前位置差距MAX_IGPSMILES米以上 但不是很离谱(小于60) 记录里程
                    if((isFirstMilesPoint && pData->iMiles < 350)
                    || (pData->iMiles > MAX_IGPSMILES && pData->iMiles < 60))
                    {
                        setting.statusConf.totalMiles += (int)(pData->iMiles + 0.5);
                        setting.statusConf.lastMileLat = (int32_t)(nmea_ndeg2degree(g_position.nmeaInfo.lat) * 1000000.f + 0.5);
                        setting.statusConf.lastMileLon = (int32_t)(nmea_ndeg2degree(g_position.nmeaInfo.lon) * 1000000.f + 0.5);
                        statusConf_save();

                        pData->iMiles = 0;//里程已经记录 清掉
                        outrageousCount = 0;//里程已经记录 离谱GPS距离状态清掉
                        isFirstMilesPoint = 0;//重启里程已经记录 干掉
                    }
                    else if(pData->iMiles >= 60)
                    {
                        //如果上次位置和当前维持差距60米以上(1秒 很离谱) 特殊处理一下
                        if(outrageousCount++ >= 5)//连续5秒定位都很离谱 说明是之前的定位飘了 现在的定位是OK的 记录新的定位
                        {
                            setting.statusConf.totalMiles += (int)(pData->iMiles + 0.5);
                            setting.statusConf.lastMileLat = (int32_t)(nmea_ndeg2degree(g_position.nmeaInfo.lat) * 1000000.f + 0.5);
                            setting.statusConf.lastMileLon = (int32_t)(nmea_ndeg2degree(g_position.nmeaInfo.lon) * 1000000.f + 0.5);
                            statusConf_save();

                            pData->iMiles = 0;//里程已经记录 清掉
                            outrageousCount = 0;//里程已经记录 离谱GPS距离状态清掉
                        }
                    }
                    else
                    {
                        //如果小于MAX_IGPSMILES米 等达到MAX_IGPSMILES米再做里程记录 这里不做处理
                    }
                }
            }
        }

        if(setting.settingConf.isFenceEnable && !setting.settingConf.isIgnoreFence && fence_checkData(pData->fence))
        {
            data_getData()->fenceAreaType = fence_isPointInServicePolygon(pData->fence, nmea_ndeg2degree(g_position.nmeaInfo.lat),
                                            nmea_ndeg2degree(g_position.nmeaInfo.lon));
            LOG_DEBUG("data_getData()->fenceAreaType = %d", data_getData()->fenceAreaType);
            if(setting.statusConf.acc)
            {
                if(data_getData()->fenceAreaType == RIDING_AREA) //骑行区
                {
                    pData->isOutOfPoly = L_FALSE;
                }
                else if(data_getData()->fenceAreaType == ALARM_AREA) //服务区内，告警区外
                {
                    pData->isOutOfPoly = L_FALSE;
                    playCount++;
                    if(playCount >= AUDIO_PLAY_PERIOD) //如果是开电门状态，15S播放一次提示音
                    {
                        playCount = 0;
                        audio_play(AUDIO_IN_WARNING_AREA);
                    }
                }
                else if(data_getData()->fenceAreaType == OUTSERVICE_AREA)
                {
                    if(car_isAccOn()) //服务区外，主动关电门
                    {
                        setting_setAcc(L_FALSE);
                    }
                    pData->isOutOfPoly = L_TRUE;
                }
                else if(data_getData()->fenceAreaType == ERROR_AREA) //当前位置相对于围栏的位置获取失败
                {
                    pData->isOutOfPoly = L_FALSE;
                    setting.settingConf.isFenceEnable = 0;
                    LOG_ERROR("fence area get error.");
                    return -1;
                }
            }

            if (lastIsInServiceArea != data_getData()->fenceAreaType)
            {
                char ret = judgeWarningType(lastIsInServiceArea, data_getData()->fenceAreaType);
                switch (ret)
                {
                    case TYPE_OUT_WARNING_FENCE: //出告警区围栏
                    {
                        userMsg_setEvent(EVENT_ALARM, ALARM_OUT_WARNING_FENCE);
                    }
                    break;

                    case TYPE_IN_WARNING_FENCE: //进入告警区围栏
                    {
                        userMsg_setEvent(EVENT_ALARM, ALARM_IN_WARNING_FENCE);
                    }
                    break;

                    case TYPE_OUT_SERVER_FENCE: //出服务区围栏
                    {
                        if (car_isAccOn())
                        {
                            setting_setAcc(L_FALSE);
                        }
                        userMsg_setEvent(EVENT_ALARM, ALARM_FENCE_OUT);
                    }
                    break;

                    case TYPE_IN_SERVER_FENCE: //进入服务区围栏
                    {
                        if (!car_isAccOn() && car_isPowerExistence())
                        {
                            setting_setAcc(L_TRUE);
                        }
                        userMsg_setEvent(EVENT_ALARM, ALARM_FENCE_IN);
                    }
                    break;

                    default:
                        break;
                }

                lastIsInServiceArea = data_getData()->fenceAreaType;
            }
        }
        else
        {
            lastIsInServiceArea = -1;
        }
    }

    return 0;
}

static int gps_RcvHandle(u8 *data, u16 length)
{
    Ublox_isPollACK(data, length); //查找UBX消息并处理
	
    if(!g_nmea_raw_str)
    {
        g_nmea_raw_str = Malloc(MAX_BUFFER_SIZE);
    }
    if(g_nmea_raw_str)
    {
        if(length > MAX_BUFFER_SIZE)
        {
            length = MAX_BUFFER_SIZE;
        }
        memset(g_nmea_raw_str, 0, MAX_BUFFER_SIZE);
        memcpy(g_nmea_raw_str, data, length);

        g_nmea_raw_len = length;
        data_getData()->gpsPortData = L_TRUE; //收到GPS数据标志位置1 休眠相关
        timer_start(TIEMR_GPS_UART, TIMER_MS, 10, gps_parse);//从串口中断转移到定时器线程
    }
    return 0;
}

void gps_getCLBS(AT_CB_PROC fun)
{
    at_run("AT+GTGIS=6\r",fun);
}

ATResult_enum gps_getCLBS_proc(uint8_t isTimeout,char *buf, u16 len)
{
    int rc = 0;
    double lat, lon;
    if(isTimeout)
    {
        return AT_RES_FINISHED;
    }
    u8 *pos = (u8 *)string_bypass((const char *)buf, "GTGIS:\"");
    if(strstr((const char *)buf, "ERROR") || strstr((const char *)buf, "OK")||(!pos))
    {
        if(strstr((const char *)buf, "ERROR"))
        {
            return AT_RES_FINISHED;
        }
        if(!pos)
        {
            return AT_RES_CONTRINUE;
        }
    }
    rc = sscanf((char *)pos, "%lf,%lf%*s", &lon, &lat);
    LOG_DEBUG("rc:%d lon:%lf lat:%lf", rc, lon, lat);
    if(rc == 2)
    {
        g_position.isCLBS = L_TRUE;
        g_position.lbsTimestamp = (u32)rtc_getTimestamp();
        g_position.lbsInfo.lat = nmea_degree2ndeg(lat);
        g_position.lbsInfo.lon = nmea_degree2ndeg(lon);
        data_savePosition(&g_position);
    }
    return AT_RES_FINISHED;
}

void gps_uart_send(void *msg, unsigned short length)
{
    fibo_hal_uart_put(UART_GPS, (unsigned char *)msg, length);
    LOG_DEBUG("send gps uart:");
    LOG_BIN(msg, length);
}

void gps_initial(void)
{
    if(setting.settingConf.gpsType == GPS_UBLOX_M8U && setting.settingConf.accleType == ACCLE_LIS3DH)
    {
        Ublox_M8U_config(); //配置M8U
        fibo_taskSleep(50);
        timer_startRepeat(TIMER_HNR_CAL, TIMER_MS, 250, Ublox_M8U_cal_hnr);
        timer_startRepeat(TIMER_UBLOX_RESET, TIMER_S, 2, Ublox_M8U_reset_state);
        timer_startRepeat(TIMER_M8U_CHECK, TIMER_S, 1, Ublox_M8U_state_handle);
    }
    else if(setting.settingConf.gpsType == GPS_ALLYSTAR_8040)
    {

    }
    else if(setting.settingConf.gpsType == GPS_UBLOX_8130 || setting.settingConf.gpsType == GPS_UBLOX_7020)
    {
        Ublox_init(gps_uart_send); //69版本以后需动态识别8130或7020
    }
    else if(setting.settingConf.gpsType == GPS_UBLOX_M8U && setting.settingConf.accleType == ACCLE_MPU6500)
    {
        Ublox_M8U_baudrate_handle(gps_uart_send);
    }

    if(setting.settingConf.gpsType == GPS_UBLOX_M8U || setting.settingConf.gpsType == GPS_UBLOX_8130
        || setting.settingConf.gpsType == GPS_UBLOX_7020)
    {
        agps_initail();
        gps_nmeaOutputEnable(L_TRUE);
        timer_startRepeat(TIMER_GPS_LOOP, TIMER_S, 1, gps_powerManagerByModeHandler); //暂存
    }
    if(!g_nmea_str) g_nmea_str = (uint8_t*)Malloc(MAX_BUFFER_SIZE);
    uart_registerHandler(UART_GPS, gps_RcvHandle);
}

float gps_getGPSValue(double val)
{
    float out = 0.0f;
    double deg = ((int)(val / 100));
    out = deg + (val - deg * 100) / 60;
    return out;
}

u32 gps_getGPSU32(double val)
{
    float out = gps_getGPSValue(val);
    return (u32)(out * 1000000); //取小数点后六位
}

static int gps_rstGpsCB(void)
{
    fibo_gpio_set(PIN_GNSSRTS_DRIVER, GPIO_LEVEL_LOW);
    return 0;
}

void gps_moudleReset(void)
{
    fibo_gpio_set(PIN_GNSSRTS_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_UBLOX_RESET, TIMER_MS, 500, gps_rstGpsCB);
}

static L_BOOL isRevGpsData = L_FALSE;
u8 gps_isRevGPSMsg(void)
{
    return isRevGpsData;
}

void gps_setRevGpsMsg(u8 isRevGpsMsg)
{
    isRevGpsData = isRevGpsMsg;
}

int gps_setNmeaStr(u8 *pNmea, int size)
{
    //TODO 屏蔽gps解析
    int len = MAX_BUFFER_SIZE;
    if(size < len)
    {
        len = size;
    }

    memset(g_nmea_raw_str, 0, MAX_BUFFER_SIZE);
    memcpy(g_nmea_raw_str, pNmea, len);
    return 0;
}

