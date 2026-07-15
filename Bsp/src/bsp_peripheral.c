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
	PLASMA_CTRL_ON();
	if(gpro_t.water_pos_warning_flag==0){
		TEC_CTRL_ON() ;
	}
}

void power_off_ctrl_handler(void)
{

	PLASMA_CTRL_OFF();
	TEC_CTRL_OFF(); 

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

	      PLASMA_CTRL_ON() ;
		  LED_PLASMA_ON();
				
	  }
	  else{

        if(idata == 1){
		    PLASMA_CTRL_ON() ;
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
	  power_on_ctrl_handler();
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
void workd_interval_time_peripheral_handle(void)
{
	
 
}



void workd_interval_turn_off_handle(void)
{
	
	PLASMA_CTRL_OFF();
		
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
void peripheral_fun_handler(void)
{
   if(gpro_t.g_power_flag==1){

    switch(works_interval_f){

	case 0:
      
    break;

	case 1: //have a rest 10 minutes 
	   

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





