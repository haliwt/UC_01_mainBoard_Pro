/* USER CODE BEGIN header */
/**
  ******************************************************************************
  * @file    main.c  
  * @author  YSPRING Application Team
  * @version 1.0.0
  * @date    2023.3.20
  * @brief   Main program
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
/* USER CODE END header */
#include "ys32t031.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "dma.h"
#include "uart.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN includes */
#include "tx_api.h"
#include "bsp.h"
/* USER CODE END includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN typedef */

/* USER CODE END typedef */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN macro */

/* USER CODE END macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN variables */

/* USER CODE END variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN prototypes */

/* USER CODE END prototypes */

/* Private user code ---------------------------------------------------------*/
// RCC initialization configuration
void RCC_Configuration(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
  // Enable LSI
  LL_RCC_LSI_Enable();

  LL_RCC_HSI_Enable();
  LL_RCC_HSI_SetDiv(LL_RCC_HSI_DIV_1);
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_16MHz);
  while (LL_RCC_HSI_IsReady() != 1);
  LL_Init1msTick(16000000);

  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_4);
  LL_RCC_PLL_Enable();
  // while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  LL_mDelay(1);

  // HCLK = 64 MHz
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

  // PCLK = 64 MHz
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

  // SYSCLK = 64 MHz
  SystemCoreClockUpdate();

  LL_Init1msTick(64000000);
}





// NVIC 初始化配置
void NVIC_Configuration(void)
{
  NVIC_SetPriority(TIM17_IRQn, 0);
  NVIC_EnableIRQ(TIM17_IRQn);

  NVIC_SetPriority(UART1_IRQn, 2);
  NVIC_EnableIRQ(UART1_IRQn);

  NVIC_SetPriority(UART2_IRQn, 3);
  NVIC_EnableIRQ(UART2_IRQn);
}

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{
  RCC_Configuration();
  GPIO_Configuration();
  UART1_Configuration();
  UART2_Configuration();
  TIM1_Configuration();
  TIM3_Configuration();
  TIM16_Configuration();
  TIM17_Configuration();
  IWDG_Configuration();
  
  ADC_Configuration();
  DMA_Configuration();
  NVIC_Configuration();

  /* USER CODE BEGIN 1 */
   tx_kernel_enter(); 
  /* USER CODE END 1 */

  while(1)
  {
    /* USER CODE BEGIN while */
    
    /* USER CODE END while */
  }
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
