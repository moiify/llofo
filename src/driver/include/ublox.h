/* Copyright (C) Xiaoan Technology Co., Ltd - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Tom Chiang <jiangtao@xiaoantech.com>, Feb 2017
 *
 * ublox.h
 *
 * ublox模块消息定义
 */

#ifndef __USER_GPS_UBLOX_H__
#define __USER_GPS_UBLOX_H__

#include "stdint.h"

#pragma pack(push, 1)

//! Header prepended to ubx binary messages
#define HDR_CHKSM_LENGTH 8 //(includes "sync1 sync2 classid msgid length checksum")
#define UBX_SYNC_BYTE_1 0xB5
#define UBX_SYNC_BYTE_2 0x62
    
//! UBX Protocol Class/Message ID's
#define MSG_CLASS_ACK 0X05
    #define MSG_ID_ACK_ACK 0x01
    #define MSG_ID_ACK_NAK 0x00
    
#define MSG_CLASS_AID 0x0B
    #define MSG_ID_AID_ALM 0x30
    #define MSG_ID_AID_ALPSRV 0X32
    #define MSG_ID_AID_ALP 0x50
    #define MSG_ID_AID_AOP 0x33
    #define MSG_ID_AID_DATA 0x10
    #define MSG_ID_AID_EPH 0x31
    #define MSG_ID_AID_HUI 0x02
    #define MSG_ID_AID_INI 0x01
    #define MSG_ID_AID_REQ 0x00
    
#define MSG_CLASS_CFG 0x06
    #define MSG_ID_CFG_ANT 0X13
    #define MSG_ID_CFG_CNFGR 0x09
    #define MSG_ID_CFG_DAT 0x06
    #define MSG_ID_CFG_EKF 0x12
    #define MSG_ID_CFG_ESFGWT 0x29
    #define MSG_ID_CFG_FXN 0x0E
    #define MSG_ID_CFG_ITFM 0x39
    #define MSG_ID_CFG_MSG 0x01
    #define MSG_ID_CFG_NAV5 0x24
    #define MSG_ID_CFG_NAVX5 0x23
    #define MSG_ID_CFG_NMEA 0x17
    #define MSG_ID_CFG_NVS 0x22
    #define MSG_ID_CFG_PIO 0x2C
    #define MSG_ID_CFG_PM2 0x3B
    #define MSG_ID_CFG_PM 0x32
    #define MSG_ID_CFG_PRT 0x00
    #define MSG_ID_CFG_RATE 0x08
    #define MSG_ID_CFG_RINV 0x34
    #define MSG_ID_CFG_RST 0x04
    #define MSG_ID_CFG_RXM 0x11
    #define MSG_ID_CFG_SBAS 0x16
    #define MSG_ID_CFG_TMODE2 0x3D
    #define MSG_ID_CFG_TMODE 0x1D
    #define MSG_ID_CFG_TP5 0x31
    #define MSG_ID_CFG_TP 0x07
    #define MSG_ID_CFG_USB 0x1B
    
#define MSG_CLASS_ESF 0x10
    #define MSG_ID_ESF_MEAS 0x02
    #define MSG_ID_ESF_STATUS 0x10
    
#define MSG_CLASS_INF 0x04
    #define MSG_ID_INF_DEBUG 0x04
    #define MSG_ID_INF_ERROR 0x00
    #define MSG_ID_INF_NOTICE 0x02
    #define MSG_ID_INF_TEST 0x03
    #define MSG_ID_INF_WARNING 0x01
    
#define MSG_CLASS_MON 0x0A
    #define MSG_ID_MON_HW2 0x0B
    #define MSG_ID_MON_HW 0x09
    #define MSG_ID_MON_IO 0x02
    #define MSG_ID_MON_MSGPP 0x06
    #define MSG_ID_MON_RXBUF 0x07
    #define MSG_ID_MON_RXR 0x21
    #define MSG_ID_MON_TXBUF 0X08
    #define MSG_ID_MON_VER 0x04
    
#define MSG_CLASS_NAV 0x01
    #define MSG_ID_NAV_AOPSTATUS 0x60
    #define MSG_ID_NAV_CLOCK 0x22
    #define MSG_ID_NAV_DGPS 0x31
    #define MSG_ID_NAV_DOP 0x04
    #define MSG_ID_NAV_EKFSTATUS 0x40
    #define MSG_ID_NAV_POSECEF 0x01
    #define MSG_ID_NAV_POSLLH 0x02
    #define MSG_ID_NAV_SBAS 0x32
    #define MSG_ID_NAV_SOL 0x06
    #define MSG_ID_NAV_STATUS 0x03
    #define MSG_ID_NAV_SVINFO 0x30
    #define MSG_ID_NAV_TIMEGPS 0x20
    #define MSG_ID_NAV_TIMEUTC 0x21
    #define MSG_ID_NAV_VELECEF 0x11
    #define MSG_ID_NAV_VELNED 0x12
    
#define MSG_CLASS_RXM 0x02
    #define MSG_ID_RXM_ALM 0x30
    #define MSG_ID_RXM_EPH 0x31
    #define MSG_ID_RXM_PMREQ 0x41
    #define MSG_ID_RXM_RAW 0x10
    #define MSG_ID_RXM_SFRB 0x11
    #define MSG_ID_RXM_SVSI 0x20
    
#define MSG_CLASS_TIM 0x0D
    #define MSG_ID_TIM_SVIN 0x04
    #define MSG_ID_TIM_TM2 0x03
    #define MSG_ID_TIM_TP 0x01
    #define MSG_ID_TIM_VRFY 0x06

typedef struct
{
    uint8_t sync1;   //!< start of packet first byte (0xB5)
    uint8_t sync2;   //!< start of packet second byte (0x62)
    uint8_t message_class; //!< Class that defines basic subset of message (NAV, RXM, etc.)
    uint8_t message_id;     //!< Message ID
    uint16_t payload_length; //!< length of the payload data, excluding header and checksum
} __attribute__((__packed__))UbloxHeader;

///////////////////////////////////////////////////////////
// Configuration Messages
///////////////////////////////////////////////////////////
/*!
 * CFM-MSG Message Structure
 * This message requests a specifiable message at a given rate.
 * ID: 0x06  0x01 Payload Length=3 bytes
 */
typedef struct
{
    UbloxHeader header;     //!< Ublox header
    uint8_t message_class;  //!< class of message to request
    uint8_t message_id;     //!< id of message to request
    uint8_t rate;           //!< rate message will be sent
    uint8_t checksum[2];
} __attribute__((__packed__))CfgMsgRate;

/*!
 * CFM-MSG Message Structure
 * This message requests a message once.
 * ID: 0x06  0x01 Payload Length=2 bytes
 */
typedef struct
{
    UbloxHeader header;     //!< Ublox header
    uint8_t message_class;  //!< class of message to request
    uint8_t message_id;     //!< id of message to request
    uint8_t checksum[2];
} __attribute__((__packed__))CfgMsg;

/*!
 * CFG-CFG Message Structure
 * This message clears, saves, or loads novalitle memory.
 * Set masks to 0x061F to clear, save, or load all values.
 * ID: 0x06  0x09 Payload Length=12 bytes
 */
typedef struct
{
    UbloxHeader header;     //!< Ublox header
    uint32_t clear_mask;  //!< clear mask
    uint32_t save_mask;     //!< save mask
    uint32_t load_mask;           //!< load mask
    uint8_t checksum[2];      //!< Checksum
} __attribute__((__packed__))CfgCfg;

/*
 * CFG-PIO Message Structure
 */
#define REQ_EXIT_TEST           0
#define REQ_SET_PIN             1
#define REQ_EXTERNAL_NODRIVE    2
#define REQ_EXTERNAL_DRIVE      3

typedef enum
{
    UBLOX_PIN_UNALTERED     = 0,
    UBLOX_PIN_FLOATING      = 1,
    UBLOX_PIN_PULLED_DOWN   = 2,
    UBLOX_PIN_PULLED_UP     = 3,
    UBLOX_PIN_DRIVEN_HIGH   = 4,
    UBLOX_PIN_DRIVEN_LOW    = 5,
    UBLOX_PIN_INVESIGATE    = 6,
} ENUM_UBLOX_PIN_STATE;
    
#define MAX_PIO_NUMBER  17

typedef struct
{
    UbloxHeader header;     //!< Ublox header
    uint8_t version;    //always 0
    uint8_t request;    //0: EXIT-TEST; 1: SET-PIN; 2:EXTERNAL-NODRIVE; 3: EXTERNAL-DRIVE
    uint8_t pio[MAX_PIO_NUMBER];    //One value per PIO pin
    uint8_t checksum[2];      //!< Checksum
} __attribute__((__packed__))CfgPio;

/*!
 * CFM-RST Message Structure
 * This message allows a receiver to be reset.
 * ID: 0x06  0x04 Payload Length=4 bytes
 */
 
 typedef struct
 {
     UbloxHeader header;     //!< Ublox header
     uint16_t nav_bbr_mask;  //!< Nav data to clear: 0x0000 = hot start, 0x0001 = warm start, 0xFFFF=cold start
     uint8_t  reset_mode;     //!< Reset mode
     uint8_t  reserved;       //!< reserved
     uint8_t checksum[2];
 } __attribute__((__packed__))CfgRst;


/*!
 * CFM-PRT Message Structure
 * This message configures a USART or USB port.
 * Use to specify input/output protocols to use
 * ID: 0x06  0x00 Payload Length=20 bytes
 */
 #define PROTO_MASK_UBX 1
 #define PROTO_MASK_NMEA    1 << 1
 #define PROTO_MASK_RTCM    1 << 2
 typedef struct
 {
     UbloxHeader header;     //!< Ublox header
     uint8_t port_id; //!< port identifier (0 or 1 for USART or 3 for USB)
     uint8_t reserved0; //!< reserved
     uint16_t txReady; //!< transmit ready status
     uint32_t mode; 
     uint32_t baudRate; 
     uint16_t inProtoMask; //!< input protocol mask
     uint16_t outProtoMask; //!< output protocol mask
     uint16_t flags; 
     uint16_t reserved5; //!< reserved
     uint8_t checksum[2];
 } __attribute__((__packed__))CfgPrt;

/*!
* CFG-NAV5 Message Structure
* This message configures Navigation algorithm
* parameters.
* ID: 0x06  0x24 Payload Length=36 bytes
*/
typedef struct
{
    UbloxHeader header;     //!< Ublox header
    uint16_t mask; //!< parameters bitmask (only masked params applied)
    uint8_t dynamic_model; //!< dynamic platform
    uint8_t fix_mode; //!< positioning fix mode
    int32_t fixed_altitude; //!< (scale .01) (m)
    uint32_t fixed_altitude_variance; //!< (scale .0001) (m^2)
    int8_t min_elevation; //!< (deg)
    uint8_t dead_reckoning_limit; //!< max time to perform DR w/out GPS (sec)
    uint16_t pdop; //!< (scale .1)
    uint16_t tdop; //!< (scale .1)
    uint16_t pos_accuracy_mask; //!< (m)
    uint16_t time_accuracy_mask; //!< (m)
    uint8_t static_hold_threshold; //!<
    uint8_t dgps_timeout; //!<
    uint8_t cnoThreshNumSVs; //!Number of satellites required to have C/N0 above cnoThresh for a fix to be attempted
    uint8_t cnoThresh;  //C/N0 threshold for deciding whether to attempt a fix
    uint16_t  reserved2; //!< reserved (always set to zero)
    uint32_t reserved3; //!< reserved (always set to zero)
    uint32_t reserved4; //!< reserved (always set to zero)
    uint8_t checksum[2];
} __attribute__((__packed__))CfgNav5;

/*!
* CFG-SBAS Message Structure
* This message configures the SBAS receiver 
* subsystem (i.e. WAAS, EGNOS, MSAS).
* TYPE: POLL(empty payload) and COMMAND
* ID: 0x06  0x16 Payload Length=8 bytes
*/
typedef struct
{
    UbloxHeader header;     //!< Ublox header
    uint8_t mode;
    uint8_t usage;
    uint8_t maxSBAS;        //< (0-3)
    uint8_t scanmode2;      //< =0 for autoscan
    uint32_t scanmode1;     //< =0 for autoscan
    uint8_t checksum[2];
} __attribute__((__packed__))CfgSbas;

typedef struct
{
    UbloxHeader header;     //!< Ublox header
    uint8_t filter;
    uint8_t nmeaVersion;
    uint8_t numSV;
    uint8_t flags;
    uint32_t gnssToFilter;
    uint8_t svNumbering;
    uint8_t mainTalkerId;
    uint8_t gsvTalkerId;
    uint8_t reserved;
    uint8_t checksum[2];
} __attribute__((__packed__))CfgNMEA;

#pragma pack(pop)

typedef enum
{
    UBLOX_DYNAMIC_MODLE_PORTABLE      = 0,  //便携式
    UBLOX_DYNAMIC_MODLE_STATIONNARY   = 2,  //静止
    UBLOX_DYNAMIC_MODLE_PEDESTRIAN    = 3,  //步行
    UBLOX_DYNAMIC_MODLE_AUTOMOTIVE    = 4,  //车载
    UBLOX_DYNAMIC_MODLE_SEA           = 5,  //航行
    UBLOX_DYNAMIC_MODLE_AIRBORNE_1    = 6,  //热气球 < 1g
    UBLOX_DYNAMIC_MODLE_AIRBORNE_2    = 7,  //热气球 < 2g
    UBLOX_DYNAMIC_MODLE_AIRBORNE_4    = 8,  //热气球 < 4g
    UBLOX_DYNAMIC_UNSET               = 99, //自定义未设置时的初始值
} UBLOX_DYNAMIC_MODLES;

typedef enum
{
    GPS_FIX_NOT_VALID                 = 0,  //无定位
    GPS_FIX                           = 1,  //单点定位
    GPS_DGPS                          = 2,  //差分定位
    GPS_INVALID_PPS                   = 3,  //无效PPS
    GPS_RTK_FIX                       = 4,  //实时差分定位（获得固定解）
    GPS_RTK_FLOAT                     = 5,  //实时差分定位（浮点解）
    GPS_ESTIMATING                    = 6,  //正在估算
}GPS_STATE;

typedef enum
{
    GPS_COLDRESTART                   = 0, //冷重启
    GPS_USERRESTART                   = 1, //用户自定义重启
    GPS_HOTRESTART                    = 2, //热重启
    GPS_UPDATECONFIG                  = 3, //刷新模块配置信息
}GPS_RESET_MODE;

typedef void (*PORT_WRITER)(void* msg, unsigned short length);

void Ublox_init(PORT_WRITER);
void Ublox_gotoAwake(void);
void Ublox_gotoSleep(void);
void Ublox_hotRestart(void);
void Ublox_coldRestart(void);
void Ublox_initNMEAConfig(void);
void Ublox_initNMEAConfig_7020(void);
void Ublox_configGNSS(void);
void ublox_getGPS_Speed(double *speed);
void Ublox_setModel(UBLOX_DYNAMIC_MODLES model);
void Ublox_setModelACK(UBLOX_DYNAMIC_MODLES model);
UBLOX_DYNAMIC_MODLES Ublox_getExpectMode(void);

int Ublox_M8U_reset_state(void);
int Ublox_M8U_cal_hnr(void);
void Ublox_M8U_config(void);
void Ublox_M8U_enableMonHW(void);
void Ublox_M8U_enableATT(void);
void Ublox_M8U_enablePVT(void);
void Ublox_M8U_setHNROutputRate(void);
void Ublox_M8U_setHNRmsg(void);
void Ublox_M8U_procUbloxMsg(u8 *msg, s16 len);
int Ublox_M8U_state_handle(void);
void Ublox_M8U_baudrate_handle(PORT_WRITER uart_writer);
void Ublox_M8U_userReset(void);
int Ublox_checkVersion_cb(void);
int Ublox_isPollACK(u8 *nmea_str, u16 length);

#endif //__USER_GPS_UBLOX_H__
