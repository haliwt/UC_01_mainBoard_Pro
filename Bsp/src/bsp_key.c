#include "bsp.h"



/**
*
*@brief  key of power
*@notice
*@param
*
**/
void key_power_short_handler(void)
{
 
	  // 1. 无论是开还是关，都要响一下蜂鸣器并翻转状态，直接提到最前面
	beep_key_click();
  
    // 2. 根据翻转后的最新状态，决定执行开机动作还是关机动作
	if (gpro_t.g_power_flag ==false) 
	{ 
	    // 最新状态为 true，说明刚刚执行了“开机”翻转
	    if(ANGLE_SENSOR_VALUE() == 0){
		    gpro_t.g_power_flag  = true;
		    power_on_led_handler();
		    power_on_ctrl_init_handler();
	    }
		else{
           beep_angle_thresdhold_sound();

		}
	}
	else 
	{ 
	    // 最新状态为 false，说明刚刚执行了“关机”翻转
        gpro_t.g_power_flag = false;
	    power_off_led_handler();
	    power_off_ctrl_handler();
	}

}
/**
*
*@brief 
*@notice
*@param
*
**/

void key_power_long_handler(void)
{


}

/**
*
*@brief 
*@notice
*@param
*
**/
void key_fan_short_handler(void)
{
   
   if(gpro_t.g_ai_flag == true ) return;
   
 
      beep_key_click();
	  gpro_t.g_fan_speed++;
      if (gpro_t.g_fan_speed > 3) {
         gpro_t.g_fan_speed= 1; // 确保异常时能正确恢复到 1 档
      }
	  if(works_interval_f ==0){
	  	
        fan_speed_adjust_handler(gpro_t.g_fan_speed);
	   }

   
}

/**
*
*@brief 
*@notice
*@param
*
**/
void key_plasma_short_handler(void)
{ 
   static uint8_t plasma_key_cnt = 0;
   if(gpro_t.g_ai_flag == true) return;
   
	
   beep_key_click();
   gpro_t.g_plasma_flag = !gpro_t.g_plasma_flag;
   plasma_set_status(gpro_t.g_plasma_flag);
   
	
	

}
/**
*
*@brief 
*@notice
*@param
*
**/
void key_ai_short_handler(void)
{
   beep_key_click();
   gpro_t.g_ai_flag = !gpro_t.g_ai_flag;
   ai_set_status(gpro_t.g_ai_flag);  

}

/**
*
*@brief 
*@notice
*@param
*
**/

void key_water_long_handler(void)
{
    WATER_PUMP_CTRL_ON() ;

}



/**
*
*@brief 
*@notice
*@param
*
**/
void ai_module_hanlder(void)
{
   if(gpro_t.g_ai_flag == 1){
      if(works_interval_f ==0 && gpro_t.fan_warning_f ==0 && gpro_t.water_pos_warning_flag ==0){
         power_on_run_handler();
   	  }
	  
	  LED_FAN_ON();
      LED_PLASMA_ON();
      LED_KEY_AI_ON();

   }
   else{

     LED_KEY_AI_OFF();
	 if(works_interval_f ==0){
        plasma_set_status(gpro_t.g_plasma_flag);
        fan_speed_adjust_handler(gpro_t.g_fan_speed);
     }

   }

   if(gpro_t.g_water_pump_flag == 1){
	    WATER_PUMP_CTRL_OFF() ;

 	}
  
}





