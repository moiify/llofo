#ifndef __BLE_UART_PORT_H__
#define __BLE_UART_PORT_H__

void send_data_toBLE(const uint8_t *buf, uint16_t len);
void send_data_toSIM868(const uint8_t *buf, uint16_t len);
void send_data_to485(const uint8_t *buf, uint16_t len);

void reciv_data_fromBLE_cb(const uint8_t *buf, uint16_t len);
void reciv_data_fromSIM868_cb(const uint8_t *buf, uint16_t len);

#endif 
