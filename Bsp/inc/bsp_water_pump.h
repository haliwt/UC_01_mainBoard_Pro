#ifndef __BSP_WATER_PUMP_H
#define __BSP_WATER_PUMP_H
#include "ys32t031.h"
#include "main.h"
#include"gpio.h"




#define WATER_PUMP_CTRL_ON()       do{WATER_PUMP_GPIO_Port ->BSRR = LL_WATER_PUMP_Pin;}while(0)//LL_GPIO_SetOutputPin(WATER_PUMP_CTRL_GPIO_Port,LL_WATER_PUMP_CTRL_Pin) 
#define WATER_PUMP_CTRL_OFF()      do{WATER_PUMP_GPIO_Port ->BSRR = (uint32_t)LL_WATER_PUMP_Pin<<16;}while(0)//LL_GPIO_ResetOutputPin(WATER_PUMP_CTRL_GPIO_Port,LL_WATER_PUMP_CTRL_Pin) 





#endif 

