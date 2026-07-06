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




//Display Board TX and RX 
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

  UART1->ICR = 0xFF;//ICR：Interrupt Clear Register 的缩写，即 “中断清除寄存器”。
}


/**
* @brief  UART2�����ַ���
 * @param  String: �ַ���
 * @retval None
 */
// UART1 初始化配置,Display Board bpd = 9600
void UART1_Configuration(void)
{
  LL_UART_InitTypeDef UART_InitStructure= {0};

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UART1);

  LL_UART_DeInit(UART1);
  LL_UART_StructInit(&UART_InitStructure);
  UART_InitStructure.BaudRate = 9600;
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

  UART2->ICR = 0xFF;//ICR：Interrupt Clear Register 的缩写，即 “中断清除寄存器”。
}

// UART2 初始化配置
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


/* USER CODE BEGIN fputc */
#if defined ( __CC_ARM )
int fputc(int ch, FILE *f)
{
  LL_UART_TransmitData8(UART1, ch);
  while(LL_UART_IsActiveFlag_TC(UART1) == RESET);
  return ch;
}
#elif defined ( __GNUC__ )
int _write(int file, char *ptr, int len)
{
  for (int i = 0; i < len; ++i)
  {
    LL_UART_TransmitData8(UART1, ptr[i]);
    while(LL_UART_IsActiveFlag_TC(UART1) == RESET);
  }
  return len;
}
#endif
/* USER CODE END fputc */



/**
  * @brief  UART1 DMA 发送函数（非阻塞）
  * @param  pData: 待发送的数据缓冲区指针
  * @param  Size:  发送数据长度
  */
void UART1_DMA_Disp_Send(const uint8_t *pData, uint16_t Size)
{

  /* 1. 安全边界检查：指针为空或长度为0时直接退出，拒绝非法非法操作 */
  if (pData == NULL || Size == 0) return ;
  /* 1. 等待上一次 DMA 发送完成（如果通道还开启着，说明还没发完） */
  while(LL_DMA_IsEnabledChannel(DMA, LL_DMA_CHANNEL_1));

  /* 2. 清除通道 1 的传输完成标志位 */
  LL_DMA_ClearFlag_TC1(DMA);

  /* 3. 动态重新配置内存地址和数据长度 */
  LL_DMA_SetMemoryAddress(DMA, LL_DMA_CHANNEL_1, (uint32_t)pData);
  LL_DMA_SetDataLength(DMA, LL_DMA_CHANNEL_1, Size);

  /* 4. 使能 DMA 通道，立刻启动硬件级发送 */
  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_1);
}


/**
  * @brief  UART2 DMA 发送函数（非阻塞）
  */
void UART2_DMA_Wifi_Send(const uint8_t *pData, uint16_t Size)
{

  /* 1. 安全边界检查：指针为空或长度为0时直接退出，拒绝非法非法操作 */
  if (pData == NULL || Size == 0) return ;
  
  while(LL_DMA_IsEnabledChannel(DMA, LL_DMA_CHANNEL_2));
  LL_DMA_ClearFlag_TC2(DMA);

  LL_DMA_SetMemoryAddress(DMA, LL_DMA_CHANNEL_2, (uint32_t)pData);
  LL_DMA_SetDataLength(DMA, LL_DMA_CHANNEL_2, Size);

  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_2);
}










