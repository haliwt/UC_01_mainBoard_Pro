#ifndef __DMA_H
#define __DMA_H

#include "main.h"

#define BUF_SIZE 20

extern uint8_t BUFFER[BUF_SIZE];


void DMA_Configuration(void);

void DMA_ADC_Init(void);

void LL_DMA_Configuration_Channel3(uint32_t MemoryOrDstAddr, uint32_t PeriphOrSrcAddr, uint16_t BufferSize);


void UART1_TX_RX_DMA_Init(void);

void UART1_DMA_Disp_Send(const uint8_t *pData, uint16_t Size);


#endif 

