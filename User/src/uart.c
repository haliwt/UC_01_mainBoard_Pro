/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    uart.C
  * @author  Yspring Firmware Team  
  * @brief   uart Source Code.
  ******************************************************************************      
*/

#include "uart.h"   
#include "ys32t031.h"





void UART1_Int_Call(void)
{
  if(LL_UART_IsActiveFlag_RXNE(UART1)&& LL_UART_IsEnabledIT_RXNE(UART1))
  {
    /* USER CODE BEGIN Code_UART1_Int_Call_UART_FLAG_RXNE */
    // UART_ReceiveData(UART1);
    
    /* USER CODE END Code_UART1_Int_Call_UART_FLAG_RXNE */
  }

  if (LL_UART_IsActiveFlag_TC(UART1) && LL_UART_IsEnabledIT_TC(UART1))
  {
    /* USER CODE BEGIN Code_UART1_Int_Call_UART_FLAG_TC */
    
    /* USER CODE END Code_UART1_Int_Call_UART_FLAG_TC */
    LL_UART_ClearFlag_TC(UART1);
  }

  UART1->ICR = 0xFF;
}


/**
* @brief  UART2∑¢ÀÕ◊÷∑˚¥Æ
 * @param  String: ◊÷∑˚¥Æ
 * @retval None
 */
// UART1 ÂàùÂßãÂåñÈÖçÁΩÆ
void UART1_Configuration(void)
{
  LL_UART_InitTypeDef UART_InitStructure= {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UART1);

  LL_UART_DeInit(UART1);
  LL_UART_StructInit(&UART_InitStructure);
  UART_InitStructure.BaudRate = 115200;
  UART_InitStructure.DataWidth = LL_UART_DATAWIDTH_8B;
  UART_InitStructure.StopBits = LL_UART_STOPBITS_1;
  UART_InitStructure.Parity = LL_UART_PARITY_NONE;
  UART_InitStructure.TransferDirection = LL_UART_DIRECTION_TX_RX;
  LL_UART_Init(UART1, &UART_InitStructure);

  LL_UART_EnableIT_RXNE(UART1);
  LL_UART_EnableIT_TC(UART1);

  LL_UART_Enable(UART1);
}

void UART2_Int_Call(void)
{
  if(LL_UART_IsActiveFlag_RXNE(UART2)&& LL_UART_IsEnabledIT_RXNE(UART2))
  {
    /* USER CODE BEGIN Code_UART2_Int_Call_UART_FLAG_RXNE */
    // UART_ReceiveData(UART2);
    
    /* USER CODE END Code_UART2_Int_Call_UART_FLAG_RXNE */
  }

  if (LL_UART_IsActiveFlag_TC(UART2) && LL_UART_IsEnabledIT_TC(UART2))
  {
    /* USER CODE BEGIN Code_UART2_Int_Call_UART_FLAG_TC */
    
    /* USER CODE END Code_UART2_Int_Call_UART_FLAG_TC */
    LL_UART_ClearFlag_TC(UART2);
  }

  UART2->ICR = 0xFF;
}

// UART2 ÂàùÂßãÂåñÈÖçÁΩÆ
void UART2_Configuration(void)
{
  LL_UART_InitTypeDef UART_InitStructure= {0};

  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART2);

  LL_UART_DeInit(UART2);
  LL_UART_StructInit(&UART_InitStructure);
  UART_InitStructure.BaudRate = 115200;
  UART_InitStructure.DataWidth = LL_UART_DATAWIDTH_8B;
  UART_InitStructure.StopBits = LL_UART_STOPBITS_1;
  UART_InitStructure.Parity = LL_UART_PARITY_NONE;
  UART_InitStructure.TransferDirection = LL_UART_DIRECTION_TX_RX;
  LL_UART_Init(UART2, &UART_InitStructure);

  LL_UART_EnableIT_RXNE(UART2);
  LL_UART_EnableIT_TC(UART2);

  LL_UART_Enable(UART2);
}



//¥Ú”° ‰≥ˆ
int fputc(int ch, FILE *f)
{
    UART1_SendByte(ch);
    return ch;
}













