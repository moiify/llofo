#ifndef __USER_SETTING_H__
#define __USER_SETTING_H__

#include <stdio.h>
#include <stdbool.h> 
#include <stdint.h>
#include "co_bt.h"

#include "app_user_config.h"

#define BLE_TYPE_16UUID         0x02
#define BLE_TYPE_128UUID        0x07
#define BLE_TYPE_NAME           0x09
#define BLE_TYPE_MANUFACTURE    0xFF

#define BLE_ADDRESS_LEN         6

#define MAX_KEY_NUM             5
#define PKE_TM_ID_LEN           2
#define PKE_KEY_ID_LEN          6

//adv
#define MAX_BLE_ADV_NAME_LEN            (15)
#define MAX_BLE_ADV_MEANUFDATA_LEN      (15)
#define DEFAULT_ADV_INTV                MS_TO_BLESLOTS(100) //100ms

//scan
#define MAX_SCAN_TIME                   (0)
#define MAX_BLE_SCAN_SUPPOSED_NAME_LEN  (12)
#define MAX_BLE_MANUFACTURE_DATA_LEN    (16)

#define MAX(a,b) (a>b ? a:b)
#define MIN(a,b) (a>b ? b:a)

#define htonl(l) ((((l >> 24) & 0x000000ff)) | \
                  (((l >>  8) & 0x0000ff00)) | \
                  (((l) & 0x0000ff00) <<  8) | \
                  (((l) & 0x000000ff) << 24))
#define ntohl(l) htonl(l)
#define htons(s) ((((s) >> 8) & 0xff) | \
                  (((s) << 8) & 0xff00))
#define ntohs(s) htons(s)

typedef enum
{
    BLE_MODE_ADV,
    BLE_MODE_SCAN,
    BLE_MODE_ERROR,
}ENUM_BLE_MODE;

typedef enum
{
    PKE_CMD_PKE         = 0x00,
    PKE_CMD_DEFEND      = 0x01,
    PKE_CMD_FINDME      = 0x02,
    PKE_CMD_UNLOCK      = 0x03,
}ENUM_PKEKEY_CMD;

typedef enum
{
    //pke
    PKE_VALUE_PKE         = 0x00,
    //defend
    PKE_VALUE_DEFEND_OFF  = 0x00,
    PKE_VALUE_DEFEND_ON   = 0x01,
    //find car
    PKE_VALUE_FINDME      = 0x00,
    //start adv
    PKE_VALUE_UNLOCK      = 0x01,
    
}ENUM_PKEKEY_VALUE;

   
typedef enum
{
    BLE_SUCCESS,    
    BLE_FAILED,
}ENUM_BLE_RETURN;


typedef struct {
    uint8_t name[MAX_BLE_ADV_NAME_LEN];
    uint8_t nameLen;
    uint8_t meanufData[MAX_BLE_ADV_MEANUFDATA_LEN];   //0xFF字段信息
    uint8_t meanufDataLen;
}ST_BLE_ADV;

typedef uint8_t ST_PKE_KEYID[PKE_KEY_ID_LEN];

typedef struct
{
    uint8_t tmId[PKE_TM_ID_LEN];    //公司名
    uint8_t keyId[PKE_KEY_ID_LEN];  //钥匙ID
    uint8_t cmd;                    
    uint8_t value;
}ST_BLE_SCAN_PKE_MANUFACTURE_DATA;

typedef struct {
    uint8_t supposedName[MAX_BLE_SCAN_SUPPOSED_NAME_LEN + 1];   //蓝牙钥匙名称（未用到）
    ST_PKE_KEYID cfgedKeyID[MAX_KEY_NUM];                       //蓝牙钥匙配置信息
    uint8_t keyNum;                                             //蓝牙钥匙数量
    ST_BLE_SCAN_PKE_MANUFACTURE_DATA key;                       //最近一次扫描到的钥匙
}ST_BLE_SCAN;    

typedef struct{
	uint8_t ScanFailCount;
	uint8_t isGetTBeacon;
	uint8_t savedatablock;
    ENUM_BLE_MODE mode;                 //蓝牙所处的状态
    ST_BLE_ADV adv;
    ST_BLE_SCAN scan;
    uint8_t address[BLE_ADDRESS_LEN];   //本地蓝牙设备地址
    uint8_t isHeartBeatOn;
	uint8_t isconnected;
    uint8_t protocol_type;              // 0: 小安协议 ; 1: 小遛协议 ; 
    uint8_t noscanbestTbeacon;
    uint8_t beaconRssi; //道钉阈值
    uint8_t lastbeaconRssi;
    uint8_t updateBeaconRssi;
    uint8_t isPKEType;
}ST_BLE_STATE;

extern ST_BLE_STATE setting;

ENUM_BLE_MODE setting_getMode(void);
ENUM_BLE_RETURN setting_isParamConfiged(void);

void setting_set_address(const uint8_t * address);
void setting_set_address_from_imei(uint8_t *imei);

#endif/*__USER_SETTING_H__*/

