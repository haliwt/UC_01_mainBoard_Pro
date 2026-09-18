#include "bsp.h"


/**
  * @brief	:  
  * @note	: timer 17 is 10ms .
  * @param	 None
  * @retval  None
**/
void tim6_10ms_tick_handler(void)
{

  volatile static uint8_t cnt100 =0,cnt1000,cnt1m=0,cnt20ms=0;

  volatile static uint8_t c100ms;
       

	 cnt100++ ;

	if(cnt100 >=10){ //10* 10 = 100ms .
		cnt100 =0;

		//wifi_fast_led_state();
         cnt1000++ ;
        if(cnt1000> 9){ // 100ms *10 =1000ms=1s 
			cnt1000 = 0;
			

			

	        gpro_t.gTime_link_net_counter++;
			gpro_t.gTimer_one_minute_counter++;
			gpro_t.gTimer_led_blink_counter ++ ;

			gpro_t.time_base_1s_counter++;
            if(gpro_t.time_base_1s_counter > 59){//1s *60 =60s 
				gpro_t.time_base_1s_counter = 0;
                gpro_t.gTimer_one_minute++;
			
				
				

            }

		} 

	}

}






