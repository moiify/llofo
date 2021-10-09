/*
 * user_at.h
 *
 *  Created on: 2020.04.03
 *      Author: lc
 */

#ifndef __USER_AT_H__
#define __USER_AT_H__

typedef enum
{
    AT_RES_CONTRINUE= -1,
    AT_RES_FINISHED = 0
} ATResult_enum;

/****************************************************************************
* Function : modem_register
* Description: register one modem AT command.
* Parameters:
*     cmd   AT command, MUST end with '\r'[CR].
*     fun   callback function.
* Returns: void
*
* NOTE:
*   In callback function, if the at command needs multi-result, if command not
*   end, please retrun -1, else return 0.
*   In callback function, you can proc the param buf, but if the callback function
*    needs the next result, the param cmd must be reserved in buf.
*****************************************************************************/
typedef ATResult_enum (*AT_CB_PROC)(uint8_t isTimeout, char *buf, uint16_t len);
typedef int (*MODEM_CB_PROC)(char *buf, uint16_t len);

void at_res_callback(uint8_t *buf, uint16_t len);

ATResult_enum at_default_cb(uint8_t isTimeout, char *buf, uint16_t len);
void at_run(const char *cmd, AT_CB_PROC fun);
void at_runwithTimeout(const char *cmd, AT_CB_PROC fun, uint8_t timeout);

#define CR  "\r"    //CR (carriage return)
#define LF  "\n"    //LF (line feed - new line)

#define MODEM_TEST_CMD  "=?"
#define MODEM_READ_CMD  "?"
#define MODEM_WRITE_CMD "="

#define MODEM_AT_MAX_LEN (512)  //because http download need extra 32 byte
#define MODEM_READF_SIZE (1024)

#endif /* __USER_AT_H__ */

