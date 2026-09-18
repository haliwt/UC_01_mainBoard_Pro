#ifndef __BSP_ANGLE_SENSOR_H
#define __BSP_ANGLE_SENSOR_H
#include "ys32t031.h"
#include "main.h"
#include "gpio.h"


//GPIO INPUT
#define ANGLE_SENSOR_VALUE()     ((GPIOF->IDR & LL_ANGLE_SENSOR_Pin) ? 1 : 0 )//LL_GPIO_IsInputPinSet(ANGLE_SENSOR_GPIO_Port,LL_ANGLE_SENSOR_Pin)




#endif 

