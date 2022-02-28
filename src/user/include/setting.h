/*
 * setting.h
 *
 *  Created on: 2020/04/09
 *      Author: lc
 */

#ifndef USER_ELECTROMBILE_SETTING_H_
#define USER_ELECTROMBILE_SETTING_H_

#include "types.h"
#include "protocol.h"

#define BLE_NAME_STRING "XiaoanTech"

#define COREURL_14_23  "http://xc-res.oss-cn-shenzhen.aliyuncs.com/firmware/L610_Core/14_23.bin"

#define MAX_URL_LEN              (128)
#define SLEEP_DEFAULT_TIME       (30)
#define SLEEP_SOCKET_WAKE        (30)
#define SLEEP_BLE_WAKE           (30)
#define SLEEP_SHARK_WAKE         (10)
#define SLEEP_SMS_WAKE           (10)
#define SLEEP_CALL_WAKE          (10)

#define APP_SIGNATURE_LEN     10
#define MAX_APP_VERSION_LEN   16
#define MAX_PLATFORM_NAME_LEN 16
#define MAX_CORE_VERSION_LEN  64
#define MAX_TIMELEN           6

typedef struct
{
    u8 signature[APP_SIGNATURE_LEN];
    u8 platform[MAX_PLATFORM_NAME_LEN];
    u8 appversion[MAX_APP_VERSION_LEN];
    u8 coreversion[MAX_CORE_VERSION_LEN];
} APP_HEAD;

#define APP_HEAD_LEN        sizeof(APP_HEAD)

#define PRODUCT_NAME_LEN    15
#define MAX_DOMAIN_NAME_LEN 64
#define MAX_IP_PORT_LEN     22
#define MAX_BLE_NAME_LEN    15
#define HTTP_URL_LEN        256

#define BLE_DFT_TOKEN       (0x0A0A0505)
#define BLE_DFT_NAME        "XiaoanTech"

#define SETTING_DFT_MOVEPERIOD      5
#define SETTING_DFT_NORMPERIOD      600
#define SETTING_DFT_AUTOLOCKPERIOD  600
#define SETTING_DFT_PROTECTVOLATGE  39000
#define SETTING_DFT_RESTOREVOLATGE  45000
#define SETTING_DFT_TURNANGLE       20
#define SETTING_DFT_TURNAUDIO       600
#define SETTING_MPU_AVOIDANCE_RATIO 1
#define SETTING_MOVE_THRESHOLD      300
#define SETTING_DEF_AUTYPE          0
#define SETTING_DFT_BEACONRSSI      70
#define SETTING_DFT_BMSPERIOD       600

#define ETC_DEFAULT_SPEED           100
#define ETC_DEFAULT_ISSLOWSTART     0
#define ETC_DEFAULT_LIMITCURRENT    130
#define ETC_DEFAUTL_PROTECTVOLTAGE  410
#define ETC_DEFAULT_FUNCSWITCH      0


#define SETTING_DFT_OVERSPEED   L_FALSE
#define SETTING_DFT_MOVEALARM   L_FALSE
#define SETTING_DFT_FENCE       L_FALSE
#define SETTING_DFT_IGNORE      L_FALSE
#define SETTING_DFT_IGNORE_ONEC L_FALSE
#define SETTING_DFT_SLEEP       L_TRUE
#define SETTING_DFT_BEACON      L_TRUE
#define SETTING_DFT_NIGHTVO     L_FALSE
#define SETTING_DFT_SHARKAL     L_FALSE
#define SETTING_DFT_TURNOVER    L_FALSE
#define SETTING_DFT_AUTOLOCK    L_TRUE
#define SETTING_DFT_AGPS        L_TRUE
#define SETTING_DFT_RFID        L_FALSE

typedef enum
{
    ADDR_TYPE_IP,
    ADDR_TYPE_DOMAIN
} ADDR_TYPE;

typedef enum
{
    MODE_NORM,
    MODE_ECO,
    MODE_SLEEP
} MODE_TYPE;

typedef enum
{
    FREQ_NULL,
    FREQ_MOVE,  //5s一次
    FREQ_NORM,  //10min一次
} FREQ_TYPE;

typedef enum
{
    SETTING_SUCCESS,
    SETTING_ALREADY,
    SETTING_NOTSTOP,
    SETTING_OUTSERVICE,
} SETTING_RESULT;

typedef enum
{
    TYPE_NOCCU          = 0, //无控制器通信
    TYPE_XIAOANCCU      = 1, //小安协议控制器通信
    TYPE_YIHUCCU        = 2, //奕虎协议控制器通信
    TYPE_JINGHUICCU     = 3, //晶汇协议控制器通信
    TYPE_TAIBITE        = 4, //泰比特协议控制器通信
    TYPE_GENFO          = 5, //锂享出行金丰控制器通信
    TYPE_TAIBITE_NEW    = 6, //泰比特0x66协议控制器通信
    TYPE_TAIBITE_SOC    = 7, //泰比特协议控制器通信，增加SOC高位填至低位异常过滤逻辑
    TYPE_TAIBITE_09     = 8, //泰比特0x09协议控制器通信
    TYPE_CCU_MAX
} TYPE_CCUTYPE;

typedef enum
{
    TYPE_NOBMS          = 0, //无BMS通信
    TYPE_XIAOANBMS      = 1, //小安协议BMS通信
    TYPE_NANDUBMS       = 2, //南都协议BMS通信
    TYPE_ZHONGTIANBMS   = 3, //中天协议BMS通信
    TYPE_XINGHENGBMS    = 4, //星恒协议BMS通信
    TYPE_YIQIBMS        = 5, //易骑协议BMS通信
    TYPE_TIETABMS       = 6, //铁塔协议BMS通信
    TYPE_BMS_MAX
} TYPE_BMSTYPE;

enum
{
    VERSION_TYPE_MX5F = 0,
    VERSION_TYPE_MX5K4 = 1,
    VERSION_TYPE_MX5F3 = 3,
    VERSION_TYPE_MX5H3 = 4,
    VERSION_TYPE_MX5K3 = 5,
    VERSION_TYPE_MX5Z3 = 6,
    VERSION_TYPE_MX5Z = 7,
    VERSION_TYPE_MX5D = 8,
    VERSION_TYPE_MX5H = 9,
    VERSION_TYPE_MX5F_JDY = 10,
    VERSION_TYPE_MX5Z5 = 11,
    VERSION_TYPE_MX5D2 = 12,
    VERSION_TYPE_MX5K6 = 13,
    VERSION_TYPE_MX5S = 14,
    VERSION_TYPE_MX5L3 = 15,
    VERSION_TYPE_MX5D4 = 16,
    VERSION_TYPE_MX5S2 = 18,
    VERSION_TYPE_MX5E = 19,
    VERSION_TYPE_MX5K2_LM = 20,
    VERSION_TYPE_MX5K6_DD = 23,
    VERSION_TYPE_MX5F6_DD = 24,
    VERSION_TYPE_MX5F_JC = 26,
    VERSION_TYPE_MX5K6_LS = 27,
    VERSION_TYPE_MX5Y = 28,
    VERSION_TYPE_MX5Y3 = 29,
    VERSION_TYPE_MX5Y6_DD = 30,
    VERSION_TYPE_MX5D3_RF = 31,
    VERSION_TYPE_MX5H6_DD = 32,
    VERSION_TYPE_MX5H7_DD = 33,
    VERSION_TYPE_MX5F7_DD = 34,
    VERSION_TYPE_MX5K7_DD = 35,
    VERSION_TYPE_MX5Y3_LS = 29,
    VERSION_TYPE_MX5K8_RF = 38,
    VERSION_TYPE_MX5Y6_RF = 39,
    VERSION_TYPE_MX5K4_XBD = 40,
    VERSION_TYPE_MX5F7_RF  = 41,
    VERSION_TYPE_MX5F6_RF  = 42,
    VERSION_TYPE_MX5H7_RF  = 43,
    VERSION_TYPE_MX5Y3_XL_CC  = 44,
    VERSION_TYPE_MX5K5 = 45,
    VERSION_TYPE_MX5K6_RF = 46,
    VERSION_TYPE_MX5D3 = 47,
    VERSION_TYPE_MX5Y4 = 48,
    VERSION_TYPE_MX5X5 = 50,
    VERSION_TYPE_MX5F5 = 51,
    VERSION_TYPE_MX5F8 = 52,
    VERSION_TYPE_MX5K4_RF = 53,
    VERSION_TYPE_MX5K7_RF = 54,
};

typedef enum
{
    GPS_UBLOX_8130,
    GPS_UBLOX_M8U,
    GPS_ALLYSTAR_8040,
    GPS_UBLOX_7020,
    GPS_UBLOX_8130_OR_7020,
    GPS_UNKNOWN
} GPS_MOUDLE_TYPE;

typedef enum
{
    ETC_NO_SPEED_OR_HALL,
    ETC_FIRST_USE_SPEED,
    ETC_ONLT_USE_SPEED,
    ETC_ONLT_USE_HALL
} ETC_SPEED_SOURCE_TYPE;

typedef enum
{
    ACCLE_LIS3DH,
    ACCLE_MPU6500
} ACCLE_MOUDLE_TYPE;

typedef struct
{
    u8  name[PRODUCT_NAME_LEN + 1];//配置名称
    u32 version;                   //配置版本号
    u16 productType;               //配置产品类型
    u8  ccuType;                   //控制器类型
    u8  bmsType;                   //BMS类型
    u8  saddleType;                //电池仓锁类型
    u8  helmetType;                //头盔锁类型
    u8  backWheelType;             //后轮锁类型
    u8  lightCtrlType;             //大灯控制类型
    u8  batteryType;               //电池电压类型
    u8  isOverSpeedOn;             //超速报警使能
    u8  isMoveAlarmOn;             //移动语音告警使能
    float audioRatio;              //系统音量
    u8  isNightVoiceOn;            //夜间语音使能
    u8  isShakeAlarmOn;            //震动语音告警使能
    u8  isAutoLockOn;              //自动落锁使能
    u8  etcSpeed;                  //控制限速
    u8  isTurnOverEnable;          //倾倒检测使能
} DEFAULT_CONF;

typedef struct
{
    u8 isRepeat;
    u8 isTrigger;
    u8 isOn;
    u8 triggerLedType;
    u8 repeatLedType;
    u32 remainTime;
    u32 durationTime;
    u8 repeatMode;
    u8 triggerMode;
    u32 startTime;
    u32 endTime;
} LEDCONFIG;

typedef struct
{

    u8  mode;                   //工作模式：正常0, 省电1 休眠2 [默认0]
    u16 freq_norm;              //正常模式下的上报频率[秒 1~18000] [默认600]
    u16 freq_move;              //运动状态下的上报频率[秒 1~30] [默认5]

    u32 token;
    u8  ble_name[MAX_BLE_NAME_LEN + 1];

    u8  loglevel;               //打印日志级别
    u8  isFenceEnable;          //fence使能
    u8  isIgnoreFence;          //忽略围栏功能
    u8  isIgnoreFenceOnce;      //仅首次生效
    u8  isTBeaconEnable;        //道钉还车使能
    u8  isSleepEnable;          //低电压休眠功能
    u8  isAgpsEnable;           //辅助定位使能
    u32 autoLockPeriod;         //自动落锁周期
    u16 diffAngle;              //翻倒报警角度范围，如：30
    u16 periodDiffAngleAudio;   //连续播放语音周期
    u8  forceLock;              //强制锁车权限
    u16 audioType;              //定制的语音文件序号
    u16 checkOverSpeedTime;     //超速报警间隔时间    单位秒
    u16 devInstallMode;         //中控安装方式：0：纵向安装，线朝车尾，1：纵向安装，线朝车头，2：横向安装，线朝左，3：横向安装，线朝右
    u16 mpuAvoidanceRatio;
    u32 fenceVersion;
    u8  displaylog;
    u8  isEtcSOC;
    u32 activeFreqSOC; //主动获取一线通SOC的频率，单位min，默认0
    u8  beaconRssi; //道钉阈值
    u32 protectVoltage;         //mV 休眠电压
    u32 restoreVoltage;         //mV 唤醒电压

    u16 overSpeedVolume;
    u8  overSpeedUrl[MAX_URL_LEN];
    u16 overSpeedCrc;
    u16 move_threshold;

    u8  etcFuncSwitch;
    u8  etcIsSlowStart;
    u16 etcLimitCurrent_100mA;
    u16 etcProtectVoltage_100mV;

    u8 gpsType;
    u8 accleType;
    u8 isNmeaOut;

    u8 isEtcAccProtect;
    u8 isEtcDefendProtect;
    u8 isRFIDEnable;            //打开RFID定点功能
    u8 isKickStandEnable;       //打开脚撑还车
    LEDCONFIG ledConfig;
    u8 isDefaultSpeed;
    float etcHallRatio;
    float etcSpeedRatio;
    u32 etcSpeedSource;
    u8 isMX5EEAudio1K;
    u8 isEtcOverspeedBit; //是否使用控制器超速故障判断超速，0不使用，1使用（默认）
    u8 overspeedThreshold; //超速报警超速阈值，取值范围0-25，默认15

    u8 apnname[64];
    u8 username[64];
    u8 password[64];

    u8 isBackLogOn;             //无需固化

    u8 imsi[MAX_IMSI_LENGTH + 1]; //无需固化
    u8 ccid[MAX_CCID_LENGTH + 1]; //无需固化
} SETTING_CONF;

typedef struct
{
    u8  acc;                        //0:熄火 1:启动
    u8  isDefend;                   //防盗开关: EAT_TRUE 开，EAT_FALSE 关
    u32 totalMiles;
    s32 lastMileLat;
    s32 lastMileLon;
    u16 rebootType;                 //重启原因
    u32 rebootTimeStamp;            //重启时间戳
    u16 lastreboot;                 //上次重启原因
    u16 accOnCount;                 //开电门次数
    u16 pwrCutCount;                //换电次数
    u32     Cnt_autoLockTime;       //自动落锁时间s 暂存:如果要做重启也能继续自动落锁的功能 需要用到这个
    L_BOOL  OperatingSaddlelock;    //电池仓锁正在解锁后恢复
    u8  etcUpgradeFlag;             //控制器升级标志
    u8  isTerminateETCUpgrade;      //是否终止控制器升级
    u8  etcVersion;                 //记录版本号，用于升级后查询
    u8  etcUpgradeVersion;          //服务器下发的版本号
    u16 etcFirmwareCRC;             //当前etc固件crc校验码
    u8  bmsUpgradeFlag;             //BMS升级标志
    u8  isTerminateBMSUpgrade;      //是否终止BMS升级
    u16 bmsVersion;                 //记录版本号，用于升级后查询，协议上为2个字节
    u16 bmsUpgradeVersion;          //服务器下发的版本号
    u16 bmsFirmwareCRC;             //当前BMS固件crc校验码
    u8  coreUpdateCount;            //升级内核失败次数,作保护,成功或者C32命令清零
    u8  bmsSoc;                     //记录当前BMS电量
    u32 bmsSendPeriod;              //BMS上报周期
    u8  gpsBaudrateUpdateFlag;      //gps波特率更新调整完成标志位（针对MX5K6-LS产品）
    u8  helmetTargetStatus;          //头盔锁目标状态 0：无  1：开锁且自动关锁  2：开锁不自动关锁  3：关锁且失败自动开锁  4：关锁且失败不自动开锁
} STATUS_CONF;

typedef enum
{
    HELMET_NULL = 0,
    HELMET_UNLOCK_ONLY,
    HELMET_UNLOCK_WITH_AUTOLOCK,
    HELMET_AUTOLOCK_ENABLE,
    HELMET_LOCK_ONLY,
    HELMET_LOCK_WITH_AUTOOPEN,
} HELMET_STATUS_TYPE;

typedef struct
{
    ADDR_TYPE addr_type;
    struct
    {
        char domain[MAX_DOMAIN_NAME_LEN];
        u8 ipaddr[4];
    };
    u16 port;
} SERVER_CONF;
typedef struct
{
    u32 coreVersion;                    //内核版本
    u8  platform[MAX_PLATFORM_NAME_LEN];//平台类型

    DEFAULT_CONF defaultConf;   //存储标品的配置选项
    SETTING_CONF settingConf;   //设备当前的配置类型
    STATUS_CONF  statusConf;    //重启后不丢失的易修改状态
    SERVER_CONF  serverConf;    //非默认服务器信息
    SERVER_CONF  srvBakConf;    //备份的服务器信息，用于切回，不做固化
} SETTING;

extern SETTING setting;

u8 setting_isAccOn(void);
u8 setting_isDefendOn(void);

SETTING_RESULT setting_setAcc(u8 accState);
SETTING_RESULT setting_setDefend(u8 defendState);

int setting_listnerHandler(void);

void sysConf_initial(void);

u8 serverConf_save(void);
u8 serverConf_restore(void);

u8 statusConf_save(void);
u8 statusConf_restore(void);

u8 settingConf_save(void);

L_BOOL defaultConf_save(void);
int setting_setServerTimeout(void);
u8 *setting_getIMEI(void);
u8 *setting_getIMSI(void);
u8 *setting_getCCID(void);
void *setting_obtainIMSI_cb(u8 *imsi);

u8 setting_saveFlash(void);
u8 setting_restoreFlash(void);

int setting_serverReinit(void);

int setting_setRebootType(u16 rebootType);
u8  setting_getVerisonType(void);
int setting_checkCore(void);
L_BOOL setting_isCoreUnmatch(void);
void setting_versionPatch(void);
int setting_getVersion_cb(int result, uint8_t *data, int data_len);

void *setting_allocConfig(int *pSize);

#endif /* USER_ELECTROMBILE_SETTING_H_ */
