#include "bsp.h"



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
		  ;
				
	  }
	  else{

        if(idata == 1){
		    if(works_interval_f ==0 )PLASMA_CTRL_ON() ;
			;
         }
		 else{
            PLASMA_CTRL_OFF();
			;

		 }


	  }
   }
}

