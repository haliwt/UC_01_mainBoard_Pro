#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "main.h"


#define LED_POWER_ON()      LL_GPIO_ResetOutputPin(LED_POWER_GPIO_Port, LL_LED_POWER_Pin)
#define LED_POWER_OFF()     LL_GPIO_SetOutputPin(LED_POWER_GPIO_Port, LL_LED_POWER_Pin)
#define LED_POWER_TOGGLE()   LL_GPIO_TogglePin(LED_POWER_GPIO_Port, LL_LED_POWER_Pin)

#define  LED_TIME_ON()       do{LED_TIME_GPIO_Port -> BSRR = LL_LED_TIME_Pin;}while(0)
#define  LED_TIME_OFF()      do{LED_TIME_GPIO_Port -> BSRR =(uint32_t)LL_LED_TIME_Pin<<16;}while(0)



//水位指示灯
    
#define LED_WATER_LEVEL_LOW_ON()          LL_GPIO_ResetOutputPin(LED_WATER_G_GPIO_Port,LL_LED_WATER_G_Pin)//do{LED_WATER_RB_GPIO_Port->BSRR = (uint32_t)LL_LED_WATER_RB_Pin << 16;}while(0)
#define LED_WATER_LEVEL_LOW_OFF()         LL_GPIO_SetOutputPin(LED_WATER_G_GPIO_Port,LL_LED_WATER_G_Pin)  //do{LED_WATER_RB_GPIO_Port->BSRR = LL_LED_WATER_RB_Pin ;}while(0)

   
#define LED_WATER_LEVEL_MIDDLE_ON()         LL_GPIO_ResetOutputPin(LED_WATER_R_GPIO_Port,LL_LED_WATER_R_Pin)    
#define LED_WATER_LEVEL_MIDDLE_OFF()         LL_GPIO_SetOutputPin(LED_WATER_R_GPIO_Port,LL_LED_WATER_R_Pin) 

  
//#define LED_WATER_LEVEL_HIGH_ON()         LL_GPIO_ResetOutputPin(LED_WATER_G_GPIO_Port,LL_LED_WATER_G_Pin)    
//#define LED_WATER_LEVEL_HIGH_OFF()         LL_GPIO_SetOutputPin(LED_WATER_G_GPIO_Port,LL_LED_WATER_G_Pin)  

#define LED_WATER_LEVEL_HIGH_ON()         do{LED_WATER_RB_GPIO_Port->BSRR = (uint32_t)LL_LED_WATER_RB_Pin << 16;}while(0)//LL_GPIO_ResetOutputPin(LED_WATER_G_GPIO_Port,LL_LED_WATER_G_Pin)    
#define LED_WATER_LEVEL_HIGH_OFF()        do{LED_WATER_RB_GPIO_Port->BSRR = LL_LED_WATER_RB_Pin ;}while(0)//LL_GPIO_SetOutputPin(LED_WATER_G_GPIO_Port,LL_LED_WATER_G_Pin)  

    


#define LED_WATER_WARNING_ON()        do{LED_WATER_B_GPIO_Port -> BSRR = (uint32_t)LL_LED_WATER_B_Pin<<16;}while(0)    //LL_GPIO_ResetOutputPin(LED_WATER_B_GPIO_Port,LL_LED_WATER_B_Pin)
#define LED_WATER_WARNING_OFF()       do{LED_WATER_B_GPIO_Port -> BSRR =LL_LED_WATER_B_Pin;}while(0) 

//湿度指示灯
#define  LED_HUMIDITY_ON_HIGH()     LL_GPIO_SetOutputPin(LED_B_3_GPIO_Port,LL_LED_B_3_Pin)
#define  LED_HUMIDITY_OFF_HIGH()    LL_GPIO_ResetOutputPin(LED_B_3_GPIO_Port,LL_LED_B_3_Pin)

#define  LED_HUMIDITY_ON_MIDDLE()     LL_GPIO_SetOutputPin(LED_R_1_GPIO_Port,LL_LED_R_1_Pin) //
#define  LED_HUMIDITY_OFF_MIDDLE()    LL_GPIO_ResetOutputPin(LED_R_1_GPIO_Port,LL_LED_R_1_Pin)//

#define  LED_HUMIDIY_ON_LOW()        LL_GPIO_SetOutputPin(LED_G_2_GPIO_Port,LL_LED_G_2_Pin) //
#define  LED_HUMIDIY_OFF_LOW()       LL_GPIO_ResetOutputPin(LED_G_2_GPIO_Port,LL_LED_G_2_Pin) //





void wifi_fast_led_state(void);


void wifi_led_state_handler(void);

void power_on_led_handler(void);

void power_off_led_handler(void);

void humidity_indicate_led_handler(void);

void power_off_led_blink_handler(void);



#endif 

