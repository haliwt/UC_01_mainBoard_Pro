#ifndef __DMA_H
#define __DMA_H

#include "main.h"

void DMA_Configuration(void);

void DMA_ADC_Init(void);

void LL_DMA_Configuration_Channel3(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize);

#endif 

