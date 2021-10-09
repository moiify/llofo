/*
 * car.c
 *
 *  Created on: 2016/11/29
 *      Author: lc
 */

#include "fibo_opencpu.h"

#include "hardware.h"
#include "user_timer.h"
#include "car.h"
#include "log.h"
#include "data.h"
#include "flash.h"
#include "etcMsg.h"
#include "da14580.h"
#include "setting.h"
#include "usermsg.h"
#include "audio_driver.h"

#define MAX_LOCKCAR_LONG    (10)    //10s

static void control595_delay(void)
{
    uint32_t times = 500; // [1: 0.2346us]
    while(times--)
    {
        asm("nop");
    }
}

void control595(uint8_t PIN_MASK, GpioLevel_enum level)
{
    static uint8_t pinState = 0x00;
    static uint8_t isFirst = L_TRUE;

    uint8_t i = 0;
    uint8_t state = pinState;
    if(level == GPIO_LEVEL_LOW)
    {
        state &= ~PIN_MASK;//移除该位寄存
    }
    else
    {
        state |= PIN_MASK;//装上该位寄存
    }

    pinState = state;//将输出情况存下来
    if(isFirst)
    {
        isFirst = L_FALSE;
        gpio_init_595_CLR();
        fibo_gpio_mode_set(PIN_595_LATCH_CLK, 0);
        fibo_gpio_cfg(PIN_595_LATCH_CLK, GPIO_DIR_OUTPUT);
        fibo_gpio_set(PIN_595_LATCH_CLK, GPIO_LEVEL_LOW);
        fibo_gpio_set(PIN_595_CLR, GPIO_LEVEL_LOW);
    }

    fibo_gpio_set(PIN_595_LATCH_CLK, GPIO_LEVEL_LOW);

    for(i = 0; i < 8; i++)
    {
        //从Q7->Q0装载
        uint8_t bit = state >> 7;
        fibo_gpio_set(PIN_595_DATA_DRIVER, bit ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
        state = state << 1;

        fibo_gpio_set(PIN_595_SHIFT_CLK, GPIO_LEVEL_HIGH);//上升沿
        control595_delay();
        fibo_gpio_set(PIN_595_SHIFT_CLK, GPIO_LEVEL_LOW);
        control595_delay();
    }

    /*位移寄存器数据准备完毕,转移到存储寄存器输出*/
    fibo_gpio_set(PIN_595_LATCH_CLK, GPIO_LEVEL_HIGH);//上升沿
}

/*
*function: 电机磁场锁上锁
*/
void car_lockElectricalBrake(void)
{
    control595(PIN_MASK_BRAKE_DRIVER, GPIO_LEVEL_HIGH);
}

/*
*function: 电机磁场锁解锁
*/
void car_unlockElectricalBrake(void)
{
    timer_stop(TIMER_RELEASE_ELOCK);
    control595(PIN_MASK_BRAKE_DRIVER, GPIO_LEVEL_LOW);
}

uint8_t car_isCarLocking(void)
{
    return timer_isTimerStart(TIMER_RELEASE_ELOCK);
}

int car_open_RFIDPower(void)
{
    da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_HIGH); //关闭RFID 5V供电
    return 0;
}

/*
*function: 打开电门, 高电平启动
*/
void car_accOn(void)
{
    data_getData()->speedCountTime = 30;    //短时间内允许相位检测
    control595(PIN_MASK_ACC_DRIVER, GPIO_LEVEL_HIGH);
    etcMsg_setETCAccOn();
    etcMsg_setETCDefend(L_FALSE);//设置控制器撤防

    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
    {
        car_open_RFIDPower(); //开启RFID 5V供电
        timer_start(TIMER_RFID_POWER, TIMER_MS, 100, car_open_RFIDPower); //100ms后再次发送保证成功开启5v供电
    }
}

//关闭RFID 5V供电
int car_close_RFIDPower(void)
{
    da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_LOW);
    return 0;
}

/*
*function: 关闭电门, 与mangguo_G0-G2版本逻辑相反, 低电平熄火
*/
void car_accOff(void)
{
    data_getData()->speedCountTime = 0; //短时间内不进行相位检测
    control595(PIN_MASK_ACC_DRIVER, GPIO_LEVEL_LOW);

    if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
    {
        car_close_RFIDPower(); //关闭RFID 5V供电
        timer_start(TIMER_RFID_POWER, TIMER_MS, 100, car_close_RFIDPower); //100ms后再次发送保证成功关闭5v供电
    }
}

void car_closeRFIDPower_SetDeffend(void)
{
    car_close_RFIDPower(); //关闭RFID 5V供电
    data_getData()->isRFIDPowerOn = L_FALSE;
}

void car_openRFIDPower_SetDeffend(void)
{
    car_open_RFIDPower();
    data_getData()->isRFIDPowerOn = L_TRUE;
    timer_start(TIMER_RFID_DELAY_POWERON, TIMER_MS, 8000, car_closeRFIDPower_SetDeffend);
}

void car_accAction(void)
{
    if(setting_isAccOn())
    {
        car_accOn();
    }
    else
    {
        car_accOff();
    }
}

//打开RFID的485发送使能，发送指令到RFID
void car_open_RFID485(void)
{
    da14580_setBlePinLevel(BLE_PORT2, BLE_PIN1, PIN_LEVEL_HIGH);
}

//关闭RFID的485发送使能，接受RFID回复信息
void car_close_RFID485(void)
{
    da14580_setBlePinLevel(BLE_PORT2, BLE_PIN1, PIN_LEVEL_LOW);
}

/*
*function: 获取电门开关状态 高电平为电门关 低电平为电门开
*/
L_BOOL car_isAccOn(void)
{
    uint8_t level = 0;
    fibo_gpio_get(PIN_ACC_DETECT, &level);
    return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;
}

/*
*function: 解锁电动车，即电门关闭，电机关闭
*/
static int car_unlockAccoff(void)
{
    car_accOff();
    return 0;
}
int car_unlock(void)
{
    car_unlockElectricalBrake();
    etcMsg_setETCDefend(L_FALSE);//设置控制器撤防
    data_getData()->speedCountTime = 0; //短时间内不进行相位检测
    data_getData()->socWait = L_FALSE; //超时未获取到soc
    timer_start(TIMER_RELEASE_ELOCK, TIMER_MS, 300, car_unlockAccoff);//兼容控制器问题 接触设防后600ms执行熄火
    return 0;
}

/*
*function: 锁死电动车，即电门打开, 电机锁锁上, 10秒钟后自动解锁
*/
void car_lock(void)
{
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag)
    {
        return;
    }
    car_lockElectricalBrake();
    timer_start(TIMER_RELEASE_ELOCK, TIMER_S, MAX_LOCKCAR_LONG, car_unlock);
    control595(PIN_MASK_ACC_DRIVER, GPIO_LEVEL_HIGH);
    etcMsg_setETCDefend(L_TRUE);//设置控制器设防
}

void car_lockAndGetSoc(void)
{
    if(!car_isAccOn() && car_isPowerExistence())
    {
        if(setting.defaultConf.ccuType != TYPE_TAIBITE_SOC) //此特殊版本需要多个soc数据做过滤，则不提前关闭电门
        {
            data_getData()->socWait = L_TRUE; //标记等待控制器soc消息，以便拿到soc后提前关闭电门
        }
        car_lock(); //如果电门未开则开电门并抱死车辆，最多10s
    }

    //实际上开电门后也会触发这些消息，这里作冗余
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        ETC_XiaoAn_GetSOC();
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE
    || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
    || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
    || setting.defaultConf.ccuType == TYPE_TAIBITE_09)
    {
        ETC_TaiBiTe_GetETCInfo(); //泰比特控制器从获取控制器消息中得到soc
    }
}

/*
* 鞍座锁上锁
*/
static int car_lockSaddle_cb(void)
{
    control595( PIN_MASK_SADDLE_P_DRIVER | PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_LOW);
    return 0;
}
void car_lockSaddle(void)
{
    if (setting.defaultConf.saddleType == TYPE_LOCKPINSADDLE)  //唐泽电池仓锁,与唐泽后轮锁逻辑相反
    {
        control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 2000, car_lockSaddle_cb);
    }
    else
    {
        return;
    }
}

/*
* 鞍座锁解锁
*/
static int car_unlockSaddle_cb(void)
{
    control595(PIN_MASK_SADDLE_P_DRIVER | PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_LOW);
    setting.statusConf.OperatingSaddlelock = L_FALSE;
    statusConf_save();
    return 0;
}

static int car_unlockYaKeTeK1Saddle_reverse_cb(void)
{
    control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 1200, car_unlockSaddle_cb);
    return 0;
}

static int car_unlockYaKeTeK1Saddle_onWait_cb(void)
{
    control595(PIN_MASK_SADDLE_P_DRIVER | PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_LOW);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 300, car_unlockYaKeTeK1Saddle_reverse_cb);
    return 0;
}

static void car_unlockYaKeTeK1Saddle(void)
{
    control595(PIN_MASK_SADDLE_P_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 1200, car_unlockYaKeTeK1Saddle_onWait_cb);
}

static int car_unlockYaKeTeB02Saddle_wait_cb(void)
{
    control595(PIN_MASK_SADDLE_P_DRIVER, GPIO_LEVEL_HIGH);
    return timer_start(TIMER_SET_SADDLE, TIMER_MS, 1000, car_unlockSaddle_cb);
}

static int car_unlockDaHaSaddle_wait_cb(void)
{
    control595(PIN_MASK_SADDLE_P_DRIVER, GPIO_LEVEL_HIGH);
    return timer_start(TIMER_SET_SADDLE, TIMER_MS, 1000, car_unlockSaddle_cb);
}

static int car_unlockYaKeTeB02Saddle_P_cb(void)
{
    control595(PIN_MASK_SADDLE_P_DRIVER | PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_LOW);
    return timer_start(TIMER_SET_SADDLE, TIMER_MS, 3000, car_unlockYaKeTeB02Saddle_wait_cb);
}

static int car_unlockDaHaSaddle_P_cb(void)
{
    control595(PIN_MASK_SADDLE_P_DRIVER | PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_LOW);
    return timer_start(TIMER_SET_SADDLE, TIMER_MS, 3000, car_unlockDaHaSaddle_wait_cb);
}

static void car_unlockYaKeTeB02Saddle(void)
{
    control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 1000, car_unlockYaKeTeB02Saddle_P_cb);
}

static void car_unlockDaHaSaddle(void)
{
    control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 1000, car_unlockDaHaSaddle_P_cb);
}

static void car_unlock48VSaddle(void)
{
    control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 600, car_unlockSaddle_cb);
}

static void car_unlock48VSaddle_200(void)
{
    control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 200, car_unlockSaddle_cb);
}

static void car_unlockMagneticSaddle(void)
{
    control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 200, car_unlockSaddle_cb);
}

static void car_unlockJDYSaddle(void)
{
    control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_SADDLE, TIMER_MS, 500, car_unlockSaddle_cb);
}

void car_unlockSaddle(void)
{
    if (setting.defaultConf.saddleType == TYPE_EMAGNETICSADDLE)//电磁锁
    {
        car_unlockMagneticSaddle();
    }
    else if(setting.defaultConf.saddleType == TYPE_BUCKLESADDLE)//亚克特B02电池仓锁
    {
        car_unlockYaKeTeB02Saddle();
        setting.statusConf.OperatingSaddlelock  = L_TRUE;
        statusConf_save();
    }
    else if(setting.defaultConf.saddleType == TYPE_BUCKLESADDLE_REVERT)//亚克特K1电池仓锁,和亚克特B02逻辑相反
    {
        car_unlockYaKeTeK1Saddle();
    }
    else if (setting.defaultConf.saddleType == TYPE_JDY500MS_MX5F)//筋斗云500ms锁
    {
        car_unlockJDYSaddle();
        setting.statusConf.OperatingSaddlelock  = L_TRUE;
        statusConf_save();
    }
    else if(setting.defaultConf.saddleType == TYPE_DAHACHE)//大哈车电池仓锁
    {
        car_unlockDaHaSaddle();
        setting.statusConf.OperatingSaddlelock  = L_TRUE;
        statusConf_save();
    }
    else if (setting.defaultConf.saddleType == TYPE_LOCKPINSADDLE)  //唐泽电池仓锁,与唐泽后轮锁逻辑相反
    {
        control595(PIN_MASK_SADDLE_P_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 2000, car_unlockSaddle_cb);
        setting.statusConf.OperatingSaddlelock  = L_TRUE;
        statusConf_save();
    }
    else if(setting.defaultConf.saddleType == TYPE_48V_BUCKLESADDLE)//48V电池仓锁
    {
        car_unlock48VSaddle();
        setting.statusConf.OperatingSaddlelock  = L_TRUE;
        statusConf_save();
    }
    else if(setting.defaultConf.saddleType == TYPE_48V_SADDLELOCK_200
    || setting.defaultConf.saddleType == TYPE_48V_200_XBD) //200ms的48V电池仓锁
    {
        car_unlock48VSaddle_200();
        setting.statusConf.OperatingSaddlelock  = L_TRUE;
        statusConf_save();
    }
}

int car_checkSaddle(void)
{
    if(setting.defaultConf.saddleType != TYPE_DAHACHE)
    {
        LOG_DEBUG("check Saddle");
        if(!car_isSaddleLocked() || setting.statusConf.OperatingSaddlelock == L_TRUE) //如果电池锁无到位信号或者上次没执行完(重启),执行解锁重置
        {
            car_lockSaddleHalf();
        }
    }
    return 0;
}

int car_checkHelmet(void)
{
    LOG_DEBUG("check Helmet");
    if(!car_isHelmetLocked())
    {
        car_lockHelmet();
    }
    return 0;
}

/*
* MX5F电池仓锁高电平到位            与MXL5F相反
* MX5Z唐泽电池仓锁低电平到位
* MX5K4_XBD样机低电平到位
*/
L_BOOL car_isSaddleLocked(void)
{
    uint8_t level = 0;
    fibo_gpio_get(PIN_SADDLE_DETECT, &level);

    if (setting.defaultConf.saddleType == TYPE_LOCKPINSADDLE
    || setting.defaultConf.saddleType == TYPE_48V_200_XBD) //锁销式电池仓锁-唐泽电池仓锁，或者是喜宝达样机锁
    {
        return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;
    }
    else
    {
        return level == GPIO_LEVEL_HIGH ? L_TRUE : L_FALSE;
    }
}

void car_unlockSaddleHalf(void)
{
    LOG_DEBUG("[Crl] unlockSaddleHalf");
    if (setting.defaultConf.saddleType == TYPE_EMAGNETICSADDLE)//电磁锁
    {
    }
    if(setting.defaultConf.saddleType == TYPE_BUCKLESADDLE)//亚克特B02电池仓锁
    {
        control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 1200, car_unlockSaddle_cb);
    }
    else if (setting.defaultConf.saddleType == TYPE_BUCKLESADDLE_REVERT)//亚克特K1电池仓锁
    {
        control595(PIN_MASK_SADDLE_P_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 1200, car_unlockSaddle_cb);
    }
    else if (setting.defaultConf.saddleType == TYPE_48V_BUCKLESADDLE)//48V电池仓锁
    {
        control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 600, car_unlockSaddle_cb);
    }
    else if (setting.defaultConf.saddleType == TYPE_LOCKPINSADDLE)  //唐泽电池仓锁
    {
        control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 2000, car_unlockSaddle_cb);
    }
    else if(setting.defaultConf.saddleType == TYPE_48V_SADDLELOCK_200
    || setting.defaultConf.saddleType == TYPE_48V_200_XBD) //200ms的48V电池仓锁
    {
        control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 200, car_unlockSaddle_cb);
    }
}

void car_lockSaddleHalf(void)
{
    LOG_DEBUG("[Crl] lockSaddleHalf");
    if(setting.defaultConf.saddleType == TYPE_BUCKLESADDLE)//亚克特B02电池仓锁
    {
        control595(PIN_MASK_SADDLE_P_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 1200, car_unlockSaddle_cb);
    }
    else if (setting.defaultConf.saddleType == TYPE_BUCKLESADDLE_REVERT)//亚克特K1电池仓锁
    {
        control595(PIN_MASK_SADDLE_N_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_SADDLE, TIMER_MS, 1200, car_unlockSaddle_cb);
    }
}

static int car_setBackWheel_cb(void)
{
    control595(PIN_MASK_BACKWHEEL_P_DRIVER | PIN_MASK_BACKWHEEL_N_DRIVER, GPIO_LEVEL_LOW);
    return 0;
}
void car_lockBackWheel(void)//涨阀锁上锁
{
    if(setting.defaultConf.backWheelType == TYPE_LOCKPINBACKWHEEL)
    {
        control595(PIN_MASK_BACKWHEEL_P_DRIVER, GPIO_LEVEL_HIGH);
        control595(PIN_MASK_BACKWHEEL_N_DRIVER, GPIO_LEVEL_LOW);
        timer_start(TIMER_SET_BACKWHEEL, TIMER_MS, 1500, car_setBackWheel_cb);
        return;
    }
    else if(setting.defaultConf.backWheelType == TYPE_TANGZE_BACKWHEEL) //唐泽后轮锁，与唐泽电池仓锁控制逻辑相反
    {
        control595(PIN_MASK_BACKWHEEL_P_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_BACKWHEEL, TIMER_MS, 1500, car_setBackWheel_cb);
        return;
    }
}
static int car_unlockBackWheel_cb(void) //涨阀锁解锁
{
    return 0;
}
void car_unlockBackWheel(void)
{
    if(setting.defaultConf.backWheelType == TYPE_LOCKPINBACKWHEEL)
    {
        control595(PIN_MASK_BACKWHEEL_N_DRIVER, GPIO_LEVEL_HIGH);
        control595(PIN_MASK_BACKWHEEL_P_DRIVER, GPIO_LEVEL_LOW);
        timer_start(TIMER_SET_BACKWHEEL, TIMER_MS, 1500, car_unlockBackWheel_cb);
        return;
    }
    else if(setting.defaultConf.backWheelType == TYPE_TANGZE_BACKWHEEL) //唐泽后轮锁，与唐泽电池仓锁控制逻辑相反
    {
        control595(PIN_MASK_BACKWHEEL_N_DRIVER, GPIO_LEVEL_HIGH);
        timer_start(TIMER_SET_BACKWHEEL, TIMER_MS, 1500, car_setBackWheel_cb);
        return;
    }
}

/*
*后轮锁，锁上到位，到位后低电平
*/
L_BOOL car_isBackWheelLocked(void)
{
    uint8_t level = 0;
    fibo_gpio_get(PIN_BACKWHEEL_DETECT, &level);
    if(setting.defaultConf.backWheelType == TYPE_TANGZE_BACKWHEEL) 
    {
        return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;//唐泽后轮锁，与唐泽电池仓锁控制逻辑相反
    }
    return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;
}

//获得电池的在位状态, 高电平在位
L_BOOL car_isPowerExistence(void)
{
    uint8_t level = 0;
    fibo_gpio_get(PIN_PWR_DETECT, &level);
    return level == GPIO_LEVEL_HIGH ? L_TRUE : L_FALSE;
}

//获得超速报警状态, 低电平超速
L_BOOL car_isOverSpeed(void)
{
    uint8_t level = 0;
    fibo_gpio_get(PIN_OVERSPEED_DETECT, &level);
    return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;
}

//获得磁脚撑在位状态 低电平为检测到磁铁
L_BOOL car_isMagneticKick(void)
{
    uint8_t level = 0;
    fibo_gpio_get(PIN_OVERSPEED_DETECT, &level);
    return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;
}

static int car_rebootDa14580_cb(void)
{
    control595(PIN_MASK_BLERST_DRIVER, GPIO_LEVEL_LOW);
    return 0;
}
void car_rebootDA14580(void)
{
    control595(PIN_MASK_BLERST_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_REBOOT_DA14580, TIMER_MS, 20, car_rebootDa14580_cb);
}

void car_lightOperate(u8 sw)
{
    if(setting.defaultConf.lightCtrlType == TYPE_PINHEADLIGHT)
    {
        if(sw)
        {
            control595(PIN_MASK_LIGHT_DRIVER, GPIO_LEVEL_HIGH);
        }
        else
        {
            control595(PIN_MASK_LIGHT_DRIVER, GPIO_LEVEL_LOW);
        }
    }
    else if(setting.defaultConf.lightCtrlType == TYPE_CCUHEADLIGHT && setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        etcMsg_setETCLight(sw);
    }
}

static uint8_t lightState = L_FALSE;
static int car_blinkLight_cb(void)
{
    static uint32_t time = 0;
    lightState = !lightState;
    if(lightState == L_TRUE)
    {
        control595(PIN_MASK_ACC_DRIVER, GPIO_LEVEL_HIGH);//HIGH
    }
    else
    {
        control595(PIN_MASK_ACC_DRIVER, GPIO_LEVEL_LOW);//LOW
    }
    time++;
    if(time >= 4)
    {
        time = 0;
        timer_stop(TIMER_BLINK_LIGHT);
        if(setting_isAccOn())//如果当前电门开启
        {
            control595(PIN_MASK_ACC_DRIVER, GPIO_LEVEL_HIGH);//HIGH
        }
        else
        {
            control595(PIN_MASK_ACC_DRIVER, GPIO_LEVEL_LOW);//LOW
        }
        return 0;
    }
    return 0;
}

void car_blinkLight(void)
{
    data_getData()->speedCountTime = 30;//短时间内不进行相位检测
    lightState = car_isAccOn();//记录当前电门状态
    if(lightState && data_getData()->isWheelSpinning) //开电门且轮动状态则不要闪灯，为避免Q20车型抱死
    {
        return;
    }
    timer_startRepeat(TIMER_BLINK_LIGHT, TIMER_MS, 500, car_blinkLight_cb);
}

/*********************************************************************
*                  6线雅克特头盔锁开锁与关锁逻辑                       *
**********************************************************************/
L_BOOL car_isHelmetClose(void) //检测头盔锁销是否到位
{
    uint8_t level = 0;
    fibo_gpio_get(PIN_HELMET6_EXIS_DETECT, &level); //P30
    return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;
}

L_BOOL car_isHelmetAtPos(void) //检测头盔是否在位
{
    uint8_t level = 0;
    fibo_gpio_get(PIN_HELMET6_LOCK_DETECT, &level); //P31
    return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;
}

//判断头盔锁是否真正锁上，只有当头盔锁到位信号、头盔锁感应信号以及锁已复位同时满足才认为是真正锁上
static L_BOOL car_isHelmetRealLocked(void)
{
    if(car_isHelmetClose() && car_isHelmetAtPos())
    {
        return L_TRUE;
    }
    return L_FALSE;
}

static int car_unlockYaKeTeB06SHelmet_N_cb(void) //解锁复位电平
{
    control595(PIN_MASK_HELMET_P_DRIVER | PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_LOW);

    if(car_isHelmetClose()) //开锁操作后仍为关闭，则返回错误
    {
        userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_UNLOCK_ERR);
        return -1;
    }
    else
    {
        userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_UNLOCK);
    }
    return 0;
}

//解锁
int car_unlockYaKeTe06Helmet(void)
{
    control595(PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_LOW);
    control595(PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_HELMET, TIMER_MS, HELMET_TIME, car_unlockYaKeTeB06SHelmet_N_cb);
    return 0;
}

//上锁复位电平
static int car_lockYaKeTeB06SHelmet_P_cb(void)
{
    control595(PIN_MASK_HELMET_P_DRIVER | PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_LOW);
    
    if(!car_isHelmetAtPos() || !car_isHelmetClose()) //关锁操作后有任一信号不在位，则返回错误
    {
        userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_LOCK_ERR);
        car_unlockYaKeTe06Helmet(); //自动复位动作操作完毕后，如失败一定自动解锁
        return -1;
    }
    else if(car_isHelmetAtPos() && car_isHelmetClose()) //两个信号都在才清空HELMET_UNLOCK_WITH_AUTOLOCK状态
    {
        audio_play(AUDIO_HELMET_LOCK);
        userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_LOCK);

        if(setting.statusConf.helmetTargetStatus == HELMET_UNLOCK_WITH_AUTOLOCK)
        {
            setting.statusConf.helmetTargetStatus = HELMET_NULL;
            statusConf_save();
        }
    }
    return 0;
}

//上锁
void car_lockYaKeTe06Helmet(void)
{
    control595(PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_LOW);
    control595(PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_LOCK_HELMET, TIMER_MS, HELMET_TIME, car_lockYaKeTeB06SHelmet_P_cb);
}

/*********************************************************************
*                  其他头盔锁开锁与关锁逻辑                            *
**********************************************************************/
//完全释放
static int car_unlockBuckleHelmet_cb(void)
{
    control595(PIN_MASK_HELMET_N_DRIVER | PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_LOW);

    if(setting.statusConf.helmetTargetStatus == HELMET_UNLOCK_WITH_AUTOLOCK)
    {
        setting.statusConf.helmetTargetStatus = HELMET_NULL;
        statusConf_save();
    }
    return 0;
}

//上锁
static int car_unlockBuckleHelmet_wait_cb(void)
{
    control595(PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_HIGH);
    return timer_start(TIMER_SET_HELMET, TIMER_MS, 1000, car_unlockBuckleHelmet_cb);
}

int car_checkBuckHelmetState(void)
{
    static u8 checkTimes = 0;

    if(car_isHelmetLocked() == L_FALSE) //连续2秒检测到无感应信号，认为客户已经拿走头盔，执行复位动作
    {
        checkTimes++;
        if(checkTimes > (1000 / 100) * HELMET_CHECK_TIME)
        {
            checkTimes = 0;
            car_unlockBuckleHelmet_wait_cb();
            return 0;
        }
    }
    else
    {
        checkTimes = 0;
    }
    timer_start(TIMER_SET_HELMET, TIMER_MS, 100, car_checkBuckHelmetState);
    return 0;
}

//释放4s
static int car_unlockBuckleHelmet_P_cb(void)
{
    control595(PIN_MASK_HELMET_N_DRIVER | PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_LOW);

    if(setting.statusConf.helmetTargetStatus == HELMET_UNLOCK_WITH_AUTOLOCK) //打开四线头盔锁自动上锁逻辑
    {
        return timer_start(TIMER_SET_HELMET, TIMER_MS, 100, car_checkBuckHelmetState);
    }
    else
    {
        setting.statusConf.helmetTargetStatus = HELMET_NULL;
        statusConf_save();
        return 0;
    }
}

//解锁1s
static void car_unlockBuckleHelmet(void)
{
    control595(PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_HELMET, TIMER_MS, 1000, car_unlockBuckleHelmet_P_cb);
}

//释放4s
static int car_unlockXingQiHelmet_P_cb(void)
{
    control595(PIN_MASK_HELMET_N_DRIVER | PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_LOW);
    return timer_start(TIMER_SET_HELMET, TIMER_MS, 4000, car_unlockBuckleHelmet_wait_cb);
}

//解锁1s
static void car_unlockXingQiHelmet(void)
{
    control595(PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_HELMET, TIMER_MS, 1000, car_unlockXingQiHelmet_P_cb);
}

//头盔解锁
int car_unlockHelmet(void)
{
    if(timer_isTimerStart(TIMER_SET_HELMET)) //如果在执行动作则不要操作
    {
        return 0;
    }

    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET || setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_LOW)
    {
        car_unlockBuckleHelmet();
    }
    else if(setting.defaultConf.helmetType == TYPE_XINGQIHELMET) //星骑头盔锁
    {
        car_unlockXingQiHelmet();
    }
    else
    {
        LOG_ERROR("setting.helmetType = %d\n", setting.defaultConf.helmetType);
    }
    return 0;
}

//头盔解锁同步接口
int car_unlockHelmet_sync(u8 isAutoLock)
{
    if(isAutoLock)
    {
        setting.statusConf.helmetTargetStatus = HELMET_UNLOCK_WITH_AUTOLOCK; //自动上锁需要在头盔离开再在位后生效
    }
    else
    {
        setting.statusConf.helmetTargetStatus = HELMET_UNLOCK_ONLY;
    }
    statusConf_save(); //固化以应对操作过程中设备重启

    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX) //六线亚克特头盔锁
    {
        control595(PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_LOW);
        control595(PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_HIGH);

        fibo_taskSleep(HELMET_TIME);

        control595(PIN_MASK_HELMET_P_DRIVER | PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_LOW);

        if(setting.statusConf.helmetTargetStatus == HELMET_UNLOCK_ONLY)
        {
            setting.statusConf.helmetTargetStatus = HELMET_NULL;
            statusConf_save();
        }

        if(car_isHelmetClose()) //开锁操作后仍为关闭，则返回错误
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_UNLOCK_ERR);
            return -1;
        }
        else
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_UNLOCK);
        }
    }
    return 0;
}

//释放
static int car_lockHelmet_cb(void)
{
    control595(PIN_MASK_HELMET_P_DRIVER | PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_LOW);
    return 0;
}

//上锁1s
static void car_lockBuckleHelmet(void)
{
    control595(PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_HIGH);
    timer_start(TIMER_SET_HELMET, TIMER_MS, 1000, car_lockHelmet_cb);
}

//头盔上锁
int car_lockHelmet(void)
{
    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET || setting.defaultConf.helmetType == TYPE_XINGQIHELMET
    || setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_LOW)
    {
        LOG_DEBUG("[Car] lockBuckHelmet");
        car_lockBuckleHelmet();
    }
    else if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
    {
        if(timer_isTimerStart(TIMER_LOCK_HELMET) == L_FALSE)
        {
            car_lockYaKeTe06Helmet();
        }
    }
    return 0;
}

int car_lockHelmet_sync(u8 isAutoOpen)
{
    if(isAutoOpen)
    {
        setting.statusConf.helmetTargetStatus = HELMET_LOCK_WITH_AUTOOPEN; //自动开锁在上锁结束后如发现状态不正确则自动操作
    }
    else
    {
        setting.statusConf.helmetTargetStatus = HELMET_LOCK_ONLY;
    }
    statusConf_save(); //固化以应对操作过程中设备重启

    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
    {
        control595(PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_LOW);
        control595(PIN_MASK_HELMET_P_DRIVER, GPIO_LEVEL_HIGH);

        fibo_taskSleep(HELMET_TIME);

        control595(PIN_MASK_HELMET_P_DRIVER | PIN_MASK_HELMET_N_DRIVER, GPIO_LEVEL_LOW);

        if(setting.statusConf.helmetTargetStatus == HELMET_LOCK_ONLY)
        {
            setting.statusConf.helmetTargetStatus = HELMET_NULL;
            statusConf_save();
        }

        if(!car_isHelmetAtPos() || !car_isHelmetClose()) //关锁操作后有任一信号不在位，则返回错误
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_LOCK_ERR);
            if(setting.statusConf.helmetTargetStatus == HELMET_LOCK_WITH_AUTOOPEN) //关锁失败且打开自动开锁
            {
                car_unlockYaKeTe06Helmet();
                setting.statusConf.helmetTargetStatus = HELMET_NULL;
                statusConf_save();
            }
            return -1;
        }
        else if(car_isHelmetAtPos() && car_isHelmetClose()) //两个信号都在才认为关锁成功
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_LOCK);
        }
    }
    return 0;
}

/*
* 头盔锁，锁上到位，默认高电平在位
*/
L_BOOL car_isHelmetLocked(void)
{
    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX) //六线亚克特头盔锁
    {
        return car_isHelmetRealLocked();
    }
    else
    {
        uint8_t level = 0;
        fibo_gpio_get(PIN_HELMET4_LOCK_DETECT, &level);

        if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_LOW) //低到位
        {
            return level == GPIO_LEVEL_LOW ? L_TRUE : L_FALSE;
        }
        return level == GPIO_LEVEL_HIGH ? L_TRUE : L_FALSE;
    }
}

L_BOOL car_isHelmetConnected(void) //六线头盔锁X5系列目前没有头盔锁连接信号
{
    return L_FALSE;
}

L_BOOL car_isSpeedSingal(void)
{
    uint8_t pin_level = 0;
    fibo_gpio_get(PIN_SPEED_DETECT, &pin_level);//读速度端口的电平
    return pin_level;
}

L_BOOL car_setHandlebarsLED(u8 sw)
{
    if(!data_getData()->ble_state.isDA14580Alive)
    {
        return L_FALSE;
    }
    if(sw)
    {
        da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_HIGH);
    }
    else
    {
        da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_LOW);
    }
    return L_TRUE;
}

L_BOOL car_setRGBLed(u8 ledType, u8 onoff)
{
    if(!data_getData()->ble_state.isDA14580Alive)
    {
        return L_FALSE;
    }
    if(onoff)
    {
        if(ledType == CAR_REDLED)
        {   
            da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_HIGH);
        }
        else if(ledType == CAR_GREENLED)
        {
            LOG_DEBUG("wait deal");
        }
        else if(ledType == CAR_BLUELED)
        {
            LOG_DEBUG("wait deal");
        }
    }
    else
    {
        if(ledType == CAR_REDLED)
        {
            da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_LOW);
        }
        else if(ledType == CAR_GREENLED)
        {
            LOG_DEBUG("wait deal");
        }
        else if(ledType == CAR_BLUELED)
        {
            LOG_DEBUG("wait deal");
        }
    }
    return L_TRUE;
}
