/*
 * flash.h
 *
 *  Created on: 2017/1/11
 *      Author: lc
 */
#ifndef USER_INC_FLASH_H_
#define USER_INC_FLASH_H_

/*
 * 对应default_config.txt数组的TLV
 */
typedef enum {
    TYPE_ISOVERSPEEDON      = 1,   //uint8_t 超速语音报警开关是否默认使能 <0 非使能>, <1 使能>
    TYPE_ISMOVEALARMON      = 2,   //uint8_t 移动语音报警开关是否默认使能 <0 非使能>, <1 使能>
    TYPE_AUDIORATIO         = 3,   //uint8_t 默认最大语音系数  单位: 0.01 范围<1~100>
    TYPE_ISNIGHTVOICEON     = 4,   //uint8_t 夜间语音功能开关是否默认使能 <0 非使能>, <1 使能>
    TYPE_SADDLE             = 5,   //uint8_t 电池仓锁类型 <0 200ms电磁锁>, <1 卡扣式电池仓锁>, <2 锁销式电池仓锁>
    TYPE_BACKWHEEL          = 6,   //uint8_t 后轮锁类型 <0 无后轮锁>, <1 5V锁销式涨阀锁>
    TYPE_ISSHAKEALARMON     = 7,   //uint8_t 震动告警否上报是否默认使能 <0 非使能>, <1 使能>
    TYPE_CONTROLLIGHT       = 8,   //uint8_t 大灯控制类型 <0 无大灯控制>, <1 电平大灯控制>, <1 控制器大灯控制>
    TYPE_CCU                = 9,   //uint8_t 控制器类型 <0 无控制器协议>, <1 小安控制器协议>, <2 奕虎控制器协议>, <3 ME3晶汇控制器协议>，<4 泰比特控制器协议>
    TYPE_BMS                = 10,  //uint8_t BMS类型 <0 无BMS>, <1 小安BMS协议>, <2 南都BMS协议>, <3 如易出行BMS协议>
    TYPE_BATTERY            = 11,  //uint8_t 电池类型 单位:V 电池类型为12V 36V 48V 60V 72V
    TYPE_HELMET             = 12,  //uint8_t 头盔锁类型 <0 无头盔锁>, <1 200ms电磁锁>, <2 卡扣式头盔锁>, <3 锁销式头盔锁>, <4 卡扣式头盔锁-亚克特头盔锁-MX3S>
    TYPE_ISAUTOLOCKON       = 13,  //uint8_t 自动落锁功能开关是否默认使能 <0 非使能>, <1 使能>
    TYPE_ETC_SPEED          = 14,  //uint8_t 控制器限速值 <0~100>
    TYPE_ISTURNOVERON       = 15,  //uint8_t 倾倒检测功能开关是否默认使能 <0 非使能>, <1 使能>
    TYPE_MAX_CONFIG
} USER_CONFIG_TYPE;

typedef enum {
    TYPE_DISABLE = 0,
    TYPE_ENABLE  = 1
}TYPE_ISENBALE;

typedef enum {
    TYPE_EMAGNETICSADDLE        = 0,  //电磁式电池仓锁
    TYPE_BUCKLESADDLE           = 1,  //卡扣式电池仓锁-亚克特电池仓锁
    TYPE_LOCKPINSADDLE          = 2,  //锁销式电池仓锁-唐泽电池仓锁
    TYPE_BUCKLESADDLE_REVERT    = 3,  //卡扣式电池仓锁-亚克特电池仓锁-MX3S
    TYPE_BUCKLESADDLE_MX3Y      = 4,  //卡扣式电池仓锁-亚克特电池仓锁-MX3Y 用在后轮锁管脚上
    TYPE_DAHACHE                = 5,  //大哈车的电池仓锁-无到位信号 MX5Z\MX5Z3
    TYPE_48V_SADDLELOCK_200     = 7,  //48V电池仓锁，200ms高电平
    TYPE_JDY500MS_MX5F          = 8,  //筋斗云500ms锁
    TYPE_48V_BUCKLESADDLE       = 9,  //48V电池仓锁，600ms高电平
    TYPE_48V_200_XBD            = 10, //48V电池仓锁，200ms高电平，跟类型7到位信号相反 MX5K4-XBD
    TYPE_SADDLE_MAX
}TYPE_SADDLETYPE;

typedef enum {
    TYPE_NOHELMET               = 0, //无头盔锁
    TYPE_EMAGNETICHELMET        = 1, //电磁式头盔锁
    TYPE_BUCKLEHELMET           = 2, //卡扣式头盔锁-同亚克特电池仓锁
    TYPE_LOCKPINHELMET          = 3, //锁销式头盔锁-同唐泽电池仓锁
    TYPE_BUCKLEHELMET_REVERT    = 4, //卡扣式头盔锁-同亚克特电池仓锁-MX3S
    TYPE_XINGQIHELMET           = 5, //星骑头盔锁-开电门关联开头盔锁
    TYPE_BUCKLEHELMET_SIX       = 6, //六线亚克特头盔锁
    TYPE_BUCKLEHELMET_LOW       = 7, //卡扣式头盔锁-同亚克特电池仓锁-低到位
    TYPE_HELMET_MAX
}TYPE_HELMETTYPE;

typedef enum {
    TYPE_NOBACKWHEEL        = 0, //无后轮锁
    TYPE_LOCKPINBACKWHEEL   = 1, //锁销式后轮锁
    TYPE_TANGZE_BACKWHEEL   = 2, //唐泽后轮锁
    TYPE_BACKWHEEL_MAX
}TYPE_BACKWHEELTYPE;

typedef enum {
    TYPE_NOHEADLIGHT   = 0, //无大灯控制
    TYPE_PINHEADLIGHT  = 1, //电平大灯控制
    TYPE_CCUHEADLIGHT  = 2, //控制器大灯控制
    TYPE_LIGHT_MAX
}TYPE_HEADLIGHTTYPE;

typedef enum {
    TYPE_BATTERY12V  = 12, 
    TYPE_BATTERY36V  = 36, 
    TYPE_BATTERY48V  = 48, 
	TYPE_BATTERY60V  = 60, 
	TYPE_BATTERY72V  = 72,
}TYPE_BATTERYTYPE;

typedef enum {
    TYPE_SILENCETIME,   //uint32_t 静止时间 用于进行自动落锁 单位:s
    TYPE_TOTALMILES,    //uint32_t 历史总里程 单位:m
    TYPE_LASTMILELAT,   //uint32_t 总里程使用的历史GPS的lat 单位0.000001°
    TYPE_LASTMILELON,   //uint32_t 总里程使用的历史GPS的lon 单位0.000001°
    TYPE_BUILDTIME_S,   //固件烧写时间,字符串类型
    TYPE_MAX
} USER_FLASH_TYPE;

#define SETTING_DATA_SIZE   (4 * 1024)


#pragma pack(push, 1)
typedef struct
{
    uint8_t  signature;
    uint16_t payloadLen;
    uint8_t  payload[];
}__attribute__((__packed__))ST_FLASH_DATA_HEADER;
typedef struct
{
    uint8_t type;
    uint8_t len;
    uint8_t value[];
}__attribute__((__packed__))ST_FLASH_DATA;


typedef struct
{
    uint8_t  signature[10];  //"XiaoanTech"
    uint32_t totalLen;       //包括signature的总长度
    uint8_t  name[10];       //名称
    uint32_t version;        //版本号
    uint16_t productType;    //产品类型
    uint8_t  num;            //数据数目
    uint8_t  payload[];      //config数据体
}__attribute__((__packed__))CONFIG_HEADER;

#pragma pack(pop)

const ST_FLASH_DATA_HEADER *flash_getBlockData(void);
bool flash_save2Block(const ST_FLASH_DATA_HEADER *pData, unsigned int len);

#endif /*USER_INC_FLASH_H_*/

