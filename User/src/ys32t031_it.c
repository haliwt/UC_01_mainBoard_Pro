/* USER CODE BEGIN header */
/**
  ******************************************************************************
  * @file    ys32t031_it.c 
  * @author  YSPRING Application Team
  * @version V1.0.0
  * @date    
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* USER CODE END header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ys32t031_it.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN includes */
#include "bsp.h"
/* USER CODE END includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN typedef */

/* USER CODE END typedef */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN define */

/* USER CODE END define */

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
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN External variables */

/* USER CODE END External variables */

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NMI_Handler */

  /* USER CODE END NMI_Handler */
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  /* USER CODE BEGIN HardFault_Handler 0 */

  /* USER CODE END HardFault_Handler 0 */
  while (1)
  {
    /* USER CODE BEGIN HardFault_Handler 1 */
    
    /* USER CODE END HardFault_Handler 1 */
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_Handler */

  /* USER CODE END SVC_Handler */
}

#if 0 //be used to threadx 
/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_Handler */

  /* USER CODE END PendSV_Handler */
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_Handler */

  /* USER CODE END SysTick_Handler */
}
#endif 
/**
  * @brief  This function handles TIM17_IRQn.
  * @param  None
  * @retval None
  */
void TIM6_LPTIM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM17_IRQHandler */
  // 1. 检查是否是由定时器更新（溢出）产生的中断
	if (LL_TIM_IsActiveFlag_UPDATE(TIM6) == 1)
	{
	  // 2. 必须立刻手动清除更新中断标志位，防止重复进入中断
	  LL_TIM_ClearFlag_UPDATE(TIM6);
  
	  // 3. 执行你的 10ms 周期性任务
	  // 示例：可以用来累加系统滴答时间，或者递减某些超时计数器
	   tim6_10ms_tick_handler(); 
  
	}

     
  /* USER CODE END TIM17_IRQHandler */
}

/**
  * @brief  This function handles UART1_IRQn displayBoard.
  * @param  None
  * @retval None
  */
void UART1_IRQHandler(void)
{
  //extern void UART1_Int_Call(void);
  UART1_Int_Call();
  /* USER CODE BEGIN UART1_IRQHandler */
 
  /* USER CODE END UART1_IRQHandler */
}

/**
  * @brief  This function handles UART2_IRQn wifi.
  * @param  None
  * @retval None
  */
void UART2_IRQHandler(void)
{
  extern void UART2_Int_Call(void);
  UART2_Int_Call();
  /* USER CODE BEGIN UART2_IRQHandler */
  
  /* USER CODE END UART2_IRQHandler */
}

/**
  * @brief  This function handles DMA CHANNEL1 interrupt request.
  * @param  None
  * @retval None
  */
#if 0
void DMA_CHANNEL1_IRQHandler(void)
{
	if((LL_DMA_IsEnabledIT_TC(DMA, LL_DMA_CHANNEL_1) == SET) && (LL_DMA_IsActiveFlag_TC1(DMA) == SET))
  {
    LL_DMA_ClearFlag_TC1(DMA);  //clear interrupt
		//gpro_t.dma_dong_flag = 1;           //notice CUP transmiter is complete
		return;
  }

  /* 2. (建议补充) 处理 DMA 传输错误中断，避免程序死锁 */
    if (LL_DMA_IsEnabledIT_TE(DMA, LL_DMA_CHANNEL_1) && LL_DMA_IsActiveFlag_TE1(DMA))
    {
        LL_DMA_ClearFlag_TE1(DMA);
        /* 可在此处加入错误处理逻辑 */
    }
}

#endif 
/* USER CODE BEGIN 1 */


/* USER CODE END 1 */
