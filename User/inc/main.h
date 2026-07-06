/* USER CODE BEGIN header */
/**
  ******************************************************************************
  * @file    main.h
  * @author  YSPRING Application Team
  * @version V1.0.1
  * @date    2023.3.20
  * @brief   Library configuration file.
  ******************************************************************************
  */
/* USER CODE END header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ys32t031.h"
#include "ys32t031_ll_utils.h"
#include "ys32t031_ll_system.h"
#include "ys32t031_ll_cortex.h"
#include "ys32t031_ll_bus.h"
#include "ys32t031_ll_adc.h"
#include "ys32t031_ll_comp.h"
#include "ys32t031_ll_crc.h"
#include "ys32t031_ll_dma.h"
#include "ys32t031_ll_exti.h"
#include "ys32t031_ll_flash.h"
#include "ys32t031_ll_gpio.h"
#include "ys32t031_ll_i2c.h"
#include "ys32t031_ll_iwdg.h"
#include "ys32t031_ll_led.h"
#include "ys32t031_ll_lptim.h"
#include "ys32t031_ll_pwr.h"
#include "ys32t031_ll_rcc.h"
#include "ys32t031_ll_rtc.h"
#include "ys32t031_ll_spi.h"
#include "ys32t031_ll_tim.h"
#include "ys32t031_ll_uart.h"
#include "ys32t031_ll_vrefbuf.h"
#include "ys32t031_ll_wwdg.h"
#include "ys32t031_ll_tsc.h"

#if defined(USE_FULL_ASSERT)
#include "ys32_assert.h"
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN includes */

/* USER CODE END includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN types */

/* USER CODE END types */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN constants */

/* USER CODE END constants */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN macro */

/* USER CODE END macro */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN prototypes */

/* USER CODE END prototypes */

/* Private defines -----------------------------------------------------------*/
#define LED_AI_GPIO_Port GPIOA
#define LL_LED_AI_Pin LL_GPIO_PIN_15
#define WATER_POS_GPIO_Port GPIOB
#define LL_WATER_POS_Pin LL_GPIO_PIN_0
#define LED_B_3_GPIO_Port GPIOB
#define LL_LED_B_3_Pin LL_GPIO_PIN_14
#define LED_G_2_GPIO_Port GPIOB
#define LL_LED_G_2_Pin LL_GPIO_PIN_15
#define PLASMA_CTL_GPIO_Port GPIOA
#define LL_PLASMA_CTL_Pin LL_GPIO_PIN_8
#define LED_PLASMA_GPIO_Port GPIOC
#define LL_LED_PLASMA_Pin LL_GPIO_PIN_13
#define LED_FAN_GPIO_Port GPIOC
#define LL_LED_FAN_Pin LL_GPIO_PIN_14
#define LED_POWER_GPIO_Port GPIOC
#define LL_LED_POWER_Pin LL_GPIO_PIN_15
#define LED_WATER_G_GPIO_Port GPIOF
#define LL_LED_WATER_G_Pin LL_GPIO_PIN_0
#define LED_WATER_B_GPIO_Port GPIOF
#define LL_LED_WATER_B_Pin LL_GPIO_PIN_1
#define LED_WATER_R_GPIO_Port GPIOF
#define LL_LED_WATER_R_Pin LL_GPIO_PIN_3
#define LED_WATER_RB_GPIO_Port GPIOF
#define LL_LED_WATER_RB_Pin LL_GPIO_PIN_4
#define COOLER_CTL_GPIO_Port GPIOA
#define LL_COOLER_CTL_Pin LL_GPIO_PIN_6
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
#define LED_R_1_GPIO_Port GPIOA
#define LL_LED_R_1_Pin LL_GPIO_PIN_11
#define FAN_PWM_GPIO_Port GPIOA
#define LL_FAN_PWM_Pin LL_GPIO_PIN_5
#define BEEP_PWM_GPIO_Port GPIOB
#define LL_BEEP_PWM_Pin LL_GPIO_PIN_1
#define I2C_SCL_GPIO_Port GPIOF
#define LL_I2C_SCL_Pin LL_GPIO_PIN_6
#define I2C_SDA_GPIO_Port GPIOF
#define LL_I2C_SDA_Pin LL_GPIO_PIN_7
#define TX_DISP_GPIO_Port GPIOA
#define LL_TX_DISP_Pin LL_GPIO_PIN_9
#define RX_DISP_GPIO_Port GPIOA
#define LL_RX_DISP_Pin LL_GPIO_PIN_10
#define TX_WIFI_GPIO_Port GPIOA
#define LL_TX_WIFI_Pin LL_GPIO_PIN_2
#define RX_WIFI_GPIO_Port GPIOA
#define LL_RX_WIFI_Pin LL_GPIO_PIN_3

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
