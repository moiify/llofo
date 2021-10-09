#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cJSON/cJSON.h"
#include "nmea/gmath.h"
#include "utils.h"
#include "http.h"
#include "msg.h"
#include "log.h"
#include "data.h"
#include "audio.h"
#include "fence.h"
#include "bioMsg.h"
#include "audio_driver.h"
#include "types.h"
#include "device.h"
#include "setting.h"
#include "car.h"
#include "user_fs.h"
#include "version.h"
#include "user_at.h"
#include "user_timer.h"
#include "etcMsg.h"
#include "flash.h"
#include "device_msg.h"
#include "da14580.h"
#include "gps_parse.h"
#include "request.h"
#include "crc/crc16.h"
#include "etc_ota.h"
#include "bms_ota.h"
#include "RFID.h"
#include "socket.h"
#include "detect.h"
#include "ETC_TaiBiTe.h"

#define COV2MCC(imsi) (imsi[1]*100+imsi[2]*10+imsi[3])
#define COV2MNC(imsi) (imsi[4])
#define CHECK_TIME 5

static uint8_t g_isSetDefending = L_FALSE;
static uint8_t g_isForceLock = L_FALSE;

static APP_HEAD current_head = {"xiaoantech", {0}, {0}, {0}};

static int g_playAudio_idx = -1;
static int g_playAudio_volume = 100;
static int g_httpAudio_idx = -1;
static int g_httpAudio_crc = -1;

uint8_t device_isSetDefending(void)
{
    return g_isSetDefending;
}

uint8_t device_getCustomizedAudioIdx(void)
{
    return g_playAudio_idx;
}

static L_BOOL refeshAudioFinish(void)
{
    if(audio_isAudioplaying()) //语音播放结束后保存定制语音
    {
        timer_start(TIMER_REFRISH_AUDIO_FILE, TIMER_MS, 500, refeshAudioFinish);
        return L_FALSE;
    }

    audio_renameBak2Custom();
    return L_TRUE;
}

static int DynamicCustomAudio_cb(int result, uint8_t *data, int data_len) //下载定制语音，播放并存储
{
    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(g_httpAudio_crc == crc16)
        {
            audio_deleteBakAudio(g_httpAudio_idx);
            audio_saveBakAudio(data, data_len, g_httpAudio_idx);
            refeshAudioFinish();
            return 0;
        }
    }
    return -1;
}

static int device_DynamicCutsomAudio(int idx, char *url, int crc) //动态语音定制
{
    int ret = -1;

    ret = audio_getCustomAudioCrc(idx); //获取当前定制语音的crc以进行比对
    if(ret > 0 && ret == crc) //如果当前定制语音crc与下发的语音crc一致，则说明不再需要定制
    {
        LOG_INFO("already customed audio, idx: %d, crc: %d", idx, crc);
        return 0;
    }

    if(http_isProcing() == L_TRUE)
    {
        LOG_ERROR("http is procing!");
        return -1;
    }
    g_httpAudio_idx = idx; //保证开始下载才会更新存储id
    g_httpAudio_crc = crc;

    ret = http_get((u8 *)url, DynamicCustomAudio_cb); //下载并以备份语音存储，并等待无语音播放再存为定制语音
    if(ret != 0)
    {
        LOG_ERROR("http get custom audio failed, url: %s", url);
        return -1;
    }
    return 0;
}

static int device_PlayAudioWithParam(int index, const void *param)
{
    int vol = 100;

    if(!param)
    {
        return audio_play(index);
    }

    cJSON *idx = cJSON_GetObjectItem(param, "idx");
    cJSON *url = cJSON_GetObjectItem(param, "url");
    cJSON *crc = cJSON_GetObjectItem(param, "crc");
    cJSON *volume = cJSON_GetObjectItem(param, "volume");

    //更新目标语音音量
    if(volume && volume->valueint >= 0 && volume->valueint <= 100)
    {
        vol = volume->valueint;
    }

    //更新目标语音id
    if(idx && idx->valueint >= 0 && idx->valueint < AUDIO_MAX_NUMBER)
    {
        index = idx->valueint;

        //如果有正确的url和crc则运行动态语音定制逻辑
        if(url && strstr(url->valuestring, "http://") && crc && crc->valueint >= 0)
        {
            device_DynamicCutsomAudio(idx->valueint, url->valuestring, crc->valueint);
        }
    }
    g_playAudio_idx = index; //保存调用接口后需要播放的语音序号
    return audio_playWithVolume(index, vol);
}

//检查方向角是否在指定范围
//headingAngle: 实际方向角        targetDegree: 目标方向角        biasDegree: 目标角度偏差
static u8 device_checkIsDegreeMatching(int headingAngle, int targetDegree, int biasDegree)
{
    //设备未进惯导的情况
    if(data_isHeadingAngleFixed() == L_FALSE)
    {
        return DEGREE_NOT_FIXED;
    }

    int angleDiff = abs(targetDegree - headingAngle);
    if(angleDiff <= biasDegree || 360 - angleDiff <= biasDegree)
    {
        return DEGREE_MATCH; //角度在规定误差范围内
    }

    return DEGREE_OUT_OF_RANGE; //角度不在规定误差范围内
}

static int device_SetDeffendOnWithTBeaconRsp(const void *req, cJSON *param, beaconInfo_t *info, u8 isConsider90Degree)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *json_root = cJSON_CreateObject();
    cJSON *json_degree = cJSON_CreateObject();
    DATA *pData = data_getData();
    u8 tempData[24 + 1] = {0};
    u8 ret = 0;

    if(!root || !json_root || !json_degree)
    {
        if(root)
        {
            cJSON_Delete(root);
        }
        if(json_root)
        {
            cJSON_Delete(json_root);
        }
        if(json_degree)
        {
            cJSON_Delete(json_degree);
        }

        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        g_isSetDefending = L_FALSE;
        return L_FALSE;
    }    

    if((!setting_isDefendOn() || setting_isAccOn()) && data_getData()->isWheelSpinning) //设防的时候有轮动，直接返回
    {
        device_rspErr(req, ERR_CAR_NOT_STOP);
        g_isSetDefending = L_FALSE;
        return -1;
    }

    pData->isWaitingTBeaconResult = L_FALSE;
    if(info && info->dbm <= setting.settingConf.beaconRssi) //扫到道钉
    {
        LOG_INFO("scan daoding successful");
        ret = L_TRUE;
        cJSON_AddNumberToObject(json_root, "code", ERR_SUCCESS);
    }
    else
    {
        LOG_INFO("scan daoding fail");
        ret = L_FALSE;
        cJSON_AddNumberToObject(json_root, "code", ERR_OPERATION_ERROR);
    }

    //考虑90度定向停车功能
    if(isConsider90Degree)
    {
        cJSON *json_biasDegree = cJSON_GetObjectItem(param, "biasDegree"); //方向角偏差
        cJSON *json_targetDegree = cJSON_GetObjectItem(param, "targetDegree"); //目标方向角
        u8 tmp = 0;

        tmp = device_checkIsDegreeMatching((int)data_getData()->headingAngle, json_targetDegree->valueint, json_biasDegree->valueint);
        if(tmp == DEGREE_MATCH)
        {
            if(ret == L_TRUE) //只有道钉扫描成功，这里才把code置为0
            {
                cJSON_AddNumberToObject(json_root, "code", ERR_SUCCESS);
            }

            cJSON_AddNumberToObject(json_root, "code", ERR_SUCCESS);
            cJSON_AddNumberToObject(json_degree, "event", DEGREE_MATCH);
            cJSON_AddNumberToObject(json_degree, "Degree", data_getData()->headingAngle);
        }
        else if(tmp == DEGREE_OUT_OF_RANGE)
        {
            cJSON_AddNumberToObject(json_root, "code", ERR_OPERATION_ERROR);
            cJSON_AddNumberToObject(json_degree, "event", DEGREE_OUT_OF_RANGE);
            cJSON_AddNumberToObject(json_degree, "Degree", data_getData()->headingAngle);
            ret = L_FALSE;
        }
        else if(tmp == DEGREE_NOT_FIXED)
        {
            cJSON_AddNumberToObject(json_root, "code", ERR_OPERATION_ERROR);
            cJSON_AddNumberToObject(json_degree, "event", DEGREE_NOT_FIXED);
            ret = L_FALSE;
        }
        cJSON_AddItemToObject(root, "90degree", json_degree);
    }

    if(info && info->dbm <= setting.settingConf.beaconRssi) //扫到道钉
    {
        cJSON_AddNumberToObject(root, "event", EVENT_DEFENDONTBEACON);
        HexToAscii(info->mac, tempData, 6);
        cJSON_AddStringToObject(root, "tBeaconAddr", (const char *)tempData);
        if(strlen(info->tBeaconID) != 0) //浩源道钉才返回id,soc，vsn信息，其他默认没有
        {
            cJSON_AddStringToObject(root, "tBeaconId", (const char *)info->tBeaconID);
            cJSON_AddNumberToObject(root, "tBeaconSOC", info->tBeaconSOC);

            {
                u8 version_str[5] = {0};
                HexToAscii(info->tBeaconVersion, version_str, 2);
                cJSON_AddStringToObject(root, "TbeaconVsn", (const char *)version_str);
            }
        }
        else
        {
            cJSON_AddStringToObject(root, "tBeaconId", " ");
            cJSON_AddNumberToObject(root, "tBeaconSOC", 0);
            {
                u8 version_str[5] = {0};
                HexToAscii(info->tBeaconVersion, version_str, 2);
                cJSON_AddStringToObject(root, "TbeaconVsn", " ");
            }
        }
    }

    cJSON_AddNumberToObject(root, "defend", setting_isDefendOn());
    if(pData->lastPosition.isGPS)
    {
        cJSON_AddNumberToObject(root, "lon", gps_getGPSValue(pData->lastPosition.nmeaInfo.lon));
        cJSON_AddNumberToObject(root, "lat", gps_getGPSValue(pData->lastPosition.nmeaInfo.lat));
        cJSON_AddNumberToObject(root, "timestamp", pData->lastPosition.timestamp);
    }
    else
    {
        cJSON_AddNumberToObject(root, "lon", gps_getGPSValue(pData->lastPosition.lbsInfo.lon));
        cJSON_AddNumberToObject(root, "lat", gps_getGPSValue(pData->lastPosition.lbsInfo.lat));
        cJSON_AddNumberToObject(root, "timestamp", pData->lastPosition.lbsTimestamp);
    }
    cJSON_AddItemToObject(json_root, "result", root);
    device_responseJSONData(req, json_root);

    if(audio_isRFIDAudioDone())
    {
        fibo_audio_stop(); //打断RFID提示音
        fibo_taskSleep(500); //避免RFID提示音和还车语音同时播放
    }

    if(ret == L_TRUE)
    {
        setting_setDefend(L_TRUE);
        device_PlayAudioWithParam(AUDIO_DEFEND_ON, param);
    }
    else
    {
        audio_play(AUDIO_CAOZUOSHIBAI);
    }
    g_isSetDefending = L_FALSE;
    return 0;
}

//考虑道钉条件的还车逻辑
static int device_SetDeffendOnWithTBeacon(const void *req, cJSON *param, u8 isConsider90Degree)
{
    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return L_FALSE;
    }

    cJSON *isForce = cJSON_GetObjectItem(param, "force");

    if(!isForce || !isForce->valueint) //非强制锁车
    {
        beaconInfo_t *info = data_getTBeaconInfo(3);
        if(!info)
        {
            LOG_ERROR("no beacon info");
            audio_play(AUDIO_CAOZUOSHIBAI);
            device_rspErr(req, ERR_OPERATION_ERROR);
            g_isSetDefending = L_FALSE;
            return -1;
        }
        return device_SetDeffendOnWithTBeaconRsp(req, param, info, isConsider90Degree);
    }
    else //强制锁车
    {
        car_accOff();
        car_lockBackWheel();
        setting.statusConf.acc = L_FALSE;
        setting.statusConf.isDefend = L_TRUE;
    }

    if(audio_isRFIDAudioDone())
    {
        fibo_audio_stop(); //打断RFID提示音
        fibo_taskSleep(500); //避免RFID提示音和还车语音同时播放
    }
    device_PlayAudioWithParam(AUDIO_DEFEND_ON, param);
    device_rspErr(req, ERR_SUCCESS);
    g_isSetDefending = L_FALSE;
    return 0;
}

static int device_SetDefendOnWithRFIDRsp(const void *req, cJSON *param, u8 isConsider90Degree)
{
    DATA *pData = data_getData();

    cJSON *json_result = cJSON_CreateObject();
    cJSON *json_root = cJSON_CreateObject();
    cJSON *json_rfid = cJSON_CreateObject();
    cJSON *json_degree = cJSON_CreateObject();
    u8 ret = 0;

    if(!json_result || !json_root || !json_rfid || !json_degree)
    {
        if(json_result)
        {
            cJSON_Delete(json_result);
        }
        if(json_root)
        {
            cJSON_Delete(json_root);
        }
        if(json_rfid)
        {
            cJSON_Delete(json_rfid);
        }
        if(json_degree)
        {
            cJSON_Delete(json_degree);
        }
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        g_isSetDefending = L_FALSE;
        return -1;
    }

    if((!setting_isDefendOn() || setting_isAccOn()) && data_getData()->isWheelSpinning)
    {
        device_rspErr(req, ERR_CAR_NOT_STOP);
        g_isSetDefending = L_FALSE;
        return -1;
    }

    //未连接RFID模块或连接但未读到标签信息时返回136
    if(!data_getData()->isRFIDConnect || (data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal))
    {
        ret = L_FALSE;
        cJSON_AddNumberToObject(json_root, "code", ERR_OPERATION_ERROR);
    }
    else
    {
        ret = L_TRUE;
        cJSON_AddNumberToObject(json_root, "code", ERR_SUCCESS);
    }

    //考虑90度定向停车功能
    if(isConsider90Degree)
    {
        cJSON *json_biasDegree = cJSON_GetObjectItem(param, "biasDegree"); //方向角偏差
        cJSON *json_targetDegree = cJSON_GetObjectItem(param, "targetDegree"); //目标方向角
        u8 tmp = 0;

        tmp = device_checkIsDegreeMatching((int)data_getData()->headingAngle, json_targetDegree->valueint, json_biasDegree->valueint);
        if(tmp == DEGREE_MATCH)
        {
            if(ret == L_TRUE) //只有RFID成功，这里才把code置为0
            {
                cJSON_AddNumberToObject(json_root, "code", ERR_SUCCESS);
            }

            cJSON_AddNumberToObject(json_root, "code", ERR_SUCCESS);
            cJSON_AddNumberToObject(json_degree, "event", DEGREE_MATCH);
            cJSON_AddNumberToObject(json_degree, "Degree", data_getData()->headingAngle);
        }
        else if(tmp == DEGREE_OUT_OF_RANGE)
        {
            cJSON_AddNumberToObject(json_root, "code", ERR_OPERATION_ERROR);
            cJSON_AddNumberToObject(json_degree, "event", DEGREE_OUT_OF_RANGE);
            cJSON_AddNumberToObject(json_degree, "Degree", data_getData()->headingAngle);
            ret = L_FALSE;
        }
        else if(tmp == DEGREE_NOT_FIXED)
        {
            cJSON_AddNumberToObject(json_root, "code", ERR_OPERATION_ERROR);
            cJSON_AddNumberToObject(json_degree, "event", DEGREE_NOT_FIXED);
            ret = L_FALSE;
        }
        cJSON_AddItemToObject(json_result, "90degree", json_degree);
    }

    cJSON_AddNumberToObject(json_result, "defend", setting_isDefendOn());
    if(pData->lastPosition.isGPS)
    {
        cJSON_AddNumberToObject(json_result, "lon", gps_getGPSValue(pData->lastPosition.nmeaInfo.lon));
        cJSON_AddNumberToObject(json_result, "lat", gps_getGPSValue(pData->lastPosition.nmeaInfo.lat));
        cJSON_AddNumberToObject(json_result, "timestamp", pData->lastPosition.timestamp);
    }
    else
    {
        cJSON_AddNumberToObject(json_result, "lon", gps_getGPSValue(pData->lastPosition.lbsInfo.lon));
        cJSON_AddNumberToObject(json_result, "lat", gps_getGPSValue(pData->lastPosition.lbsInfo.lat));
        cJSON_AddNumberToObject(json_result, "timestamp", pData->lastPosition.lbsTimestamp);
    }

    if(data_getData()->isRFIDConnect && data_getData()->isCardIdLegal) //RFID读卡器已连接并且读到卡片
    {
        cJSON_AddNumberToObject(json_rfid, "event", RFID_SCAN_SUCCESS);
        cJSON_AddStringToObject(json_rfid, "id", pData->cardID);
    }
    else if(data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID读卡器已连接但未读取到卡片
    {
        cJSON_AddNumberToObject(json_rfid, "event", RFID_SCAN_NONE);
    }
    else
    {
        cJSON_AddNumberToObject(json_rfid, "event", RFID_DISCONNECT); //RFID未连接
    }

    cJSON_AddItemToObject(json_result, "RFID", json_rfid);
    cJSON_AddItemToObject(json_root, "result", json_result);
    device_responseJSONData(req, json_root);

    if(data_getData()->isRFIDPowerOn == L_TRUE)
    {
        car_closeRFIDPower_SetDeffend(); //立即关闭RFID 5v供电
    }

    //正常供电状态下，读取到合法卡片，并且方向角在设定误差范围内，执行设防动作
    if(audio_isRFIDAudioDone())
    {
        fibo_audio_stop(); //打断RFID提示音
        fibo_taskSleep(500); //避免RFID提示音和还车语音同时播放
    }

    if(ret == L_TRUE)
    {
        setting_setDefend(L_TRUE);
        device_PlayAudioWithParam(AUDIO_DEFEND_ON, param);
    }
    else
    {
        audio_play(AUDIO_CAOZUOSHIBAI);
    }
    g_isSetDefending = L_FALSE;
    return -1;
}

//考虑rfid条件的还车逻辑
static int device_SetDefendOnWithRFID(const void *req, cJSON *param, u8 isConsider90Degree)
{
    if((car_isAccOn() && !car_isCarLocking()) || data_getData()->isRFIDPowerOn) //RFID正常供电情况下，直接判断
    {
        device_SetDefendOnWithRFIDRsp(req, param, isConsider90Degree);
    }
    else
    {
        u8 checkTimes = 0;

        car_openRFIDPower_SetDeffend();//先打开RFID的5V供电，8秒后或完成业务逻辑后再关闭

        //5秒内判断是否读到RFID，若超时直接返回
        while(checkTimes < ((1000 / 500) * CHECK_TIME) && (!data_getData()->isRFIDConnect || !data_getData()->isCardIdLegal))
        {
            checkTimes++;
            fibo_taskSleep(500);
        }
        checkTimes = 0;
        device_SetDefendOnWithRFIDRsp(req, param, isConsider90Degree);
    }
    return 0;
}

static int device_SetDefendOnWithDegree(const void *req, cJSON *param) //考虑90度定向停车的响应
{
    cJSON *json_result = cJSON_CreateObject();
    cJSON *json_root = cJSON_CreateObject();
    cJSON *json_degree = cJSON_CreateObject();
    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return L_FALSE;
    }

    cJSON *json_biasDegree = cJSON_GetObjectItem(param, "biasDegree"); //方向角偏差
    cJSON *json_targetDegree = cJSON_GetObjectItem(param, "targetDegree"); //目标方向角
    u8 ret = 0;

    if(!json_result || !json_root || !json_degree)
    {
        if(json_result)
        {
            cJSON_Delete(json_result);
        }
        if(json_root)
        {
            cJSON_Delete(json_root);
        }
        if(json_degree)
        {
            cJSON_Delete(json_degree);
        }
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        g_isSetDefending = L_FALSE;
        return -1;
    }

    ret = device_checkIsDegreeMatching((int)data_getData()->headingAngle, json_targetDegree->valueint, json_biasDegree->valueint);
    if(ret == DEGREE_MATCH)
    {
        cJSON_AddNumberToObject(json_root, "code", ERR_SUCCESS);
        cJSON_AddNumberToObject(json_degree, "event", DEGREE_MATCH);
        cJSON_AddNumberToObject(json_degree, "Degree", data_getData()->headingAngle);
        cJSON_AddItemToObject(json_result, "90degree", json_degree);
        cJSON_AddItemToObject(json_root, "result", json_result);
        device_responseJSONData(req, json_root);

        if(audio_isRFIDAudioDone())
        {
            fibo_audio_stop(); //打断哔哔哔声音
            fibo_taskSleep(500); //避免RFID提示音和还车语音同时播放
        }
        device_PlayAudioWithParam(AUDIO_DEFEND_ON, param);
        setting_setDefend(L_TRUE);
        g_isSetDefending = L_FALSE;
        return 0;
    }
    else if(ret == DEGREE_OUT_OF_RANGE)
    {
        cJSON_AddNumberToObject(json_root, "code", ERR_OPERATION_ERROR);
        cJSON_AddNumberToObject(json_degree, "event", DEGREE_OUT_OF_RANGE);
        cJSON_AddNumberToObject(json_degree, "Degree", data_getData()->headingAngle);
    }
    else if(ret == DEGREE_NOT_FIXED) //未进惯导不显示实际角度
    {
        cJSON_AddNumberToObject(json_root, "code", ERR_OPERATION_ERROR);
        cJSON_AddNumberToObject(json_degree, "event", DEGREE_NOT_FIXED);
    }

    cJSON_AddItemToObject(json_result, "90degree", json_degree);
    cJSON_AddItemToObject(json_root, "result", json_result);
    device_responseJSONData(req, json_root);
    g_isSetDefending = L_FALSE;
    audio_play(AUDIO_CAOZUOSHIBAI);
    return 0;
}

static int device_SetDefendOnwithKickstand(const void *req, cJSON *param)
{
    if(setting_getVerisonType() != VERSION_TYPE_MX5F_JC)
    {
        return device_rspErr(req, ERR_OPERATION_ERROR); //只匹配支持脚撑还车的版本
    }

    cJSON *isForce = cJSON_GetObjectItem(param, "force");
    if(!isForce || !isForce->valueint) //非强制锁车
    {
        if(data_getData()->isKickMeet == 1 || car_isMagneticKick()) //满足磁脚撑条件 可以设防
        {
            if(SETTING_NOTSTOP == setting_setDefend(L_TRUE))
            {
                device_rspErr(req, ERR_CAR_NOT_STOP);
                return -1;
            }
            data_getData()->isKickUse = 1;
        }
        else
        {
            audio_play(AUDIO_KICKFAILED);
            device_rspErr(req, ERR_OPERATION_ERROR);
            return -1;
        }
    }
    else //强制锁车
    {
        car_accOff();
        car_lockBackWheel();
        setting.statusConf.acc = L_FALSE;
        setting.statusConf.isDefend = L_TRUE;
    }

    if(audio_isRFIDAudioDone())
    {
        fibo_audio_stop(); //打断RFID提示音
        fibo_taskSleep(500); //避免RFID提示音和还车语音同时播放
    }
    device_PlayAudioWithParam(AUDIO_DEFEND_ON, param);
    device_rspErr(req, ERR_SUCCESS);
    g_isSetDefending = L_FALSE;
    return 0;
}

static int device_SetDefendOnDefault(const void *req, cJSON *param) //默认设防逻辑
{
    if(SETTING_NOTSTOP == setting_setDefend(L_TRUE))
    {
        cJSON *isForce = cJSON_GetObjectItem(param, "force");
        if(!isForce || !isForce->valueint)
        {
            device_rspErr(req, ERR_CAR_NOT_STOP);
            g_isSetDefending = L_FALSE;
            return -1;
        }
        else
        {
            //危险动作
            car_lockBackWheel();
            setting_setDefend(L_TRUE);
        }
    }

    if(audio_isRFIDAudioDone())
    {
        fibo_audio_stop(); //打断哔哔哔声音
        fibo_taskSleep(500); //避免RFID提示音和还车语音同时播放
    }

    //播放语音
    device_PlayAudioWithParam(AUDIO_DEFEND_ON, param);
    device_rspErr(req, ERR_SUCCESS);
    return 0;
}

static int device_SetDefendOff(const void *req, cJSON *param) //默认设防逻辑
{
    //超级锁车下, 不支持撤防操作, 先解除超级锁车
    if(setting.settingConf.forceLock)
    {
        device_rspErr(req, ERR_ACCESS_DENY);
        g_isSetDefending = L_FALSE;
        return 0;
    }

    setting_setDefend(L_FALSE);
    data_getData()->tBeaconInfo.event = EVENT_NOTBEACON; //标志道钉数据不可用

    if(audio_isRFIDAudioDone())
    {
        fibo_audio_stop(); //打断哔哔哔声音
        fibo_taskSleep(500); //避免RFID提示音和还车语音同时播放
    }

    //播放语音
    device_PlayAudioWithParam(AUDIO_DEFEND_OFF, param);
    timer_stop(TIMER_RELEASE_ELOCK);
    device_rspErr(req, ERR_SUCCESS);
    return 0;
}

static int device_SetDeffend(const void *req, cJSON *param)
{
    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return L_FALSE;
    }

    cJSON *defend = cJSON_GetObjectItem(param, "defend");                   //设防接口
    cJSON *withHelmet = cJSON_GetObjectItem(param, "withHelmet");           //关联头盔锁
    cJSON *isTBeacon = cJSON_GetObjectItem(param, "isTBeacon");             //使能道钉条件还车
    cJSON *isKickstand = cJSON_GetObjectItem(param, "isKickstand");         //使能脚撑条件还车
    cJSON *json_rfid = cJSON_GetObjectItem(param, "isRFID");                //使能RFID条件还车
    cJSON *json_degree = cJSON_GetObjectItem(param, "is90degree");          //使能90度定向停车
    cJSON *json_biasDegree = cJSON_GetObjectItem(param, "biasDegree");      //方向角偏差
    cJSON *json_targetDegree = cJSON_GetObjectItem(param, "targetDegree");  //目标方向角

    //升级过程中,不执行操作
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    //入参检查, 非法入参直接返回失败
    if((defend->type != cJSON_Number || defend->valueint > 1)
    || (json_rfid && (json_rfid->type != cJSON_Number || json_rfid->valueint > 1))
    || (isTBeacon && (isTBeacon->type != cJSON_Number || isTBeacon->valueint > 1))
    || (isKickstand && (isKickstand->type != cJSON_Number || isKickstand->valueint > 1))
    || (withHelmet && (withHelmet->type != cJSON_Number || withHelmet->valueint > 1)))
    {
        device_rspErr(req, ERR_PARAM_INVALID);
        return -1;
    }

    //入参二级检查
    if(json_degree && json_degree->valueint == 1)
    {
        //如果下发is90degree = 1，但是没有下发角度偏差条件biasDegree或目标角度targetDegree，则返回115
        if(!json_biasDegree || !json_targetDegree)
        {
            device_rspErr(req, ERR_PARAM_MISSING);
            return -1;
        }

        //目标角度值和角度偏差的数值不对，返回115
        if(json_biasDegree->valueint < 0 || json_biasDegree->valueint > 359 || json_targetDegree->valueint < 0 || json_targetDegree->valueint > 359)
        {
            device_rspErr(req, ERR_PARAM_INVALID);
            return -1;
        }
    }

    //设防操作
    if(defend && defend->valueint)
    {
        u8 tmp = 0;
        if(json_rfid && json_rfid->valueint != 0)
        {
            tmp++;
        }
        if(isTBeacon && isTBeacon->valueint != 0)
        {
            tmp++;
        }
        if(isKickstand && isKickstand->valueint != 0)
        {
            tmp++;
        }

        //RFID、脚撑还车、道钉指令同时置位, 认为指令不支持
        if(tmp >= 2)
        {
            device_rspErr(req, ERR_CMD_NOT_SUPPORTED);
            return -1;
        }

        //90°还车逻辑
        if(json_degree && json_degree->valueint >= 1)
        {
            if(json_rfid && json_rfid->valueint >= 1)
            {
                //90°+RFID还车
                return device_SetDefendOnWithRFID(req, param, L_TRUE);
            }
            else if(isTBeacon && isTBeacon->valueint >= 1)
            {
                //90°+道钉
                return device_SetDeffendOnWithTBeacon(req, param, L_TRUE);
            }
            else
            {
                //纯90°还车逻辑
                return device_SetDefendOnWithDegree(req, param);
            }
        }

        //RFID还车逻辑
        if(json_rfid && json_rfid->valueint >= 1) //考虑RFID的情况
        {
            if(json_degree && json_degree->valueint >= 1)
            {
                //90+RFID还车
                return device_SetDefendOnWithRFID(req, param, L_TRUE);
            }
            else
            {
                //纯RFID还车
                return device_SetDefendOnWithRFID(req, param, L_FALSE);
            }
        }

        if(isTBeacon && isTBeacon->valueint >= 1)
        {
            if(json_degree && json_degree->valueint >= 1)
            {
                //90+道钉还车
                return device_SetDeffendOnWithTBeacon(req, param, L_TRUE);
            }
            else
            {
                //纯道钉还车
                return device_SetDeffendOnWithTBeacon(req, param, L_FALSE);
            }
        }

        //如果带检测磁脚撑指令
        if(isKickstand && isKickstand->valueint >= 1)
        {
            return device_SetDefendOnwithKickstand(req, param);
        }

        return device_SetDefendOnDefault(req, param);
    }
    else if(defend && !defend->valueint)//撤防
    {
        return device_SetDefendOff(req, param);
    }

    //default 参数不对
    return device_rspErr(req, ERR_PARAM_INVALID);
}

static int device_GetDeffend(const void *req, cJSON *param)
{
    cJSON *result = NULL;
    cJSON *json_root = NULL;

    result = cJSON_CreateObject();
    if(!result)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    cJSON_AddNumberToObject(json_root, "code", 0);

    cJSON_AddNumberToObject(result, "defend", setting.statusConf.isDefend);
    cJSON_AddItemToObject(json_root, "result", result);

    return device_responseJSONData(req, json_root);
}

//带道钉信息开电门成功响应
static int device_SetAccOnWithTBeacon_successful(const void *req, beaconInfo_t *info)
{
    DATA *pData = data_getData();
    u8 tempData[24 + 1] = {0};

    LOG_INFO("scan daoding successful");
    pData->isWaitingTBeaconResult = L_FALSE;

    {
        cJSON *root = cJSON_CreateObject();
        cJSON *json_root = cJSON_CreateObject();

        if(!root || !json_root)
        {
            if(root)
            {
                cJSON_Delete(root);
            }
            if(json_root)
            {
                cJSON_Delete(json_root);
            }
            device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
            return L_FALSE;
        }

        cJSON_AddNumberToObject(json_root, "code", 0);

        cJSON_AddNumberToObject(root, "event", EVENT_ACCONTBEACON);
        HexToAscii(info->mac, tempData, 6);
        cJSON_AddStringToObject(root, "tBeaconAddr", (const char *)tempData);
        if(strlen(info->tBeaconID) != 0) //浩源道钉才返回id,soc，vsn信息，其他默认没有
        {
            cJSON_AddStringToObject(root, "tBeaconId", (const char *)info->tBeaconID);
            cJSON_AddNumberToObject(root, "tBeaconSOC", info->tBeaconSOC);

            {
                u8 version_str[5] = {0};
                HexToAscii(info->tBeaconVersion, version_str, 2);
                cJSON_AddStringToObject(root, "TbeaconVsn", (const char *)version_str);
            }
        }
        else
        {
            cJSON_AddStringToObject(root, "tBeaconId", " ");
            cJSON_AddNumberToObject(root, "tBeaconSOC", 0);
            {
                u8 version_str[5] = {0};
                HexToAscii(info->tBeaconVersion, version_str, 2);
                cJSON_AddStringToObject(root, "TbeaconVsn", " ");
            }
        }

        if(pData->lastPosition.isGPS)
        {
            cJSON_AddNumberToObject(root, "lon", gps_getGPSValue(pData->lastPosition.nmeaInfo.lon));
            cJSON_AddNumberToObject(root, "lat", gps_getGPSValue(pData->lastPosition.nmeaInfo.lat));
            cJSON_AddNumberToObject(root, "timestamp", pData->lastPosition.timestamp);
        }
        else
        {
            cJSON_AddNumberToObject(root, "lon", gps_getGPSValue(pData->lastPosition.lbsInfo.lon));
            cJSON_AddNumberToObject(root, "lat", gps_getGPSValue(pData->lastPosition.lbsInfo.lat));
            cJSON_AddNumberToObject(root, "timestamp", pData->lastPosition.lbsTimestamp);
        }

        cJSON_AddItemToObject(json_root, "result", root);

        device_responseJSONData(req, json_root);
    }
    return 0;
}

//带道钉信息开电门失败响应
static int device_SetAccOnWithTBeacon_fail(const void *req)
{
    LOG_INFO("scan daoding fail");
    data_getData()->isWaitingTBeaconResult = L_FALSE;
    device_rspErr(req, ERR_OPERATION_ERROR);
    audio_play(AUDIO_CAOZUOSHIBAI);
    return 0;
}

static int device_acc(const void *req, cJSON *param)
{
    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        audio_play(AUDIO_CAOZUOSHIBAI);
        return -1;
    }

    cJSON *acc = cJSON_GetObjectItem(param, "acc");
    if(acc)
    {
        cJSON *isTBeacon = cJSON_GetObjectItem(param, "isTBeacon");
        cJSON *isIgnoreFence = cJSON_GetObjectItem(param, "isIgnoreFence");
        cJSON *withHelmet = cJSON_GetObjectItem(param, "withHelmet");

        if((isIgnoreFence && (isIgnoreFence->type != cJSON_Number || isIgnoreFence->valueint > 1))
        || (isTBeacon && (isTBeacon->type != cJSON_Number || isTBeacon->valueint > 1))
        || acc->type != cJSON_Number || acc->valueint > 1)
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }

        if(acc->valueint == 1)
        {
            if(setting.settingConf.isFenceEnable == L_TRUE && data_getData()->fenceAreaType == OUTSERVICE_AREA)
            {
                device_rspErr(req, ERR_OPERATION_ERROR);
                return 0;
            }
            if(setting.settingConf.forceLock)
            {
                device_rspErr(req, ERR_ACCESS_DENY);
                audio_play(AUDIO_CAOZUOSHIBAI);
                return 0;
            }

            if(isIgnoreFence && isIgnoreFence->valueint == 1)
            {
                setting.settingConf.isIgnoreFence = L_TRUE;
                setting.settingConf.isIgnoreFenceOnce = L_TRUE;
            }

            if(isTBeacon && isTBeacon->valueint == 1) //使能扫描道钉
            {
                LOG_INFO("start scan DaoDing for acc on");
                beaconInfo_t *info = data_getTBeaconInfo(3);
                if(!info)
                {
                    LOG_ERROR("no beacon info");
                    device_rspErr(req, ERR_OPERATION_ERROR);
                }
                if(info && info->dbm <= setting.settingConf.beaconRssi)
                {
                    device_SetAccOnWithTBeacon_successful(req, info);
                }
                else
                {
                    return device_SetAccOnWithTBeacon_fail(req);
                }
            }

            //启动电门，并撤防
            if(SETTING_OUTSERVICE == setting_setAcc(L_TRUE))
            {
                device_rspErr(req, ERR_OPERATION_ERROR);
                return 0;
            }

            //如果关联打开头盔锁, 则执行打开头盔锁, 不进行检测, 开锁没有问题
            if((withHelmet && withHelmet->valueint == 1) 
            || setting.defaultConf.helmetType == TYPE_XINGQIHELMET) //星骑头盔锁硬关联 
            {
                car_unlockHelmet();
            }

            device_PlayAudioWithParam(AUDIO_ACC_ON, param);
            timer_stop(TIMER_RELEASE_ELOCK);
        }
        else if(acc->valueint == 0)
        {
            setting_setAcc(L_FALSE);
            data_getData()->tBeaconInfo.event = EVENT_NOTBEACON;//标志道钉数据不可用
            device_PlayAudioWithParam(AUDIO_ACC_OFF, param);
        }

        device_rspErr(req, ERR_SUCCESS);
        return 0;
    }

    device_rspErr(req, ERR_PARAM_INVALID);
    return -1;
}

static int device_SetServer(const void *req, cJSON *param)
{
    int count = 0;
    uint32_t port = 0;
    u32 ip[4] = {0};
    DATA *pData = data_getData();
    L_BOOL rc = L_FALSE;
    cJSON *json_server = NULL;
    cJSON *result = NULL;
    cJSON *json_root = NULL;
    char domain[MAX_DOMAIN_NAME_LEN + 6] = {0};

    if(param)
    {
        json_server = cJSON_GetObjectItem(param, "server");//这个服务器地址更改了需要重启，所以必须放在最后
    }

    if(!param || !json_server)
    {
        result = cJSON_CreateObject();
        if(!result)
        {
            device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
            return -1;
        }

        json_root = cJSON_CreateObject();
        if(!json_root)
        {
            cJSON_Delete(result);
            device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
            return -1;
        }

        if(setting.serverConf.addr_type == ADDR_TYPE_DOMAIN)
        {
            snprintf(domain, MAX_DOMAIN_NAME_LEN + 6, "%s:%d", setting.serverConf.domain, setting.serverConf.port);
        }
        else if(setting.serverConf.addr_type == ADDR_TYPE_IP)
        {
            snprintf(domain, MAX_IP_PORT_LEN, "%u.%u.%u.%u:%d", setting.serverConf.ipaddr[0], setting.serverConf.ipaddr[1], setting.serverConf.ipaddr[2], setting.serverConf.ipaddr[3], setting.serverConf.port);
        }

        cJSON_AddNumberToObject(json_root, "code", 0);
        cJSON_AddStringToObject(result, "server", domain);
        cJSON_AddItemToObject(json_root, "result", result);
        return device_responseJSONData(req, json_root);
    }

    do
    {
        count = sscanf(json_server->valuestring, "%u.%u.%u.%u:%u", &ip[0], &ip[1], &ip[2], &ip[3], &port);
        if(5 == count)
        {
            if(check_ip(ip[0], ip[1], ip[2], ip[3]))
            {
                LOG_DEBUG("Ip cannot be %u.%u.%u.%u.", ip[0], ip[1], ip[2], ip[3]);
                device_rspErr(req, ERR_OPERATION_ERROR);
                return -1;
            }
            if(check_port(port))
            {
                LOG_DEBUG("Port cannot be %d.", port);
                device_rspErr(req, ERR_OPERATION_ERROR);
                return -1;
            }

            if(data_isLogined())
            {
                memcpy(&setting.srvBakConf, &setting.serverConf, sizeof(SERVER_CONF)); //保存备份服务器信息
            }

            setting.serverConf.addr_type = ADDR_TYPE_IP;
            setting.serverConf.ipaddr[0] = (uint8_t)ip[0];
            setting.serverConf.ipaddr[1] = (uint8_t)ip[1];
            setting.serverConf.ipaddr[2] = (uint8_t)ip[2];
            setting.serverConf.ipaddr[3] = (uint8_t)ip[3];
            setting.serverConf.port = (uint16_t)port;
            LOG_DEBUG("server save %s:%d successful!",json_server->valuestring, port);
            rc = L_TRUE;
            break;
        }

        count = sscanf(json_server->valuestring, "%[^:]:%u", domain, &port);
        if(2 == count)
        {
            if(check_port(port))
            {
                LOG_DEBUG("Port cannot be %d.", port);
                device_rspErr(req, ERR_OPERATION_ERROR);
                return -1;
            }

            if(data_isLogined())
            {
                memcpy(&setting.srvBakConf, &setting.serverConf, sizeof(SERVER_CONF)); //保存备份服务器信息
            }

            setting.serverConf.addr_type = ADDR_TYPE_DOMAIN;
            memset(setting.serverConf.domain, 0, MAX_DOMAIN_NAME_LEN);
            strncpy(setting.serverConf.domain, domain, MAX_DOMAIN_NAME_LEN);
            setting.serverConf.port = (uint16_t)port;
            rc = L_TRUE;
            LOG_DEBUG("server proc %s:%d successful!", json_server->valuestring, port);
            break;
        }
    }
    while (L_FALSE);

    if(rc == L_TRUE)
    {
        //登陆响应后再保存，否则超时切回原服务器
        device_rspErr(req, ERR_SUCCESS);
        LOG_DEBUG("change server initial");
        socket_initial(); //收到马上关闭socket，避免二次接收造成的保存异常
        timer_start(TIMER_CHANGESERVER_TIMEOUT, TIMER_S, 60, setting_setServerTimeout);
    }
    else
    {
        LOG_DEBUG("param format error.");
        device_rspErr(req, ERR_PARAM_INVALID);
    }

    return 0;
}

static int device_playAudio(const void *req, cJSON *param)
{
    cJSON* audio_idx = NULL;
    cJSON* audio_volume = NULL;
    u8 volume = 0;
    if (!param)
    {
        return device_rspErr(req, ERR_PARAM_MISSING);
    }
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }
    audio_idx = cJSON_GetObjectItem(param, "idx");
    if (!audio_idx) //兼容老接口
    {
        return device_rspErr(req, ERR_SUCCESS);
    }

    audio_volume = cJSON_GetObjectItem(param, "volume");
    if(audio_volume)
    {
        volume = audio_volume->valueint;
    }
    else
    {
        volume = 100;
    }

    if(audio_idx->valueint < 0 || audio_idx->valueint >= AUDIO_MAX_NUMBER || volume < 0 || volume > 100)
    {
        return device_rspErr(req, ERR_RANGE_TOO_LARGE);
    }

    audio_playWithVolume(audio_idx->valueint, volume);
    if(audio_idx->valueint == AUDIO_SEEK || audio_idx->valueint == AUDIO_WHO_AM_I)
    {
        car_blinkLight();
    }
    return device_rspErr(req, ERR_SUCCESS);
}

static int device_GetServer(const void *req, cJSON *param)
{
    char server[MAX_DOMAIN_NAME_LEN] = {0};

    cJSON *result = NULL;
    cJSON *json_root = NULL;

    result = cJSON_CreateObject();
    if(!result)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return -1;
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return -1;
    }

    if(setting.serverConf.addr_type == ADDR_TYPE_DOMAIN)
    {
        snprintf(server, MAX_DOMAIN_NAME_LEN + 6, "%s:%d", setting.serverConf.domain, setting.serverConf.port);
    }
    else if(setting.serverConf.addr_type == ADDR_TYPE_IP)
    {
        snprintf(server, MAX_IP_PORT_LEN, "%u.%u.%u.%u:%d", setting.serverConf.ipaddr[0], setting.serverConf.ipaddr[1], setting.serverConf.ipaddr[2], setting.serverConf.ipaddr[3], setting.serverConf.port);
    }


    cJSON_AddNumberToObject(json_root, "code", 0);
    cJSON_AddStringToObject(result, "server", server);
    cJSON_AddItemToObject(json_root, "result", result);

    return device_responseJSONData(req, json_root);
}

static int device_reboot(const void *req, cJSON *param)
{
    LOG_INFO("[Device] reboot.");
    device_rspErr(req, ERR_SUCCESS);
    setting_setRebootType(REBOOT_COMAND);
    fibo_taskSleep(500);     //延时500ms后重启，保证回应消息送出
    fibo_softReset();
    return 0;
}

static int device_backseat_unlock(const void *req, cJSON *param)
{
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && !setting_isDefendOn()) //只在设防下能开电池仓锁
    {
        device_rspErr(req, ERR_OPERATION_ERROR);
        return -1;
    }

    if(!param)
    {
        car_unlockSaddle();
        audio_play(AUDIO_BEEP);
        device_rspErr(req, ERR_SUCCESS); //兼容无param的协议
        return 0;
    }

    cJSON *isHalfUnlock = cJSON_GetObjectItem(param, "isHalfUnlock");

    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    if(isHalfUnlock && (isHalfUnlock->valueint > 1 || isHalfUnlock->type != cJSON_Number))
    {
        return device_rspErr(req, ERR_PARAM_INVALID);
    }

    device_PlayAudioWithParam(AUDIO_BEEP, param);

    if(isHalfUnlock && isHalfUnlock->valueint == 1)
    {
        car_unlockSaddleHalf();
    }
    else
    {
        car_unlockSaddle();
    }

    device_rspErr(req, ERR_SUCCESS);
    return 0;
}

static int device_BackWheel(const void *req, cJSON *param)
{
    cJSON *sw = NULL;

    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }

    sw = cJSON_GetObjectItem(param, "sw");
    if(sw)
    {
        if(sw->type != cJSON_Number || sw->valueint > 1)
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }


        if(sw->valueint == 1)
        {
            if(data_getData()->isWheelSpinning)
            {
                cJSON *isForce = cJSON_GetObjectItem(param, "force");
                if(!isForce || !isForce->valueint)
                {
                    return device_rspErr(req, ERR_CAR_NOT_STOP);
                }
            }
            car_lockBackWheel();
            device_PlayAudioWithParam(AUDIO_BEEP, param);
            return device_rspErr(req, ERR_SUCCESS);
        }
        else if(sw->valueint == 0)
        {
            car_unlockBackWheel();
            device_PlayAudioWithParam(AUDIO_BEEP, param);
            return device_rspErr(req, ERR_SUCCESS);
        }
    }

    return device_rspErr(req, ERR_PARAM_MISSING);
}

static int device_getInnerParam(const void *req, cJSON *param)
{
    cJSON *result = NULL;
    cJSON *json_root = NULL;
    u8 sendDebug = 0;
    if(param)
    {
        cJSON *token = cJSON_GetObjectItem(param, "token");
        if(token)
        {
            if(strcmp((const char *)token->valuestring, "XiaoAnDebug") == 0 )
            {
                sendDebug = 1;
            }
        }
    }
    result = cJSON_CreateObject();
    if(!result)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }
    cJSON_AddNumberToObject(json_root, "code", 0);

    cJSON_AddNumberToObject(result, "freq_norm", setting.settingConf.freq_norm);
    cJSON_AddNumberToObject(result, "freq_move", setting.settingConf.freq_move);
    cJSON_AddNumberToObject(result, "protectVoltage", setting.settingConf.protectVoltage);
    cJSON_AddNumberToObject(result, "restoreVoltage", setting.settingConf.restoreVoltage);
    cJSON_AddNumberToObject(result, "isOverSpeedOn", setting.defaultConf.isOverSpeedOn);
    cJSON_AddNumberToObject(result, "isMoveAlarmOn", setting.defaultConf.isMoveAlarmOn);
    cJSON_AddNumberToObject(result, "isAutoLockOn", setting.defaultConf.isAutoLockOn);
    cJSON_AddNumberToObject(result, "autoLockPeriod", setting.settingConf.autoLockPeriod);
    cJSON_AddNumberToObject(result, "audioRatio", setting.defaultConf.audioRatio);
    cJSON_AddNumberToObject(result, "isNightVoiceOn", setting.defaultConf.isNightVoiceOn);
    cJSON_AddNumberToObject(result, "isSleepEnable", setting.settingConf.isSleepEnable);
    cJSON_AddNumberToObject(result, "isFenceEnable", setting.settingConf.isFenceEnable);
    cJSON_AddNumberToObject(result, "isTBeaconEnable", setting.settingConf.isTBeaconEnable);
    cJSON_AddNumberToObject(result, "fenceVersion", data_getData()->fence ? data_getData()->fence->version : 0);
    cJSON_AddNumberToObject(result, "isTurnOverEnable", setting.defaultConf.isTurnOverEnable);
    cJSON_AddNumberToObject(result, "turnOverAngle", setting.settingConf.diffAngle);
    cJSON_AddNumberToObject(result, "turnOverAudioPeriod", setting.settingConf.periodDiffAngleAudio);
    cJSON_AddNumberToObject(result, "isEtcSOC", setting.settingConf.isEtcSOC);
    cJSON_AddNumberToObject(result, "activeFreqSOC", setting.settingConf.activeFreqSOC);
    cJSON_AddNumberToObject(result, "beaconRssi", setting.settingConf.beaconRssi);
    cJSON_AddNumberToObject(result, "bmsType",  setting.defaultConf.bmsType);
    cJSON_AddNumberToObject(result, "ccuType", setting.defaultConf.ccuType);
    cJSON_AddNumberToObject(result, "saddleType",  setting.defaultConf.saddleType);
    cJSON_AddNumberToObject(result, "backWheelType", setting.defaultConf.backWheelType);
    cJSON_AddNumberToObject(result, "helmetType", setting.defaultConf.helmetType);
    cJSON_AddNumberToObject(result, "devInstallMode", setting.settingConf.devInstallMode);
    cJSON_AddNumberToObject(result, "isTerminateETCUpgrade", setting.statusConf.isTerminateETCUpgrade);
    cJSON_AddNumberToObject(result, "isTerminateBMSUpgrade", setting.statusConf.isTerminateBMSUpgrade);
    cJSON_AddNumberToObject(result, "isEtcAccProtect", setting.settingConf.isEtcAccProtect);
    cJSON_AddNumberToObject(result, "isEtcDefendProtect", setting.settingConf.isEtcDefendProtect);
    cJSON_AddNumberToObject(result, "bmsSendPeriod", setting.statusConf.bmsSendPeriod);
    cJSON_AddNumberToObject(result, "isRFIDEnable", setting.settingConf.isRFIDEnable);
    cJSON_AddNumberToObject(result, "overspeedThreshold", setting.settingConf.overspeedThreshold);
    if(sendDebug)
    {
        cJSON_AddNumberToObject(result, "coreUpdateCount", setting.statusConf.coreUpdateCount);
        cJSON_AddNumberToObject(result, "moveThreshold", setting.settingConf.move_threshold);
        cJSON_AddNumberToObject(result, "isIgnoreFence", setting.settingConf.isIgnoreFence);
        cJSON_AddNumberToObject(result, "isMX5EEAudio1K", setting.settingConf.isMX5EEAudio1K);
    }
    cJSON_AddItemToObject(json_root, "result", result);

    return device_responseJSONData(req, json_root);
}

static int device_setInnerParam(const void *req, cJSON *param)
{
    cJSON *item = NULL;

    //先保存原始配置值,如果所有参数校验通过，则一次性更新；否则，全部不更新
    L_BOOL rc = L_FALSE;
    uint16_t freq_norm = setting.settingConf.freq_norm;
    uint16_t freq_move = setting.settingConf.freq_move;
    //uint16_t freq_sleep = setting.freq_sleep;
    uint16_t isOverSpeedOn = setting.defaultConf.isOverSpeedOn;
    u8 isSocChanged = L_FALSE;

    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return L_FALSE;
    }

    item = cJSON_GetObjectItem(param, "mode");
    if(item)
    {
        switch(item->valueint)
        {
            case MODE_NORM:
                data_getData()->gpsSendPeriod_ms = setting.settingConf.freq_norm * 1000;
                break;

            case MODE_SLEEP:
                data_getData()->gpsSendPeriod_ms = setting.settingConf.freq_norm * 1000;
                break;
        }
        gps_nmeaOutputEnable(L_TRUE);
        data_setAwakeTime(SLEEP_DEFAULT_TIME);
    }

    item = cJSON_GetObjectItem(param, "freq");
    if(item)
    {
        freq_norm = item->valueint;
    }

    item = cJSON_GetObjectItem(param, "freq_norm");
    if(item)
    {
        freq_norm = item->valueint;
    }

    item = cJSON_GetObjectItem(param, "freq_move");
    if(item)
    {
        freq_move = item->valueint;
    }

    item =cJSON_GetObjectItem(param, "protectVoltage");
    if(item)
    {
        setting.settingConf.protectVoltage = item->valueint;
    }

    item =cJSON_GetObjectItem(param, "restoreVoltage");
    if(item)
    {
        setting.settingConf.restoreVoltage = item->valueint;
    }

    item = cJSON_GetObjectItem(param, "isAutoLockOn");
    if(item)
    {
        if(item->valueint)
        {
            setting.defaultConf.isAutoLockOn = L_TRUE;
        }
        else
        {
            setting.defaultConf.isAutoLockOn = L_FALSE;
        }
    }

    item = cJSON_GetObjectItem(param, "autoLockPeriod");
    if(item)
    {
        if(item->valueint >= (5 * 60) && item->valueint <= (60 * 60))
        {
            setting.settingConf.autoLockPeriod = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isOverSpeedOn");
    if(item)
    {
        isOverSpeedOn = item->valueint;
    }
    setting.defaultConf.isOverSpeedOn = isOverSpeedOn;

    item = cJSON_GetObjectItem(param, "isMoveAlarmOn");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.defaultConf.isMoveAlarmOn = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "audioRatio");
    if(item)
    {
        if(item->valuedouble >= 0.0 && item->valuedouble <= 1.0)
        {
            setting.defaultConf.audioRatio = item->valuedouble;
        }
    }

    item = cJSON_GetObjectItem(param, "isNightVoiceOn");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.defaultConf.isNightVoiceOn = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isSleepEnable");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.settingConf.isSleepEnable = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isFenceEnable");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            if(fence_checkData(data_getData()->fence) == L_FALSE)
            {
                setting.settingConf.isFenceEnable = L_FALSE;
            }
            else
            {
                setting.settingConf.isFenceEnable = item->valueint;
            }
        }
    }

    item = cJSON_GetObjectItem(param, "isTBeaconEnable");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.settingConf.isTBeaconEnable = item->valueint;
        }
    }


    item = cJSON_GetObjectItem(param, "isTurnOverEnable");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.defaultConf.isTurnOverEnable = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "turnOverAngle");
    if(item)
    {
        if(item->valueint > 0 && item->valueint < 90)
        {
            setting.settingConf.diffAngle = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "turnOverAudioPeriod");
    if(item)
    {
        if(item->valueint > 0)
        {
            setting.settingConf.periodDiffAngleAudio = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "devInstallMode");
    if(item)
    {
        if(item->valueint >= 0 && item->valueint < 4)
        {
            setting.settingConf.devInstallMode = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "bmsType");
    if(item)
    {
        if(item->valueint >= TYPE_NOBMS && item->valueint < TYPE_BMS_MAX)
        {
            setting.defaultConf.bmsType = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "ccuType");
    if(item)
    {
        if(item->valueint >= TYPE_NOCCU && item->valueint < TYPE_CCU_MAX)
        {
            setting.defaultConf.ccuType = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "etcType");
    if(item)
    {
        if(item->valueint >= TYPE_NOCCU && item->valueint < TYPE_CCU_MAX)
        {
            setting.defaultConf.ccuType = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "moveThreshold");
    if(item)
    {
        if(item->valueint >= 0)
        {
            setting.settingConf.move_threshold = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isEtcSOC");
    if(item)
    {
        if(setting.settingConf.isEtcSOC == L_FALSE && item->valueint == L_TRUE) //从失能到使能也获取一次SOC
        {
            car_lockAndGetSoc();
        }

        if(item->valueint == L_FALSE || item->valueint == L_TRUE)
        {
            if(setting.settingConf.isEtcSOC != item->valueint)
            {
                isSocChanged = L_TRUE;
            }
            setting.settingConf.isEtcSOC = item->valueint;
        }
    }
    item = cJSON_GetObjectItem(param, "activeFreqSOC");
    if(item)
    {
        if(item->valueint >= 0)
        {
            if(setting.settingConf.activeFreqSOC != item->valueint)
            {
                isSocChanged = L_TRUE;
            }
            setting.settingConf.activeFreqSOC = item->valueint;
        }
    }
    if(isSocChanged == L_TRUE)
    {
        event_checkActiveFreqSOC(); //一线通修改配置后，重启主动获取定时器
    }

    item = cJSON_GetObjectItem(param, "beaconRssi");
    if(item)
    {
        //道钉阈值有效范围20~128
        if(item->valueint >= 20 && item->valueint <= 128)
        {
            setting.settingConf.beaconRssi = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isTerminateETCUpgrade");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.statusConf.isTerminateETCUpgrade = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isTerminateBMSUpgrade");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.statusConf.isTerminateBMSUpgrade = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "coreUpdateCount");
    if(item)
    {
        if(item->valueint >= 0)
        {
            setting.statusConf.coreUpdateCount = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isEtcAccProtect");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.settingConf.isEtcAccProtect = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isEtcDefendProtect");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.settingConf.isEtcDefendProtect = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isRFIDEnable");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.settingConf.isRFIDEnable = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "isMX5EEAudio1K");
    if(item)
    {
        if(item->valueint == 0 || item->valueint == 1)
        {
            setting.settingConf.isMX5EEAudio1K = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "overspeedThreshold");
    if(item)
    {
        if(item->type == cJSON_Number && item->valueint > 0 && item->valueint <= 25) //0-25，默认15
        {
            setting.settingConf.overspeedThreshold = item->valueint;
        }
    }

    item = cJSON_GetObjectItem(param, "bmsSendPeriod");
    if(item)
    {
        if(item->valueint >= 5 && item->valueint <= 60 * 60) //5~3600 s
        {
            setting.statusConf.bmsSendPeriod = item->valueint;
            statusConf_save();
        }
    }
    setting.settingConf.freq_norm = freq_norm;
    setting.settingConf.freq_move = freq_move;

    rc = settingConf_save();
    if(rc == L_TRUE)
    {
        device_rspErr(req, ERR_SUCCESS);
    }
    else
    {
        device_rspErr(req, ERR_FILE_ERROR);
    }

    return 0;
}

static MSG_HEADER device_get_lbs_header = {0, 0, 0, 0};
static ATResult_enum device_getLBS_cb(uint8_t isTimeout,char *buf, u16 len)
{
    int rc = 0;
    double lat, lon;

    if(isTimeout)
    {
        return AT_RES_FINISHED;
    }

    u8 *pos = (u8 *)string_bypass((const char *)buf, "GTGIS:\"");
    if(strstr((const char *)buf, "ERROR") || strstr((const char *)buf, "OK")||(!pos))
    {
        if(strstr((const char *)buf, "ERROR"))
        {
            return AT_RES_FINISHED;
        }
        if(!pos)
        {
            return AT_RES_CONTRINUE;
        }
    }
    pos = (u8 *)string_trimLeft(pos);
    rc = sscanf((char *)pos, "%lf,%lf%*s", &lon, &lat);
    LOG_DEBUG("rc:%d  lon:%lf lat:%lf",rc,lon,lat);
    if(rc == 2)
    {
        cJSON *lbs = cJSON_CreateObject();
        cJSON *root = cJSON_CreateObject();
        cJSON *json_root = cJSON_CreateObject();

        data_getData()->lastPosition.isCLBS = L_TRUE;
        data_getData()->lastPosition.lbsTimestamp = (u32)rtc_getTimestamp();
        data_getData()->lastPosition.lbsInfo.lat = nmea_degree2ndeg(lat);
        data_getData()->lastPosition.lbsInfo.lon = nmea_degree2ndeg(lon);

        if(!lbs || !root || !json_root)
        {
            if(lbs)cJSON_Delete(lbs);
            if(root)cJSON_Delete(root);
            if(json_root)cJSON_Delete(json_root);
            return AT_RES_FINISHED;
        }

        cJSON_AddNumberToObject(json_root, "code", 0);
        cJSON_AddNumberToObject(lbs, "lat", lat);
        cJSON_AddNumberToObject(lbs, "lon", lon);
        cJSON_AddItemToObject(root, "lbs", lbs);
        cJSON_AddItemToObject(json_root, "result", root);
        device_responseJSONData(&device_get_lbs_header, json_root);
    }
    return AT_RES_FINISHED;
}

static int device_getLBS(const void *req, cJSON *param)
{
    //如果没有定位 获取基站进行回复
    device_get_lbs_header.cmd = ((MSG_HEADER *)req)->cmd;
    device_get_lbs_header.seq = ((MSG_HEADER *)req)->seq;
    device_get_lbs_header.signature = ((MSG_HEADER *)req)->signature;
    gps_getCLBS(device_getLBS_cb);
    return 0;
}

static MSG_HEADER device_get_wifi_header = {0, 0, 0, 0};
static ATResult_enum wifi_GETLocation_cb(uint8_t isTimeout, char *buf, u16 len)
{
    int rc = 0;
    double lat, lon;
    if(isTimeout)
    {
        device_rspErr(&device_get_wifi_header, ERR_FILE_ERROR);
        return AT_RES_FINISHED;
    }
    u8 *pos = (u8 *)string_bypass((const char *)buf, "GTGIS:\"");
    if(strstr((const char *)buf, "ERROR") || strstr((const char *)buf, "OK") || (!pos))
    {
        if(strstr((const char *)buf, "ERROR"))
        {
            device_rspErr(&device_get_wifi_header, ERR_FILE_ERROR);
            return AT_RES_FINISHED;
        }
        if(!pos)
        {
            return AT_RES_CONTRINUE;
        }
    }
    pos = (u8 *)string_trimLeft(pos);
    rc = sscanf((char *)pos, "%lf,%lf%*s", &lon, &lat);
    if(rc != 2)
    {
        device_rspErr(&device_get_wifi_header, ERR_FILE_ERROR);
        return AT_RES_FINISHED;
    }
    cJSON *wifi = cJSON_CreateObject();
    cJSON *root = cJSON_CreateObject();
    cJSON *json_root = cJSON_CreateObject();
    if(!wifi || !root || !json_root)
    {
        if(wifi)cJSON_Delete(wifi);
        if(root)cJSON_Delete(root);
        if(json_root)cJSON_Delete(json_root);
        device_rspErr(&device_get_wifi_header, ERR_FILE_ERROR);
        return AT_RES_FINISHED;
    }
    cJSON_AddNumberToObject(json_root, "code", 0);
    cJSON_AddNumberToObject(wifi, "lat", lat);
    cJSON_AddNumberToObject(wifi, "lon", lon);
    cJSON_AddNumberToObject(wifi, "timestamp", (u32)rtc_getTimestamp());
    cJSON_AddItemToObject(root, "wifiCoord", wifi);
    cJSON_AddItemToObject(json_root, "result", root);
    device_responseJSONData(&device_get_wifi_header, json_root);
    return AT_RES_FINISHED;
}

static int device_wificoord(const void *req, cJSON *param)
{
    device_get_wifi_header.cmd = ((MSG_HEADER *)req)->cmd;
    device_get_wifi_header.seq = ((MSG_HEADER *)req)->seq;
    device_get_wifi_header.signature = ((MSG_HEADER *)req)->signature;
    at_runwithTimeout("AT+GTGIS=7\r", wifi_GETLocation_cb, 15); //使用wifi辅助定位，使用高德地图及其KEY
    return 0;
}

static int device_status(const void *req, cJSON *param)
{
    cJSON *gps = cJSON_CreateObject();
    cJSON *root = cJSON_CreateObject();
    cJSON *json_root = cJSON_CreateObject();
    DATA *pData = data_getData();
    u8 sendDebug = 0;

    if(param)
    {
        cJSON *token = cJSON_GetObjectItem(param, "token");
        if(token)
        {
            if(strcmp((const char *)token->valuestring, "XiaoAnDebug") == 0 )
            {
                sendDebug = 1;
            }
        }
    }

    if(!root || !gps || !json_root)
    {
        if(gps)
        {
            cJSON_Delete(gps);
        }
        if(root)
        {
            cJSON_Delete(root);
        }
        if(json_root)
        {
            cJSON_Delete(json_root);
        }
        return device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
    }

    cJSON_AddNumberToObject(json_root, "code", 0);

    cJSON_AddNumberToObject(root, "defend", setting_isDefendOn());
    cJSON_AddNumberToObject(root, "acc", (car_isAccOn() || setting.statusConf.acc));
    cJSON_AddNumberToObject(root, "voltage", (u8)(pData->vehicleBattery_mV / 1000.f + 0.5));
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && pData->staticBikeBat_mV != 0)
    {
        cJSON_AddNumberToObject(root, "voltageMv", pData->staticBikeBat_mV); //大电电压 毫伏
    }
    else
    {
        cJSON_AddNumberToObject(root, "voltageMv", pData->vehicleBattery_mV);
    }
    int rssi = 0, ber = 0;
    fibo_get_csq(&rssi, &ber);
    cJSON_AddNumberToObject(root, "gsm", rssi);
    if(setting.defaultConf.backWheelType != TYPE_NOBACKWHEEL)
    {
        cJSON_AddNumberToObject(root, "wheelLock", car_isBackWheelLocked() ? 1 : 0); //后轮锁低电平到位
    }
    if(setting.defaultConf.helmetType != TYPE_NOHELMET)
    {
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            cJSON_AddNumberToObject(root, "helmetLock", car_isHelmetAtPos() ? 1 : 0);
            cJSON_AddNumberToObject(root, "helmetReact", car_isHelmetClose() ? 1 : 0);
            cJSON_AddNumberToObject(root, "helmet6Lock", car_isHelmetClose() ? 1 : 0);
            cJSON_AddNumberToObject(root, "helmet6React", car_isHelmetAtPos() ? 1 : 0);
        }
        else
        {
            cJSON_AddNumberToObject(root, "helmetLock", car_isHelmetLocked() ? 1 : 0);
        }
    }
    cJSON_AddNumberToObject(root, "seatLock", car_isSaddleLocked() ? 1 : 0);
    cJSON_AddNumberToObject(root, "isWheelSpan", pData->isWheelSpinning ? 1 : 0);
    cJSON_AddNumberToObject(root, "powerState", car_isPowerExistence() ? 1 : 0);
    cJSON_AddNumberToObject(root, "audioType", setting.settingConf.audioType);
    cJSON_AddNumberToObject(root, "totalMiles", setting.statusConf.totalMiles + pData->iMiles);
    cJSON_AddNumberToObject(root, "EtcComm", data_getData()->faultRecord.EtcComm);
    cJSON_AddNumberToObject(root, "BmsComm", data_getData()->faultRecord.BmsComm);
    cJSON_AddNumberToObject(root, "etcSpeed", data_getRealEtcSpeed());
    if(setting.settingConf.isEtcSOC)
    {
        cJSON_AddNumberToObject(root, "bmsSOC", setting.statusConf.bmsSoc);
    }
    if(pData->bms.voltage != 0)
    {
        cJSON_AddNumberToObject(root, "bmsvoltage", pData->bms.voltage);
    }

    if(setting.settingConf.isKickStandEnable == L_TRUE)
    {
        cJSON *kickStand = cJSON_CreateObject();
        if(!kickStand)
        {
            cJSON_Delete(gps);
            cJSON_Delete(root);
            cJSON_Delete(json_root);
            return device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        }

        cJSON_AddNumberToObject(kickStand, "type", pData->kickType);
        if(pData->kickType == KICK_TYPE_MAG || pData->kickType == KICK_TYPE_MAG_AND_RFID)
        {
            cJSON_AddNumberToObject(kickStand, "magState", car_isMagneticKick());
        }

        if(pData->kickType == KICK_TYPE_RFID || pData->kickType == KICK_TYPE_MAG_AND_RFID)
        {
            if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
            {
                if(data_getData()->isRFIDConnect && data_getData()->isCardIdLegal) //RFID连接并扫描到标签
                {
                    cJSON_AddNumberToObject(kickStand, "rfState", RFID_SCAN_SUCCESS);
                    cJSON_AddStringToObject(kickStand, "version", pData->RFIDVersion);
                    cJSON_AddStringToObject(kickStand, "cardID", pData->cardID);
                }
                else if(data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID连接未扫描到标签
                {
                    cJSON_AddNumberToObject(kickStand, "rfState", RFID_SCAN_NONE);
                    cJSON_AddStringToObject(kickStand, "version", pData->RFIDVersion);
                    cJSON_AddStringToObject(kickStand, "cardID", "");
                }
                else if(!data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID未连接
                {
                    cJSON_AddNumberToObject(kickStand, "rfState", RFID_DISCONNECT);
                    cJSON_AddStringToObject(kickStand, "version", "");
                    cJSON_AddStringToObject(kickStand, "cardID", "");
                }
            }
        }
        cJSON_AddItemToObject(root, "kickStand", kickStand);
    }

    if(sendDebug)
    {
        cJSON_AddNumberToObject(root, "smallBatMv", pData->smallBattery_mV);//小电池电压      毫伏
        cJSON_AddNumberToObject(root, "malloctimes", data_getData()->malloctimes);
        cJSON_AddNumberToObject(root, "ATtimeoutCount", data_getData()->ATtimeout);
        cJSON_AddStringToObject(root, "firstBlockAT", (const char *)data_getData()->AT_blockCMD);
        cJSON_AddNumberToObject(root, "parseFilter", data_getData()->gps_parseFilter);
        cJSON_AddNumberToObject(root, "statusFilter", data_getData()->gps_statusFilter);
        cJSON_AddNumberToObject(root, "etcUpgradeFlag", setting.statusConf.etcUpgradeFlag);
        cJSON_AddNumberToObject(root, "bmsUpgradeFlag", setting.statusConf.bmsUpgradeFlag);

        if(setting.defaultConf.ccuType == TYPE_TAIBITE_SOC)
        {
            u8 str[128] = {0};
            u8 tmp[8] = {0};
            u8 *socWindow = ETC_TaiBiTe_getSocWindow();
            int i = 0;
            for(i = 0; i < SOC_WINDOW_SIZE; i++)
            {
                sprintf(tmp, "%d,", socWindow[i]);
                strcat(str, tmp);
                memset(tmp, 0, strlen(tmp));
            }
            cJSON_AddStringToObject(root, "socWindow", str);
            cJSON_AddNumberToObject(root, "socPoint", ETC_TaiBiTe_getSocPoint());
        }
    }

    if(pData->lastPosition.isGPS)
    {
        cJSON_AddNumberToObject(gps, "timestamp", pData->lastPosition.timestamp);

        cJSON_AddNumberToObject(gps, "lat", nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lat));
        cJSON_AddNumberToObject(gps, "lng", nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lon));
        cJSON_AddNumberToObject(gps, "speed", (uint8_t)(pData->lastPosition.nmeaInfo.speed + 0.5));
        cJSON_AddNumberToObject(gps, "course", (uint16_t)(pData->lastPosition.nmeaInfo.direction + 0.5));
        cJSON_AddItemToObject(root, "gps", gps);
    }
    else
    {
        opencpu_cellinfo_t cellinfo;
        int i = 0;
        cJSON *array = NULL;
        cJSON *tmp = NULL;
        if(fibo_getCellInfo(&cellinfo, 0) == 0)
        {
            if(cellinfo.curr_rat == 4)
            {
                LOG_DEBUG("LTE cELL num:%d",cellinfo.lte_cellinfo.lteNcellNum);
                cJSON_AddNumberToObject(gps, "mcc", COV2MCC(cellinfo.lte_cellinfo.lteScell.imsi));
                cJSON_AddNumberToObject(gps, "mnc", COV2MNC(cellinfo.lte_cellinfo.lteScell.imsi));
                array = cJSON_CreateArray();
                if(!array)
                {
                    cJSON_Delete(gps);
                    cJSON_Delete(root);
                    cJSON_Delete(json_root);
                    device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
                    return 0;
                }
                tmp = cJSON_CreateObject();
                if(!tmp)
                {
                    cJSON_Delete(gps);
                    cJSON_Delete(root);
                    cJSON_Delete(array);
                    cJSON_Delete(json_root);
                    device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
                    return 0;
                }
                cJSON_AddNumberToObject(tmp, "lac", cellinfo.lte_cellinfo.lteScell.tac);
                cJSON_AddNumberToObject(tmp, "ci", cellinfo.lte_cellinfo.lteScell.cellId);
                cJSON_AddNumberToObject(tmp, "rxl", cellinfo.lte_cellinfo.lteScell.rsrp-140);
                cJSON_AddItemToArray(array, tmp);
                for(i = 0; i < cellinfo.lte_cellinfo.lteNcellNum; i++)
                {
                    tmp = cJSON_CreateObject();
                    if(!tmp)
                    {
                        cJSON_Delete(gps);
                        cJSON_Delete(root);
                        cJSON_Delete(array);
                        cJSON_Delete(json_root);
                        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
                        return 0;
                    }
                    cJSON_AddNumberToObject(tmp, "lac", cellinfo.lte_cellinfo.lteNcell[i].cellAccRelInfo.tac);
                    cJSON_AddNumberToObject(tmp, "ci", cellinfo.lte_cellinfo.lteNcell[i].cellAccRelInfo.cellId);
                    cJSON_AddNumberToObject(tmp, "rxl", cellinfo.lte_cellinfo.lteNcell[i].rsrp-140);
                    cJSON_AddItemToArray(array, tmp);
                }
                cJSON_AddItemToObject(gps, "ltecells", array);
            }
            cJSON_AddItemToObject(root, "cell", gps);
        }
    }

    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
    {
        cJSON *RFID = cJSON_CreateObject();
        if(!RFID)
        {
            cJSON_Delete(root);
            cJSON_Delete(json_root);
            cJSON_Delete(gps);
            device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
            return L_FALSE;
        }

        u8 tmp_event = RFID_SCAN_NONE;
        if(data_getData()->isRFIDConnect && data_getData()->isCardIdLegal) //RFID连接并扫描到标签
        {
            tmp_event = RFID_SCAN_SUCCESS;
            cJSON_AddStringToObject(RFID, "version",pData->RFIDVersion);
            cJSON_AddStringToObject(RFID, "cardID",pData->cardID);
        }
        else if(data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID连接未扫描到标签
        {
            tmp_event = RFID_SCAN_NONE;
            cJSON_AddStringToObject(RFID, "version",pData->RFIDVersion);
        }
        else if(!data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID未连接
        {
            tmp_event = RFID_DISCONNECT;
        }
        cJSON_AddNumberToObject(RFID, "event",tmp_event);
        cJSON_AddItemToObject(root, "RFID", RFID);
    }

    u8 isHeadingProduct =  (setting.settingConf.gpsType == GPS_UBLOX_M8U || setting.settingConf.accleType == ACCLE_MPU6500) ? 1 : 0;
    cJSON_AddNumberToObject(root, "isHeadingProduct", isHeadingProduct);
    if(setting.settingConf.gpsType == GPS_UBLOX_M8U || setting.settingConf.accleType == ACCLE_MPU6500)
    {
        cJSON *heading = cJSON_CreateObject();
        if(!heading)
        {
            cJSON_Delete(root);
            cJSON_Delete(json_root);
            cJSON_Delete(gps);
            cJSON_Delete(heading);
            device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
            return L_FALSE;
        }
        cJSON_AddNumberToObject(heading, "headingAngle", data_getHeadingAngle());
        cJSON_AddNumberToObject(heading, "fixtype", pData->fixtype);

        if(setting.settingConf.gpsType == GPS_UBLOX_M8U && setting.settingConf.accleType == ACCLE_LIS3DH) //M8U定向停车方案产品
        {
            cJSON_AddNumberToObject(heading, "accHeading", pData->accHeading);
            cJSON_AddNumberToObject(heading, "resetFixnum", pData->resetFixnum);
            cJSON_AddNumberToObject(heading, "agcCnt", (int)(1000 * pData->agcCnt / 8191.0f));

            u8 str[50] = {0};
            u8 tmp[10] = {0};
            for(int i = 0; i < 11; i++)
            {
                sprintf(tmp,"%d,",data_getData()->gpsSigs[i]);
                strcat(str, tmp);
                memset(tmp, 0, strlen(tmp));
            }
            sprintf(tmp,"%d",data_getData()->gpsSigs[11]);
            strcat(str, tmp);
            cJSON_AddStringToObject(heading, "gpsSignals", str);
            memset(str, 0, strlen(str));
        }
        cJSON_AddItemToObject(root, "heading", heading);
    }

    cJSON_AddItemToObject(json_root, "result", root);
    return device_responseJSONData(req, json_root);
}

/******************************************************************************
* Function:     APP_check
* Description:  Check whether the app upgrade package is compatible
* Input:        Original data
******************************************************************************/
static int APP_check(uint8_t *data)
{
    static APP_HEAD *app_head = NULL;
    app_head = (APP_HEAD *)Malloc(APP_HEAD_LEN * sizeof(char));
    memset(app_head, 0, APP_HEAD_LEN * sizeof(char));

    //本地的头部信息
    memcpy(current_head.platform, setting.platform, MAX_PLATFORM_NAME_LEN);
    snprintf((char *)current_head.coreversion, 16, "%d.%d.%d", (setting.coreVersion >> 16) & 0xFF,
             (setting.coreVersion >> 8) & 0xFF,
             (setting.coreVersion >> 0) & 0xFF);
    //更新固件的头部
    memcpy(app_head, data, APP_HEAD_LEN);
    if(memcmp(current_head.signature, app_head->signature, APP_SIGNATURE_LEN)) //signature
    {
        LOG_ERROR("[device] signature error");
        Free(app_head);
        return -1;
    }
    if(memcmp(current_head.platform, app_head->platform, MAX_PLATFORM_NAME_LEN))
    {
        LOG_ERROR("[device] platform error,current platform is %s,app platform is %s", current_head.platform, app_head->platform);
        Free(app_head);
        return -1;
    }
    return 0;
}

static u16 app_upgrade_check_crc16 = 0;
static MSG_HEADER device_upgrade_header = {0, 0, 0, 0};

static void device_UpgradeAPP(int result, uint8_t *data, int data_len)
{
    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(app_upgrade_check_crc16 == crc16 || app_upgrade_check_crc16 == 0)
        {
            if(0 == memcmp(data, "xiaoantech", APP_SIGNATURE_LEN))
            {
                LOG_ERROR("[device] please use param:surl and scrc!");
                device_rspErr(&device_upgrade_header, ERR_OPERATION_ERROR);
                return;
            }
            setting_setRebootType(REBOOT_UPGRADE);
            device_responseOK(&device_upgrade_header);
            fibo_taskSleep(1500); //保证resp发出去
            int ret = fibo_ota_handle((char *)data, data_len);
            if(0 < ret)
            {
                LOG_ERROR("[device] fibo_open_ota failed");
                device_rspErr(&device_upgrade_header, ERR_OPERATION_ERROR);
                return;
            }
            LOG_INFO("[device] App upgrade success");
        }
        else
        {
            device_rspErr(&device_upgrade_header, ERR_UPGRADE_CRCERROR);
            LOG_WARNING("[Device] APP File crc error! UrlInput:%d  Operate:%d", app_upgrade_check_crc16, crc16);
        }
    }
    else
    {
        LOG_WARNING("[device] Http get APP pack failed, errorcode:%d", result);
        device_rspErr(&device_upgrade_header, ERR_OPERATION_ERROR);
    }
}

//带升级保护的升级回调函数
static void device_UpgradeAPP_WithCheck(int result, uint8_t *data, int data_len)
{
    char *appdata = NULL;
    int appdata_len = data_len - APP_HEAD_LEN;
    appdata = (char *)Malloc(appdata_len * sizeof(char));
    memset(appdata, 0, appdata_len * sizeof(char));

    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(app_upgrade_check_crc16 == crc16 || app_upgrade_check_crc16 == 0)
        {
            if(APP_check(data))
            {
                device_rspErr(&device_upgrade_header, ERR_OPERATION_ERROR);
                LOG_ERROR("[device] APP File mismatch");
                Free(appdata);
                return;
            }
            memmove(appdata, data + APP_HEAD_LEN, appdata_len);
            setting_setRebootType(REBOOT_UPGRADE);
            device_responseOK(&device_upgrade_header);
            fibo_taskSleep(1500); //保证resp发出去
            int ret = fibo_ota_handle((char *)appdata, appdata_len);
            Free(appdata);
            if(0 < ret)
            {
                LOG_ERROR("[device] fibo_open_ota failed");
                device_rspErr(&device_upgrade_header, ERR_OPERATION_ERROR);
                return;
            }
            LOG_INFO("[device] App upgrade success");
        }
        else
        {
            device_rspErr(&device_upgrade_header, ERR_UPGRADE_CRCERROR);
            LOG_WARNING("[Device] APP File crc error! UrlInput:%d  Operate:%d", app_upgrade_check_crc16, crc16);
            Free(appdata);
        }
    }
    else
    {
        LOG_WARNING("[device] Http get APP pack failed, errorcode:%d", result);
        device_rspErr(&device_upgrade_header, ERR_OPERATION_ERROR);
    }
}

static int device_upgrade(const void *req, cJSON *param)
{
    cJSON *json_url = NULL;
    cJSON *json_crc = NULL;
    cJSON *json_surl = NULL;
    cJSON *json_scrc = NULL;

    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }
    json_url = cJSON_GetObjectItem(param, "url");
    json_crc = cJSON_GetObjectItem(param, "crc");
    json_surl = cJSON_GetObjectItem(param, "surl");
    json_scrc = cJSON_GetObjectItem(param, "scrc");
    if(json_surl)
    {
        if(json_scrc)
        {
            app_upgrade_check_crc16 = json_scrc->valueint;
        }
        else
        {
            app_upgrade_check_crc16 = 0;
        }
        if(strstr(json_surl->valuestring, "http://"))
        {
            char url[MAX_HTTPURL_LEN] = {0};
            char imei[MAX_IMEI_LENGTH + 1] = {0};
            fibo_get_imei((UINT8 *)imei, CFW_SIM_0);
            snprintf(url, MAX_HTTPURL_LEN, "%s?version=%d.%d.%d&imei=%s", json_surl->valuestring,
                     (setting.defaultConf.version >> 16) & 0xFF,
                     (setting.defaultConf.version >> 8) & 0xFF,
                     (setting.defaultConf.version >> 0) & 0xFF,
                     imei);
            int ret = http_get((u8 *)url, device_UpgradeAPP_WithCheck); //异步获取
            if(ret != 0)
            {
                return device_rspErr(req, ERR_OPERATION_ERROR);
            }
            device_upgrade_header.cmd = ((MSG_HEADER *)req)->cmd;
            device_upgrade_header.seq = ((MSG_HEADER *)req)->seq;
            device_upgrade_header.signature = ((MSG_HEADER *)req)->signature;
            return 0; //等待异步下载
        }
        else
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }
    }
    if(json_url)
    {

        if(json_crc)
        {
            app_upgrade_check_crc16 = json_crc->valueint;
        }
        else
        {
            app_upgrade_check_crc16 = 0;
        }
        if(strstr(json_url->valuestring, "http://"))
        {
            char url[MAX_HTTPURL_LEN] = {0};
            char imei[MAX_IMEI_LENGTH + 1] = {0};
            fibo_get_imei((UINT8 *)imei, CFW_SIM_0);
            snprintf(url, MAX_HTTPURL_LEN, "%s?version=%d.%d.%d&imei=%s", json_url->valuestring,
                     (setting.defaultConf.version >> 16) & 0xFF,
                     (setting.defaultConf.version >> 8) & 0xFF,
                     (setting.defaultConf.version >> 0) & 0xFF,
                     imei);
            int ret = http_get((u8 *)url, device_UpgradeAPP); //异步获取
            if(ret != 0)
            {
                return device_rspErr(req, ERR_OPERATION_ERROR);
            }
            device_upgrade_header.cmd = ((MSG_HEADER *)req)->cmd;
            device_upgrade_header.seq = ((MSG_HEADER *)req)->seq;
            device_upgrade_header.signature = ((MSG_HEADER *)req)->signature;
            return 0; //等待异步下载
        }
        else
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }
    }
    return device_rspErr(req, ERR_PARAM_INVALID);
}

static int device_getCustomAudio(const void *req, cJSON *param)
{
    int count = 0, i = 0;
    int idx_array[AUDIO_MAX_NUMBER + 2] = {0};
    unsigned char filename[MAX_FILENAME_LEN];

    cJSON *root = NULL;
    cJSON *result = NULL;
    cJSON *aud = NULL;
    //查找是否有语音文件
    for(count = 1; count <= AUDIO_MAX_NUMBER; count++)
    {
        snprintf((char *)filename, MAX_FILENAME_LEN, "%sdt%d.amr", FILE_AUDIO_DIR, count);
        if(fs_isFileExists((const char *)filename))
        {
            idx_array[i] = count;
            i++;
            continue;
        }
        snprintf((char *)filename, MAX_FILENAME_LEN, "%sdt%d.mp3", FILE_AUDIO_DIR, count);
        if(fs_isFileExists((const char *)filename))
        {
            idx_array[i] = count;
            i++;
            continue;
        }
        snprintf((char *)filename, MAX_FILENAME_LEN, "%sdt%d.wav", FILE_AUDIO_DIR, count);
        if(fs_isFileExists((const char *)filename))
        {
            idx_array[i] = count;
            i++;
            continue;
        }
    }

    result = cJSON_CreateObject();
    if(!result)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    aud = cJSON_CreateIntArray(idx_array, i);
    if(!aud)
    {
        cJSON_Delete(result);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    root = cJSON_CreateObject();
    if(!root)
    {
        cJSON_Delete(result);
        cJSON_Delete(aud);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    cJSON_AddItemToObject(result, "aud", aud);
    cJSON_AddNumberToObject(result, "audioType", setting.settingConf.audioType);

    cJSON_AddNumberToObject(root, "code", 0);
    cJSON_AddItemToObject(root, "result", result);

    return device_responseJSONData(req, root);
}

static int device_PownDown(const void *req, cJSON *param)
{
    if(car_isPowerExistence() || data_getData()->vehicleBattery_mV > setting.settingConf.restoreVoltage)
    {
        return device_rspErr(req, ERR_OPERATION_ERROR);
    }

    device_rspErr(req, ERR_SUCCESS);
    fibo_taskSleep(1000);
    fibo_softPowerOff();
    return 0;
}

static int device_setSaddle(const void *req, cJSON *param)
{
    cJSON *lockSaddle = NULL;
    if(!param)
    {
        return device_rspErr(req, ERR_PARAM_MISSING);
    }
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && !setting_isDefendOn())  //只在设防下能开电池仓锁
    {
        device_rspErr(req, ERR_OPERATION_ERROR);
        return -1;
    }
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    lockSaddle = cJSON_GetObjectItem(param, "sw");
    if(lockSaddle)
    {
        cJSON *isHalfUnlock = cJSON_GetObjectItem(param, "isHalfUnlock");

        if(lockSaddle->type != cJSON_Number || lockSaddle->valueint > 1)
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }

        if(lockSaddle->valueint == 1)
        {
            car_lockSaddle();
            device_PlayAudioWithParam(AUDIO_BEEP, param);
            return device_rspErr(req, ERR_SUCCESS);
        }
        else if(lockSaddle->valueint == 0)
        {
            if(isHalfUnlock && isHalfUnlock->valueint == 1)
            {
                car_unlockSaddleHalf();
            }
            else
            {
                car_unlockSaddle();
            }
            device_PlayAudioWithParam(AUDIO_BEEP, param);
            return device_rspErr(req, ERR_SUCCESS);
        }
    }

    return device_rspErr(req, ERR_PARAM_MISSING);
}

static int device_setBLE(const void *req, cJSON *param)
{
    cJSON *json_token = NULL;
    cJSON *json_name  = NULL;
    cJSON *root = cJSON_CreateObject();
    cJSON *json_root = cJSON_CreateObject();
    uint8_t isParamValid = L_FALSE;

    if(!root || !json_root)
    {
        if(root)
        {
            cJSON_Delete(root);
        }
        if(json_root)
        {
            cJSON_Delete(json_root);
        }
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return -1;
    }

    if(param)
    {
        json_token = cJSON_GetObjectItem(param, "token");
        json_name = cJSON_GetObjectItem(param, "name");
    }

    cJSON_AddNumberToObject(json_root, "code", 0);

    if(json_token)
    {
        isParamValid = L_TRUE;
        setting.settingConf.token = (u32)json_token->valueint;
    }
    cJSON_AddNumberToObject(root, "token", setting.settingConf.token);

    if(json_name)
    {
        isParamValid = L_TRUE;
        strncpy((char *)setting.settingConf.ble_name, json_name->valuestring, MAX_BLE_NAME_LEN);
        bioMsg_setBLEConfig();
    }
    cJSON_AddStringToObject(root, "name", (const char *)setting.settingConf.ble_name);

    if(isParamValid)
    {
        settingConf_save();
    }

    cJSON_AddItemToObject(json_root, "result", root);
    return device_responseJSONData(req, json_root);
}

u8 g_set_audio_check_idx = 0;
u16 g_set_audio_check_crc16 = 0;
static MSG_HEADER device_set_audio_header = {0, 0, 0, 0};

void set_audio_cb(int result, uint8_t *data, int data_len)
{
    if(result == 0  && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(g_set_audio_check_crc16 == crc16 || g_set_audio_check_crc16 == 0)
        {
            audio_deleteCustomAudio(g_set_audio_check_idx);
            audio_deleteBakAudio(g_set_audio_check_idx);
            audio_saveAudio(data, data_len, g_set_audio_check_idx, L_TRUE);
            LOG_INFO("[Device] Audio File:%d Save",g_set_audio_check_idx);
            device_responseOK(&device_set_audio_header);
            cmd_notify_V2(NOTIFY_SINGLEAUDIO_SUCCESS, g_set_audio_check_idx, 0);
            return;
        }
        else
        {
            device_rspErr(&device_set_audio_header, ERR_UPGRADE_CRCERROR);
            LOG_WARNING("[Device] Audio File crc error: %d should be %d",crc16, g_set_audio_check_crc16);
        }
        cmd_notify_V2(NOTIFY_SINGLEAUDIO_FAILED, g_set_audio_check_idx, 0);
    }
    else
    {
        LOG_WARNING("[device] Http get One Audio pack failed errorcode:%d", result);
        device_rspErr(&device_set_audio_header, ERR_OPERATION_ERROR);
    }
}

static int device_set_audio(const void *req, cJSON *param)
{
    cJSON *url = NULL;
    cJSON *idx = NULL;
    cJSON *crc = NULL;
    __attribute__((unused))cJSON *type = NULL;

    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return L_FALSE;
    }

    idx = cJSON_GetObjectItem(param, "idx");
    url = cJSON_GetObjectItem(param, "url");
    crc = cJSON_GetObjectItem(param, "crc");
    type = cJSON_GetObjectItem(param, "type");

    if (!idx)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }

    if(idx->valueint >= AUDIO_MAX_NUMBER || idx->valueint < 1)     //ID未定义
    {
        device_rspErr(req, ERR_PARAM_INVALID);
        return -1;
    }

    g_set_audio_check_idx = idx->valueint;

    if(crc)
    {
        g_set_audio_check_crc16 = crc->valueint;
    }

    //没有url或长度为空则删除定制语音，恢复使用默认语音
    if(!url || !strlen(url->valuestring))
    {
        audio_deleteCustomAudio(g_set_audio_check_idx);
        audio_deleteBakAudio(g_set_audio_check_idx);
        return device_rspErr(req, ERR_SUCCESS);
    }

    if(url && strlen(url->valuestring))
    {
        if(0 == http_get((u8 *)url->valuestring,  set_audio_cb))
        {
            device_set_audio_header.cmd = ((MSG_HEADER *)req)->cmd;
            device_set_audio_header.seq = ((MSG_HEADER *)req)->seq;
            device_set_audio_header.signature = ((MSG_HEADER *)req)->signature;
            return 0;
        }
        else
        {
            return device_rspErr(req, ERR_HTTP_IS_PROCING);
        }
    }

    return device_rspErr(req, ERR_PARAM_INVALID);
}

static uint16_t audioType = 0;
static uint8_t audio_idx[AUDIO_MAX_NUMBER + 1] = {0};//{num,idx1,idx2,idx3}
uint16_t set_audio_in_one_crc = 0;
static MSG_HEADER device_setAudioInOne_header = {0, 0, 0, 0};

void device_setAudioInOne_cb(int result, u8 *data, int data_len)
{
    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char*)data,data_len);//crc校验
        if(set_audio_in_one_crc == crc16 || set_audio_in_one_crc == 0)
        {
            if(audio_sepreateData(data, data_len, audio_idx) == 0)
            {
                device_responseOK(&device_setAudioInOne_header);
                cmd_notify_V2(NOTIFY_MASSAUDIO_SUCCESS, audioType, 0);
                setting.settingConf.audioType = audioType;
                settingConf_save();
                return;
            }
        }
        else
        {
            device_rspErr(&device_setAudioInOne_header, ERR_UPGRADE_CRCERROR);
            LOG_WARNING("crc error: %d should be %d",crc16, set_audio_in_one_crc);
        }
        cmd_notify_V2(NOTIFY_MASSAUDIO_FAILED, audioType, 0);
    }
    else
    {
        LOG_WARNING("[device] Http get Audios pack failed, errorcode:%d", result);
        device_rspErr(&device_setAudioInOne_header, ERR_OPERATION_ERROR);
    }
}

static int device_setAudioInOne(const void *req, cJSON *param)
{
    cJSON *json_url = NULL;
    cJSON *json_idx = NULL;
    cJSON *json_type = NULL;
    cJSON *json_crc = NULL;

    if(!param) //所有参数为空
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }

    //没有url或长度为空则删除定制语音，恢复使用默认语音
    json_url = cJSON_GetObjectItem(param, "url");
    if(!json_url || !strlen(json_url->valuestring))
    {
        audio_factoryDt_withoutOverspeed(); //删除除了定制的超速语音外其他所有定制的语音文件
        setting.settingConf.audioType = 0; //清除定制语音type
        settingConf_save();
        return device_rspErr(req, ERR_SUCCESS);
    }

    json_idx = cJSON_GetObjectItem(param, "idx");
    json_type = cJSON_GetObjectItem(param, "type");
    json_crc = cJSON_GetObjectItem(param, "crc");
    if(json_crc)
    {
        set_audio_in_one_crc = json_crc->valueint;
    }
    if(json_url && json_idx && json_type)
    {
        if(strstr(json_url->valuestring, "http://"))
        {
            uint8_t i = 0;
            cJSON *tmp = 0;

            audioType = json_type->valueint;
            audio_idx[0] = cJSON_GetArraySize(json_idx);
            for(; i < audio_idx[0]; i++)
            {
                tmp = cJSON_GetArrayItem(json_idx, i);
                if(!tmp)
                {
                    memset(audio_idx, 0, AUDIO_MAX_NUMBER);
                    return device_rspErr(req, ERR_PARAM_INVALID);
                }
                audio_idx[i + 1] = tmp->valueint;
            }
            if(0 == http_get((u8 *)json_url->valuestring, device_setAudioInOne_cb))
            {
                device_setAudioInOne_header.cmd = ((MSG_HEADER *)req)->cmd;
                device_setAudioInOne_header.seq = ((MSG_HEADER *)req)->seq;
                device_setAudioInOne_header.signature = ((MSG_HEADER *)req)->signature;
                return 0;
            }
            else
            {
                return device_rspErr(req, ERR_HTTP_IS_PROCING);
            }
        }
    }

    return device_rspErr(req, ERR_PARAM_INVALID);
}

static int device_getState(const void *req, cJSON *param)
{
    cJSON *root = NULL;
    cJSON *json_root = NULL;
    DATA *pData = data_getData();

    root = cJSON_CreateObject();
    if(!root)
    {
        return device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(root);
        return device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
    }

    cJSON_AddNumberToObject(json_root, "code", 0);

    cJSON_AddNumberToObject(root, "defend", setting.statusConf.isDefend);
    cJSON_AddNumberToObject(root, "acc", (car_isAccOn() || setting.statusConf.acc));
    cJSON_AddNumberToObject(root, "accSetting", setting.statusConf.acc ? L_TRUE : L_FALSE);
    cJSON_AddNumberToObject(root, "accCar", car_isAccOn() ? L_TRUE : L_FALSE);
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY && pData->staticBikeBat_mV != 0)
    {
        cJSON_AddNumberToObject(root, "voltageMv", pData->staticBikeBat_mV);//毫伏
    }
    else
    {
        cJSON_AddNumberToObject(root, "voltageMv", pData->vehicleBattery_mV);//毫伏
    }
    int rssi = 0, ber = 0;
    fibo_get_csq(&rssi, &ber);
    cJSON_AddNumberToObject(root, "gsm", rssi);
    if(setting.defaultConf.backWheelType != TYPE_NOBACKWHEEL)
    {
        cJSON_AddNumberToObject(root, "wheelLock", car_isBackWheelLocked() ? L_TRUE : L_FALSE);
    }
    if(setting.defaultConf.helmetType != TYPE_NOHELMET)
    {
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            cJSON_AddNumberToObject(root, "helmetLock", car_isHelmetAtPos() ? 1 : 0);
            cJSON_AddNumberToObject(root, "helmetReact", car_isHelmetClose() ? 1 : 0);
        }
        else
        {
            cJSON_AddNumberToObject(root, "helmetLock", car_isHelmetLocked() ? 1 : 0);
        }
    }
    cJSON_AddNumberToObject(root, "seatLock", car_isSaddleLocked());
    cJSON_AddNumberToObject(root, "totalMiles", setting.statusConf.totalMiles + pData->iMiles);
    cJSON_AddNumberToObject(root, "EtcComm", data_getData()->faultRecord.EtcComm);
    cJSON_AddNumberToObject(root, "BmsComm", data_getData()->faultRecord.BmsComm);

    if(pData->ble_state.isDA14580Alive)
    {
        uint8_t version[16] = {0};
        snprintf((char *)version, 16, "%d.%d.%d", (data_getData()->ble_state.version >> 16) & 0xFF,
                    (data_getData()->ble_state.version >> 8) & 0xFF,
                    (data_getData()->ble_state.version >> 0) & 0xFF);
        cJSON_AddStringToObject(root, "bleVsn", (const char *)version);
    }

//    if(setting.config.isConfigUsed)//如果有配置 配置可以查看
    {
        cJSON *config = cJSON_CreateObject();
        if(!config)
        {
            cJSON_Delete(root);
            cJSON_Delete(json_root);
            device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
            return L_FALSE;
        }
        else
        {
            uint8_t version[16] = {0};
            snprintf((char *)version, 16, "%d.%d.%d", (setting.defaultConf.version >> 16) & 0xFF,
                        (setting.defaultConf.version >> 8) & 0xFF,
                        (setting.defaultConf.version >> 0) & 0xFF);
            cJSON_AddStringToObject(config, "devName", (const char *)setting.defaultConf.name);
            cJSON_AddStringToObject(config, "devVsn", (const char *)version);
            cJSON_AddNumberToObject(config, "devType", setting.defaultConf.productType);
            snprintf((char *)version, 16, "%d.%d.%d", (setting.coreVersion >> 16) & 0xFF,
                        (setting.coreVersion >> 8) & 0xFF,
                        (setting.coreVersion >> 0) & 0xFF);
            cJSON_AddStringToObject(config, "coreVersion", (const char *)version);
            cJSON_AddItemToObject(root, "config", config);
        }
    }

    if(pData->lastPosition.isGPS)
    {
        cJSON *gps = cJSON_CreateObject();
        if(!gps)
        {
            cJSON_Delete(root);
            cJSON_Delete(json_root);
            device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
            return L_FALSE;
        }
        cJSON_AddNumberToObject(gps, "timestamp", pData->lastPosition.timestamp);
        cJSON_AddNumberToObject(gps, "lat", nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lat));
        cJSON_AddNumberToObject(gps, "lng", nmea_ndeg2degree(pData->lastPosition.nmeaInfo.lon));
        cJSON_AddNumberToObject(gps, "speed", (uint8_t)(pData->lastPosition.nmeaInfo.speed + 0.5));
        cJSON_AddNumberToObject(gps, "course", (uint16_t)(pData->lastPosition.nmeaInfo.direction + 0.5));
        cJSON_AddItemToObject(root, "gps", gps);
    }

    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
    {
        cJSON *RFID = cJSON_CreateObject();
        if(!RFID)
        {
            cJSON_Delete(root);
            cJSON_Delete(json_root);
            device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
            return L_FALSE;
        }

        u8 tmp_event = 0;
        if(data_getData()->isRFIDConnect && data_getData()->isCardIdLegal) //RFID连接并扫描到标签
        {
            tmp_event = 1;
            cJSON_AddStringToObject(RFID, "version",pData->RFIDVersion);
            cJSON_AddStringToObject(RFID, "cardID",pData->cardID);
        }
        else if(data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID连接未扫描到标签
        {
            tmp_event = 0;
            cJSON_AddStringToObject(RFID, "version",pData->RFIDVersion);
        }
        else if(!data_getData()->isRFIDConnect && !data_getData()->isCardIdLegal) //RFID未连接
        {
            tmp_event = 2;
        }
        cJSON_AddNumberToObject(RFID, "event",tmp_event);
        cJSON_AddItemToObject(root, "RFID", RFID);
    }

    cJSON_AddItemToObject(json_root, "result", root);

    return device_responseJSONData(req, json_root);
}

static int device_getBMSTimingInfo(const void *req, cJSON *param) //服务器获取BMS信息
{
    cJSON *result = NULL;
    cJSON *json_root = NULL;
    DATA *pData = data_getData();
    result = cJSON_CreateObject();

    LOG_DEBUG("[Device] GetBMSTimingInfo");
    if(!result)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return -1;
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return -1;
    }

    cJSON_AddNumberToObject(json_root, "code", 0);

    if(setting.defaultConf.bmsType == TYPE_NOBMS)
    {
        if(setting.settingConf.isEtcSOC)
        {
            cJSON_AddNumberToObject(result, "SOC", setting.statusConf.bmsSoc);
        }
    }
    else if(setting.defaultConf.bmsType == TYPE_XIAOANBMS)
    {
        cJSON_AddNumberToObject(json_root, "code", 0);
        cJSON_AddNumberToObject(result, "protocolVer", pData->bms.protocolVer);
        cJSON_AddNumberToObject(result, "voltage", pData->bms.voltage);
        cJSON_AddNumberToObject(result, "current", pData->bms.current);
        cJSON_AddNumberToObject(result, "temperature", pData->bms.MOSTemperature);
        cJSON_AddNumberToObject(result, "temperature1", pData->bms.temperature1);
        cJSON_AddNumberToObject(result, "temperature2", pData->bms.temperature2);
        cJSON_AddNumberToObject(result, "cellVoltageMax", pData->bms.cellVoltageMax);
        cJSON_AddNumberToObject(result, "cellVoltageMin", pData->bms.cellVoltageMin);
        cJSON_AddNumberToObject(result, "cellVoltageDIF", pData->bms.cellVoltageDIF);
        cJSON_AddNumberToObject(result, "fault", pData->bms.fault);
        cJSON_AddNumberToObject(result, "SOC", setting.statusConf.bmsSoc);
        cJSON_AddNumberToObject(result, "remain", pData->bms.remainCapacity);
    }
    else if(setting.defaultConf.bmsType == TYPE_XINGHENGBMS)
    {
        float temp = (float)pData->bms.temperature / 10;
        cJSON_AddNumberToObject(result, "temperature", temp);
        cJSON_AddNumberToObject(result, "voltage", pData->bms.voltage);
        cJSON_AddNumberToObject(result, "current", pData->bms.current);
        cJSON_AddNumberToObject(result, "SOC", setting.statusConf.bmsSoc);
        cJSON_AddNumberToObject(result, "remain", pData->bms.remainCapacity);
        cJSON_AddNumberToObject(result, "health", pData->bms.health);
    }
    cJSON_AddItemToObject(json_root, "result", result);

    return device_responseJSONData(req, json_root);
}

static int device_getBMSFixedInfo(const void *req, cJSON *param)
{
    cJSON *result = NULL;
    cJSON *json_root = NULL;
    DATA *pData = data_getData();
    result = cJSON_CreateObject();

    LOG_DEBUG("[Device] GetBMSFixedInfo");

    if(!result)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return -1;
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return -1;
    }
    if(setting.defaultConf.bmsType == TYPE_XIAOANBMS)
    {
        u8 tempData[17] = {0};
        cJSON_AddNumberToObject(json_root, "code", 0);

        memcpy(tempData, pData->bms.manufacturer, 16);
        cJSON_AddStringToObject(result, "manufacturer", (const char *)tempData);

        memset(tempData, 0, 17);
        memcpy(tempData, pData->bms.model, 16);
        cJSON_AddStringToObject(result, "model", (const char *)tempData);

        cJSON_AddNumberToObject(result, "hardware", pData->bms.hardwareVer);
        cJSON_AddNumberToObject(result, "software", pData->bms.softwareVer);

        memset(tempData, 0, 17);
        memcpy(tempData, pData->bms.SN, 16);
        cJSON_AddStringToObject(result, "SN", (const char *)tempData);

        memset(tempData, 0, 17);
        memcpy(tempData, pData->bms.gpsId, 16);
        cJSON_AddStringToObject(result, "gpsId", (const char *)tempData);

        cJSON_AddNumberToObject(result, "capacity", pData->bms.capacity);
        cJSON_AddNumberToObject(result, "cycle", pData->bms.cycleCount);
    }
    else if(setting.defaultConf.bmsType == TYPE_XINGHENGBMS)
    {
        cJSON_AddNumberToObject(json_root, "code", 0);
        cJSON_AddNumberToObject(result, "software", pData->bms.softwareVer);
        cJSON_AddNumberToObject(result, "hardware", pData->bms.hardwareVer);
        cJSON_AddStringToObject(result, "SN", (const char *)pData->bms.SN);
        cJSON_AddNumberToObject(result, "capacity", pData->bms.capacity);
        cJSON_AddNumberToObject(result, "cycle", pData->bms.cycleCount);
    }
    else if(setting.defaultConf.bmsType == TYPE_NOBMS)
    {
        ;
    }
    cJSON_AddItemToObject(json_root, "result", result);

    return device_responseJSONData(req, json_root);
}

static int device_getETCInfo(const void *req, cJSON *param)
{
    cJSON *result = NULL;
    cJSON *json_root = NULL;

    DATA *pData = data_getData();
    result = cJSON_CreateObject();
    if(!result)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    cJSON_AddNumberToObject(json_root, "code", 0);

    cJSON_AddNumberToObject(result, "protocolVer", pData->etc.protocolVer);
    cJSON_AddNumberToObject(result, "manufacturer", pData->etc.manufacturer);
    cJSON_AddNumberToObject(result, "type", pData->etc.type);
    cJSON_AddNumberToObject(result, "version", pData->etc.version);
    cJSON_AddNumberToObject(result, "voltage", pData->etc.voltage_mV);
    cJSON_AddNumberToObject(result, "current", pData->etc.current_mA);
    cJSON_AddNumberToObject(result, "pulse", pData->etc.pulse);
    cJSON_AddNumberToObject(result, "speed", pData->etc.speed);
    cJSON_AddNumberToObject(result, "fault", pData->etc.fault);
    cJSON_AddNumberToObject(result, "function", pData->etc.function);
    cJSON_AddNumberToObject(result, "ratio", pData->etc.ratio);
    cJSON_AddNumberToObject(result, "limitSpeed", setting.defaultConf.etcSpeed);
    cJSON_AddNumberToObject(result, "voltageLimit", setting.settingConf.etcProtectVoltage_100mV * 100);
    cJSON_AddNumberToObject(result, "currentLimit", setting.settingConf.etcLimitCurrent_100mA * 100);
    cJSON_AddNumberToObject(result, "timestamp", pData->etc.timestamp);

    if(setting.settingConf.isEtcSOC == 1)
    {
        cJSON_AddNumberToObject(result, "soc", pData->etc.soc);
        cJSON_AddNumberToObject(result, "soh", pData->etc.soh);
        cJSON_AddNumberToObject(result, "capacity", pData->etc.capacity);
        cJSON_AddNumberToObject(result, "cycle", pData->etc.cycle);
        cJSON_AddNumberToObject(result, "batTemp", pData->etc.batTemp);
        cJSON_AddNumberToObject(result, "bmsFault", pData->etc.bmsFault);
    }
    cJSON_AddItemToObject(json_root, "result", result);
    return device_responseJSONData(req, json_root);
}

static int device_setETCSpeed(const void *req, cJSON *param)
{
    cJSON *json_speed = NULL;
    if(param == NULL)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return 0;
    }
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    json_speed = cJSON_GetObjectItem(param, "speed");
    if(json_speed)
    {
        device_rspErr(req, ERR_SUCCESS);

        setting.defaultConf.etcSpeed = json_speed->valueint;
        setting.settingConf.isDefaultSpeed = L_FALSE;
        settingConf_save();
        return 0;
    }

    return device_rspErr(req, ERR_PARAM_MISSING);
}

static int device_setETCProtectVoltage(const void *req, cJSON *param)
{
    cJSON *json_speed = NULL;
    if(param == NULL)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return 0;
    }
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    json_speed = cJSON_GetObjectItem(param, "volatge");
    if(json_speed)
    {
        setting.settingConf.etcProtectVoltage_100mV = json_speed->valueint / 100;
        settingConf_save();
        return device_rspErr(req, ERR_SUCCESS);
    }
    return device_rspErr(req, ERR_PARAM_MISSING);
}

static int device_setETCLimitCurrent(const void *req, cJSON *param)
{
    cJSON *json_speed = NULL;
    if(param == NULL)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return 0;
    }
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    json_speed = cJSON_GetObjectItem(param, "current");
    if(json_speed)
    {
        setting.settingConf.etcLimitCurrent_100mA = json_speed->valueint / 100;
        settingConf_save();
        return device_rspErr(req, ERR_SUCCESS);
    }
    return device_rspErr(req, ERR_PARAM_MISSING);
}

static int device_setETCSlowStart(const void *req, cJSON *param)
{
    cJSON *json_slowstart = NULL;
    if(param == NULL)
    {
        return device_rspErr(req, ERR_PARAM_MISSING);
    }
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    json_slowstart = cJSON_GetObjectItem(param, "sw");
    if(json_slowstart)
    {
        setting.settingConf.etcIsSlowStart = json_slowstart->valueint;
        settingConf_save();
        return device_rspErr(req, ERR_SUCCESS);
    }
    return device_rspErr(req, ERR_PARAM_MISSING);
}

static int device_setETCLight(const void *req, cJSON *param)
{
    cJSON *light = NULL;
    if(param == NULL)
    {
        return device_rspErr(req, ERR_PARAM_MISSING);
    }
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    light = cJSON_GetObjectItem(param, "sw");
    if(light)
    {
        uint8_t sw = light->valueint;
        etcMsg_setETCLight(sw);
        return device_rspErr(req, ERR_SUCCESS);
    }
    return device_rspErr(req, ERR_PARAM_MISSING);
}

static int device_getNMEA_str(const void *req, cJSON *param)
{
    cJSON *result = NULL;
    cJSON *json_root = NULL;

    result = cJSON_CreateObject();
    if(!result)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        return device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
    }

    cJSON_AddNumberToObject(json_root, "code", 0);

    char *nmeaStr = (char *)gps_getLastNMEA_strLimit();
    cJSON_AddStringToObject(result, "nmea", nmeaStr);

    cJSON_AddItemToObject(json_root, "result", result);

    return device_responseJSONData(req, json_root);
}

static int device_setLockCarForce(const void *req, cJSON *param)
{
    cJSON *forceLock = NULL;
    cJSON *idx = cJSON_GetObjectItem(param, "idx");
    cJSON *volume = cJSON_GetObjectItem(param, "volume");
    if(param == NULL)
    {
        return device_rspErr(req, ERR_PARAM_MISSING);
    }

    forceLock = cJSON_GetObjectItem(param, "forceLock");
    if(forceLock)
    {
        if(idx && idx->valueint > 0 && idx->valueint < AUDIO_MAX_NUMBER)
        {
            if(volume)
            {
                audio_playWithVolume(idx->valueint, volume->valueint);
            }
            else
            {
                audio_play(idx->valueint);
            }
        }
        setting.settingConf.forceLock = forceLock->valueint;
        settingConf_save();
        return device_rspErr(req, ERR_SUCCESS);
    }
    return device_rspErr(req, ERR_PARAM_MISSING);
}
static MSG_HEADER device_get_cellinfo_header = {0, 0, 0, 0};
static int device_getCellInfo(const void *req, cJSON *param)
{
    opencpu_cellinfo_t cellinfo;
    cJSON *root = NULL;
    cJSON *json_root = NULL;
    device_get_cellinfo_header.cmd = ((MSG_HEADER *)req)->cmd;
    device_get_cellinfo_header.seq = ((MSG_HEADER *)req)->seq;
    device_get_cellinfo_header.signature = ((MSG_HEADER *)req)->signature;

    if(fibo_getCellInfo(&cellinfo, 0) == 0)
    {
        root = cJSON_CreateObject();
        if(!root)
        {
            device_rspErr(&device_get_cellinfo_header, ERR_MEMORY_NOT_ENOUGH);
            return L_FALSE;
        }

        json_root = cJSON_CreateObject();
        if(!json_root)
        {
            cJSON_Delete(root);
            device_rspErr(&device_get_cellinfo_header, ERR_MEMORY_NOT_ENOUGH);
            return L_FALSE;
        }

        cJSON_AddNumberToObject(json_root, "code", 0);
        {
            int i = 0;
            cJSON *array = NULL;
            cJSON *gps = cJSON_CreateObject();
            cJSON *tmp = NULL;
            if(!gps)
            {
                cJSON_Delete(root);
                cJSON_Delete(json_root);
                device_rspErr(&device_get_cellinfo_header, ERR_MEMORY_NOT_ENOUGH);
                return -1;
            }
            cJSON_AddNumberToObject(gps, "mcc", COV2MCC(cellinfo.lte_cellinfo.lteScell.imsi));
            cJSON_AddNumberToObject(gps, "mnc", COV2MNC(cellinfo.lte_cellinfo.lteScell.imsi));

            if(cellinfo.curr_rat == 4)
            {
                LOG_DEBUG("LTE ncELL num:%d",cellinfo.lte_cellinfo.lteNcellNum);
                array = cJSON_CreateArray();
                if(!array)
                {
                    cJSON_Delete(gps);
                    cJSON_Delete(root);
                    cJSON_Delete(json_root);
                    device_rspErr(&device_get_cellinfo_header, ERR_MEMORY_NOT_ENOUGH);
                    return -1;
                }
                tmp = cJSON_CreateObject();
                if(!tmp)
                {
                    cJSON_Delete(gps);
                    cJSON_Delete(root);
                    cJSON_Delete(array);
                    cJSON_Delete(json_root);
                    device_rspErr(&device_get_cellinfo_header, ERR_MEMORY_NOT_ENOUGH);
                    return -1;
                }
                cJSON_AddNumberToObject(tmp, "lac", cellinfo.lte_cellinfo.lteScell.tac);
                cJSON_AddNumberToObject(tmp, "ci", cellinfo.lte_cellinfo.lteScell.cellId);
                cJSON_AddNumberToObject(tmp, "rxl", cellinfo.lte_cellinfo.lteScell.rsrp-140);
                cJSON_AddItemToArray(array, tmp);
                for(i = 0; i < cellinfo.lte_cellinfo.lteNcellNum; i++)
                {
                    tmp = cJSON_CreateObject();
                    if(!tmp)
                    {
                        cJSON_Delete(gps);
                        cJSON_Delete(root);
                        cJSON_Delete(array);
                        cJSON_Delete(json_root);
                        device_rspErr(&device_get_cellinfo_header, ERR_MEMORY_NOT_ENOUGH);
                        break;
                    }
                    cJSON_AddNumberToObject(tmp, "lac", cellinfo.lte_cellinfo.lteNcell[i].cellAccRelInfo.tac);
                    cJSON_AddNumberToObject(tmp, "ci", cellinfo.lte_cellinfo.lteNcell[i].cellAccRelInfo.cellId);
                    cJSON_AddNumberToObject(tmp, "rxl", cellinfo.lte_cellinfo.lteNcell[i].rsrp-140);
                    cJSON_AddItemToArray(array, tmp);
                }
                cJSON_AddItemToObject(gps, "ltecells", array);
            }
            else if(cellinfo.curr_rat == 2)
            {
                LOG_DEBUG("GSM ncELL num:%d",cellinfo.gsm_cellinfo.pNeighborCellInfo.nTSM_NebCellNUM);
                array = cJSON_CreateArray();
                if(!array)
                {
                    cJSON_Delete(gps);
                    cJSON_Delete(root);
                    cJSON_Delete(json_root);
                    device_rspErr(&device_get_cellinfo_header, ERR_MEMORY_NOT_ENOUGH);
                    return -1;
                }
                cJSON *tmp = cJSON_CreateObject();
                if(!tmp)
                {
                    cJSON_Delete(gps);
                    cJSON_Delete(root);
                    cJSON_Delete(array);
                    cJSON_Delete(json_root);
                    device_rspErr(&device_get_cellinfo_header, ERR_MEMORY_NOT_ENOUGH);
                    return -1;
                }
//                cJSON_AddNumberToObject(tmp, "lac", cellinfo.lte_cellinfo.gsmNcell.);
//                cJSON_AddNumberToObject(tmp, "ci", cellinfo.gsm_cellinfo.pCurrCellInfo.nTSM_CellID);
//                cJSON_AddNumberToObject(tmp, "rxl", cellinfo.gsm_cellinfo.pCurrCellInfo.lteScell.rsrp-140);
//                cJSON_AddItemToArray(array, tmp);
//                for(i = 0; i < cellinfo.lte_cellinfo.lteNcellNum; i++)
//                {
//                    cJSON_AddNumberToObject(tmp, "lac", cellinfo.lte_cellinfo.lteNcell[i].cellAccRelInfo.tac);
//                    cJSON_AddNumberToObject(tmp, "ci", cellinfo.lte_cellinfo.lteNcell[i].cellAccRelInfo.cellId);
//                    cJSON_AddNumberToObject(tmp, "rxl", cellinfo.lte_cellinfo.lteNcell[i].rsrp-140);
//                    cJSON_AddItemToArray(array, tmp);
//                }
                cJSON_AddItemToObject(gps, "cells", array);
            }
            cJSON_AddItemToObject(root, "cell", gps);
        }
        cJSON_AddItemToObject(json_root, "result", root);
        device_responseJSONData(&device_get_cellinfo_header, json_root);
    }
    return 0;
}

static u16 changeConfig_check_crc16 = 0;
static MSG_HEADER device_changeConfig_header = {0, 0, 0, 0};

static void device_UpgradeConfig(int result, uint8_t *data, int data_len)
{
    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(changeConfig_check_crc16 == crc16)
        {
            if(setting_getVersion_cb(result, data, data_len) == 0)
            {
                data_getData()->isLogined = L_FALSE; //重发登录包,更新小安工具上的版本号
                device_responseOK(&device_changeConfig_header);
                LOG_INFO("[device] config upgrade success");
            }
            else
            {
                device_rspErr(&device_changeConfig_header, ERR_OPERATION_ERROR);
                LOG_INFO("[device] config upgrade failed");
            }
        }
        else
        {
            device_rspErr(&device_changeConfig_header, ERR_UPGRADE_CRCERROR);
            LOG_WARNING("[device] config json File crc error! UrlInput:%d  Operate:%d", changeConfig_check_crc16, crc16);
        }
    }
    else
    {
        LOG_WARNING("[device] Http get config json file failed, errorcode:%d", result);
        device_rspErr(&device_changeConfig_header, ERR_OPERATION_ERROR);
    }
}

static int device_changeConfig(const void *req, cJSON *param)
{
    cJSON *json_url = NULL;
    cJSON *json_crc = NULL;

    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }

    json_url = cJSON_GetObjectItem(param, "url");
    json_crc = cJSON_GetObjectItem(param, "crc");

    if(json_url)
    {
        if(json_crc)
        {
            changeConfig_check_crc16 = json_crc->valueint;
        }
        else
        {
            device_rspErr(req, ERR_PARAM_MISSING);
            return -1;
        }
        if(strstr(json_url->valuestring, "http://"))
        {
            int ret = http_get((u8 *)json_url->valuestring, device_UpgradeConfig); //异步获取
            if(ret != 0)
            {
                LOG_ERROR("[device] http error %d", ret);
                return device_rspErr(req, ERR_OPERATION_ERROR);
            }
            device_changeConfig_header.cmd = ((MSG_HEADER *)req)->cmd;
            device_changeConfig_header.seq = ((MSG_HEADER *)req)->seq;
            device_changeConfig_header.signature = ((MSG_HEADER *)req)->signature;
            return 0; //等待异步下载
        }
        else
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }
    }
    return device_rspErr(req, ERR_PARAM_INVALID);

}

//网络解锁头盔
static int device_Helmet(const void *req, cJSON *param)
{
    cJSON *sw = NULL;
    cJSON *json_isAutoLock = NULL;
    cJSON *json_isAutoOpen = NULL;
    cJSON *root = NULL;
    cJSON *result = NULL;
    u8 isAutoLock = L_TRUE; //开锁后默认自动上锁
    u8 isAutoOpen = L_FALSE; //关锁失败后默认不自动开锁
    int ret = 0; //默认为0

    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    if(!param)
    {
        return device_rspErr(req, ERR_PARAM_MISSING);
    }

    sw = cJSON_GetObjectItem(param, "sw");
    if(!sw)
    {
        return device_rspErr(req, ERR_PARAM_MISSING);
    }

    if(sw->type != cJSON_Number || (sw->valueint != 0 && sw->valueint != 1))
    {
        return device_rspErr(req, ERR_PARAM_INVALID);
    }

    json_isAutoLock = cJSON_GetObjectItem(param, "isAutoLock");
    if(json_isAutoLock && json_isAutoLock->type == cJSON_Number 
    && (json_isAutoLock->valueint == 0 || json_isAutoLock->valueint == 1))
    {
        isAutoLock = json_isAutoLock->valueint;
    }

    json_isAutoOpen = cJSON_GetObjectItem(param, "isAutoOpen");
    if(json_isAutoOpen && json_isAutoOpen->type == cJSON_Number 
    && (json_isAutoOpen->valueint == 0 || json_isAutoOpen->valueint == 1))
    {
        isAutoOpen = json_isAutoOpen->valueint;
    }

    if(sw->valueint == 0)
    {
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            ret = car_unlockHelmet_sync(isAutoLock); //同步阻塞接口，以便操作完成后返回锁状态
        }
        else
        {
            if(isAutoLock)
            {
                setting.statusConf.helmetTargetStatus = HELMET_UNLOCK_WITH_AUTOLOCK;
            }
            else
            {
                setting.statusConf.helmetTargetStatus = HELMET_UNLOCK_ONLY;
            }
            statusConf_save();
            car_unlockHelmet();
        }
        device_PlayAudioWithParam(AUDIO_BEEP, param); //开锁直接播放语音
    }
    else if(sw->valueint == 1)
    {
        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
        {
            ret = car_lockHelmet_sync(isAutoOpen); //同步阻塞接口，以便操作完成后返回锁状态
        }
        else
        {
            car_lockHelmet();
        }

        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX && ret == 0)
        {
            device_PlayAudioWithParam(AUDIO_HELMET_LOCK, param); //关锁成功则播放头盔已归还
        }
        else
        {
            device_PlayAudioWithParam(AUDIO_BEEP, param); //关锁播放语音
        }
    }
    
    root = cJSON_CreateObject();
    result = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "code", (ret == 0) ? ERR_SUCCESS : ERR_OPERATION_ERROR);
    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
    {
        cJSON_AddNumberToObject(result, "helmet6Lock", car_isHelmetClose() ? 1 : 0);
        cJSON_AddNumberToObject(result, "helmet6React", car_isHelmetAtPos() ? 1 : 0);
    }
    else
    {
        cJSON_AddNumberToObject(result, "helmetLock", car_isHelmetLocked() ? 1 : 0);
    }
    cJSON_AddItemToObject(root, "result", result);
    return device_responseJSONData(req, root);
}

static uint16_t fence_upgrade_check_crc16 = 0;
static uint8_t fence_isFenceEnable = 0;
void device_upgradeFence_cb(int result, uint8_t *data, int data_len, const void* msg)
{
    L_BOOL ret = L_FALSE;

    if(result == 0 && data)
    {
        uint16_t crc16 = crc16_ccitt((const char *)data, data_len);
        if(fence_upgrade_check_crc16 == crc16) //CRC校验，如果成功，则替换升级文件
        {
            if(0 != memcmp(data, "XiaoanTech", 10))
            {
                LOG_ERROR("fence data signature error.");
                return;
            }

            ret = fence_saveFenceFromData((FENCE *)data);//存储围栏数据
            if(!ret)
            {
                LOG_ERROR("fence data save error.");
                return;
            }

            ret = fence_getFenceFromFile(&data_getData()->fence);//更新围栏数据
            if(!ret)
            {
                LOG_ERROR("fence data get error.");
                return;
            }

            if(setting.settingConf.isFenceEnable != fence_isFenceEnable)
            {
                setting.settingConf.isFenceEnable = fence_isFenceEnable;
                settingConf_save();
            }
        }
        else
        {
            LOG_ERROR("fence upgrade crc check faield,crc = %u (%x)h", fence_upgrade_check_crc16, crc16);
        }
    }
}

static int device_upgradeFence(const void *req, cJSON *param)
{
    cJSON *json_url = NULL;
    cJSON *json_crc = NULL;
    cJSON *json_isFenceEnable = NULL;
    DATA *pData = data_getData();
    u8 ret = 0;

    if(!param)
    {
        return device_rspErr(req, ERR_PARAM_INVALID);
    }

    json_url = cJSON_GetObjectItem(param, "url");
    json_crc = cJSON_GetObjectItem(param, "crc");
    json_isFenceEnable = cJSON_GetObjectItem(param, "isFenceEnable");
    if(json_isFenceEnable)
    {
        fence_isFenceEnable = json_isFenceEnable->valueint;
    }
    if(json_url && json_crc)//有url，且有对应的fenceid和crc，使用指定路径升级
    {
        fence_upgrade_check_crc16 = json_crc->valueint;
        if(strstr(json_url->valuestring, "http://"))
        {
            ret = http_get(json_url->valuestring, device_upgradeFence_cb);
            if(0 == ret)
            {
                return device_rspErr(req, ERR_SUCCESS);
            }
            return device_rspErr(req, ERR_HTTP_IS_PROCING);
        }
    }

    return device_rspErr(req, ERR_PARAM_INVALID);
}

//命令主动道钉扫描
static int device_getNearTBeaconInfo(const void *req, cJSON *param)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *json_root = cJSON_CreateObject();

    u8 tempData[24 + 1] = {0};
    DATA *pData = data_getData();
    beaconInfo_t *pBeaconInfo = data_getTBeaconInfo(3);

    if(!root || !json_root)
    {
        if(root)
        {
            cJSON_Delete(root);
        }
        if(json_root)
        {
            cJSON_Delete(json_root);
        }
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    if(!pBeaconInfo || pBeaconInfo->dbm > setting.settingConf.beaconRssi)
    {
        return device_rspErr(req, ERR_OPERATION_ERROR);
    }

    cJSON_AddNumberToObject(json_root, "code", 0);
    cJSON_AddNumberToObject(root, "event", EVENT_FINDTBEACON);
    HexToAscii(pBeaconInfo->mac, tempData, 6);
    cJSON_AddStringToObject(root, "tBeaconAddr", (const char *)tempData);
    cJSON_AddNumberToObject(root, "realRssi", pBeaconInfo->dbm);
    cJSON_AddNumberToObject(root, "beaconRssi", setting.settingConf.beaconRssi);
    if(strlen(pBeaconInfo->tBeaconID) != 0) //浩源道钉才返回id,soc，vsn信息，其他默认没有
    {
        cJSON_AddStringToObject(root, "tBeaconId", (const char *)pBeaconInfo->tBeaconID);
        cJSON_AddNumberToObject(root, "tBeaconSOC", pBeaconInfo->tBeaconSOC);

        {
            u8 version_str[5] = {0};
            HexToAscii(pBeaconInfo->tBeaconVersion, version_str, 2);
            cJSON_AddStringToObject(root, "TbeaconVsn", (const char *)version_str);
        }
    }
    else
    {
        cJSON_AddStringToObject(root, "tBeaconId", " ");
        cJSON_AddNumberToObject(root, "tBeaconSOC", 0);
        cJSON_AddStringToObject(root, "TbeaconVsn", " ");
    }

    if(pData->lastPosition.isGPS)
    {
        cJSON_AddNumberToObject(root, "lon", gps_getGPSValue(pData->lastPosition.nmeaInfo.lon));
        cJSON_AddNumberToObject(root, "lat", gps_getGPSValue(pData->lastPosition.nmeaInfo.lat));
        cJSON_AddNumberToObject(root, "timestamp", rtc_getTimestamp());
    }
    else
    {
        cJSON_AddNumberToObject(root, "lon", gps_getGPSValue(pData->lastPosition.lbsInfo.lon));
        cJSON_AddNumberToObject(root, "lat", gps_getGPSValue(pData->lastPosition.lbsInfo.lat));
        cJSON_AddNumberToObject(root, "timestamp", pData->lastPosition.lbsTimestamp);
    }
    cJSON_AddItemToObject(json_root, "result", root);
    return device_responseJSONData(req, json_root);
}

static u16 etc_upgrade_check_crc16 = 0;
static MSG_HEADER device_saveETCFirmware_header = {0, 0, 0, 0};
static u16 device_etc_verison = 0;

static void device_saveETCFirmware(int result, uint8_t *data, int data_len)
{
    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(etc_upgrade_check_crc16 == crc16)
        {
            fs_deleteFile(UPGRADE_ETC_FILE_NAME);
            fs_saveFileData(UPGRADE_ETC_FILE_NAME,data,data_len);
            LOG_INFO("[Device] ETC OTA File Save->%s<",UPGRADE_ETC_FILE_NAME);
            setting.statusConf.etcUpgradeVersion = device_etc_verison;//保存下发的ETC版本号
            setting.statusConf.etcFirmwareCRC = etc_upgrade_check_crc16;
            setting.statusConf.etcUpgradeFlag = 1;//下载文件后认为需要升级控制器
            statusConf_save();
            device_responseOK(&device_saveETCFirmware_header);
            LOG_DEBUG("[device] ETC OTA Start");
            LOG_DEBUG("[device] ETC Version:%d CRC:%d",device_etc_verison,etc_upgrade_check_crc16);
            etcOta_upgardeTimerHandler();
            timer_startRepeat(TIMER_ETC_UPGRADE, TIMER_S, 5, etcOta_upgardeTimerHandler);
        }
        else
        {
            fs_deleteFile(UPGRADE_ETC_FILE_NAME);
            device_rspErr(&device_saveETCFirmware_header, ERR_UPGRADE_CRCERROR);
            LOG_ERROR("[Device] ETC OTA File crc error: %d should be %d",crc16, etc_upgrade_check_crc16);
        }
    }
    else
    {
        LOG_ERROR("[device] Http get ETC pack failed, errorcode:%d", result);
        device_rspErr(&device_saveETCFirmware_header, ERR_OPERATION_ERROR);
    }
}

static int device_ETC_upgrade(const void *req, cJSON *param)
{
    cJSON *json_url = NULL;
    cJSON *json_crc = NULL;
    cJSON *json_version = NULL;

    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }

    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    if(!setting_isDefendOn() || setting.statusConf.isTerminateETCUpgrade)
    {
        device_rspErr(req, ERR_OPERATION_ERROR );
        return -1;
    }

    json_url = cJSON_GetObjectItem(param, "url");
    json_crc = cJSON_GetObjectItem(param, "crc");
    json_version = cJSON_GetObjectItem(param, "version");
    if(!json_url || !json_crc || !json_version || !strstr(json_url->valuestring, "http://"))
    {
        return device_rspErr(req, ERR_PARAM_INVALID);
    }
    etc_upgrade_check_crc16 = json_crc->valueint;
    device_etc_verison = json_version->valueint;

    if(car_isPowerExistence() && device_etc_verison != data_getData()->etc.version)
    {
        int ret = http_get((u8 *)json_url->valuestring, device_saveETCFirmware); //异步获取
        if(ret != 0)
        {
            return device_rspErr(req, ERR_OPERATION_ERROR);
        }
        device_saveETCFirmware_header.cmd = ((MSG_HEADER *)req)->cmd;
        device_saveETCFirmware_header.seq = ((MSG_HEADER *)req)->seq;
        device_saveETCFirmware_header.signature = ((MSG_HEADER *)req)->signature;
        return 0; //等待异步下载
    }

    return device_rspErr(req, ERR_OPERATION_ERROR);
}



static u16 bms_upgrade_check_crc16 = 0;
static MSG_HEADER device_saveBMSFirmware_header = {0, 0, 0, 0};
static u16 device_bms_verison = 0;

static void device_saveBMSFirmware(int result, uint8_t *data, int data_len)
{
    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(bms_upgrade_check_crc16 == crc16)
        {
            fs_deleteFile(UPGRADE_BMS_FILE_NAME);
            fs_saveFileData(UPGRADE_BMS_FILE_NAME,data,data_len);
            LOG_INFO("[Device] BMS OTA File Save->%s<",UPGRADE_BMS_FILE_NAME);
            setting.statusConf.bmsUpgradeVersion = device_bms_verison;//保存下发的ETC版本号
            setting.statusConf.bmsFirmwareCRC = bms_upgrade_check_crc16;
            setting.statusConf.bmsUpgradeFlag = 1;
            statusConf_save();
            device_responseOK(&device_saveBMSFirmware_header);
            LOG_DEBUG("[device] BMS OTA Start");
            LOG_DEBUG("[device] BMS Version:%d CRC:%d",device_bms_verison,bms_upgrade_check_crc16);
            bmsOta_upgardeTimerHandler();
            timer_startRepeat(TIMER_ETC_UPGRADE, TIMER_S, 5, bmsOta_upgardeTimerHandler);
        }
        else
        {
            fs_deleteFile(UPGRADE_ETC_FILE_NAME);
            LOG_WARNING("[Device] BMS OTA File crc error: %d should be %d",crc16, bms_upgrade_check_crc16);
            device_rspErr(&device_saveBMSFirmware_header, ERR_UPGRADE_CRCERROR);
        }
    }
    else
    {
        LOG_WARNING("[device] Http get BMS pack failed, errorcode:%d", result);
        device_rspErr(&device_saveBMSFirmware_header, ERR_OPERATION_ERROR);
    }
}

static int device_BMS_upgrade(const void *req, cJSON *param)
{
    cJSON *json_url = NULL;
    cJSON *json_crc = NULL;
    cJSON *json_version = NULL;

    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }

    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag )
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }

    if(!setting_isDefendOn() || setting.statusConf.isTerminateBMSUpgrade)
    {
        device_rspErr(req, ERR_OPERATION_ERROR);
        return -1;
    }

    json_url = cJSON_GetObjectItem(param, "url");
    json_crc = cJSON_GetObjectItem(param, "crc");
    json_version = cJSON_GetObjectItem(param, "version");
    if(!json_url || !json_crc || !json_version || !strstr(json_url->valuestring, "http://"))
    {
        return device_rspErr(req, ERR_PARAM_INVALID);
    }
    bms_upgrade_check_crc16 = json_crc->valueint;
    device_bms_verison = json_version->valueint;

    if(car_isPowerExistence() && device_bms_verison != data_getData()->bms.softwareVer)//控制器版本号不同则开始升级
    {
        int ret = http_get((u8 *)json_url->valuestring, device_saveBMSFirmware); //异步获取
        if(ret != 0)
        {
            return device_rspErr(req, ERR_OPERATION_ERROR);
        }
        device_saveBMSFirmware_header.cmd = ((MSG_HEADER *)req)->cmd;
        device_saveBMSFirmware_header.seq = ((MSG_HEADER *)req)->seq;
        device_saveBMSFirmware_header.signature = ((MSG_HEADER *)req)->signature;
        return 0; //等待异步下载
    }

    return device_rspErr(req, ERR_OPERATION_ERROR);
}



static u16 firmware_upgrade_check_crc16 = 0;
static MSG_HEADER device_FOTA_header = {0, 0, 0, 0};

static void device_UpgradeFirmware(int result, uint8_t *data, int data_len)
{
    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(firmware_upgrade_check_crc16 == crc16 ||firmware_upgrade_check_crc16 == 0)
        {
            setting_setRebootType(REBOOT_UPGRADE);
            device_responseOK(&device_FOTA_header);
            fibo_taskSleep(1500); //保证resp发出去
            int ret = fibo_firmware_handle((char *)data, data_len);
            if(0 < ret)
            {
                LOG_ERROR("[device] fibo_firmware_handle failed");
                device_rspErr(&device_FOTA_header, ERR_OPERATION_ERROR);
                return;
            }
            LOG_INFO("[device] Firmware upgrade success");
        }
        else
        {
            device_rspErr(&device_FOTA_header, ERR_UPGRADE_CRCERROR);
            LOG_WARNING("[Device] FIRMWARE File crc error! UrlInput:%d  Operate:%d",firmware_upgrade_check_crc16, crc16);
        }
    }
    else
    {
        LOG_WARNING("[device] Http get Firmware pack failed, errorcode:%d", result);
        device_rspErr(&device_FOTA_header, ERR_OPERATION_ERROR);
    }
}

static int device_FOTA(const void *req, cJSON *param)
{
    cJSON *json_url = NULL;
    cJSON *json_crc = NULL;

    if(!param)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return -1;
    }
    if(setting.statusConf.bmsUpgradeFlag|| setting.statusConf.etcUpgradeFlag)
    {
        device_rspErr(req, ERR_OTA_UPGRADING);
        return -1;
    }
    if((setting.coreVersion & 0xff) == 9  && (setting.coreVersion >> 8 & 0xff)== 1  && (setting.coreVersion >> 16 & 0xff)== 5 )  //5.1.9内核不支持FOTA 若进行操作会发生异常
    {
        return device_rspErr(req, ERR_OPERATION_ERROR);
    }
    json_url = cJSON_GetObjectItem(param, "url");
    json_crc = cJSON_GetObjectItem(param, "crc");
    if(json_url)
    {
        if(json_crc)
        {
            firmware_upgrade_check_crc16 = json_crc->valueint;
        }
        else
        {
            firmware_upgrade_check_crc16 = 0;
        }
        if(strstr(json_url->valuestring, "http://"))
        {
            int ret = http_get((u8 *)json_url->valuestring, device_UpgradeFirmware); //异步获取
            if(ret != 0)
            {
                LOG_ERROR("[device] http error %d", ret);
                return device_rspErr(req, ERR_OPERATION_ERROR);
            }
            device_FOTA_header.cmd = ((MSG_HEADER *)req)->cmd;
            device_FOTA_header.seq = ((MSG_HEADER *)req)->seq;
            device_FOTA_header.signature = ((MSG_HEADER *)req)->signature;
            return 0; //等待异步下载
        }
        else
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }
    }
    return device_rspErr(req, ERR_PARAM_INVALID);
}

static u16 g_set_overspeed_crc16 = 0;
static u8 g_set_overspeed_volume = OVERSPEED_VOLUME_DEFAULT;//默认
static u16 g_set_overspeed_period = 3;
static char g_set_url[MAX_URL_LEN] = {0};
static MSG_HEADER device_overspeed_header = {0, 0, 0, 0};

void set_overspeed_cb(int result, uint8_t *data, int data_len)
{
    if(result == 0 && data)
    {
        u16 crc16 = crc16_ccitt((const char *)data, data_len);
        if(g_set_overspeed_crc16 == crc16 || g_set_overspeed_crc16 == 0)
        {
            audio_deleteCustomAudio(AUDIO_OVER_SPEED);
            audio_deleteBakAudio(AUDIO_OVER_SPEED);
            audio_saveAudio(data, data_len, AUDIO_OVER_SPEED, L_TRUE);
            LOG_INFO("[Device] Audio File:%d Save",AUDIO_OVER_SPEED);
            setting.settingConf.overSpeedVolume = g_set_overspeed_volume;
            memcpy((char *)setting.settingConf.overSpeedUrl, g_set_url, strlen(g_set_url));
            if(g_set_overspeed_period)
            {
                setting.settingConf.checkOverSpeedTime = g_set_overspeed_period;
            }
            setting.settingConf.overSpeedCrc = g_set_overspeed_crc16;
            settingConf_save();
            device_responseOK(&device_overspeed_header);
            cmd_notify_V2(NOTIFY_SETOVERSPEEDAUDIO_SUCCESS, 0, 0);
            return;
        }
        else
        {
            device_rspErr(&device_overspeed_header, ERR_UPGRADE_CRCERROR);
            LOG_WARNING("[Device] OverSpeed Audio File crc error: %d should be %d",crc16, g_set_overspeed_crc16);
        }
        cmd_notify_V2(NOTIFY_SETOVERSPEEDAUDIO_FAILED, 0, 0);
    }
    else
    {
        LOG_WARNING("[device] Http get OverSpeed Audio pack failed, errorcode:%d", result);
        device_rspErr(&device_overspeed_header, ERR_OPERATION_ERROR);
    }
}

static int get_overSpeedSetting(const void *req)
{
    cJSON *json_root = NULL;
    cJSON *json_param = NULL;
    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    json_param = cJSON_CreateObject();
    if(!json_param)
    {
        cJSON_Delete(json_root);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }
    cJSON_AddNumberToObject(json_root, "code", 0);

    cJSON_AddNumberToObject(json_param, "repeatTime", setting.settingConf.checkOverSpeedTime*1000);//转换为ms
    cJSON_AddNumberToObject(json_param, "volume", setting.settingConf.overSpeedVolume);
    cJSON_AddStringToObject(json_param, "url", (char *)setting.settingConf.overSpeedUrl);
    cJSON_AddNumberToObject(json_param, "crc", setting.settingConf.overSpeedCrc);

    cJSON_AddItemToObject(json_root, "param", json_param);

    return device_responseJSONData(req, json_root);
}
static int device_setOverSpeed(const void *req, cJSON *param)
{
    cJSON *url = NULL;
    cJSON *volume = NULL;
    cJSON *repeatTime = NULL;
    cJSON *crc = NULL;
    if(!param)//查询超速定制音
    {
        get_overSpeedSetting(req);
        return L_TRUE;
    }

    url = cJSON_GetObjectItem(param, "url");
    crc = cJSON_GetObjectItem(param, "crc");
    repeatTime = cJSON_GetObjectItem(param, "repeatTime");
    volume = cJSON_GetObjectItem(param, "volume");
    if(volume)
    {
        if(volume->valueint > 0)
        {
            g_set_overspeed_volume = volume->valueint;
        }
    }
    else
    {
        g_set_overspeed_volume = OVERSPEED_VOLUME_DEFAULT;
    }

    if(crc)
    {
        g_set_overspeed_crc16 = crc->valueint;
    }
    else
    {
        g_set_overspeed_crc16 = 0;
    }
    if(!repeatTime)//必须有
    {
        return device_rspErr(req, ERR_PARAM_MISSING);
    }
    else
    {
        if(repeatTime->valueint > 0)
        {
            g_set_overspeed_period = repeatTime->valueint/1000;//秒级
        }
    }
    if(url && strlen(url->valuestring))
    {
        if(0 == http_get((u8 *)url->valuestring, set_overspeed_cb))
        {
            memset(g_set_url, 0, MAX_URL_LEN);
            memcpy(g_set_url, url->valuestring, strlen((const char *)url->valuestring));
            device_overspeed_header.cmd = ((MSG_HEADER *)req)->cmd;
            device_overspeed_header.seq = ((MSG_HEADER *)req)->seq;
            device_overspeed_header.signature = ((MSG_HEADER *)req)->signature;
            return 0;
        }
        else
        {
            return device_rspErr(req, ERR_HTTP_IS_PROCING);
        }
    }

    return device_rspErr(req, ERR_PARAM_INVALID);
}

void device_setBreathLedRsp(const void *req)
{
    cJSON *json_root = NULL;
    cJSON *param = NULL;
    cJSON *repeat = NULL;
    cJSON *trigger = NULL;
    uint16_t hour,minute;
    char tmp[6] = {0};

    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }
    param = cJSON_CreateObject();
    if(!param)
    {
        cJSON_Delete(json_root);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }
    repeat = cJSON_CreateObject();
    if(!repeat)
    {
        cJSON_Delete(json_root);
        cJSON_Delete(param);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }
    trigger = cJSON_CreateObject();
    if(!trigger)
    {
        cJSON_Delete(json_root);
        cJSON_Delete(param);
        cJSON_Delete(repeat);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return L_FALSE;
    }

    hour = setting.settingConf.ledConfig.startTime / 3600;
    minute = (setting.settingConf.ledConfig.startTime - (hour * 3600)) / 60;
    snprintf(tmp, 6,"%d:%02d",hour, minute);
    cJSON_AddNumberToObject(repeat, "isOn", setting.settingConf.ledConfig.isOn);
    cJSON_AddNumberToObject(repeat, "ledType", setting.settingConf.ledConfig.repeatLedType);
    cJSON_AddStringToObject(repeat, "startTime", tmp);
    memset(tmp, 0, 6);
    hour = setting.settingConf.ledConfig.endTime / 3600;
    minute = (setting.settingConf.ledConfig.endTime - (hour * 3600)) / 60;
    snprintf(tmp, 6,"%d:%02d",hour, minute);
    cJSON_AddStringToObject(repeat, "endTime", tmp);
    cJSON_AddNumberToObject(repeat, "mode", setting.settingConf.ledConfig.repeatMode);

    cJSON_AddNumberToObject(trigger, "ledType", setting.settingConf.ledConfig.triggerLedType);
    cJSON_AddNumberToObject(trigger, "durationTime", setting.settingConf.ledConfig.durationTime);
    cJSON_AddNumberToObject(trigger, "remainTime", setting.settingConf.ledConfig.remainTime);
    cJSON_AddNumberToObject(trigger, "mode", setting.settingConf.ledConfig.triggerMode);

    cJSON_AddNumberToObject(json_root, "code", 0);

    cJSON_AddItemToObject(param, "trigger", trigger);
    cJSON_AddItemToObject(param, "repeat", repeat);

    cJSON_AddItemToObject(json_root, "result", param);
    return device_responseJSONData(req, json_root);
}

static int device_setBreathLed(const void *req, cJSON *param)
{
    cJSON *repeat = NULL;
    cJSON *trigger = NULL;
    cJSON *isOn = NULL;
    cJSON *ledType = NULL;
    cJSON *startTime = NULL;
    cJSON *endTime = NULL;
    cJSON *durationTime = NULL;
    cJSON *mode = NULL;
    u32 hour = 0,minute = 0;
    //目前只有MX5D2 MX5D4三个设备硬件上支持闪灯
    if((setting_getVerisonType() != VERSION_TYPE_MX5D2) && (setting_getVerisonType() != VERSION_TYPE_MX5D4))
    {
        return device_rspErr(req, ERR_CMD_NOT_SUPPORTED);
    }

    if(!param)
    {
        device_setBreathLedRsp(req);
        return L_TRUE;
    }

    trigger = cJSON_GetObjectItem(param, "trigger");
    if(trigger)
    {
        ledType = cJSON_GetObjectItem(trigger, "ledType");
        durationTime = cJSON_GetObjectItem(trigger, "durationTime");
        mode = cJSON_GetObjectItem(trigger, "mode");

        if(!ledType || !durationTime || !mode)
        {
            return device_rspErr(req, ERR_PARAM_MISSING);
        }
        setting.settingConf.ledConfig.triggerLedType = ledType->valueint;
        setting.settingConf.ledConfig.durationTime = durationTime->valueint;
        setting.settingConf.ledConfig.remainTime = durationTime->valueint;
        setting.settingConf.ledConfig.triggerMode = mode->valueint;
        setting.settingConf.ledConfig.isTrigger = 1;
    }

    repeat = cJSON_GetObjectItem(param, "repeat");
    if(repeat)
    {
        isOn = cJSON_GetObjectItem(repeat, "isOn");
        ledType = cJSON_GetObjectItem(repeat, "ledType");
        startTime = cJSON_GetObjectItem(repeat, "startTime");
        endTime = cJSON_GetObjectItem(repeat, "endTime");
        mode = cJSON_GetObjectItem(repeat, "mode");

        if(!isOn || !ledType || !startTime || !endTime || !mode)
        {
            return device_rspErr(req, ERR_PARAM_MISSING);
        }
        setting.settingConf.ledConfig.isOn = isOn->valueint;
        setting.settingConf.ledConfig.repeatLedType = ledType->valueint;
        int count = sscanf(startTime->valuestring, "%d:%d", &hour, &minute);//转换为当天秒
        if(count != 2)
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }
        setting.settingConf.ledConfig.startTime = hour*3600 + minute*60;
        count = 0;
        count = sscanf(endTime->valuestring, "%d:%d", &hour, &minute);
        if(count != 2)
        {
            return device_rspErr(req, ERR_PARAM_INVALID);
        }
        setting.settingConf.ledConfig.endTime = hour*3600 + minute*60;
        setting.settingConf.ledConfig.repeatMode = mode->valueint;
        setting.settingConf.ledConfig.isRepeat = 1;
    }
    settingConf_save();
    device_setBreathLedRsp(req);
    return L_TRUE;
}

static int device_setHardConfig(const void *req, cJSON *param)
{
    cJSON *item = NULL;
    cJSON *result = NULL;
    cJSON *json_root = NULL;
    u8 sendDebug = L_FALSE;
    s8 helmetType = -1;
    s8 saddleType = -1;
    s8 backWheelType = -1;
    s8 lightCtrlType = -1;
    s8 ccuType = -1;
    s8 bmsType = -1;
    s8 batteryType = -1;
    u8 isChanged = L_FALSE;
    float etcSpeedRatio = -1.0;
    float etcHallRatio = -1.0;
    s32 etcSpeedSource = -1;
    u8 isEtcOverspeedBit = L_TRUE; //默认使用控制器超速故障位
    u8 isBackLogOn = L_FALSE;
    u8 logLevel = LOG_LEVEL_INFO;
    if(param == NULL)
    {
        device_rspErr(req, ERR_PARAM_MISSING);
        return 0;
    }

    item = cJSON_GetObjectItem(param, "token");
    if(item)
    {
        if(strcmp((const char *)item->valuestring, "XiaoAnDebug") == 0)
        {
            sendDebug = L_TRUE;
        }
    }

    item = cJSON_GetObjectItem(param, "helmetType");
    if(item)
    {
        if(item->valueint >= TYPE_NOHELMET && item->valueint < TYPE_HELMET_MAX)
        {
            helmetType = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "saddleType");
    if(item)
    {
        if(item->valueint >= TYPE_EMAGNETICSADDLE && item->valueint < TYPE_SADDLE_MAX)
        {
            saddleType = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "wheelLockType");
    if(item)
    {
        if(item->valueint >= TYPE_NOBACKWHEEL && item->valueint < TYPE_BACKWHEEL_MAX)
        {
            backWheelType = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "ctrlLightType");
    if(item)
    {
        if(item->valueint >= TYPE_NOHEADLIGHT && item->valueint < TYPE_LIGHT_MAX)
        {
            lightCtrlType = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "etcType");
    if(item)
    {
        if(item->valueint >= TYPE_NOCCU && item->valueint < TYPE_CCU_MAX)
        {
            ccuType = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "bmsType");
    if(item)
    {
        if(item->valueint >= TYPE_NOBMS && item->valueint < TYPE_BMS_MAX)
        {
            bmsType = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "batteryType");
    if(item)
    {
        if(item->valueint >= TYPE_BATTERY12V && item->valueint <= TYPE_BATTERY72V)
        {
            batteryType = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "etcSpeedSource");
    if(item)
    {
        if (item->valueint >= ETC_NO_SPEED_OR_HALL && item->valueint <= ETC_ONLT_USE_HALL)
        {
            etcSpeedSource = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "etcSpeedRatio");
    if (item)
    {
        if (item->valuedouble > 0)
        {
            etcSpeedRatio = item->valuedouble;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "etcHallRatio");
    if (item)
    {
        if (item->valuedouble > 0)
        {
            etcHallRatio = item->valuedouble;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "isEtcOverspeedBit");
    if(item)
    {
        if(item->type == cJSON_Number && (item->valueint == 0 || item->valueint == 1))
        {
            isEtcOverspeedBit = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "isBackLogOn");
    if(item)
    {
        if(item->type == cJSON_Number && (item->valueint == 0 || item->valueint == 1))
        {
            isBackLogOn = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }
    item = cJSON_GetObjectItem(param, "logLevel");
    if(item)
    {
        if(item->type == cJSON_Number && item->valueint >= LOG_LEVEL_NULL && item->valueint <= LOG_LEVEL_DEBUG)
        {
            logLevel = item->valueint;
        }
        else
        {
            device_rspErr(req, ERR_RANGE_TOO_LARGE);
            return 0;
        }
    }

    if(helmetType != -1)
    {
        setting.defaultConf.helmetType = helmetType;
        isChanged = L_TRUE;
    }
    if(saddleType != -1)
    {
        setting.defaultConf.saddleType = saddleType;
        isChanged = L_TRUE;
    }
    if(backWheelType != -1)
    {
        setting.defaultConf.backWheelType = backWheelType;
        isChanged = L_TRUE;
    }
    if(lightCtrlType != -1)
    {
        setting.defaultConf.lightCtrlType = lightCtrlType;
        isChanged = L_TRUE;
    }
    if(ccuType != -1)
    {
        setting.defaultConf.ccuType = ccuType;
        isChanged = L_TRUE;
    }
    if(bmsType != -1)
    {
        setting.defaultConf.bmsType = bmsType;
        isChanged = L_TRUE;
    }
    if(batteryType != -1)
    {
        setting.defaultConf.batteryType = batteryType;
        isChanged = L_TRUE;
    }
    if (etcSpeedSource != -1)
    {
        setting.settingConf.etcSpeedSource = etcSpeedSource;
        isChanged = L_TRUE;
    }
    if (etcSpeedRatio > 0)
    {
        setting.settingConf.etcSpeedRatio = etcSpeedRatio;
        isChanged = L_TRUE;
    }
    if (etcHallRatio > 0)
    {
        setting.settingConf.etcHallRatio = etcHallRatio;
        isChanged = L_TRUE;
    }
    if (isEtcOverspeedBit != setting.settingConf.isEtcOverspeedBit)
    {
        setting.settingConf.isEtcOverspeedBit = isEtcOverspeedBit;
        isChanged = L_TRUE;
    }
    if (isBackLogOn != setting.settingConf.isBackLogOn)
    {
        setting.settingConf.isBackLogOn = isBackLogOn;
        isChanged = L_TRUE;
    }
    if (logLevel != setting.settingConf.loglevel)
    {
        setting.settingConf.loglevel = logLevel;
        isChanged = L_TRUE;
    }

    if(isChanged == L_TRUE)
    {
        defaultConf_save();
        settingConf_save();
    }

    result = cJSON_CreateObject();
    if(!result)
    {
        return device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
    }
    json_root = cJSON_CreateObject();
    if(!json_root)
    {
        cJSON_Delete(result);
        return device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
    }
    cJSON_AddNumberToObject(json_root, "code", 0);

    cJSON_AddNumberToObject(result, "helmetType", setting.defaultConf.helmetType);
    cJSON_AddNumberToObject(result, "saddleType", setting.defaultConf.saddleType);
    cJSON_AddNumberToObject(result, "wheelLockType", setting.defaultConf.backWheelType);
    cJSON_AddNumberToObject(result, "ctrlLightType", setting.defaultConf.lightCtrlType);
    cJSON_AddNumberToObject(result, "etcType", setting.defaultConf.ccuType);
    cJSON_AddNumberToObject(result, "bmsType", setting.defaultConf.bmsType);
    cJSON_AddNumberToObject(result, "batteryType", setting.defaultConf.batteryType);
    cJSON_AddNumberToObject(result, "etcSpeedSource", setting.settingConf.etcSpeedSource);
    cJSON_AddNumberToObject(result, "etcSpeedRatio", setting.settingConf.etcSpeedRatio);
    cJSON_AddNumberToObject(result, "etcHallRatio", setting.settingConf.etcHallRatio);
    cJSON_AddNumberToObject(result, "isEtcOverspeedBit", setting.settingConf.isEtcOverspeedBit);
    if(sendDebug)
    {
        cJSON_AddNumberToObject(result, "isBackLogOn", setting.settingConf.isBackLogOn);
        cJSON_AddNumberToObject(result, "logLevel", setting.settingConf.loglevel);
    }

    cJSON_AddItemToObject(json_root, "result", result);
    return device_responseJSONData(req, json_root);
}

static DEVICE_MSG_PROC deviceProcs[] =
{
    {DEVICE_SET_DEFENDSTATE,        device_SetDeffend},
    {DEVICE_GET_DEFENDSTATE,        device_GetDeffend},
    {DEVICE_PLAY_AUDIO,             device_playAudio},
    {DEVICE_SET_SERVER,             device_SetServer},
    {DEVICE_GET_SERVER,             device_GetServer},
    {DEVICE_REBOOT,                 device_reboot},
    {DEVICE_BACKSEAT_UNLOCK,        device_backseat_unlock},
    {DEVICE_BACKWHEEL,              device_BackWheel},
    {DEVICE_SET_AUDIO,              device_set_audio},
    {DEVICE_GET_PARAMS,             device_getInnerParam},
    {DEVICE_SET_PARAMS,             device_setInnerParam},
    {DEVICE_ACC,                    device_acc},
    {DEVICE_STATUS,                 device_status},
    {DEVICE_UPGRADE,                device_upgrade},
    {DEVICE_GET_CUSTOM_AUDIO,       device_getCustomAudio},
    {DEVICE_POWER_DOWN,             device_PownDown},
    {DEVICE_SET_SADDLE,             device_setSaddle},
    {DEVICE_SET_BLETOKEN,           device_setBLE},
    {DEVICE_GET_STATE,              device_getState},
    {DEVICE_GET_NMEA_STR,           device_getNMEA_str},
    {DEVICE_SET_AUDIO_IN_ONE,       device_setAudioInOne},
    {DEVICE_SET_LOCKCAR_FORCE,      device_setLockCarForce},
    {DEVICE_GET_ETC_INFO,           device_getETCInfo},
    {DEVICE_SET_ETCSPEED,           device_setETCSpeed},
    {DEVICE_SET_ETCPROTECTVOLTAGE,  device_setETCProtectVoltage},
    {DEVICE_SET_ETCLIMITCURRENT,    device_setETCLimitCurrent},
    {DEVICE_SET_ETCSLOWSTART,       device_setETCSlowStart},
    {DEVICE_SET_ETCLIGHT,           device_setETCLight},
    {DEVICE_GET_LBS,                device_getLBS},
    {DEVICE_GET_CELLINFO,           device_getCellInfo},
    {DEVICE_CHANGE_CONFIG,          device_changeConfig},
    {DEVICE_UPGRADE_FENCE,          device_upgradeFence},
    {DEVICE_GET_BMS_TIMING_INFO,    device_getBMSTimingInfo},
    {DEVICE_GET_BMS_FIXED_INFO,     device_getBMSFixedInfo},
    {DEVICE_HELMET,                 device_Helmet},
    {DEVICE_GET_NEARTBEACONINFO,    device_getNearTBeaconInfo},
    {DEVICE_ETC_UPGRADE,            device_ETC_upgrade},
    {DEVICE_BMS_UPGRADE,            device_BMS_upgrade},
    {DEVICE_FOTA,                   device_FOTA},
    {DEVICE_GET_WIFILOCAL,          device_wificoord},
    {DEVICE_DT_OVERSPPED,           device_setOverSpeed},
    {DEVICE_SET_BREATHLED,          device_setBreathLed},
    {DEVICE_SET_HARD_CONFIG,        device_setHardConfig},
};

int device_initail(void)
{
    int i = 0;
    int num = sizeof(deviceProcs) / sizeof(deviceProcs[0]);
    for(; i < num; i++)
    {
        device_msg_regist(deviceProcs[i].cmd, deviceProcs[i].pfn);
    }
    return 0;
}

