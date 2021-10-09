#ifndef __AUDIO_DRIVER_H__
#define __AUDIO_DRIVER_H__

#include "types.h"

#define AUDIO_HELMET_LOCK            252  //头盔已归还 (中控默认语音)
#define AUDIO_DIAG_SPK               253
#define AUDIO_DIAG_SUCCESS           254
#define AUDIO_DIAG_FAIL              255

#define OVERSPEED_VOLUME_DEFAULT  70//默认音量

enum AUDIO_TYPE
{
    AUDIO_BEEP                      = 0,
    AUDIO_STARTUP                   = 0,    //默认 设备启动
    AUDIO_DEFEND_ON                 = 1,    //默认 车辆设防提示音
    AUDIO_DEFEND_OFF                = 2,    //默认 车辆撤防提示音
    AUDIO_ACC_ON                    = 3,    //默认 车辆启动提示音
    AUDIO_ACC_OFF                   = 4,    //共享默认 车辆关闭提示音 车厂版本
    AUDIO_SEEK                      = 5,    //共享默认 找车提示音 车厂版本
    AUDIO_ALARM                     = 6,    //共享默认 车辆告警提示音
    ALARM_NEAR_BOUNDARY             = 7,    //共享默认 临时锁车
    ALARM_OUT_BOUNDARY              = 8,    //共享默认 车辆已驶出服务区
    AUDIO_WHO_AM_I                  = 9,    //共享默认 我在这里
    ALARM_NEAR_PROHIBITED_AREA      = 10,   //共享默认 临近禁行区
    ALARM_INTO_PROHIBITED_AREA      = 11,   //共享默认 进入禁行区语音
    ALARM_IN_PROHIBITED_AREA        = 12,   //共享默认 在禁停区语音
    AUDIO_RESERVE                   = 13,
    AUDIO_RESERVE0                  = 14,
    AUDIO_OVER_SPEED                = 15,   //超速打嘀(包括超速定制音)
    AUDIO_CAR_REPAIR                = 16,   //车辆报修
    AUDIO_BATTERY_LOW               = 17,   //电量过低
    AUDIO_CAR_USED                  = 18,   //车辆已使用
    AUDIO_IN_WARNING_AREA           = 19,   //临近服务区边界，请尽快骑回
    AUDIO_OVER_STOP_AREA            = 21,   //MX3L定制，不在停车区，请到停车区还车
    AUDIO_KICKOK                    = 24,
    AUDIO_KICKERROR                 = 25,
    AUDIO_KICKFAILED                = 26,
    AUDIO_RFIDBEEP                  = 27,   //标签进入RFID读卡器识别区提示音
    AUDIO_RESERVE6                  = 28,
    AUDIO_RESERVE7                  = 29,
    AUDIO_RESERVE8                  = 30,
    AUDIO_RESERVE9                  = 31,
    AUDIO_LEARN433OK                = 32,   //钥匙绑定成功
    AUDIO_TURNOVER                  = 33,   //倾倒告警语音
    AUDIO_SHAKE_ALARM               = 34,   //MX3H定制，车辆未解锁，请扫码骑行
    AUDIO_CAOZUOSHIBAI              = 35,   //开关电门及设置设防失败提示音

    AUDIO_MAX_NUMBER,
};

typedef struct
{
    unsigned int index;
    const void *dat;
    unsigned int len;
} AudioDef_st;

void audio_play_finish(void);
uint8_t audio_isAudioplaying(void);

int audio_deleteCustomAudio(int index);
int audio_deleteDefaultAudio(int index);
int audio_deleteBakAudio(int index);

void audio_factoryAll(void);
void audio_factoryDt(void);
void audio_initailDriver(void);
int audio_initialAudios(AudioDef_st *pAudios, int num);
void audio_initialIsNightVoiceOn(uint8_t *p_isNightVoiceOn);

int audio_play(u8 audio_index);
int audio_playWithVolume(int audio_index, int volume);
void audio_BeepOverSpeedwithRatio(void);
void audio_factoryDt_withoutOverspeed(void);
int audio_getAudioCrc(char *filename);
int audio_getCustomAudioCrc(int audio_index);

int audio_saveAudio(uint8_t *data, int data_len, uint8_t audio_index, uint8_t isCustomed);
int audio_saveBakAudio(uint8_t *data, int data_len, uint8_t audio_index);
L_BOOL audio_sepreateData(uint8_t *data, int data_len, uint8_t *idx);
L_BOOL audio_enqueueAudio(int audio_index);
L_BOOL audio_dequeueAudio(int *audio_index);

int audio_renameBak2Custom(void);

#endif //__AUDIO_DRIVER_H__

