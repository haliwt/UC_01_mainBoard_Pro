#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "main.h"

#define  ADC_CH_COUNT  6

#define  ADC_ENABLE    1


extern uint16_t ADC_ConvertedValues[ADC_CH_COUNT];


void adc_read_6channels_value(void);

uint16_t adc_water_1_value(void);

uint16_t adc_water_2_value(void);

uint16_t adc_water_3_value(void);


uint16_t adc_water_warning_value(void);

uint16_t adc_ntc_mv_value(void);

uint16_t adc_fan_mv_value(void);


#endif 

