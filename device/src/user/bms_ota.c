#include "log.h"
#include "car.h"
#include "data.h"
#include "setting.h"
#include "types.h"
#include "da14580.h"
#include "bioMsg.h"
#include "bms_ota.h"
#include "etcMsg.h"

u8 isBMSUpgrading = 0;

u8 bmsOta_GetUpgrading(void)
{
    return isBMSUpgrading;
}

u8 bmsOta_SetUpgrading(u8 isUpgrading)
{
    isBMSUpgrading = isUpgrading;
    return 0;
}

int bmsOta_upgardeTimerHandler(void) //开始BMS升级
{
    //设防状态下开始升级，且控制器和BMS无法同时进行OTA升级
    if(setting.statusConf.isDefend && setting.statusConf.bmsUpgradeFlag == 1 && !isBMSUpgrading && !setting.statusConf.etcUpgradeFlag)
    {
        memset((u8 *)&data_getData()->bms, 0 ,sizeof(BMS)); //升级前清除掉BMS数据,确保升级后查询到的为实时数据
        setting.statusConf.bmsSoc = 0;
        da14580_sendDATA(BIO_ADDRESS, CMD_BIO_PING, NULL, 0); //OTA开始升级，喂狗一次
        da14580_setHeartbeat(L_FALSE); //关闭蓝牙心跳，以免干扰OTA升级
        isBMSUpgrading = 1;
        etcMsg_SendBmsStartPAC();
        statusConf_save();
    }
    return 0; 
}

