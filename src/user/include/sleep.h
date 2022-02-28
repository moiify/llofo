/*
 * sleep.h
 *
 *  Created on: 2017/08/26
 *      Author: lc
 */

#ifndef __SLEEP_H__
#define __SLEEP_H__

/*
* 睡眠说明:
*    开始唤醒都在main进行触发 main -> gps -> detect, 最终进入睡眠状态都在main进行触发:detect -> gps -> main
*/
void sleep_awakeEnvironment(void);
void sleep_sleepEnvironment(void);
void sleep_socketAction(void);
void sleep_wakeupAction(void);

#endif/*__SLEEP_H__*/

