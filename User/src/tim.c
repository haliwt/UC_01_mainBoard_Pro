/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    TIM.C
  * @author  Yspring Firmware Team  
  * @brief   TIM Source Code.
  ******************************************************************************      
*/

#include "ys32t031.h"
#include "tim.h"
#include "bsp.h"

// TIM1 初始化配置  风扇 25KHZ 
void TIM1_Configuration(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  // Overflow time = ((Auto-reload 31999 + 1) * (Prescaler 0 + 1)) / 64000000 = 500 μs, frequency= 2 kHz
  // 频率计算: 64,000,000 / ((0 + 1) * (2559 + 1)) = 25,000 Hz (25 kHz)
  LL_TIM_StructInit(&TIM_InitStruct);
  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.Autoreload = 2559; // TIM_ARR
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

// TIM3 初始化配置 蜂鸣器 4KHZ
void TIM3_Configuration(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  // Overflow time = ((Auto-reload 31999 + 1) * (Prescaler 0 + 1)) / 64000000 = 500 μs, frequency= 2 kHz
  // Overflow time = ((Auto-reload 2559 + 1) * (Prescaler 0 + 1)) / 64000000 = 40 μs, frequency = 25 kHz
  // Overflow time = ((Auto-reload 15999 + 1) * (Prescaler 0 + 1)) / 64000000 = 250 μs, frequency = 4 kHz
  LL_TIM_StructInit(&TIM_InitStruct);
  TIM_InitStruct.Prescaler = 63;
  TIM_InitStruct.Autoreload =249;//4KHZ // TIM_ARR
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

// TIM16 初始化配置 PMW 检测水位 20
void TIM16_Configuration(void)
{
	LL_TIM_InitTypeDef TIM_InitStruct = {0};
	 LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
	
	 LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM16);
	
	 // Overflow time = ((Auto-reload 39 + 1) * (Prescaler 63 + 1)) / 64000000 = 40 μs, frequency= 25 kHz
	 LL_TIM_StructInit(&TIM_InitStruct);
	 TIM_InitStruct.Prescaler = 63;
	 TIM_InitStruct.Autoreload = 39; // TIM_ARR
	 TIM_InitStruct.ClockDivision = 0;
	 TIM_InitStruct.RepetitionCounter = 0;
	 LL_TIM_Init(TIM16, &TIM_InitStruct);
	
	 LL_TIM_OC_StructInit(&TIM_OC_InitStruct);
	 TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
	 TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
	 TIM_OC_InitStruct.CompareValue = 0; // TIM_CCR, Duty = TIM_CCR/(TIM_ARR+1)
	 TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_LOW;
	 TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
	 LL_TIM_OC_Init(TIM16,LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
	
	 LL_TIM_EnableCounter(TIM16);
	 LL_TIM_EnableAllOutputs(TIM16);

}


// TIM17 初始化配置
void TIM17_Configuration(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM17);

  // Overflow time = ((Auto-reload 63999 + 1) * (Prescaler 9 + 1)) / 64000000 = 10 ms, frequency= 100 Hz
  LL_TIM_StructInit(&TIM_InitStruct);
  TIM_InitStruct.Prescaler = 63;
  TIM_InitStruct.Autoreload = 999; // 计 1000 个数 = 1000us = 10ms// TIM_ARR
  TIM_InitStruct.ClockDivision = 0;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM17, &TIM_InitStruct);

  LL_TIM_EnableIT_UPDATE(TIM17);
  LL_TIM_EnableCounter(TIM17);
}












