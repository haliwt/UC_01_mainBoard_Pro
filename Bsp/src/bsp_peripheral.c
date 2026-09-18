#include "bsp.h"




/**
*
*@brief 
*@notice
*@param
*
**/
void power_on_ctrl_init_handler(void)
{
    fan_adjust_high_speed();
	PLASMA_CTRL_ON();
	if(gpro_t.water_pos_warning_flag==0 ){
		TEC_CTRL_ON() ;
	}
	WATER_PUMP_CTRL_OFF();
}




void power_on_run_handler(void)
{
    fan_adjust_high_speed();
	PLASMA_CTRL_ON();
	if(gpro_t.water_pos_warning_flag==0 && gpro_t.fan_warning_f ==0 && works_interval_f ==0){
		TEC_CTRL_ON() ;
	}
}

void power_off_ctrl_handler(void)
{

	PLASMA_CTRL_OFF();
	TEC_CTRL_OFF();
	WATER_PUMP_CTRL_OFF();

}


/**
  * @brief  
  * @note  
  * @param: 
  *
**/
void plasma_set_status(bool idata) // 1-开启，0-关闭
{
  
    if(gpro_t.g_power_flag){
	   if(gpro_t.g_ai_flag==true){

          
         if(works_interval_f ==0 ) PLASMA_CTRL_ON() ;
		  LED_PLASMA_ON();
				
	  }
	  else{

        if(idata == 1){
		    if(works_interval_f ==0 )PLASMA_CTRL_ON() ;
			LED_PLASMA_ON();
         }
		 else{
            PLASMA_CTRL_OFF();
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

      LED_KEY_AI_ON();
	   gpro_t.g_fan_speed = 3;
	  if(works_interval_f ==0 && gpro_t.fan_warning_f ==0 && gpro_t.water_pos_warning_flag ==0){
	     fan_adjust_high_speed(); 	
	  }
	  LED_FAN_ON();
      LED_PLASMA_ON();
	 
	  
      
	}
	else{
       LED_KEY_AI_OFF();

	}


}

/**
*
*@brief 
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
*@brief 
*@notice
*@param
*
**/





