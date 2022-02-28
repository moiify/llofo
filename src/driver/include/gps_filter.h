/*
 * gps_filter.h
 *
 *  Created on: 2017/03/24
 *      Author: lc
 */
#ifndef __USER_GPS_FILTER_H__
#define __USER_GPS_FILTER_H__
#include "fibo_opencpu.h"

#include "nmea/info.h"

#define GPS_FIX_CACHE_DEEP_MAX 10

typedef struct{
    double lng;
    double lat;
    unsigned int timeStamp;
} ST_GPS_POINTS_FIX;


void gps_filterProc(uint8_t isMoving, ST_GPS_POINTS_FIX *position);

#endif//__USER_GPS_FILTER_H__
