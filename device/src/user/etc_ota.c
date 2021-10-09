#include "log.h"
#include "car.h"
#include "data.h"
#include "etc_ota.h"
#include "etcMsg.h"
#include "setting.h"
#include "types.h"
#include "da14580.h"
#include "bioMsg.h"

u8 isETCUpgrading = 0;

u8  etcOta_getUpgrading(void)
{
    return isETCUpgrading;
}

u8  etcOta_setUpgrading(u8 isUpgrading)
{
    isETCUpgrading = isUpgrading;
    return isETCUpgrading;
}

int etcOta_upgardeTimerHandler(void) //开始ETC升级
{
    //设防状态下开始升级，且控制器和BMS无法同时进行OTA升级
    if(setting.statusConf.isDefend && setting.statusConf.etcUpgradeFlag == 1 && !etcOta_getUpgrading() && !setting.statusConf.bmsUpgradeFlag)
    {
        memset((u8 *)&data_getData()->etc, 0 ,sizeof(ETC)); //升级前清除掉ETC数据,确保升级后查询到的为实时数据
        da14580_sendDATA(BIO_ADDRESS, CMD_BIO_PING, NULL, 0); //OTA开始升级，喂狗一次
        da14580_setHeartbeat(L_FALSE); //关闭蓝牙心跳，以免干扰OTA升级
        car_accOn();
        etcOta_setUpgrading(L_TRUE);
        etcMsg_SendEtcStartPAC();
    }
    return 0;
}

