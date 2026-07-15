/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    adc.C
  * @author  Yspring Firmware Team  
  * @brief   adc Source Code.
  ******************************************************************************      
*/

#include "adc.h"   
#include "bsp.h"

// ADC 初始化配置
void ADC_Configuration(void)
{

 #if 0
 LL_ADC_InitTypeDef ADC_InitStruct;
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC);
  LL_ADC_DeInit();
  LL_ADC_StructInit(&ADC_InitStruct);
  
  ADC_InitStruct.ClockMode = LL_ADC_CLOCK_MODE_PCLK;
  ADC_InitStruct.DataAlign = LL_ADC_DATA_ALIGN_RIGHT;
  ADC_InitStruct.ScanMode = LL_ADC_SCAN_MODE_EN;   //LL_ADC_SCAN_MODE_DIS;
  ADC_InitStruct.ContinuousMode = LL_ADC_REG_CONTINUOUS_DIS;
  ADC_InitStruct.REG_ExternalTrig = LL_ADC_REG_EXT_TRIG_EN;
  ADC_InitStruct.REG_ExternalEvent = LL_ADC_REG_EXTERNAL_TRIG_SWSTART;
  ADC_InitStruct.INJ_ExternalTrig = LL_ADC_INJ_EXT_TRIG_DIS;
  ADC_InitStruct.INJ_ExternalEvent = LL_ADC_INJ_EXTERNAL_TRIG_SWSTART;
  LL_ADC_Init(ADC, &ADC_InitStruct);
  
  LL_ADC_SetOverrunMode(LL_ADC_OVERRUN_MODE_OLD);
  LL_ADC_SetWaitConversion(LL_ADC_WAIT_CONVERSION_DIS);
  LL_ADC_SetBiasCurrent(LL_ADC_BIAS_CURRENT_10_20UA);
  LL_ADC_DisableTempSensor();
  
  LL_ADC_REG_SetSequencerDiscont(0);
  LL_ADC_INJ_SetSequencerDiscont(LL_ADC_INJ_DISCONTINUOUS_DIS);
  LL_ADC_REG_SetSequencerDiscont(DISABLE);
  
  LL_ADC_SetSampleTime(LL_ADC_SAMPLE_TIME_127_5_CYCLES);
  LL_ADC_REG_SetSequencerLength(LL_ADC_REG_SEQ_SCAN_RANKS_6);
  LL_ADC_REG_SetSequencerRanks(1, LL_ADC_CHANNEL_2);
  LL_ADC_REG_SetSequencerRanks(2, LL_ADC_CHANNEL_3);
  LL_ADC_REG_SetSequencerRanks(3, LL_ADC_CHANNEL_6);
  LL_ADC_REG_SetSequencerRanks(4, LL_ADC_CHANNEL_9);
  LL_ADC_REG_SetSequencerRanks(5, LL_ADC_CHANNEL_12);
  LL_ADC_REG_SetSequencerRanks(6, LL_ADC_CHANNEL_13);
  
  LL_ADC_INJ_SetTrigAuto(LL_ADC_INJ_TRIG_INDEPENDENT);
  LL_ADC_INJ_SetSequencerLength(LL_ADC_INJ_SEQ_SCAN_RANKS_1);


  LL_ADC_DisableIT_EOS();
  LL_ADC_DisableIT_JEOSEQ();
  LL_ADC_DisableIT_EOSEQ();
  LL_ADC_DisableIT_JEOC();
  LL_ADC_DisableIT_EOC();

  LL_ADC_ClearFlag_EOC();
  LL_ADC_Enable();

  #else
  LL_ADC_InitTypeDef ADC_InitStruct;
    uint32_t i;
  
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC);
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA);
  
    LL_ADC_StructInit(&ADC_InitStruct);
  
    ADC_InitStruct.ClockMode = LL_ADC_CLOCK_MODE_PCLK;             
    ADC_InitStruct.ScanMode = LL_ADC_SCAN_MODE_EN;              
    ADC_InitStruct.ContinuousMode = LL_ADC_REG_CONTINUOUS_DIS;        
    ADC_InitStruct.DataAlign = LL_ADC_DATA_ALIGN_RIGHT;             
    ADC_InitStruct.REG_ExternalTrig = LL_ADC_REG_EXT_TRIG_EN;  
    ADC_InitStruct.REG_ExternalEvent = LL_ADC_REG_EXTERNAL_TRIG_SWSTART; 
    LL_ADC_Init(ADC, &ADC_InitStruct);
  
		LL_VREFBUF_Enable(VREFBUF);
		//LL_ADC_EnableTempSensor();
	
    LL_ADC_SetSampleTime(LL_ADC_SAMPLE_TIME_10_5_CYCLES);
    LL_ADC_REG_SetSequencerLength(LL_ADC_REG_SEQ_SCAN_RANKS_6);  
//    for(i=0; i<ADC_CH_COUNT; i++)
//    {
//        LL_ADC_REG_SetSequencerRanks(i+1, i+1);
//    }

	  LL_ADC_REG_SetSequencerRanks(1, LL_ADC_CHANNEL_2);
	  LL_ADC_REG_SetSequencerRanks(2, LL_ADC_CHANNEL_3);
	  LL_ADC_REG_SetSequencerRanks(3, LL_ADC_CHANNEL_6);  //第三级水位[2]
	  LL_ADC_REG_SetSequencerRanks(4, LL_ADC_CHANNEL_9);  //第二级水位[3]
	  LL_ADC_REG_SetSequencerRanks(5, LL_ADC_CHANNEL_12); //第一级数位[4]
	  LL_ADC_REG_SetSequencerRanks(6, LL_ADC_CHANNEL_13); // 警告水位[5]
    
    LL_ADC_REG_SetDMATransfer(LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
    LL_ADC_ClearFlag_EOC();
    LL_ADC_Enable();


  #endif 
}













