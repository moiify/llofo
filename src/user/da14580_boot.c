
#include "fibo_opencpu.h"

#include "car.h"
#include "log.h"
#include "data.h"
#include "uart.h"
#include "hardware.h"
#include "user_timer.h"
#include "da14580_boot.h"

#include "dacode/dacode.txt"

void da14580_bootStart(void)
{
    // 重置蓝牙版本号,蓝牙启动时获取
    DATA *pData = data_getData();

    pData->ble_state.version = 0;
    pData->ble_state.isBooting = L_TRUE;
    pData->ble_state.missHeartbeatCount = 0;
    pData->ble_state.isDA14580Alive = L_FALSE;
    LOG_DEBUG("[Ble] start to reload DA14580, code len(%d)", sizeof(src_dacode));

    car_rebootDA14580();
}


static u8 step = 0;
//测试下来原本的定时器优先级很高,所以不会被串口中断打断,IIC读取失败导致内核阻塞了一会,定时器的优先级也不高,所以蓝牙芯片会发个不停
static int da14580_TransFirmware(void)
{
    uint16_t writeLen = 0;
    uint8_t result = 0x06;
    int16_t leftLen = sizeof(src_dacode);
    do
    {
        writeLen = fibo_hal_uart_put(UART_BLE, (unsigned char *)(src_dacode + (sizeof(src_dacode) - leftLen)), leftLen > 512 ? 512 : leftLen);
        leftLen -= writeLen;
	}while(leftLen > 0);

    /* 不知道为什么 多发一个字节就会成功 */
    fibo_hal_uart_put(UART_BLE, &result, 1);

    /* 第二步执行完了 等待DA14580回复crc校验 */
    LOG_DEBUG(">>>boot da14580 step 2\r\n");
    step = 2;
    return 0;
}

void da14580_bootHandler(uint8_t *data, uint16_t dataLen)
{
    if(step == 2)
    {
        uint8_t result = 0x06;

        step = 0;
        fibo_hal_uart_put(UART_BLE, &result, 1);
        LOG_DEBUG(">>>up OK");
        return;
    }

    if(data_getData()->ble_state.isBooting)
    {
        uint16_t i = 0;
        for(i = 0; i < dataLen; i++)
        {
            if(data[i] == 0x02)
            {
                break;
            }
        }

        if(i < dataLen)
        {
            data[0] = 0x02;
            data_getData()->ble_state.isBooting = L_FALSE;
            LOG_DEBUG(">>>set false");
        }
    }

    if(data[0] == 0x02 || (dataLen > 1 && data[1] == 0x02))
    {
        uint16_t writeLen = 0;
        uint8_t returnBuff[3] = {0};
        uint32_t size = sizeof(src_dacode);
        u8 writetimes = 0;

        returnBuff[0] = 0x01;
        returnBuff[1] = size & 0xff;
        returnBuff[2] = size >> 8 & 0xff;
        do
        {
            writeLen += fibo_hal_uart_put(UART_BLE, returnBuff + writeLen, 3 - writeLen);
            writetimes ++;
        }while(writeLen < 3 && writetimes < 10);

        if(writetimes >= 25)
        {
            fibo_taskSleep(500);
            fibo_softReset();
            return;
        }
        /* 第一步执行完了 等待DA14580回复0x06 */
        LOG_DEBUG(">>>boot da14580 step 1");
        step = 1;
    }
    else if(data[0] == 0x06)
    {
        LOG_DEBUG(">>>star firmware timer");
        timer_start(TIMER_BLE_BOOT, TIMER_MS, 10, da14580_TransFirmware); //不在中断接收中执行发送。
    }

    return;
}

