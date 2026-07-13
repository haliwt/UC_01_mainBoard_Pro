#ifndef __BSP_PERIPHERAL_H
#define __BSP_PERIPHERAL_H
#include "main.h"

#define PLASMA_ON()   LL_GPIO_SetOutputPin(PLASMA_CTL_GPIO_Port,LL_PLASMA_CTL_Pin)
#define PLASMA_OFF()  LL_GPIO_ResetOutputPin(PLASMA_CTL_GPIO_Port,LL_PLASMA_CTL_Pin)

#define TEC_ON()     LL_GPIO_SetOutputPin(COOLER_CTL_GPIO_Port,LL_COOLER_CTL_Pin)
#define TEC_OFF()    LL_GPIO_ResetOutputPin(COOLER_CTL_GPIO_Port,LL_COOLER_CTL_Pin)

#define ANGLE_SENSOR_VALUE()     LL_GPIO_IsInputPinSet(ANGLE_SENSOR_GPIO_Port,LL_ANGLE_SENSOR_Pin)


void plasma_set_status(bool idata) // 1-开启，0-关闭

void ai_set_status(bool idata);    // 1--开启, 0- 关闭


void Heat_Process(void);

void Fan_Current_Det(void);

void power_on_ctrl_handler(void);
void power_off_ctrl_handler(void);




void workd_interval_time_peripheral_handle(void);
void workd_interval_turn_off_handle(void);






#endif 
