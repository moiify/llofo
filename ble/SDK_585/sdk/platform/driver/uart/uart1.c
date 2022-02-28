
//#include "global_io.h"

#include <stddef.h>     /* standard definition */
#include "uart.h"       /* uart definition */
#include "reg_uart.h"   /* uart register */
//#include "hcic_eif.h"   /* hci uart definition */

#include "arch.h"
#include "app_task.h"
#include "rwble_config.h"

#include "gpio.h"
#include "uart1.h"
#include "user_timer.h"
#include "ble_uart_port.h"
#include "local_event.h"

/*
 * STRUCT DEFINITIONS
 *****************************************************************************************
 */
    
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
struct UART_TX_EN  uart_tx_en = {0,0,0,{0}};
struct UART_TX_EN  *uart1_tx   = &uart_tx_en;
struct UART_RX_EN  uart_rx_en = {0,{0}};
struct UART_RX_EN  *uart1_rx   = &uart_rx_en;

/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
static void uart1_TX_interrupt_proc( void )
{
    uart1_tx->pos++;
    uart1_tx->remain--;
    if(uart1_tx->remain > 0)
    {
        uart_txdata_setf(uart1_tx->buffer[uart1_tx->pos]);
    }
    else
    {
        uart_thr_empty_setf(0);
        uart1_tx->pos = 0;
        uart1_tx->remain = 0;
        uart1_tx->busyFlag = 0;     
        while (!uart_thre_getf() || !uart_temt_getf());
    }
}

static int uart1_reciv_timerout_hd(void)
{
    reciv_data_fromSIM868_cb((const uint8_t *)uart1_rx->buffer, uart1_rx->length);    
    uart1_rx->length = 0;
    return 0;
};

static void uart1_RX_interrupt_proc( void )
{
    while (uart_data_rdy_getf())
    {
        if (uart1_rx->length < UART_BUFFER_LEN)
        {
            uart1_rx->buffer[uart1_rx->length++] = uart_rxdata_getf();
        }
        else  
        {
            uart_rxdata_getf();
        }
    }
    
    timer_start(TIMER_UART1_RX_TIMEOUT, 20, uart1_reciv_timerout_hd);
}

static void uart1_init( uint8_t baudr, uint8_t mode )
{
    SetBits16( CLK_PER_REG, UART1_ENABLE, 1 ); /* 使能串口1时钟 */

    /*
     * ENABLE FIFO, REGISTER FCR IF UART_LCR_REG.DLAB=0
     * XMIT FIFO RESET, RCVR FIFO RESET, FIFO ENABLED
     */
    SetBits16( UART_LCR_REG, UART_DLAB, 0 );
    SetWord16( UART_IIR_FCR_REG, 7 );

    /* DISABLE INTERRUPTS, REGISTER IER IF UART_LCR_REG.DLAB=0 */
    SetWord16( UART_IER_DLH_REG, 0 );

    /* ACCESS DIVISORLATCH REGISTER FOR BAUDRATE 115200, REGISTER UART_DLH/DLL_REG IF UART_LCR_REG.DLAB=1 */
    SetBits16( UART_LCR_REG, UART_DLAB, 1 );
    SetWord16( UART_IER_DLH_REG, 0 );                      /* for serial clk 16MHz baudrate 115200 */
    SetWord16( UART_IER_DLH_REG, (baudr >> 8) & 0xFF );
    SetWord16( UART_RBR_THR_DLL_REG, baudr & 0xFF );       /* set baudrate ~115200  = serial_clk/(16*9) */

    /*
     * NO PARITY, 1 STOP BIT, 8 DATA LENGTH AND
     * SetWord16(UART_LCR_REG,3);
     */
    SetWord16( UART_LCR_REG, mode );
	//SetWord16( UART_DLF_REG, dlf_value);
    /* ENABLE TX INTERRUPTS, REGISTER IER IF UART_LCR_REG.DLAB=0 */
    SetBits16( UART_LCR_REG, UART_DLAB, 0 );

    NVIC_DisableIRQ( UART_IRQn );
    NVIC_SetPriority( UART_IRQn, 1 );
    NVIC_EnableIRQ( UART_IRQn );
    NVIC_ClearPendingIRQ( UART_IRQn );
	
    uart_rec_data_avail_setf( 1 );
}


void app_uart1_init( void )
{
    uart1_init( UART_BAUDRATE_115K2, 3 );
}

/****************************************************************
* **串口IO保留初始值
****************************************************************/
void uart1_reserve_gpio( void )
{
    RESERVE_GPIO( UART1_TX, UART1_TX_PORT, UART1_TX_PIN, PID_UART1_TX );
    RESERVE_GPIO( UART1_RX, UART1_RX_PORT, UART1_RX_PIN, PID_UART1_RX );
}


/****************************************************************
* **串口IO配置
****************************************************************/
void uart1_configPIN( void )
{
    GPIO_ConfigurePin( UART1_TX_PORT, UART1_TX_PIN, OUTPUT, PID_UART1_TX, false );
    GPIO_ConfigurePin( UART1_RX_PORT, UART1_RX_PIN, INPUT_PULLUP, PID_UART1_RX, false );
}

#ifdef __GNUC__
void __real_UART_Handler(void);
#else
void $Super$$UART_Handler(void);
#endif

#ifdef __GNUC__
void __wrap_UART_Handler(void)
#else
void $Sub$$UART_Handler(void)
#endif
{
    uint32_t idd;
    idd = 0x0F & GetWord32( UART_IIR_FCR_REG );
    if ( idd != NO_INT_PEND )
    {
        switch ( idd )
        {
        case UART_TIMEOUT:
            //串口接收错误,不进行处理
            break;
            
        case RECEIVED_AVAILABLE:
            uart1_RX_interrupt_proc();
            break; 

        case THR_EMPTY:
            uart1_TX_interrupt_proc();
            break;

        default:
            break;
        }
    }
}

uint8_t uart1_isUartBusy(void)
{
    return uart1_tx->busyFlag;
}

void uart1_launch(void)
{
    if(!uart1_tx->busyFlag && uart1_tx->remain > 0)
    {
        uart1_tx->busyFlag  = 1;
        uart_txdata_setf(uart1_tx->buffer[uart1_tx->pos]);
        uart_thr_empty_setf(1);// 使能中断
    }
}

/*
* send data to simcom
*/
void uart1_sendData( uint8_t *data, uint16_t length )
{
    if ( length == 0 || length > UART_BUFFER_LEN )
    {
        return;
    }
    if (uart1_tx->busyFlag)
    {
        uart_thr_empty_setf(0);// 关掉中断
        if(uart1_tx->remain > 0)
        {
            uint16_t bufferLen = uart1_tx->pos + uart1_tx->remain;
            if(length + bufferLen <= UART_BUFFER_LEN) //承担不住的丢掉
            {
                uart_thr_empty_setf(0);// 关掉中断
                
                uart1_tx->remain += length;
                memcpy(uart1_tx->buffer + bufferLen, data, length);
            }
                        
            uart_thr_empty_setf(1);// 使能中断
            return;
        }
        else 
        {
            uart1_tx->remain = 0;
            uart1_tx->busyFlag = 0;
        }
    }

    uart1_tx->pos       = 0;
    uart1_tx->busyFlag  = 1;
    uart1_tx->remain    = length;
    memcpy( uart1_tx->buffer, data, length );
    uart_txdata_setf(uart1_tx->buffer[uart1_tx->pos]);
    uart_thr_empty_setf(1);
}


/*
*与uart1_launch配合使用
*如果uart busy 则数据直接进队
*如果uart not busy 则初始化队列，然后让数据进队，且置位busy，但并不马上开始
*    然后在下一次uart1_sendData 才开始真正传数据
*和 uart1_sendData 唯一的区别是 不主动开启中断
*/
void uart1_enqueneData(const uint8_t *data, uint16_t length)
{
    if ( length == 0 || length > UART_BUFFER_LEN )
    {
        return;
    }

    if (uart1_tx->busyFlag)
    {
        /* 如果标志位表示当前仍在发数据 */
        uart_thr_empty_setf(0); //关闭中断

        /* 剩余buffer不为空, 向buffer中追加数据 */
        if(uart1_tx->remain > 0)
        {
            uint16_t bufferLen = uart1_tx->pos + uart1_tx->remain;
            if(length + bufferLen <= UART_BUFFER_LEN) //承担不住的丢掉
            {
                uart1_tx->remain += length;
                memcpy(uart1_tx->buffer + bufferLen, data, length);
            }
            uart_thr_empty_setf(1);// 只有开始时使能了中断 才重新使能中断
            return;
        }
        else 
        {
            /* 异常情况 在此打个patch */
            uart1_tx->remain = 0;
            uart1_tx->busyFlag = 0;
        }

    }
    
    /* 如果当前没有在发数据 那么等待唤醒868后进行数据发送 */
    uint16_t bufferLen = uart1_tx->pos + uart1_tx->remain;
    if(length + bufferLen <= UART_BUFFER_LEN) //承担不住的丢掉
    {
        uart1_tx->remain += length;
        memcpy(uart1_tx->buffer + bufferLen, data, length);
    }
}

