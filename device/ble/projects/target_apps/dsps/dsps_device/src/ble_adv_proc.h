
#ifndef __USER_BLE_ADV_PROC_H__
#define __USER_BLE_ADV_PROC_H__

#include <stdio.h>
#include <stdbool.h> 
#include <stdint.h>

typedef enum{
    CMD_BLE_SET_DEFEND    = 0x20,//BLE控制车辆启动和设防
    CMD_BLE_GET_STATUS    = 0x21,//BLE获取车辆当前状态
    CMD_BLE_SET_SERVER    = 0x22,//BLE控制盒子更改服务器地址
    CMD_BLE_AWAKE_DEVICE  = 0x23 //BLE控制盒子唤醒
}MSG_CMD_BLE;


typedef struct {
    uint8_t pHead[3];
    uint8_t len;
    uint8_t localAddress;
    uint8_t destAddress;
    uint8_t optionCode;
    uint8_t randomCode;
    uint8_t data[];
}__attribute__((__packed__))ST_BLE_MSG_HEAD;//3个字节

typedef struct {
    uint8_t xorCode;
    uint16_t keyWord;
}__attribute__((__packed__))ST_BLE_MSG_TAIL;//3个字节


void ble_connect_handler(void);
void ble_disConnect_handler(void);

void ble_adv_timeout_handler(void);

void ble_adv_set_name(const uint8_t *name,uint8_t len);
void ble_adv_set_manufData(const uint8_t *manufData,uint8_t len);

uint8_t ble_adv_load_advData(uint8_t *pAdvData);
uint8_t ble_adv_load_scanRspData(uint8_t *scanRspData);


#endif /*__USER_BLE_PROC_H__*/
