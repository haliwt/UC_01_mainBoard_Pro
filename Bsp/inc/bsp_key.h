#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "main.h"

#define KEY_POWER_VALUE()         ((GPIOB->IDR & LL_KEY_POWER_Pin) ? 1 : 0 )//sys_read_gpio_pin_value(GPIOD, KEY_POWER_Pin) //GPIO_1 按键按下，返回�??: 1
//#define KEY_MODE_VALUE()          ((GPIOB->IDR & GPIO_Pin_5) ? 1 : 0 ) //sys_read_gpio_pin_value(GPIOD, KEY_MODE_Pin)
#define KEY_AI_VALUE()          ((GPIOB->IDR & LL_KEY_AI_Pin) ? 1 : 0 )

//#define KEY_DOWN_VALUE()          ((GPIOB->IDR & GPIO_Pin_3) ? 1 : 0 )//sys_read_gpio_pin_value(GPIOD, KEY_DOWN_Pin)
#define KEY_FAN_VALUE()           ((GPIOB->IDR & LL_KEY_FAN_Pin) ? 1 : 0 )

#define KEY_PLASMA_VALUE()            ((GPIOB->IDR & LL_KEY_PLASMA_Pin) ? 1 : 0 )



typedef enum{

    KEY_DOWN,
	KEY_UP
}key_state;

extern uint8_t key_worked_f;
//extern uint8_t key_long_f;
extern uint16_t key_data;
extern uint16_t key_time;




void key_power_short_handler(void);

void key_power_long_handler(void);

void key_ai_short_handler(void);

void key_fan_short_handler(void);



void key_plasma_short_handler(void);

void ai_module_hanlder(void);


#endif 

