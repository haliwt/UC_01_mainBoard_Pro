#include "bsp.h"




/**
*
*@brief 
*@notice
*@param
*
**/
void power_on_ctrl_handler(void)
{
    fan_adjust_high_speed();
	PLASMA_ON();
	TEC_ON() ;
}

void power_off_ctrl_handler(void)
{

	fan_stop();
	PLASMA_OFF();
	TEC_OFF(); 

}


/**
  * @brief  
  * @note  
  * @param: 
  *
**/
void plasma_set_status(bool idata) // 1-开启，0-关闭
{
  
    if(works_interval_f ==1) return ;

	if(gpro_t.g_power_flag){
	   if(gpro_t.g_ai_flag==true){

	      PLASMA_ON() ;
		  LED_PLASMA_ON();
				
	  }
	  else{

        if(idata == 1){
		    PLASMA_ON() ;
			LED_PLASMA_ON();
         }
		 else{
            PLASMA_OFF();
			LED_PLASMA_OFF();

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
void ai_set_status(bool idata)    // 1--开启, 0- 关闭
{
    if(idata == true){

       LED_AI_ON();
	}
	else{
       LED_AI_OFF();

	}


}

/**
*
*@brief environment temperature value compare set temperater value
*@notice
*@param
*@retrval 
*
**/


/**
*
*@brief 
*@notice
*@param
*
**/
	

/**
*
*@brief environment temperature value compare set temperater value
*@notice
*@param
*@retrval 
*
**/
void workd_interval_time_peripheral_handle(void)
{
	
 
}



void workd_interval_turn_off_handle(void)
{
	RELAY_OFF();
	ultra_sound_off();
	PLASMA_OFF();
		
}

/**
*
*@brief environment temperature value compare set temperater value
*@notice
*@param
*@retrval 
*
**/

/************************************************************************
*
* Function Name: LED_Power_Breathing(void)
* ĺč˝:
* ĺć°:ć 
* čżĺĺź:ć 
*
************************************************************************/
void compare_set_temp_value(void)
{
   if(wifi_connected_success_f == 1 ){
		MqttData_Publis_SetTemp(setting_temperature);
		//wait_timeout = tx_time_get()+20;
	}

	if(PTC_heat_open_f == 1 && wifi_connected_success_f==1){
     	MqttData_Publish_SetPtc(1);

	}
	else if(wifi_connected_success_f==1){

	  MqttData_Publish_SetPtc(0);

	}

}

void direct_compare_set_temp_value(void)
{

    
    // 如果当前正处于“等待响应”的时间段内，直接跳出，让 UI 任务跑别的 Slot
   
	if(temperature >= setting_temperature){
	     ptc_prohibit_off_f = 0;
	     PTC_heat_open_f = 0;   // 立即关闭
	     RELAY_OFF();
		 LED_PTC_OFF();
		

    }
	else{
	    ptc_prohibit_off_f = 0;
		PTC_heat_open_f = 1;   // 立即open
		LED_PTC_ON();
		if(works_interval_f == 0)RELAY_ON();
		 
	}

}

/**
*
*@brief environment temperature value compare set temperater value
*@notice
*@param
*@retrval 
*
**/
void Fan_Current_Det(void)
{
	if((discharge_f)&&(fan_open_f) && works_interval_f == 0)
	{
		if(fan_current<_NO_FAN_LOAD_CURRENT){
			fan_current_det_time++;
			if(fan_current_det_time>=2){
				fan_current_det_time = 0;

				if(!fan_warning_f)
				{
					//Beep(BEEP_THREE);
					beep_interval_time = 0;

					fan_open_f = 0;
				}

				fan_warning_f = 1;
			}
		}
		else{
		   fan_current_det_time = 0;
		}
	}
	else
	{
		fan_current_det_time = 0;
	}		   
}


/**
*
*@brief 
*@notice
*@param
*
**/
void peripheral_fun_handler(void)
{
   if(discharge_f==1){

    switch(works_interval_f){

	case 0:
      LED_Strip_Ctrl();
      Plasma_Ctrl();
      Ultra_Sound_Ctrl();
	  Relay_Ctrl();

	 if(disp_set_hours_time_f == 1 || Is_time_setting_f ==1) return ;
	  
      if(AI_led_open_f==1){
	  	LED_AI_ON();
	  }
	  else{
	     LED_AI_OFF();

	  }
    break;

	case 1: //have a rest 10 minutes 
	   LED_Strip_Ctrl();
       workd_interval_time_peripheral_handle();
	   workd_interval_turn_off_handle();
	   
	   if(disp_set_hours_time_f == 1 || Is_time_setting_f ==1) return ;
	   if(AI_led_open_f==1){
	  	LED_AI_ON();
	   }
	   else{
	     LED_AI_OFF();
       }

	break;
	  
    }

	}

}

/**
*
*@brief 
*@notice
*@param
*
**/

void power_off_peripheral_handler(void)
{

	RELAY_OFF();
	ultra_sound_off();
	PLASMA_OFF();


}

/**
*
*@brief 
*@notice
*@param
*
**/

void power_on_peripheral_handler(void)
{

	RELAY_ON();
	 ultra_sound_on(20);//(159); 
	PLASMA_ON();


}


