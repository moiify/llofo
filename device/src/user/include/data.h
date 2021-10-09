/*
 * data.h
 *
 *  Created on: 2020/04/09
 *      Author: lc
 */

#ifndef USER_ELECTROMBILE_DATA_H_
#define USER_ELECTROMBILE_DATA_H_

#include "stdint.h"

#include "nmea/info.h"

#include "types.h"
#include "fence.h"
#include "protocol.h"
#include "setting.h"

#define MAX_BMS_SN_LEN 32
#define MAX_STC_ID_LEN (7)
#define BATTERY_NUM 13
#define MAX_BARCODE_LEN (32)

typedef struct
{
    short header;
    u8 Class;
    u8 id;
    u16 length;
}__attribute__((__packed__))UBLOX_HEAD_DATA;

typedef struct
{
    UBLOX_HEAD_DATA head;
    u32 iTOW;
    u8 version;
    u8 reservedl[3];
    s32 roll;
    s32 pitch;
    s32 heading;
    u32 accRoll;
    u32 accPitch;
    u32 accHeading;
    u16 checksum;
}__attribute__((__packed__))UBLOX_ATTITUDE_DATA;

typedef struct
{
    UBLOX_HEAD_DATA head;
    u32 iTOW;
    u16 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 min;
    u8 sec;
    u8 valid;
    u32 tAcc;
    int nano;
    u8 fixType;
    s8 flags;
    s8 flags2;
    u8 numSV;
    s32 lon;
    s32 lat;
    s32 height;
    s32 hMSL;
    u32 hAcc;
    u32 vAcc;
    s32 velN;
    s32 velE;
    s32 velD;
    s32 gSpeed;
    s32 headMot;
    u32 sAcc;
    u32 headAcc;
    u16 pDOP;
    u8 reserved1[6];
    s32 headVeh;
    s16 magDec;
    u16 magAcc;
}__attribute__((__packed__))UBLOX_FIX_DATA;

typedef struct
{
    UBLOX_HEAD_DATA head;
    u32 iTOW;
    u16 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 min;
    u8 sec;
    s8 valid;
    s32 nano;
    u8 gpsFix;
    s8 flags;
    u8 reserved1[2];
    s32 lon;
    s32 lat;
    s32 height;
    s32 hMSL;
    s32 gSpeed;
    s32 speed;
    s32 headMot;
    s32 headVeh;
}__attribute__((__packed__))UBLOX_HNR_DATA;

typedef struct
{
    UBLOX_HEAD_DATA head;
    s32 pinSel;
    s32 pinBank;
    s32 pinDir;
    s32 pinVal;
    u16 noisePerMS;
    u16 agcCnt;
    u8 aStatus;
}__attribute__((__packed__))UBLOX_MON_HW_DATA;

typedef enum
{
    DIR_NOT_FIX = 0,        //未定位/未校准
    DIR_INS_STATUS = 1,     //纯惯导状态
    DIR_2D_FIX = 2,         //2D-fix
    DIR_3D_FIX = 3,         //3D-fix
    DIR_DR_STATUS = 4,      //GNSS下惯导状态
    DIR_STATIC_FIXED = 1,   //已校准（静止状态或不带控制器速度的校准）
    DIR_DYNAMIC_FIXED = 4,  //已校准（带控制器速度的校准状态）
} DIR_MODE;

typedef enum
{
    DEGREE_MATCH        = 0, //角度匹配
    DEGREE_OUT_OF_RANGE = 1, //角度超出范围
    DEGREE_NOT_FIXED    = 2, //设备未进惯导
}DEGREE_MODE;

typedef enum
{
    POSE_Z,
    POSE_Y,
    POSE_X
} POSE_enum;

typedef struct
{
    float lat;
    float lon;   
}LBS_INFO;

typedef struct
{
    short mcc;   //mobile country code
    short mnc;   //mobile network code
    char  cellNo;// cell count
    CELL  cell[MAX_CELL_NUM];
}CELL_INFO;      //Cell Global Identifier

typedef enum
{
    NORMAL_MODE = 0,
    CHECK_MODE = 1,
} WORK_MODE;//工作模式，正常模式和测试模式

typedef struct
{
    u8  isCLBS;
    LBS_INFO lbsInfo;
    u32 lbsTimestamp;

    u8   isCell;
    CELL_INFO cellInfo;
    u32  cellTimestamp;
    
    u8  isGPS;
    u32 timestamp;
    nmeaINFO nmeaInfo;

    u32 tagTimestamp;
    nmeaINFO tagNmeaInfo;
}POSITION;

typedef struct
{
    u32 holdtime;
    u8  isBLEConnected;
    
    u32 version;
    u8  isBooting;
    u8  isDA14580Alive;
    u8  missHeartbeatCount;
} ST_BLE_STATE;

typedef struct
{
    u8 ratio;
    u8 version;
    u8 current;
    u8 voltage;
    u8 status1;
    u8 status2;
    u8 function;
    u8 protocolVer;
    u8 manufacturer;
    
    u16 fault;
    u32 errorCode;

    u8 type;
    u8 speed;
    u32 pulse;
    u32 voltage_mV;
    u32 current_mA;
    u32 limitCurrent_mA;
    u32 protectVoltage_mV;
    u32 timestamp;

    u16 hw;//硬件版本号
    u16 sw;//软件版本号
    u16 sn[20];//串号12位，末位补0
    
    //通过ETC获取的BMS信息
    u8  soc;
    u8  soh;
    u16 capacity;
    u16 cycle;
    s8  batTemp;
    u16 bmsFault;
    
    u8 isPulseWork;
} ETC;

#define MANUFACTURER_LEN 16
typedef struct
{
    //BMS状态
    u32 lastErrorCode;   //最后一次错误码
    u8  funcSwitch;      //功能开关
    u8  elecSwitch;      //放电开关
    u8  inputMosSwitch;  //充电MOS开关控制
    u8  outputMosSwitch; //放电MOS开关控制
    
    //BMS基础信息
    u8  protocolVer;     //协议版本号
    u8  manufacturer[MANUFACTURER_LEN];//厂商名称
    u8  model[16];       //BMS型号
    u16 hardwareVer;     //BMS硬件版本号
    u16 softwareVer;     //BMS软件版本号
    u8  SN[MAX_BMS_SN_LEN]; //电池SN号
    u8  gpsId[16];       //GPS编码
    u16 capacity;        //电池满充容量
    u16 cycleCount;      //循环次数

    //BMS实时信息
    u16 voltage;         //总电压(mV)
    s32 current;         //总电流(mA)
    s16 temperature;     //电池温度(0.1℃)
    u8  health;          //健康状态
    s8  MOSTemperature;  //MOS管温度
    s8  temperature1;    //电池包第一路温度
    s8  temperature2;    //电池包第二路温度
    u16 cellVoltageMax;  //单体电池最大电压
    u16 cellVoltageMin;  //单体电池最小电压
    u16 cellVoltageDIF;  //单体电压压差
    u16 fault;           //故障标志位
    u8  mosfetState;     //电池状态
    u8  SOH;             //电池健康状态
    u8  SOC;             //电池剩余容量百分比(1%)
    u16 remainCapacity;  //电池剩余容量(mAH)
    u16 relativeCapity;  //相对容量(mAH)
    u16 absoluteCapity;  //绝对容量(mAH)
    s8  HighestTemperature;
    s8  LowestTemperature;
    u8  switchState;     //充电开关状态
    u32 timestamp;       //BMS信息采集点时间戳

    u8  getSocTimes;
    u8  sendSocFaultTimes; 
}BMS;

//蓝牙道钉信息
typedef struct
{
    u8 event;       				   //道钉状态
    u8 tBeaconAddr[6];                 //道钉蓝牙mac地址                  
    u8 tBeaconID[12 + 1];              //站点编号
    u8 tBeaconNum;                     //站点数量
    u8 tBeaconPileNum;                 //桩位编号
    u8 tBeaconSignalThreshold;         //信号限制
    u8 tBeaconSOC;                     //信号限制
    u8 tBeaconVersion[2 + 1];          //版本
    double lat;
    double lon;                        //扫到道钉时候的经纬度
    u32 timestamp;                     //扫描时间戳
    int rssi;						   //道钉信号强度
}TBEACON_INFO_DATA;

//蓝牙道钉信息
typedef struct
{
    u8 tBeaconID[12 + 1];              //站点编号
    u8 tBeaconNum;                     //站点数量
    u8 tBeaconPileNum;                 //桩位编号
    u8 tBeaconSignalThreshold;         //信号限制
    u8 tBeaconSOC;                     //道钉剩余电量
    u8 tBeaconVersion[2 + 1];          //道钉版本
    
    uint8_t mac[6];                     //道钉MAC地址
    uint8_t dbm;                        //信号强度 单位: dBm
} beaconInfo_t;

typedef struct
{
    beaconInfo_t highestInfoNSecondsAgo[5];
} beaconStatus_t;


typedef struct
{
    u8 event;       				   //道钉状态
    u8 tBeaconAddr[6];                 //道钉蓝牙mac地址                  
    u8 tBeaconID[12 + 1];              //站点编号
    u8 tBeaconNum;                     //站点数量
    u8 tBeaconPileNum;                 //桩位编号
    u8 tBeaconSignalThreshold;         //信号限制
    u8 tBeaconSOC;                     //信号限制
    u8 tBeaconVersion[2 + 1];          //版本
    double lat;
    double lon;                        //扫到道钉时候的经纬度
    u32 timestamp;                     //扫描时间戳
    int rssi;						   //道钉信号强度
}TBEACON_INFO;


typedef struct
{
    u8 isRead;     //是否读取到数据
    short x_data;
    short y_data;
    short z_data;
    short pitch; //俯仰角
    short roll; //横滚角
    short yaw; //偏航角
}ACCELEROMETER_DATA;//加速度计数据

typedef struct  
{
    bool isEtcRsp; 		//ETC是否应答标志
    bool isBmsRsp;		//BMS是否应答标志
    bool EtcComm; 	    //ETC通信标志
    bool BmsComm;	    //BMS通信标志
    bool isDelayCheckAccState;//开关电门acc延迟检测，避免误判
    bool isRFIDRsp;     //RFID是否应答标志
    u8 etcSendNoRspTimes; //控制器无应答次数
    u8 bmsSendNoRspTimes; //BMS无应答次数
    u8 rfidSendNoRspTimes; //RFID无应答次数
    u8 accFaultSendTimes; //故障上报计数
    u8 bmsFaultSendTimes;
    u8 etcFaultSendTimes;
    u8 bmsComFaultSendTimes;
    u8 etcComFaultSendTimes;
    u8 acceleraFaultSendTimes;
    u8 rfidComFaultSendTimes;
}FAULT_RECORD_DATA;

typedef struct
{
    u64 pkts_sent;
    u64 bytes_sent;
    u64 pkts_acked;
    u64 bytes_acked;
    u32 conn_success;
    u32 conn_fail;
    u32 conn_close;
}SocketStatistics;

typedef enum 
{
    KICK_TYPE_NONE          = 0,
    KICK_TYPE_MAG           = 1,
    KICK_TYPE_RFID          = 2,
    KICK_TYPE_MAG_AND_RFID  = 3
} Kick_Tpye_e;

typedef struct
{
    u8 isMoving;
    u8 isNewGPS;
    u8 isShaking;
    u8 isLogined;
    u8 isSleeping;
    u8 isChangeUrl;
    u8 isOutOfPoly;
    u8 isUrlUpdated;
    u8 isOpidUpdated;
    u8 isWheelSpinning;
    u8 isAccelerateFault;
    u8 isAccelerometerFault;
    u8 isAccelerateInitFault;
    u8 mode; //工作模式：正常0, 省电1 休眠2 [默认0]
    WORK_MODE workMode;
    u8 isCheckSPK; //是否通过AD检测喇叭
    
    FENCE *fence;
    POSE_enum pose;
    POSITION  lastPosition;
    u32  vehicleBattery_mV;
    u32  smallBattery_mV;
    u32  staticBikeBat_mV;
    u8 voltageState;
    u32 iMiles;
    u32 awakeTime;
    u32 staticTime;
    u32 tsSendState;        // 上一次发送状态的时间戳
    u32 carStaticTime;
    u32 cnt_vibration;
    u32 speedCountTime;
    u32 lastSyncTimestamp;
    u32 vibrationTime;
    u16 vibration_level;    // 震动等级
    u8  heartBeatLostTimes;
    u32 gpsSendPeriod_ms;
    s32 angle; 
    u8  shaketimes;
    u8  isTurnoverChange;
    u8  buckstate;
    
    u8  checkCSQ;       //自检:信号强度
    u8  checkSimcard;	//自检:卡状态
    u8  checkVolt;		//自检:模组电压
    u8  checkAccel;		//自检:加速度计
    u8  checkBle;		//自检:蓝牙模块

    s16 malloctimes;    //测试用
    u16 ATtimeout;      //测试用
    u8 AT_blockCMD[20]; //测试用
    
    u8 blePortData;
    u8 gpsPortData;

    u8 socFluct;
    u8 socWait;
    u8 isWaitingTBeaconResult;
    ST_BLE_STATE ble_state;

    u16 ecuFault;
    ETC etc;
    BMS bms;//BMS

    TBEACON_INFO_DATA tBeaconInfo;
    beaconStatus_t tBeaconStatus;
    
    ACCELEROMETER_DATA acceleromterData;
    FAULT_RECORD_DATA faultRecord;     //整车故障上报记录

    SocketStatistics socstate;
    s8 isSocketConnect;

    u8  ble_workMode;
    u16 gps_parseFilter;
    u16 gps_statusFilter;

    L_BOOL ublox_setModeACK;

    u32 accHeading; //M8U方向因子
    float headingAngle;//定向停车系列产品方向角（小数格式）
    u16 agcCnt; //M8U天线增益参数
    u8 resetFixnum; //M8U异常退出惯导次数
    u8 fixtype; //定向停车校准状态类型（M8U定向方案：0 = 未定位，1 = 纯惯导，2 = 2D-fix，3 = 3D-fix，4 = GNSS下惯导状态; MPU6500定向方案：0 = 未校准，1 = 已校准）

    u8 gpsPrns[12];
    u8 gpsSigs[12];

    u8 isRFIDPowerOn;
    u8 cardID[17];
    u8 RFIDVersion[12];
    s16 RFID_ErrorCode;
    u8 cardIDlen;
    u8 isCardIdLegal;
    u8 isRFIDConnect;
    u8 isStopRFIDAudio;
    u8 isKickMeet;
    u8 isKickUse;
    u8 kickType;
    L_BOOL isBleBootDown;
    u8 fenceAreaType;
    u8 isHelmetLocking; //六线头盔锁正在关锁标志位
    u8 isReadyToSleep; //即将进入休眠模式标志位
    u8 isWheelSpinConti; //在开电门后是否发生过2秒连续轮动
    u8 isPulseUsable; //从控制器读取的霍尔值是否可用
    u8 isReadRFIDVersion; //是否获取一次RFID的版本号
    u8 isPowerChangeComplete; //是否换电真实完成
} DATA;

DATA *data_getData(void);

POSITION* data_getPosition(void);
void data_savePosition(POSITION* pos);

void data_minusAwakeTime(void);
void data_setAwakeTime(u32 time_s);
u32 data_getAwakeTime(void);
u8 data_isTime2Sleep(void);

void data_addVivrationTime(void);
void data_resetVibrationTime(void);
u32 data_getVibrationTime(void);
u8 data_getBMSSOC(void);

u8 data_isSleeping(void);
void data_setSleepState(u8 state);
u8 data_isLogined(void);
void data_setAccelerometerFault(L_BOOL sw);
L_BOOL data_getAccelerometerFault(void);
void data_setMovedState(u8 state);
u8   data_GetMoveState(void);

float HALL2SPEED(u32 pulse);
u8 data_getRealEtcSpeed(void);
s16 data_getHeadingAngle(void);
u8 data_isHeadingAngleFixed(void);

beaconInfo_t *data_getTBeaconInfo(int limitTime);

L_BOOL data_isInNight(u8 night, u8 day);

#endif /* USER_ELECTROMBILE_DATA_H_ */

