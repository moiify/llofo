//#include "global_io.h"

#include <stddef.h>     /* standard definition */
#include "uart.h"       /* uart definition */
#include "reg_uart.h"   /* uart register */
//#include "hcic_eif.h"   /* hci uart definition */


#include "rwble_config.h"

#include "gpio.h"
#include "uart1.h"
#include "timer0.h"
#include "user_timer.h"
#include "local_event.h"
#include "ble_uart_port.h"

#define NO_PWM            0x0       // PWM not used
#define RELOAD_100US      (20)      // 100us
void app_timer0_init(void)
{
    timer0_stop();

    // register callback function for SWTIM_IRQn irq
    timer0_register_callback(timer0_callback_func);

    // Enable TIMER0 clock
    set_tmr_enable(CLK_PER_REG_TMR_ENABLED);

    // Sets TIMER0,TIMER2 clock division factor to 8, so TIM0 Fclk is F = 16MHz/8 = 2Mhz
    set_tmr_div(CLK_PER_REG_TMR_DIV_8);

    // clear PWM settings register to not generate PWM
    timer0_set_pwm_high_counter(NO_PWM);
    timer0_set_pwm_low_counter(NO_PWM);
    // Set timer with 2MHz source clock divided by 10 so Fclk = 2MHz/10 = 200kHz
    timer0_init(TIM0_CLK_FAST, PWM_MODE_ONE, TIM0_CLK_DIV_BY_10);

    // reload value for 100us (T = 1/200kHz * RELOAD_100US = 0,000005 * 20 = 100us)
    timer0_set_pwm_on_counter(RELOAD_100US);

    // Enable SWTIM_IRQn irq
    timer0_enable_irq();
    
    // Start Timer0
    timer0_start();
    
}

/*
 * STRUCT DEFINITIONS
 *****************************************************************************************
 */


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

struct UART_TX_EN  uart2_tx_en = {0,0,0,{0}};
struct UART_TX_EN  *uart2_tx   = &uart2_tx_en;
struct UART_RX_EN  uart2_rx_en = {0,{0}};
struct UART_RX_EN  *uart2_rx   = &uart2_rx_en;

/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

static void uart2_TX_interrupt_proc( void )
{
    uart2_tx->pos++;
    uart2_tx->remain--;
    if (uart2_tx->remain <= 0)
    {        
        uart2_tx->pos = 0;
        uart2_tx->busyFlag = 0;
        memset(uart2_tx->buffer, 0, UART_BUFFER_LEN);//清空发送区
        
        uart2_thr_empty_setf( 0 );
        
        while (!uart2_thre_getf() || !uart2_temt_getf());
        GPIO_SetInactive(UART2_485_EN_PORT, UART2_485_EN_PIN);
//        GPIO_SetInactive(UART2_485_EN_PORT2, UART2_485_EN_PIN2);
    }
    else
    {
        uart2_txdata_setf(uart2_tx->buffer[uart2_tx->pos]);
    }
}

static int uart2_reciv_timerout_hd(void)
{
    send_data_toSIM868(uart2_rx->buffer, uart2_rx->length);
    uart2_rx->length = 0;
    return 0;
};

static void uart2_RX_interrupt_proc( void )
{
    while(uart2_data_rdy_getf())
    {
        if (uart2_rx->length < UART_BUFFER_LEN)
        {
            uart2_rx->buffer[uart2_rx->length++] = uart2_rxdata_getf();
        }
        else
        {
            uart2_rxdata_getf();
        }
    }

    timer_start(TIMER_UART2_RX_TIMEOUT, 20, uart2_reciv_timerout_hd);
}

static void uart2_init(uint8_t baudr, uint8_t mode )
{
    SetBits16( CLK_PER_REG, UART2_ENABLE, 1 ); /* 使能串口2时钟 */

    /*
     * ENABLE FIFO, REGISTER FCR IF UART2_LCR_REG.DLAB=0
     * XMIT FIFO RESET, RCVR FIFO RESET, FIFO ENABLED
     */
    SetBits16( UART2_LCR_REG, UART_DLAB, 0 );
    SetWord16( UART2_IIR_FCR_REG, 7 );

    /* DISABLE INTERRUPTS, REGISTER IER IF UART2_LCR_REG.DLAB=0 */
    SetWord16( UART2_IER_DLH_REG, 0 );

    /* ACCESS DIVISORLATCH REGISTER FOR BAUDRATE 115200, REGISTER UART_DLH/DLL_REG IF UART2_LCR_REG.DLAB=1 */
    SetBits16( UART2_LCR_REG, UART_DLAB, 1 );
    SetWord16( UART2_IER_DLH_REG, 0 );                      /* for serial clk 16MHz baudrate 115200 */
    SetWord16( UART2_IER_DLH_REG, (baudr >> 8) & 0xFF );
    SetWord16( UART2_RBR_THR_DLL_REG, baudr & 0xFF );       /* set baudrate ~115200  = serial_clk/(16*9) */

    /*
     * NO PARITY, 1 STOP BIT, 8 DATA LENGTH AND
     * SetWord16(UART2_LCR_REG,3);
     */
    SetWord16( UART2_LCR_REG, mode );
    //SetWord16( UART2_DLF_REG,dlf_value);
    /* ENABLE TX INTERRUPTS, REGISTER IER IF UART2_LCR_REG.DLAB=0 */
    SetBits16( UART2_LCR_REG, UART_DLAB, 0 );

    NVIC_DisableIRQ( UART2_IRQn );
    NVIC_SetPriority( UART2_IRQn, 1 );
    NVIC_EnableIRQ( UART2_IRQn );
    NVIC_ClearPendingIRQ( UART2_IRQn );
    
    //ke_timer_set( BLE_WORKING_TIMER, TASK_APP, 10 );//开启IO扫描 100ms
    uart2_rec_data_avail_setf( 1 );
}


void app_uart2_init( void )
{
    uart2_init(UART_BAUDRATE_9K6, 3);
}


/****************************************************************
* **串口IO保留初始�?
****************************************************************/
void uart2_reserve_gpio( void )
{
    RESERVE_GPIO( UART2_485_EN, UART2_485_EN_PORT, UART2_485_EN_PIN, PID_GPIO);
//    RESERVE_GPIO( UART2_485_EN2, UART2_485_EN_PORT2, UART2_485_EN_PIN2, PID_GPIO);
    RESERVE_GPIO( UART2_TX, UART2_TX_PORT, UART2_TX_PIN, PID_UART2_TX );
    RESERVE_GPIO( UART2_RX, UART2_RX_PORT, UART2_RX_PIN, PID_UART2_RX );
}


/****************************************************************
* **串口IO配置
****************************************************************/
void uart2_configPIN( void )
{
    GPIO_ConfigurePin(UART2_485_EN_PORT, UART2_485_EN_PIN, OUTPUT, PID_GPIO, false);
    GPIO_ConfigurePin(UART2_TX_PORT, UART2_TX_PIN, OUTPUT, PID_UART2_TX, false);
    GPIO_ConfigurePin(UART2_RX_PORT, UART2_RX_PIN, INPUT_PULLUP, PID_UART2_RX, false);
}

#ifdef __GNUC__
void __real_UART2_Handler(void);
#else
void $Super$$UART2_Handler(void);
#endif

#ifdef __GNUC__
void __wrap_UART2_Handler(void)
#else
void $Sub$$UART2_Handler(void)
#endif
{
    uint32_t idd;
    idd = 0x0F & GetWord32( UART2_IIR_FCR_REG );
    if ( idd != NO_INT_PEND )
    {
        switch ( idd )
        {
        case UART_TIMEOUT:
            //串口接收错误,不进行处理
            break;
            
        case RECEIVED_AVAILABLE:
            uart2_RX_interrupt_proc();
            break;

        case THR_EMPTY:
            uart2_TX_interrupt_proc();
            break;

        default:
            break;
        }
    }
}

uint8_t uart2_isUartBusy(void)
{
    return uart2_tx->busyFlag;
}

void uart2_launch(void)
{
    if(!uart2_tx->busyFlag)
    {
        uart2_tx->busyFlag = 1;
        uart2_txdata_setf(uart2_tx->buffer[uart2_tx->pos]);
        uart2_thr_empty_setf(1);// 使能中断
    }
}

void uart2_sendData( uint8_t *data, uint16_t length )
{
    if (uart2_tx->busyFlag)
    {
        if(uart2_tx->remain > 0)
        {
            uint16_t bufferLen = uart2_tx->pos + uart2_tx->remain;
            if(length + bufferLen <= UART_BUFFER_LEN) //承担不住的丢掉
            {
                uart2_thr_empty_setf(0);// 关掉中断
                
                uart2_tx->remain += length;
                memcpy(uart2_tx->buffer + bufferLen, data, length);
            }
                        
            uart2_thr_empty_setf(1);// 使能中断
            return;
        }
        else 
        {
            uart2_tx->remain = 0;
            uart2_tx->busyFlag = 0;
        }
    }
    
    if (length == 0 || length > UART_BUFFER_LEN)
    {
        return;
    }
    
    uart2_tx->busyFlag = 1;
    uart2_tx->pos      = 0;
    uart2_tx->remain   = length;
    memcpy( uart2_tx->buffer, data, length );
    uart2_txdata_setf(uart2_tx->buffer[uart2_tx->pos]);

    GPIO_SetActive(UART2_485_EN_PORT, UART2_485_EN_PIN);
//    GPIO_SetActive(UART2_485_EN_PORT2, UART2_485_EN_PIN2);
    uart2_thr_empty_setf(1);
}

