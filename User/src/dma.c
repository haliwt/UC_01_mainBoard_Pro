#include "dma.h"
// DMA 初始化配置
void DMA_Configuration()
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA);
  LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_3);

  LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_1);
  LL_SYSCFG_SetDMARemap_CH1(LL_SYSCFG_DMA_MAP_UART1_TX);

  LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_2);
  LL_SYSCFG_SetDMARemap_CH2(LL_SYSCFG_DMA_MAP_UART2_TX);
}



/**
  * @brief   ADC DMA 6 channel 
  * @note  
  * @param: 
  *
**/
void LL_DMA_Configuration_Channel3(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize)
{
  LL_DMA_InitTypeDef DMA_InitStruct;
  LL_DMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.PeriphOrM2MSrcAddress = PeriphOrSrcAddr;
  DMA_InitStruct.MemoryOrM2MDstAddress = MemoryOrDstAddr;
  DMA_InitStruct.NbData = BufferSize;
  DMA_InitStruct.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;

  /* 关键：外设（ADC 寄存器）地址不增，内存数组地址自动递增 */
  DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;//LL_DMA_MEMORY_NOINCREMENT;
  
  //DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  ///DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;

  /* 关键：数据宽度必须是 16位 半字 (HalfWord) */
   DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD; 
   DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;

  
  DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA, LL_DMA_CHANNEL_3, &DMA_InitStruct);

  /* 重定向：把 ADC 的 DMA 请求映射到 DMA 通道 3 上 */
   LL_SYSCFG_SetDMARemap_CH3(LL_SYSCFG_DMA_MAP_ADC);

  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_3);
}


void LL_DMA_Configuration_Channel1(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize)
{
  LL_DMA_InitTypeDef DMA_InitStruct;
  LL_DMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.PeriphOrM2MSrcAddress = PeriphOrSrcAddr;
  DMA_InitStruct.MemoryOrM2MDstAddress = MemoryOrDstAddr;
  DMA_InitStruct.NbData = BufferSize;
  DMA_InitStruct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA, LL_DMA_CHANNEL_1, &DMA_InitStruct);

  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_1);
}


void LL_DMA_Configuration_Channel2(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize)
{
  LL_DMA_InitTypeDef DMA_InitStruct;
  LL_DMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.PeriphOrM2MSrcAddress = PeriphOrSrcAddr;
  DMA_InitStruct.MemoryOrM2MDstAddress = MemoryOrDstAddr;
  DMA_InitStruct.NbData = BufferSize;
  DMA_InitStruct.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA, LL_DMA_CHANNEL_2, &DMA_InitStruct);

  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_2);
}


