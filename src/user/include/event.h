/*
 * event.h
 *
 *  Created on: 2015/6/25
 *      Author: jk
 */

#ifndef USER_ELECTROMBILE_EVENT_H_
#define USER_ELECTROMBILE_EVENT_H_

void event_initial(void);
int  event_long_loop(void);
int  event_fsm_running(void);

int event_checkActiveFreqSOC(void);

#endif /* USER_ELECTROMBILE_EVENT_H_ */
