#include "bsp.h"




/**
*@brief:  
*@param:
*@notice
**/
void power_on_led_handler(void)
{
   LED_POWER_ON();
   LED_FAN_ON();
   LED_PLASMA_ON();
   LED_KEY_AI_ON();
   humidity_indicate_led_handler();

}


/**
*@brief:  
*@param:
*@notice
**/
void power_off_led_handler(void)
{
	 LED_POWER_OFF();
	 LED_FAN_OFF();
	 LED_PLASMA_OFF();
	 LED_KEY_AI_OFF();
   //water pos led 
   LED_WATER_INDICATOR_1();
   LED_WATER_INDICATOR_2();
	LED_WATER_INDICATOR_3();
	LED_WATER_INDICATOR_4();

	 LED_HUMIDITY_OFF_HIGH();
	 LED_HUMIDITY_OFF_MIDDLE();
	 LED_HUMIDIY_OFF_LOW();
 
}

/**
*@brief:  
*@param:
*@notice
**/
void wifi_fast_led_state(void)
{
   static uint8_t slowly_led_counter = 0;//100ms
   if((gpro_t.g_power_flag ==1) && (gpro_t.link_net_flag ==1) && (gpro_t.wifi_connected_success_flag == 0)){
	   // LED_WIFI_TOGGLE();
		
   }
   else if((gpro_t.g_power_flag ==1) && (gpro_t.link_net_flag ==0) && (gpro_t.wifi_connected_success_flag == 0)){

      
		if(++slowly_led_counter > 9){//100ms *10 =1000ms =1s 

		    slowly_led_counter =0;
		    // LED_WIFI_TOGGLE();
		}
   }
   else if(gpro_t.g_power_flag ==0){
	     
	   if(++slowly_led_counter > 9){//100ms *10 =1000ms =1s
	     slowly_led_counter=0;
       // LED_POWER_TOGGLE();

      }
   }
   else if(gpro_t.wifi_connected_success_flag==1 && gpro_t.g_power_flag ==1){
			
	      // LED_WIFI_ON();

   	}
}
/**
*@brief:  
*@param:
*@notice
**/
void wifi_led_state_handler(void)
{
	
     if(gpro_t.link_net_flag==1) return ;
	 if(gpro_t.wifi_connected_success_flag==1)
		{
			//LED_WIFI_ON();
//			  #if DEBUG_ENABLE

//			   printf("wifi_flag = %d\n\r",gpro_t.wifi_connected_success_flag);

//			  #endif 
		}

}


/**
*@brief:  water of detected display led
*@param:
*@notice
**/
void humidity_indicate_led_handler(void)
{
    if(gpro_t.humidity >= 40 &&  gpro_t.humidity<= 70){

        LED_HUMIDITY_OFF_HIGH();
		LED_HUMIDITY_ON_MIDDLE();
	    LED_HUMIDIY_OFF_LOW();
	}
	else if(gpro_t.humidity <= 40){

       LED_HUMIDITY_OFF_HIGH();
	   LED_HUMIDITY_OFF_MIDDLE();
	   LED_HUMIDIY_ON_LOW();    
	}
	else{

        LED_HUMIDITY_ON_HIGH();
		LED_HUMIDITY_OFF_MIDDLE();
	    LED_HUMIDIY_OFF_LOW();
	}


}

/**
*@brief:  power off led is blink 
*@param:
*@notice
**/

void power_off_led_blink_handler(void)
{

    if(gpro_t.gTimer_led_blink_counter > 1){

	    gpro_t.gTimer_led_blink_counter  =0;
		LED_POWER_TOGGLE();

	}

}


