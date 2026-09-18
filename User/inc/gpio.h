#ifndef __GPIO_H
#define __GPIO_H
#include "main.h"


/* Private defines -----------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/
#define LED_WATER_G_GPIO_Port GPIOB
#define LL_LED_WATER_G_Pin LL_GPIO_PIN_14
#define LED_WATER_B_GPIO_Port GPIOB
#define LL_LED_WATER_B_Pin LL_GPIO_PIN_15
#define LED_POWER_GPIO_Port GPIOC
#define LL_LED_POWER_Pin LL_GPIO_PIN_13
#define WATER_SW_GPIO_Port GPIOC
#define LL_WATER_SW_Pin LL_GPIO_PIN_14
#define WATER_PUMP_GPIO_Port GPIOF
#define LL_WATER_PUMP_Pin LL_GPIO_PIN_4
#define KEY_FAN_GPIO_Port GPIOB
#define LL_KEY_FAN_Pin LL_GPIO_PIN_4
#define KEY_PLASMA_GPIO_Port GPIOB
#define LL_KEY_PLASMA_Pin LL_GPIO_PIN_3
#define I2C_SDA_GPIO_Port GPIOF
#define LL_I2C_SDA_Pin LL_GPIO_PIN_7
#define I2C_SCL_GPIO_Port GPIOF
#define LL_I2C_SCL_Pin LL_GPIO_PIN_6
#define PLASMA_GPIO_Port GPIOB
#define LL_PLASMA_Pin LL_GPIO_PIN_0
#define LED_B_3_GPIO_Port GPIOA
#define LL_LED_B_3_Pin LL_GPIO_PIN_8
#define LED_R_1_GPIO_Port GPIOA
#define LL_LED_R_1_Pin LL_GPIO_PIN_11
#define LED_G_2_GPIO_Port GPIOA
#define LL_LED_G_2_Pin LL_GPIO_PIN_12
#define KEY_AI_GPIO_Port GPIOA
#define LL_KEY_AI_Pin LL_GPIO_PIN_15
#define KEY_POWER_GPIO_Port GPIOB
#define LL_KEY_POWER_Pin LL_GPIO_PIN_5
#define COOLER_CTL_GPIO_Port GPIOB
#define LL_COOLER_CTL_Pin LL_GPIO_PIN_11
#define LED_WATER_RB_GPIO_Port GPIOB
#define LL_LED_WATER_RB_Pin LL_GPIO_PIN_12
#define LED_WATER_R_GPIO_Port GPIOB
#define LL_LED_WATER_R_Pin LL_GPIO_PIN_13
#define LED_TIME_GPIO_Port GPIOF
#define LL_LED_TIME_Pin LL_GPIO_PIN_9
#define ANGLE_SENSOR_GPIO_Port GPIOF
#define LL_ANGLE_SENSOR_Pin LL_GPIO_PIN_3
#define ADC_FAN_GPIO_Port GPIOA
#define LL_ADC_FAN_Pin LL_GPIO_PIN_0
#define ADC_NTC_GPIO_Port GPIOA
#define LL_ADC_NTC_Pin LL_GPIO_PIN_1
#define ADC_WATER_2_GPIO_Port GPIOA
#define LL_ADC_WATER_2_Pin LL_GPIO_PIN_4
#define ADC_WATER_3_GPIO_Port GPIOA
#define LL_ADC_WATER_3_Pin LL_GPIO_PIN_7
#define ADC_WATER_4_GPIO_Port GPIOB
#define LL_ADC_WATER_4_Pin LL_GPIO_PIN_2
#define ADC_WATER_1_GPIO_Port GPIOB
#define LL_ADC_WATER_1_Pin LL_GPIO_PIN_10
#define FAN_PWM_GPIO_Port GPIOA
#define LL_FAN_PWM_Pin LL_GPIO_PIN_5
#define BEEP_PWM_GPIO_Port GPIOB
#define LL_BEEP_PWM_Pin LL_GPIO_PIN_1
#define WATER_PWM_GPIO_Port GPIOB
#define LL_WATER_PWM_Pin LL_GPIO_PIN_8
#define TX_DISP_GPIO_Port GPIOA
#define LL_TX_DISP_Pin LL_GPIO_PIN_9
#define RX_DISP_GPIO_Port GPIOA
#define LL_RX_DISP_Pin LL_GPIO_PIN_10
#define TX_WIFI_GPIO_Port GPIOA
#define LL_TX_WIFI_Pin LL_GPIO_PIN_2
#define RX_WIFI_GPIO_Port GPIOA
#define LL_RX_WIFI_Pin LL_GPIO_PIN_3





void GPIO_Configuration(void);



#endif 

