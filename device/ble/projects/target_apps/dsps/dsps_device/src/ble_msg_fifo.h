#ifndef __BLE_MSG_FIFO_H__
#define __BLE_MSG_FIFO_H__

#define MAX_BLE_MSG_FIFO_SIZE 256

typedef uint8_t u8;
typedef uint16_t u16;

typedef u8 datatype;
typedef struct 
{
    datatype buf[MAX_BLE_MSG_FIFO_SIZE];

    int head;

    int tail;
}ST_BLE_MSG_FIFO;


int ble_msg_fifo_isEmpty(ST_BLE_MSG_FIFO *q);
int ble_msg_fifo_isFull(ST_BLE_MSG_FIFO *q);
int ble_msg_fifo_enData(ST_BLE_MSG_FIFO *q, datatype *e, u16 len);
int ble_msg_fifo_en(ST_BLE_MSG_FIFO *q, datatype e);
int ble_msg_fifo_de(ST_BLE_MSG_FIFO *q, datatype *e);
void ble_msg_fifo_clear(ST_BLE_MSG_FIFO *q);
int ble_msg_fifo_len(ST_BLE_MSG_FIFO *q);


#endif 
