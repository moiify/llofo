#ifndef __USER_BLE_SCAN_PROC_H__
#define __USER_BLE_SCAN_PROC_H__
#include <stdio.h>
#include <stdbool.h> 
#include <stdint.h>

#include "setting.h"
#include "protocol.h"

typedef struct {
    uint8_t        evt_type;
    ///Advertising address type: public/random
    uint8_t        adv_addr_type;
    ///Advertising address value
    struct bd_addr adv_addr;
    ///Data length in advertising packet
    uint8_t        data_len;
    ///Data of advertising packet
    uint8_t        data[ADV_DATA_LEN];
    ///RSSI value for advertising packet
    uint8_t        rssi;
}ST_SCAN_INFO;

typedef struct
{
    uint8_t type;
    uint8_t dataLen;
    char *data;
}__attribute__((__packed__))ST_BLE_SCAN_DATA_FEATURE;

typedef struct
{
    char *name;
    uint8_t nameLen;
    char *manufacture;
    uint8_t manufactureLen;
}__attribute__((__packed__))ST_BLE_SCAN_RESULT;

typedef struct
{
    uint8_t tBeaconSignalStr[2];
    uint8_t tBeaconIDStr[12];              // TBEACON_ID_LEN = 12
    uint8_t tBeaconNumStr;                 
    uint8_t tBeaconPileNumStr;                 
    uint8_t tBeaconSignalThresholdStr[2];      
    uint8_t tBeaconSOCStr[2];                  
    uint8_t tBeaconVersionStr[2];              
}__attribute__((__packed__))TBEACON_INFO_STR;

typedef struct
{
    uint8_t manufCode[2];
    uint8_t version[2];
    uint8_t state;
    uint8_t voltage;
    uint8_t info[7];
    uint8_t merchantNum[2];
    uint8_t manufTime[3];
    uint8_t type;
    uint8_t temperature;
    uint8_t name[4];
}__attribute__((__packed__))ST_BLE_MANUF_DATA;

typedef enum
{
    BEACON_NONE = 0, //未扫描到道钉
    BEACON_WY = 1,   //浩源道钉
    BEACON_JT = 2,   //金通道钉
    BEACON_JJ = 3,   //金桔道钉
}BEACON_TYPE;


beaconStatus_t *ble_getBeaconStatus(void);



void ble_scan_cb(ST_SCAN_INFO *param);
int ble_scan_timeout_callback(void);

#endif/*__USER_BEACON_H__*/
