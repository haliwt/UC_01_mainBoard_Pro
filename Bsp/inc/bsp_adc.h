#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "main.h"

#define  ADC_CH_COUNT  6

#define  ADC_ENABLE    0

#define  FAN_ADC_THRESHOLD     400


extern uint16_t ADC_ConvertedValues[ADC_CH_COUNT];


void adc_read_6channels_value(void);

uint16_t adc_water_level_low(void);

uint16_t adc_water_level_middle(void);

uint16_t adc_water_level_high(void);


uint16_t adc_water_warning_value(void);

uint16_t adc_ntc_mv_value(void);

uint16_t adc_fan_mv_value(void);


#endif 

