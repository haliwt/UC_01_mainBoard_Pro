/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    user.C
  * @author  Yspring Firmware Team  
  * @brief   user Source Code.
  ******************************************************************************      
*/

#include "bsp.h"

power_state gon_t;


bool  works_interval_f;

uint8_t  soft_version ;



// 任务结构体：这次我们直接检查标志位
typedef struct {
	uint32_t last_tick; 	   // 记录上一次真正运行时的系统绝对时间戳
    //volatile uint8_t *task_f; // 指向定时器置位的标志位
    //uint32_t period;        // 任务运行周期
    uint32_t period_ms;     // 存储的是 毫秒(ms) 值，更改名字更清晰
    void (*task_handler)(void);  // 任务函数
} Task_Config_t;


typedef struct{

  uint8_t adc_6_channels_done_flag;
  bool adc_fan_channel_flag ;

}Run_Ref_t;

Run_Ref_t gl_ref;


// 1ms 系统心跳计数器

// --- 任务函数声明 ---
static void handler_read_6_channels_adc_value(void);
static void handler_wifi_update_data(void);
static void handler_works_hours(void);
static void handler_read_gxht40ad(void);
static void handler_AI_module_action(void);
static void handler_fan_adc_detected(void);
static void handler_tec_adc_value(void);



// 2. 任务注册表：将标志位地址与函数关联
static Task_Config_t g_tasks[] = {
    // last_tick,  period(ms),  task_handler
    {0,            50,         handler_AI_module_action},//10ms*30=300ms
    {0,            300,        handler_works_hours},
    {0,            450,        handler_read_gxht40ad},
    {0,            6000,       handler_wifi_update_data},        // 1分钟 = 60000ms
    {0,            100,        handler_read_6_channels_adc_value},         // 10ms*100=1000ms =1s
    {0,            500,        handler_fan_adc_detected},                  //500 *10ms =5000ms = 5s 
    {0,            260,        handler_tec_adc_value},
    
    
};


#define TASK_COUNT     (sizeof(g_tasks) / sizeof(Task_Config_t))


volatile uint8_t static beep_sound_f =0;
static void power_on_handler(void);
static void power_off_handler(void);
static void power_on_initial(void);
static void power_on_cycle_handler(void);

static void works_two_hours_times_handler(void);

uint8_t gxht4_rec=0;


/**
  * @brief  fan run is ok
  * @note  
  *
  *
**/

/************************************************************************
 * Function Name: LED_Power_Breathing(void)
 * 功能:
 * 参数:无
 * 返回值:无
 ************************************************************************/
static void power_on_initial(void)
{
   uint32_t boot_tick;
   uint8_t i;


   	  gon_t.off_step = 0;
      gpro_t.g_fan_speed =3;
      gpro_t.g_plasma_flag = true;
	  gpro_t.g_ai_flag = true;
      //two hours ref
	  gpro_t.time_base_1s_counter=0;
	  gpro_t.gTimer_one_minute=0;
	  works_interval_f=0;
	  //error 
	  gpro_t.fan_warning_f=0;
	  //wifi 
	  gpro_t.g_is_net_flag=0;
  
      gon_t.on_step =0;
	
	
	  fan_adjust_high_speed();   // 切换到高速档

  
   	    boot_tick = tx_time_get();
		for(i=0;i <TASK_COUNT;i ++){

		     g_tasks[i].last_tick = boot_tick;
		}
	   gon_t.on_step =0xfe;



   	
}
/************************************************************************
*
* Function Name: LED_Power_Breathing(void)
* 功能:
* 参数:无
* 返回值:无
*
************************************************************************/
void power_on_handler(void)
{

        if(gon_t.on_step  < 8){
		  power_on_initial();
        }
		else{
	 // ✨【新增：紧急事件拦截响应】✨
        // 如果按键任务设置完温度，将 g_pro.g_immediate_heat_f 置为 1
          power_on_cycle_handler();
	

		}
        
}
/************************************************************************
 *
 * Function Name:void power_on_cycle_handler(void)
 * 功能:
 * 参数:无
 * 返回值:无
 *
 ************************************************************************/
void power_on_cycle_handler(void)
{
	 // 获取当前系统的绝对时间戳
      uint32_t current_tick = tx_time_get();
    // 通过时间片轮询核心算法，分时调用各个功能模块
    for (uint8_t i = 0; i < TASK_COUNT; i++) 
    {

       // 【关键对齐】：将配置表的 ms 转换为当前硬件环境的 Tick 数
        // 既然 1 Tick = 10ms，那么 Tick数 = ms / 10
        //uint32_t period_tick = g_tasks[i].period_ms / 10;
        
        // 防止配置错误：如果误填了小于 10ms 的周期，强制算作 1 个 Tick
        
       // if (period_tick == 0) {
         //   period_tick = 1; 
       // }

        // 使用纯 Tick 单位进行无符号减法，完美天然支持死循环绕回（Overflow）
		if ((current_tick - g_tasks[i].last_tick) >= g_tasks[i].period_ms) 
        {
            // 【工业级进化：防轰炸饱和截断】
            // 如果卡顿/被高优先级抢占的时间超过了 2 个周期，直接对齐当前时间，放弃追赶
            if ((current_tick - g_tasks[i].last_tick) > ( g_tasks[i].period_ms * 2)) 
            {
                g_tasks[i].last_tick = current_tick;
            }
            else 
            {
                // 如果只是正常范围内的轻微抖动，滚动累加周期，死锁锁相，消除长期长跑漂移
                g_tasks[i].last_tick += g_tasks[i].period_ms;
            }
            
            // 触发对应周期的执行函数（确保不为 NULL，防止空指针崩溃）
            if (g_tasks[i].task_handler != NULL)
            {
                g_tasks[i].task_handler(); 
            }
        }
    }


}


/************************************************************************
 *
 * Function Name: 
 * 功能:
 * 参数:无
 * 返回值:无
 *
 ************************************************************************/
static void handler_wifi_update_data(void)
{
	 if(gpro_t.g_is_net_flag==1){

	 }

}
static void handler_works_hours(void)
{
  
     works_two_hours_times_handler();
   

}
uint8_t counter_test,adc_counter;

static void handler_read_gxht40ad(void)
{
    if(gpro_t.g_water_pump_flag == 0){
    // gxht4_rec = GXHT40_Read_TempHumi(&gpro_t.temperature, &gpro_t.humidity);
  gxht4_rec  =  AHT30_Read_TempAndHumidity(&gpro_t.temperature, &gpro_t.humidity);
	if(gxht4_rec==0){
      #if 1
      printf("temp = %d , humidity = %d \r\n",gpro_t.temperature,gpro_t.humidity);
	  #endif 
	  sendData_Real_TimeHum(gpro_t.humidity, gpro_t.temperature);

	}
	else{
		#if 1
	      printf("read temp is error !!!!\r\n");
		#endif 
	   counter_test++;
	}

	humidity_indicate_led_handler();

    }


}

static void handler_AI_module_action(void)
{
   ai_model_handler();
}



static void handler_read_6_channels_adc_value(void)
{
  adc_counter++;
  if(gpro_t.g_water_pump_flag == 0){
	  water_pwm_on();

	
	   adc_read_6channels_value();
       Water_System_Process();
      gl_ref.adc_fan_channel_flag = 1;
	  gl_ref.adc_6_channels_done_flag = 1;
	
      water_pwm_off();

  }
  

}


static void handler_fan_adc_detected(void)
{
    if(gl_ref.adc_fan_channel_flag == 1){
        gl_ref.adc_fan_channel_flag = 0;
	
	  fan_adc_detected_value();

	
      fan_warning_sound_handler();
    }

}
static void handler_tec_adc_value(void)
{
   if(gl_ref.adc_6_channels_done_flag ==1 && gpro_t.g_water_pump_flag == 0){
   	   
	   gpro_t.ntc_adc_value =adc_ntc_mv_value();
       Get_Ntc_Resistance_Temperature_Handler(gpro_t.ntc_adc_value);

	    ntc_temperature_compare_handler();
		gl_ref.adc_6_channels_done_flag++;

   	}


}

void ntc_temperature_compare_handler(void)
{
   if(gpro_t.ntc_temperature_value > 60 || gpro_t.water_pos_warning_flag ==1 ||  gpro_t.fan_warning_f ==1){
 
         TEC_CTRL_OFF();

   }
   else if(works_interval_f == 0 && gpro_t.water_pos_warning_flag ==0 &&  gpro_t.fan_warning_f ==0){

        TEC_CTRL_ON();
	}

}


/************************************************************************
 *
 * Function Name: 
 * 功能:
 * 参数:无
 * 返回值:无
 *
 ************************************************************************/
 uint8_t fan_one_f;
static void power_off_handler(void)
{
    static uint8_t  dc_power_f,counter;
	
	switch(gon_t.off_step){
	
		 case 0:
			gon_t.on_step =0;
	       
		    fan_one_f =1;
		    gpro_t.fan_warning_f =0;
			gpro_t.water_pos_warning_flag =0;
			
			power_off_led_handler();
		
			power_off_ctrl_handler();
	        gpro_t.gTimer_one_minute_counter =0;
			gpro_t.time_base_1s_counter=0;
			gpro_t.gTimer_one_minute=0;
			works_interval_f=0;
			gpro_t.g_water_pump_flag = 0; //关闭的.water _pump 
            fan_adn_error_counter =0;
			
	        gon_t.off_step = 1;
	
		 break;
	
		 case 1:
            
			 water_pwm_off();
		  
             if(dc_power_f ==0){
			 	dc_power_f ++;
			 	beep_key_click();
			    fan_stop();
		        fan_one_f =0;
				
			 
			  }
			  else{

                  fan_adjust_high_speed();
				  	gpro_t.gTimer_one_minute_counter =0;
			  }

			if(gpro_t.wifi_connected_success_flag ==1 ){
	
               MqttData_Publish_PowerOff_Ref(); 
			}

			gon_t.off_step = 2;
			 
        break;


		case 2:


		   if(fan_one_f == 1  && gpro_t.gTimer_one_minute_counter>59){
				     fan_one_f ++;
	                 fan_stop();

			}
           if(gpro_t.gTime_link_net_counter >4){
				gpro_t.gTime_link_net_counter=0;
							 
				//GXHT40_Read_TempHumi(&gpro_t.temperature, &gpro_t.humidity);
				AHT30_Read_TempAndHumidity(&gpro_t.temperature, &gpro_t.humidity);
							 
			}
            water_pwm_off();
		    power_off_led_blink_handler();
		  if(gpro_t.wifi_connected_success_flag ==1 ){
		     gon_t.off_step = 3;
		  

		  }
		  else
		    gon_t.off_step = 2;



		break;

		case 3:
            if(gpro_t.wifi_connected_success_flag ==1 ){
                    
				     MqttData_Publish_SetOpen(0);  
				   	
			    }
			
		
	       gon_t.off_step = 4;
            	
		break;

		 case 4:
            
		    
		    if(gpro_t.wifi_connected_success_flag ==1  ){//10ms*800 =8000ms =8s
      
			    Subscriber_Data_FromCloud_Handler();
		    	
	    
			   }
		
		  gon_t.off_step = 5;
		break;

		case 5:
			

			if(gpro_t.wifi_connected_success_flag ==1 ){
				
               MqttData_Publish_PowerOff_Ref(); 
			
			}
		
         
		
		     gon_t.off_step = 2;

		break;

	

   }
}

/**
  * @brief  
  * @note  
  * @param: 
  *
**/

uint8_t fan_run_one_minute_flag ;

static void works_two_hours_times_handler(void)
{
  
	 switch(works_interval_f){

	  case 0:
	 
		#if  0 //DEBUG_ENABLE 
			if(gpro_t.gTimer_one_minute >6 && works_interval_f==0){
		#else 
			if(gpro_t.gTimer_one_minute > 119 && works_interval_f==0){

		#endif 

			gpro_t.gTimer_one_minute = 0;
		    gpro_t.time_base_1s_counter=0;
			works_interval_f=true;
			fan_run_one_minute_flag =1;
			gpro_t.gTimer_one_minute_counter =0;

			
			PLASMA_CTRL_OFF();
			TEC_CTRL_OFF();
			
			
		#if DEBUG_ENABLE 
			printf("works_interval_f = %d \n\r",works_interval_f);
		#endif 
		}

	  break;

	  case 1:

        if(fan_run_one_minute_flag==1 && gpro_t.gTimer_one_minute_counter > 60){
		    fan_run_one_minute_flag ++;
            fan_stop();
        }
			
        #if 0
		   if(works_interval_f==1 && gpro_t.gTimer_one_minute >4){
		#else 
		  if(works_interval_f==true && gpro_t.gTimer_one_minute >10){

		#endif 
				gpro_t.gTimer_one_minute = 0;  
				works_interval_f =0;
		        gpro_t.time_base_1s_counter=0;
				
				ai_model_handler();
				ntc_temperature_compare_handler();
				
		#if DEBUG_ENABLE 
			printf("works_interval_f = %d \n\r",works_interval_f);
		#endif 

		  }
		  
	

	  break;
	 }

}
		
    
  



/**
	*
	*@brief 
	*@notice
	*@param
	*
**/

/**
  * @brief  
  * @note  
  * @param: 
  *
**/

void power_on_off_handler(void)
{

 
	 switch(gpro_t.g_power_flag){

      case 1:
	 
           power_on_handler();
	    
	  break;

	  case 0:
	  	   power_off_handler();
		 

	  break;
      }

   if(gpro_t.wifi_linking_tencent_f==1 &&  gpro_t.wifi_read_net_data_f==1){
	   gpro_t.wifi_read_net_data_f++;

	   Wifi_Rx_InputInfo_Handler();
	}
    if(gpro_t.g_is_net_flag==1){
	   wifi_parse_tencennt_hadler();//
    }
    
	if(gpro_t.link_net_flag==0 && gpro_t.g_is_net_flag==1){
      wifi_auto_detected_link_state();

   	}

	
}
/**
  * @brief  
  * @note  
  * @param: 
  *
**/
void power_on_ref_init_handler(void)
{
  gpro_t.g_ai_flag = 1;
  gpro_t.g_plasma_flag = 1;
  gpro_t.g_fan_speed = 100 ;


}

void power_off_ref_init_handler(void)
{
  gpro_t.g_ai_flag = 0;
  gpro_t.g_plasma_flag = 0;
  gpro_t.g_fan_speed = 0 ;


}


