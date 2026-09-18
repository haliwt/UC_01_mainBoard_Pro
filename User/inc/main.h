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

//LED KEY GPIO


/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

