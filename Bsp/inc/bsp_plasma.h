#ifndef __BSP_PLASMA_H
#define __BSP_PLASMA_H
#include "ys32t031.h"
#include "main.h"
#include "gpio.h"



#define PLASMA_CTRL_ON()   do{PLASMA_GPIO_Port->BSRR = LL_PLASMA_Pin;}while(0)//LL_GPIO_SetOutputPin(PLASMA_CTL_GPIO_Port,LL_PLASMA_CTL_Pin)
#define PLASMA_CTRL_OFF()  do{PLASMA_GPIO_Port->BSRR = (uint32_t)LL_PLASMA_Pin<<16;}while(0)//LL_GPIO_ResetOutputPin(PLASMA_CTL_GPIO_Port,LL_PLASMA_CTL_Pin)


void plasma_set_status(bool idata); // 1-开启，0-关闭





#endif 

