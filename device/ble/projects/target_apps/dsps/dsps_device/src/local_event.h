#ifndef __LOCOL_EVENT_H__
#define __LOCOL_EVENT_H__

#include "hardware.h"


// 旧的配置（留存备份
////PORT_0
////#define PIN_ADC_BAT             GPIO_PIN_0 //与uart2冲突
////#define PIN_ADC_TMP             GPIO_PIN_1
//#define WAKEUP_SIM868_PORT      GPIO_PORT_0
////GPIO_PIN_0 UART_TX
////GPIO_PIN_1 UART_RX
////GPIO_PIN_2 SIMCOM_TX
////GPIO_PIN_3 SIMCOM_RX
////GPIO_PIN_4 NULL
//#define WAKEUP_SIM868_PIN       GPIO_PIN_5  //868唤醒处理
////GPIO_PIN_6 NULL
////GPIO_PIN_7 NULL

////PORT_1
////GPIO_PIN_0  SADDLE_DETECT
////GPIO_PIN_1  NULL_DETECT
////GPIO_PIN_2  NULL_DETECT
////GPIO_PIN_3  NULL_DETECT



// 唤醒868/800C 的蓝牙中断脚
//PORT_0
#define PIN_ADC_BAT             GPIO_PIN_0  // 小电池电压检测
#define PIN_ADC_TMP             GPIO_PIN_1  // 小电池电池温度检测

#define WAKEUP_SIM868_PORT      GPIO_PORT_2
#define WAKEUP_SIM868_PIN       GPIO_PIN_3  //  L610唤醒处理



// 旧的配置（留存备份
////PORT_2
//#define PIN_595_DATA_DRIVER     GPIO_PIN_0
//#define PIN_SP4502_EN           GPIO_PIN_2
//#define PIN_SPK_EN              GPIO_PIN_3
//#define PIN_BACKWHEEL_DETECT    GPIO_PIN_4
//#define PIN_VBUS_DRIVER         GPIO_PIN_5
//#define PIN_POWER_DETECT        GPIO_PIN_6
//#define PIN_595_SHIFT_CLK       GPIO_PIN_8
//#define PIN_595_LATCH_CLK       GPIO_PIN_9

////PORT_1
//#define PIN_SADDLE_DETECT       GPIO_PIN_0

//PORT_2
#define PIN_595_DATA_DRIVER     GPIO_PIN_0
#define PIN_SGM66052_EN         GPIO_PIN_2  // 66052输出控制
#define PIN_SWITCH_DETECT       GPIO_PIN_3
#define PIN_BACKWHEEL_DETECT    GPIO_PIN_4
#define PIN_VBUS_DRIVER         GPIO_PIN_5
#define PIN_POWER_DETECT        GPIO_PIN_6
#define PIN_595_SHIFT_CLK       GPIO_PIN_8
#define PIN_595_LATCH_CLK       GPIO_PIN_9

//PORT_1
#define PIN_SADDLE_DETECT       GPIO_PIN_0
#define PIN_OVERSPEED_DETECT    GPIO_PIN_1


#define WAKEUP_SIM868_DELAY (3)     //30ms
#define ENABLE_SP4502_DELAY (10)    //100ms


void enable_VBUS(void);
void wakeup_SIM868(void);
void GPIO_commonInit(void);
void wakeup_others_init(void);

void uart_config_proc(uint8_t *data, uint16_t length);

int uart_print_SIM868(uint8_t *data, uint8_t dataLen);
int  uart_sendNotify(uint8_t address, uint8_t cmd, uint8_t notify);
void uart_sendMsgtoSIM868(uint8_t address, uint8_t cmd, uint8_t len,uint8_t *data);
void AsciiToHex(unsigned char * pAscii, unsigned char * pHex, int nLen);
void event_onConnection(void);
void event_onDisconnection(void);
void event_setConnectionID(uint8_t connection_id);

void String2Hex(unsigned char *pString, unsigned char *pHex, int stringLen);
void Hex2String(unsigned char *pHex, unsigned char *pString, int hexLen);

void timer0_callback_func(void);



#endif

