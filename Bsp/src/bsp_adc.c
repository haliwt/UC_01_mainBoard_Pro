#include "bsp.h"

#define  ADC_CH_COUNT  6
//uint16_t ADC_DATA_BUF[ADC_DMA_CH_LEN];

/* 建立一个 16 位数组，专门用于接收 6 个通道的 ADC 原始值 */
uint16_t ADC_ConvertedValues[ADC_CH_COUNT];

uint16_t ptc_adc_filtered = 0; // 全局或静态变量：滤波后的ADC值
uint16_t ptc_voltage_mv = 0;   // 全局或静态变量：转换后的电压值（单位：mV）

#if 0

 LL_ADC_REG_SetSequencerRanks(1, LL_ADC_CHANNEL_2); //ADC_FAN   // 对应 ADC_ConvertedValues[0]
 LL_ADC_REG_SetSequencerRanks(2, LL_ADC_CHANNEL_3); //ADC_PTC	// 对应 ADC_ConvertedValues[1]
 LL_ADC_REG_SetSequencerRanks(3, LL_ADC_CHANNEL_6); //ADC_WATER_2	// 对应 ADC_ConvertedValues[2]
 LL_ADC_REG_SetSequencerRanks(4, LL_ADC_CHANNEL_9); //ADC_WATER_3	// 对应 ADC_ConvertedValues[3]
 LL_ADC_REG_SetSequencerRanks(5, LL_ADC_CHANNEL_12);//ADC_WATER_4	// 对应 ADC_ConvertedValues[4]
 LL_ADC_REG_SetSequencerRanks(6, LL_ADC_CHANNEL_13); //ADC_WATER_1	// 对应 ADC_ConvertedValues[5]


#endif 
void adc_read_6channels_value(void)
{
 #if 0
   uint8_t i = 0;
/* 3. 配置 DMA 通道 3 */
    // 传入：内存数组地址、ADC 数据寄存器地址、传输长度（6）
    LL_DMA_Configuration_Channel3((uint32_t)ADC_ConvertedValues, (uint32_t)&ADC->DR, ADC_CH_COUNT);

    for(i = 0; i < ADC_CH_COUNT; i++)
        {
            // 顺次输出：Channel_2, 3, 6, 9, 12, 13
            printf("CH[%d]=%d  ", i, ADC_ConvertedValues[i]);
        }
        printf("\n");
        
        /* 延时 500ms 再次触发 */
       tx_thread_sleep(10) ;//LL_mDelay(500);

	   /* --- 重新启动下一轮 ADC+DMA 采集 --- */
        // a. 先关闭 DMA 通道以允许重新配置长度
        LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_3);
        
        // b. 重新设置需要传输的数据长度
        LL_DMA_SetDataLength(DMA, LL_DMA_CHANNEL_3, ADC_CH_COUNT);
        
        // c. 重新使能 DMA 通道，开始静静等待 ADC 扔数据过来
        LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_3);
        
        // d. 再次软件触发 ADC 开始新一轮 6 通道扫描
        LL_ADC_REG_StartConversionSWStart();
	#else

    uint8_t i = 0;

    /* 1. 【核心修改】不要在读取函数里重复初始化 DMA！ 
       LL_DMA_Configuration_Channel3(...) 应该移到 main.c 的初始化部分中去 */

    /* 2. 等待 DMA 传输完成（非常重要！）
       如果你不用中断，必须在这里判断 DMA 传输完成标志位（TC - Transfer Complete），
       否则直接打印会读到垃圾数据。注意：请根据你的芯片型号修改 DMAx 和 CHANNELx */
    while (!LL_DMA_IsActiveFlag_TC3(DMA)) 
    {
        // 等待传输完成... 
        // 如果是在 RTOS (ThreadX) 中，这里也可以用信号量等待，防止死等卡死 CPU
    }
    
    /* 3. 清除 DMA 传输完成标志位，为下一轮做准备 */
    LL_DMA_ClearFlag_TC3(DMA);
    #if 0
    /* 4. 此时数据 100% 已经是最新准确的了，开始顺次输出 */
    for(i = 0; i < ADC_CH_COUNT; i++)
    {
        // Channel_2, 3, 6, 9, 12, 13
        printf("CH[%d]=%d  ", i, ADC_ConvertedValues[i]);
    }
    printf("\n");
	#endif 
        
    /* 5. 延时 500ms 再次触发 */
    tx_thread_sleep(10); // ThreadX 延时

    /* 6. --- 重新启动下一轮 ADC+DMA 采集 --- */
    // a. 先关闭 DMA 通道以允许重新配置长度
    LL_DMA_DisableChannel(DMA, LL_DMA_CHANNEL_3);
    
    // b. 重新设置需要传输的数据长度
    LL_DMA_SetDataLength(DMA, LL_DMA_CHANNEL_3, ADC_CH_COUNT);
    
    // c. 重新使能 DMA 通道
    LL_DMA_EnableChannel(DMA, LL_DMA_CHANNEL_3);
    
    // d. 再次软件触发 ADC 开始新一轮 6 通道扫描
    LL_ADC_REG_StartConversionSWStart(); 



	#endif 
}



void adc_fan_value(void)
{
    /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
    ptc_voltage_mv = (ADC_ConvertedValues[0]* 3300) / 4095;
}


void adc_ntc_value(void)
{
    /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
    ptc_voltage_mv = (ADC_ConvertedValues[1] * 3300) / 4095;
}


uint16_t adc_water_3_value(void)//adc_water_2_value
{
    /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
    ptc_voltage_mv = (ADC_ConvertedValues[2] * 3300) / 4095;

	return ptc_voltage_mv;
}

uint16_t adc_water_2_value(void)//adc_water_3_value
{
    /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
    ptc_voltage_mv = (ADC_ConvertedValues[3] * 3300) / 4095;

	return ptc_voltage_mv;
}

uint16_t adc_water_1_value(void)//adc_water_4_value
{
    /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
    ptc_voltage_mv = (ADC_ConvertedValues[4] * 3300) / 4095;

	return ptc_voltage_mv;
}

uint16_t adc_water_warning_value(void)//adc_water_1_value
{
    /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
    ptc_voltage_mv = (ADC_ConvertedValues[5] * 3300) / 4095;

	return ptc_voltage_mv;
}


uint16_t adc_ntc_mv_value(void)
{


//LL_ADC_REG_SetSequencerRanks(1, LL_ADC_CHANNEL_2); //ADC_FAN   // 对应 ADC_ConvertedValues[0]
//LL_ADC_REG_SetSequencerRanks(2, LL_ADC_CHANNEL_3); //ADC_PTC   // 对应 ADC_ConvertedValues[1]
	/* 2. 转换成电压（单位：毫伏 mV）
		   假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
	 ptc_voltage_mv = (ADC_ConvertedValues[1] * 3300) / 4095;
	
	 return ptc_voltage_mv;

}

uint16_t adc_fan_mv_value(void)
{
	/* 2. 转换成电压（单位：毫伏 mV）
		   假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
	 ptc_voltage_mv = (ADC_ConvertedValues[0] * 3300) / 4095;
	
	 return ptc_voltage_mv;

}

