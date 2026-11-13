#ifndef BSP_AHT30_H
#define BSP_AHT30_H
#include "ys32t031.h"
#include "main.h"
#include "gpio.h"



#define I2C_SCL_GPIO_Port    			 GPIOF
#define I2C_SCL_Pin      			  LL_GPIO_PIN_6//LL_GPIO_PIN_7

#define I2C_SDA_GPIO_Port 				    GPIOF
#define I2C_SDA_Pin 						LL_GPIO_PIN_7//LL_GPIO_PIN_6


/* I2C 引脚控制宏定义 */
#define SCL_HIGH()  LL_GPIO_SetOutputPin(I2C_SCL_GPIO_Port, I2C_SCL_Pin)
#define SCL_LOW()   LL_GPIO_ResetOutputPin(I2C_SCL_GPIO_Port, I2C_SCL_Pin)
#define SDA_HIGH()  LL_GPIO_SetOutputPin(I2C_SDA_GPIO_Port, I2C_SDA_Pin)
#define SDA_LOW()   LL_GPIO_ResetOutputPin(I2C_SDA_GPIO_Port, I2C_SDA_Pin)
#define SDA_READ()  LL_GPIO_IsInputPinSet(I2C_SDA_GPIO_Port, I2C_SDA_Pin)


/* 引脚定义 */
#define AHT30_SCL_PORT         GPIOF
#define AHT30_SCL_PIN          LL_GPIO_PIN_6//LL_GPIO_PIN_7

#define AHT30_SDA_PORT         GPIOF
#define AHT30_SDA_PIN          LL_GPIO_PIN_7//LL_GPIO_PIN_6


/* 软件 I2C 信号控制宏 */
#define SCL_H()                 LL_GPIO_SetOutputPin(AHT30_SCL_PORT, AHT30_SCL_PIN)
#define SCL_L()                 LL_GPIO_ResetOutputPin(AHT30_SCL_PORT, AHT30_SCL_PIN)
#define SDA_H()                 LL_GPIO_SetOutputPin(AHT30_SDA_PORT, AHT30_SDA_PIN)
#define SDA_L()                 LL_GPIO_ResetOutputPin(AHT30_SDA_PORT, AHT30_SDA_PIN)
//#define SDA_READ()              LL_GPIO_IsInputPinSet(AHT30_SDA_PORT, AHT30_SDA_PIN)


/* AHT30 I2C 协议常量 */
#define AHT30_ADDR_WRITE        0x70
#define AHT30_ADDR_READ         0x71

/* 函数声明 */
void AHT30_Init(void);
//uint8_t AHT30_Read_TempHumi(float *temperature, float *humidity);



void TIM17_Delay_Init(void);

void AHT30_GPIO_Init(void);

//uint8_t AHT30_Read_TempAndHumidity(int16_t *temperature, int16_t *humidity);


uint8_t AHT30_Read_TempHumi(int16_t *temperature, int16_t *humidity);


#endif 



