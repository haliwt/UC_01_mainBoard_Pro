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
#include "bsp.h"

/*接收数据中断（RXNE - Receive Data Register Not Empty*/

static uint32_t HCLK,PCLK;
#define  Freq_M    (1000000U) 


/**
* @brief  UART1 displayBoard
 * @param  String: 
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

  LL_UART_EnableDMAReq_TX(UART1);
  
  LL_UART_EnableIT_RXNE(UART1);
  LL_UART_EnableIT_TC(UART1);
  // LL_UART_EnableIT_IDLE(UART1); //Ê¹ÄÜUART1µÄ¿ÕÏÐÖÐ¶Ï

  LL_UART_Enable(UART1);

 
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



//Display Board TX and RX 
void UART1_Int_Call(void)
{
  uint8_t res ;
   //uint8_t ch = 0 ;
  
  if(LL_UART_IsActiveFlag_RXNE(UART1)&& LL_UART_IsEnabledIT_RXNE(UART1))
  {
    /* USER CODE BEGIN Code_UART1_Int_Call_UART_FLAG_RXNE */
     res =  LL_UART_ReceiveData8(UART1);
	  usart1_isr_callback_handler(res);
    
    /* USER CODE END Code_UART1_Int_Call_UART_FLAG_RXNE */
  }

  /* =====================================================================
       2. 溢出错误处理 (ORE) —— 彻底防止串口死锁卡死
       ===================================================================== */
    // 检查是否触发了溢出错误（上一个数据没读走，新数据又覆盖上来了）
    if (LL_UART_IsActiveFlag_ORE(UART1))
    {
        /* 
           【核心解锁步骤】
           必须先强行读取一次数据寄存器（DR）。
           这一步是为了清空移位寄存器和硬件缓冲区，向外设硬件发出“允许继续接收”信号。
           如果不读 DR，单纯清除标志位，硬件的接收移位状态机依然处于锁死状态。
        */
        volatile uint32_t dummy_read = UART1->RDR; 
        
        // 使用 volatile 防止这行没用的读取代码被编译器优化掉
        ((void)dummy_read); 
        
        /* 
           可以增加一个错误计数器，方便你在 ThreadX 任务中监控串口健康度
           g_uart1_error_count.ore_count++; 
        */
    }

  if (LL_UART_IsActiveFlag_TC(UART1) && LL_UART_IsEnabledIT_TC(UART1))
  {
    /* USER CODE BEGIN Code_UART1_Int_Call_UART_FLAG_TC */
    
    /* USER CODE END Code_UART1_Int_Call_UART_FLAG_TC */
    LL_UART_ClearFlag_TC(UART1);
  }

  UART1->ICR = 0xFF;//ICR：Interrupt Clear Register 的缩写，即 “中断清除寄存器”。
  //LL_UART_ClearFlag_ORE(UART1)
}



//  #else 
//	 if(LL_UART_IsActiveFlag_IDLE(UART1) && LL_UART_IsEnabledIT_IDLE(UART1))
//    {
//        LL_UART_ClearFlag_IDLE(UART1);
//        LL_UART_ClearFlag_RTO(UART1);

//        ch =  LL_UART_ReceiveData8(UART1);
//	    usart1_isr_callback_handler(ch);
        
     
//    }

//  #endif 




/**
* @brief  UART2  wifi 
 * @param  String: �ַ���
 * @retval None
 */

void UART2_Int_Call(void)
{
  if(LL_UART_IsActiveFlag_RXNE(UART2)&& LL_UART_IsEnabledIT_RXNE(UART2))
  {
    /* USER CODE BEGIN Code_UART2_Int_Call_UART_FLAG_RXNE */
    // LL_UART_ReceiveData8(UART2);
    
    /* USER CODE END Code_UART2_Int_Call_UART_FLAG_RXNE */
  }

    /* =====================================================================
       2. 溢出错误处理 (ORE) —— 彻底防止串口死锁卡死
       ===================================================================== */
    // 检查是否触发了溢出错误（上一个数据没读走，新数据又覆盖上来了）
    if (LL_UART_IsActiveFlag_ORE(UART2))
    {
        /* 
           【核心解锁步骤】
           必须先强行读取一次数据寄存器（DR）。
           这一步是为了清空移位寄存器和硬件缓冲区，向外设硬件发出“允许继续接收”信号。
           如果不读 DR，单纯清除标志位，硬件的接收移位状态机依然处于锁死状态。
        */
        volatile uint32_t dummy_read = UART2->RDR; 
        
        // 使用 volatile 防止这行没用的读取代码被编译器优化掉
        ((void)dummy_read); 
        
        /* 
           可以增加一个错误计数器，方便你在 ThreadX 任务中监控串口健康度
           g_uart1_error_count.ore_count++; 
        */
    }

  if (LL_UART_IsActiveFlag_TC(UART2) && LL_UART_IsEnabledIT_TC(UART2))
  {
    /* USER CODE BEGIN Code_UART2_Int_Call_UART_FLAG_TC */
    
    /* USER CODE END Code_UART2_Int_Call_UART_FLAG_TC */
    LL_UART_ClearFlag_TC(UART2);
  }

  UART2->ICR = 0xFF;//ICR：Interrupt Clear Register 的缩写，即 “中断清除寄存器”。
}







/**
  * @brief  UART1 DMA 发送函数（非阻塞）--display board
  * @param  pData: 待发送的数据缓冲区指针
  * @param  Size:  发送数据长度
  */
void UART1_DMA_Disp_Send(const uint8_t *pData, uint16_t Size)
{

  /* 1. 安全边界检查：指针为空或长度为0时直接退出，拒绝非法非法操作 */
  if (pData == NULL || Size == 0) return ;
  /* 1. 等待上一次 DMA 发送完成（如果通道还开启着，说明还没发完） */
 // while(LL_DMA_IsEnabledChannel(DMA, LL_DMA_CHANNEL_1));
 /* 【安全修改 1】通过检查 TC 标志位或剩余数据量来判断是否发送完成，而不是仅看 Enable 状态 */
    // 如果通道开着，且传输计数器不为 0，说明还在发，等待它发完
 /* 2. 判断上一次是否发完：如果通道开着，且【剩余传输计数不为0】，说明还在发，等待它发完 */
  // LL_DMA_GetDataLength 读取的是剩余要发送的字节数（递减计数器）
  while(LL_DMA_IsEnabledChannel(DMA, LL_DMA_CHANNEL_1) && (LL_DMA_GetDataLength(DMA, LL_DMA_CHANNEL_1) > 0));

	/* 3. 必须先关闭通道，才能重新配置数据长度 */
  LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_1);


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





/* USER CODE BEGIN fputc */
//#if defined ( __CC_ARM )
int fputc(int ch, FILE *f)
{

  LL_UART_TransmitData8(UART2, ch);
  while (!LL_UART_IsActiveFlag_TXE(UART2));

  return ch;
}



// 自己写一个安全的、绝对不依赖 C 库的字符发送函数
void My_UART_SendChar(uint8_t ch) 
{
    // 只有时钟开启且寄存器有效时，这样写才安全
    // 如果怕卡死，这里甚至不需要等
    UART1->TDR = ch; 
}



