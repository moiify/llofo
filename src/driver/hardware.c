#include "fibo_opencpu.h"
#include "hardware.h"
#include "detect.h"
#include "types.h"
#include "setting.h"
typedef struct
{
    uint16_t pin;
    uint8_t  mode;
    uint16_t dir;
    uint8_t  level;
} GPIO_Config_st;

void pwrkey_null_cb(void *param)
{
    return ;
}

void hardware_initial(void)
{
    GPIO_Config_st gpio_cfg[] = 
    {
        {PIN_BLE_INT,           2, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO29
        {PIN_LIS_INT,           4, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO23
        {PIN_SADDLE_DETECT,     1, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO27
        {PIN_BACKWHEEL_DETECT,  1, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO26
        {PIN_OVERSPEED_DETECT,  1, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO25
        {PIN_ACC_DETECT,        1, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO24
        {PIN_SPEED_DETECT,      0, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO10
        {PIN_PWR_DETECT,        0, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO12
        //{PIN_ADCCOMM_DETECT,    0, GPIO_DIR_INPUT, GPIO_LEVEL_HIGH},    //GPIO44
        
        {PIN_LED_DRIVER,        2, GPIO_DIR_OUTPUT, GPIO_LEVEL_LOW},   //GPIO30
        {PIN_LED_GPS_DRIVER,    0, GPIO_DIR_OUTPUT, GPIO_LEVEL_LOW},   //GPIO9
        {PIN_GNSSRTS_DRIVER,    0, GPIO_DIR_OUTPUT, GPIO_LEVEL_LOW},   //GPIO8
        {PIN_MPU6500_DRIVER,    2, GPIO_DIR_OUTPUT, GPIO_LEVEL_HIGH},  //GPIO7
        {PIN_LED_NETWORK_DRIVER,0, GPIO_DIR_OUTPUT, GPIO_LEVEL_LOW},   //GPIO13
        {PIN_SPK_CTRL,          0, GPIO_DIR_OUTPUT, GPIO_LEVEL_LOW},   //GPIO2
        {PIN_CHARGE_DRIVER,     0, GPIO_DIR_OUTPUT, GPIO_LEVEL_HIGH},  //GPIO11
        
        {PIN_595_DATA_DRIVER,   0, GPIO_DIR_OUTPUT, GPIO_LEVEL_LOW},   //GPIO0
        {PIN_595_SHIFT_CLK,     0, GPIO_DIR_OUTPUT, GPIO_LEVEL_LOW},   //GPIO3
        //{PIN_595_CLR,           1, GPIO_DIR_OUTPUT, GPIO_LEVEL_HIGH},  //GPIO28
    };
		
    fibo_gpio_mode_set(PIN_GPIO_127, 3);//GPIO23冲突,调成zsp_uart_rts
    fibo_gpio_mode_set(PIN_GPIO_41, 4);//I2C冲突,调成GPIO16
    fibo_gpio_mode_set(PIN_GPIO_42, 4);//I2C冲突,调成GPIO17
    
    for (int i = 0; i < sizeof(gpio_cfg) / sizeof(gpio_cfg[0]); i++)
    {
        fibo_gpio_mode_set(gpio_cfg[i].pin, gpio_cfg[i].mode);
        fibo_gpio_cfg(gpio_cfg[i].pin, gpio_cfg[i].dir);
        if(gpio_cfg[i].dir == GPIO_DIR_OUTPUT)
        {
            fibo_gpio_set(gpio_cfg[i].pin, gpio_cfg[i].level);
        }
    }
    fibo_gpio_pull_up_or_down(PIN_BLE_INT,true); //默认weakup拉高
    fibo_gpio_mode_set(PIN_I2CSCL_141, 1);//I2C2_SCL
    fibo_gpio_mode_set(PIN_I2CSDA_142, 1);//I2C2_SDA
	fibo_inner_flash_init();
    uart_initial(UART_GPS,   9600,   100);//70ms可以让nmea数据整包回传, 100ms做保险起见
    uart_initial(UART_BLE,   115200, 0);
    uart_initial(UART_DEBUG, 115200, 0);
	fibo_setSleepMode(0);  //唤醒模式
	fibo_set_pwr_callback(pwrkey_null_cb, 1000); //禁用pwrkey关机功能
}

void gpio_init_595_CLR(void)
{
    fibo_gpio_mode_set(PIN_595_CLR, 1);
    fibo_gpio_cfg(PIN_595_CLR, GPIO_DIR_OUTPUT);
    fibo_gpio_set(PIN_595_CLR, GPIO_LEVEL_HIGH);
}
