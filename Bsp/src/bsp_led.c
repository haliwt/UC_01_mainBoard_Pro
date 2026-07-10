#include "bsp.h"




void power_on_led_handler(void)
{
   LED_POWER_ON();
   LED_FAN_ON();
   LED_PLASMA_ON();
   LED_AI_ON();

}


void power_off_led_handler(void)
{
	 LED_POWER_OFF();
	 LED_FAN_OFF();
	 LED_PLASMA_OFF();
	 LED_AI_OFF();

}


//300ms
void wifi_fast_led_state(void)
{
   static uint8_t slowly_led_counter = 0;//100ms
   if((discharge_f ==1) && (key_net_config_f ==1) && (wifi_connected_success_f == 0)){
	    LED_WIFI_TOGGLE();
		
   }
   else if((discharge_f ==1) && (key_net_config_f ==0) && (wifi_connected_success_f == 0)){

      
		if(++slowly_led_counter > 9){//100ms *10 =1000ms =1s 

		    slowly_led_counter =0;
		     LED_WIFI_TOGGLE();
		}
   }
   else if(discharge_f ==0){
	     
	   if(++slowly_led_counter > 9){//100ms *10 =1000ms =1s
	     slowly_led_counter=0;
        LED_POWER_TOGGLE();

      }
   }
   else if(wifi_connected_success_f==1 && discharge_f ==1){
			
	       LED_WIFI_ON();

   	}
}


void wifi_led_state_handler(void)
{
	
     if(key_net_config_f==1) return ;
	 if(wifi_connected_success_f==1)
		{
			LED_WIFI_ON();
//			  #if DEBUG_ENABLE

//			   printf("wifi_flag = %d\n\r",wifi_connected_success_f);

//			  #endif 
		}

	}




