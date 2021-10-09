/*
 * bleMsg.h
 *
 *  Created on: 2018.08.21
 *      Author: lc
 */

#ifndef __BLE_MSG_H__
#define __BLE_MSG_H__

#include "types.h"
#include "protocol.h"

#define MAX_BLE_MSG_LEN 52 //超过该长度则会校验不通过

typedef enum
{
    CMD_BLE_WILD                = 0x00, //蓝牙透传命令     
    CMD_BLE_SET_DEFEND          = 0x20, //蓝牙设置启动和设防
    CMD_BLE_GET_STATUS          = 0x21, //蓝牙获取状态值
    CMD_BLE_SET_SERVER          = 0x22, //蓝牙更改服务器地址
    CMD_BLE_SET_SADDLE          = 0X24, //蓝牙设置后座锁
    CMD_BLE_SET_BACKWHEEL       = 0x25, //蓝牙设置后轮锁
    CMD_BLE_REBOOT              = 0x26, //蓝牙控制重启
    CMD_BLE_SET_ACC             = 0x27, //蓝牙控制电门
    CMD_BLE_AUDIO               = 0x28, //蓝牙播放语音
    CMD_BLE_PKE                 = 0x29, //蓝牙进入PKE
    CMD_BLE_GET_STATUS_V2       = 0x2A,
    CMD_BLE_SET_DEFENDON        = 0x2B,
    CMD_BLE_SET_ACCON           = 0x2C,
    CMD_BLE_SET_ACCOFF          = 0x2D, //蓝牙熄火
    CMD_BLE_UNLOCK_WHEEL        = 0x2E,
    CMD_BLE_LOCK_WHEEL          = 0x2F,
    CMD_BLE_SHUTDOWN            = 0x30, //蓝牙控制关机
    CMD_BLE_PKEOFF              = 0x31, //蓝牙退出PKE
    CMD_BLE_GET_GPS             = 0x32, //蓝牙获取状态信息 包含GPS
    CMD_BLE_GET_CARD_INFO       = 0x33, //蓝牙获取sim卡信息
    CMD_BLE_UNLOCK_SADDLE       = 0x34,
    CMD_BLE_LOCK_SADDLE         = 0x35,
    CMD_BLE_GET_CCID            = 0x3d,
    CMD_BLE_SET_APN             = 0x3e,

    CMD_BLE_GET_NET_STATE       = 0x3f,
    CMD_BLE_SET_DEEP_SLEEP      = 0x40,
    CMD_BLE_GET_STATUS_V3       = 0x41,
    CMD_BLE_GET_TBEACON_INFO  	= 0x42,//获取最后一次道钉信息
    CMD_BLE_SET_HELMET          = 0x43,//操作头盔锁
	CMD_BLE_SET_DEFEND_TBEACON  = 0x44,//带道钉设防
    CMD_BLE_SET_ACC_TBEACON     = 0x45,//带道钉撤防
    CMD_BLE_GET_DIAGNOSIS       = 0x47, //蓝牙获取动态诊断信息
	CMD_BLE_SET_WORKMODE 		= 0x48, //控制蓝牙工作模式(0 正常 1透传)
    CMD_BLE_SET_DEFENDON_TYPE   = 0x52, //蓝牙设防车辆（指定类型）
    CMD_BLE_GET_RFID_INFO       = 0x54, //查询RFID信息
    CMD_BLE_CHNAGE_SERVER       = 0xff,
} CMD_BLE;

typedef enum
{
    CODE_SUCCESS          = 0,
    CODE_ERROR_TOKEN      = 1,
    CODE_ERROR_CONTENT    = 2,
    CODE_ERROR_CMD        = 3,
    CODE_ERROR_OPREATION  = 4,
    CODE_ERROR_UNSUPPORT  = 5,
    CODE_ERROR_NOTSTOP    = 6,
    CODE_ERROR_ACCESSDENY = 7,
    CODE_ERROR_KICK_ERROR = 8,
    CODE_ERROR_CONTINUALLY= 9,
} BLE_RESPONSE_CODE;

#pragma pack(push, 1)

typedef struct
{    
    uint32_t token;
    uint8_t data[];
}__attribute__((__packed__)) BLE_MSG_DATA;

typedef struct
{    
    uint8_t mode;
    uint8_t gsm;
    uint8_t sw;
    uint32_t volatge_mV;
}__attribute__((__packed__)) BLE_STATUS_MSG;

typedef struct
{    
    GPS gps;
}__attribute__((__packed__)) DA14580_GPS_MSG;

#define BLE_SW_MASK_DEFEND  (1 << 0)
#define BLE_SW_MASK_ACC     (1 << 1)
#define BLE_SW_MASK_WHEEL   (1 << 2)
#define BLE_SW_MASK_SEAT    (1 << 3)
#define BLE_SW_MASK_POWER   (1 << 4)
#define BLE_SW_MASK_LOGIN   (1 << 5)
#define BLE_SW_MASK_BEEP    (1 << 6)
#define BLE_SW_MASK_SILENT  (1 << 7)
#define BLE_SW_MASK_AUTOLOCKON   (1 << 8)
#define BLE_SW_MASK_OVERSPEEDON  (1 << 9)
#define BLE_SW_MASK_KEYRELATED   (1 << 10)
#define BLE_SW_MASK_HELMETREACT_V2  (1 << 11)
#define BLE_SW_MASK_WIRELOCKED_V2   (1 << 12)
#define BLE_SW_MASK_HELMETLOCKED_V2 (1 << 13)

#define BLE_SW_HELMETUNLOCK_V2    (1 << 11)

#define BLE_SW_HELMETUNLOCK       (1 << 5)

#define BLE_SW_HELMETLOCKED_4     (1 << 16)
#define BLE_SW_GSSLOCKED_V3       (1 << 17)
#define BLE_SW_HELMETREACT_6      (1 << 18) //6芯头盔锁的头盔在位信号
#define BLE_SW_HELMELOCK_6        (1 << 19) //6芯头盔锁的锁到位信号

typedef struct
{    
    uint8_t event;
    uint16_t sw;
    uint8_t gsm;
    uint8_t voltage[3];
    uint8_t version[3];
    uint8_t bleVersion[3];
}__attribute__((__packed__)) DA14580_STATUS_V2_MSG;

typedef struct
{    
    uint8_t event;
    uint32_t sw;
    uint8_t gsm;
    uint16_t voltage;
    uint8_t version[3];
    uint8_t bleVersion[3];
    uint32_t timstamp;
    int32_t lon;
    int32_t lat;
    uint8_t speed;
    uint16_t course;
    uint16_t hdop;
    uint8_t  satelites;
    uint32_t totalMiles;
}__attribute__((__packed__)) DA14580_STATUS_V3_MSG;

typedef struct
{
    uint8_t state; //当前网络状态
    uint32_t cnt; //当前网络状态持续的秒数
}__attribute__((__packed__)) BLE_NET_STATE_MSG;

#define CHECK_STATE_GSM     (1 << 0)
#define CHECK_STATE_SIM     (1 << 1)
#define CHECK_STATE_ACCEL   (1 << 2)

#define TIMER_STATE_200MS   (1 << 0)
#define TIMER_STATE_1S      (1 << 1)
#define TIMER_STATE_2M      (1 << 2)
#define TIMER_STATE_DETECT  (1 << 3)
#define TIMER_STATE_FSM     (1 << 4)
#define TIMER_STATE_WAKEUP  (1 << 5)
#define TIMER_STATE_SLEEP   (1 << 6)

#define SETTING_STATE_OVER_SPEED        (1 << 0)
#define SETTING_STATE_MOVE_ALARM        (1 << 1)
#define SETTING_STATE_NIGHT_VOICE       (1 << 2)
#define SETTING_STATE_SHAKE_ALARM       (1 << 3)
#define SETTING_STATE_TBEACON_ENABLE    (1 << 4)
#define SETTING_STATE_SLEEP_ENABLE      (1 << 5)
#define SETTING_STATE_AUTOLOCK          (1 << 6) 
#define SETTING_STATE_TRANSFORM         (1 << 7)

typedef enum
{
    TYPE_CHECK_STATE            = 0,
    TYPE_TIMER_STATE            = 1,
    TYPE_SETTING_STATE          = 2,

    TYPE_FSM_STATE              = 3,
    TYPE_FSM_CNT                = 4,

    TYPE_CONN_SUCCESS           = 5,
    TYPE_CONN_FAIL              = 6,
    TYPE_CONN_CLOSE             = 7,
    TYPE_PKTS_SENT              = 8,
    TYPE_PKTS_ACKED             = 9,
    TYPE_BYTES_SENT             = 10,
    TYPE_BYTES_ACKED            = 11,

    TYPE_SERVER                 = 12,
    TYPE_BLE_NAME               = 13,
    TYPE_BLE_TOKEN              = 14,
    TYPE_GPS_PERIOD             = 15,
    TYPE_FREQ_NORM              = 16,
    TYPE_FREQ_MOVE              = 17,
    TYPE_REBOOT_CNT             = 18,
    TYPE_ACCON_CNT              = 19,
    TYPE_PWRCUT_CNT             = 20,
    TYPE_AUTOLOCK_PERIOD        = 21,
    TYPE_PROTECT_VOLTAGE        = 22,
    TYPE_RESTORE_VOLTAGE        = 23,

    TYPE_SADDLE_TYPE            = 24,
    TYPE_CCU_TYPE               = 25,
    TYPE_BMS_TYPE               = 26,
    TYPE_HELMET_TYPE            = 27,
    TYPE_BACKWHEEL_TYPE         = 28,

    TYPE_ETC_VOLTAGE            = 29, //控制器电压
    TYPE_ETC_CURRENT            = 30, //控制器电流
    TYPE_ETC_PRO_VER            = 31, //控制器协议版本号
    TYPE_ETC_HALL               = 32, //控制器hall值
    TYPE_ETC_FAULT              = 33, //控制器错误标志
    TYPE_BMS_VOLTAGE            = 34, //BMS电压
    TYPE_BMS_CURRENT            = 35, //BMS电流
    TYPE_BMS_SOC                = 36, //BMSSOC
} DIAG_TYPE; //不大于255，为了应对设备不联网的情况下用蓝牙进行功能诊断

typedef struct
{
    uint8_t type;
    uint8_t len;
    uint8_t val[];
}__attribute__((__packed__)) DIAG_MSG;

typedef struct
{
    uint8_t cnt;
    DIAG_MSG diag[];
}__attribute__((__packed__)) BLE_DIAG_MSG;

typedef struct
{
    uint8_t errCode;
    uint8_t type;
    uint8_t payload[];
}BLE_RESPONSE_WITHTYPE;

#define BLE_RESPONSE_LEN sizeof(BLE_RESPONSE_WITHTYPE)

typedef struct
{
    uint8_t result; //RFID查询结果
    uint8_t version[3]; //RFID读卡器固件版本号
    uint8_t cardID[16]; //标签卡号
}__attribute__((__packed__)) BLE_RFID_STATE_MSG;

#pragma pack(pop)

int bleMsg_msgProc(uint8_t *data, uint16_t dataLen);
uint8_t bleMsg_isSetDefending(void);

#endif //__BLE_MSG_H__
