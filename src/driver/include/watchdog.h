/*
 * watchdog.h
 *
 *  Created on: 2015/6/25
 *      Author: jk
 */

#ifndef USER_ELECTROMBILE_WATCHDOG_H_
#define USER_ELECTROMBILE_WATCHDOG_H_


typedef enum
{
	WD_WAKE,
	WD_SLEEP
}WatchDog_Env;
	
void startWatchdog(WatchDog_Env env);
void stopWatchdog(void);
void feedWatchdog(void);

#endif /* USER_ELECTROMBILE_WATCHDOG_H_ */

