#ifndef __USER_XIAOANETC_H__
#define __USER_XIAOANETC_H__

#define XIAOAN_ETC_ADDRESS   0x10//小安ETC通信地址
#define ETC_MANUFACTURER_JF  0x06//金丰控制器厂商代码

enum
{
    XIAOAN_GET_ETC_LASTERROR           = 0x00,//获取最后一次错误代码
    XIAOAN_GET_ETC_INFO                = 0x11,//获取控制器信息
    XIAOAN_SET_ETC_SPEED               = 0x12,//修改控制器最高时速
    XIAOAN_SET_ETC_PROTECTION_VOLTAGE  = 0x13,//修改控制器欠压保护值
    XIAOAN_SET_ETC_LIMIT_CURRENT       = 0x14,//修改控制器限流值
    XIAOAN_SET_ETC_SLOWSTART           = 0x15,//修改控制器是否缓启动
    XIAOAN_SET_ETC_LIGHT               = 0x16,//设置控制器大灯控制
    XIAOAN_SET_ETC_ACC                 = 0x17,//打开ACC
    XIAOAN_SET_ETC_FUNC                = 0x18,//设置控制器的功能开关
    XIAOAN_SET_ETC_DEFEND              = 0x19,//防盗开关
    XIAOAN_SET_ETC_UPGRADE_START       = 0x1A,//升级开始
    XIAOAN_SET_ETC_UPGRADE_DATA        = 0x1B,//发送升级数据
    XIAOAN_SET_ETC_UPGRADE_END         = 0x1C,//升级结束
    XIAOAN_SET_ETC_BOOST_RATIO         = 0x1D,//设置控制器助力比
    XIAOAN_SET_ETC_BMS_SOC             = 0x1E,//设置电池SOC
    XIAOAN_GET_ETC_EVENT_INFO          = 0x1F,//查询控制器事件信息
    XIAOAN_SET_ETC_SYNC_TIME           = 0x20,//同步时间
    XIAOAN_SET_ETC_STATE_INFO          = 0x21,//设置状态信息
    XIAOAN_SET_ETC_CTRL_EVENT          = 0x22,//执行控制器操作
	XIAOAN_GET_ETC_SOC                 = 0x23,//从控制器获取SOC
};

#pragma pack(push, 1)

typedef struct
{
    short signature;
    uint8_t address;
    uint8_t cmd;
    uint8_t length;
    uint8_t data[];
} __attribute__((__packed__)) MSG_HEADER_XIAOAN_ETC;

typedef struct
{
    uint8_t type;
    uint16_t voltage_mV;
    uint16_t current_mA;
    uint16_t pulse;
    uint8_t speed_per;
    uint16_t underVoltage_mV;
    uint16_t currentLimiting_mA;
    uint8_t fault;
} __attribute__((__packed__))XIAOAN_ETC_DATA;

typedef struct
{
    uint8_t protocolVer; //协议版本号
    uint8_t manufacturer;//厂商代码
    uint8_t type;        //型号
    uint8_t version;     //控制器软件版本号
    uint16_t voltage;    //0.1V
    uint16_t current;    //0.1A
    uint16_t pulse;      //500ms内电机霍尔数
    uint8_t speed;       //最高转速百分比 限速
    uint8_t fault;       //故障信息
    uint8_t function;    //功能开关
} __attribute__((__packed__))XIAOAN_ETC_DATA_V3;

typedef struct
{
    uint8_t protocolVer; //协议版本号
    uint8_t manufacturer;//厂商代码
    uint8_t type;        //型号
    uint8_t version;     //控制器软件版本号
    uint16_t voltage;    //0.1V
    uint16_t current;    //0.1A
    uint16_t pulse;      //500ms内电机霍尔数
    uint8_t speed;       //实时速度
    uint8_t fault;       //故障信息
    uint8_t function;    //功能开关
    uint8_t ratio;       //助力比
} __attribute__((__packed__))XIAOAN_ETC_DATA_V5;

typedef struct
{
    uint8_t protocolVer; //协议版本号
    uint8_t manufacturer;//厂商代码
    uint8_t type;        //型号
    uint8_t version;     //控制器软件版本号
    uint16_t voltage;    //0.1V
    uint16_t current;    //0.1A
    uint16_t pulse;      //500ms内电机霍尔数
    uint8_t speed;       //实时速度
    uint16_t fault;      //故障信息
    uint8_t function;    //功能开关
    uint8_t ratio;       //助力比
} __attribute__((__packed__))XIAOAN_ETC_DATA_V6;

typedef struct
{
    uint32_t lastError;
} __attribute__((__packed__))XIAOAN_ETC_LAST_ERROR;

typedef struct
{
    uint16_t hw;//硬件版本号
    uint16_t sw;//软件版本号
    uint8_t sn[12];//串号12位，末位补0
} __attribute__((__packed__))XIAOAN_ETC_VERSION;


typedef struct
{
	u8  etc_version;
    u32 etc_firmwareDataBytes;
} __attribute__((__packed__))XIAOAN_ETC_START_OTA;

typedef struct
{
    u16 pageID;
} __attribute__((__packed__))XIAOAN_ETC_pageID;

typedef struct
{
    u8 isRevSuccess;
} __attribute__((__packed__))XIAOAN_ETC_ISSUCCESS;

typedef struct
{
	u8  canUpgrade;
    u16 size;
} __attribute__((__packed__))XIAOAN_ETC_START_OTA_RSP;

typedef struct
{
    u8  soc;
    u8  soh;
    u16 capacity;
    u16 cycle;
    s8  batTemp;
    u16 bmsFault;
    u8  reserved[7];
} __attribute__((__packed__))XIAOAN_ETC_GET_BMSINFO;

#define MSG_HEADER_XIAOAN_ETC_LEN sizeof(MSG_HEADER_XIAOAN_ETC)

#pragma pack(pop)

void   ETC_XiaoAn_Initial(void);
L_BOOL ETC_XiaoAn_IsCheckSumPass(MSG_HEADER_XIAOAN_ETC *msg);
L_BOOL XiaoAn_FilterFrame(u8 * data, u16 length);

void ETC_XiaoAn_GetETCInfo(void);
void ETC_XiaoAn_SetETCAccOn(void);
void ETC_XiaoAn_SetETCAccOnOnce(void);
void ETC_XiaoAn_SetETCDefend(u8 isDefend);
void ETC_XiaoAn_SetETCDefendOnce(u8 isDefend);
void ETC_XiaoAn_SetLight(u8 state);
void ETC_XiaoAn_SetBMSSoc(void);
void ETC_XiaoAn_OTAStart(void);
void ETC_XiaoAn_OTARealData(void);
void ETC_XiaoAn_OTAComplete(void);
void ETC_XiaoAn_GetSOC(void);
int ETC_getSocTimeout(void);

#endif

