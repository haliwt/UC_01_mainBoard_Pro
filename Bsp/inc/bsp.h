#ifndef __BSP_H
#define __BSP_H
#include "main.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h> // 确保包含此头文件以使用 NULL 定义，或者通过 main.h 引入
#include <stdbool.h>



#include "ys32t031.h"
#include "main.h"

#include "dma.h"
#include "uart.h"  
#include "tim.h"
#include "iwdg.h"
#include "adc.h"

//


#include "tx_api.h"

#include "bsp_key.h"


//
#include "bsp_power.h"
#include "bsp_led.h"
#include "bsp_peripheral.h"
#include "bsp_key.h"
#include "bsp_cmd_link.h"
#include "bsp_xdp.h"
#include "bsp_fan.h"
#include "bsp_buzzer.h"
#include "bsp_adc.h"
#include "bsp_water_adc.h"


#include "bsp_gxht40.h"
#include "bsp_threadx.h"
#include "bsp_ntc.h"


#include "interrupt_manager.h"

//wifi
#include "bsp_usart_wifi.h"
#include "bsp_mqtt_iot.h"
#include "bsp_esp8266.h"
#include "bsp_mqtt_iot.h"

#define Enable_EventRecorder  0

#define DEBUG_ENABLE    0





#if(Enable_EventRecorder == 1)
	#include "EventRecorder.h"
#endif


typedef struct _main_ref{

 bool g_power_flag;

 bool g_ai_flag;
 uint8_t g_fan_speed;
 bool g_plasma_flag;
 bool g_tec_flag;

 bool wifi_connected_success_flag;
 int16_t temperature;
 int16_t humidity;

 uint8_t ntc_temperature_value;

 bool fan_warning_f;
 volatile bool dma_dong_flag ;
 bool tec_control_flag;
 bool g_water_pump_flag;
 bool g_out_display_flag;
	    

 uint16_t fan_adc_value;
 uint16_t ntc_adc_value;

 //wifi reference 
 bool link_net_flag;
 bool g_is_net_flag;
 uint8_t wifi_linking_tencent_f;
 uint8_t wifi_read_net_data_f;

 uint16_t water_pos_1_flag ;
 uint16_t water_pos_2_flag ;
 uint16_t water_pos_3_flag ;
 uint16_t water_pos_warning_value;
 bool water_pos_warning_flag ;



 //volatile uint8_t time_200ms_f;
 volatile uint8_t time_100ms_fast_led_f;



 volatile uint8_t  time_base_1s_counter;


  volatile uint8_t gTimer_one_minute;

volatile uint8_t gTime_link_net_counter;
volatile uint8_t gTimer_one_minute_cuonter;




}main_ref;

extern main_ref gpro_t;



void bsp_init(void);


void task_scheduler(void);

void Task_beep_called_100ms(void);



uint32_t Get_Unique_ID_32bit(void);
uint8_t bcc_check(const unsigned char *data, int len) ;



#endif 

