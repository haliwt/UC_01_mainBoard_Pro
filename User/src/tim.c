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

// TIM1 ÂàùÂßãÂåñÈÖçÁΩÆ
void TIM1_Configuration(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  // Overflow time = ((Auto-reload 31999 + 1) * (Prescaler 0 + 1)) / 64000000 = 500 Œºs, frequency= 2 kHz
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

// TIM3 ÂàùÂßãÂåñÈÖçÁΩÆ
void TIM3_Configuration(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  // Overflow time = ((Auto-reload 31999 + 1) * (Prescaler 0 + 1)) / 64000000 = 500 Œºs, frequency= 2 kHz
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

// TIM17 ÂàùÂßãÂåñÈÖçÁΩÆ
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





#if 0
// TIM1 ≥ı ºªØ≈‰÷√
void TIM1_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    // “Á≥ˆ ±º‰ = ((◊‘∂Ø÷ÿ◊∞÷µ319 + 1) * (∑÷∆µœµ ˝ 5 + 1)) / 48000000 = 40 ¶Ãs, ∆µ¬ = 25 kHz
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 47;// 5;
    TIM_TimeBaseStructure.TIM_Period = 39;//319;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OC3Init(TIM1, &TIM_OCInitStructure); //ÈÄöÈÅì 3

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);//ÈÄöÈÅì 1 

    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}



// TIM3 FAN IS SET 25KHZ FREQUENCY 
void TIM3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // “Á≥ˆ ±º‰ = ((◊‘∂Ø÷ÿ◊∞÷µ319 + 1) * (∑÷∆µœµ ˝ 5 + 1)) / 48000000 = 40 ¶Ãs, ∆µ¬ = 25 kHz
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 5;//47;//5; SYSCLOCK IS 48MHZ .
    TIM_TimeBaseStructure.TIM_Period = 319;//39;//319; //F =1/(39+1)= 0.025MHZ 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    TIM_Cmd(TIM3, ENABLE);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);  
}



// TIM6 ≥ı ºªØ≈‰÷√
void TIM6_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    // “Á≥ˆ ±º‰ = ((◊‘∂Ø÷ÿ◊∞÷µ3332 + 1) * (∑÷∆µœµ ˝ 47 + 1)) / 48000000 = 5 ms, ∆µ¬ = 200 Hz
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 95;
    TIM_TimeBaseStructure.TIM_Period = 2499;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	  TIM_ClearFlag(TIM6, TIM_FLAG_Update);                   // «Â≥˝º∆ ˝∆˜÷–∂œ±Í÷æŒª  
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	
    TIM_Cmd(TIM6, ENABLE);
}



// TIM14 ≥ı ºªØ≈‰÷√
void TIM14_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM14, ENABLE);

    // “Á≥ˆ ±º‰ = ((◊‘∂Ø÷ÿ◊∞÷µ749 + 1) * (∑÷∆µœµ ˝ 15 + 1)) / 48000000 = 250 ¶Ãs, ∆µ¬ = 4 kHz
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 15;
    TIM_TimeBaseStructure.TIM_Period = 749;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OC1Init(TIM14, &TIM_OCInitStructure);

    TIM_Cmd(TIM14, ENABLE);
    TIM_CtrlPWMOutputs(TIM14, ENABLE);
}



//∑‰√˘∆˜ø™
//void BEEP_ON(void)
//{
//    TIM_SetCompare1(TIM14,374);
//    TIM_Cmd(TIM14, ENABLE);
//    TIM_CtrlPWMOutputs(TIM14, ENABLE);
//	tx_thread_sleep(2);//2*10ms =20ms
//	//TIM_SetCompare1(TIM14,0);
	
//	TIM_Cmd(TIM14, DISABLE);
//}


////∑‰√˘∆˜πÿ
//void BEEP_OFF(void)
//{
//    TIM_SetCompare1(TIM14,0);
	
//	TIM_Cmd(TIM14, DISABLE);
//    //TIM_CtrlPWMOutputs(TIM14, ENABLE);
//}



//∑Á…»ø™
void fan_on(uint16_t fan_duty)
{
    #if 0
	TIM_SetCompare1(TIM3,fan_duty);
	
	TIM_Cmd(TIM3, ENABLE);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
	#else 

	TIM_SetCompare1(TIM1,fan_duty);
	
	TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	#endif 
}


//∑Á…»πÿ
void fan_off(void)
{
//    TIM_SetCompare1(TIM3,0);
	
//	TIM_Cmd(TIM3, DISABLE);
//    TIM_CtrlPWMOutputs(TIM3, DISABLE);
	fan_on(0);

}



//≥¨…˘≤®ø™
void ultra_sound_on(uint16_t us_duty)
{
    
	TIM_SetCompare3(TIM1,us_duty);
	
	  TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
}


//≥¨…˘≤®πÿ
void ultra_sound_off(void)
{
    TIM_SetCompare3(TIM1,0);
	
	  TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

#endif 








