#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "main.h"


#define LED_POWER_ON()      LL_GPIO_ResetOutputPin(LED_POWER_GPIO_Port, LL_LED_POWER_Pin)
#define LED_POWER_OFF()     LL_GPIO_SetOutputPin(LED_POWER_GPIO_Port, LL_LED_POWER_Pin)

#define LED_FAN_ON()       LL_GPIO_ResetOutputPin(LED_FAN_GPIO_Port, LL_LED_FAN_Pin)
#define LED_FAN_OFF()      LL_GPIO_SetOutputPin(LED_FAN_GPIO_Port, LL_LED_FAN_Pin)

#define LED_PLASMA_ON()    LL_GPIO_ResetOutputPin(LED_PLASMA_GPIO_Port, LL_LED_PLASMA_Pin)
#define LED_PLASMA_OFF()   LL_GPIO_SetOutputPin(LED_PLASMA_GPIO_Port, LL_LED_PLASMA_Pin)

#define LED_KEY_AI_ON()        LL_GPIO_ResetOutputPin(LED_AI_GPIO_Port, LL_LED_AI_Pin)
#define LED_KEY_AI_OFF()       LL_GPIO_SetOutputPin(LED_AI_GPIO_Port, LL_LED_AI_Pin)


//水位指示灯
#define LED_WATER_INDICATOR_1()      LL_GPIO_SetOutputPin(LED_WATER_RB_GPIO_Port,LL_LED_WATER_RB_Pin)     
#define LED_WATER_LEVEL_1()          LL_GPIO_ResetOutputPin(LED_WATER_RB_GPIO_Port,LL_LED_WATER_RB_Pin)     

#define LED_WATER_INDICATOR_2()     LL_GPIO_SetOutputPin(LED_WATER_R_GPIO_Port,LL_LED_WATER_R_Pin)     
#define LED_WATER_LEVEL_2()         LL_GPIO_ResetOutputPin(LED_WATER_R_GPIO_Port,LL_LED_WATER_R_Pin)    

#define LED_WATER_INDICATOR_3()     LL_GPIO_SetOutputPin(LED_WATER_G_GPIO_Port,LL_LED_WATER_G_Pin)    
#define LED_WATER_LEVEL_3()         LL_GPIO_ResetOutputPin(LED_WATER_G_GPIO_Port,LL_LED_WATER_G_Pin)    

#define LED_WATER_INDICATOR_4()    LL_GPIO_SetOutputPin(LED_WATER_B_GPIO_Port,LL_LED_WATER_B_Pin)    
#define LED_WATER_WARNING()              LL_GPIO_ResetOutputPin(LED_WATER_B_GPIO_Port,LL_LED_WATER_B_Pin)
  






void wifi_fast_led_state(void);


void wifi_led_state_handler(void);

void power_on_led_handler(void);

void power_off_led_handler(void);






#endif 

