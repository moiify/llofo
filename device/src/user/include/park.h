/*
 * park.h
 *
 *  Created on: 2019/5/28
 *      Author:GCC
 */
#ifndef PARKING_H_
#define PARKING_H_

#define CALC_DIR_TIME 10 //计算方向角的时间间隔（ms）

void park_initial(void);
int park_dirFix_timerHandler(void);
u8   park_isDirFixed(void);
void park_setIsDirFixed(u8 isDirFixed);

#endif
