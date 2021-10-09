#include "ble_uart_port.h"
#include "ble_msg_fifo.h"
#include "decode.h"
#include "protocol.h"
#include "local_event.h"
#include "user_spss.h"
#include "ble_adv_proc.h"
#include "uart1.h"

ST_BLE_MSG_FIFO ble_msg_reciv_fifo = {{0}, 0, 0};

int ble_msg_fifo_isEmpty(ST_BLE_MSG_FIFO *q)
{
    return q->head == q->tail;
}

int ble_msg_fifo_isFull(ST_BLE_MSG_FIFO *q)
{
    return (q->tail+1)%MAX_BLE_MSG_FIFO_SIZE == q->head;
}


int ble_msg_fifo_enData(ST_BLE_MSG_FIFO *q, datatype *e, u16 len)
{
    int i = 0;
    
    for(i = 0; i< len; i++)
    {
        ble_msg_fifo_en(q, e[i]);

    }
    return true;
}

int ble_msg_fifo_en(ST_BLE_MSG_FIFO *q, datatype e)
{
    //若溢出则顶出老数据
    if (ble_msg_fifo_isFull(q))
    {
        datatype temp = 0;
        ble_msg_fifo_de(q, &temp);
    }
    
    q->buf[q->tail] = e;
    q->tail=(q->tail+1)%MAX_BLE_MSG_FIFO_SIZE;
    return true;

}

int ble_msg_fifo_de(ST_BLE_MSG_FIFO *q, datatype *e)
{
    if(ble_msg_fifo_isEmpty(q)) return false;

    if(e)
    {
        *e = q->buf[q->head];
    }
    
    q->head = (q->head+1)%MAX_BLE_MSG_FIFO_SIZE;  
    
    return true;
}

void ble_msg_fifo_clear(ST_BLE_MSG_FIFO *q)
{
    q->head = q->tail = 0;
}

int ble_msg_fifo_len(ST_BLE_MSG_FIFO *q)
{
    return (q->tail - q->head + MAX_BLE_MSG_FIFO_SIZE)%MAX_BLE_MSG_FIFO_SIZE;
}

