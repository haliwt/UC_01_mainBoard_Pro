#ifndef __BSP_TEC_H
#define __BSP_TEC_H
#include "ys32t031.h"
#include "main.h"
#include "gpio.h"



#define TEC_CTRL_ON()     LL_GPIO_SetOutputPin(COOLER_CTL_GPIO_Port,LL_COOLER_CTL_Pin)
#define TEC_CTRL_OFF()    LL_GPIO_ResetOutputPin(COOLER_CTL_GPIO_Port,LL_COOLER_CTL_Pin)



#endif 

