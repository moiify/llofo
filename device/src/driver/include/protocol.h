/*
 * protocol.h
 *
 *  Created on: 2015/6/29
 *      Author: jk
 *
 *  Copyright (c) 2015 Wuhan Xiaoan Technology Co., Ltd. All rights reserved.
 *
 */

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "types.h"
#include "stdint.h"

#define DEVICE_TYPE 100

#define START_FLAG (0xAA55)
#define START_FLAG_UDP (0xA5A5)
#define MAX_IMEI_LENGTH 15
#define MAX_CCID_LENGTH 20
#define MAX_IMSI_LENGTH 15
#define MAX_CELL_NUM 7
#define TEL_NO_LENGTH 11

enum
{
    CMD_WILD            =  0,
    CMD_WILD_NEW        =  100, //仅用于新版即时后台消息
    CMD_LOGIN           =  1,
    CMD_PING            =  2,
    CMD_GPS             =  3,
    CMD_CELL            =  4,
    CMD_ALARM           =  5,
    CMD_SMS             =  6,
    CMD_433             =  7,
    CMD_DEFEND          =  8,
    CMD_SEEK            =  9,
    CMD_LOCATE          = 10,
    CMD_SET_SERVER      = 11,
    CMD_SET_TIMER       = 12,
    CMD_SET_AUTOSWITCH  = 13,
    CMD_GET_AUTOSWITCH  = 14,
    CMD_SET_PERIOD      = 15,
    CMD_GET_PERIOD      = 16,
    CMD_ITINERARY       = 17,
    CMD_BATTERY         = 18,
    CMD_DEFEND_ON       = 19,
    CMD_DEFEND_OFF      = 20,
    CMD_DEFEND_GET      = 21,
    CMD_DEFEND_NOTIFY   = 22,
    CMD_UPGRADE_START   = 23,
    CMD_UPGRADE_DATA    = 24,
    CMD_UPGRADE_END     = 25,
    CMD_SIM_INFO        = 26,
    CMD_REBOOT          = 27,
    CMD_DEVICE_INFO_GET = 28,
    CMD_GPS_PACK        = 29,
    CMD_SET_BATTERY_TYPE= 30,
    CMD_DEVICE          = 31,
    CMD_AUDIO           = 32,
    CMD_GPS_MANGO_V2    = 34,   //芒果定制的GPS上报命令
    CMD_LOGIN_NEW       = 35,
    CMD_PING_NEW        = 36,
    CMD_STATUSGPS_MGBT  = 36,   //芒果定制电池低功耗版本上报命令
    CMD_STATUSCELL_MGBT = 37,   //芒果定制电池低功耗版本上报命令
    CMD_GPS_MANGO_V3    = 38,
    CMD_PING_V2         = 39,
    CMD_GPS_V4          = 41,
    CMD_NOTIFY_ERROR    = 42,
    CMD_UPGRADE_NOTIFY  = 42,
    CMD_BMS_ETC_INFO_MG = 44,
    CMD_UPLOAD_NMEA     = 46,
    CMD_GPS_MANGO_V4    = 50,
    CMD_UPDATE_FENCE    = 51,
    CMD_NOTIFY          = 52,
    CMD_BMS_MSG         = 55,
    CMD_GPS_V5          = 56,
    CMD_STATUS_LEXING   = 57,
    CMD_BMS_MSG_V2      = 58,
    CMD_BMS_HELLO       = 59,
    CMD_LOGIN_V3        = 60,
    CMD_DIAGNOSIS_RESULT= 61,
    CMD_DIAGNOSIS_RESULT_STM= 62,
    CMD_WILD_UARTMSG    = 63,
    CMD_ND_BMS_INFORMATION  = 65,
    CMD_BMS_INFO        = 66,
    CMD_WATCHDOG_INFO   = 67,
    CMD_GPS_V6          = 68,
    CMD_FAULTINFO       = 70,
    CMD_NOTIFY_V2       = 72,
    CMD_SIMINFO         = 73,
};

enum
{
    DEVICE_GET_DEVICEINFO    = 0,
    DEVICE_GET_LOCATE        = 1,
    DEVICE_SET_AUTOLOCK      = 2,
    DEVICE_GET_AUTOLOCK      = 3,
    DEVICE_SET_DEFENDSTATE   = 4,
    DEVICE_GET_DEFENDSTATE   = 5,
    DEVICE_GET_BATTERY       = 6,
    DEVICE_SET_BATTERYTYPE   = 7,
    DEVICE_START_RECORD      = 8,
    DEVICE_STOP_RECORD       = 9,
    DEVICE_SET_BLUETOOTHID   = 10,
    DEVICE_SET_SERVER        = 11,
    DEVICE_DOWNLOAD_AUDIOFILE= 12,
    DEVICE_SET_BLUETOOTHSW   = 13,
    DEVICE_PLAY_AUDIO        = 14,
    DEVICE_CONTROL_LOCK      = 15,
    DEVICE_GET_SERVER        = 16,
    DEVICE_GET_GPS_SIGNAL    = 17,
    DEVICE_GET_GSM_SIGNAL    = 18,
    DEVICE_AT                = 19,
    DEVICE_GET_LOG           = 20,
    DEVICE_REBOOT            = 21,
    DEVICE_SWITCHDEFEND      = 22,
    DEVICE_GET_SWICTHDEFEND  = 23,
    DEVICE_GET_CONTROL_LOCK  = 24,
    DEVICE_POWER_DOWN        = 25,
    DEVICE_SET_PKETYPE       = 26,

    DEVICE_BACKWHEEL            = 28,
    DEVICE_BACKSEAT_UNLOCK      = 29,
    DEVICE_SET_AUDIO            = 30,
    DEVICE_GET_PARAMS           = 31,
    DEVICE_SET_PARAMS           = 32,
    DEVICE_ACC                  = 33,
    DEVICE_STATUS               = 34,
    DEVICE_UPGRADE              = 35,
    DEVICE_GET_CUSTOM_AUDIO     = 36,
    DEVICE_GET_PARAM_MGBT       = 37,
    DEVICE_SET_PARAM_MGBT       = 38,
    DEVICE_GET_STATUS_MGBT      = 39,
    DEVICE_SET_SADDLE           = 40,
    DEVICE_GET_BMS_TIMING_INFO  = 41,
    DEVICE_GET_BMS_FIXED_INFO   = 42,
    DEVICE_UPDATE_BMS           = 43,
    DEVICE_GET_ETC_INFO         = 44,
    DEVICE_SET_ETCSPEED         = 45,
    DEVICE_SET_ETCPROTECTVOLTAGE= 46,
    DEVICE_SET_ETCLIMITCURRENT  = 47,
    DEVICE_SET_ETCSLOWSTART     = 48,
    DEVICE_SET_BLETOKEN         = 49,
    DEVICE_GET_STATISTICS       = 50,
    DEVICE_UPGRADE_FENCE        = 50,
    DEVICE_SET_ISBEEP           = 51,

    DEVICE_START_BEEP           = 53,
    DEVICE_SET_ISMOTOR          = 54,
    DEVICE_BLE_UPGRADE          = 55,
    DEVICE_SET_ETCLIGHT         = 56,
    DEVICE_SET_AUDIO_IN_ONE     = 57,
    DEVICE_GET_NMEA_STR         = 58,
    DEVICE_GET_STATE            = 59,
    DEVICE_STM_UPGRADE          = 60,//hello d的 stm升级
    //DEVICE_SET_FENCE         = 60,
    DEVICE_GET_ETCINFO_BEE      = 63,
    DEVICE_GET_STATUS_LEXING    = 65,
    DEVICE_SET_BATTERYMODE      = 67,
    DEVICE_SET_BMSBALANCE       = 68,
    DEVICE_SET_BATTERYDIFFV     = 69,
    DEVICE_SET_CHARGEFET        = 70,
    DEVICE_SET_DISCHARGEFET     = 71,
    DEVICE_SET_STMWORKMODE      = 72,
    DEVICE_GET_LBS              = 73,
    DEVICE_GET_CELLINFO         = 74,
    DEVICE_SET_433_MODE         = 75,
    DEVICE_FOTA                 = 76,
    DEVICE_SET_LOCKCAR_FORCE    = 78,

    DEVICE_CHANGE_CONFIG        = 80,
    DEVICE_SET_FLASH_AUDIO_IN_ONE= 81,
    DEVICE_HELMET                = 82,
    DEVICE_SET_BATTERY           = 84,
    DEVICE_GET_NEARTBEACONINFO   = 85,
    DEVICE_ETC_UPGRADE           = 83,
    DEVICE_BMS_UPGRADE           = 88,
    DEVICE_GET_WIFILOCAL         = 89,
    DEVICE_DT_OVERSPPED          = 90,
    DEVICE_SET_BREATHLED         = 91,
    DEVICE_SET_LED               = 92,
	DEVICE_SET_HARD_CONFIG       = 97,
};

/*
 * 错误码区段划分：
 *  成功返回0
 *  二进制接口的错误码为负数
 *  文本接口的错误码为正数
 */
enum
{
    ERR_SUCCESS = 0,
    ERR_VERSION_DOWNGRADE = -1,     //目标版本低于当前版本
    ERR_DISK_NO_SPACE = -2,         //磁盘空间不足
    ERR_CHECKSUM_FAILED = -3,       //文件校验出错

    ERR_RANGE_TOO_LARGE         = 105,//请求越界

    ERR_MEMORY_NOT_ENOUGH       = 110,  //内存申请出错
    ERR_CMD_NOT_SUPPORTED       = 111,  //命令不支持
    ERR_NO_BATTERY_TYPE         = 113,  //电池类型未设置
    ERR_PARAM_INVALID           = 114,  //请求消息参数不合法
    ERR_PARAM_MISSING           = 115,  //请求消息中参数缺失
    ERR_HTTP_CID                = 116,//HTTPCID错误
    ERR_HTTP_URL                = 117,//HTTPURL错误
    ERR_HTTP_USERDATA           = 118,//HTTPUSERDATA错误
    ERR_HTTP_WRITEDATA          = 119,//post数据写入modem时错误
    ERR_HTTP_ACTION             = 120,//HTTPACTION除去常301 500 601 603 404错误的其他错误
    ERR_HTTP_POSTREAD           = 121,//post读取服务器返回数据失败
    ERR_HTTP_IS_PROCING         = 122,//http中正在执行进程
    ERR_HTTP_READFILE           = 123,//post中读取文件数据失败
    ERR_HTTP_MOVEDPERMANENTLY   = 124,//301 error
    ERR_HTTP_NOTFOUND           = 125,//404 error
    ERR_HTTP_REQUESTTIMEOUT     = 126,//408 error
    ERR_HTTP_INTERNALSERVERERROR= 127,//500 error
    ERR_HTTP_GATEWAYTIMEOUT     = 128,//504 error
    ERR_HTTP_NETWORKERROR       = 129,//601 error
    ERR_HTTP_DNSERROR           = 130,//603 error
    ERR_FILE_ERROR              = 131,//setting文件和server修改错误
    ERR_CAR_NOT_STOP            = 132,//车辆未停止
    ERR_UPGRADE_CRCERROR        = 133,//CRC校验失败
    ERR_OPEN_GPRS_FAILED        = 134,//http打开GPRS失败
    ERR_OPERATION_TIMEOUT       = 135,//操作超时
    ERR_OPERATION_ERROR         = 136,//操作失败
    ERR_OUT_OF_TIME             = 137,//收到命令的时候已经超时了
    ERR_CONTINUALLY             = 138,
    ERR_ACCESS_DENY             = 139,//超级锁车功能开启，无法操作
    ERR_OTA_UPGRADING           = 140,//控制器或者BMS OTA升级中，无法操作
};

enum
{
    CMD_UDP_GPS         = 0,
    CMD_UDP_DEVICE_INFO = 1,
    CMD_UDP_LOGIN           = 2,
    CMD_UDP_DEVICE_INFO_V2  = 3,
    CMD_UDP_DEVICE_INFO_V4  = 5,
    CMD_UDP_TLV             = 6,
    CMD_UDP_LOG_NEW         = 8,
};

typedef enum
{
    REBOOT_NULL         = 0,        // 无重启
    REBOOT_NORMAL       = 1,        // 正常开机
    REBOOT_COMAND       = 2,        // 指令重启
    REBOOT_UPGRADE      = 3,        // 升级重启
    REBOOT_ERROR        = 4,        // 异常重启
    REBOOT_NETWORK      = 5,        // 网络异常
    REBOOT_HEARTBEAT    = 6,        // 心跳丢失重启
    REBOOT_GPSNMEA      = 7,        // GPS nmea不输出
    REBOOT_MEMORY       = 8,        // 内存问题重启
    REBOOT_HTTPERROR    = 9,        // http问题重启
    REBOOT_FSMERROR     = 10,       // 状态机异常重启
    REBOOT_MPUERROR     = 11,       // 加速度计异常重启
    REBOOT_SWITCHSIM    = 12,       // 主备卡切卡
    REBOOT_SIMCHECK     = 13,       // 检测卡信息
    REBOOT_TYPEMAX
} REBOOT_TYPE;



#pragma pack(push, 1)

/*
 * Message header definition
 */
typedef struct
{
    short signature;
    char cmd;
    char seq;
    short length;
} __attribute__((__packed__)) MSG_HEADER;

#define MSG_HEADER_LEN sizeof(MSG_HEADER)



/*
 * Login message structure
 */
typedef struct
{
    MSG_HEADER header;
    int version;
    char deviceType;
    char IMEI[MAX_IMEI_LENGTH];
    char voltage;
} __attribute__((__packed__)) MSG_LOGIN_REQ;

typedef struct
{
    MSG_HEADER header;
    uint32_t version;
    uint8_t deviceType;
    uint8_t IMEI[MAX_IMEI_LENGTH];
    uint8_t IMSI[MAX_IMSI_LENGTH];
} __attribute__((__packed__)) MSG_LOGIN_REQ_NEW;

typedef struct
{
    MSG_HEADER header;
    uint8_t IMEI[MAX_IMEI_LENGTH];
    uint8_t mainIMSI[MAX_IMSI_LENGTH];
	uint8_t mainCCID[MAX_CCID_LENGTH];
	uint8_t backupIMSI[MAX_IMSI_LENGTH];
	uint8_t backupCCID[MAX_CCID_LENGTH];
} __attribute__((__packed__)) MSG_SIMINFO_REQ;

typedef struct
{
    MSG_HEADER header;
    uint32_t version;
    uint8_t deviceType;
    uint8_t IMEI[MAX_IMEI_LENGTH];
    uint8_t IMSI[MAX_IMSI_LENGTH];
    uint32_t newIP;
} __attribute__((__packed__)) MSG_LOGIN_V2_REQ;

typedef MSG_HEADER MSG_LOGIN_RSP;

typedef struct
{
    MSG_HEADER header;
    uint32_t timestamp;
} __attribute__((__packed__)) MSG_LOGIN_REQ_NEW_RSP;

typedef struct
{
    MSG_HEADER header;
    uint32_t timestamp;
    uint32_t newServerIP;
    uint16_t newServerPort;
} __attribute__((__packed__)) MSG_LOGIN_REQ_V3_RSP;

/*
 * ping message structure
 */
typedef struct
{
    MSG_HEADER header;
    char gsm;
    char voltage;
} __attribute__((__packed__)) MSG_PING_REQ;

typedef struct
{
    MSG_HEADER header;
    char gsm;
    uint32_t voltage_mV;
} __attribute__((__packed__)) MSG_PING_REQ_NEW;

typedef MSG_HEADER MSG_PING_RSP;

typedef struct
{
    MSG_HEADER header;
    char gsm;
} __attribute__((__packed__)) MSG_PINGV2_REQ;

/*
 * GPS structure
 */
typedef struct
{
    uint32_t timestamp;
    float longitude;
    float latitude;
    uint16_t course;
    uint8_t speed;
} __attribute__((__packed__))GPS;

typedef struct
{
    MSG_HEADER header;
    GPS gps;
} __attribute__((__packed__)) MSG_GPS;

typedef struct
{
    MSG_HEADER header;
    u16 etcFault;
    u16 bmsFault;
    u16 ecuFault;
} __attribute__((__packed__)) MSG_FAULT_INFO;

/*
 * CELL structure
 */
typedef struct
{
    unsigned short lac;      //local area code
    unsigned short cellid;   //cell id
    short          rxl;      //receive level  dBm = rxl - 113
} __attribute__((__packed__)) CELL;


/*
 * alarm message structure
 */
typedef enum
{
    ALARM_BATTERYNULL   = 0,
    ALARM_FENCE_OUT     = 1,
    ALARM_FENCE_IN      = 2,
    ALARM_VIBRATE       = 3,
    ALARM_BATTERY50     = 4,
    ALARM_BATTERY30     = 5,
    ALARM_POWER_CUT     = 6,
    ALARM_SWITCH_OPEN   = 7,
    ALARM_SWITCH_CLOSE  = 8,
    ALARM_BACKSEAT_OPEN = 9,
    ALARM_BACKSEAT_SHUT = 10,
    ALARM_POWER_RESTORE = 11,
    ALARM_SHAKE         = 12,
    ALARM_AUTOLOCK_DEFEND   = 13,
    ALARM_AUTOLOCK_WARNING  = 14,
    ALARM_DEFENDON          = 15,
    ALARM_DEFENDOFF         = 16,
    ALARM_DEFENDON_BLE      = 19,
    ALARM_DEFENDOFF_BLE     = 20,
    ALARM_ACCON_BLE         = 21,
    ALARM_LOCK_CAR          = 22,
    ALARM_ACCON             = 23,
    ALARM_ACCON_PKE         = 24,
    ALARM_CONSTANTLYSHAKE   = 25,
    ALARM_UNLOCKSADDLE_BLE  = 26,
    ALARM_OVERTURN          = 27,
    ALARM_OVERTURN_RESTORE  = 28,
    ALARM_OUT_WARNING_FENCE = 32,
    ALARM_IN_WARNING_FENCE  = 33,

    ALARM_HELMET_NOTATPOS    = 41, //头盔离位通知
    ALARM_HELMET_ATPOS       = 42, //头盔在位通知
    ALARM_HELMET_LOCK        = 43, //头盔锁上锁通知
    ALARM_HELMET_UNLOCK      = 44, //头盔锁解锁通知
    ALARM_HELMET_CONNECT     = 45, //头盔锁连接通知
    ALARM_HELMET_DISCONNECT  = 46, //头盔锁断开通知
    ALARM_HELMET_LOCK_ERR    = 47, //头盔锁上锁失败通知：关锁后helmetLock仍为0
    ALARM_HELMET_UNLOCK_ERR  = 48, //头盔锁解锁失败通知：解锁后helmetLock仍为1
    
    ALARM_NUM
} ALARM_TYPE;

typedef struct
{
    MSG_HEADER header;
    char alarmType;
} __attribute__((__packed__)) MSG_ALARM_REQ;

typedef MSG_HEADER MSG_ALARM_RSP;

/*
 * alarm message structure
 */
enum NOTIFY_TYPE
{
    NOTIFY_MASSAUDIO_SUCCESS = 0,
    NOTIFY_MASSAUDIO_FAILED  = 1,
    NOTIFY_MC_FAULT_CHANGED = 2,
    NOTIFY_SINGLEAUDIO_SUCCESS = 3,
    NOTIFY_SINGLEAUDIO_FAILED  = 4,
    NOTIFY_SETOVERSPEEDAUDIO_SUCCESS = 5,
    NOTIFY_SETOVERSPEEDAUDIO_FAILED  = 6,
    NOTIFY_HELMET_OPERATE_FAILED  = 7,
};

typedef struct
{
    MSG_HEADER header;
    uint8_t notifyType;
    uint8_t notifyValue;
} __attribute__((__packed__)) MSG_NOTIFY_REQ;

typedef struct
{
    MSG_HEADER header;
    uint16_t notifyType;
    uint16_t payload;
    uint32_t reserved;
} __attribute__((__packed__)) MSG_NOTIFY_V2_REQ;

typedef MSG_HEADER MSG_NOTIFY_RSP;

typedef struct
{
    MSG_HEADER header;
    char WatchDog_Type;
} __attribute__((__packed__)) MSG_SOFTWATCHDOG_REQ;

/*
 * upgrade message structure
 */
typedef struct
{
    MSG_HEADER header;
    int version;
    int size;
} __attribute__((__packed__)) MSG_UPGRADE_START;

typedef struct
{
    MSG_HEADER header;
    char code;      //MSG_SUCCESS means OK to upgrade
} __attribute__((__packed__)) MSG_UPGRADE_START_RSP;

typedef struct
{
    MSG_HEADER header;
    int offset;
    char data[];
} __attribute__((__packed__)) MSG_UPGRADE_DATA;

typedef struct
{
    MSG_HEADER header;
    int offset;
} __attribute__((__packed__)) MSG_UPGRADE_DATA_RSP;

typedef struct
{
    MSG_HEADER header;
    int checksum;
    int size;
} __attribute__((__packed__)) MSG_UPGRADE_END;

typedef struct
{
    MSG_HEADER header;
    char code;
} __attribute__((__packed__)) MSG_UPGRADE_END_RSP;

/*
 * sim info message structure
 */
typedef struct
{
    MSG_HEADER header;
    char CCID[MAX_CCID_LENGTH];
    char IMSI[MAX_IMSI_LENGTH];
} __attribute__((__packed__)) MSG_SIM_INFO;

/*
 * packed GPS message structure
 */
typedef struct
{
    MSG_HEADER header;
    GPS gps[];
} __attribute__((__packed__)) MSG_GPS_PACK;

/*
 * CMD_DEVICE message structure
 */
typedef struct
{
    MSG_HEADER header;
    char data[];
} __attribute__((__packed__)) MSG_DEVICE_REQ;

typedef struct
{
    MSG_HEADER header;
    char data[];
} __attribute__((__packed__)) MSG_DEVICE_RSP;

/*
 * CMD_FTPPUTOK message structure
 */
typedef struct
{
    MSG_HEADER header;
    char code;
    char fileName[];
} __attribute__((__packed__)) MSG_FTPPUT_REQ;

typedef struct
{
    MSG_HEADER header;
} __attribute__((__packed__)) MSG_FTPPUT_RSP;

#define SW_MASK_DEFEND          (1 << 0)
#define SW_MASK_ACC             (1 << 1)
#define SW_MASK_WHEEL           (1 << 2)
#define SW_MASK_SEAT            (1 << 3)
#define SW_MASK_POWER           (1 << 4)
#define ST_MASK_FREQ            (1 << 5)
#define ST_MASK_MOVE            (1 << 6)
#define ST_MASK_WHEEL           (1 << 7)
#define ST_MASK_UNHELMET        (1 << 8)
#define ST_MASK_SLEEP           (1 << 9)
#define ST_MASK_DISTURB         (1 << 10)
#define ST_MASK_ISOVERSPEED     (1 << 11)
#define ST_MASK_ISGPSUNFIXED    (1 << 12)
#define ST_MASK_ISGYROFIXED     (1 << 13)
#define SW_MASK_BATTERY         (1 << 13)
#define ST_MASK_ISFENCEENABLE   (1 << 14)
#define ST_MASK_ISOUTOFSERVAERA (1 << 15)

#define ST_HELMET_TYPE                (1 << 0)
#define ST_HELMET_CONNECTDETECT_SW    (1 << 1)
#define ST_HELMET_PINDETECT           (1 << 2)
#define ST_HELMET_LOCKDETECT          (1 << 3)
#define ST_HELMET_CONNECTDETECT       (1 << 4)
#define ST_HEMLET_RESERVE5            (1 << 5)
#define ST_HEMLET_RESERVE6            (1 << 6)
#define ST_HEMLET_RESERVE7            (1 << 7)

enum//电池电压值准与不准
{
    STATIC_ACCURATE,
    MOTION_ACCURATE,
    BATTRY_INACCURATE
};

typedef struct
{
    MSG_HEADER header;
    uint8_t sw;
    uint8_t gsm;
    uint32_t voltage;
    uint32_t timestamp;
    float longitude;
    float latitude;
    uint8_t speed;
    uint16_t course;
} __attribute__((__packed__)) MSG_GPS_MANGO;

typedef struct
{
    MSG_HEADER header;
    uint8_t mode;
    uint8_t gsm;
    uint32_t voltage;
    GPS gps;
} __attribute__((__packed__)) MSG_STATUSGPS_MANGO;

typedef struct
{
    MSG_HEADER header;
    uint8_t mode;
    uint8_t gsm;
    uint32_t voltage;
    uint16_t mcc;  //mobile country code
    uint16_t mnc;  //mobile network code
    uint8_t  cellNo;// cell count
    CELL cell[];
} __attribute__((__packed__)) MSG_STATUSCELL_MANGO;


typedef struct
{
    MSG_HEADER header;
    uint16_t sw;
    uint8_t gsm;
    uint32_t voltage;
    uint32_t timestamp;
    float longitude;
    float latitude;
    uint8_t speed;
    uint16_t course;
    float hdop;
    uint8_t satellite;
} __attribute__((__packed__)) MSG_GPS_V4;

typedef struct
{
    MSG_HEADER header;
    uint16_t sw;
    uint8_t gsm;
    uint32_t voltage;
    uint32_t timestamp;
    float longitude;
    float latitude;
    uint8_t speed;
    uint16_t course;
    float hdop;
    uint8_t satellite;
} __attribute__((__packed__)) MSG_GPS_MANGO_V4;

typedef struct
{
    MSG_HEADER header;
    uint16_t sw;
    uint8_t gsm;
    uint32_t voltage;
    uint32_t timestamp;
    float longitude;
    float latitude;
    uint8_t speed;
    uint16_t course;
    float hdop;
    uint8_t satellite;
    float miles;
    u8 reserve[];
} __attribute__((__packed__)) MSG_GPS_V5;

typedef struct
{
    MSG_HEADER header;
    uint32_t sw;
    uint8_t gsm;
    uint32_t voltage;
    uint32_t timestamp;
    uint32_t longitude;
    uint32_t latitude;
    uint16_t speed;
    uint16_t course;
    uint16_t hdop;
    uint8_t satellite;
    uint32_t totalMiles;
    uint32_t fenceVersion;
    u8 reserve[];
} __attribute__((__packed__)) MSG_GPS_V6;

typedef struct
{
    MSG_HEADER header;
    uint8_t manufacturer[16];//厂商名称
    uint8_t model[16];       //BMS型号
    uint16_t hardwareVer;    //BMS硬件版本
    uint16_t softwareVer;    //BMS软件版本
    uint8_t SN[16];          //BMS串号
    uint8_t gpsId[16];       //GPS编码
    uint16_t capacity;       //电池满充容量
    uint16_t cycleCount;     //循环次数
    uint16_t voltage;        //总电压 单位mV
    int32_t current;         //总电流 单位mA(+:放电电流-:充电电流)
    int8_t MOSTemperature;   //MOS温度 单位: 摄氏度
    int8_t temperature1;     //电池包第一路温度
    int8_t temperature2;     //电池包第二路温度
    uint16_t cellVoltageMax; //单体电池最大电压 单位mV
    uint16_t cellVoltageMin; //单体电池最小电压 单位mV
    uint16_t cellVoltageDIF; //单体电压压差 单位mV
    uint16_t fault;          //故障位: 0为正常，1为故障
    uint8_t mosfetState;     //0x01: 充电状态 0x02: 放电状态 0x03: 储藏状态
    uint8_t SOC;             //电池剩余容量百分比，单位1%
    uint16_t remainCapacity; //电池剩余容量 单位: mAH
    uint32_t timestamp;      //BMS数据采集点时间戳
} __attribute__((__packed__)) SUBMIT_ND_BMS_INFO_DATA; //南都BMS上报协议


typedef struct
{
    MSG_HEADER header;
    u8 sn[20];
    u16 hardVersion;
    u16 softVersion;
    s16 MOSTemp;
    u8 MOSState;
    u8 maxVoltage;
    u8 minVoltage;
    u8 healthState;
    u16 fault;
    u16 capacity;
    u16 remainCapacity;
    u8 SOC;
    u16 cycle;
    u16 voltage;
    s16 current;
    u32 timestamp;
} __attribute__((__packed__)) MSG_BMS_INFO_CMD;


typedef struct
{
    MSG_HEADER header;
    uint8_t data[];
} __attribute__((__packed__)) MSG_UPLOAD_NMEA;


typedef struct
{
    uint8_t healthState;
    uint8_t temperature;
    uint32_t remaining_mAH;
    uint32_t timestamp;
} __attribute__((__packed__))MSG_BMS_INFO;

typedef struct
{
    uint8_t fault;
    uint16_t current;
    uint32_t voltage;
    uint32_t pulse;
    uint32_t timestamp;
} __attribute__((__packed__))MSG_ETC_INFO;

typedef struct
{
    MSG_HEADER header;
    MSG_BMS_INFO bms;
    MSG_ETC_INFO etc;
} __attribute__((__packed__)) MSG_BMS_ETC_INFO;

typedef struct
{
    MSG_HEADER header;
    int16_t bms1Temp;   //单位 0.1摄氏度
    uint16_t bms1Voltage;//单位 0.01V
    uint16_t bms1Current;//单位 0.01A
    uint8_t  bms1SOC;    //单位 %
    uint8_t  bms1SN[16]; //字符串
    int16_t bms2Temp;   //单位 0.1摄氏度
    uint16_t bms2Voltage;//单位 0.01V
    uint16_t bms2Current;//单位 0.01A
    uint8_t  bms2SOC;    //单位 %
    uint8_t  bms2SN[16]; //字符串
    uint32_t timestamp;  //单位 秒
} __attribute__((__packed__)) MSG_BMS_HELLO;

typedef struct
{
    MSG_HEADER header;
    uint8_t data[];
} __attribute__((__packed__)) MSG_UPDATE_FENCE_REQ;

typedef struct
{
    MSG_HEADER header;
    uint8_t code;
} __attribute__((__packed__)) MSG_UPDATE_FENCE_RSP;


typedef struct
{
    MSG_HEADER header;
    uint32_t timestamp;
    uint8_t version;
    uint8_t cycletimes;
    uint8_t healthState;
    uint8_t temperature;
    uint32_t remaining_mAH;
    uint32_t capacity_mAH;
    uint8_t SN[16];
} __attribute__((__packed__)) MSG_BMS_REQ;

typedef struct
{
    MSG_HEADER header;
    uint8_t version;
    uint8_t id[10];
    uint8_t SN[20];
    uint32_t timestamp;
    uint8_t sw;
    uint8_t SOH;
    uint8_t SOC;
    uint16_t state;
    uint16_t cycletimes;
    uint16_t remaining_mAH;
    uint16_t voltage;
    int16_t current;
    uint16_t balancestate;
    uint16_t cellVoltage[16];
    uint8_t fetState;
    int8_t cellTemperatrure[5];
    int8_t MOSTemperature;
    int8_t enTemperature;
    uint8_t software;
} __attribute__((__packed__)) MSG_BMS_MSG_REQ_V2;

typedef struct
{
    MSG_HEADER header;
    uint8_t imei[15];
    uint32_t version;
    uint64_t diagnosisList;
    uint64_t diagnosisError;
    uint32_t lat;
    uint32_t lon;
} __attribute__((__packed__)) MSG_DIAGNOSIS_RESULT_REQ;

typedef struct
{
    MSG_HEADER header;
    uint8_t uuid[32];
    uint32_t version;
    uint64_t diagnosisList;
    uint64_t diagnosisError;
    uint32_t lat;
    uint32_t lon;
} __attribute__((__packed__)) MSG_DIAGNOSIS_RESULT_STM_REQ;


typedef MSG_HEADER MSG_DIAGNOSIS_RESULT_RSP;



/*
 * UDP Message header definition
 */

#define FAULT_ACCELEROMETER 1 << 0
#define FAULT_ACC_SWICTH    1 << 1
#define FAULT_GPS_NMEA      1 << 2

typedef struct
{
    short signature;
    char imei[15];
    char cmd;
    short length;
} __attribute__((__packed__)) MSG_UDP_HEADER;

#define MSG_UDP_HEADER_LEN sizeof(MSG_UDP_HEADER)

typedef struct
{
    MSG_UDP_HEADER header;
    uint8_t IMSI[MAX_IMSI_LENGTH];
    uint32_t version;
} __attribute__((__packed__)) MSG_UDP_LOGIN;


typedef enum
{
    TLV_UDP_VERSION         = 0,    //length 4  //U32
    TLV_UDP_IMSI            = 1,    //length 15 //U8[15]
    TLV_UDP_DEVICEFAULT     = 2,    //length 1  //BIT8
    TLV_UDP_GPS             = 3,    //length 15 //GPS
    TLV_UDP_REBOOT_REASON   = 4,    //length 1  //U8
    TLV_UDP_VCAR            = 5,    //length 4  //U32
    TLV_UDP_VBATTERY        = 6,    //length 2  //U16
    TLV_UDP_PKTS_STATE      = 7,    //length 8  //U32
    TLV_UDP_STATUS_BIT      = 8,    //length 2  //BIT16
    TLV_UDP_BMS_ID          = 9,    //length X  //uint8_t[]
    TLV_UDP_BMS_SOC         = 10,   //length 1  //uint8_t
    TLV_UDP_BMS_SOH         = 11,   //length 1  //uint8_t
    TLV_UDP_BMS_VOLTAGE_mV  = 12,   //length 4  //uint32_t
    TLV_UDP_BMS_CURRENT_mA  = 13,   //length 4  //uint32_t
    TLV_UDP_BMS_TEMPERATURE = 14,   //length 2  //int16_t 0.1摄氏度
    TLV_UDP_BMS_CYCLETIMES  = 15,   //length 2  //uint16_t
    TLV_UDP_BMS_ERRORS_MT   = 16,   //length 4  //bit32
    TLV_UDP_ETC_MERCHANT    = 17,   //length 1  //uint8_t
    TLV_UDP_ETC_TYPE        = 18,   //length 1  //uint8_t
    TLV_UDP_ETC_PROTOCOL_VER= 19,   //length 1  //uint8_t
    TLV_UDP_ETC_FAULT       = 20,   //length 1  //bit8
    TLV_UDP_CCID            = 21,   //length 20 //uint8_t[20]
    TLV_UDP_BER             = 22,   //length 1  //uint8_t
    TLV_UDP_GSM             = 23,   //length 1  //uint8_t
    TLV_UDP_CELLINFO        = 24,   //length x  //CELLINFO
    TLV_UDP_IMSI_BAK        = 25,   //length 15 //U8[15]
    TLV_UDP_CCID_BAK        = 26,   //length 20 //uint8_t[20]
	TLV_UDP_CONFIG          = 100,  //length x  //config
    TLV_UDP_MAX
} Enum_TLV_TYPE_UDP;

typedef struct
{
    MSG_UDP_HEADER header;
    uint8_t tlv[];
} __attribute__((__packed__)) MSG_UDP_STATUS;

/*
 * UDP packed GPS message structure
 */
typedef struct
{
    MSG_UDP_HEADER header;
    GPS gps;
    uint8_t gsm;
    uint32_t voltage_car;
    uint32_t voltage_bat;
    uint32_t pkts_sent;
    uint32_t pkts_acked;
    uint32_t bytes_sent;
    uint32_t bytes_acked;
} __attribute__((__packed__)) MSG_DEVICE_INFO_UDP_V2;

/*
 * UDP packed GPS message structure
 */
typedef struct
{
    MSG_UDP_HEADER header;
    GPS gps;
    uint8_t gsm;
    uint32_t voltage_car;
    uint32_t voltage_bat;
    uint32_t pkts_sent;
    uint32_t pkts_acked;
    uint32_t bytes_sent;
    uint32_t bytes_acked;
    uint16_t accOnCount;
    uint16_t pwrCutCount;
    uint8_t deviceFault;
} __attribute__((__packed__)) MSG_DEVICE_INFO_UDP_V4;

/*
 * UDP packed GPS message structure
 */
typedef struct
{
    MSG_UDP_HEADER header;
    float speed;
} __attribute__((__packed__)) MSG_SPEED_UDP;


typedef struct
{
    uint8_t merchantCode;    //厂商编码
    uint8_t type;            //控制器类型
    uint8_t protocolVersion; //协议版本
    uint32_t hallCount;      //500ms内霍尔数
    uint8_t limitSpeed;      //% [40-100]
    uint8_t fault;           //[isDefend, isETCfault, isHallFault, isHandleFault, isUnderVoltage, isBrakeFault]
} MSG_MT_ETC_UDP;

typedef struct
{
    uint8_t barcodeNumber[32];
    uint16_t softVersion;
    uint16_t hardVersion;
    uint16_t innerStatus;    //内部状态
    uint32_t errors;         //错误码
    uint16_t warnings;       //警告
    uint8_t  batterySOC;     //剩余容量百分比
    uint8_t  batterySOH;     //健康状态百分比
    uint32_t packVoltage;    //电池包总电压
    uint32_t realCurrent;    //实时电流
    uint8_t highestTemp;     //实时电芯最高温度
    uint8_t lowestTemp;      //实时电芯最低温度
    uint8_t mosTemp;         //实时mos管温度
    uint8_t otherTemp;       //其它温度
    uint8_t maxChargeCurrent;//允许的最大电流
    uint16_t cycleCounter;   //电池循环次数
} __attribute__((__packed__)) MSG_MT_BMS_UDP;

typedef struct
{
    uint32_t pkts_sent;
    uint32_t pkts_acked;
} __attribute__((__packed__)) MSG_PKTS_STATUS_UDP;


typedef struct
{
    uint16_t mcc;    //mobile country code
    uint16_t mnc;    //mobile network code
    uint16_t lac;    //local area code
    uint16_t cellid; //cell id
    uint16_t rxl;    //receive level  dBm = rxl - 113
} __attribute__((__packed__)) MSG_CELLINFO_UDP;


typedef struct
{
    MSG_UDP_HEADER header;
    char data[];
} __attribute__((__packed__)) MSG_DEVICE_UDP_LOG;


typedef struct
{
    uint64_t val;
} __attribute__((__packed__)) MSG_U64_VALUE;

typedef struct
{
    int64_t val;
} __attribute__((__packed__)) MSG_S64_VALUE;

typedef struct
{
    uint32_t val;
} __attribute__((__packed__)) MSG_U32_VALUE;

typedef struct
{
    int32_t val;
} __attribute__((__packed__)) MSG_S32_VALUE;


typedef struct
{
    uint16_t val;
} __attribute__((__packed__)) MSG_U16_VALUE;

typedef struct
{
    int16_t val;
} __attribute__((__packed__)) MSG_S16_VALUE;

typedef struct
{
    uint8_t val;
} __attribute__((__packed__)) MSG_U8_VALUE;

typedef struct
{
    int8_t val;
} __attribute__((__packed__)) MSG_S8_VALUE;


#pragma pack(pop)

#endif /* _PROTOCOL_H_ */
