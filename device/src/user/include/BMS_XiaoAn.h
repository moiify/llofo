#ifndef __USER_XIAOANBMS_H__
#define __USER_XIAOANBMS_H__

#define XIAOAN_BMS_ADDRESS   0x01 //小安BMS通信地址

enum
{
    XIAOAN_BMS_GET_LASTERROR           = 0x00,//获取最后一次错误代码
    XIAOAN_BMS_HEART                   = 0x0A,//BMS心跳
    XIAOAN_BMS_SET_FUNC                = 0x0B,//设置BMS的功能开关
    XIAOAN_BMS_SET_OUT_ELEC_SWITCH     = 0X0C,//设置放电开关
    XIAOAN_BMS_SET_STORE_MODE          = 0X0F,//设置存储模式
    XIAOAN_BMS_SET_INPUT_MOS           = 0X11,//充电MOS控制
    XIAOAN_BMS_SET_OUTPUT_MOS          = 0X12,//放电MOS控制
    XIAOAN_BMS_GET_BMS_BASE_INFO       = 0X15,//查询BMS基本数据
    XIAOAN_BMS_GET_BMS_RETIME_INFO     = 0X16,//查询BMS实时数据
    XIAOAN_BMS_START_UPDATE            = 0X17,//开始升级
    XIAOAN_BMS_SENDFILE                = 0X18,//发送升级文件
    XIAOAN_BMS_STOP_UPDATE             = 0X19,//结束升级
};

#pragma pack(push, 1)

typedef struct
{
    short signature;
    uint8_t address;
    uint8_t cmd;
    uint8_t length;
    uint8_t data[];
} __attribute__((__packed__)) MSG_HEADER_XIAOAN_BMS;

typedef struct
{
    //BMS基础信息
    u8 protocolVer;     //协议版本号
    u8 manufacturer[16];//厂商名称
    u8 model[16];       //BMS型号
    u16 hardwareVer;    //BMS硬件版本号
    u16 softwareVer;    //BMS软件版本号
    u8 SN[16];          //电池SN号
    u8 gpsId[16];       //GPS编码
    u16 capacity;       //电池满充容量
    u16 cycleCount;     //循环次数
}__attribute__((__packed__)) XIAOAN_BMS_BASE_DATA;
typedef struct
{
    //BMS实时信息
    u8 protocolVer;     //协议版本号
    u16 voltage;        //总电压(mV)
    s32 current;        //总电流(mA)
    u8 MOSTemperature;  //MOS管温度
    s8 temperature1;    //电池包第一路温度
    s8 temperature2;    //电池包第二路温度
    u16 cellVoltageMax; //单体电池最大电压
    u16 cellVoltageMin; //单体电池最小电压
    u16 cellVoltageDIF; //单体电压压差
    u16 fault;          //故障标志位
    u8 mosfetState;     //电池状态
    u8 SOC;             //电池剩余容量百分比(1%)
    u16 remainCapacity; //电池剩余容量(mAH)
}__attribute__((__packed__)) XIAOAN_BMS_RETIME_DATA;

typedef struct
{
    u16  bms_version;
    u32  g_bmsFirmwareDataBytes;
} __attribute__((__packed__))XIAOAN_BMS_START_OTA;

typedef struct
{
    u16 pageID;
} __attribute__((__packed__))XIAOAN_BMS_pageID;

typedef struct
{
    u8 isRevSuccess;
} __attribute__((__packed__))XIAOAN_BMS_ISSUCCESS;

typedef struct
{
    u8  canUpgrade;
    u16 size;
} __attribute__((__packed__))XIAOAN_BMS_START_OTA_RSP;

#pragma pack(pop)

#define MSG_HEADER_XIAOAN_BMS_LEN sizeof(MSG_HEADER_XIAOAN_BMS)

void BMS_XiaoAn_Initial(void);
int  BMS_XiaoAn_LoopGetData(void);
void BMS_XiaoAn_OTAStart(void);
void BMS_XiaoAn_OTARealData(void);
void BMS_XiaoAn_OTAComplete(void);

#endif//__USER_DA14580_XHBMS_H__

