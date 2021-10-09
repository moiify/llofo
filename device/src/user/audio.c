/* Copyright (C) Xiaoan Technology Co., Ltd - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Tom Chiang <jiangtao@xiaoantech.com>, Feb 2017
 *
 * audio.c
 *
 * 语音模块
 */
#include <fibo_opencpu.h>

#include "audio.h"
#include "setting.h"
#include "audio_driver.h"

#if defined(APP_RELEASE) //升级包需包括固件包中没有的新增语音
    #include "audio/audio_WoDieDaoLe"
    #include "audio/audio_CaoZuoShiBai"
    #include "audio/audio_TouKuiYiGuiHuan"
    
#else
    #include "audio/audio_Beep"
    #include "audio/audio_KaiSuoChengGong"

    #if defined(BM5)
        #include "audio/audio_BaiMiHuanYingShiYongDianDanChe"
        #include "audio/audio_QingXianSaoMaZaiKaiSuo"
        #include "audio/audio_BaiMiCheLiangYiShiChuFuWuQu"
        #include "audio/audio_BaiMiAlarm"
        #include "audio/audio_ZhuRenZhuRen"
        #include "audio/audio_YuTianLuHua"
        #include "audio/audio_YuXueTianQi"
        #include "audio/audio_YeWanJiaShi"
        #include "audio/audio_TouCheTouChe"
        #include "audio/audio_TouDianPingTouDianPing"
        #include "audio/audio_BaiMiKaiSuoChengGong"
    #else
        #include "audio/audio_CheLiangYiShiChuFuWuQu"
        #include "audio/audio_HuanYingShiYongDianDanChe"
        #include "audio/audio_KaiShiQiDong"
        #include "audio/audio_SuoCheChengGong"
        #include "audio/audio_LinJinFuWuQu"
        #include "audio/audio_WoZaiZheLi"
        #include "audio/audio_YiDongGaoJin"
        #include "audio/audio_LinShiSuoCheChengGong"
        #include "audio/audio_CheLiangYiBaoXiu"
        #include "audio/audio_DianLiangGuoDi"
        #include "audio/audio_CheLiangYiBeiShiYong"
        #include "audio/audio_LinJinFuWuQuBianJieQingJinKuaiQiHui"
        #include "audio/audio_WoDieDaoLe"
    #endif

    #include "audio/audio_RFIDTiShiYin"
    #include "audio/audio_CaoZuoShiBai"
    #include "audio/audio_TouKuiYiGuiHuan"
    #include "audio/audio_LaBaJianCe"
    #include "audio/audio_DiagnosisSuccess"
    #include "audio/audio_DiagnosisFailed"
#endif

//数组定义顺序必须和audio_driver.h文件中的AUDIO_TYPE定义一致
static AudioDef_st audios[] = 
{
#if defined(APP_RELEASE)
    {AUDIO_TURNOVER, audio_WoDieDaoLe, sizeof(audio_WoDieDaoLe) },//我跌倒了啦
    {AUDIO_HELMET_LOCK, audio_TouKuiYiGuiHuan, sizeof(audio_TouKuiYiGuiHuan) },//头盔已归还
#else
#if defined(BM5)
            {AUDIO_DEFEND_OFF, audio_BaiMiKaiSuoChengGong, sizeof(audio_BaiMiKaiSuoChengGong)},//开锁成功
            {AUDIO_SEEK, audio_BaiMiHuanYingShiYongDianDanChe, sizeof(audio_BaiMiHuanYingShiYongDianDanChe)},//欢迎使用电单车
            {AUDIO_ALARM, audio_QingXianSaoMaZaiKaiSuo, sizeof(audio_QingXianSaoMaZaiKaiSuo)},//移动告警滴滴声
            {ALARM_OUT_BOUNDARY, audio_BaiMiCheLiangYiShiChuFuWuQu, sizeof(audio_BaiMiCheLiangYiShiChuFuWuQu)},//车辆已驶出服务区，请尽快骑回
            {AUDIO_WHO_AM_I, audio_BaiMiAlarm, sizeof(audio_BaiMiAlarm)},//语音9改为拜米报警音
            {12, audio_ZhuRenZhuRen, sizeof(audio_ZhuRenZhuRen) },//主人主人
            {16, audio_YuTianLuHua, sizeof(audio_YuTianLuHua) },//雨天路滑
            {17, audio_YuXueTianQi, sizeof(audio_YuXueTianQi) },//雨雪天气
            {18, audio_YeWanJiaShi, sizeof(audio_YeWanJiaShi) },//夜晚驾车
            {19, audio_TouCheTouChe, sizeof(audio_TouCheTouChe) },//偷车偷车
            {20, audio_TouDianPingTouDianPing, sizeof(audio_TouDianPingTouDianPing) },//偷电瓶偷电瓶
#else
            {AUDIO_DEFEND_ON, audio_SuoCheChengGong, sizeof(audio_SuoCheChengGong)},//锁车成功
            {AUDIO_DEFEND_OFF, audio_KaiSuoChengGong, sizeof(audio_KaiSuoChengGong)},//开锁成功
            {AUDIO_ACC_ON, audio_KaiShiQiDong,    sizeof(audio_KaiShiQiDong)},//开始启动
            {AUDIO_SEEK, audio_HuanYingShiYongDianDanChe, sizeof(audio_HuanYingShiYongDianDanChe)},//欢迎使用电单车
            {AUDIO_ALARM, audio_YiDongGaoJin, sizeof(audio_YiDongGaoJin) },//移动告警滴滴声
            {ALARM_NEAR_BOUNDARY, audio_LinShiSuoCheChengGong, sizeof(audio_LinShiSuoCheChengGong) },//临时锁车成功
            {ALARM_OUT_BOUNDARY, audio_CheLiangYiShiChuFuWuQu, sizeof(audio_CheLiangYiShiChuFuWuQu) },//车辆已驶出服务区，请尽快骑回
            {AUDIO_WHO_AM_I, audio_WoZaiZheLi, sizeof(audio_WoZaiZheLi) },//我在这里
            {ALARM_NEAR_PROHIBITED_AREA, audio_LinJinFuWuQu, sizeof(audio_LinJinFuWuQu) },//临近服务区,使出将断电
            {AUDIO_CAR_REPAIR, audio_CheLiangYiBaoXiu, sizeof(audio_CheLiangYiBaoXiu) },//车辆已报修请试试其他车
            {AUDIO_BATTERY_LOW, audio_DianLiangGuoDi, sizeof(audio_DianLiangGuoDi) },//电量过低请试试其他车
            {AUDIO_CAR_USED, audio_CheLiangYiBeiShiYong, sizeof(audio_CheLiangYiBeiShiYong) },//车辆已被使用请试试其他车
            {AUDIO_IN_WARNING_AREA, audio_LinJinFuWuQuBianJieQingJinKuaiQiHui, sizeof(audio_LinJinFuWuQuBianJieQingJinKuaiQiHui) },//临近服务区边界，请尽快骑回
            {AUDIO_TURNOVER, audio_WoDieDaoLe, sizeof(audio_WoDieDaoLe) },//我跌倒了啦
#endif
            {AUDIO_RFIDBEEP, audio_RFIDTiShiYin, sizeof(audio_RFIDTiShiYin) },//RFID提示音
            {AUDIO_CAOZUOSHIBAI, audio_CaoZuoShiBai, sizeof(audio_CaoZuoShiBai) },//开关电门及设置设防失败提示音
            
            {AUDIO_HELMET_LOCK, audio_TouKuiYiGuiHuan, sizeof(audio_TouKuiYiGuiHuan) },//头盔已归还
            {AUDIO_DIAG_SPK, audio_LaBaJianCe, sizeof(audio_LaBaJianCe) },//喇叭检测语音
            {AUDIO_DIAG_SUCCESS, audio_DiagnosisSuccess, sizeof(audio_DiagnosisSuccess) },//诊断成功音乐
            {AUDIO_DIAG_FAIL, audio_DiagnosisFailed, sizeof(audio_DiagnosisFailed) },//诊断失败音乐
            {AUDIO_BEEP, audio_Beep, sizeof(audio_Beep) },//滴一声Beep音
#endif
};

void audio_initail(void)
{
    audio_initailDriver();
    audio_initialIsNightVoiceOn(&setting.defaultConf.isNightVoiceOn);
    audio_initialAudios(audios, sizeof(audios) / sizeof(audios[0]));
}

void audio_RstoreDefaultAudios(void) //默认语音文件恢复
{
    for(int i = 0; i < AUDIO_MAX_NUMBER; i++)
    {
        audio_deleteDefaultAudio(i);
    }

    audio_initialAudios(audios, sizeof(audios)/sizeof(audios[0]));
    return;
}
