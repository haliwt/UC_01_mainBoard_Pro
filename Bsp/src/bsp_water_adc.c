#include "bsp.h"


/**
*
*@brief 
*@notice
*@param
*
**/
void water_pwm_on(void)
{
    LL_TIM_OC_SetCompareCH1(TIM16,100); // 设置 50% 占空比
	LL_TIM_EnableCounter(TIM16);             // 使能定时器计数器 (对应 TIM_Cmd)
    LL_TIM_EnableAllOutputs(TIM16);          // 使能主输出 (对应 TIM_CtrlPWMOutputs, 仅高级定时    
}

void water_pwm_off(void)
{

    LL_TIM_OC_SetCompareCH1(TIM16,0);         // 设置 0% 占空比
	LL_TIM_DisableCounter(TIM16);             // 禁止定时器计数器 (对应 TIM_Cmd)
              
}


