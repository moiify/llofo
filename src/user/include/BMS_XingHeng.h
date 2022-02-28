#ifndef __USER_XINGHENGBMS_H__
#define __USER_XINGHENGBMS_H__

typedef enum
{
    CMD_BMS_GET_TEMPERATURE         = 0x08,//获取电池组温度
    CMD_BMS_GET_VOLTAGE             = 0x09,//读取电压
    CMD_BMS_GET_CURRENT             = 0x0a,//读取电流
    CMD_BMS_GET_HEALTH              = 0x0c,//健康状态
    CMD_BMS_GET_POWER_PERCENT_RE    = 0x0d,//读取剩余电量百分比(相对容量)
    CMD_BMS_GET_POWER_PERCENT_AB    = 0x0e,//读取剩余电量百分比(绝对容量)
    CMD_BMS_GET_REMAIN              = 0x0f,//读取剩余电量值
    CMD_BMS_GET_CAPACITY            = 0x10,//读取满充容量值
    CMD_BMS_GET_CIRCLE_TIMES        = 0x17,//读取循环次数
    CMD_BMS_GET_VOLTAGE_SINGLE_0    = 0x24,//读取单个电池电压1-7
    CMD_BMS_GET_VOLTAGE_SINGLE_1    = 0x25,//读取单个电池电压8-14
    CMD_BMS_GET_SN                  = 0x7e,//获取条码信息
    CMD_BMS_GET_VERSION             = 0x7f,//获取版本信息
} CMD_BMS;

#pragma pack(push, 1)

typedef struct
{
    u8 signature;
    u8 address;
    u8 cmd;
    u8 length;
    u8 data[];
} __attribute__((__packed__)) MSG_HEADER_XINGHENG_BMS;

#pragma pack(pop)

#define MSG_HEADER_XINGHENG_BMS_LEN sizeof(MSG_HEADER_XINGHENG_BMS)

void BMS_XingHeng_getBMSDataLoop(void);
int BMS_XingHeng_sendBMSDATA(u8 cmd, u8 *data, u8 dataLen);
L_BOOL BMS_XingHeng_isBMSCheckSumPass(MSG_HEADER_XINGHENG_BMS *cmdData);
int BMS_XingHeng_procOneMsg(u8 *data, u8 dataLen);
L_BOOL XingHeng_FilterFrame(u8 * data, u16 length);
void BMS_XingHeng_Initial(void);

#endif//__USER_DA14580_XHBMS_H__

