#include "dma.h"
#include "bsp.h"
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
  * @brief DMA Init
  * @param  None
  * @retval None
  */
void DMA_ADC_Init(void)
{
    LL_DMA_InitTypeDef DMA_InitStruct;

    /* 使能DMA时钟 */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA);
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  
    //DMA
    DMA_InitStruct.PeriphOrM2MSrcAddress  = (uint32_t)&ADC->DR;
    DMA_InitStruct.MemoryOrM2MDstAddress  = (uint32_t)ADC_ConvertedValues;
    DMA_InitStruct.Direction              = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
    DMA_InitStruct.Mode                   = LL_DMA_MODE_NORMAL;
    DMA_InitStruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
    DMA_InitStruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
    DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD;
    DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;
    DMA_InitStruct.NbData                 = ADC_CH_COUNT;
    DMA_InitStruct.Priority               = LL_DMA_PRIORITY_MEDIUM;
    LL_DMA_Init(DMA, LL_DMA_CHANNEL_3, &DMA_InitStruct);
    LL_SYSCFG_SetDMARemap_CH3(LL_SYSCFG_DMA_MAP_ADC);
}




/**
  * @brief   ADC DMA 6 channel 
  * @note  
  * @param: 
  *
**/
void LL_DMA_Configuration_Channel3(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize)
{
 #if 0
 LL_DMA_InitTypeDef DMA_InitStruct;
  LL_DMA_StructInit(&DMA_InitStruct);
  DMA_InitStruct.PeriphOrM2MSrcAddress = PeriphOrSrcAddr;
  DMA_InitStruct.MemoryOrM2MDstAddress = MemoryOrDstAddr;
  DMA_InitStruct.NbData = BufferSize;
  DMA_InitStruct.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_NOINCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.Mode = LL_DMA_MODE_NORMAL;
  DMA_InitStruct.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA, LL_DMA_CHANNEL_3, &DMA_InitStruct);

  LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_3);
  #else

    LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_3);
    LL_DMA_SetMemoryAddress(DMA, LL_DMA_CHANNEL_3, MemoryOrDstAddr);
    LL_DMA_SetPeriphAddress(DMA, LL_DMA_CHANNEL_3, PeriphOrSrcAddr);
    LL_DMA_SetDataLength(DMA, LL_DMA_CHANNEL_3, BufferSize);
    LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_3);

  #endif 
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


