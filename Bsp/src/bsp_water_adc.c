#include "bsp.h"

// 硬件控制宏定义
#define ALARM_ON()    Platform_Buzzer_Set(1)  // 开启报警
#define ALARM_OFF()   Platform_Buzzer_Set(0)  // 关闭报警

// 传感器“有水”的电压阈值（单位：mV，根据实际传感器微调）
#define WATER_TOUCH_THRESHOLD_MV    2000


// 定义水位等级枚举
typedef enum {
    LEVEL_0_EMPTY = 0,      // 无水/极低水位
    LEVEL_1_LOW,            // 1级低水位 (对应 adc_water_1)
    LEVEL_2_MEDIUM,         // 2级中水位 (对应 adc_water_2)
    LEVEL_3_HIGH,           // 3级高水位 (对应 adc_water_3)
    LEVEL_4_MAX_WARN        // 4级最高水位/报警 (对应 adc_water_warning)
} WaterLevel_t;


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

/* ==================== 2. 多级水位核心检测与报警逻辑 ==================== */

/**
 * @brief  获取当前综合水位等级
 * @return WaterLevel_t 当前的水位状态 (LEVEL_0 到 LEVEL_4)
 */
WaterLevel_t Get_Current_Water_Level(void)
{
    // 读取 4 个通道的实时电压值
    uint16_t v_water_3 = adc_water_3_value();
    uint16_t v_water_2 = adc_water_2_value();
    uint16_t v_water_1 = adc_water_1_value();
    uint16_t v_water_warn = adc_water_warning_value();

    // 采用“从最高级向最低级”倒推的逻辑判定
    // 只要高级别传感器有水，说明水位已经到达该高度
    if (v_water_warn >= WATER_TOUCH_THRESHOLD_MV) 
    {
        return LEVEL_4_MAX_WARN; // 最高级报警水位
    }
    else if (v_water_3 >= WATER_TOUCH_THRESHOLD_MV) 
    {
        return LEVEL_3_HIGH;     // 高水位
    }
    else if (v_water_2 >= WATER_TOUCH_THRESHOLD_MV) 
    {
        return LEVEL_2_MEDIUM;   // 中水位
    }
    else if (v_water_1 >= WATER_TOUCH_THRESHOLD_MV) 
    {
        return LEVEL_1_LOW;      // 低水位
    }
    
    return LEVEL_0_EMPTY;        // 容器空或低于1级水位
}

/**
 * @brief  水位监控主处理函数（需在主循环中持续调用）
 */
void Water_System_Process(void)
{
    // 获取当前的水位等级
    WaterLevel_t current_level = Get_Current_Water_Level();
    
    // 报警消抖计数器
    static uint8_t alarm_debounce_cnt = 0;
	static uint16_t beep_cycle_cnt = 0;    // 蜂鸣器节奏计数器

    // 根据水位等级进行相应处理
    switch (current_level)
    {
        case LEVEL_4_MAX_WARN:
            // 达到了最高一级水位，触发报警消抖
            if (alarm_debounce_cnt < 5) 
            {
                alarm_debounce_cnt++;
            }
            else 
            {
               // ALARM_ON(); // 确认为最高水位，持续报警！
               /* ---------- 10ms 非阻塞声音控制核心算法 ---------- */
	            beep_cycle_cnt++;
			    LED_WATER_WARNING();
	            
	            if (beep_cycle_cnt <= 20)      // 1 ~ 20 次循环 (0 ~ 200ms) -> 鸣叫
	            {
	                beep_on();
	            }
	            else if (beep_cycle_cnt <= 40) // 21 ~ 40 次循环 (200ms ~ 400ms) -> 闭嘴
	            {
	                beep_off(); 
	            }
	            
	            if (beep_cycle_cnt >= 40)      // 满 400ms 重置，开始下一轮“嘀-哒-”
	            {
	                beep_cycle_cnt = 0;
	            }
	        }
            break;

        case LEVEL_3_HIGH:
           LED_WATER_LEVEL_3();
		break;
		
        case LEVEL_2_MEDIUM:
			LED_WATER_LEVEL_2();

		break;
			
        case LEVEL_1_LOW:
			LED_WATER_LEVEL_1();

		break;
			
        case LEVEL_0_EMPTY:
			  LED_WATER_INDICATOR_1();
			  LED_WATER_INDICATOR_2();
		      LED_WATER_INDICATOR_3();
			  LED_WATER_INDICATOR_4();
		

		break;

		
        default:
            // 未达到最高警告水位，或者水位退下来了，解除报警
            if (alarm_debounce_cnt > 0) 
            {
                alarm_debounce_cnt--;
            }
            else 
            {
                beep_off(); //ALARM_OFF(); // 安全水位，关闭报警器
            }
       break;
    }

    /* 提示：你可以利用 current_level 变量去驱动你的屏幕或者 LED。
       例如：
       if (current_level == LEVEL_1_LOW) { Light_Up_LED1(); }
    */
}
