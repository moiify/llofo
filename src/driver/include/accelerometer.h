#ifndef __ACCELEROMETER_H_
#define __ACCELEROMETER_H_

bool accelerometer_readOutputXYZ(short *x_data, short *y_data, short *z_data);
bool accelerometer_initial(void);
bool accelerometer_check(void);
bool accelerometer_reset(void);

#endif 
