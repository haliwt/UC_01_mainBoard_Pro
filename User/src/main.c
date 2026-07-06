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


#if 0
// GPIO 初始化配置
void GPIO_Configuration(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);

  // GPIO_Output
  LL_GPIO_ResetOutputPin(LED_AI_GPIO_Port, LL_LED_AI_Pin);
  LL_GPIO_ResetOutputPin(PLASMA_CTL_GPIO_Port, LL_PLASMA_CTL_Pin);
  LL_GPIO_ResetOutputPin(COOLER_CTL_GPIO_Port, LL_COOLER_CTL_Pin);
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_LED_AI_Pin | LL_PLASMA_CTL_Pin | LL_COOLER_CTL_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_AI_GPIO_Port, &GPIO_InitStruct);

  // ADC_IN2
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_ADC_FAN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(ADC_FAN_GPIO_Port, &GPIO_InitStruct);

  // ADC_IN3
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_ADC_NTC_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(ADC_NTC_GPIO_Port, &GPIO_InitStruct);

  // ADC_IN6
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_ADC_WATER_2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(ADC_WATER_2_GPIO_Port, &GPIO_InitStruct);

  // ADC_IN9
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_ADC_WATER_3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(ADC_WATER_3_GPIO_Port, &GPIO_InitStruct);

  // COMP1_OUT
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  GPIO_InitStruct.Pin = LL_LED_R_1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_R_1_GPIO_Port, &GPIO_InitStruct);

  // TIM1_CH1
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
  GPIO_InitStruct.Pin = LL_FAN_PWM_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(FAN_PWM_GPIO_Port, &GPIO_InitStruct);

  // UART1_TX
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  GPIO_InitStruct.Pin = LL_TX_DISP_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(TX_DISP_GPIO_Port, &GPIO_InitStruct);

  // UART1_RX
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  GPIO_InitStruct.Pin = LL_RX_DISP_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(RX_DISP_GPIO_Port, &GPIO_InitStruct);

  // UART2_TX
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  GPIO_InitStruct.Pin = LL_TX_WIFI_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(TX_WIFI_GPIO_Port, &GPIO_InitStruct);

  // UART2_RX
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
  GPIO_InitStruct.Pin = LL_RX_WIFI_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(RX_WIFI_GPIO_Port, &GPIO_InitStruct);

  // GPIO_Input
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_WATER_POS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(WATER_POS_GPIO_Port, &GPIO_InitStruct);

  // GPIO_Output
  LL_GPIO_ResetOutputPin(LED_B_3_GPIO_Port, LL_LED_B_3_Pin);
  LL_GPIO_ResetOutputPin(LED_G_2_GPIO_Port, LL_LED_G_2_Pin);
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_LED_B_3_Pin | LL_LED_G_2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_B_3_GPIO_Port, &GPIO_InitStruct);

  // ADC_IN12
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_ADC_WATER_4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(ADC_WATER_4_GPIO_Port, &GPIO_InitStruct);

  // ADC_IN13
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_ADC_WATER_1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(ADC_WATER_1_GPIO_Port, &GPIO_InitStruct);

  // TIM3_CH4
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  GPIO_InitStruct.Pin = LL_BEEP_PWM_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BEEP_PWM_GPIO_Port, &GPIO_InitStruct);

  // GPIO_Output
  LL_GPIO_ResetOutputPin(LED_PLASMA_GPIO_Port, LL_LED_PLASMA_Pin);
  LL_GPIO_ResetOutputPin(LED_FAN_GPIO_Port, LL_LED_FAN_Pin);
  LL_GPIO_ResetOutputPin(LED_POWER_GPIO_Port, LL_LED_POWER_Pin);
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_LED_PLASMA_Pin | LL_LED_FAN_Pin | LL_LED_POWER_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_PLASMA_GPIO_Port, &GPIO_InitStruct);

  // GPIO_Output
  LL_GPIO_ResetOutputPin(LED_WATER_G_GPIO_Port, LL_LED_WATER_G_Pin);
  LL_GPIO_ResetOutputPin(LED_WATER_B_GPIO_Port, LL_LED_WATER_B_Pin);
  LL_GPIO_ResetOutputPin(LED_WATER_R_GPIO_Port, LL_LED_WATER_R_Pin);
  LL_GPIO_ResetOutputPin(LED_WATER_RB_GPIO_Port, LL_LED_WATER_RB_Pin);
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_LED_WATER_G_Pin | LL_LED_WATER_B_Pin | LL_LED_WATER_R_Pin | LL_LED_WATER_RB_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_WATER_G_GPIO_Port, &GPIO_InitStruct);

  // I2C2_SCL
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  GPIO_InitStruct.Pin = LL_I2C_SCL_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(I2C_SCL_GPIO_Port, &GPIO_InitStruct);

  // I2C2_SDA
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  GPIO_InitStruct.Pin = LL_I2C_SDA_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(I2C_SDA_GPIO_Port, &GPIO_InitStruct);
}
#endif 
#if 0
void UART1_Int_Call(void)
{
  if(LL_UART_IsActiveFlag_RXNE(UART1)&& LL_UART_IsEnabledIT_RXNE(UART1))
  {
    /* USER CODE BEGIN Code_UART1_Int_Call_UART_FLAG_RXNE */
    // UART_ReceiveData(UART1);
    
    /* USER CODE END Code_UART1_Int_Call_UART_FLAG_RXNE */
  }

  if (LL_UART_IsActiveFlag_TC(UART1) && LL_UART_IsEnabledIT_TC(UART1))
  {
    /* USER CODE BEGIN Code_UART1_Int_Call_UART_FLAG_TC */
    
    /* USER CODE END Code_UART1_Int_Call_UART_FLAG_TC */
    LL_UART_ClearFlag_TC(UART1);
  }

  UART1->ICR = 0xFF;
}

#endif 




#if 0
// UART1 初始化配置
void UART1_Configuration(void)
{
  LL_UART_InitTypeDef UART_InitStructure= {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UART1);

  LL_UART_DeInit(UART1);
  LL_UART_StructInit(&UART_InitStructure);
  UART_InitStructure.BaudRate = 115200;
  UART_InitStructure.DataWidth = LL_UART_DATAWIDTH_8B;
  UART_InitStructure.StopBits = LL_UART_STOPBITS_1;
  UART_InitStructure.Parity = LL_UART_PARITY_NONE;
  UART_InitStructure.TransferDirection = LL_UART_DIRECTION_TX_RX;
  LL_UART_Init(UART1, &UART_InitStructure);

  LL_UART_EnableIT_RXNE(UART1);
  LL_UART_EnableIT_TC(UART1);

  LL_UART_Enable(UART1);
}

void UART2_Int_Call(void)
{
  if(LL_UART_IsActiveFlag_RXNE(UART2)&& LL_UART_IsEnabledIT_RXNE(UART2))
  {
    /* USER CODE BEGIN Code_UART2_Int_Call_UART_FLAG_RXNE */
    // UART_ReceiveData(UART2);
    
    /* USER CODE END Code_UART2_Int_Call_UART_FLAG_RXNE */
  }

  if (LL_UART_IsActiveFlag_TC(UART2) && LL_UART_IsEnabledIT_TC(UART2))
  {
    /* USER CODE BEGIN Code_UART2_Int_Call_UART_FLAG_TC */
    
    /* USER CODE END Code_UART2_Int_Call_UART_FLAG_TC */
    LL_UART_ClearFlag_TC(UART2);
  }

  UART2->ICR = 0xFF;
}

// UART2 初始化配置
void UART2_Configuration(void)
{
  LL_UART_InitTypeDef UART_InitStructure= {0};

  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART2);

  LL_UART_DeInit(UART2);
  LL_UART_StructInit(&UART_InitStructure);
  UART_InitStructure.BaudRate = 115200;
  UART_InitStructure.DataWidth = LL_UART_DATAWIDTH_8B;
  UART_InitStructure.StopBits = LL_UART_STOPBITS_1;
  UART_InitStructure.Parity = LL_UART_PARITY_NONE;
  UART_InitStructure.TransferDirection = LL_UART_DIRECTION_TX_RX;
  LL_UART_Init(UART2, &UART_InitStructure);

  LL_UART_EnableIT_RXNE(UART2);
  LL_UART_EnableIT_TC(UART2);

  LL_UART_Enable(UART2);
}

#endif 

#if 0

// TIM1 初始化配置
void TIM1_Configuration(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  // Overflow time = ((Auto-reload 31999 + 1) * (Prescaler 0 + 1)) / 64000000 = 500 μs, frequency= 2 kHz
  LL_TIM_StructInit(&TIM_InitStruct);
  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.Autoreload = 31999; // TIM_ARR
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.ClockDivision = 0;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM1, &TIM_InitStruct);

  LL_TIM_OC_StructInit(&TIM_OC_InitStruct);
  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
  TIM_OC_InitStruct.CompareValue = 0; // TIM_CCR, Duty = TIM_CCR/(TIM_ARR+1)
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_LOW;
  TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_TIM_EnableCounter(TIM1);
  LL_TIM_EnableAllOutputs(TIM1);
}

// TIM3 初始化配置
void TIM3_Configuration(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  // Overflow time = ((Auto-reload 31999 + 1) * (Prescaler 0 + 1)) / 64000000 = 500 μs, frequency= 2 kHz
  LL_TIM_StructInit(&TIM_InitStruct);
  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.Autoreload = 31999; // TIM_ARR
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.ClockDivision = 0;
  LL_TIM_Init(TIM3, &TIM_InitStruct);

  LL_TIM_OC_StructInit(&TIM_OC_InitStruct);
  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
  TIM_OC_InitStruct.CompareValue = 0; // TIM_CCR, Duty = TIM_CCR/(TIM_ARR+1)
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_LOW;
  TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
  LL_TIM_OC_Init(TIM3,LL_TIM_CHANNEL_CH4, &TIM_OC_InitStruct);

  LL_TIM_EnableCounter(TIM3);
  LL_TIM_EnableAllOutputs(TIM3);
}

// TIM17 初始化配置
void TIM17_Configuration(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM17);

  // Overflow time = ((Auto-reload 63999 + 1) * (Prescaler 9 + 1)) / 64000000 = 10 ms, frequency= 100 Hz
  LL_TIM_StructInit(&TIM_InitStruct);
  TIM_InitStruct.Prescaler = 9;
  TIM_InitStruct.Autoreload = 63999; // TIM_ARR
  TIM_InitStruct.ClockDivision = 0;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM17, &TIM_InitStruct);

  LL_TIM_EnableIT_UPDATE(TIM17);
  LL_TIM_EnableCounter(TIM17);
}

#endif 
#if 0
// COMP1 初始化配置
void COMP1_Configuration(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_COMP1);
  LL_COMP_DisableLock(COMP1);
  LL_COMP_DisableFilter(COMP1);

  LL_COMP_SetPWRMode(COMP1, LL_COMP_PWRMODE_HIGH);
  LL_COMP_SetPolarity(COMP1, LL_COMP_POLARITY_NONE);
  LL_COMP_SetFilterCount(COMP1, 0);
  LL_COMP_EnableFilter(COMP1);
 // LL_COMP1_SetInputPlusSel(LL_COMP1_INPSEL_);
//  LL_COMP1_SetInputMinus(LL_COMP1_INMSEL_);
  LL_COMP_EnableCOMP(COMP1);
  LL_COMP_EnableLock(COMP1);
}
#endif 
#if 0
// IWDG 初始化配置
void IWDG_Configuration(void)
{
  LL_RCC_LSI_Enable();
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_IWDG);
  LL_IWDG_EnableWriteAccess(IWDG);
  LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_4);
  LL_IWDG_SetReloadCounter(IWDG, 2048);
  while (LL_IWDG_IsReady(IWDG) == RESET){}

  LL_IWDG_SetWindow(IWDG, 4095);
  LL_IWDG_ReloadCounter(IWDG);
  LL_IWDG_Enable(IWDG);
}

#endif 
// I2C2 初始化配置
void I2C2_Configuration(void)
{
  LL_I2C_InitTypeDef I2C_InitStruct = {0};
  
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
  LL_I2C_DisableOwnAddress2(I2C2);
  LL_I2C_DisableGeneralCall(I2C2);
  LL_I2C_EnableClockStretching(I2C2);
  I2C_InitStruct.DigitalFilter = 0 ;
  I2C_InitStruct.OwnAddress1 = 0 ;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
  I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
  I2C_InitStruct.Timing = 4062315777;
  LL_I2C_Init(I2C2, &I2C_InitStruct);
}
#if 0
// ADC 初始化配置
void ADC_Configuration(void)
{
  LL_ADC_InitTypeDef ADC_InitStruct;
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC);
  LL_ADC_DeInit();
  LL_ADC_StructInit(&ADC_InitStruct);
  
  ADC_InitStruct.ClockMode = LL_ADC_CLOCK_MODE_PCLK;
  ADC_InitStruct.DataAlign = LL_ADC_DATA_ALIGN_RIGHT;
  ADC_InitStruct.ScanMode = LL_ADC_SCAN_MODE_DIS;
  ADC_InitStruct.ContinuousMode = LL_ADC_REG_CONTINUOUS_DIS;
  ADC_InitStruct.REG_ExternalTrig = LL_ADC_REG_EXT_TRIG_DIS;
  ADC_InitStruct.REG_ExternalEvent = LL_ADC_REG_EXTERNAL_TRIG_SWSTART;
  ADC_InitStruct.INJ_ExternalTrig = LL_ADC_INJ_EXT_TRIG_DIS;
  ADC_InitStruct.INJ_ExternalEvent = LL_ADC_INJ_EXTERNAL_TRIG_SWSTART;
  LL_ADC_Init(ADC, &ADC_InitStruct);
  
  LL_ADC_SetOverrunMode(LL_ADC_OVERRUN_MODE_OLD);
  LL_ADC_SetWaitConversion(LL_ADC_WAIT_CONVERSION_DIS);
  LL_ADC_SetBiasCurrent(LL_ADC_BIAS_CURRENT_10_20UA);
  LL_ADC_DisableTempSensor();
  
  LL_ADC_REG_SetSequencerDiscont(0);
  LL_ADC_INJ_SetSequencerDiscont(LL_ADC_INJ_DISCONTINUOUS_DIS);
  LL_ADC_REG_SetSequencerDiscont(DISABLE);
  
  LL_ADC_SetSampleTime(LL_ADC_SAMPLE_TIME_15_5_CYCLES);
  LL_ADC_REG_SetSequencerLength(LL_ADC_REG_SEQ_SCAN_RANKS_6);
  LL_ADC_REG_SetSequencerRanks(1, LL_ADC_CHANNEL_2);
  LL_ADC_REG_SetSequencerRanks(2, LL_ADC_CHANNEL_3);
  LL_ADC_REG_SetSequencerRanks(3, LL_ADC_CHANNEL_6);
  LL_ADC_REG_SetSequencerRanks(4, LL_ADC_CHANNEL_9);
  LL_ADC_REG_SetSequencerRanks(5, LL_ADC_CHANNEL_12);
  LL_ADC_REG_SetSequencerRanks(6, LL_ADC_CHANNEL_13);
  
  LL_ADC_INJ_SetTrigAuto(LL_ADC_INJ_TRIG_INDEPENDENT);
  LL_ADC_INJ_SetSequencerLength(LL_ADC_INJ_SEQ_SCAN_RANKS_1);


  LL_ADC_DisableIT_EOS();
  LL_ADC_DisableIT_JEOSEQ();
  LL_ADC_DisableIT_EOSEQ();
  LL_ADC_DisableIT_JEOC();
  LL_ADC_DisableIT_EOC();

  LL_ADC_ClearFlag_EOC();
  LL_ADC_Enable();
}
#endif 

#if 0
// DMA 初始化配置
void DMA_Configuration()
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA);
  LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_3);

  LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_1);
  LL_SYSCFG_SetDMARemap_CH1(LL_SYSCFG_DMA_MAP_UART1_TX);

  LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_2);
  LL_SYSCFG_SetDMARemap_CH2(LL_SYSCFG_DMA_MAP_UART2_TX);
}

void LL_DMA_Configuration_Channel3(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize)
{
  LL_DMA_InitTypeDef DMA_InitStruct;
  LL_DMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.PeriphOrM2MSrcAddress = PeriphOrSrcAddr;
  DMA_InitStruct.MemoryOrM2MDstAddress = MemoryOrDstAddr;
  DMA_InitStruct.NbData = BufferSize;
  DMA_InitStruct.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA, LL_DMA_CHANNEL_3, &DMA_InitStruct);

  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_3);
}


void LL_DMA_Configuration_Channel1(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize)
{
  LL_DMA_InitTypeDef DMA_InitStruct;
  LL_DMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.PeriphOrM2MSrcAddress = PeriphOrSrcAddr;
  DMA_InitStruct.MemoryOrM2MDstAddress = MemoryOrDstAddr;
  DMA_InitStruct.NbData = BufferSize;
  DMA_InitStruct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA, LL_DMA_CHANNEL_1, &DMA_InitStruct);

  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_1);
}


void LL_DMA_Configuration_Channel2(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize)
{
  LL_DMA_InitTypeDef DMA_InitStruct;
  LL_DMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.PeriphOrM2MSrcAddress = PeriphOrSrcAddr;
  DMA_InitStruct.MemoryOrM2MDstAddress = MemoryOrDstAddr;
  DMA_InitStruct.NbData = BufferSize;
  DMA_InitStruct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA, LL_DMA_CHANNEL_2, &DMA_InitStruct);

  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_2);
}

#endif 
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
  TIM17_Configuration();
  IWDG_Configuration();
  I2C2_Configuration();
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
