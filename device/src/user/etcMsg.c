/*
 * etcMsg.c
 *
 *  Created on: 2018/06/03
 *      Author: lc
 */
#include <string.h>

#include <fibo_opencpu.h>

#include "log.h"
#include "msg.h"
#include "data.h"
#include "flash.h"
#include "async.h"
#include "car.h"
#include "etcMsg.h"
#include "da14580.h"
#include "setting.h"
#include "hardware.h"
#include "user_timer.h"
#include "bioMsg.h"
#include "user_fs.h"
#include "etc_ota.h"
#include "bms_ota.h"
#include "ETC_TaiBite.h"
#include "ETC_XiaoAn.h"
#include "BMS_XiaoAn.h"
#include "BMS_XingHeng.h"
#include "RFID.h"

/*
 * ETC OTA global parameters
 */
u8 *g_etcFirmwareData = NULL;
u8 *g_etcFirmwareDataP = NULL;
u16 g_etcPackID = 0;
u16 g_etcSendCompleteFlag = 0;
u16 g_etcResendLenBak = 0;
u32 g_etcFirmwareDataBytes = 0;
u16 g_etcSendDataLenPerTime = 0;
u16 g_etcRetransferCnt = 0;
u16 g_etcReupgradeCnt = 0;
u16 g_etcResendCommpleteDataCnt = 0;

/*
 * BMS OTA global parameters
 */
u8 *g_bmsFirmwareData = NULL;
u8 *g_bmsFirmwareDataP = NULL;
u16 g_bmsPackID = 0;
u16 g_bmsSendCompleteFlag = 0;
u16 g_bmsResendLenBak = 0;
u32 g_bmsFirmwareDataBytes = 0;
u16 g_bmsSendDataLenPerTime = 0;
u16 g_bmsRetransferCnt = 0;
u16 g_bmsReupgradeCnt = 0;
u16 g_bmsResendCompleteDataCnt = 0;

static int etcMsg_etcProcHandler(void);
static void etcMsg_otaRebootAction(void);

#define MAX_ASYNC_ARRAY_COUNT (100)
static volatile int async_procs_size = 0;
static volatile ASYNC_PROC_MAP async_procs[MAX_ASYNC_ARRAY_COUNT] = {0};
static int etcMsg_getAsyncProcsIdx(u8 address, u8 cmd)
{
    int i = 0;
    for(; i < MAX_ASYNC_ARRAY_COUNT; i++)
    {
        if(cmd == async_procs[i].cmd && address == async_procs[i].address)
        {
            break;//寻找到相同的地址符和命令字了,返回当时注册的
        }
        else if(async_procs[i].cmd == 0 && async_procs[i].address == 0)
        {
            break;//已经走到了空余的地方,说明没有注册,返回新的idx
        }
    }

    if(i >= MAX_ASYNC_ARRAY_COUNT)
    {
        return -1;
    }

    if(i >= async_procs_size)
    {
        async_procs_size = i + 1;
    }

    return i;
}

int etcMsg_getAsyncProcsSize(void)
{
    return async_procs_size;
}

ASYNC_PROC_MAP *etcMsg_getAsyncProcs(void)
{
    return (ASYNC_PROC_MAP *)async_procs;
}

/*
*   RFID下行协议逻辑
*/
static void RFID_Initial(void)
{
    etcMsg_setAsyncHandler(RFID_ADDRESS, CMD_GET_CARDID_RSP, NULL, RFID_getCardIDRsp, NULL, L_FALSE);
    etcMsg_setAsyncHandler(RFID_ADDRESS, CMD_GET_VERSION_RSP, NULL, RFID_versionRsp, NULL, L_FALSE);
}

static int da14580_getRFIDCardIDAction(void)
{
    RFID_getCardID();
    return 0;
}

static int da14580_getRFIDVersionAction(void)
{
    RFID_getDeviceVersion();
    return 0;
}

void etcMsg_setRFIDETCHandler(uint8_t address, uint8_t cmd, ASYNC_PROC action, ASYNC_MSG_PROC msgProc, ASYNC_RESPONSE_PROC responseAction)
{
    int i = etcMsg_getAsyncProcsIdx(address, cmd);
    if(i < 0) return;
    async_procs[i].cmd = cmd;
    async_procs[i].address = address;
    async_procs[i].time = 10; // N * TIMER_MAIN_LOOP_PERIOD
    async_procs[i].actionTimes = 0;
    async_procs[i].param = NULL;
    async_procs[i].action = action;
    async_procs[i].msgProc = msgProc;
    async_procs[i].responseAction = responseAction;
}

static void da14580_getRFIDCardID(void)//
{
    etcMsg_setRFIDETCHandler(RFID_ADDRESS, CMD_GET_CARDID_RSP, da14580_getRFIDCardIDAction, RFID_getCardIDRsp, NULL);
}

static void da14580_getRFIDVersion(void)//
{
    etcMsg_setRFIDETCHandler(RFID_ADDRESS, CMD_GET_VERSION_RSP, da14580_getRFIDVersionAction, RFID_versionRsp, NULL);
}

typedef void (*GET_RFID_DATA_LOOP)(void);
typedef struct
{
    GET_RFID_DATA_LOOP fun;
} GET_RFID_DATA_LOOP_MAP;

static const GET_RFID_DATA_LOOP_MAP getRFIDDataLoopMap[] = 
{
    {da14580_getRFIDCardID},
//    {da14580_getRFIDVersion}, //暂时不需要读RFID版本号
};

static void da14580_getRFIDLoop(void)
{
    static u8 i = 0;
    if(i >= sizeof(getRFIDDataLoopMap)/sizeof(getRFIDDataLoopMap[0]))
    {
        i = 0;
    }
    if(getRFIDDataLoopMap[i].fun)
    {
        getRFIDDataLoopMap[i].fun();
    }
    i++;
}

void etcMsg_etcInitial(void)
{
    etcMsg_otaRebootAction(); //重启检测控制器或BMS是否需要升级

    //优先级: ETC > RFID > BMS
    /***************************ETC************************/
    if(setting.defaultConf.ccuType == TYPE_NOCCU)  //无控制器类型,不注册
    {
        LOG_INFO("[EtcMsg] Initial None ETC");
    }
    else if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)  //小安控制器协议
    {
        ETC_XiaoAn_Initial();
        LOG_INFO("[EtcMsg] Initial XiaoAn ETC");
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE
    || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
    || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
    || setting.defaultConf.ccuType == TYPE_TAIBITE_09) //泰比特控制器协议
    {
        ETC_TaiBiTe_Initial();
        LOG_INFO("[EtcMsg] Initial TaiBiTe ETC");
    }
    else
    {
        LOG_ERROR("[EtcMsg] ETC Config Error");
    }

    /***************************RFID************************/   
    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
    {
        RFID_Initial(); //注册RFID控制命令字
        LOG_INFO("[RFIDMsg] Initial RFID");
    }

    /***************************BMS************************/
    if(setting.defaultConf.bmsType == TYPE_NOBMS)  //无BMS类型,不注册
    {
        LOG_INFO("[EtcMsg] Initial None BMS");
    }
    else if(setting.defaultConf.bmsType == TYPE_XIAOANBMS)  //小安BMS协议
    {
        BMS_XiaoAn_Initial();
        LOG_INFO("[EtcMsg] Initial XiaoAn BMS");
    }
    else if(setting.defaultConf.bmsType == TYPE_XINGHENGBMS)
    {
        BMS_XingHeng_Initial();
        LOG_INFO("[EtcMsg] Initial XingHeng BMS");
    }
       
    timer_startRepeat(TIMER_ETC_LOOP, TIMER_MS, 200, etcMsg_etcProcHandler);  //开启控制器和BMS的轮询事件
}

void etcMsg_setETCHandler(uint8_t address, uint8_t cmd, ASYNC_PROC action, ASYNC_MSG_PROC msgProc, ASYNC_RESPONSE_PROC responseAction)
{
    int i = etcMsg_getAsyncProcsIdx(address, cmd);
    if(i < 0) return;
    async_procs[i].cmd = cmd;
    async_procs[i].address = address;
    async_procs[i].time = 20; // N * TIMER_MAIN_LOOP_PERIOD
    async_procs[i].actionTimes = 0;
    async_procs[i].param = NULL;
    async_procs[i].action = action;
    async_procs[i].msgProc = msgProc;
    async_procs[i].responseAction = responseAction;
}

void etcMsg_setETCHandlerOnce(uint8_t address, uint8_t cmd, ASYNC_PROC action, ASYNC_MSG_PROC msgProc, ASYNC_RESPONSE_PROC responseAction)
{
    int i = etcMsg_getAsyncProcsIdx(address, cmd);
    if(i < 0) return;
    if(async_procs[i].cmd == cmd && async_procs[i].address == address && async_procs[i].time != 0 && async_procs[i].action)
    {
        //如果当前命令已经注册了并且还没有执行完, 禁止执行单次注册, 避免影响重传
        return;
    }
    async_procs[i].cmd = cmd;
    async_procs[i].address = address;
    async_procs[i].time = 1; // N * TIMER_MAIN_LOOP_PERIOD
    async_procs[i].actionTimes = 0;
    async_procs[i].param = NULL;
    async_procs[i].action = action;
    async_procs[i].msgProc = msgProc;
    async_procs[i].responseAction = responseAction;
}

void etcMsg_setAsyncHandler(u8 address, u8 cmd, ASYNC_PROC action, ASYNC_MSG_PROC msgProc, ASYNC_RESPONSE_PROC responseAction, u8 isWaitRsp)
{
    int i = etcMsg_getAsyncProcsIdx(address, cmd);

    if(i < 0) return;

    async_procs[i].cmd = cmd;
    async_procs[i].address = address;
    async_procs[i].time = 20; // N * TIMER_MAIN_LOOP_PERIOD
    async_procs[i].actionTimes = 0;
    async_procs[i].param = NULL;
    async_procs[i].action = action;
    async_procs[i].msgProc = msgProc;
    async_procs[i].isWaitRsp = isWaitRsp;
    async_procs[i].responseAction = responseAction;
}

void etcMsg_getETCInfo(void)
{
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        ETC_XiaoAn_GetETCInfo();
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE
    || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
    || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
    || setting.defaultConf.ccuType == TYPE_TAIBITE_09)
    {
        ETC_TaiBiTe_GetETCInfo();
    }
    else
    {
        ;
    }
}

void etcMsg_getSOC(void)
{
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        ETC_XiaoAn_GetSOC();
    }
	else
    {
        ;
    }
}

void etcMsg_setETCAccOn(void)
{
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        ETC_XiaoAn_SetETCAccOn();
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE
    || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
    || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
    || setting.defaultConf.ccuType == TYPE_TAIBITE_09)
    {
        ETC_TaiBiTe_SetETCAccOn();
    }
    else
    {
        ;
    }
}

void etcMsg_setETCAccOnOnce(void)
{
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        ETC_XiaoAn_SetETCAccOnOnce();
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE
    || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
    || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
    || setting.defaultConf.ccuType == TYPE_TAIBITE_09)
    {
        ETC_TaiBiTe_SetETCAccOnOnce();
    }
    else
    {
        ;
    }
}

void etcMsg_setETCDefend(uint8_t isDefend)
{
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        ETC_XiaoAn_SetETCDefend(isDefend);
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE
    || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
    || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
    || setting.defaultConf.ccuType == TYPE_TAIBITE_09)
    {
        ETC_TaiBiTe_SetETCDefend(isDefend);
    }
}

void etcMsg_setETCDefendOnce(uint8_t isDefend)
{
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        ETC_XiaoAn_SetETCDefendOnce(isDefend);
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE
    || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
    || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
    || setting.defaultConf.ccuType == TYPE_TAIBITE_09)
    {
        ETC_TaiBiTe_SetETCDefendOnce(isDefend);
    }
}

void etcMsg_setETCLight(u8 state)
{
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        ETC_XiaoAn_SetLight(state);
    }
}

int etcMsg_MsgProc(uint8_t *data, uint16_t dataLen)
{
    return async_procMsg(data, etcMsg_getAsyncProcs(), etcMsg_getAsyncProcsSize());
}

static void etcMsg_etcinfoEmpty(void)
{
    memset((u8 *)&data_getData()->etc, 0, sizeof(ETC)); //通信故障清除掉ETC数据，避免查询残留
}

static int etcMsg_etcProcHandler(void)
{
    static uint32_t time = 0;
    
    /************************************* ETC ****************************************/
    if(car_isAccOn())
    {
        if(time % ((1 * 1000) / 200) == 0 && data_getData()->workMode == NORMAL_MODE && setting.defaultConf.ccuType != TYPE_NOCCU)
        {
            if(!setting.statusConf.bmsUpgradeFlag && !setting.statusConf.etcUpgradeFlag)
            {
                if(setting_isDefendOn())
                {
                    etcMsg_setETCDefendOnce(L_TRUE); //保障性设置
                }
                else
                {
                    if(setting.settingConf.isEtcAccProtect) //默认开
                    {
                        etcMsg_setETCAccOnOnce(); //保障性设置开电门
                    }

                    if(setting.settingConf.isEtcDefendProtect) //默认关
                    {
                        etcMsg_setETCDefendOnce(L_FALSE); //保障性设置撤防
                    }
                    etcMsg_getETCInfo(); //如果电门打开且处于没有设防,获取ETC信息
                }
                
                data_getData()->faultRecord.etcSendNoRspTimes++;
                if(data_getData()->faultRecord.etcSendNoRspTimes >= 4) //4s内收不到ETC应答,认为ETC通讯异常
                {
                    etcMsg_etcinfoEmpty(); //控制器无回复，清空ETC获取的信息，以避免控制器异常而导致数据不更新
                    data_getData()->faultRecord.etcSendNoRspTimes = 0;
                    data_getData()->faultRecord.isEtcRsp = L_FALSE;
                    data_getData()->faultRecord.EtcComm = L_FALSE;
                }
            }
        }
    }
    else
    {
        etcMsg_etcinfoEmpty(); //电门关闭,清空ETC获取的信息,置位控制器未通讯标志
        data_getData()->faultRecord.EtcComm = L_FALSE;
    }

    /************************************* RFID ****************************************/
    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
    {        
        if(time % ((1 * 400) / 200) == 0) //每400ms获取一次RFID信息
        {
            if(car_isAccOn() || data_getData()->isRFIDPowerOn)
            {
                if(data_getData()->isReadRFIDVersion == L_TRUE) //只获取一次版本号
                {
                    data_getData()->isReadRFIDVersion = L_FALSE;
                    da14580_getRFIDVersion(); //获取RFID的app版本号
                }
                da14580_getRFIDCardID(); //读RFID卡号
                data_getData()->faultRecord.rfidSendNoRspTimes++;
                if(data_getData()->faultRecord.rfidSendNoRspTimes >= 10) //4s内收不到RFID应答,认为RFID通讯异常
                {
                    data_getData()->faultRecord.rfidSendNoRspTimes = 0;
                    data_getData()->faultRecord.isRFIDRsp = L_FALSE;
                }
            }
        }
    }
    
    /************************************* BMS ****************************************/
    if(time % ((1 * 1000) / 200) == 0)
    {
        if(!setting.statusConf.bmsUpgradeFlag && !setting.statusConf.etcUpgradeFlag)
        {
            if(data_getData()->workMode == NORMAL_MODE && setting.defaultConf.bmsType != TYPE_NOBMS)
            {                
                if(setting.defaultConf.bmsType == TYPE_XIAOANBMS)
                {
                    BMS_XiaoAn_LoopGetData();
                }
                else if(setting.defaultConf.bmsType == TYPE_XINGHENGBMS)
                {
                    BMS_XingHeng_getBMSDataLoop();
                }
                
                data_getData()->faultRecord.bmsSendNoRspTimes++;
                if(data_getData()->faultRecord.bmsSendNoRspTimes >= 4) //4s内收不到BMS应答,认为BMS通讯异常
                {
                    data_getData()->faultRecord.bmsSendNoRspTimes = 0;
                    data_getData()->faultRecord.isBmsRsp = L_FALSE;
					data_getData()->faultRecord.BmsComm = L_FALSE;
                }
            }
			if(data_getData()->workMode == NORMAL_MODE && setting.settingConf.isEtcSOC && car_isAccOn())
			{
                etcMsg_getSOC();
			}
        }
    }
    async_procTimeout(etcMsg_getAsyncProcs(), etcMsg_getAsyncProcsSize());
    time++;
    return 0;
}

//控制器OTA升级
void etcMsg_ETCOTA_Failed(void)
{
    car_accOff();
    da14580_sendDATA(BIO_ADDRESS, CMD_BIO_PING, NULL, 0);
    da14580_setHeartbeat(L_TRUE);
    setting.statusConf.etcUpgradeFlag = 0;  //升级标志清零 不再进行升级
    setting.statusConf.isTerminateETCUpgrade = 0;
    etcOta_setUpgrading(L_FALSE);
    statusConf_save();
    fs_deleteFile(UPGRADE_ETC_FILE_NAME);
    timer_stop(TIMER_ETC_RETRANSFER);
    timer_stop(TIMER_ETC_UPGRADE);
    timer_stop(TIMER_ETC_DELAY);
    Free(g_etcFirmwareDataP);
    g_etcFirmwareDataP = NULL;
    LOG_DEBUG("[etcMsg] *************** ETC OTA END >>> FAILED **************");
}

int etcMsg_ETCStartOTAUpgrade(void)
{
    static u8 ETCstartUpgrade_times = 0;
    LOG_DEBUG("[etcMsg] *************** StartOTA_UpgradeTimers:%d **************",ETCstartUpgrade_times);
    if(setting.statusConf.isTerminateETCUpgrade || ETCstartUpgrade_times++ >= 20)//如果要强行终止控制器升级或超过一分钟不回复说明该控制器不支持升级，升级终止
    {
        ETCstartUpgrade_times = 0;
        etcMsg_ETCOTA_Failed();
        return -1;
    }

    timer_start(TIMER_ETC_RETRANSFER, TIMER_S, 3, etcMsg_ETCStartOTAUpgrade);

    ETC_XiaoAn_OTAStart();
    return 0;
}

int etcMsg_SendEtcOTARealData(void)
{
    if(setting.statusConf.isTerminateETCUpgrade)//如果要强行终止控制器升级
    {
        etcMsg_ETCOTA_Failed();
        return -1;
    }
    ETC_XiaoAn_OTARealData();
    return 0;
}

int etcMsg_SendEtcOTAComplete(void)
{
    LOG_DEBUG("[etcMsg] *************** etcResendCommpleteDataCnt:%d **************",g_etcResendCommpleteDataCnt);
    if(setting.statusConf.isTerminateETCUpgrade)//如果要强行终止控制器升级
    {
        etcMsg_ETCOTA_Failed();
        return -1;
    }
    if(g_etcResendCommpleteDataCnt++ > 5)
    {
        g_etcResendCommpleteDataCnt = 0;
        timer_stop(TIMER_ETC_RETRANSFER);
        Free(g_etcFirmwareDataP);
        g_etcFirmwareDataP = NULL;
        etcOta_setUpgrading(L_FALSE);
    }
    timer_start(TIMER_ETC_RETRANSFER, TIMER_S, 2, etcMsg_SendEtcOTAComplete);
    ETC_XiaoAn_OTAComplete();
    return 0;
}

static int etcMsg_readEtcUpdateFile(void)
{
    int filesize = fs_getFileSize(UPGRADE_ETC_FILE_NAME);
    if(g_etcFirmwareDataP)
    {
        Free(g_etcFirmwareDataP);
        g_etcFirmwareDataP = NULL;
    }
    g_etcFirmwareDataP = Malloc(filesize);
    fs_getFileData(UPGRADE_ETC_FILE_NAME,(u8 *)g_etcFirmwareDataP,filesize + 1);
    g_etcFirmwareDataBytes = filesize;
    if(!g_etcFirmwareDataP)
    {
        Free(g_etcFirmwareDataP);
        return -1;
    }
    g_etcFirmwareData = g_etcFirmwareDataP;

    return 0;
}

void etcMsg_SendEtcStartPAC(void)
{
    g_etcPackID = 0;
    g_etcSendCompleteFlag = 0;
    g_etcRetransferCnt = 0;
    if(etcMsg_readEtcUpdateFile() == 0)
    {
        etcMsg_ETCStartOTAUpgrade();
    }
}

//bms ota 升級
void etcMsg_BMSOTA_Failed(void)
{
    car_accOff();
    da14580_sendDATA(BIO_ADDRESS, CMD_BIO_PING, NULL, 0);
    da14580_setHeartbeat(L_TRUE);
    setting.statusConf.bmsUpgradeFlag = 0;
    setting.statusConf.isTerminateBMSUpgrade = 0;
    bmsOta_SetUpgrading(L_FALSE);
    statusConf_save();
    fs_deleteFile(UPGRADE_BMS_FILE_NAME);
    timer_stop(TIMER_BMS_RETRANSFER);
    timer_stop(TIMER_BMS_UPGRADE);
    timer_stop(TIMER_BMS_DELAY);
    Free(g_bmsFirmwareDataP);
    g_bmsFirmwareDataP = NULL;
}

int etcMsg_BMSStartOTAUpgrade(void)
{
    static u8 BMSstartUpgrade_times = 0;

    if(setting.statusConf.isTerminateBMSUpgrade || BMSstartUpgrade_times++ >= 20)//如果要强行终止控制器升级
    {
        etcMsg_BMSOTA_Failed();
        BMSstartUpgrade_times = 0;
        return -1;
    }
    timer_start(TIMER_BMS_RETRANSFER, TIMER_S, 3, etcMsg_BMSStartOTAUpgrade);
    BMS_XiaoAn_OTAStart();
    return 0;
}

int etcMsg_SendBmsRealData(void)
{
    if(setting.statusConf.isTerminateBMSUpgrade)//如果要强行终止控制器升级
    {
        etcMsg_BMSOTA_Failed();
        return -1;
    }
    BMS_XiaoAn_OTARealData();
    return 0;
}

int etcMsg_SendBmsOTAComplete(void)
{
    if(setting.statusConf.isTerminateBMSUpgrade)
    {
        etcMsg_BMSOTA_Failed();
        return -1;
    }
    if(g_bmsResendCompleteDataCnt++ > 5)
    {
        g_bmsResendCompleteDataCnt = 0;
        timer_stop(TIMER_BMS_RETRANSFER);
        Free(g_bmsFirmwareDataP);
        g_bmsFirmwareDataP = NULL;
        bmsOta_SetUpgrading(L_FALSE);
    }
    timer_start(TIMER_BMS_RETRANSFER, TIMER_S, 2, etcMsg_SendBmsOTAComplete);
    BMS_XiaoAn_OTAComplete();
    return 0;
}

static int etcMsg_readBmsUpdateFile(void)
{
    int filesize = fs_getFileSize(UPGRADE_BMS_FILE_NAME);

    if(g_bmsFirmwareDataP)
    {
        Free(g_bmsFirmwareDataP);
        g_bmsFirmwareDataP = NULL;
    }

    g_bmsFirmwareDataP = Malloc(filesize);
    fs_getFileData(UPGRADE_BMS_FILE_NAME,(u8 *)g_bmsFirmwareDataP,filesize + 1);
    g_bmsFirmwareDataBytes = filesize;
    if(!g_bmsFirmwareDataP)
    {
        Free(g_bmsFirmwareDataP);
        g_bmsFirmwareDataP = NULL;
        return -1;
    }
    g_bmsFirmwareData = g_bmsFirmwareDataP;

    return 0;
}

void etcMsg_SendBmsStartPAC(void)
{
    g_bmsPackID = 0;
    g_bmsSendCompleteFlag = 0;
    g_bmsRetransferCnt = 0;

    if(etcMsg_readBmsUpdateFile() == 0)
    {
        etcMsg_BMSStartOTAUpgrade();
    }
    else
    {
        LOG_ERROR("[BMS] start OTA failed");
    }
}

static void etcMsg_otaRebootAction(void)
{
    if(setting.statusConf.etcUpgradeFlag)//重启检测是否需要升级控制器
    {
        timer_startRepeat(TIMER_ETC_UPGRADE, TIMER_S, 5, etcOta_upgardeTimerHandler);
    }
    if(setting.statusConf.bmsUpgradeFlag)//重启检测是否需要升级BMS
    {
        timer_startRepeat(TIMER_BMS_UPGRADE, TIMER_S, 5, bmsOta_upgardeTimerHandler);
    }
    return;
}

