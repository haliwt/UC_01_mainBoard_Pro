#ifndef __BSP_FAN_H
#define __BSP_FAN_H
#include "main.h"

#define FAN_SPEED_HIGH       0//2560-2560//40   100%
#define FAN_SPEED_MIDDLE     512//2048//2560-2048 80%
#define FAN_SPEED_LOW        1280//2560-1280=   50%


extern uint8_t fan_adn_error_counter;


void fan_stop(void);


void fan_adjust_high_speed(void);

void fan_adjust_middle_speed(void);

void fan_adjust_low_speed(void);


void fan_adc_detected_value(void);



void fan_speed_adjust_handler(uint8_t speed_value);



void fan_warning_sound_handler(void);


#endif 


