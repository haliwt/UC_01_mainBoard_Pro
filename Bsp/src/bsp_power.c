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

// 任务结构体：这次我们直接检查标志位
typedef struct {
    volatile uint8_t *task_f; // 指向定时器置位的标志位
    void (*task_func)(void);  // 任务函数
} Task_Config_t;




// 1ms 系统心跳计数器

// --- 任务函数声明 ---
void Task_Key_Scan_10ms(void);
void Task_link_wifi_20ms(void);
void Task_Logic_100ms(void);
void Task_ui_200ms(void);
void Task_Peripheral_300ms(void);
void Task_400ms(void);
void Task_500ms(void);
void Task_600ms(void);
void Task_900ms(void);
void Task_System_1s(void);
void Task_2s(void);
void Task_3s(void);
void Task_4s(void);
void Task_5s(void);
void Task_10s(void);

void Task_1minutes(void);
void Task_2minutes(void);

// 2. 任务注册表：将标志位地址与函数关联
static const Task_Config_t Task_Table[] = {
    {&gpro_t.time_10ms_f,  Task_Key_Scan_10ms},
    {&gpro_t.time_20ms_f,  Task_link_wifi_20ms},
    {&gpro_t.time_100ms_f, Task_Logic_100ms},
    {&gpro_t.time_200ms_f, Task_ui_200ms},
    {&gpro_t.time_100ms_fast_led_f, Task_Peripheral_300ms},
    {&gpro_t.time_400ms_f, Task_400ms},
    {&gpro_t.time_500ms_f, Task_500ms},
    {&gpro_t.time_600ms_f, Task_600ms},
    {&gpro_t.time_1s_f,    Task_System_1s},
    {&gpro_t.time_2s_f,    Task_2s},
    {&gpro_t.time_3s_f,    Task_3s},
    {&gpro_t.time_4s_f,    Task_4s},
    {&gpro_t.time_5s_f,    Task_5s},
    {&gpro_t.time_10s_f,    Task_10s},
    {&gpro_t.time_1m_f,    Task_1minutes},
    {&gpro_t.time_2m_f,    Task_2minutes}
};


#define TASK_COUNT (sizeof(Task_Table) / sizeof(Task_Config_t))


volatile uint8_t static beep_sound_f =0;
static void power_on_handler(void);
static void power_off_handler(void);
static void power_on_initial(void);


/**
  * @brief  fan run is error
  * @note  
  * @param: 
  *
**/
void Clear_Ram(void)
{
    time_5ms_f = 0;
	

	  gpro_t.time_400ms_f =0;
	  gpro_t.time_500ms_f =0;
	  gpro_t.time_1s_f = 0;
	  gpro_t.time_1m_f=0;
	

		
		
	
		

}




/**
  * @brief  fan run is error
  * @note  
  * @param: 
  *
**/






//ADC  PTC 



/**
  * @brief  fan run is error
  * @note  
  * @param: 
  *
**/




/****************************************************/
void printf_ptc_adc_numbers(void)
{
  printf("ptc_adc_numbers = %d \n\r",ptc_adc_numbers);

}


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

   
   switch(gon_t.on_step){

   case 0:
   	  gon_t.off_step = 0;
      wifi_off_step =0; //WT.EDT 2026.05.15
      
    
	 // dht11_read_temp_humidity_value();
	
      gon_t.on_step =1;
	

   break;

   case 1:
    //dht11_read_temp_humidity_value();

    gon_t.on_step =2;


   break;

   case 2:
   	 
      // dht11_read_temp_humidity_value();
	  // display_digital_3_numbers();
	   gon_t.on_step =0xfe;

   break;

   	}
}
/************************************************************************
*
* Function Name: LED_Power_Breathing(void)
* 功能:
* 参数:无
* 返回值:无
*
************************************************************************/
uint16_t disp_counter;

void power_on_handler(void)
{

  volatile  static uint8_t time_slot = 0,ptc_counter=0,fan_counter=0,fan_error=0;
  volatile static uint8_t per_counter=0,switch_done =0,disp_counter=0;
  volatile static uint8_t high_tmep_counter = 0,warning_counter=0,has_warning_counter=0;

  volatile static uint16_t wifi_check_counter=0;

	
        if(gon_t.on_step  < 8){
		  power_on_initial();
        }
	 // ✨【新增：紧急事件拦截响应】✨
        // 如果按键任务设置完温度，将 g_pro.g_immediate_heat_f 置为 1
       
         if(time_10ms_f ==1 &&  ptc_high_temperature_f == 0 && fan_warning_f ==0){
		    time_10ms_f=0;
           
		    //disp_key_input_handler();

			if(heat_open_close_f == 1 && ptc_high_temperature_f == 0 && fan_warning_f ==0)
	        {
	           heat_open_close_f = 0; // 立即清除触发标志，防止重复执行
	            
	            // 强制、立刻执行一次加热控制函数
	            // 确保底层硬件（如继电器、PWM、PTC）在 20ms 内得到响应
	           compare_set_temp_value(); //set_temperature_value_handler(); 
	        }
			    

         }
	     

		switch(time_slot){

		case 0://1* 20ms
		     per_counter++;
		     if(per_counter > 40 &&  ptc_high_temperature_f == 0 && fan_warning_f ==0){ //10ms * 100
			 	per_counter =0;
		       peripheral_fun_handler();
		     }

			
		break;



		case 1:
			 disp_counter ++;
			 if(disp_counter > 30 && ptc_high_temperature_f == 0 && fan_warning_f ==0 ){
			 disp_counter=0;	
	

			 }
			  

		break;

		case 2://2*20m = 40
		  if(gpro_t.time_3s_f > 3 && ptc_high_temperature_f == 0 && fan_warning_f ==0){
		    gpro_t.time_3s_f =0;	
		    Fan_Ctrl_Process();	  // 风扇控制

           }

		break;
		
		case 3:
		 if(wifi_connected_success_f==1 && gpro_t.time_4s_f > 0 && ptc_high_temperature_f == 0 && fan_warning_f ==0){
	  	   gpro_t.time_4s_f=0;
		   wifi_power_on_handler();
         }
		
		break;

		
		case 4:
			if(ptc_high_temperature_f == 0 && fan_warning_f ==0){
				if(key_net_config_f)
				 {
					
					if(key_net_config_time>=130)
					{
						key_net_config_time = 0;

						key_net_config_f = 0;
						
					}
					else{ //conneting to wifi net 
				        
						link_wifi_net_handler();
					}
				 } 
		  }
				
		break;

		
		case 5:
		if(gpro_t.time_5s_f > 1){
	   	  gpro_t.time_5s_f=0;
           Heat_Process(); //
	      }
				
		break;


		case 6:

		 if(gpro_t.time_6s_f > 2 && ptc_high_temperature_f == 0 && fan_warning_f ==0){
		   gpro_t.time_6s_f =0;
      	   //dht11_read_temp_humidity_value();
   	      }

		break;


		case 7:

		   if(Is_countdown_timer_f ==1 && ptc_high_temperature_f == 0 && fan_warning_f ==0){
             Countdown_timer_Handler();
	   	    }

		break;


		case 8:
			 if( ptc_high_temperature_f == 0 && fan_warning_f ==0){
			      works_nomal_run_time_handler();
			 }

		break;


		case 9:
	       if(gpro_t.time_7s_f > 4 && ptc_high_temperature_f == 0 && fan_warning_f ==0 && works_interval_f==0){

		    gpro_t.time_7s_f =0 ;
			fan_counter =1;
		
		    Adc_Channel_Sample();
		    AD_Filter();
		 
	       }

		break;

		case 10:
			if(ptc_high_temperature_f == 0 && fan_warning_f ==0){
			 if(key_net_config_f==0 &&  wifi_linking_tencent_f ==0 && gpro_t.time_1m_wifi_f > 1){
	   	   gpro_t.time_1m_wifi_f =0;
		   #if DEBUG_ENABLE
		     printf("reconnection wifi ! \n\r");
		   #endif 
		   Reconnection_Wifi_Order();

	 		}
			}

		break;

		case 11:
           
			wifi_check_counter++; //20ms * 100
		    if(wifi_check_counter > 300 && ptc_high_temperature_f == 0 && fan_warning_f ==0){
			  wifi_check_counter =0;
                wifi_check_ifnot_link_net_handler();
		    }

		break;

		case 12:

		   ptc_counter++ ;
		   if(ptc_counter > 50 && ptc_high_temperature_f == 0){
		   	   ptc_counter =0;
			   switch_done=1;
		    
		      ptc_adc_detected_voltage();
             #if 0
			  printf_ptc_adc_numbers();
			 #endif 
			 
            }
		   

		break;

		 case 13:
		    if(switch_done==1){
				switch_done ++;
			
				ptc_switch_temperature();
				Get_Ntc_Resistance_Temperature_Handler(ptc_current);
				 #if 0
						  printf("ntc_temp_v = %d \n\r",ptc_current);
						  printf("temperature = %d \n\r",read_ntc_temperature_value);
				 #endif 
						
			}

		break;

	    case 14:

		   
			
           if(switch_done==2){
		       switch_done++;

			if(read_ntc_temperature_value >120 && ptc_high_temperature_f == 0){

		       high_tmep_counter++;

		      if(high_tmep_counter > 2){

                
			    
		           ptc_high_temperature_f = 1;
		         
			       beep_high_temperature_sound();
                   if(wifi_connected_success_f ==1){
				   	 Publish_Data_Ptc_Temp_Warning(0x01);
                     
				     }
		       }
           }
		   else if(ptc_high_temperature_f == 0){
              high_tmep_counter =0;
		       read_ntc_temperature_value =0;

		   }

		   }
		   
               
		break;

		case 15:

		  has_warning_counter++;

         
		 if(has_warning_counter > 100){

		   has_warning_counter=0;
			
		  if(ptc_high_temperature_f == 1){
		  	 
			  beep_high_temperature_sound();
			  if(wifi_connected_success_f ==1){
			  	 Publish_Data_Ptc_Temp_Warning(0x01);
                    
			  }

		  }

		   if(fan_warning_f == 1){
			       fan_counter=0;
				   fan_error=0;
			      
					if(wifi_connected_success_f ==1){
                        Publish_Data_fan_Warning(0x01);//fan warning
					}
					beep_fan_default_sound();
					
            }

		 }
		  
		   if(fan_counter ==1){
		   	  fan_counter ++; 
			  #if 0
				  printf("fan_current  = %d \n\r",fan_current );
				  printf("temperature = %d \n\r",read_ntc_temperature_value);
			  #endif 
           if(fan_current < 30  &&  fan_warning_f == 0 && works_interval_f==0){
		  	    
                 fan_error ++ ;
				 #if 0
				 
				  printf("fan_error= %d \n\r",fan_error);
			    #endif 
			     if(fan_error > 6){
				  fan_warning_f = 1;
				     
						if(wifi_connected_success_f ==1){
                            Publish_Data_fan_Warning(0x01);//fan warning
						}
						beep_high_temperature_sound();
						
	            }
				 
			}
		    else if(fan_current  >29   &&  fan_warning_f == 0 && works_interval_f==0){

			   fan_error  =0;


			}

		 	}
		   
		 
		break;

		default:

		break;


		
       }

	 // ==================== 4. 时间片轮转维护 ====================
           time_slot++;
           if (time_slot >15 ) time_slot = 0;  //10ms* 16 = 160ms 

        
}
/************************************************************************
 *
 * Function Name: LED_Power_Breathing(void)
 * 功能:
 * 参数:无
 * 返回值:无
 *
 ************************************************************************/
static void power_off_handler(void)
{
   static uint8_t dc_on=0,fan_one_f=0;

   static uint32_t wait_timeout = 0;

   if(tx_time_get() < wait_timeout){
       return ;
   }
	switch(gon_t.off_step){
	
		 case 0:
			gon_t.on_step =0;
	       
		    fan_one_f =1;
			time_1s_counter=0;
			fan_one_minute_cuonter =0;
			wifi_run_step = 0;
			wifi_off_step =0;
			power_off_peripheral_handler();
			all_led_off();
	        TM1639_Display_ON_OFF(0);
			
			
			gon_t.off_step = 1;
	
		 break;
	
		 case 1:
             power_off_peripheral_handler();
		  
             if(dc_on ==0){
			 	beep_power_sound();
			 	dc_on++;
				fan_one_f =0;
			    //FAN_RUN_OFF();
				//fan_on(40);
				fan_on(0);
				//FAN_PWM_GPIO_OFF();//WT.EDIT 2026-05-16
			  }

			if(wifi_connected_success_f ==1 ){
	
               MqttData_Publish_PowerOff_Ref(); 
			}

			gon_t.off_step = 2;
			 
        break;


		case 2:
        if(wifi_connected_success_f ==1){
			     gon_t.off_step = 3;
			
				fan_warning_f = 0;
			    ptc_high_temperature_f =0;
			    Publish_Data_fan_Warning(0); //fan warning .

				Publish_Data_Ptc_Temp_Warning(0);
				//wait_timeout=tx_time_get()+20;//tx_thread_sleep(20);///delay_ms(200);
		    }
            else{

                gon_t.off_step = 3;
			}

		break;

		case 3:

		  
			
			   if(fan_one_f == 1  && fan_one_minute_cuonter>59){
				     fan_one_f ++;
	                // FAN_RUN_OFF();
                     //fan_on(40); 
					fan_on(0);
					//#if DEBUG_ENABLE
                     // printf("power_off_fan_stop !!!\n\r");
					//#endif 

				 }

				 if(wifi_connected_success_f ==1 && gpro_t.time_2s_f > 5){
                     gpro_t.time_2s_f=0;
				     MqttData_Publish_SetOpen(0);  
				   	
					
		
		    	   wait_timeout = tx_time_get()+20;//tx_thread_sleep(20);//delay_ms(100);
	    
			      }
			
		
	       gon_t.off_step = 4;
            	
		break;

		 case 4 :

		    
		   if(time_1s_counter > 1){
				 	time_1s_counter =0;
				    dht11_read_temp_humidity_value();
				    //#if DEBUG_ENABLE
                     /// printf(" gon_t.off_step = %d \n\r", gon_t.off_step );
				    ///#endif 
			}

        
		    gon_t.off_step = 5;

		  break;

		  case 5:

		     if(time_1s_counter > 2){
				 	time_1s_counter =0;
				    dht11_read_temp_humidity_value();
				   // #if DEBUG_ENABLE
                     /// printf(" gon_t.off_step = %d \n\r", gon_t.off_step );
				    //#endif 
			}
		
		    gon_t.off_step =6;

		  break;

		  case 6:

		 

			 if(wifi_connected_success_f ==1 &&  gpro_t.time_3s_f> 5 ){//10ms*800 =8000ms =8s
      
			       gpro_t.time_3s_f =0;
				   Subscriber_Data_FromCloud_Handler();
		    	   wait_timeout = tx_time_get() + 20 ;//tx_thread_sleep(20);//delay_ms(100);
	    
			     }
		
		  gon_t.off_step = 7;
		break;

		case 7:
			

		    if(wifi_connected_success_f ==1 &&   gpro_t.time_4s_f> 8){
				gpro_t.time_4s_f=0;
				fan_warning_f = 0;
			    ptc_high_temperature_f =0;
			    Publish_Data_fan_Warning(0); //fan warning .

				Publish_Data_Ptc_Temp_Warning(0);
				//wait_timeout=tx_time_get()+20;//tx_thread_sleep(20);///delay_ms(200);
		    }
		    gon_t.off_step = 8;

		break;

		case 8:
			if(setting_timing_second > 6 && wifi_connected_success_f ==1 ){
				setting_timing_second =0;
               MqttData_Publish_PowerOff_Ref(); 
			   wait_timeout = tx_time_get()+ 20;   
			}
		
          gon_t.off_step = 3;
		break;

   }
}

/**
  * @brief  
  * @note  
  * @param: 
  *
**/
void Countdown_timer_Handler(void)
{
   static int8_t dsip_timer_value ;
 
   if(setting_timing_second >=60) //60s
    {
	   setting_timing_second=0;

	   #if DEBUG_ENABLE

		timing_min_cnt = timing_min_cnt - 40;
	   #else 
		 timing_min_cnt --;

	   #endif 

        if(timing_min_cnt <  0)
        {
           timing_min_cnt =59;
		   real_hours_counter++;
		   if((setting_timing_hour > 1) && setting_timing_hour !=1){
		   	
		          dsip_timer_value = temporary_timer_hours - real_hours_counter +1;
				  setting_timing_hour = dsip_timer_value;


		   }

		   if(setting_timing_hour ==1 || setting_timing_hour==0){
               
				   setting_timing_hour--;
				   
            }

        }

        if (setting_timing_hour < 0)
        {
             discharge_f = 0;
			 System_Status_PowerOff() ;

        }
    }
}
/**
  * @brief  
  * @note  
  * @param: 
  *
**/
void works_nomal_run_time_handler(void)
{
     static uint8_t interval_10m_f = 0;
	 
		#if  0 //DEBUG_ENABLE 
			if(gpro_t.time_1m_f >11 && works_interval_f==0){
		#else 
			if(gpro_t.time_1m_f > 119 && works_interval_f==0){

		#endif 

			gpro_t.time_1m_f = 0;
		    gpro_t.time_base_1s_counter=0;
			works_interval_f=1;
			fan_one_minute_cuonter =0;
			
		#if DEBUG_ENABLE 
			printf("works_interval_f = %d \n\r",works_interval_f);
		#endif 
		}

		#if 0
		  else if(works_interval_f==1 && gpro_t.time_1m_f >9){
		#else 
		  else if(works_interval_f==1 && gpro_t.time_1m_f >10){

		#endif 
				gpro_t.time_1m_f = 0;  
				works_interval_f =0;
		        gpro_t.time_base_1s_counter=0;
				interval_10m_f = 1;
				
		#if DEBUG_ENABLE 
			printf("works_interval_f = %d \n\r",works_interval_f);
		#endif 
		}


		if(interval_10m_f == 1 && works_interval_f==0){
             interval_10m_f ++;
		   fan_full_fun();
		  if(ptc_prohibit_off_f == 0 &&  PTC_heat_open_f == 1){
			 // 立即open
		      LED_PTC_ON();
		      RELAY_ON();
		  
		  	}
		 
		}
		
 }
  



/**
	*
	*@brief environment temperature value compare set temperater value
	*@notice
	*@param
	*
**/
void Heat_Process(void)
{
     static uint8_t default_init = 0xff;   // 第一次比较标志
     
     if(discharge_f == 1){
	   if(ptc_prohibit_off_f == 1 || set_temperature_value_f ==1 ) return ;

	  uint8_t target_temp;

	  target_temp = setting_temperature;

	  if(temperature > 39){

        PTC_heat_open_f = 0;   // 立即关闭
	    first_temp_compare_f = 1; 
	    if(default_init != PTC_heat_open_f || key_input_temp_f ==1 || key_input_temp_f==2 ){
					default_init= PTC_heat_open_f;
					key_input_temp_f++;
				if(disp_second_f == 1){
					SendWifiData_To_Cmd(0x02,0);
		        //delay_ms(100);//HAL_Delay(5);
					}
		        if(wifi_connected_success_f == 1){
					MqttData_Publish_SetPtc(0);
		        }

				}
	  
	     return ;

	  }

      // -----------------------------
    // 2. 第一次比较：必须立即决定 PTC 开关
    // -----------------------------
	  if(first_temp_compare_f == 0){

		if(temperature >= target_temp){
            PTC_heat_open_f = 0;   // 立即关闭

		       if(default_init != PTC_heat_open_f  || key_input_temp_f ==1 || key_input_temp_f==2 ){
					default_init = PTC_heat_open_f;
					key_input_temp_f ++;
				if(disp_second_f == 1)SendWifiData_To_Cmd(0x02,0);
		        //delay_ms(100);//HAL_Delay(5);
		        if(wifi_connected_success_f == 1)MqttData_Publish_SetPtc(0);

				}
		}
        else{
            PTC_heat_open_f = 1;   // 立即打开
            first_temp_compare_f = 1;         // 以后进入滞后控制
            if(default_init!= PTC_heat_open_f || key_input_temp_f ==1 || key_input_temp_f==2 ){
					default_init = PTC_heat_open_f;
					key_input_temp_f++;
				if(disp_second_f == 1)SendWifiData_To_Cmd(0x02,0x01);
		        //delay_ms(100);//HAL_Delay(5);
		        if(wifi_connected_success_f == 1)MqttData_Publish_SetPtc(0x01);

			}
        }
        return;


	  }

		// -----------------------------
		// 3. 第二次及以后：使用 -2°C 滞后控制
		// -----------------------------
		if(first_temp_compare_f == 1)
		{
			// 当前是开启状态 → 高于设定温度则关闭
			if(temperature >= target_temp){
					PTC_heat_open_f = 0;
				if(default_init != PTC_heat_open_f  || key_input_temp_f ==1 || key_input_temp_f==2 ){
					default_init = PTC_heat_open_f;
					key_input_temp_f++;
				if(disp_second_f == 1)SendWifiData_To_Cmd(0x02,0);
		       // delay_ms(100);//HAL_Delay(5);
		        if(wifi_connected_success_f == 1)MqttData_Publish_SetPtc(0);

				}
			}
			else
			{
				// 当前是关闭状态 → 低于设定温度 - 2 才重新打开
				if(temperature <  (target_temp - 2))
				PTC_heat_open_f = 1;
				
				if(default_init!= PTC_heat_open_f || key_input_temp_f ==1 || key_input_temp_f==2 ){
					default_init = PTC_heat_open_f;
					key_input_temp_f++;
				if(disp_second_f == 1)SendWifiData_To_Cmd(0x02,0x01);
		       // delay_ms(100);//HAL_Delay(5);
		        if(wifi_connected_success_f == 1)MqttData_Publish_SetPtc(0x01);

				}
			}
		}

       }

}
/**
  * @brief  
  * @note  
  * @param: 
  *
**/
void power_on_off_handler(void)
{

 
	 switch(discharge_f){

      case 1:
           power_on_handler();
	 
	  break;

	  case 0:
	  	   power_off_handler();
		 

	  break;
      }

   if(wifi_linking_tencent_f==1 &&  wifi_read_net_data_f==1){
	   wifi_read_net_data_f++;

	   Wifi_Rx_InputInfo_Handler();
	}

	wifi_parse_tencennt_hadler();//
    
	if(key_net_config_f==0 ){
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


