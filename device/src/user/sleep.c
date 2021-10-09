#include "hardware.h"
#include "led.h"
#include "data.h"
#include "user_timer.h"
#include "uart.h"
#include "gps_parse.h"
#include "log.h"
#include "da14580.h"
#include "diagnosis.h"
#include "socket.h"
#include "setting.h"
#include "request.h"
#include "car.h"
#include "watchdog.h"
#include "ublox.h"
#include "inv_mpu.h"
#include "mpu_dmp_api.h"
#include "detect.h"

#define SLEEP_AFTERTIME 3

static void sleep_accIntEvent_handler(void *param)
{
    data_setAwakeTime(SLEEP_SHARK_WAKE);
}

static int sleep_DisableMoudlecb(void)
{
    static u8  checktimes = 0;

    if(data_getData()->gpsPortData == L_TRUE && checktimes++ < 3)
    {
        LOG_ERROR("[Sleep] disable nmeaOutput failed, try:%dtimes",checktimes);
        gps_nmeaOutputEnable(L_FALSE);
        data_getData()->gpsPortData = L_FALSE;
        return 0;
    }
    if (data_getData()->blePortData == L_TRUE && checktimes++ < 3)
    {
        LOG_ERROR("[Sleep] disable bleHeartbeat failed, try:%dtimes",checktimes);
        da14580_setHeartbeat(L_FALSE);
        data_getData()->blePortData = L_FALSE;
        return 0;
    }
    if(data_getData()->blePortData == L_FALSE && data_getData()->gpsPortData == L_FALSE)
    {
        LOG_INFO("[Sleep] disable ble and gps output success");
    }
    
    checktimes = 0;

    if(setting.settingConf.accleType == ACCLE_MPU6500)
    {
        mpu_wake_on_motion_interrupt(); //先进入运动休眠,使能中断,避开mpu不稳
        
        oc_isr_t oc_ist_lis = {
            .is_debounce = L_TRUE,
            .intr_enable = L_TRUE,
            .intr_level = L_FALSE,
            .intr_falling = L_TRUE,
            .inte_rising = L_TRUE,
            .callback = sleep_accIntEvent_handler,
        };
        fibo_gpio_isr_init(PIN_LIS_INT, &oc_ist_lis); //初始化加速度中断,上升沿触发
    }
    
    timer_stop(TIMER_SLEEP_MOUDLE);
    LED_off(LED_WORK);
    LED_off(LED_GNSS);
    if(data_getData()->buckstate == 1) //进入休眠时处于升压状态，则关闭升压
    {
        data_getData()->buckstate = 0;
        da14580_setBlePinLevel(BLE_PORT2, BLE_PIN2, PIN_LEVEL_LOW);
    }
    
    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能产品
    {
        car_close_RFIDPower(); //休眠关闭RFID 5V供电
    }
    uart_deinitial(UART_GPS);
    timer_enableSleep(L_TRUE);
    data_setSleepState(L_TRUE);
    startWatchdog(WD_SLEEP);
    data_getData()->mode = MODE_SLEEP;
    // 睡眠模式下每10分钟上报一次状态 休眠直接发
    timer_startRepeat(TIMER_SLEEP_STATUS, TIMER_M, 10, cmd_status);
    LOG_INFO("[Sleep] moudle will sleep after%dseconds",SLEEP_AFTERTIME);
    uart_deinitial(UART_DEBUG);
    INT32 ret = fibo_setSleepMode(SLEEP_AFTERTIME);
    if(ret != 0)
    {
        fibo_setSleepMode(SLEEP_AFTERTIME); //尝试再进一次休眠,后续状态在long event中检测
    }
    return 0;
}

void sleep_awakeEnvironment(void)
{
    uint8_t ret = 0;

    /* 唤醒模块 */
    if(setting.settingConf.gpsType == GPS_ALLYSTAR_8040)
    {
        //
    }
    else
    {
        uart_initial(UART_GPS, 9600, 100);
    }
    
    uart_initial(UART_DEBUG, 115200, 0);    //初始化两个串口
    
    ret = fibo_setSleepMode(0); //退出休眠  要先初始化UART1
    if(ret != 0)
    {
        LOG_ERROR("[Sleep] leave sleep moode failed!!");
        uart_initial(UART_BLE, 115200, 0);
        fibo_setSleepMode(0);
    }
    timer_stop(TIMER_SLEEP_STATUS);
    da14580_setHeartbeat(L_TRUE);
    data_getData()->mode = MODE_NORM;
    data_getData()->isReadyToSleep = L_FALSE;
    
    if(setting.settingConf.gpsType == GPS_UBLOX_M8U && setting.settingConf.accleType == ACCLE_LIS3DH) //M8U定向停车方案产品
    { 
        Ublox_M8U_config(); //唤醒后对M8U再次初始化
    }
    else if(setting.settingConf.accleType == ACCLE_MPU6500) //MPU6500产品
    {
        fibo_gpio_isr_deinit(PIN_LIS_INT); //禁止加速度中断
        mpu_dmp_init(); //退出休眠时,重新初始化陀螺仪
    }
    
    data_setSleepState(L_FALSE);
    gps_nmeaOutputEnable(L_TRUE);
    timer_enableSleep(L_FALSE);
    //adc_enable(L_TRUE);
    LED_on(LED_WORK);
    LED_on(LED_GNSS);
    startWatchdog(WD_WAKE);
    
    if(!car_isPowerExistence()) //退出休眠时若大电不在，则开启升压
    {
        data_getData()->buckstate = 1;
        fibo_gpio_set(PIN_CHARGE_DRIVER, GPIO_LEVEL_LOW); //关闭充电
        g_buckctrl = 1;
        timer_start(TIMER_5V_CTRL, TIMER_MS, 5000, detect_5v_ctrl_cb); //大电源没了5秒后将5V升压控制打开
    }
    else
    {
        if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能产品
        {
            car_open_RFIDPower(); //唤醒大电在时开启RFID 5V供电
        }
    }
}

void sleep_sleepEnvironment(void)
{
    /* 使能休眠 */
    da14580_setHeartbeat(L_FALSE);
    gps_nmeaOutputEnable(L_FALSE);
    data_getData()->gpsPortData = L_FALSE;
    data_getData()->blePortData = L_FALSE;
    data_getData()->isReadyToSleep = L_TRUE;
    LOG_DEBUG("[Sleep] sleepEnvironment");
    timer_startRepeat(TIMER_SLEEP_MOUDLE, TIMER_MS, 1500, sleep_DisableMoudlecb);
}

//100ms
void sleep_socketAction(void)
{
    static u8 times = 0;
    if(data_isSleeping())
    {
        times++;
        if(times == 30)
        {	
            times = 0;
            socket_run();
            socket_select();
        }
    }
    else
    {
        socket_select();
    }
}

//100ms
void sleep_wakeupAction(void)
{
    if(data_isSleeping() && data_getData()->awakeTime > 0)
    {
        sleep_awakeEnvironment();
    }
}

