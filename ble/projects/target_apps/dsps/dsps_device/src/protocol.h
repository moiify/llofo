
#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdint.h>


#define htonl(l) ((((l >> 24) & 0x000000ff)) | \
                  (((l >>  8) & 0x0000ff00)) | \
                  (((l) & 0x0000ff00) <<  8) | \
                  (((l) & 0x000000ff) << 24))
#define ntohl(l) htonl(l)

#define htons(s) ((((s) >> 8) & 0xff) | \
                  (((s) << 8) & 0xff00))
#define ntohs(s) htons(s)

typedef enum{
  BLE_WILD = 0x00,//透传到蓝牙
  BMS_WILD = 0x01,//透传到485
  BLE_CONF = 0x02,//IO 
  ETC_WILD = 0x10,//透传到485
  OTHERS,     //透传到485
 
} MSG_ADRESS;

typedef enum{
    BIO_SET_IOCFG           = 0x00,
    BIO_CONTROL_595         = 0x01,
    BIO_READ_IOLEVEL        = 0x02,
    BIO_SET_CONFIG          = 0x03,
    BIO_PING                = 0x04,
    BIO_REBOOT              = 0x05,
    BIO_ENABLE_SP4502       = 0x06,

    BIO_SET_CONFIG_V2       = 0x0B,
    
    BLE_VERSION             = 0x0E,

    PKE_KEYS_CONFIG         = 0x10,//PKE配置钥匙
    BIO_NOTIFY              = 0x11,
    BIO_SET_BEATHEART       = 0x12,
    
    BIO_CONFIG_PARAM_YA     = 0x13,
    BIO_BLE_START_SCAN_DD   = 0x14,
    BIO_WILD_YOUON          = 0x15,
    BIO_CONFIG_PARAM_YAV2   = 0x16,
    
    BIO_LOG                 = 0x18,
    
    BIO_ADC                 = 0x1A,
    BIO_DISCONNECT_REQ      = 0x1B,
	BIO_TBEACONSCAN_RESULT  = 0x1C,
	BIO_RST_MCU             = 0x1D,
	BIO_SET_PIN_LEVEL		= 0x1E,
	
    BIO_GET_SECONDBOOT      = 0x3C,
}MSG_CMD_BIO;

typedef enum{
    NOTIFY_PKE              = 0,
    NOTIFY_DEFEND_ON        = 1,
    NOTIFY_DEFEND_OFF       = 2,
    NOTIFY_FINDME           = 3,
    NOTIFY_START            = 4,
    NOTIFY_CONNECTED        = 5,
    NOTIFY_DISCONNECTED     = 6,
    NOTIFY_GET_SCAN_YSIG    = 7,
    NOTIFY_NON_SCAN         = 8,
    NOTIFY_GET_SCAN_YBRA    = 9,
    NOTIFY_STACKRESTART     = 10,
} BLE_EVENT_NOTIFY;

typedef enum
{
    //pke func
    PKE_KEY_DEFAULT     = 0x00,
    PKE_KEY_1           = 0x01,
    PKE_KEY_2           = 0x02,
    PKE_KEY_3           = 0x03,
    PKE_KEY_4           = 0x04,
    
    //connect
    PKE_CONNNECT_SET    = 0x05,
    PKE_CONNNECT_BREAK  = 0x06,
    PKE_FUNC_ERROR,
}ENUM_PKEKEY_FUNC_NUM;

  
typedef enum{
  CHECK_SUM_ERR   = 0x03,
  CMD_NOT_EXIST,
  IO_ST_ERR,//data结构错误
  IO_PARAM_ERR,//IO参数错误
  IO_TIMER_BUSY//IO设置繁忙
      
}ERR_CODE;

typedef enum
{
    PROTOCOL_XIAOAN    = 0,
    PROTOCOL_XL        = 1,

}ENUM_BLE_PROTOCOL_TYPE;

typedef struct
{
    uint8_t macAddr[6];
    uint8_t name[9];
    uint8_t meanufData[15];
    uint8_t userID[16];
}__attribute__((__packed__))ST_MSG_BLE_CONFIG_YOUON_ADV;


typedef struct
{
    uint8_t sw;
}__attribute__((__packed__))ST_MSG_CAR_STATE;


typedef struct {
    uint8_t  name[15];
    uint8_t  imei[15];
}__attribute__((__packed__))BLE_CONFIG_PARAM;

typedef struct {
    uint32_t version;
}__attribute__((__packed__))BLE_VERSION_NUM;

#define BD_ADDR_LEN         6
#define ADV_DATA_LEN        0x1F


typedef struct
{
    uint8_t adv[ADV_DATA_LEN];       //道钉广播内容
    uint8_t mac[BD_ADDR_LEN];        //道钉MAC地址
    uint8_t dbm;                     //信号强度 单位: dBm
} __attribute__((__packed__))beaconInfo_t;

typedef struct
{
    beaconInfo_t highestInfo1SecondsAgo;
    beaconInfo_t highestInfo2SecondsAgo;
    beaconInfo_t highestInfo3SecondsAgo;
    beaconInfo_t highestInfo4SecondsAgo;
    beaconInfo_t highestInfo5SecondsAgo;
} __attribute__((__packed__))beaconStatus_t;

typedef struct{
    uint8_t state;
    beaconInfo_t highestInfo1SecondsAgo; //倒数1秒的最强信号道钉信息
    beaconInfo_t highestInfo2SecondsAgo; //倒数2秒的最强信号道钉信息
    beaconInfo_t highestInfo3SecondsAgo; //倒数3秒的最强信号道钉信息
    beaconInfo_t highestInfo4SecondsAgo; //倒数4秒的最强信号道钉信息
    beaconInfo_t highestInfo5SecondsAgo; //倒数5秒的最强信号道钉信息
}__attribute__((__packed__))ST_BEACON_STATUS;


#define SW_IS_ADV        (0x01 << 0)    // bit 1:蓝牙处于广播模式 0:蓝牙处于扫描模式
#define SW_IS_PKEKEY     (0x01 << 2)    // if !SW_IS_ADV && SW_IS_PKEKEY 车机支持PKE 并且扫描钥匙
#define SW_IS_PKEPHONE   (0x01 << 3)    // if SW_IS_ADV && SW_IS_PKEPHONE 车机支持PKE 并且被手机扫描
typedef struct
{
    uint8_t sw;
    uint8_t name[15];
    uint8_t imei[15];
    uint8_t token[4];
    uint8_t protocol_type;
}__attribute__((__packed__))ST_MSG_BLE_CONFIG;

typedef struct {
    uint8_t  cmd;
    uint8_t  len;
    uint8_t  data[];
}__attribute__((__packed__))BLE_MSG_HEADER;//3个字节

typedef struct {
    
    uint16_t signature;//0xAA55
    uint8_t  address;
    uint8_t  cmd;
    uint8_t  len;
    uint8_t  data[];
}__attribute__((__packed__))MSG_HEADER;//5个字节

#pragma pack(push, 1)
typedef struct{
    uint8_t channel;
    float volMv; //max 65.35v
}__attribute__((__packed__))ST_MSG_ADC;
#pragma pack(pop)

typedef struct {
    uint16_t  ioStatus;
}__attribute__((__packed__))ST_IO_STATUS;//2个字节


#define MSG_HEADER_LEN (sizeof(MSG_HEADER))

typedef struct {
    
    uint8_t signature;//0x3A
    uint8_t  address;
    uint8_t  cmd;
    uint8_t  len;
    uint8_t  data[];
}__attribute__((__packed__))MSG_HEADER_YAX;//4个字节

typedef struct {
    uint8_t err;
}ERR_ST;

typedef struct {
    uint8_t code;
    uint8_t checkSum;
}RETURN_ST;


void uart1_router(const uint8_t * data, uint16_t length);
bool uart_isCheckSumPass(MSG_HEADER *msg);

#endif

