#include "gpio.h"

// GPIO 初始化配置
// GPIO 初始化配置
void GPIO_Configuration(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);

  // GPIO_Output
  //LL_GPIO_ResetOutputPin(LED_AI_GPIO_Port, LL_LED_AI_Pin);
  LL_GPIO_SetOutputPin(LED_AI_GPIO_Port,LL_LED_AI_Pin);
  
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
  GPIO_InitStruct.Pin = LL_WATER_POS_Pin | LL_KEY_POWER_Pin | LL_KEY_AI_Pin | LL_KEY_FAN_Pin | LL_KEY_PLASMA_Pin;
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
  //LL_GPIO_ResetOutputPin(LED_PLASMA_GPIO_Port, LL_LED_PLASMA_Pin);
  LL_GPIO_SetOutputPin(LED_PLASMA_GPIO_Port, LL_LED_PLASMA_Pin);//output high level
  LL_GPIO_SetOutputPin(LED_FAN_GPIO_Port, LL_LED_FAN_Pin);
  LL_GPIO_SetOutputPin(LED_POWER_GPIO_Port, LL_LED_POWER_Pin);
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

  #if 0
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
  #endif 
  LL_GPIO_SetOutputPin(I2C_SCL_GPIO_Port, LL_I2C_SCL_Pin);
  LL_GPIO_SetOutputPin(I2C_SDA_GPIO_Port, LL_I2C_SDA_Pin);
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_I2C_SCL_Pin| LL_I2C_SDA_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

   // GPIO_Input
  LL_GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_ANGLE_SENSOR_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(ANGLE_SENSOR_GPIO_Port, &GPIO_InitStruct);
  
}


