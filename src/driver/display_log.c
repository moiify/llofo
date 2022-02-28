#include "uart.h"
#include "user_timer.h"//定时器头文件
#include <string.h>
#include "setting.h"
#include "display_log.h"

#define MAX_LINE  6
#define MAX_LINENUM  19
#define SPOT_LINE_SIZE  40
//！！！！需要根据平台修改串口输出函数
//ec20 ec25..
//x5广和通
#define DISPLAY_UART(fmt, ...) uart_print(fmt, ##__VA_ARGS__)//打印函数
#define PRINTF_CRLF()          DISPLAY_UART("\r\n") //回车换行

static DISPLAY_STRUCT displayBuf[MAX_LINE];//只能显示6行
static unsigned char clr_cnt = 0;

int display_log_handle(void)
{
    unsigned char i;
    for(i = 0; i < MAX_LINE; i++)
    {
        if(displayBuf[i].needShow == true)
        {
            PRINTF_CRLF();
            displayBuf[i].needShow = false;
            DISPLAY_UART("%s", displayBuf[i].str);
            PRINTF_CRLF();
            break;
        }
    }
    if(clr_cnt++ > 80 && setting.settingConf.displaylog)//8s清屏一次避免残留显示
    {
        clr_cnt = 0;
        DISPLAY_UART("CLR(0);");
        PRINTF_CRLF();        
    }
    return 0;
}

void display_log_timer_init(void)
{
    unsigned char i;
    for(i = 0; i < MAX_LINE; i++)
    {
        displayBuf[i].needShow = false;
    }

    timer_startRepeat(TIMER_DISPLAY_LOG, TIMER_MS, 100, display_log_handle);
    PRINTF_CRLF();
    DISPLAY_UART("CLR(0);");//清屏
    PRINTF_CRLF();
}

/*
传入字符串和显示行号  行号：0-5
*/
int display_log(char *str, unsigned char line)
{
    unsigned char tmp[6]={0};

    if(str == NULL || line >= MAX_LINE)//超过最大行
    {
        return -1;
    }

    memset(displayBuf[line].str, 0, LINE_BUFFER);//拼接格式
    strcat(displayBuf[line].str, "DCV32(0,");
    sprintf((char *)tmp,"%d,'", line*SPOT_LINE_SIZE);//显示行位置打包
    strcat(displayBuf[line].str, (const char *)tmp);//显示行号
    strncat(displayBuf[line].str,str, MAX_LINENUM);//显示内容
    strcat(displayBuf[line].str, "',1);");
    displayBuf[line].needShow = true;
    return 0;
}
