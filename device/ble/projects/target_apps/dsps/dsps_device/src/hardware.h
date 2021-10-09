#ifndef __HARDWARE__H__
#define __HARDWARE__H__

// 更改/增加引脚配置需要同步 uart1.h, local_event.h 及其绑定功能
// 引脚配置说明汇总，硬件功能与引脚绑定，软件功能用开关配置



// ------------ 868 系列引脚配置 0xx  -------------- //
// 000：
// 默认配置: 只有两个串口，中断唤醒
#define PIN_CONFIG_000 00  

// 001：
#define PIN_CONFIG_001 01
#define PIN_CONFIG_002 02
#define PIN_CONFIG_003 03




// ------------ 800c 系列引脚配置 1xx -------------- //
// 100：
// 默认配置
// 绑定功能：SP4502
#define PIN_CONFIG_100 100  

// 101：
// 485串口和蓝牙中断下移，增加 ADC、看门狗
//
// 绑定功能：adc，SGM66052
#define PIN_CONFIG_101 101

// 102：
#define PIN_CONFIG_102 102
#define PIN_CONFIG_103 103







#endif

