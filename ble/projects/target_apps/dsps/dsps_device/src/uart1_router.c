#include "uart1.h"
#include "setting.h"
#include "protocol.h"
#include "local_event.h"
#include "ble_uart_port.h"

extern ST_BLE_STATE setting;
bool uart_isCheckSumPass(MSG_HEADER *msg)
{
    uint8_t i = 0;
    uint8_t checksum = msg->address + msg->cmd + msg->len;
    for(i = 0; i < msg->len; i++)
    {
        checksum += msg->data[i];
    }

    if(checksum == msg->data[msg->len])
    {
        return true;
    }

    return false;
}

/*
* brief: proc msg from simcom with uart
* [note]
*       BLE_WILD: just send body to app
*       BLE_CONF: just proc and response
*       OTHERS  : just send to uart2
*/
static int uart1_router_one_msg(uint8_t* data, uint16_t length)
{
    MSG_HEADER *msg = (MSG_HEADER *)data;
    uint16_t msgLen = msg->len + MSG_HEADER_LEN + 1;

    if(0x55AA != msg->signature)
    {
        return -1;
    }

    if(false == uart_isCheckSumPass(msg))
    {
        return -1;
    }

    if(length < msgLen)
    {
        return -1;
    }

    switch(msg->address)
    {
        case BLE_WILD:
        {
            if(msg->cmd != 0x00)
            {
                send_data_toBLE(&(msg->cmd), msgLen - sizeof(uint16_t) - 1);
            }
            else//透传接口
            {
                send_data_toBLE(msg->data, msg->len);
            }
            break;
        }
        case BLE_CONF:
            uart_config_proc(data, msgLen);
            break;

        case BMS_WILD:
        case ETC_WILD:
        default:
            //patch 如果是控制485的锁 那么使能VBUS10秒钟以给锁供电
//            if(msg->address == 0x05)
//            {
//                enable_VBUS();
//            }
            uart2_sendData(data, msgLen);
            break;
    }

    return 0;
}

/*
*收到868传的消息
*然后根据格式分配到 uart2/ble/自己
*/
void uart1_router(const uint8_t * data, uint16_t length)
{
    if(PROTOCOL_XL == setting.protocol_type)
    {
        int i = 0;
        uint8_t *p = NULL;
        int16_t leftLen = length;
        MSG_HEADER *msg = (MSG_HEADER*)data;

        while(leftLen > 0)
        {
            if(ntohs(msg->signature) != 0xAA55)//避免连包 需要拆包
            {
                p = (uint8_t *)msg;
                for(i = 0; i < leftLen - 1; i++)
                {
                    if(*(p + i) == 0xAA && *(p + i + 1) == 0x55 && uart_isCheckSumPass((MSG_HEADER *)(p + i)))
                    {
                        break;//如果尾缀着小安的协议 那么分包处理一下
                    }
                }

                if(i == (leftLen - 1))
                {
                    uart2_sendData((uint8_t *)msg, leftLen);
                    return;
                }

                uart2_sendData((uint8_t *)msg, i);
                leftLen = leftLen - i;
                msg = (MSG_HEADER *)((uint8_t *)data + (length - leftLen));
                continue;
            }

            uart1_router_one_msg((uint8_t *)msg, leftLen);

            leftLen = leftLen - (msg->len + MSG_HEADER_LEN + 1);
            msg = (MSG_HEADER *)((uint8_t *)data + (length - leftLen));
        }
    }
    else  // 默认小安的协议
    {
        int16_t leftLen = length;
        MSG_HEADER *msg = (MSG_HEADER *)data;

        while(leftLen > 0)
        {
            if(ntohs(msg->signature) != 0xAA55)
            {
                uart2_sendData((uint8_t *)msg, leftLen);
                return;
            }

            uart1_router_one_msg((uint8_t *)msg, leftLen);

            leftLen = leftLen - (msg->len + MSG_HEADER_LEN + 1);
            msg = (MSG_HEADER *)((uint8_t *)data + (length - leftLen));
        }

    }
    return;
}

