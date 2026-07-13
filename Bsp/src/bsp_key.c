\#include "bsp.h"



/**
*
*@brief  key of power
*@notice
*@param
*
**/
void key_power_short_handler(void)
{
  if(gpro_t.g_power_flag){ //power_off
      gpro_t.g_power_flag = false;
	  beep_key_click();
	  power_on_ref_init_handler();
	  power_on_led_handler();
	  power_on_ctrl_handler();

  }
  else{ //power_on
      beep_key_click();
      gpro_t.g_power_flag = true;
	  power_off_ref_init_handler();
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
void key_fan_short_handler(void)
{
   static uint8_t fan_key_cnt = 0;
   if(gpro_t.g_ai_flag == true ||  works_interval_f ==1) return;
   
 
      beep_key_click();
	  fan_key_cnt++;
      if (fan_key_cnt > 3) {
         fan_key_cnt = 1; // 确保异常时能正确恢复到 1 档
       }
      switch(fan_key_cnt){

	     case 1:

             fan_adjust_low_speed();
	     break;

		 case 2:
		 	 fan_adjust_middle_speed();

		 break;

		 case 3:
		 	
		 	fan_adjust_high_speed();
		  
		 break;

		 default:
		    fan_key_cnt =0;

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
void key_plasma_short_handler(void)
{ 
   static uint8_t plasma_key_cnt = 0;
   if(gpro_t.g_ai_flag == true || works_interval_f ==1) return;
   
	if(gpro_t.g_ai_flag == false){
		beep_key_click();
		plasma_set_status(gpro_t.g_plasma_flag);
	
	}

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

