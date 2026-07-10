#include "bsp.h"


/**
*
*@brief 
*@notice
*@param
*
**/
void beep_on(void)
{
    LL_TIM_OC_SetCompareCH4(TIM3,125); // 设置 50% 占空比
	LL_TIM_EnableCounter(TIM3);             // 使能定时器计数器 (对应 TIM_Cmd)
    LL_TIM_EnableAllOutputs(TIM3);          // 使能主输出 (对应 TIM_CtrlPWMOutputs, 仅高级定时    
	tx_thread_sleep(2);
    LL_TIM_OC_SetCompareCH4(TIM3,0);         // 设置 0% 占空比
	LL_TIM_DisableCounter(TIM3);             // 禁止定时器计数器 (对应 TIM_Cmd)
              
}
/**
  * @brief 
  * @note  
  * @param: 
  *
**/

void beep_off(void)
{
	LL_TIM_OC_SetCompareCH4(TIM3,0);         // 设置 0% 占空比
	LL_TIM_DisableCounter(TIM3);             // 禁止定时器计数器 (对应 TIM_Cmd)  

}
/**
  * @brief 
  * @note  
  * @param: 
  *
**/
void beep_high_temperature_sound(void)
{
	beep_on();
	tx_thread_sleep(20);
	beep_on();
	tx_thread_sleep(20);
	beep_on();
	tx_thread_sleep(20);
	beep_on();
	tx_thread_sleep(20);
	beep_on();
	tx_thread_sleep(20);
	beep_on();
	tx_thread_sleep(20);

}
/**
  * @brief  
  * @note  
  * @param: 
  *
**/
void beep_fan_default_sound(void)
{
	beep_on();
	tx_thread_sleep(40);
	beep_on();
	tx_thread_sleep(40);
	beep_on();
	tx_thread_sleep(40);
	beep_on();
	tx_thread_sleep(40);
	beep_on();
	tx_thread_sleep(40);
	beep_on();
	tx_thread_sleep(40);

}



