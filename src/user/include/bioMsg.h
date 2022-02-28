/*
 * bioMsg.h
 *
 *  Created on: 2018.08.21
 *      Author: lc
 */

#ifndef __BIO_MSG_H__
#define __BIO_MSG_H__

#include "types.h"
#include "da14580.h"

#define BD_ADDR_LEN         6
#define ADV_DATA_LEN        0x1F

typedef int (*SACNTBEACON_RESULT_CB)(void);

typedef enum
{
    CMD_BIO_SET_CFG         			= 0x00,
    CMD_BIO_WRITE_OUTPUT    			= 0x01,
    CMD_BIO_READ_INPUT      			= 0x02,
    CMD_BIO_SET_NAME        			= 0x03,    
    CMD_BIO_PING            			= 0x04,
    CMD_BIO_REBOOT                      = 0x05,
    CMD_BIO_SET_CONFIG      			= 0x0b,
    CMD_BIO_VERSION         			= 0x0E,
    CMD_BIO_GET_KEY         			= 0x10,
    CMD_BIO_NOTIFY          			= 0x11,
    CMD_BIO_SET_BEATHEART   			= 0x12,//开关蓝牙心跳
    
    CMD_BIO_LOG             			= 0x18,
    CMD_BIO_LOG_HEX         			= 0x19,
    CMD_BIO_START_SCAN_TBEACON          = 0x14,//开始扫描道钉
    CMD_BIO_ADC             			= 0x1A,
    CMD_BIO_DISCONNECT_REQ  			= 0x1B,
	CMD_TBEACONSCAN_RESULT              = 0X1C,//道钉扫描结果
	CMD_BIO_RST_MCU             		= 0x1D,//蓝牙硬件复位MCU
	CMD_BIO_SET_PIN_LEVEL   			= 0x1E,//控制蓝牙升降压

    CMD_BIO_GET_BOOTSTATUS              = 0x3C,//获取蓝牙boot下载状态
	CMD_BIO_NETWATCHDOG    			    = 0x3D,//网络状态看门狗
} CMD_BIO;

#pragma pack(push, 1)

typedef struct
{
    uint8_t name[15];
    uint8_t imei[15];
}__attribute__((__packed__))BIO_BLE_SETNAME;

typedef struct
{
    uint8_t notify;
}__attribute__((__packed__))BIO_BLE_NOTIFY;

typedef struct
{
    uint8_t sw;
    uint8_t name[15];
    uint8_t imei[15];
    uint8_t token[4];
}__attribute__((__packed__))  BIO_BLE_CONFIG;

typedef struct {
    uint32_t version;
}__attribute__((__packed__))BIO_VERSION_NUM;

typedef struct{
    uint8_t channel;
    float volMv;
}__attribute__((__packed__))ST_BIO_ADC;

typedef struct{
    uint8_t adv[ADV_DATA_LEN];       //道钉广播内容
    uint8_t mac[BD_ADDR_LEN];        //道钉MAC地址
    uint8_t dbm;                     //信号强度 单位: dBm
}__attribute__((__packed__))ST_BEACON_INFO;

typedef struct{
    uint8_t state;
    ST_BEACON_INFO highestInfoNSecondsAgo[5]; //倒数N秒的最强信号道钉信息
}__attribute__((__packed__))ST_BEACON_STTAUS;

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

#pragma pack(pop)

#define SW_IS_ADV        (0x01 << 0)    // bit 1:蓝牙处于广播模式 0:蓝牙处于扫描模式

#define SW_IS_PKEKEY     (0x01 << 2)    // if !SW_IS_ADV && SW_IS_PKEKEY 车机支持PKE 并且扫描钥匙
#define SW_IS_PKEPHONE   (0x01 << 3)    // if SW_IS_ADV && SW_IS_PKEPHONE 车机支持PKE 并且被手机扫描

int bioMsg_msgProc(uint8_t *data, uint16_t dataLen);

int bioMsg_setBLEConfig(void);
int bioMsg_setBleName(void *m);

int bio_getAdcFromDa14580(unsigned char channel);
void bioMsg_startScanTBeacon(u8 *data, u8 dataLen);
int bioMsg_setScanTBeaconResult_cb(SACNTBEACON_RESULT_CB scanSuccessful, SACNTBEACON_RESULT_CB scanFail);
void bioMsg_getBootDownStatus(void);

#endif //__BIO_MSG_H__

