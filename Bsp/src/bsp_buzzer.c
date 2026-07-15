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
	//tx_thread_sleep(2);                     // 2*10ms =20ms 
   // LL_TIM_OC_SetCompareCH4(TIM3,0);         // 设置 0% 占空比
	///LL_TIM_DisableCounter(TIM3);             // 禁止定时器计数器 (对应 TIM_Cmd)
              
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


// 如果你的按键还需要原来的短响一声功能，可以单独封装成这个函数给按键用：
void beep_key_click(void)
{
    LL_TIM_OC_SetCompareCH4(TIM3,125); // 设置 50% 占空比
	LL_TIM_EnableCounter(TIM3);             // 使能定时器计数器 (对应 TIM_Cmd)
    LL_TIM_EnableAllOutputs(TIM3);          // 使能主输出 (对应 TIM_CtrlPWMOutputs, 仅高级定时    
	tx_thread_sleep(2);                     // 2*10ms =20ms 
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
	beep_key_click();
	tx_thread_sleep(20);//10ms*20 = 200ms
	beep_key_click();
	tx_thread_sleep(20);
	beep_key_click();
	tx_thread_sleep(20);
	beep_key_click();
	tx_thread_sleep(20);
	beep_key_click();
	tx_thread_sleep(20);
	beep_key_click();
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
	beep_key_click();
	tx_thread_sleep(10);//10ms*40 = 400ms
	beep_key_click();
	tx_thread_sleep(10);
	beep_key_click();
	tx_thread_sleep(10);
	beep_key_click();
	tx_thread_sleep(110);
	beep_key_click();
	tx_thread_sleep(10);
	beep_key_click();
	tx_thread_sleep(40);

}

/**
  * @brief  
  * @note  
  * @param: 
  *
**/
void beep_water_warning_sound(void)
{
	beep_key_click();
	tx_thread_sleep(10);//10ms*50 = 400ms
	beep_key_click();
	tx_thread_sleep(10);
	beep_key_click();
	tx_thread_sleep(10);
	beep_key_click();
	tx_thread_sleep(10);
	beep_key_click();
	tx_thread_sleep(10);
	beep_key_click();
	tx_thread_sleep(10);

}



