#include "app_easy_timer.h"

#include "uart1.h"
#include "setting.h"
#include "ble_proc.h"
#include "protocol.h"
#include "user_spss.h"
#include "local_event.h"

#define SPS_TX_PACKET_SIZE 60
#define BLE_SEND_ONE_PACK_SIZE 20

void send_data_toBLE(const uint8_t *buf, uint16_t len)
{
    //len = len > SPS_TX_PACKET_SIZE ? SPS_TX_PACKET_SIZE : len;
    user_send_ble_data(buf, len);
}

/*
* 尝试发送数据给868
*/
void send_data_toSIM868(const uint8_t *buf, uint16_t len)
{  
    uart1_enqueneData(buf, len);
	uart1_launch(); 
}

void send_data_to485(const uint8_t *buf, uint16_t len)
{
    uart2_sendData((uint8_t *)buf, len);
}

void reciv_data_fromBLE_cb(const uint8_t *buf, uint16_t len)
{
    ble_procOneMsg(buf, len);
}

void reciv_data_fromSIM868_cb(const uint8_t *buf, uint16_t len)
{
    uart1_router(buf, len);
}

