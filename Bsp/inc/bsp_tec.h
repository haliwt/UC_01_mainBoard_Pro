#ifndef __BSP_TEC_H
#define __BSP_TEC_H
#include "ys32t031.h"
#include "main.h"
#include "gpio.h"

#define  OLDER_VERSION    0  //WT.EDIT 2026-10-30


#if OLDER_VERSION 
#define TEC_CTRL_ON()     LL_GPIO_SetOutputPin(COOLER_CTL_GPIO_Port,LL_COOLER_CTL_Pin)
#define TEC_CTRL_OFF()    LL_GPIO_ResetOutputPin(COOLER_CTL_GPIO_Port,LL_COOLER_CTL_Pin)

#else 
#define TEC_CTRL_ON()     LL_GPIO_SetOutputPin(COOLER_CTL_GPIO_Port,LL_COOLER_CTL_Pin)
#define TEC_CTRL_OFF()    LL_GPIO_ResetOutputPin(COOLER_CTL_GPIO_Port,LL_COOLER_CTL_Pin)


#endif 



#endif 

