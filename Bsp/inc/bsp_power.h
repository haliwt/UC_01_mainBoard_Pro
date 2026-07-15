/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    user.H
  * @version V1.0.0
  * @date    2024
  * @author  Yspring Firmware Team  
  * @brief   user Header Code.
  ******************************************************************************      
*/
#ifndef __BSP_POWER_H
#define __BSP_POWER_H

#ifdef __cplusplus
extern "C" {
#endif
   
#include "main.h"
#include "stdbool.h"

//fan


//time couter 


extern bool  works_interval_f;

extern uint8_t  soft_version ;








typedef struct  _power_state{

    uint8_t on_step;
	uint8_t  off_step;


}power_state;

extern power_state gon_t;

void power_on_handler(void);

void power_on_off_handler(void);

void ntc_temperature_compare_handler(void);


	
#ifdef __cplusplus
}
#endif

#endif /* __USER_H */
