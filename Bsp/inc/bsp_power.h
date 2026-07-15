/*
  ******************************************************************************
  * Copyright (c) 2024 Yspring.
  * All rights reserved..
  * @file    user.H
  * @version V1.0.0
  * @date    2024
  * @author  Yspring Firmware Team  
  * @brief   user Header Code.
  ******************************************************************************      
*/
#ifndef __BSP_POWER_H
#define __BSP_POWER_H

#ifdef __cplusplus
extern "C" {
#endif
   
#include "main.h"
#include "stdbool.h"

//fan


//time couter 


extern bool  works_interval_f;

extern uint8_t  soft_version ;




//wifi end 



#define _SMA            (1<<0)
#define _SMB            (1<<1)
#define _SMC            (1<<2)
#define _SMD            (1<<3)
#define _SME            (1<<4)
#define _SMF            (1<<5)
#define _SMG            (1<<6)
#define _SMDP           (1<<7)

#define Lcdch_A         _SMA|_SMB|_SMC|_SME|_SMF|_SMG               //A
#define Lcdch_b         _SMC|_SMD|_SME|_SMF|_SMG                    //b
#define Lcdch_C         _SMA|_SMD|_SME|_SMF                         //C
#define Lcdch_d         _SMB|_SMC|_SMD|_SME|_SMG                    //d
#define Lcdch_E         _SMA|_SMD|_SME|_SMF|_SMG                    //E
#define Lcdch_F         _SMA|_SME|_SMF|_SMG                         //F
#define Lcdch_u         _SMC|_SMD|_SME                              //u
#define Lcdch_L         _SMD|_SME|_SMF                              //L
#define Lcdch_P         _SMA|_SMB|_SME|_SMF|_SMG                    //P
#define Lcdch_S         _SMA|_SMC|_SMD|_SMF|_SMG                    //S
#define Lcdch_I         _SMB|_SMC                                   //I
#define Lcdch_o         _SMC|_SMD|_SME|_SMG                         //o
#define Lcdch_          _SMG                                        //-
#define Lcdch_r         _SME|_SMG                                   //r
#define Lcdch_h         _SMC|_SME|_SMF|_SMG                         //h
#define Lcdch_H         _SMB|_SMC|_SME|_SMF|_SMG                    //H
#define Lcdch_t         _SMD|_SME|_SMF|_SMG                         //t
#define Lcdch_J         _SMB|_SMC|_SMD|_SME                         //J

#define Lcdch_0         _SMA|_SMB|_SMC|_SMD|_SME|_SMF               //0
#define Lcdch_1         _SMB|_SMC                                   //1
#define Lcdch_2         _SMA|_SMB|_SMD|_SME|_SMG                    //2
#define Lcdch_3         _SMA|_SMB|_SMC|_SMD|_SMG                    //3
#define Lcdch_4         _SMB|_SMC|_SMF|_SMG                         //4
#define Lcdch_5         _SMA|_SMC|_SMD|_SMF|_SMG                    //5
#define Lcdch_6         _SMA|_SMC|_SMD|_SME|_SMF|_SMG               //6
#define Lcdch_7         _SMA|_SMB|_SMC                              //7
#define Lcdch_8         _SMA|_SMB|_SMC|_SMD|_SME|_SMF|_SMG          //8
#define Lcdch_9         _SMA|_SMB|_SMC|_SMD|_SMF|_SMG               //9

extern const uint8_t LED_TAB[11];

//LEDBUF0
#define _DA1             (1<<0)
#define _DA2             (1<<1)
#define _DA3             (1<<2)
#define _DA4             (1<<3)
#define _DA5             (1<<4)
#define _DA6             (1<<5)
#define _DA7             (1<<6)

//LEDBUF1
#define _DB1             (1<<0)
#define _DB2             (1<<1)
#define _DB3             (1<<2)
#define _DB4             (1<<3)
#define _DB5             (1<<4)
#define _DB6             (1<<5)
#define _DB7             (1<<6)
#define _DP1             (1<<7) 

//LEDBUF2
#define _DC1             (1<<0)
#define _DC2             (1<<1)
#define _DC3             (1<<2)
#define _DC4             (1<<3)
#define _DC5             (1<<4)
#define _DC6             (1<<5)
#define _DC7             (1<<6)
#define _DP2             (1<<7) 

//LEDBUF3
#define _A5              (1<<0)
#define _B5              (1<<1)
#define _CC5             (1<<2)
#define _DD5             (1<<3)
#define _E5              (1<<4)
#define _F5              (1<<5)
#define _G5              (1<<6)
#define _H5              (1<<7) 

//LEDBUF4
#define _A1              (1<<0)
#define _B1              (1<<1)
#define _CC1             (1<<2)
#define _DD1             (1<<3)
#define _E1              (1<<4)
#define _F1              (1<<5)
#define _G1              (1<<6)
#define _H1              (1<<7) 

//LEDBUF5
#define _A2              (1<<0)
#define _B2              (1<<1)
#define _CC2             (1<<2)
#define _DD2             (1<<3)
#define _E2              (1<<4)
#define _F2              (1<<5)
#define _G2              (1<<6)
#define _H2              (1<<7) 

//LEDBUF6
#define _A3              (1<<0)
#define _B3              (1<<1)
#define _CC3             (1<<2)
#define _DD3             (1<<3)
#define _E3              (1<<4)
#define _F3              (1<<5)
#define _G3              (1<<6)
#define _H3              (1<<7) 

//LEDBUF7
#define _A4              (1<<0)
#define _B4              (1<<1)
#define _CC4             (1<<2)
#define _DD4             (1<<3)
#define _E4              (1<<4)
#define _F4              (1<<5)
#define _G4              (1<<6)
#define _H4              (1<<7) 

#define _LED_MODE        ((1<<4)|(1<<5))
#define _LED_UP          ((1<<2)|(1<<3))  
#define _LED_DOWN        ((1<<6)|(1<<7))

typedef struct  _power_state{

    uint8_t on_step;
	uint8_t  off_step;


}power_state;

extern power_state gon_t;

void power_on_handler(void);

void power_on_off_handler(void);

	
#ifdef __cplusplus
}
#endif

#endif /* __USER_H */
