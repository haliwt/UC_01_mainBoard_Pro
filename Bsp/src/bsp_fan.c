#include "bsp.h"


/**
*
*@brief 
*@notice
*@param
*
**/

void fan_stop(void)
{
  LL_TIM_OC_SetCompareCH1(TIM1, 0);

 // LL_TIM_DisableAllOutputs(TIM1); // 关闭主输出
  LL_TIM_DisableCounter(TIM1);    // 关闭计数器
}

/**
*
*@brief 
*@notice
*@param
*
**/

void fan_adjust_high_speed(void)
{
    
    LL_TIM_OC_SetCompareCH1(TIM1, 2560); // 设置 100% 占空比
	LL_TIM_EnableCounter(TIM1);             // 使能定时器计数器 (对应 TIM_Cmd)
    LL_TIM_EnableAllOutputs(TIM1);          // 使能主输出 (对应 TIM_CtrlPWMOutputs, 仅高级定时器 TIM1 需要)

}
/**
*
*@brief 
*@notice
*@param
*
**/

void fan_adjust_middle_speed(void)
{

	
	LL_TIM_OC_SetCompareCH1(TIM1, 2304); // 设置 90% 占空比
	LL_TIM_EnableCounter(TIM1); 			// 使能定时器计数器 (对应 TIM_Cmd)
	LL_TIM_EnableAllOutputs(TIM1);			// 使能主输出 (对应 TIM_CtrlPWMOutputs, 仅高级定时器 TIM1 需要)


}
/**
*
*@brief 
*@notice
*@param
*
**/

void fan_adjust_low_speed(void)
{

	LL_TIM_OC_SetCompareCH1(TIM1, 2048); // 设置 80% 占空比
	LL_TIM_EnableCounter(TIM1);             // 使能定时器计数器 (对应 TIM_Cmd)
    LL_TIM_EnableAllOutputs(TIM1);          // 使能主输出 (对应 TIM_CtrlPWMOutputs, 仅高级定时

}


/**
*
*@brief 
*@notice
*@param
*
**/

void wifiFan_Ctrl_Process(void)
{
   
	if(discharge_f){
	   if(works_interval_f == 0 && fan_rx_stop_flag ==0){
	      	
	     
		if((fan_open_f)){
			if(fan_speed_level < 34)
			{
			fan_on(10);
			}
			else if(fan_speed_level > 33 && fan_speed_level < 67)
			{
			fan_on(20);
			}
			else if(fan_speed_level==100 || fan_speed_level > 66)
			{
			fan_on(40);
			}

			///__NOP();__NOP();__NOP();__NOP();__NOP();

			//FAN_RUN_ON();
		}
    }
	}
}


