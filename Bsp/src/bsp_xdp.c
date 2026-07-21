#include "bsp.h"


// 为协议中的魔术字节定义常量，提高可读性
#define FRAME_HEADER        0xA5        //receive display board header  
#define FRAME_NUM           0x02          //main deviece number is 0x10 
#define FRAME_OLD_NUM       0x01          //older version device NUM
#define FRAME_ACK_NUM       0x80          //new version from main answer singnal 0x80 new version . 
#define FRAME_END_BYTE              0xFE
#define DATA_FRAME_TYPE_INDICATOR   0x0F
#define FRAME_COPY_NUM              0xFF   //this is older version .

#define ACK_SUCCESS 0x00U
#define ACK_FAILURE 0x01U




volatile uint8_t uart1_rx_buf[UART1_RX_BUF_SIZE];
volatile uint16_t uart1_rx_head ;
volatile uint16_t uart1_rx_tail ;

uint8_t fan_rx_stop_flag;



typedef void (*Usart1RxCallback)(uint8_t data);

static Usart1RxCallback usart1_rx_cb = NULL;  //定义一个全局静态函数指针

//static void usart1_invoke_callback(uint8_t data);


//static void usart1_isr_callback_handler(uint8_t data);
static void parse_recieve_copy_data(uint8_t *pddata);


uint8_t rx_inputBuf[12];
uint8_t check_bcc_code;
uint8_t rx1_data;
uint8_t counter_power_flag;
uint8_t ptc_onoff_default ;


//提供注册接口
void usart1_register_rx_callback(Usart1RxCallback cb)
{
   usart1_rx_cb = cb;

}

void usart1_invoke_callback(uint8_t data)
{
   if(usart1_rx_cb !=NULL){

       usart1_rx_cb(data);
   }


}


void callback_register_usart1_rx(void)
{

   usart1_register_rx_callback(usart1_isr_callback_handler);

}

volatile uint8_t rx_state;

typedef struct Msg
{
    
	uint8_t   cmd_notice;
	uint8_t   execuite_cmd_notice;
	uint8_t   copy_cmd_flag;
	uint8_t   rx_data_flag;	
    uint8_t   bcc_check_code;
	uint8_t   check_code_hex;
    uint8_t   receive_data_length;
    uint8_t   data_length;
	uint8_t   rc_data_length;
	uint8_t   total_data_length;
    uint8_t   rx_end_code;
	uint8_t   rx_total_numbers;
	uint8_t   rx_data[4];
	uint8_t   usData[12];


}MSG_T;

MSG_T   gl_tMsg; 

uint8_t inputBuf[1];



static void usart1_protocol_state_machine(uint8_t *pdata);

volatile uint8_t rx_usart1_data_counter=0;

uint8_t parse_exit_flag,parse_decoder_flag;
/********************************************************************************
	**
	*Function Name:void usart1_isr_callback_handler(void)
	*Function :  this is receive data from mainboard.
	*Input Ref:NO
	*Return Ref:NO
	*
*******************************************************************************/
void usart1_isr_callback_handler(uint8_t data)
{
   
	switch(rx_state){

	 case 0:
		if(data == FRAME_HEADER){
			rx_usart1_data_counter=0;
			gl_tMsg.usData[rx_usart1_data_counter]=data;
			
			rx_state =1;

		}
		else{
		   rx_state =0;

		}
	 break;

	 case 1:
			rx_usart1_data_counter++;
			gl_tMsg.usData[rx_usart1_data_counter]=data;

	        if(gl_tMsg.usData[rx_usart1_data_counter]==0x01 || gl_tMsg.usData[rx_usart1_data_counter]==0x02){
			 
				 rx_state = 2;
			 }
			 else{
				rx_state = 0;
				
             }

	 break;

	 case 2:
	 
		   rx_usart1_data_counter++;
           gl_tMsg.usData[rx_usart1_data_counter]=data;
		   
		  if(gl_tMsg.usData[rx_usart1_data_counter]==0xFE && rx_usart1_data_counter> 4){
		      rx_state = 3;
		  }
		 
     break;
			 
	 case 3:
		       rx_usart1_data_counter++;
	           gl_tMsg.usData[rx_usart1_data_counter]=data;
			 
	           rx_state = 0;
               gl_tMsg.rx_total_numbers = rx_usart1_data_counter;

			   gl_tMsg.rx_end_code = 0;
			   
		       //gpro_t.decoder_success_flag=1;

			   gl_tMsg.bcc_check_code = data;

               wifi_semaphore_xtask();//display_board_xtask_notice();

	 break;

	 default:
	   rx_state =0;

	 break;

	 }

}
 
/********************************************************************************
	**
	*Function Name:void usart1_protocol_state_machine(void)
	*Function :  in process bsp_freertos.c xTaskMsgPro
	*Input Ref:NO
	*Return Ref:NO
	*
*******************************************************************************/
static void usart1_protocol_state_machine(uint8_t *pdata)
{

   static uint8_t ptc_set_wifi = 0xff;
   switch(pdata[2]){

   case 0:

   break;

   case 0x01: //power turn on or off

        if(pdata[3] == 0x01){ //open
                
		        gon_t.on_step=0;
				if(ANGLE_SENSOR_VALUE() == 0){
			        beep_key_click();//buzzer_sound_fun();
	                SendWifiData_Answer_Cmd(0x01,0x01);
		            tx_thread_sleep(2);
					 gpro_t.g_power_flag  = true;
			         power_on_led_handler();
			         power_on_ctrl_init_handler();
				     gpro_t.g_out_display_flag= 1;
				}
				else{
					
				    beep_angle_thresdhold_sound();
				}
		         
				
	    }
        else if(pdata[3] == 0x0){ //close 

			 beep_key_click();
			 SendWifiData_Answer_Cmd(0x01,0x0); //power off .
             tx_thread_sleep(2); 
		     gon_t.off_step=0;
             gpro_t.g_power_flag = false;
	         power_off_led_handler();
	         power_off_ctrl_handler();

			  gpro_t.g_out_display_flag= 1;
             
			  SendWifiData_Answer_Cmd(0x01,0x02); //compatible older version 
	          tx_thread_sleep(2);
           
		}
      
      break;

	  case 0x02: //PTC turn on or off 
          
      
       if(pdata[3] == 0x01 ){//phone_cmd_power

	     beep_key_click();
	     SendWifiData_Answer_Cmd(0x02,0x01); //
           tx_thread_sleep(2); 
		
       }
       else if(pdata[3]== 0){
	   
		  beep_key_click();
	      SendWifiData_Answer_Cmd(0x02,0x0); //
          tx_thread_sleep(2); 
     
       }
    
      break;

	  
     case 0x03: //PLASMA ACTIVE OPEN OR CLOSE
   
		  if(pdata[3]== 0x01){
			 
			 beep_key_click();
			 gpro_t.g_plasma_flag = 1;//plasma_open_f = 1;
			 LED_PLASMA_ON();
			 if(works_interval_f==0){
				 PLASMA_CTRL_ON(); 
   
			  }
			 SendWifiData_Answer_Cmd(0x03,0x01); //
			tx_thread_sleep(2); 
			 
		  }
		  else if(pdata[3]  == 0x0){
			 beep_key_click();
			
			 gpro_t.g_plasma_flag = 0;
			 PLASMA_CTRL_OFF();
			 LED_PLASMA_OFF();

			SendWifiData_Answer_Cmd(0x03,0x0); //
			tx_thread_sleep(2); 
			  
		  
		  }
   
   
	break;

	   
   	case 0x04: //ultrasonic	ACTIVE OPEN OR CLOSE
          	 
    if(pdata[3]  == 0x01){  //open 
			 beep_key_click();
			
   
			if(works_interval_f==0){
				
   
			}
			
			SendWifiData_Answer_Cmd(0x04,0x01); //
			tx_thread_sleep(2); 
   
		  }
		  else if(pdata[3] == 0x0){ //close 
              beep_key_click();
		
			
			
			SendWifiData_Answer_Cmd(0x04,0x0); //
			tx_thread_sleep(2); 
   
		  }
   
      
    break;

	
     case  0x05: // link wifi command
       if(pdata[3] == 0x01){  // link wifi 
        
          beep_key_click();
         
	      gpro_t.wifi_connected_success_flag=0;
          gpro_t.link_net_flag =1;
		 
         
		
          SendWifiData_Answer_Cmd(0x05,0x01); //WT.EDIT 2024.12.28
          tx_thread_sleep(2);
         
      
        }

     break;

	  case 0x06: //buzzer sound command 
         if(pdata[3] == 0x01)beep_key_click();
		 
     break;

	 case 0x07://AI comm turn on or turn off

      if(pdata[3]== 0x01 || pdata[3]==0x02){
         gpro_t.g_ai_flag = 1;
		 LED_KEY_AI_ON();
	     LED_PLASMA_ON();
	  }
	  else if(pdata[3]== 0){
          gpro_t.g_ai_flag = 0; 
		  LED_KEY_AI_OFF();

	  }

	break;

	//begin 0x1x command or notice or data	 

	 case 0x10: //power on or off don't sound .
	 
        

    
	 break;

      case 0x11://第二个外接显示板通知指令
		    gpro_t.g_out_display_flag = pdata[3];
	  break; 
	  
	  case 0x16 : //buzzer sound command with answer .

        beep_key_click();
        
         SendWifiData_Answer_Cmd(0x16,0x01); //WT.EDIT 2025.07.28
	     tx_thread_sleep(2); 

	  break;

	  case 0x1E: //风扇速度大小,指令
	    if(pdata[4]==1){
			beep_key_click();
			if( pdata[5] == 1){
			
		      gpro_t.g_fan_speed = 1;     

			}
			else if( pdata[5] ==2){
			
			   gpro_t.g_fan_speed = 2; 	

			}
			else if(pdata[5] ==3){
			  gpro_t.g_fan_speed = 3;     
			}
	    }

	  break;

	  
	  //begin 0x2x
      case 0x27: //AI command without buzzer sound
	  case 0x17: //AI notice
	  
	  if(pdata[3] == 0x02){
	 
		
            gpro_t.g_ai_flag = 0;//AI_led_open_f =0;
           if(gpro_t.wifi_connected_success_flag ==1){
	          MqttData_Publish_AitState(2);
			   
	       }
        
          
       }
       else if(pdata[3] == 0x01){ //AI mode 
       
	      gpro_t.g_ai_flag=1;

         if(gpro_t.wifi_connected_success_flag ==1){
	         MqttData_Publish_AitState(1);
			
	      }
		 
       }


	 break;


	  case 0x19: //works 2 hours ,then have a rest 10 minutes ->notice 
       
	  break;

  
	case 0x1C: // is time data: hours,minutes,sencodes.
		   
	break;


	case 0x22: //PTC ON OR OFF by compare temperature value .
       
    break;


	 
	 case 0x2A: //smart phone or display  board set temperature .receive.
	    
	 break;

	 

	 case 0x6C: //Synchronize local time ->two display board 

	   if(pdata[4]==0x03){ 

		     if(pdata[5] < 24 && pdata[6] < 61 && pdata[7] < 61){
         
		      //gpro_t.disp_works_hours= pdata[5];
			 
			  //gpro_t.disp_works_minutes =pdata[6];
			

			  ///gpro_t.gTimer_works_time_seconds=pdata[7];
			
		     }
		 }

	 break;

	 case 0xF0: //software version difference older and new sotfware 
      
            soft_version = pdata[3];
	 
		   #if DEBUG_ENABLE


               printf("soft_version = %d \r\n",soft_version);
		   

		   #endif 

    break;


	case 0xFF: //copy comand or notice or data.

	       parse_recieve_copy_data(pdata) ;

	break;

	}

}
/**********************************************************************
	*
	*Function Name:static void parse_recieve_copy_data_handler(void)
	*Function: display board send to mainboard answer signal
	*Input Ref:NO
	*Return Ref:NO
	*
**********************************************************************/
static void parse_recieve_copy_data(uint8_t *pddata)
{

    switch(pddata[3]){
    
       case 0:
    
    
       break;

	   case 0x01:

	     if(pddata[4] == 0x01){ //open

		   gon_t.on_step=0;
	       gpro_t.g_power_flag = 1;

		 }
        else if(pddata[4] == 0x0){ //close 

		   gon_t.off_step=1;
          gpro_t.g_power_flag =0;
			 
		}
	   

	   break;

	   
    }
      
 }



/**
  * @brief This function handles USART1 global interrupt 
  * @param
  * @retrval 
**/
void decoder_handler(void)
{
   // gpro_t.decoder_success_flag=0;
	check_bcc_code = bcc_check(gl_tMsg.usData,gl_tMsg.rx_total_numbers);
	if(check_bcc_code == gl_tMsg.bcc_check_code){
		usart1_protocol_state_machine(gl_tMsg.usData);
    }
}







