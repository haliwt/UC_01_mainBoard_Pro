#include "bsp.h"



// 定义 TEC 状态枚举
typedef enum {
    TEC_STATE_OFF = 0,
    TEC_STATE_ON = 1
} TecState_t;

// 静态变量记录当前 TEC 状态，防止重复发送控制指令
static TecState_t s_tec_state = TEC_STATE_OFF; 

/**
 * @brief  TEC 温度控制逻辑函数
 * @note   建议在主循环（Main Loop）或定时器任务中周期性调用此函数
 */
void TEC_Temperature_Control(void) 
{
    // 1. 温度大于等于 40 度，关闭 TEC
    if (gpro_t.temperature >= 40) {
        if (s_tec_state != TEC_STATE_OFF) {
            TEC_CTRL_OFF();
            s_tec_state = TEC_STATE_OFF;
            // printf("温度过高 (>= 40℃)，关闭 TEC\n"); // 调试信息（可选）
        }
    }
    // 2. 温度下降到 37 度或以下，再次打开 TEC
    else if (gpro_t.temperature <= 37) {
        if (s_tec_state != TEC_STATE_ON) {
            TEC_CTRL_ON();
            s_tec_state = TEC_STATE_ON;
            // printf("温度恢复 (<= 37℃)，打开 TEC\n"); // 调试信息（可选）
        }
    }
    // 3. 温度处于 37℃ ~ 40℃ 之间时，保持当前状态不变（迟滞区）
}



