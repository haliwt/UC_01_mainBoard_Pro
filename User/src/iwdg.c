/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    iwdg.C
  * @author  Yspring Firmware Team  
  * @brief   iwdg Source Code.
  ******************************************************************************      
*/

#include "iwdg.h"
#include "ys32t031.h"



// IWDG 初始化配置
void IWDG_Configuration(void)
{
  // 1. 开启 LSI 并等待时钟稳定
  LL_RCC_LSI_Enable();
  // 2. 开启 IWDG 外设时钟
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_IWDG);
  
  // 3. 开启寄存器写权限
  LL_IWDG_EnableWriteAccess(IWDG);
  // 4. 设置预分频为 256
  LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_256);

  // 5. 设置重装载值为 1000 (计算: 256 * 1000 / 32000Hz = 8.0 秒)
  LL_IWDG_SetReloadCounter(IWDG, 1000);
  while (LL_IWDG_IsReady(IWDG) == RESET){}
  
  // 7. 窗口值设为最大（4095），关闭窗口限制，允许任意时刻喂狗
  LL_IWDG_SetWindow(IWDG, 4095);

  // 8. 刷新计数器并使能看门狗
  LL_IWDG_ReloadCounter(IWDG);
  LL_IWDG_Enable(IWDG);
}






