/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    TIM.H
  * @version V1.0.0
  * @date    2024
  * @author  Yspring Firmware Team  
  * @brief   TIM Header Code.
  ******************************************************************************      
*/
#ifndef __TIM_H
#define __TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "ys32t031.h"


void TIM1_Configuration(void);

void TIM3_Configuration(void);

void TIM17_Configuration(void);


#ifdef __cplusplus
}
#endif

#endif /* __TIM_H */
