#ifndef __BSP_FAN_H
#define __BSP_FAN_H
#include "main.h"


void fan_stop(void);


void fan_adjust_high_speed(void);

void fan_adjust_middle_speed(void);

void fan_adjust_low_speed(void);


//void wifiFan_Ctrl_Process(void);


void fan_speed_adjust_handler(uint8_t speed_value);




#endif 


