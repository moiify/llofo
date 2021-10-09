#ifndef DA14580_H_
#define DA14580_H_

#include "types.h"
#include "protocol.h"

#define TBEACON_INFO_LEN 22
#define TBEACON_MAC_LEN 6
#define HOST_MAC_LEN 6
#define TBEACON_ID_LEN 12
#define TBEACON_VER_LEN 2

typedef enum
{
    NOTIFY_PKE,
    NOTIFY_DEFEND_ON,
    NOTIFY_DEFEND_OFF,
    NOTIFY_FINDME,
    NOTIFY_START,
    NOTIFY_CONNECTED,
    NOTIFY_DISCONNECTED,
    NOTIFY_STACKRESTART = 10,
} BLE_EVENT_NOTIFY;

typedef enum
{
    BLE_ADDRESS     = 0x00,//蓝牙通信地址
    BMS_ADDRESS     = 0x01,//BMS通信地址
    BIO_ADDRESS     = 0x02,//BIO通信地址
    CHECK_ADDRESS   = 0x03,//检测通信地址
    STC_ADDRESS     = 0x05,//STC锁通信地址
    ETC_ADDRESS     = 0X10,//小安ETC协议通信地址
    XH_BMS_ADDRESS  = 0x16,//星恒BMS通信地址
    RFID_ADDRESS    = 0xFF,//RFID通信协议
} ADDRESS_485;

enum
{
    BLE_PORT0 = 0X00,
    BLE_PORT1 = 0X01,
    BLE_PORT2 = 0X02,
};

enum
{
    BLE_PIN0 = 0X00,
    BLE_PIN1 = 0X01,
    BLE_PIN2 = 0X02,
    BLE_PIN3 = 0X03,
    BLE_PIN4 = 0X04,
    BLE_PIN5 = 0X05,
    BLE_PIN6 = 0X06,
    BLE_PIN7 = 0X07,
    BLE_PIN8 = 0X08,
    BLE_PIN9 = 0X09,
};

//检测命令
enum
{
    CMD_CHK_ALL                 = 0,
    CMD_CHK_GSM                 = 1,
    CMD_CHK_BATTERY             = 2,
    CMD_CHK_ACC                 = 3,
    CMD_CHK_SIMCARD             = 4,
    CMD_CHK_BRAKE_ON            = 5,
    CMD_CHK_BRAKE_OFF           = 6,
    CMD_CHK_BACKSEAT_UNLOCK     = 7,
    CMD_CHK_SET_DEFEND          = 8,
    CMD_CHK_END                 = 9,
    CMD_GET_IMEI                = 10,
    CMD_GET_VERSION_AND_IMEI    = 11,
    CMD_CHK_BACKSEAT_LOCK       = 12,
    CMD_CHK_BACKWHEEL_UNLOCK    = 13,
    CMD_CHK_BACKWHEEL_LOCK      = 14,
    CMD_CHK_GPS                 = 15,
    CMD_CHK_IS_WHEELSPAN        = 16,

    CMD_CHK_SADDLE_INPLACE      = 20,//K
    CMD_CHK_SADDLE_OUTPLACE     = 21,//L
    CMD_CHK_BACKWHEEL_INPLACE   = 22,//M
    CMD_CHK_BACKWHEEL_OUTPLACE  = 23,//N
    CMD_CHK_BMS_1_COM           = 24,//O
    CMD_CHK_ELEC                = 26,
    CMD_CHK_AUDIO_CUSTROM_RESULT= 29,//语音定制结果
    CMD_CHK_OVER_SPEED          = 53,//超速报警信号错误
    CMD_CHK_ALL_NEW             = 66,
    CMD_END
};

typedef enum
{
    PIN_LEVEL_LOW = 0,
    PIN_LEVEL_HIGH = 1,
} BLE_PIN_LEVEL;

//道钉状态
typedef enum{
    EVENT_NOTBEACON       = 0X00,
    EVENT_ACCONTBEACON    = 0X01,
    EVENT_DEFENDONTBEACON = 0X02,
    EVENT_FINDTBEACON     = 0X03,
}TBEACON_EVENT_CODE;

#pragma pack(push, 1)

typedef struct
{
    u8 signature;
    u8 address;
    u8 cmd;
    u8 length;
    u8 data[];
} __attribute__((__packed__)) MSG_BMS_XINGHENG;

#define MSG_HEADER_XINGHENG_LEN sizeof(MSG_BMS_XINGHENG)

typedef struct
{
    uint8_t sw;
    uint8_t name[15];
    uint8_t imei[15];
    uint8_t token[4];
} __attribute__((__packed__)) ST_MSG_SETTING_PARAM;

typedef struct
{
    u8 cmd;
    u8 len;
    u8 mode;
    u8 gsm;
    u8 sw;
    u32 volatge_mV;
    u8 checksum;
} __attribute__((__packed__))DA14580_STATUS_MSG;

typedef struct
{
    u8 cmd;
    u8 len;
    u8 data;
    u8 checksum;
} __attribute__((__packed__))DA14580_SHUTDOWN_MSG;

typedef struct
{
    u8 cmd;
    u8 length;
    u8 data[];
} __attribute__((__packed__)) MSG_HEADER_DATA;

#define MSG_HEADER_485_LEN sizeof(MSG_HEADER_DATA)

typedef struct
{
    short signature;
    uint8_t address;
    uint8_t cmd;
    uint8_t length;
    uint8_t data[];
} __attribute__((__packed__)) MSG_HEADER_XA;

#define MSG_HEADER_XA_LEN sizeof(MSG_HEADER_XA)

typedef struct
{
    u8 result;             //0表示未扫到符合条件的道钉，1表示扫到
    u8 tBeaconRssi;
	u8 thold;
    u8 tBeaconMacAddr[TBEACON_MAC_LEN];
    u8 tBeaconInfo[TBEACON_INFO_LEN];
}__attribute__((__packed__))BLE_SCAN_TBEACON_RESULT;

typedef struct
{
    u8 tBeaconSignalStr[2];
    u8 tBeaconIDStr[TBEACON_ID_LEN];      //站点编号      TBEACON_ID_LEN = 12
    u8 tBeaconNumStr;                     //站点数量
    u8 tBeaconPileNumStr;                 //桩位编号
    u8 tBeaconSignalThresholdStr[2];      //信号限制
    u8 tBeaconSOCStr[2];                  //信号限制
    u8 tBeaconVersionStr[2];              //版本      TBEACON_VER_LEN = 2
}__attribute__((__packed__))TBEACON_INFO_STR;

typedef struct
{    
    u8 event;
    u8 tBeaconAddr[6];
    u8 tBeaconId[12];
    u8 tBeaconSOC;
    u16 tBeaconVsn;
    s32 lat;
    s32 lon;
    u32 timestamp;
}__attribute__((__packed__))DA14580_TBEACON_INFO_MSG;

typedef struct
{
    uint16_t data;
}__attribute__((__packed__)) DATA_16_BITS;

typedef struct
{
    int16_t data;
}__attribute__((__packed__)) DATA_S16_BITS;

typedef struct
{
    uint32_t data;
}__attribute__((__packed__)) DATA_U32_BITS;

typedef struct
{
    u16 signature;  //帧头0XFF02
    u8 cmd;         //命令字
    u8 len;         //数据长度
    u8 data[];      //数据N个字节 + 两个字节的累加校验和
} __attribute__((__packed__))DA14580_RFID485_MSG;

#define DA14580_RFID485_MSG_LEN sizeof(DA14580_RFID485_MSG)

#pragma pack(pop)

typedef int (*DA14580_PROC)(void *);

typedef struct
{
    uint8_t cmd;
    DA14580_PROC action;
} PROC_MAP;

int da14580_initial(void);

int da14580_sendUartData(uint8_t *msg, uint32_t dataLen);
int da14580_sendDATA(uint8_t address, uint8_t cmd, uint8_t *data, uint8_t dataLen);
void *da14580_allocMsg(uint8_t address, uint8_t cmd, uint8_t *data, uint8_t dataLen);
int da14580_setHeartbeat(u8 set_heartbeat);
int da14580_setBlePinLevel(u8 port, u8 pin, BLE_PIN_LEVEL level);

//int da14580_sendBMSDATA(uint8_t cmd, uint8_t *data, uint8_t dataLen);
//int da14580_setBlePinLevel(uint8_t port , uint8_t pin, BLE_PIN_LEVEL level);

#endif /* DA14580_H_ */

