/*
 * ETC_TaiBiTe.h
 *
 *  Created on: 2020/06/15
 *      Author: ltx
 */
#ifndef __USER_TAIBITEETC_H__
#define __USER_TAIBITEETC_H__

#define TAIBITE_ETC_ADDRESS   0x2A //泰比特ETC通信地址

enum
{
    TAIBITE_CMD_GET_BATT_TEMP               = 0x08,//电池组内部温度
    TAIBITE_CMD_GET_BATT_VOLT               = 0x09,//电池组总电压
    TAIBITE_CMD_GET_BATT_CURRENT            = 0X0a,//实时电流
    TAIBITE_CMD_GET_BATT_SOH                = 0x0C,//SOH
    TAIBITE_CMD_GET_BATT_RELA_CAP           = 0x0d,//相对容量百分比
    TAIBITE_CMD_GET_BATT_ABS_CAP            = 0x0e,//绝对容量百分比
    TAIBITE_CMD_GET_BATT_REMAIN_CAP         = 0x0f,//剩余容量
    TAIBITE_CMD_GET_BATT_CAP                = 0X10,//满电容量
    TAIBITE_CMD_GET_BATT_RECYCLE_TIME       = 0x17,//循环次数
    TAIBITE_CMD_GET_BATT_VOLT_BEFORE        = 0X24,//1~7节电池电压
    TAIBITE_CMD_GET_BATT_VOLT_AFTER         = 0x25,//8~14节电池电压
    TAIBITE_CMD_GET_BATT_CHARGE_TIME        = 0x47,//当前充电间隔时间
    TAIBITE_CMD_GET_BATT_MAX_CHARGE_TIME    = 0X48,//最大充电间隔时间
    TAIBITE_CMD_GET_RW_BARCODE              = 0x7e,//读写成品条形码
    TAIBITE_CMD_GET_READ_VERSION            = 0X7f,//读版本号
    TAIBITE_CMD_GET_READ_FACTORY_NAME       = 0x20,//读电池组制造厂名称
    TAIBITE_CMD_SET                         = 0x66,//泰比特命令字
};

#pragma pack(push, 1)

typedef struct
{
    u8 head;
    u8 address;
    u8 cmd;
    u8 length;
    u8 data[];
} __attribute__((__packed__)) MSG_HEADER_TAIBITE;

typedef struct
{
    u8 etcErrorState;//控制器状态标志位
    u8 etcModeRsp;   //控制器模式回馈
    u16 hallNumber;  //0.5秒内三个霍尔变化的个数
    u8 socData5;     //兼容性soc取值
    u8 reserve[3];   //跳过解析
    u8 soc;          //控制器返回BMS相对容量百分比，经与松正、金丰沟通，data9填入一线通soc
} __attribute__((__packed__))TAIBITE_ETC_GENERAL_INFO;

typedef struct
{
    uint8_t accOff:1;
    uint8_t lock:1;
    uint8_t reserve:1;
    uint8_t etcspeed:3;
    uint8_t mode:2;
} ETC_CTRL;

#define MSG_HEADER_TAIBITE_LEN sizeof(MSG_HEADER_TAIBITE)

#pragma pack(pop)

void   ETC_TaiBiTe_Initial(void);
L_BOOL ETC_TaiBiTe_IsCheckSumPass(MSG_HEADER_TAIBITE *msg);
L_BOOL ETC_TaiBiTe_FilterFrame(u8 * data, u16 length);

void ETC_TaiBiTe_GetETCInfo(void);
void ETC_TaiBiTe_SetETCAccOn(void);
void ETC_TaiBiTe_SetETCAccOnOnce(void);
void ETC_TaiBiTe_SetETCDefend(u8 isDefend);
void ETC_TaiBiTe_SetETCDefendOnce(u8 isDefend);

//泰比特BMS相关 不可用暂存
void ETC_TaiBiTe_GetBatteryTemp(void);
void ETC_TaiBiTe_GetBatteryVoltage(void);
void ETC_TaiBiTe_GetBatteryCurrent(void);
void ETC_TaiBiTe_GetBatteryRelaCap(void);
void ETC_TaiBiTe_GetBatteryAbsCap(void);
void ETC_TaiBiTe_GetBatteryRemainCap(void);
void ETC_TaiBiTe_GetBatteryCap(void);
void ETC_TaiBiTe_GetBatteryRecycleTimes(void);
void ETC_TaiBiTe_GetBatteryVoltBefore(void);
void ETC_TaiBiTe_GetBatteryVoltAfter(void);
void ETC_TaiBiTe_GetBatteryChargeTime(void);
void ETC_TaiBiTe_GetBatteryMaxChargeTime(void);
void ETC_TaiBiTe_GetBatteryRW_Barcode(void);
void ETC_TaiBiTe_GetBatteryReadVersion(void);
void ETC_TaiBiTe_GetBatteryReadFactoryName(void);

#define SOC_WINDOW_SIZE 20
int ETC_TaiBiTe_resetSocWindow(void);
u8 *ETC_TaiBiTe_getSocWindow(void);
u8 ETC_TaiBiTe_getSocPoint(void);

#endif
