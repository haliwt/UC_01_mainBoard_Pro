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
 * @brief  风扇挡位调节处理函数
 * @note   每次调用该函数，根据当前的按键计数切换风扇速度
 * @param  None
 * @retval None
 */
void fan_speed_adjust_handler(uint8_t fan_value)
{
    switch (fan_value)
    {
        case 1:
            fan_adjust_low_speed();    // 切换到低速档
            break;

        case 2:
            fan_adjust_middle_speed(); // 切换到中速档
            break;

        case 3:
            fan_adjust_high_speed();   // 切换到高速档
            break;

        default:
                       // 计数器清零
            //fan_adjust_off();          // 【优化建议】：此处建议调用关闭风扇的函数，实现 1->2->3->关 的循环
        break;
    }
}



