
#ifndef SOFTWARE_WATCHDOG_H_
#define SOFTWARE_WATCHDOG_H_

void softwatchdog_Init(void);
void softwatchdog_start(char type, unsigned int time); //时间单位为s
void softwatchdog_stop(char type);
void softwatchdog_feed(char type);
void softwatchdog_Thread(void *argument);

#endif /* __SOFTWARE_WATCHDOG_H__ */

