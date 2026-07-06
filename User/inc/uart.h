/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    uart.H
  * @version V1.0.0
  * @date    2024
  * @author  Yspring Firmware Team  
  * @brief   uart Header Code.
  ******************************************************************************      
*/
#ifndef __UART_H
#define __UART_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "main.h"		
#include <stdint.h>  


void UART1_Int_Call(void);


void UART1_Configuration(void);

void UART2_Configuration(void);

void UART1_DMA_Disp_Send(const uint8_t *pData, uint16_t Size);

void UART2_DMA_Wifi_Send(const uint8_t *pData, uint16_t Size);



#ifdef __cplusplus
}
#endif

#endif /* __UART_H */

