#include "bsp.h"



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

  #if 1
    uint8_t i ;

    /* 1. 【核心修改】不要在读取函数里重复初始化 DMA！ 
       LL_DMA_Configuration_Channel3(...) 应该移到 main.c 的初始化部分中去 */

    /* 2. 等待 DMA 传输完成（非常重要！）
       如果你不用中断，必须在这里判断 DMA 传输完成标志位（TC - Transfer Complete），
       否则直接打印会读到垃圾数据。注意：请根据你的芯片型号修改 DMAx 和 CHANNELx */

	
  
    while (!LL_DMA_IsActiveFlag_TC3(DMA)) 
    {
        // 等待传输完成... 
        // 如果是在 RTOS (ThreadX) 中，这里也可以用信号量等待，防止死等卡死 CPU
        // 如果当前 DMA 还没传完（可能 ADC 还在转换中），为了不饿死 UI，直接开溜
        // 但在退出前，必须通过休眠让出 CPU 拥有权
       // tx_thread_sleep(20); 
       // return;
    }
    
    /* 3. 清除 DMA 传输完成标志位，为下一轮做准备 */
    LL_DMA_ClearFlag_TC3(DMA);
    #if 1
    /* 4. 此时数据 100% 已经是最新准确的了，开始顺次输出 */
    for(i = 0; i < ADC_CH_COUNT; i++)
    {
        // Channel_2, 3, 6, 9, 12, 13
        printf("CH[%d]=%d  ", i, ADC_ConvertedValues[i]);
    }
    printf("\n");
	#endif 
        
    /* 5. 延时 500ms 再次触发 */
    tx_thread_sleep(50); // ThreadX 延时

    LL_DMA_Configuration_Channel3((uint32_t)ADC_ConvertedValues,
                              (uint32_t)&ADC->DR,
                              ADC_CH_COUNT);
    
    // d. 再次软件触发 ADC 开始新一轮 6 通道扫描
     LL_ADC_REG_StartConversionSWStart(); 
  #else 
   uint8_t i;

    /* 1. 先清除上一次可能遗留的传输完成标志（TC3） */
   // LL_DMA_ClearFlag_TC3(DMA);

    /* 2. 等待新一轮的 6 通道全部传输完毕 */
    // 因为后台 ADC 转换速度极快，实际上唤醒后这里几乎是瞬间通过，不会产生阻塞卡死
//    while (!LL_DMA_IsActiveFlag_TC3(DMA)) 
//    {
//        // 如果实在不放心忙等，可以在这里加一个小延时，但通常不需要
//        // tx_thread_sleep(1); 
//    }
//     LL_DMA_ClearFlag_TC3(DMA);
    /* 3. 此时 6 个数据 100% 是同一批次新鲜出炉的数据 */
    for(i = 0; i < ADC_CH_COUNT; i++)
    {
        printf("CH[%d]=%d  ", i, ADC_ConvertedValues[i]);
    }
    printf("\n");
        
    /* 4. 延时让出 CPU */
    tx_thread_sleep(50);



  #endif 


	
}


/**************************************************************************************
*
*Function Name:  uint16_t adc_ntc_mv_value(void)
*Function: 
*
*
**************************************************************************************/
uint16_t adc_water_3_value(void)//adc_water_2_value
{
   #if 0

   uint16_t water_3_value;
  /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
    //water_3_value= (ADC_ConvertedValues[2] * 3300) / 4095;
    water_3_value= ADC_ConvertedValues[2];
    ///tx_thread_sleep(10);//10*10ms =100ms
	#if ADC_ENABLE
      printf("water_adc_3 = %d\r\n",ptc_voltage_mv);
	#endif 
     ADC_ConvertedValues[2]=0;
	
	return water_3_value;

	#else 

	uint16_t raw_value;
    uint16_t water_1_mv;
	uint16_t water_1_value;
	static uint32_t water_3_filtered = 0;

    // 1. 获取当前最新采样值（12位 ADC 原始值：0 ~ 4095）
    raw_value = ADC_ConvertedValues[2];

    // 2. 一阶低通滤波
    if (water_3_filtered == 0) {
        // 首次运行或复位后，直接用当前值作为初始值，避免从0开始缓慢爬升
        water_3_filtered = raw_value;
    } else {
        // 新值权重占 2/20 (10%)，历史值权重占 18/20 (90%)
        // 如果想让滤波更灵敏，可以改成 (raw_value * 5 + water_1_filtered * 15) / 20
        // 针对 2 秒采样周期优化的一阶滤波算法
        // 新采样值权重占 12/20 (60%)，历史滤波值权重占 8/20 (40%)
        water_3_filtered = (raw_value * 12 + water_3_filtered * 8) / 20;
    }

    // 3. 将滤波后的 ADC 值转换成电压（单位：毫伏 mV）
    // 12位 ADC：最大值 4095，基准电压 3300mV
    // 注意：water_1_filtered * 3300 最大约为 13,513,500，未超出 uint32_t 的 4,294,967,295，安全
   // water_1_mv = ((uint32_t)water_1_filtered * 3300) / 4095;
	ADC_ConvertedValues[2]=0;

    return water_3_filtered;
	


	#endif 
}

uint16_t adc_water_2_value(void)//adc_water_3_value
{
   #if 0
    uint16_t water_2_value;
   /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
   // water_2_value = (ADC_ConvertedValues[3] * 3300) / 4095;
    water_2_value = ADC_ConvertedValues[3];
    //tx_thread_sleep(10);
	#if ADC_ENABLE
      printf("water_adc_2 = %d\r\n",ptc_voltage_mv);
	#endif
    ADC_ConvertedValues[3]=0;

	return water_2_value;
	#else 
	uint16_t raw_value;
    uint16_t water_1_mv;
	uint16_t water_1_value;
	static uint32_t water_2_filtered = 0;

    // 1. 获取当前最新采样值（12位 ADC 原始值：0 ~ 4095）
    raw_value = ADC_ConvertedValues[3];

    // 2. 一阶低通滤波
    if (water_2_filtered == 0) {
        // 首次运行或复位后，直接用当前值作为初始值，避免从0开始缓慢爬升
        water_2_filtered = raw_value;
    } else {
        // 新值权重占 2/20 (10%)，历史值权重占 18/20 (90%)
        // 如果想让滤波更灵敏，可以改成 (raw_value * 5 + water_1_filtered * 15) / 20
        // 针对 2 秒采样周期优化的一阶滤波算法
        // 新采样值权重占 12/20 (60%)，历史滤波值权重占 8/20 (40%)
        water_2_filtered = (raw_value * 12 + water_2_filtered * 8) / 20;
    }

    // 3. 将滤波后的 ADC 值转换成电压（单位：毫伏 mV）
    // 12位 ADC：最大值 4095，基准电压 3300mV
    // 注意：water_1_filtered * 3300 最大约为 13,513,500，未超出 uint32_t 的 4,294,967,295，安全
   // water_1_mv = ((uint32_t)water_1_filtered * 3300) / 4095;

    ADC_ConvertedValues[3]=0;
    return water_2_filtered;



	#endif 
}

uint16_t adc_water_1_value(void)//adc_water_4_value
{

  #if 0
   uint16_t water_1_value;
  /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
    //water_1_value = (ADC_ConvertedValues[4] * 3300) / 4095;
    water_1_value = ADC_ConvertedValues[4];
	//tx_thread_sleep(10);
	#if ADC_ENABLE
      printf("water_adc_1 = %d\r\n",ptc_voltage_mv);
	#endif
	ADC_ConvertedValues[4]=0;
	

	return water_1_value;
	#else 
	uint16_t raw_value;
    uint16_t water_1_mv;
	uint16_t water_1_value;
	static uint32_t water_1_filtered = 0;

    // 1. 获取当前最新采样值（12位 ADC 原始值：0 ~ 4095）
    raw_value = ADC_ConvertedValues[4];

    // 2. 一阶低通滤波
    if (water_1_filtered == 0) {
        // 首次运行或复位后，直接用当前值作为初始值，避免从0开始缓慢爬升
        water_1_filtered = raw_value;
    } else {
        // 新值权重占 2/20 (10%)，历史值权重占 18/20 (90%)
        // 如果想让滤波更灵敏，可以改成 (raw_value * 5 + water_1_filtered * 15) / 20
        // 针对 2 秒采样周期优化的一阶滤波算法
        // 新采样值权重占 12/20 (60%)，历史滤波值权重占 8/20 (40%)
        water_1_filtered = (raw_value * 12 + water_1_filtered * 8) / 20;
    }

    // 3. 将滤波后的 ADC 值转换成电压（单位：毫伏 mV）
    // 12位 ADC：最大值 4095，基准电压 3300mV
    // 注意：water_1_filtered * 3300 最大约为 13,513,500，未超出 uint32_t 的 4,294,967,295，安全
   // water_1_mv = ((uint32_t)water_1_filtered * 3300) / 4095;
   // ADC_ConvertedValues[4]=0;
    return water_1_filtered;
	#endif 
}

uint16_t adc_water_warning_value(void)//adc_water_1_value
{

   #if 0
	uint16_t water_4_value;


    /* 1. 一阶低通滤波（理顺原本注释掉的代码）
          新采样值权重占 2/20，历史滤波值权重占 18/20 */
   // ptc_adc_filtered = (ad_ptc_value[0] * 2 + ptc_adc_filtered * 18) / 20;

    /* 2. 转换成电压（单位：毫伏 mV）
          假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
   // water_4_value = (ADC_ConvertedValues[5] * 3300) / 4095;
    water_4_value = ADC_ConvertedValues[5];
	#if ADC_ENABLE
      printf("water_adc_0 = %d\r\n",ptc_voltage_mv);
	#endif
	ADC_ConvertedValues[5]=0;
	

	return water_4_value;
	#else
	uint16_t raw_value;
    uint16_t water_1_mv;
	uint16_t water_1_value;
	static uint32_t water_warning_filtered = 0;

    // 1. 获取当前最新采样值（12位 ADC 原始值：0 ~ 4095）
    raw_value = ADC_ConvertedValues[5];

    // 2. 一阶低通滤波
    if (water_warning_filtered == 0) {
        // 首次运行或复位后，直接用当前值作为初始值，避免从0开始缓慢爬升
        water_warning_filtered = raw_value;
    } else {
        // 新值权重占 2/20 (10%)，历史值权重占 18/20 (90%)
        // 如果想让滤波更灵敏，可以改成 (raw_value * 5 + water_1_filtered * 15) / 20
        // 针对 2 秒采样周期优化的一阶滤波算法
        // 新采样值权重占 12/20 (60%)，历史滤波值权重占 8/20 (40%)
        water_warning_filtered = (raw_value * 12 + water_warning_filtered * 8) / 20;
    }

    // 3. 将滤波后的 ADC 值转换成电压（单位：毫伏 mV）
    // 12位 ADC：最大值 4095，基准电压 3300mV
    // 注意：water_1_filtered * 3300 最大约为 13,513,500，未超出 uint32_t 的 4,294,967,295，安全
   // water_1_mv = ((uint32_t)water_1_filtered * 3300) / 4095;
    ADC_ConvertedValues[5]=0;
	
    return water_warning_filtered;



	#endif 
}

/**************************************************************************************
*
*Function Name:  uint16_t adc_ntc_mv_value(void)
*Function: 
*
*
**************************************************************************************/
uint16_t adc_ntc_mv_value(void)
{


//LL_ADC_REG_SetSequencerRanks(1, LL_ADC_CHANNEL_2); //ADC_FAN   // 对应 ADC_ConvertedValues[0]
//LL_ADC_REG_SetSequencerRanks(2, LL_ADC_CHANNEL_3); //ADC_PTC   // 对应 ADC_ConvertedValues[1]
	/* 2. 转换成电压（单位：毫伏 mV）
		   假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
	 ptc_voltage_mv = (ADC_ConvertedValues[1] * 3300) / 4095;
     #if ADC_ENABLE
		   printf("ntc_adc = %d\r\n",ptc_voltage_mv);
	#endif
   
	
	 return ptc_voltage_mv;

}

/**************************************************************************************
*
*Function Name:  uint16_t adc_ntc_mv_value(void)
*Function: 
*
*
**************************************************************************************/
uint16_t adc_fan_mv_value(void)
{
	/* 2. 转换成电压（单位：毫伏 mV）
		   假设：12位ADC（最大值4095），基准电压 3.3V（3300mV） */
	 ptc_voltage_mv = (ADC_ConvertedValues[0] * 3300) / 4095;
	  ADC_ConvertedValues[0]=0;

	 #if ADC_ENABLE
      printf("fan_adc = %d\r\n",ptc_voltage_mv);
	#endif
	
	 return ptc_voltage_mv;

}

