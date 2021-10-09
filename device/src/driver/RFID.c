#include <stdio.h>
#include "log.h"
#include "msg.h"
#include "data.h"
#include "user_timer.h"
#include "string.h"
#include "version.h"
#include "da14580.h"
#include "request.h"
#include "RFID.h"
#include "car.h"
#include "audio_driver.h"

static u8 getCardID[]    = {0xff,0x02,0x00,0x00,0x25,0xC3}; //读卡
static u8 setReboot[]    = {0xff,0x02,0x02,0x00,0x43,0xA1}; //重启设备
static u8 getVersion[]   = {0xff,0x02,0x04,0x00,0xe9,0x07}; //获取版本号

static void RFID_toupper(u8 *str, u8 len)
{
    for(int i = 0; i < len; i++)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] -= 32;
        }
    }
}

int RFID_getCardIDRsp(DA14580_RFID485_MSG *msg)
{
    data_getData()->isRFIDConnect = L_TRUE; //收到回复认为设备已连接
    data_getData()->faultRecord.rfidSendNoRspTimes = 0;
    data_getData()->faultRecord.isRFIDRsp = L_TRUE; //收到RFID回复，发送通讯恢复告警
    
    if(msg->len == 2) //不合法的长度,协议对应错误码，读卡器返回-1表示标签未获取，返回-2为其他错误
    {
        data_getData()->isCardIdLegal = L_FALSE;
        if(0xFF == msg->data[0] && 0xFF == msg->data[1]) // 错误码-1，未获取到标签，上报0000000000000000到服务器
        {
            u8* str = "0000000000000000";
            memset(data_getData()->cardID, 0, 17);
            memcpy(data_getData()->cardID, str, strlen(str));
            data_getData()->cardIDlen = strlen(str);
        }
        else
        {
            data_getData()->RFID_ErrorCode = -2; //错误码-2，上报-2到服务器
            data_getData()->cardIDlen = 2;
        }
    }
    else if(msg->len == 16)
    {
        data_getData()->isCardIdLegal = L_TRUE;
        RFID_toupper(msg->data, msg->len);
        memcpy(data_getData()->cardID, msg->data, msg->len);
        data_getData()->cardIDlen = msg->len;
    }

    if(0 != memcmp(data_getData()->cardID, "\0\0\0\0\0\0", 6))
    {
        LOG_DEBUG("---------------->>>> cardID : %s", data_getData()->cardID);
    }
    return 0;
}

static int RFID_rebootRsp(DA14580_RFID485_MSG *msg)
{
    LOG_DEBUG("> reboot module success");
    return 0;
}

int RFID_versionRsp(DA14580_RFID485_MSG *msg)
{
    u32 version = 0;
    u8 tempStr[12] = {0};
    
    data_getData()->isRFIDConnect = L_TRUE; //收到回复认为设备已连接
    data_getData()->faultRecord.rfidSendNoRspTimes = 0;
    data_getData()->faultRecord.isRFIDRsp = L_TRUE; //收到RFID回复，发送通讯恢复告警

    if(msg->len != 3)
    {
        LOG_ERROR("Length error");
        return -1;
    }
    memset(data_getData()->RFIDVersion,0,12);
    sprintf(tempStr,"%d.%d.%d", msg->data[0], msg->data[1], msg->data[2]);
    memcpy(data_getData()->RFIDVersion, tempStr, 12);
    LOG_DEBUG("---------->>>>>>> RFIDVersion : %s", data_getData()->RFIDVersion);
    return 0;
}

static u8 isNeedOpen485port = L_FALSE; //默认不需要打开RFID的485使能引脚
static int RFID_close(void)
{
    if(isNeedOpen485port) //MX5F6(RF)类型产品发送完RFID指令就拉低485使能引脚
    {
        car_close_RFID485(); //关闭RFID485使能引脚，才能接受RFID回复
    }
}

int RFID_getCardID(void)
{
    if(isNeedOpen485port) //MX5F6(RF)类型产品发送RFID指令时先拉高485使能
    {
        car_open_RFID485(); //打开RFID485使能引脚，才能发送指令到RFID
    }
    
    da14580_sendUartData(getCardID, sizeof(getCardID));

    if(isNeedOpen485port) //MX5F6(RF)类型产品发送RFID指令时先拉高485使能
    {
        timer_start(TIMER_RFID485_DELAY, TIMER_MS, 10, RFID_close);
    }
    
    return 0;
}

int RFID_setDeviceReboot(void)
{
    if(isNeedOpen485port) //MX5F6(RF)类型产品发送RFID指令时先拉高485使能
    {
        car_open_RFID485(); //打开RFID485使能引脚，才能发送指令到RFID
    }
    
    da14580_sendUartData(setReboot, sizeof(setReboot));
    
    if(isNeedOpen485port) //MX5F6(RF)类型产品发送RFID指令时先拉高485使能
    {
        timer_start(TIMER_RFID485_DELAY, TIMER_MS, 10, RFID_close);
    }

    return 0;
}

int RFID_getDeviceVersion(void)
{
    if(isNeedOpen485port) //MX5F6(RF)类型产品发送RFID指令时先拉高485使能
    {
        car_open_RFID485(); //打开RFID485使能引脚，才能发送指令到RFID
    }
    
    da14580_sendUartData(getVersion, sizeof(getVersion));
    
    if(isNeedOpen485port) //MX5F6(RF)类型产品发送RFID指令时先拉高485使能
    {
        timer_start(TIMER_RFID485_DELAY, TIMER_MS, 10, RFID_close);
    }

    return 0;
}

L_BOOL async_isRFIDCheckSumPass(uint8_t *data)
{
    u16 crc16 = 0;
    DA14580_RFID485_MSG *msg = (DA14580_RFID485_MSG *)data;
    if(data[0] != 0XFF || data[1] != 0X02)
    {
        LOG_ERROR("rfid signature error");
        return L_FALSE;
    }

    crc16 = (msg->data[msg->len] << 8 | msg->data[msg->len + 1]);
    if(crc16 != crc16_ccitt((const char *)msg, msg->len + sizeof(DA14580_RFID485_MSG)))
    {
        LOG_ERROR("checksum error %d, except: %x", crc16, crc16_ccitt((const char *)msg, msg->len + sizeof(DA14580_RFID485_MSG)));
        return L_FALSE;
    }

    return L_TRUE;
}

static L_BOOL RFID_isRFIDCheckSumPass(DA14580_RFID485_MSG *msg, u16 msgLen)
{
    u16 crc16 = 0;
    if(0xFF02 != _ntohs(msg->signature))
    {
        return L_FALSE;
    }

    crc16 = (msg->data[msg->len] << 8 | msg->data[msg->len + 1]);
    if(crc16 != crc16_ccitt((const char *)msg, msgLen - 2))
    {
        return L_FALSE;
    }

    return L_TRUE;
}

static int RFID_procOneMsg(u8 *data, u8 dataLen)
{
     etcMsg_MsgProc(data, dataLen);
     return 0;
}

L_BOOL RFID_FilterFrame(u8 * data, u16 length)
{
    u8 vaild = 0;
	u8 proctimes = 0;
    s16 leftlen = length;
    DA14580_RFID485_MSG *msg = (DA14580_RFID485_MSG *)data;

    while(leftlen >= DA14580_RFID485_MSG_LEN)
    {
        if(START_FLAG != _ntohs(msg->signature))
        {
            if(length < DA14580_RFID485_MSG_LEN) //串口接收到异常数据
            {
                return -1;       
            }

            if(!RFID_isRFIDCheckSumPass((DA14580_RFID485_MSG *)msg, leftlen))
            {
                break;
            }
        }

        vaild = 1;
        RFID_procOneMsg((u8 *)msg, msg->len + MSG_HEADER_485_LEN + 1);
        leftlen = leftlen - (msg->len + MSG_HEADER_485_LEN + 1);
        msg = (DA14580_RFID485_MSG *)(data + length - leftlen);
		if(++proctimes > 10)
		{
			LOG_ERROR("[RFID] procOneMsg break");
			return L_FALSE;
		}
    }
    if(vaild == 1)
    {
        return L_TRUE;
    }
    return L_FALSE;
}

#define RFID_REPEAT_TIMES 5

static L_BOOL RFID_shakeFilter(void)
{
    //没有轮动和震动的情况下RFID感应做10ms防抖过滤
    if(!data_getData()->isShaking && !data_getData()->isMoving && data_getData()->isCardIdLegal)
    {
        fibo_taskSleep(10);
    }

    if(data_getData()->isCardIdLegal)
    {
        return L_TRUE;
    }
    else
    {
        return L_FALSE;
    }
}

static RFID_CARD_STATE RFID_checkIdentificationArea(void)
{
    return (data_getData()->isCardIdLegal ? IN_IDENTIFICATION_AREA : OUT_IDENTIFICATION_AREA);
}

int RFID_StateHandle(void)
{
    static RFID_STATE state = RFID_SHAKE_FILTER;
    static u32 audio_times = 0;
    int audio_idx = 0;
    static u32 isAudioPlayOverTime = L_FALSE;
    static u32 RFIDAudioTime = 0;
    static RFID_CARD_STATE lastRFIDCardState = OUT_IDENTIFICATION_AREA;
    RFID_CARD_STATE curRFIDCardState = RFID_checkIdentificationArea();
    
    switch(state)
    {
        case RFID_SHAKE_FILTER:
        {
            if(data_getData()->isCardIdLegal && (car_isAccOn() || data_getData()->isRFIDPowerOn))
            {
                if(RFID_shakeFilter())
                {
                    state = RFID_WHEELSPINNING_CHECK;
                }
                else
                {
                    state = RFID_SHAKE_FILTER;
                    break;
                }
            }
            else
            {
                state = RFID_FLAGRESET_HANDLE;
            }
            break;
        }
        case RFID_WHEELSPINNING_CHECK:
        {
            //如果首次开电门，并且发生了2秒轮动，则开始播放RFID提示音
            if(data_getData()->isWheelSpinConti)
            {
                state = RFID_AUDIO_HANDLE;
            }
            else
            {
                state = RFID_FLAGRESET_HANDLE;
            }
            break;
        }
        case RFID_AUDIO_HANDLE:
        {
            if(isAudioPlayOverTime == L_TRUE)
            {
                state = RFID_FLAGRESET_HANDLE;
                break;
            }
            
            if(audio_isAudioplaying())
            {
                state = RFID_FLAGRESET_HANDLE;
            }
            else
            {
                audio_enqueueAudio(AUDIO_RFIDBEEP); //将RFID响应提示音放入队列中，保证提示音均匀播放
                
                //读卡器感应到标签，提示音播放超过20秒后，停止播放语音
                if(RFIDAudioTime++ >= RFID_AUDIO_MAX_TIME) //15次约为20秒
                {
                    RFIDAudioTime = 0;
                    isAudioPlayOverTime = L_TRUE;
                }
                state = RFID_FLAGRESET_HANDLE;
            }
            break;
        }
        case RFID_FLAGRESET_HANDLE:
        {
            //以下三类情况需要对相应状态量进行复位操作
            //1.标签不在读卡器识别区；2.设备处于电门关或断大电的情况；3.读卡器异常无响应时
            if((RFID_checkIdentificationArea() == OUT_IDENTIFICATION_AREA)
            || ((!car_isAccOn() && !data_getData()->isRFIDPowerOn) || !car_isPowerExistence())
            || (data_getData()->faultRecord.isRFIDRsp == L_FALSE))
            {
                data_getData()->isCardIdLegal = L_FALSE;
                isAudioPlayOverTime = L_FALSE;
                RFIDAudioTime = 0;
                
                //在设备处于关电门或者断大电的情况下
                if((!car_isAccOn() && !data_getData()->isRFIDPowerOn) || !car_isPowerExistence())
                {
                    memset(data_getData()->cardID, 0, 17);
                    memset(data_getData()->RFIDVersion, 0, 12);
                    data_getData()->cardIDlen = 0;
                }
                else if((car_isAccOn() || data_getData()->isRFIDPowerOn)) //供电情况下，考虑RFID是否连接
                {
                    //4秒未收到RFID回复认为RFID设备未连接
                    if(data_getData()->faultRecord.isRFIDRsp == L_FALSE)
                    {
                        memset(data_getData()->cardID, 0, 17);
                        memset(data_getData()->RFIDVersion, 0, 12);
                        data_getData()->isRFIDConnect = L_FALSE;
                        data_getData()->RFID_ErrorCode = -1; //RFID读卡器未连接，上报-1到服务器
                        data_getData()->cardIDlen = 2;
                    }
                }
            }

            state = RFID_SHAKE_FILTER; //一次扫描过程结束，回到第一步判断
            break;
        }
        default:
            break;
    }
    
    if(lastRFIDCardState == OUT_IDENTIFICATION_AREA && curRFIDCardState == IN_IDENTIFICATION_AREA && data_getData()->isWheelSpinConti && !data_getData()->isRFIDPowerOn)
    {
        audio_play(AUDIO_RFIDBEEP); //首次感应到RFID标签立即播放语音
    }
    else
    {
        //每秒钟判断一次RFID语音队列是否为空，如果当前扫描到标签并且队列不为空，则进行提示音播放
        if(audio_times++ % (1000 / RFID_STATE_TIMER_PERIOD) == 0)
        {
            audio_times = 0;
            if(audio_dequeueAudio(&audio_idx) && data_getData()->isCardIdLegal)
            {
                audio_play(audio_idx);
            }
        }
    }
    
    lastRFIDCardState = curRFIDCardState;
    return 0;
}
