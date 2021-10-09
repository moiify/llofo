
#ifndef __USER_BLE_PROC_H__
#define __USER_BLE_PROC_H__
#include <stdio.h>
#include <stdbool.h> 
#include <stdint.h>

void ble_start_scan(void);
void ble_start_adv(void);

int ble_proc_timer(void);
void ble_resetMissHeartBeatTime(void);
int ble_procOneMsg(const uint8_t * data, uint16_t dataLen);
int8_t ble_rf_rssi_convert(uint8_t rssi_reg);
void ble_setNeedRstMcu(void);


#endif /*__USER_BLE_PROC_H__*/
