#include "adc.h"
#include "gpio.h"
#include "nvds.h"
#include "uart1.h"
#include "decode.h"
#include "aes_api.h"
#include "version.h"
#include "setting.h"
#include "ble_proc.h"
#include "protocol.h"
#include "user_timer.h"
#include "local_event.h"
#include "ble_adv_proc.h"
#include "ble_scan_proc.h"
#include "ble_uart_port.h"
#include "app_easy_timer.h"
#include "user_sps_device.h"
#include "ke_msg.h"

static uint8_t g_connection_id = 0;
/************************************************************************
*   功能：将一个十六进制字节串转换成 ASCII 码表示的十六进制的字符串
*   输入参数：pHex    -- 十六进制数字节串首地址
*            pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            nLen    -- 要转换的十六进制数的长度（字节数）
*   输出参数：None
*   注：  转换后的结果全部是大写 ASCII 表示的十六进制数
*   例：{ 0x23, 0x3A, 0x46, 0x4C, 0x52 } => “233A464C52”
************************************************************************/
void Hex2String(unsigned char *pHex, unsigned char *pString, int hexLen)
{
    int i = 0, j = 0;
    unsigned char Nibble[2];

    for (i = 0; i < hexLen; i++)
    {
        Nibble[0] = (pHex[i] & 0xF0) >> 4;
        Nibble[1] = pHex[i] & 0x0F;
        for (j = 0; j < 2; j++)
        {
            if (Nibble[j] < 10)
            {
                Nibble[j] += 0x30;
            }
            else
            {
                if (Nibble[j] < 16)
                    Nibble[j] = Nibble[j] - 10 + 'A';
            }
            *pString++ = Nibble[j];
        }
    }
}


/****************************************************************************
*   功能：将一个 ASCII 码表示的十六进制字符串转换成十六进制的字节串
*   输入参数：pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            pHex   -- 十六进制数字节串首地址
*            nLen   -- 要转换的 ASCII 码表示的十六进制字符串的长度（字节数）
*   输出参数：None
*   注：  要求输入的 ASCII 码表示的十六进制数的字符个数必须为偶数，除了是1 - 9 和 A(a) - F(f) 以外没有别的字符
*   例： “233A464C52” => { 0x23, 0x3A, 0x46, 0x4C, 0x52 }
****************************************************************************/
void String2Hex(unsigned char *pString, unsigned char *pHex, int stringLen)
{
    int nHexLen = 0;
    int i = 0, j = 0;
    
    if (stringLen % 2)
    {
        return;
    }

    nHexLen = stringLen / 2;
    for (i = 0; i < nHexLen; i++)
    {
        unsigned char Nibble[2];
        Nibble[0] = *pString++;
        Nibble[1] = *pString++;
        for (j = 0; j < 2; j++)
        {
            if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
                Nibble[j] = Nibble[j] - 'A' + 10;
            else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
                Nibble[j] = Nibble[j] - 'a' + 10;
            else if (Nibble[j] >= '0' && Nibble[j] <= '9')
                Nibble[j] = Nibble[j] - '0';
            else
                return;
        }
        pHex[i] = Nibble[0] << 4;   // Set the high nibble
        pHex[i] |= Nibble[1];   //Set the low nibble
    }
}

void GPIO_commonInit(void)
{
// -----------------------------------------  GPIO PORT 0  ----------------------------------------- //
    GPIO_ConfigurePin( GPIO_PORT_0, PIN_ADC_BAT,        OUTPUT,  PID_GPIO, false); // NC 默认电阻没焊接，由L610直接采集
    GPIO_ConfigurePin( GPIO_PORT_0, PIN_ADC_TMP,        OUTPUT,  PID_GPIO, false); // NC
    GPIO_ConfigurePin( GPIO_PORT_0, GPIO_PIN_6,         OUTPUT,  PID_GPIO, false);
    GPIO_ConfigurePin( GPIO_PORT_0, GPIO_PIN_7,         OUTPUT,  PID_GPIO, false);
// ------------------------------------------ GPIO PORT 1 ------------------------------------------ //
    GPIO_ConfigurePin( GPIO_PORT_1, GPIO_PIN_0,         INPUT_PULLDOWN,  PID_GPIO, false);  //预留输入管脚
    GPIO_ConfigurePin( GPIO_PORT_1, GPIO_PIN_1,         INPUT_PULLDOWN,  PID_GPIO, false);  //预留输入管脚
    GPIO_ConfigurePin( GPIO_PORT_1, GPIO_PIN_2,         OUTPUT,  PID_GPIO, true);  //rst
    GPIO_ConfigurePin( GPIO_PORT_1, GPIO_PIN_3,         INPUT_PULLDOWN,  PID_GPIO, false);  //预留输入管脚

// ------------------------------------------ GPIO PORT 2 ------------------------------------------ //
    GPIO_ConfigurePin( GPIO_PORT_2, PIN_SGM66052_EN,        OUTPUT, PID_GPIO, false);   //默认拉高 等待L610命令
    GPIO_ConfigurePin( GPIO_PORT_2, GPIO_PIN_3,      	    OUTPUT, PID_GPIO, false);   //L610的weakup引脚 保持拉低就行
    GPIO_ConfigurePin( GPIO_PORT_2, GPIO_PIN_5,             OUTPUT, PID_GPIO, true);    //开机用的VBUS使能 开机后低电平 其他时间不用操作

    GPIO_ConfigurePin( GPIO_PORT_2, PIN_595_SHIFT_CLK,      OUTPUT, PID_GPIO, false);   //NC
    GPIO_ConfigurePin( GPIO_PORT_2, PIN_595_LATCH_CLK,      OUTPUT, PID_GPIO, false);   //NC
    GPIO_ConfigurePin( GPIO_PORT_2, PIN_595_DATA_DRIVER,    OUTPUT, PID_GPIO, false);   //NC
	GPIO_ConfigurePin( GPIO_PORT_2, GPIO_PIN_1, 			OUTPUT, PID_GPIO, false);	//NC

    GPIO_ConfigurePin( GPIO_PORT_2, GPIO_PIN_4,         INPUT_PULLDOWN,  PID_GPIO, false);  //预留输入管脚
    GPIO_ConfigurePin( GPIO_PORT_2, GPIO_PIN_6,         INPUT_PULLDOWN,  PID_GPIO, false);  //预留输入管脚
    GPIO_ConfigurePin( GPIO_PORT_2, GPIO_PIN_7,         INPUT_PULLDOWN,  PID_GPIO, false);  //预留输入管脚

}

void timer0_callback_func(void)
{
	;
}


// 蓝牙钥匙模块
static int uart_keys_config_rsp(uint8_t* data, uint16_t len)
{
    if(0 != len % PKE_KEY_ID_LEN)
    {
        return 0;
    }

    if(len / PKE_KEY_ID_LEN > 5)
    {
        return 0;
    }

    setting.scan.keyNum = len/PKE_KEY_ID_LEN;
    memcpy(setting.scan.cfgedKeyID, (const void*)data, len);
    setting.isPKEType = 1;
   //如果收到钥匙配置命令，自动把模式切到pkekey
    user_scan_start();    
    timer_start(TIMER_SCAN_TIMEOUT, USER_SCAN_TIMEOUT_MS, ble_scan_timeout_callback);
    return 0;
}

// 595
static void car_control595_delay(void)
{
    uint32_t times = 10;
    while(times--)
    {
        __nop();
    }
}

void car_control595(uint8_t PIN_MASK)
{
    uint8_t i = 0;
    uint8_t state = PIN_MASK;

    for(i = 0; i < 8; i++)
    {
        //从Q7->Q0装载
        uint8_t bit = state >> 7;
        if(bit)
        {
            GPIO_SetActive(GPIO_PORT_2, PIN_595_DATA_DRIVER);
        }
        else
        {
            GPIO_SetInactive(GPIO_PORT_2, PIN_595_DATA_DRIVER);
        }
        state = state << 1;

        GPIO_SetActive(GPIO_PORT_2, PIN_595_SHIFT_CLK);//上升沿
        car_control595_delay();
        GPIO_SetInactive(GPIO_PORT_2, PIN_595_SHIFT_CLK);
        car_control595_delay();
    }

    /*位移寄存器数据准备完毕,转移到存储寄存器输出*/
    GPIO_SetActive(GPIO_PORT_2, PIN_595_LATCH_CLK);//上升沿
    car_control595_delay();
    GPIO_SetInactive(GPIO_PORT_2, PIN_595_LATCH_CLK);
    car_control595_delay();
}

static int uart_control595(uint8_t* data, uint16_t len)
{
    if(len != 1)return -1;
    uart_sendMsgtoSIM868(BLE_CONF, BIO_CONTROL_595, 1, &data[0]);
    car_control595(data[0]);
    return 0;
}

void wakeup_others_init(void)
{
    GPIO_ConfigurePin( WAKEUP_SIM868_PORT, WAKEUP_SIM868_PIN, OUTPUT, PID_GPIO, false);
}

static int wakeup_SIM868_timeOut_cb(void)
{
    GPIO_SetInactive(WAKEUP_SIM868_PORT, WAKEUP_SIM868_PIN);
    uart1_launch();
    return 0;
}
void wakeup_SIM868(void)
{
    GPIO_SetActive(WAKEUP_SIM868_PORT, WAKEUP_SIM868_PIN);
    timer_start(TIMER_AWAKE_SIMCOM, 30, wakeup_SIM868_timeOut_cb);
}

//使能5V输出持续10秒钟
static int enable_VBUS_cb(void)
{
    //GPIO_SetInactive(GPIO_PORT_2, PIN_VBUS_DRIVER);
    return 0;
}
void enable_VBUS(void)
{
    GPIO_SetActive(GPIO_PORT_2, PIN_VBUS_DRIVER);
    timer_start(TIMER_ENABLE_VBUS, 10000, enable_VBUS_cb);
}

void event_onConnection(void)
{
    uart_sendNotify(BLE_CONF, BIO_NOTIFY, NOTIFY_CONNECTED);
}

void event_setConnectionID(uint8_t connection_id)
{
    g_connection_id = connection_id;
}

void event_onDisconnection(void)
{
    uart_sendNotify(BLE_CONF, BIO_NOTIFY, NOTIFY_DISCONNECTED);
}

static int uart_getVersionRsp(uint8_t* data, uint16_t len)
{
    if(len != 0)return -1;
    BLE_VERSION_NUM version = {htonl(VERSION_NUM)};
    uart_sendMsgtoSIM868(BLE_CONF, BLE_VERSION, sizeof(BLE_VERSION_NUM), (uint8_t *)&version);
    return 0;
}

static int uart_setHeartbeat(uint8_t* data, uint16_t len)
{
    if(len != 1)return -1;
    if(data[0] == 1 || data[0] == 0)
    {
        setting.isHeartBeatOn = data[0];
    }
    return 0;
}

static int uart_reset_rsp(uint8_t* data, uint16_t len)
{
    if(len != 0)return -1;
    app_gapm_reset_op();
    return 0;
}

static int uart_updateParam_rsp(uint8_t* data, uint16_t dataLen)
{
    ST_MSG_BLE_CONFIG *ble_config = (ST_MSG_BLE_CONFIG *)data;
    // 兼容无协议配置字段(u8)的包（默认为小安协议）
    if( dataLen != sizeof(ST_MSG_BLE_CONFIG) && dataLen != (sizeof(ST_MSG_BLE_CONFIG) - 1) )
    {
        return BLE_FAILED;
    }

    if(SW_IS_ADV & ble_config->sw)
    {        
        setting.mode = BLE_MODE_ADV;
        setting.adv.nameLen = strlen((const char *)ble_config->name);
        memcpy(setting.adv.name, ble_config->name, setting.adv.nameLen);

        setting.adv.meanufDataLen = BD_ADDR_LEN;
        setting_set_address_from_imei(ble_config->imei);
        memcpy(setting.adv.meanufData, setting.address, BD_ADDR_LEN);
    }
    if(SW_IS_PKEKEY & ble_config->sw)
    {
        setting.isPKEType = 1;
    }
    
    if(dataLen == sizeof(ST_MSG_BLE_CONFIG))
    {
        setting.protocol_type = ble_config->protocol_type;
    }
    else // 默认小安协议处理
    {
        setting.protocol_type = PROTOCOL_XIAOAN;
    }
    
    setting.isconnected = 0; //配置蓝牙模式时，置位未连接，重新开启广播
    app_gapm_reset_op();
    return BLE_SUCCESS;
}

static int uart_pingACK(uint8_t* data, uint16_t len)
{
    ble_resetMissHeartBeatTime();
    return 0;
}

static int uart_readIO(uint8_t* data, uint16_t len)
{
    uint8_t state = 0x00;
    if(len != 0)return -1;
    //if(GPIO_GetPinStatus(GPIO_PORT_2, GPIO_PIN_3))state |= (1 << 0);
    if(GPIO_GetPinStatus(GPIO_PORT_2, GPIO_PIN_4))state |= (1 << 1);
    if(GPIO_GetPinStatus(GPIO_PORT_2, GPIO_PIN_6))state |= (1 << 2);
    if(GPIO_GetPinStatus(GPIO_PORT_2, GPIO_PIN_7))state |= (1 << 3);
    if(GPIO_GetPinStatus(GPIO_PORT_1, GPIO_PIN_0))state |= (1 << 4);
    if(GPIO_GetPinStatus(GPIO_PORT_1, GPIO_PIN_1))state |= (1 << 5);
    uart_sendMsgtoSIM868(BLE_CONF, BIO_READ_IOLEVEL, 1, &state);
    return 0;
}

/*
收到610通知BLE OTA STATE
static int uart_BLE_OTA_Upgrade_State(uint8_t* data, uint16_t len)
{
	if(len == 1)
	{
		setting.BleUpgradeState = data[0];//1为升级中，0 无升级
		if(setting.BleUpgradeState == 1)
		{
			timer_stop(TIMER_SCAN_TIMEOUT);
			ble_scanStop_CB();
		}
	}
	else
	{
		uart_debug(data,len);
	}
	return 0;
}
*/

static int uart_DisconnectBLE(uint8_t* data, uint16_t len)
{
    app_easy_gap_disconnect(g_connection_id);
    uart_sendMsgtoSIM868(BLE_CONF, BIO_DISCONNECT_REQ, 0, NULL);
    return 0;
}

static int uart_debug(uint8_t *data, uint16_t len)
{
    // debug
    uart_sendMsgtoSIM868(BLE_CONF, BIO_LOG, len, data);

    return 0;
}

static int uart_setPinLevel(uint8_t *data, uint16_t len)
{
    uint8_t port = data[0];
    uint8_t pin = data[1];
    uint8_t level = data[2];

    if(port > GPIO_PORT_3_REMAP)
    {
        return -1;
    }
    if(pin > GPIO_PIN_9)
    {
        return -1;
    }

    if(level == 0)
    {
        GPIO_SetInactive((GPIO_PORT)port, (GPIO_PIN)pin);
    }
    else if(level == 1)
    {
        GPIO_SetActive((GPIO_PORT)port, (GPIO_PIN)pin);
    }
    return 0;
}

static int uart_getSecondBootFlash(uint8_t* data, uint16_t len)
{
    static uint8_t checkResult = 0X01;
    static uint8_t flashData[50] = {0X00};
    static uint8_t tempData[50] = {0X00};
    memset(flashData, 0, sizeof(flashData));
    nvds_read_data_from_otp(0X7F80000, flashData, sizeof(flashData));
    //uart_sendMsgtoSIM868(BLE_CONF, BIO_GET_SECONDBOOT, sizeof(flashData), flashData);
    if(0 == memcmp(flashData, tempData, sizeof(flashData)))
    {
        checkResult = 1;//secondBootLoader未下载
    }
    else
    {
        checkResult = 0;//secondBootLoader下载了
    }
    uart_sendMsgtoSIM868(BLE_CONF, BIO_GET_SECONDBOOT, sizeof(checkResult), &checkResult);
    return 0;
}

static int uart_rstMcu(uint8_t* data, uint16_t len)
{
    ble_setNeedRstMcu();
    return 0;
}

typedef int (* UART_CONFIG_FUN)(uint8_t *data, uint16_t length);
typedef struct
{
    uint8_t cmd;
    UART_CONFIG_FUN func;
} UART_CONFIG_PROC;

UART_CONFIG_PROC uart_config_handle[] =
{
//    {BIO_CONTROL_595,          uart_control595},
    {BIO_READ_IOLEVEL,         uart_readIO},
    {BIO_REBOOT,               uart_reset_rsp},
    {BLE_VERSION,              uart_getVersionRsp},
    {BIO_SET_BEATHEART,        uart_setHeartbeat},
    {BIO_SET_CONFIG_V2,        uart_updateParam_rsp},
    {BIO_DISCONNECT_REQ,       uart_DisconnectBLE},
    {BIO_PING,                 uart_pingACK},
//    {BIO_BLE_START_SCAN_DD,    uart_StartScan}, //支持全主从一体之后,不需要该命令
// PIN func
//    {BIO_ADC,                  uart_sendAdcValue},
	{BIO_SET_PIN_LEVEL, 	   uart_setPinLevel},

// module func
    {PKE_KEYS_CONFIG,          uart_keys_config_rsp},
    {BIO_GET_SECONDBOOT,       uart_getSecondBootFlash},
    {BIO_RST_MCU,              uart_rstMcu},
};


void uart_config_proc(uint8_t *data, uint16_t length)
{
    MSG_HEADER *msg = (MSG_HEADER *)data;

    if(!uart_isCheckSumPass(msg))
    {
        return;
    }

    for(uint8_t i = 0; i < sizeof(uart_config_handle) / sizeof(uart_config_handle[0]); i++)
    {
        if(msg->cmd == uart_config_handle[i].cmd)
        {
            UART_CONFIG_FUN fun = uart_config_handle[i].func;
            if(fun)
            {
                fun(msg->data, msg->len);
                return;
            }
        }
    }

    uart_sendNotify(BLE_CONF, msg->cmd, CMD_NOT_EXIST);
    return;
}

static uint8_t uart_getCheckSum(MSG_HEADER *msg)
{
    uint8_t i = 0;
    uint8_t checksum = msg->address + msg->cmd + msg->len;
    for(i = 0; i < msg->len; i++)
    {
        checksum += msg->data[i];

    }
    return checksum;
}

void uart_sendMsgtoSIM868(uint8_t address, uint8_t cmd, uint8_t len, uint8_t *data)
{
    uint8_t buf[256] = {0};
    MSG_HEADER *msg = (MSG_HEADER *)buf;

    msg->signature = 0x55AA;
    msg->address = address;
    msg->cmd = cmd;
    msg->len= len;

    if(data && len)
    {
        memcpy(msg->data, data, len);
    }
    msg->data[len] = uart_getCheckSum(msg);
    send_data_toSIM868((const uint8_t *)msg, sizeof(MSG_HEADER) + msg->len + 1);
}

int uart_sendNotify(uint8_t address, uint8_t cmd, uint8_t err)
{
    uart_sendMsgtoSIM868(address, cmd, 1, &err);
    return 0;
}

int uart_print_SIM868(uint8_t *data, uint8_t dataLen)
{
    uart_sendMsgtoSIM868(BLE_CONF, BIO_LOG, dataLen, data);
    return 0;
}


