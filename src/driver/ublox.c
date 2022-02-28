/* Copyright (C) Xiaoan Technology Co., Ltd - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Tom Chiang <jiangtao@xiaoantech.com>, Feb 2017
 *
 * ublox.c
 *
 * ublox模块消息定义
 */
#include <stdint.h>

#include "log.h"
#include "ublox.h"
#include "data.h"
#include "user_timer.h"
#include "gps_parse.h"
#include "version.h"

static PORT_WRITER serialWriter = 0;
static double *g_pGpsSpeed = NULL;

void ublox_getGPS_Speed(double *speed)
{
    g_pGpsSpeed = speed;
}

int Ublox_isPollACK(u8 *nmea_str, u16 length)
{
    // LOG_DEBUG(" *** Ublox_isPollACK len(%d) recv:", length);
    // LOG_BIN(nmea_str, length);

    int i = 0;
    for(; i < length; i++)
    {
        if(nmea_str[i] == 0xB5 && nmea_str[i + 1] == 0x62)
        {
            u8 *ubx = nmea_str + i;
            int len = ubx[4] + ubx[5] * 256;
            int ubxLen = len + 8;
            if(0 == memcmp(ubx, "\xB5\x62\x0A\x04", 4)) //Ublox_getVersion回复报文
            {
                char *hwVer = ubx + 36;
                LOG_DEBUG(" *** 0A04 len(%d) recv:", len);
                LOG_HEX(ubx, ubxLen);
                if(strncmp(hwVer, "00080000", 8) == 0 && setting.settingConf.gpsType == GPS_UBLOX_8130_OR_7020)
                {
                    setting.settingConf.gpsType = GPS_UBLOX_8130;
                }
                else if(strncmp(hwVer, "00070000", 8) == 0 && setting.settingConf.gpsType == GPS_UBLOX_8130_OR_7020)
                {
                    setting.settingConf.gpsType = GPS_UBLOX_7020;
                }
				else
                {
                    LOG_ERROR("gpsType get error");
                }
            }
            if(0 == memcmp(ubx, "\xB5\x62\x06\x24", 4)) //mode switch
            {
                LOG_DEBUG(" *** 0624 len(%d) recv:", len);
                LOG_BIN(ubx, ubxLen);

                if(ubx[8] == Ublox_getExpectMode())
                {
                    data_getData()->ublox_setModeACK = L_TRUE;
                    LOG_DEBUG("[gps] get Mode Poll ACK %d", ubx[8]);
                }
            }
            if(0 == memcmp(ubx, "\xB5\x62\x0A\x21", 4)) //status
            {
                LOG_DEBUG(" *** 0A21 len(%d) recv:", len);
                LOG_BIN(ubx, ubxLen);
            }
            if(0 == memcmp(ubx, "\xB5\x62\x06\x57", 4)) //power
            {
                LOG_DEBUG(" *** 0657 len(%d) recv:", len);
                LOG_BIN(ubx, ubxLen);
            }
            if(0 == memcmp(ubx, "\xB5\x62\x05\x01", 4)) //ACK
            {
                LOG_DEBUG(" ****** 0501 ACK len(%d) recv:", len);
                LOG_BIN(ubx, ubxLen);
            }
            if(0 == memcmp(ubx, "\xB5\x62\x05\x00", 4)) //NAK
            {
                LOG_DEBUG(" ****** 0500 NAK len(%d) recv:", len);
                LOG_BIN(ubx, ubxLen);
            }
        }
    }
    return 0;
}

/*
* 根据 u-center生成协议数据
* 描述:
*     1. 获取软硬件版本号
*/
void Ublox_getVersion(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x0A, 0x04, 0x00, 0x00, 0x0E, 0x34};
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     1. ublox8130配置使能GPS、BeiDou、QZSS
*/
void Ublox_configGNSS(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x3E, 0x3C, 0x00, 0x00, 0x00, 0x20, 0x07, 0x00, 0x08, 0x10, 0x00, 0x01, 0x00,
                     0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00,
                     0x01, 0x01, 0x03, 0x08, 0x10, 0x00, 0x01, 0x00, 0x01, 0x01, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00,
                     0x01, 0x01, 0x05, 0x00, 0x03, 0x00, 0x01, 0x00, 0x01, 0x01, 0x06, 0x08, 0x0E, 0x00, 0x00, 0x00,
                     0x01, 0x01, 0x2E, 0x75};
                     
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     1. 速度为0也输出
*     2. 版本4.1V 带北斗数据
*     3. 兼容模式
*     4. 关闭QZSS输出
*     5. 全部GN引导
*/
void Ublox_initNMEAConfig(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x17, 0x14, 0x00, 0x20, 0x41, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x03,
                     0x01, 0x01, 0x47, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3D, 0x4B};
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     1. 速度为0也输出
*     2. 全部GN引导
*/
void Ublox_initNMEAConfig_7020(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x17, 0x0C, 0x00, 0x20, 0x23, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
                     0x01, 0x00, 0x74, 0x8C};
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     1. 无限期休眠
*     2. 串口RX唤醒
*/
void Ublox_gotoSleep(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x02, 0x41, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, \
                0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x5D, 0x4B};
	u16 len = sizeof(cfg);

    if(setting.settingConf.gpsType == GPS_UBLOX_7020)
    {
        uint8_t cfgV7[] = {0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x4D, 0x3B}; //休眠
        len = sizeof(cfgV7);
        memcpy(cfg, cfgV7, len);
    }
    
    if(serialWriter)
    {
        serialWriter(cfg, len);
    }
}

/*
* 根据文档说明,随便发个数据就能唤醒
* 描述:
*     1. 随意数据, 两个数据增大兼容性
*/
void Ublox_gotoAwake(void)
{
    uint8_t cfg[] = {0xFF, 0xFF};
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     1. 热重启
*     2. 软重启
*/
void Ublox_hotRestart(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x66};
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     1. 冷重启
*     2. 软重启
*/
void Ublox_coldRestart(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0xFF, 0xB9, 0x01, 0x00, 0xC7, 0x8D};
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     获取NAV-5设置
*/
static int Ublox_getModel(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x24, 0x00, 0x00, 0x2a, 0x84};
    if(serialWriter)
    {
        serialWriter(cfg, sizeof(cfg));
    }

    return 0;
}

#define UBLOX_MISACKTIME  5  //5次考虑到异常后Ublox重启初始化时间

typedef enum
{
    UBLOX_MODESW_SETREQ,
    UBLOX_MODESW_GETREQ,
    UBLOX_MODESW_WAITACK,
    UBLOX_MODESW_ACK,
    UBLOX_MODESW_IDLE,
} ublox_ModeState;

typedef struct
{
    UBLOX_DYNAMIC_MODLES ublox_CurrentMode; //Ublox目前所处的模式
    UBLOX_DYNAMIC_MODLES ublox_SetMode;		//将要设置的状态
    ublox_ModeState ublox_ModeSwitchState;  //状态
} ModeSwitchVar_t;

static ModeSwitchVar_t ModeSwitchVar =
{
    .ublox_ModeSwitchState = UBLOX_MODESW_IDLE,
    .ublox_CurrentMode = UBLOX_DYNAMIC_UNSET,
    .ublox_SetMode = UBLOX_DYNAMIC_UNSET,
};

UBLOX_DYNAMIC_MODLES Ublox_getExpectMode(void)
{
    return ModeSwitchVar.ublox_SetMode;
}

static L_BOOL ublox_ModeMismatch(UBLOX_DYNAMIC_MODLES * mode)
{
    if(setting_isDefendOn() && ModeSwitchVar.ublox_CurrentMode != UBLOX_DYNAMIC_MODLE_STATIONNARY)
    {
        *mode = UBLOX_DYNAMIC_MODLE_STATIONNARY;
        LOG_DEBUG("[Ublox] change to DYNAMIC_STATIONNARY mode");
        return L_TRUE;
    }
    else if(setting_isAccOn() && ModeSwitchVar.ublox_CurrentMode != UBLOX_DYNAMIC_MODLE_AUTOMOTIVE)
    {
        *mode = UBLOX_DYNAMIC_MODLE_AUTOMOTIVE;
        LOG_DEBUG("[Ublox] change to DYNAMIC_AUTOMOTIVE mode");
        return L_TRUE;
    }

    return L_FALSE;
}

static int ublox_ModeSwitch(void)
{
    static u8 missACKCount = 0;

    switch(ModeSwitchVar.ublox_ModeSwitchState)
    {
        case UBLOX_MODESW_IDLE:
        {
            LOG_DEBUG("[Ublox] Check dynMode");
            if(ublox_ModeMismatch(&ModeSwitchVar.ublox_SetMode))
            {
                ModeSwitchVar.ublox_ModeSwitchState = UBLOX_MODESW_SETREQ;
            }
        }
        break;
        case UBLOX_MODESW_SETREQ:
        {
            Ublox_setModel(ModeSwitchVar.ublox_SetMode);
            LOG_DEBUG("[Ublox] set dynMode:%d", ModeSwitchVar.ublox_SetMode);
            ModeSwitchVar.ublox_ModeSwitchState = UBLOX_MODESW_GETREQ;
        }
        break;
        case UBLOX_MODESW_GETREQ:
        {
            Ublox_getModel();
            LOG_DEBUG("[Ublox] get NAV-5 req...");
            data_getData()->ublox_setModeACK = L_FALSE;
            ModeSwitchVar.ublox_ModeSwitchState = UBLOX_MODESW_WAITACK;
        }
        break;
        case UBLOX_MODESW_WAITACK:
        {
            if(data_getData()->ublox_setModeACK == L_FALSE)
            {
                if(missACKCount++ >= UBLOX_MISACKTIME)
                {
                    gps_moudleReset();
                    missACKCount = 0;
                    ModeSwitchVar.ublox_ModeSwitchState = UBLOX_MODESW_IDLE;
					ModeSwitchVar.ublox_CurrentMode = UBLOX_DYNAMIC_UNSET;
                    LOG_ERROR("[Ublox] set failed, model reset..");
                }
                else
                {
                    ModeSwitchVar.ublox_ModeSwitchState = UBLOX_MODESW_SETREQ;
					LOG_DEBUG("[Ublox] none ACK times %d",missACKCount);
                }
            }
            else
            {
                ModeSwitchVar.ublox_ModeSwitchState = UBLOX_MODESW_ACK;
                LOG_DEBUG("[Ublox] rev modem ACK");
            }
        }
        break;
        case UBLOX_MODESW_ACK:
        {
            missACKCount = 0;
            ModeSwitchVar.ublox_CurrentMode = ModeSwitchVar.ublox_SetMode;
            LOG_DEBUG("[Ublox] set to dynmode:%d success", ModeSwitchVar.ublox_SetMode);
            ModeSwitchVar.ublox_ModeSwitchState = UBLOX_MODESW_IDLE;
        }
        break;
        default:
            break;
    }
	return 0;
}

void Ublox_init(PORT_WRITER uart_writer)
{
    serialWriter = uart_writer;

#if (VERSION_MICRO >= 69)
	setting.settingConf.gpsType = GPS_UBLOX_8130_OR_7020; //动态获取之前先置为未知类型
	timer_start(TIMER_GPS_CHECK_VERSION, TIMER_S, 1, Ublox_checkVersion_cb); //如果是8130或者7020，先获取gps版本再进行初始化
#else
    Ublox_initNMEAConfig();
    fibo_taskSleep(100);
    Ublox_configGNSS();
#endif
    timer_startRepeat(TIMER_UBLOX_MODE_PROC, TIMER_S, 1, ublox_ModeSwitch);
    return;
}

void Ublox_setModel(UBLOX_DYNAMIC_MODLES model)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x0F};
    //更改model
    cfg[8] = model;
    //重新计算checksum
    cfg[sizeof(cfg) - 2] = cfg[sizeof(cfg) - 2] + model;
    cfg[sizeof(cfg) - 1] = cfg[sizeof(cfg) - 1] + 34 * model;
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/****************************************************************************************
*   以下是跟M8U参数配置、模式设置、惯导异常检测算法等相关的函数（MX5K6、MX5F6产品系列） *
*****************************************************************************************/
static const u8 cmd_baud_9600[] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x80, 0x25, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9E, 0x95};//9600
static const u8 cmd_baud_38400[] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0x70};//38400
static const u8 cmd_baud_115200[] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0xC2, 0x01, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0x5E};//115200

//四种方向安装角
static const u8 dev_install_right[] = {0xB5, 0x62, 0x06, 0x56, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB6, 0x08, 0x00, 0x00, 0xA0, 0xFC, 0x3D, 0x04, 0x03, 0xEC};//9.7上午测的安装角(横向安装，线朝右)
static const u8 dev_install_left[] = {0xB5, 0x62, 0x06, 0x56, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xED, 0x7D, 0x00, 0x00, 0xFA, 0x02, 0xE3, 0xFE, 0xAF, 0x97}; // 横向安装，线朝左
//static const u8 dev_install_down[] = {0xB5, 0x62, 0x06, 0x56, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x79, 0x00, 0x00, 0xDE, 0xFD, 0xFB, 0xFF, 0xD5, 0xBD};//9.18测得安装角(fine状态，线朝下)   
static const u8 dev_install_down[] = {0xB5, 0x62, 0x06, 0x56, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF2, 0x2B, 0x00, 0x00, 0x9B, 0x01, 0xC5, 0xFA, 0xE0, 0xC2};//9.15旋转yaw角得出安装角（纵向安装，线朝下）
static const u8 dev_install_up[] = {0xB5, 0x62, 0x06, 0x56, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCF, 0x32, 0x00, 0x00, 0xDE, 0xFD, 0xFB, 0xFF, 0x3E, 0x4C};//纵向安装，线朝上 

/*
* 根据 u-center生成协议数据
* 描述:
*     1. 配置使能GPS、Galileo、BeiDou、QZSS、SBAS
*     2. 禁止GLONASS
*/
static void Ublox_M8U_configGNSS(void)
{
  uint8_t cfg[] ={0xB5 ,0x62 ,0x06 ,0x3E ,0x3C ,0x00 ,0x00 ,0x00 ,0x1C ,0x07 ,0x00 ,0x08 ,0x10 ,0x00,
                  0x01 ,0x00 ,0x01 ,0x01 ,0x01 ,0x01 ,0x03 ,0x00 ,0x01 ,0x00 ,0x01 ,0x01 ,0x02 ,0x04, 
                  0x08 ,0x00 ,0x01 ,0x00 ,0x01 ,0x01 ,0x03 ,0x08 ,0x10 ,0x00 ,0x01 ,0x00 ,0x01 ,0x01,
                  0x04 ,0x00 ,0x08 ,0x00 ,0x00 ,0x00 ,0x01 ,0x01 ,0x05 ,0x00 ,0x03 ,0x00 ,0x01 ,0x00,
                  0x01 ,0x01 ,0x06 ,0x08 ,0x0E ,0x00 ,0x00 ,0x00 ,0x01 ,0x01 ,0x2C ,0xDD};
  
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     1. 速度为0也输出
*     2. 版本4.1V 带北斗数据
*     3. 兼容模式
*     4. 全引导为GN
*/
static void Ublox_M8U_initNMEAConfig(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x17, 0x14, 0x00, 0x20, 0x41, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x03, 
                     0x01, 0x01, 0x47, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3D, 0x4B};

    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
		配置NAV5参数（包括惯导模式、惯导输入输出过滤设置）
*/
static void Ublox_M8U_configNAV5(void)
{
	uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x0A, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA,
					 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x63};

    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     使能ublox输出ATT方向角姿态数据
*/
void Ublox_M8U_enableATT(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x16, 0xD3};
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     使能ublox输出PVT数据
*/
void Ublox_M8U_enablePVT(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x18, 0xE1};

    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     使能ublox输出自动增益数据
*/
void Ublox_M8U_enableMonHW(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x0A, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x23, 0x37}; //开
//    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x0A, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x32}; //关   

    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}


/*
* 根据 u-center生成协议数据
* 描述:
*     将配置保存到flash
*/
static void Ublox_M8U_saveCfgToFlash(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, \
                     0x00, 0x00, 0x03, 0x1D, 0xAB};
                     
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*      擦除flash
*/
static void Ublox_M8U_EraseFlash(void)
{
    uint8_t cfg[] = {0xB5 ,0x62 ,0x06 ,0x09 ,0x0D ,0x00 ,0xFF ,0xFF ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xFF ,0xFF ,0x00 ,0x00 ,0x03 ,0x1B ,0x9A};

    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*      设置安装角度
*/
static void Ublox_M8U_setInstallAngle(void)
{
    u8 mode = setting.settingConf.devInstallMode;

    if(serialWriter)
    {
        switch(mode)
        {
            case 0:
                serialWriter((u8 *)dev_install_down, sizeof(dev_install_down));
                break;
            case 1:
                serialWriter((u8 *)dev_install_up, sizeof(dev_install_up));
                break;
            case 2:
                serialWriter((u8 *)dev_install_left, sizeof(dev_install_left));
                break;
            case 3:
                serialWriter((u8 *)dev_install_right, sizeof(dev_install_right));
                break;
            default:
                serialWriter((u8 *)dev_install_down, sizeof(dev_install_down));;
                break;
        } 
    }       
}

/*
* 根据 u-center生成协议数据
* 描述:
*     设置NMEA数据输出频率为1HZ（基于UTC时间）
*     
*/
static void Ublox_M8U_setNMEAOutputRate(void)
{
  //  uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xF4, 0x01, 0x01, 0x00, 0X00, 0X00, 0x0A, 0x75}; //2HZ
  //  uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xFA, 0x00, 0x01, 0x00, 0X00, 0X00, 0x0F, 0x94}; //4HZ   
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xE8, 0x03, 0x01, 0x00, 0X00, 0X00, 0x00, 0x37}; //1HZ
    
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     设置陀螺仪数据输出频率为4HZ
*     
*/
void Ublox_M8U_setHNROutputRate(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x5C, 0x04, 0x00, 0x04, 0x00, 0x00, 0X00, 0x6A, 0xDC}; //4HZ   
   // uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x5C, 0x04, 0x00, 0x01, 0x00, 0x00, 0X00, 0x67, 0xD0}; //1HZ   
    
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     使能输出陀螺仪HNR数据
*     
*/
void Ublox_M8U_setHNRmsg(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x37, 0x00, 0X01, 0x00, 0x00, 0x00, 0x00,0x48, 0x31}; 
    
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     配置加速度计参数
*/
static void Ublox_M8U_setAccel(void)
{
    uint8_t cfg[] = {0xB5 ,0x62 ,0x06 ,0x4C ,0x14 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
                     0x20 ,0x0A ,0x00 ,0x00 ,0xE8 ,0x03 ,0x00 ,0x00 ,0x00 ,0x00 ,0x7B ,0x35};

    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     配置陀螺仪参数
*/
static void Ublox_M8U_setGyro(void)
{
    uint8_t cfg[] = {0xB5 ,0x62 ,0x06 ,0x4D ,0x14 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xB0 ,0x04,
                     0x84 ,0x0A ,0x00 ,0x00 ,0x64 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x0D ,0x79};

    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

/*
* 根据 u-center生成协议数据
* 描述:
*     自定义模式复位M8U惯导相关参数,复位参数:1.SFDR Parameters，2.SFDR Vehicle Monitor，3.TCT Parameters
*     
*/
void Ublox_M8U_userReset(void)
{
    uint8_t cfg[] = {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x00, 0x38, 0x01, 0x00, 0x47, 0x0E};
    if(serialWriter)
        serialWriter(cfg, sizeof(cfg));
}

int Ublox_checkVersion_cb(void)
{
    switch(setting.settingConf.gpsType)
    {
        case GPS_UBLOX_8130_OR_7020:
            Ublox_getVersion(); //只有在需要决定是8130或7020时才发送此消息
            timer_start(TIMER_GPS_CHECK_VERSION, TIMER_S, 1, Ublox_checkVersion_cb);
            break;

        case GPS_UBLOX_8130:
        {
            Ublox_initNMEAConfig();
            fibo_taskSleep(100);
            Ublox_configGNSS();
        }
        break;

        case GPS_UBLOX_7020:
            Ublox_initNMEAConfig_7020();
            break;

        case GPS_UBLOX_M8U:
            break;

        case GPS_ALLYSTAR_8040:
            break;

        case GPS_UNKNOWN:
            break;

        default:
            LOG_ERROR("unhandled gpsType: %d", setting.settingConf.gpsType);
            break;
    }
    return 0;
}

static void Ublox_M8U_init(PORT_WRITER uart_writer) // 初始化波特率
{
    serialWriter = uart_writer;
    
    u16 length = sizeof(cmd_baud_115200);

    uart_initial(UART_PORT_UART3, 9600, 70);//修改本地波特率为9600
    fibo_taskSleep(50);
    serialWriter((u8 *)cmd_baud_115200, length);//设置M8U波特率为115200
    fibo_taskSleep(50);
    serialWriter((u8 *)cmd_baud_115200, length);//设置M8U波特率为115200 两遍为了保证
    fibo_taskSleep(50);

    uart_initial(UART_PORT_UART3, 115200, 70);//修改本地波特率为115200
    fibo_taskSleep(50);
}

static u32 g_pvtMissTimes = 0, g_attMissTimes = 0, g_hnrMissTimes = 0, g_agcMissTimes = 0;
static u8 g_hnrFix = 0;
static float g_hnrHeadVeh = 0, g_hnrVariance = 0;
void Ublox_M8U_procUbloxMsg(u8 *msg, s16 len)  //解析M8U角度和陀螺仪相关数据
{
    for(int pos = 0; pos < len; pos++)
    {
        DATA *pData = data_getData();
        if(msg[pos] == 0xB5 && msg[pos + 1] == 0x62)//找到B562数据包
        {
            UBLOX_HEAD_DATA *ublox_data = (UBLOX_HEAD_DATA *)(msg + pos);

            if(ublox_data->Class == 0x01 && ublox_data->id == 0x07)  //PVT校准数据
            {
                if(len - pos < sizeof(UBLOX_FIX_DATA))
                {
                    break;
                }
                g_pvtMissTimes = 0;
                UBLOX_FIX_DATA* fix_data = (UBLOX_FIX_DATA*)ublox_data;
                data_getData()->fixtype = fix_data->fixType;
                pData->headingAngle = (float)fix_data->headVeh * 1e-5; //方向角（小数格式)
                pos = pos + sizeof(UBLOX_HEAD_DATA) + ublox_data->length + 2 - 1;//-1 是往前挪一位重复判断
                continue;
            }
            else if(ublox_data->Class == 0x01 && ublox_data->id == 0x05) //ATT数据
            {
                if(len - pos < sizeof(UBLOX_ATTITUDE_DATA))
                {
                    break;
                }
                g_attMissTimes = 0;
                UBLOX_ATTITUDE_DATA *att_data = (UBLOX_ATTITUDE_DATA *)ublox_data;
                data_getData()->accHeading = (u32)(att_data->accHeading * 1e-5); //方向精度因子
                pos = pos + sizeof(UBLOX_HEAD_DATA) + ublox_data->length + 2 - 1;//-1 是往前挪一位重复判断
                continue;
            }
            else if(ublox_data->Class == 0x01 && ublox_data->id == 0x37) //HNR数据判断 (由于陀螺仪HNR数据输出频率为4HZ，1秒内比nmea数据多三个包)
            {
                if(len - pos < sizeof(UBLOX_HNR_DATA))
                {
                    break;
                }
                g_hnrMissTimes = 0;
                UBLOX_HNR_DATA* hnr_data = (UBLOX_HNR_DATA*)ublox_data;
                g_hnrHeadVeh = (float)hnr_data->headVeh * 1e-5;
                g_hnrFix = hnr_data->gpsFix;
                pos = pos + sizeof(UBLOX_HEAD_DATA) + ublox_data->length + 2 - 1;//-1 是往前挪一位重复判断
                continue;
            }
            else if(ublox_data->Class == 0x0A && ublox_data->id == 0x09) //解析天线自动增益参数
            {
                if(len - pos < sizeof(UBLOX_MON_HW_DATA))
                {
                    break;
                }
                g_agcMissTimes = 0;
                UBLOX_MON_HW_DATA* mon_data = (UBLOX_MON_HW_DATA*)ublox_data;
                data_getData()->agcCnt = (float)mon_data->agcCnt;
                pos = pos + sizeof(UBLOX_HEAD_DATA) + ublox_data->length + 2 - 1;//-1 是往前挪一位重复判断
                LOG_DEBUG("AGC ratio..................%d", (int)(1000 * mon_data->agcCnt / 8191.0f));
                continue;
            }
        }
    }
}

static double Ublox_M8U_cal_variance(double *data,u8 len)  //计算数组方差
{
    double avr = 0;
    double sum = 0;
    double variance;
    int i;

    if(len < 1)
    {
        return -1;
    }  
    for(i = 0;i < len;i++)
    {
        avr += data[i];    
    }
    avr = (double)(avr / len);
    i = 0;
    for(;i < len ;i++)
    {
        sum += (avr - data[i]) * (avr - data[i]);
    }
    variance = (double)(sum / len);
    
    return variance;
}

#define M8U_TIMES (8)
#define GPS_VALID_SPEED (10)
#define GPS_VALID_VARIANCE (5)
#define GPS_SAT_NUM (6)
#define GPS_DIR_LIMIT (130)

int Ublox_M8U_cal_hnr(void)     //每秒抓取4个HNR数据包，计算方差值并保存，根据方差大小判断车子是否在直行
{
    static double hnr_dir[M8U_TIMES] = {0};
    static u8 times = 0;
    static u32 last_hnrSec = -1;
    u32 cur_hnrSec = (u32)rtc_getTimestamp();

    if((abs(cur_hnrSec - last_hnrSec) < 2) || (-1 == last_hnrSec))         //判断相邻两次数据采样时间间隔在1秒内
    {
        //控制器速度大于10km/h满足条件,并且目前是惯导状态
        if((gps_getPosition()->nmeaInfo.speed > GPS_VALID_SPEED || data_getRealEtcSpeed() > GPS_VALID_SPEED) && 
            (DIR_DR_STATUS == g_hnrFix || DIR_INS_STATUS == g_hnrFix) && data_getData()->isWheelSpinning) 
        {   
            hnr_dir[times] = (double)g_hnrHeadVeh;
            times++;
            if(times > M8U_TIMES - 1)
            {
                times = 0;
                g_hnrVariance = Ublox_M8U_cal_variance(hnr_dir,M8U_TIMES);  //当完成8个数据采集后，求方向角方差
            }
        }
    }
    else   //不在采样时间间隔内的数据无效，此时重新采样4个数据
    {
        times = 0;
    }
    last_hnrSec = cur_hnrSec;
    return 0;
}

int Ublox_M8U_reset_state(void)     //惯导状态异常检测算法
{
    static u8 last_heading = -1;
    u8 cur_heading = data_getData()->headingAngle;

    //进入惯导状态异常检测算法大前提：
    //1.车子在直行（根据方差判断）;2.当前有GPS定位，且信号优良（根据HDOP、卫星数等）;3.车速和GPS运行速度大于一定值;
    if((gps_getPosition()->nmeaInfo.speed > GPS_VALID_SPEED || data_getRealEtcSpeed() > GPS_VALID_SPEED) &&
        gps_getPosition()->nmeaInfo.satinfo.inuse >= GPS_SAT_NUM && gps_getPosition()->nmeaInfo.HDOP < 2 &&
        gps_getPosition()->isGPS && g_hnrVariance < GPS_VALID_VARIANCE && data_getData()->isWheelSpinning)
    {
        double tmp_dir = abs(data_getData()->lastPosition.nmeaInfo.direction - (double)data_getData()->headingAngle);

        //当前是惯导状态并且GPS方位角与ATT方向角差值超过一定值时，认为此时惯导状态异常，对M8U进行复位操作
        if(tmp_dir >= GPS_DIR_LIMIT && (DIR_INS_STATUS == data_getData()->fixtype || DIR_DR_STATUS == data_getData()->fixtype) && 
           last_heading != -1 && last_heading != cur_heading)
        {
            Ublox_M8U_userReset(); //复位M8U
            data_getData()->resetFixnum++;
        }
    }
    last_heading = cur_heading;
    return 0;
}

#define M8U_CHECK_TIMES 30
int Ublox_M8U_state_handle(void) //每隔1秒检测一次M8U当前状态
{
    GPS_STATE newGpsState = gps_getPosition()->nmeaInfo.gpsState;
    static GPS_STATE lastGpsState = GPS_FIX_NOT_VALID;
    static u16 GpsStateCount = 0;
    static u8 errorLevel = 0;

    //若M8U持续M8U_CHECK_TIMES秒内没有输出PVT、ATT、HNR或AGC数据，对M8U重新进行相应配置
    if(g_pvtMissTimes > M8U_CHECK_TIMES)
    {
        g_pvtMissTimes = 0;
        Ublox_M8U_enablePVT();
    }

    if(g_attMissTimes > M8U_CHECK_TIMES)
    {
        g_attMissTimes = 0;
        Ublox_M8U_enableATT();
    }

    if(g_hnrMissTimes > M8U_CHECK_TIMES)
    {
        g_hnrMissTimes = 0;
        Ublox_M8U_setHNROutputRate();
        fibo_taskSleep(100);
        Ublox_M8U_setHNRmsg();
    }

    if(g_agcMissTimes > 5)
    {
        g_agcMissTimes = 0;
        Ublox_M8U_enableMonHW();
    }

    if(newGpsState == lastGpsState && (newGpsState == GPS_ESTIMATING || newGpsState == GPS_FIX_NOT_VALID))
    {
        GpsStateCount++;
        if(GpsStateCount > 2 * 60) //2分钟内保持在异常状态，则重置M8U以期望恢复
        {
            if(errorLevel == 0)
            {
                Ublox_M8U_config(); //修改配置，预计2s内
                errorLevel = 1;
                GpsStateCount = 0;
            }
            else if(errorLevel == 1)
            {
                Ublox_hotRestart(); //热启动
                errorLevel = 2;
                GpsStateCount = 0;
            }
            else if(errorLevel == 2)
            {
                Ublox_coldRestart(); //冷启动
                errorLevel = 3;
                GpsStateCount = 0;
            }
            else if(errorLevel == 3)
            {
                gps_moudleReset(); //硬件重启
                errorLevel = 0;
                GpsStateCount = 0;
            }
        }
    }
    else if(newGpsState != lastGpsState)
    {
        GpsStateCount = 0;
    }

    if(newGpsState == GPS_FIX || newGpsState == GPS_DGPS || newGpsState == GPS_RTK_FIX || newGpsState == GPS_RTK_FLOAT)
    {
        errorLevel = 0; //恢复定位则重置异常等级
    }
    lastGpsState = newGpsState;

    g_pvtMissTimes++;
    g_attMissTimes++;
    g_hnrMissTimes++;
    g_agcMissTimes++;
    return 0;
}

void Ublox_M8U_config(void)
{
    Ublox_M8U_init(gps_uart_send); //初始化M8U的波特率
    fibo_taskSleep(50);
    Ublox_M8U_EraseFlash();        //擦除M8U的flash重新进行配置
    fibo_taskSleep(100);
    Ublox_M8U_init(gps_uart_send); //再次初始化M8U的波特率
    fibo_taskSleep(100);
    Ublox_M8U_configNAV5();        //配置惯导模式
    fibo_taskSleep(100);
    Ublox_M8U_configNAV5();        //配置惯导模式 两次做保证
    fibo_taskSleep(100);
    Ublox_M8U_initNMEAConfig();    //配置nmea数据输出参数
    fibo_taskSleep(100);
    Ublox_M8U_configGNSS();        //配置输出GPS+北斗+伽利略nmea数据
    fibo_taskSleep(100);
    Ublox_M8U_enablePVT();         //使能输出PVT数据
    fibo_taskSleep(100);
    Ublox_M8U_enableATT();	       //使能输出ATT方向角数据
    fibo_taskSleep(100);
    Ublox_M8U_enableMonHW();	   //使能输出天线增益数据
    fibo_taskSleep(100);
    Ublox_M8U_setInstallAngle();   //将校准的安装角写入M8U
    fibo_taskSleep(100);
    Ublox_M8U_setInstallAngle();  //将校准的安装角写入M8U 两次做保证
    fibo_taskSleep(100);
    Ublox_M8U_setNMEAOutputRate(); //设置nmea数据输出频率为1HZ
    fibo_taskSleep(100);
    Ublox_M8U_setHNROutputRate();  //设置陀螺仪HNR数据输出频率为4HZ
    fibo_taskSleep(100);
    Ublox_M8U_setHNRmsg();         //使能输出HNR数据
    fibo_taskSleep(100);
    Ublox_M8U_setAccel();         //配置加速度计参数
    fibo_taskSleep(100);
    Ublox_M8U_setGyro();          //配置陀螺仪参数
    fibo_taskSleep(100);
    Ublox_M8U_saveCfgToFlash();   //保持配置到M8U的flash中
}

/****************************************************************************************
*                     以下是跟M8U+MPU6500定向停车方案相关配置                                         *
*****************************************************************************************/
static int Ublox_M8U_baudrate_init(L_BOOL isNeedEraseFlash)
{
    u16 length = sizeof(cmd_baud_9600);

    uart_initial(UART_PORT_UART3, 9600, 70);//修改本地波特率为9600
    
    if(isNeedEraseFlash)
    {
        Ublox_M8U_EraseFlash();
        fibo_taskSleep(50);
    }
    serialWriter((u8 *)cmd_baud_9600, length);//设置M8U波特率为9600
    fibo_taskSleep(50);
    serialWriter((u8 *)cmd_baud_9600, length);//设置M8U波特率为9600 两遍为了保证
    fibo_taskSleep(50);
    Ublox_M8U_configNAV5();        //配置惯导模式
    fibo_taskSleep(100);
    Ublox_M8U_configNAV5();        //配置惯导模式 两次做保证
    fibo_taskSleep(100);
    Ublox_M8U_initNMEAConfig();    //配置nmea数据输出参数
    fibo_taskSleep(100);
    Ublox_M8U_configGNSS();        //配置输出GPS+北斗+伽利略nmea数据
    fibo_taskSleep(100);

    if(!timer_isTimerStart(TIMER_UBLOX_MODE_PROC))
    {
        timer_startRepeat(TIMER_UBLOX_MODE_PROC, TIMER_S, 1, ublox_ModeSwitch);
    }
    if(setting.statusConf.gpsBaudrateUpdateFlag)
    {
        LOG_INFO("gps baudrate adjust success!");
    }
    return 0;
}

static int Ublox_M8U_baudrate_adjust_cb(void)
{
    if(!setting.statusConf.gpsBaudrateUpdateFlag) //波特率不对,进行调整
    {
        u16 length = sizeof(cmd_baud_9600);
        uart_initial(UART_PORT_UART3, 9600, 70);//修改本地波特率为9600
        fibo_taskSleep(50);
        serialWriter((u8 *)cmd_baud_9600, length);//设置M8U波特率为9600
        fibo_taskSleep(50);
        serialWriter((u8 *)cmd_baud_9600, length);//设置M8U波特率为9600 两遍为了保证
        fibo_taskSleep(50);
        Ublox_M8U_baudrate_init(L_TRUE);
        agps_initail();
        Ublox_gotoAwake();
    }
    return 0;
}

static void Ublox_M8U_baudrate_adjust(void) //调整波特率
{
    u16 length = sizeof(cmd_baud_9600);
    
    uart_initial(UART_PORT_UART3, 115200, 70);//修改本地波特率为115200
    fibo_taskSleep(50);
    serialWriter((u8 *)cmd_baud_9600, length);//设置M8U波特率为9600
    fibo_taskSleep(50);
    serialWriter((u8 *)cmd_baud_9600, length);//设置M8U波特率为9600 两遍为了保证
    fibo_taskSleep(50);
    Ublox_M8U_baudrate_init(L_TRUE);
    timer_start(TIMER_GPSBAUD_DELAY, TIMER_S, 5, Ublox_M8U_baudrate_adjust_cb);
}

void Ublox_M8U_baudrate_handle(PORT_WRITER uart_writer)
{
    serialWriter = uart_writer;

    if(!setting.statusConf.gpsBaudrateUpdateFlag)
    {
        Ublox_M8U_baudrate_adjust();
    }
    else
    {
        Ublox_M8U_baudrate_init(L_FALSE);
    }
}
