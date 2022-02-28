/*
 * display_log.h
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */
#ifndef __USER_DISPLAY_LOG_H__
#define __USER_DISPLAY_LOG_H__

#define LINE_BUFFER 32

typedef struct
{
    unsigned char needShow;
    char str[LINE_BUFFER];
}__attribute__((__packed__))DISPLAY_STRUCT;

int display_log(char *str, unsigned char line);
void display_log_timer_init(void);

#endif /* __USER_LOG_H__ */


