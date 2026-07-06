#ifndef __BSP_H
#define __BSP_H
#include "main.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h> // 确保包含此头文件以使用 NULL 定义，或者通过 main.h 引入







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


#include "bsp_gxht40.h"
#include "bsp_threadx.h"
#include "bsp_ntc.h"

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

 
 volatile uint8_t time_10ms_f;
 volatile uint8_t time_20ms_f;
 volatile uint8_t time_50ms_f;

 //volatile uint8_t time_200ms_f;
 volatile uint8_t time_100ms_fast_led_f;

 volatile uint8_t time_400ms_f;
 volatile uint8_t time_500ms_f;
 volatile uint8_t time_600ms_f;
 volatile uint8_t time_900ms_f;

 volatile uint8_t time_base_1s_counter;
 volatile uint8_t time_2s_f;
 volatile uint8_t time_1s_f;
 volatile uint8_t time_3s_f;
 volatile uint8_t time_4s_f;
 volatile uint8_t time_5s_f;
 volatile uint8_t time_6s_f;
 volatile uint8_t time_7s_f;
 volatile uint8_t time_10s_f;

 volatile uint8_t time_1m_f;
 volatile uint8_t time_1m_wifi_f;
 volatile uint8_t time_2m_f;




}main_ref;

extern main_ref gpro_t;



void bsp_init(void);


void task_scheduler(void);

void Task_beep_called_100ms(void);



uint32_t Get_Unique_ID_32bit(void);
uint8_t bcc_check(const unsigned char *data, int len) ;



#endif 

