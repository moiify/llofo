/*
 * diagnosis.h
 *
 *  Created on: 2016年3月4日
 *      Author: jk
 */

#ifndef USER_MAIN_DIAGNOSIS_H_
#define USER_MAIN_DIAGNOSIS_H_

#define CHECK_CSQCOUNT_MAX 10    //10s

enum
{
    C_SUCCESS,
    C_BATTERY_FAIL,
    C_GSM_FAIL,
    C_ACC_FAIL,
    C_SIMCARD_FAIL,
    C_ISWHEELSPAN_FAIL,
    C_SADDLE_DAOWEI_FAIL,//5
    C_BACKWHEEL_DAOWEI_FAIL,//6
    C_AUDIO_CUSTOM_RESULT_FAIL,//7
    C_OVER_SPEED_FAIL,
};
typedef enum
{
    CHECK_START,
    CHECK_CSQ,
    CHECK_SIMCARD,
    CHECK_ACCELEROMETER,
    CHECK_SUCCESS,
    CHECK_FAILED,
} checkstate_e;//检测结果错误码

//step0、获取版本号和imei
//step1、中控内部信号自检测
//step2、中控输入性质硬件检测
//step3、中控输出性质硬件检测
//step4、中控通信类型硬件检测
//step5、中控常态类型硬件检测
typedef enum
{
    CHECK_TYPE_GETBASEINFO  = 0,//获取中控基础信息
    CHECK_TYPE_CHECKSIGNAL  = 1,//中控内部参数检测
    CHECK_TYPE_CHECKINPUT   = 2,//中控输入类型硬件检测
    CHECK_TYPE_CHECKOUTPUT  = 3,//中控输出类型硬件检测
    CHECK_TYPE_CHECKTRANS   = 4,//中控通信类型硬件检测
    CHECK_TYPE_CHECKCONST   = 5,//中控常态类型硬件检测
}CHECK_TYPE;//测试大板检测的类型

typedef enum
{
    SIGNAL_BIGVILTAGE      = 0,//大电压
    SIGNAL_SIMCARD         = 1,//SIM卡检测1
    SIGNAL_GSM             = 2,//GSM信号检测
    SIGNAL_GPS             = 3,//GPS定位检测
    SIGNAL_SELFCHECK       = 4,//自检结果
    SIGNAL_ISLOGIN         = 5,//设备登录状态
    SIGNAL_SPK_N            = 6,//喇叭ADN检测
    SIGNAL_SPK_P            = 7,//喇叭ADP检测
    SIGNAL_BLE_BOOT         = 8,//蓝牙BOOT是否已下载
}SINGAL_TYPE;//内部参数检测类型

typedef enum
{
    INPUT_SADDLEINPLACE    = 0,//电池仓到位
    INPUT_BACKWHELLINPLACE = 1,//后轮到位
    INPUT_SPEEDSIGNAL      = 2,//轮动信号
    INPUT_OVERSPEED        = 3,//超速报警
    INPUT_HELMETSENSE      = 4,//头盔锁感应信号
}INPUT_TYPE;//中控输入检测类型

typedef enum
{
    INPUT_GROUP1          = 1,//输入组1
    INPUT_GROUP2          = 2,//输入组2
    INPUT_GROUP3          = 3,//输入组3
    INPUT_GROUP4          = 4,//输入组4
}INPUT_GROUP;//中控输入检测分组

typedef enum
{
    OUTPUT_ACC             = 0,//电门输出
    OUTPUT_SADDLE_ON       = 1,//电池仓开启
    OUTPUT_SADDLE_OFF      = 2,//电池仓关闭
    OUTPUT_BACKWHELL_ON    = 3,//后轮锁开启
    OUTPUT_BACKWHELL_OFF   = 4,//后轮锁关闭
    OUTPUT_BREAK_OPERATE   = 5,//刹车线开关
    OUTPUT_LIGHT           = 6,//大灯线控制
    OUTPUT_RFID_5V         = 7,//RFID5V
}OUTPUT_TYPE;//中控输出检测类型

typedef enum
{
    TRANS_RFIDCOM           = 0,//BMScom口输入输出
}TRANS_TYPE;//中控传输检测类型


typedef enum
{
    OUTPUT_BMSGND          = 0,//BMS地线
    OUTPUT_BMSVCC          = 1,//BMS5V检测
}CONST_TYPE;//中控常态输出检测类型


#pragma pack(push,1)

typedef struct
{
    float lat;
    float lon;
} CHECK_GPS;

typedef struct
{
    u32 version;
    u8 imei[15];  
}__attribute__((__packed__))CHECK_VERSION_AND_IMEI;

typedef struct
{
    u32 version;
    u8 imei[16];  
    u8 name[16];  
}__attribute__((__packed__))CHECK_MSG_INFO;

typedef struct
{
    u8 checkType;   //检测类型
    u32 version;    //被检测设备的版本号
    u8 imei[15];    //被检测设备的IMEI
    u32 checkSignal;//期望检测的信号项
    u32 checkInput; //期望检测的输入项
    u32 checkOutput;//期望检测的输出项
    u32 checkTrans; //期望检测的传输项
    u32 checkConst; //期望检测的常量项
}__attribute__((__packed__))CHECK_GET_BASEINFO;

typedef struct
{
    u8 checkType;   //检测类型
    u8 checkGroup;     //检测类型细分组
    u8 checkParam[32]; //类型对应参数
}__attribute__((__packed__)) CHECK_TYPE_MSG;

typedef struct
{
    u8 checkType;   //检测类型
    u8 checkGroup;     //检测类型细分组
    u32 checkParamRsp; //类型对应参数测试结果
}__attribute__((__packed__)) CHECK_TYPE_MSG_RSP;

typedef struct
{
    checkstate_e checkstate;
    u8 checkCSQ_count;
    L_BOOL isInitCheckSuccess;
    L_BOOL isBLECheckSuccess;
    L_BOOL isGPSCheckSuccess;
    L_BOOL isGNSSstate;
}__attribute__((__packed__)) checkLists_t;

typedef struct
{
    u8 param;
    u8 resv;
}__attribute__((__packed__)) CHECK_PARAM;

#pragma pack(pop)

int diag_selfCheck(void);

int diag_diagMsgProc(u8* data, u16 dataLen);

int diag_GPSCheckSuccess(void);
int diag_DA14580CheckSuccess(void);
int diag_GNSSState(u8 state);
void diag_selfCheckDeinit(void);


#endif /* USER_MAIN_DIAGNOSIS_H_ */
