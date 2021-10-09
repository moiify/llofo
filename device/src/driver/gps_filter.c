
#include "nmea/gmath.h"

#include "utils.h"
#include "gps_filter.h"

typedef struct{
    ST_GPS_POINTS_FIX points[GPS_FIX_CACHE_DEEP_MAX];
    int index;  //最新定位点的index points[index] is the last point
    int deep;   //最大深度 deep <= GPS_FIX_CACHE_DEEP_MAX
    int cap;    //内部实施容量
}ST_GPS_FIX_CACHE;


static float GPS_SPEED_MAX = 130.0f;//uint km/h
static ST_GPS_FIX_CACHE gpsFixCacheInst;

// 根据当前深度 取平均标准点
int gps_pointCache_getStand(ST_GPS_FIX_CACHE *gpsFixCache, ST_GPS_POINTS_FIX *gpsPointStand)
{
    int i = 0;
    uint64_t timeStand = 0;
    double latStand = 0.0;
    double lngStand = 0.0;
    int deep = gpsFixCache->cap;

    for(i = 0; i < deep; i++)
    {
        int j = (gpsFixCache->index - i + GPS_FIX_CACHE_DEEP_MAX) % GPS_FIX_CACHE_DEEP_MAX;
        latStand += gpsFixCache->points[j].lat;
        lngStand += gpsFixCache->points[j].lng;
        timeStand += gpsFixCache->points[j].timeStamp;
    }

    if(i != 0)
    {
        gpsPointStand->lat = latStand / deep;
        gpsPointStand->lng = lngStand / deep;
        gpsPointStand->timeStamp = timeStand / deep;
        return 0;
    }

    return 1;
}

//根据循环队列进行入队 并更新实时容量
int gps_pointCache_en(ST_GPS_FIX_CACHE *gpsFixCache, ST_GPS_POINTS_FIX *newPoint)
{
    //获取当前index
    gpsFixCache->index = (gpsFixCache->index + 1) % GPS_FIX_CACHE_DEEP_MAX;

    //存储当前位置信息
    *(gpsFixCache->points + gpsFixCache->index) = *newPoint;

    //更新实时容量
    if(gpsFixCache->cap < gpsFixCache->deep)
    {
        gpsFixCache->cap++;
    }
    return 0;
}

//更新队列深度
int gps_pointCache_fixDeep(ST_GPS_FIX_CACHE *gpsFixCache, int deepNew)
{
    if(gpsFixCache->cap > deepNew)
    {
        // 如果Deep由深入浅,抛弃老的deep数据; 如果Deep由浅入深, 保留老的deep数据.
        gpsFixCache->cap = deepNew;
    }

    //更新deep
    gpsFixCache->deep = deepNew;
    return 0;
}

//数据入队处理  输出GPS实时定位信息
static int gps_pointFix(ST_GPS_POINTS_FIX *positionIn, ST_GPS_POINTS_FIX *positionOut)
{
    int ret = 0;
    int errCode = 0;
    static ST_GPS_POINTS_FIX pointInTemp = {0};
    static ST_GPS_POINTS_FIX gpsPointStand = {0};
    static ST_GPS_POINTS_FIX gpsPointOptimized = {0};

    float speed = 0;
    double distGap = 0;
    double timeGap = 0;

    pointInTemp.lat = positionIn->lat;
    pointInTemp.lng = positionIn->lng;
    pointInTemp.timeStamp = positionIn->timeStamp;

    if(positionIn != positionOut)
    {
        *positionOut = *positionIn;// only optimized lat and lon and will not change others
    }

    //get the standar point
    ret = gps_pointCache_getStand(&gpsFixCacheInst, &gpsPointStand);
    if(ret != 0) gpsPointStand = pointInTemp;
    //printf("stand lat=%f,lon=%f,time=%ld\r\n", gpsPointStand.lat, gpsPointStand.lng, gpsPointStand.timeStamp);

    //get diff
    distGap = getdistance(nmea_ndeg2degree(gpsPointStand.lat), nmea_ndeg2degree(gpsPointStand.lng), 
                          nmea_ndeg2degree(positionIn->lat), nmea_ndeg2degree(positionIn->lng));
    timeGap = positionIn->timeStamp - gpsPointStand.timeStamp;

    do{
        if(timeGap > 0) speed = distGap / timeGap; // m/s
        else if(0 == timeGap) speed = 2 * KMPH2MPS(GPS_SPEED_MAX); //big enough
        else
        {
            errCode = -1;
            break;
        }

        if(MPS2KMPH(speed) > GPS_SPEED_MAX)
        {
            //todo: the first point output will be 0
            if(ret != 0) gpsPointOptimized = pointInTemp;
            positionOut->lat = gpsPointOptimized.lat;
            positionOut->lng = gpsPointOptimized.lng;

            errCode = 1;
        }

    }while(0);


    //uotput must be the best point

    gpsPointOptimized.lat = positionOut->lat;
    gpsPointOptimized.lng = positionOut->lng;

    gpsPointOptimized.timeStamp = positionOut->timeStamp;


    //all points are record to fix the next points, be the stand
    gps_pointCache_en(&gpsFixCacheInst, &pointInTemp);

    return errCode;
}

void gps_filterProc(uint8_t isMoving, ST_GPS_POINTS_FIX *position)
{
    //reset gpsfix config by defend flag
    if(!isMoving)//设防
    {
        GPS_SPEED_MAX = 130.0f;//km/h
        gps_pointCache_fixDeep(&gpsFixCacheInst, 3);//1: deep 不做过滤
    }
    else         //移动
    {
        GPS_SPEED_MAX = 50.0f;
        gps_pointCache_fixDeep(&gpsFixCacheInst, 3);//3: deep
    }
    
    //gps fix
    gps_pointFix(position, position);
}

