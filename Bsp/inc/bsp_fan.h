#ifndef __BSP_FAN_H
#define __BSP_FAN_H
#include "main.h"

#if 0   //12V FAN BE TESTING IS OK
#define FAN_SPEED_HIGH       2560//2560-2560//40   100%
#define FAN_SPEED_MIDDLE     2048//2048//2560-2048 80%
#define FAN_SPEED_LOW        1280//2560-1280=   50%

#else 
#define FAN_SPEED_HIGH       2559//2560-2560//40   100%
#define FAN_SPEED_MIDDLE     1792// 70%
#define FAN_SPEED_LOW        1280//50%

#endif 


extern uint8_t fan_adn_error_counter;


void fan_stop(void);


void fan_adjust_high_speed(void);

void fan_adjust_middle_speed(void);

void fan_adjust_low_speed(void);


void fan_adc_detected_value(void);



void fan_speed_adjust_handler(uint8_t speed_value);



void fan_warning_sound_handler(void);


#endif 


