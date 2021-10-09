#ifndef __RFID_H__
#define __RFID_H__

#include "da14580.h"

typedef enum
{
    CMD_GET_CARDID                  = 0, //查询卡ID
    CMD_GET_CARDID_RSP              = 1, //查询卡ID应答
    CMD_SET_REBOOT                  = 2, //重启
    CMD_SET_REBOOT_RSP              = 3, //重启应答
    CMD_GET_VERSION                 = 4, //查询版本号
    CMD_GET_VERSION_RSP             = 5, //查询版本号应答
} CMD_RFID485;

typedef enum
{
    RFID_SCAN_NONE                  = 0, //未扫描到标签
    RFID_SCAN_SUCCESS               = 1, //扫描到标签
    RFID_DISCONNECT                 = 2, //RFID读卡器未连接
}RFID_WORK_STATE;

typedef enum
{
    OUT_IDENTIFICATION_AREA         = 0, //标签离开读卡器识别区
    IN_IDENTIFICATION_AREA          = 1, //标签在读卡器识别区
}RFID_CARD_STATE;

typedef enum
{
    RFID_SHAKE_FILTER               = 1, //防抖过滤检测
    RFID_WHEELSPINNING_CHECK        = 2, //是否2秒轮动判断
    RFID_AUDIO_HANDLE               = 3, //提示音播放处理
    RFID_FLAGRESET_HANDLE           = 4, //状态量复位处理
}RFID_STATE;

#define RFID_STATE_TIMER_PERIOD     20
#define RFID_AUDIO_MAX_TIME         15

int RFID_getCardID(void);
int RFID_getDeviceVersion(void);
int RFID_setDeviceReboot(void);
int RFID_getCardIDRsp(DA14580_RFID485_MSG *msg);
int RFID_versionRsp(DA14580_RFID485_MSG *msg);
L_BOOL RFID_FilterFrame(u8 * data, u16 length);
L_BOOL async_isRFIDCheckSumPass(uint8_t *data);
int RFID_StateHandle(void);

#endif
