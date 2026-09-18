#ifndef BSP_AHT30_H
#define BSP_AHT30_H
#include "ys32t031.h"
#include "main.h"
#include "gpio.h"





/* I2C 引脚控制宏定义 */
#define SCL_HIGH()  LL_GPIO_SetOutputPin(I2C_SCL_GPIO_Port, LL_I2C_SCL_Pin)
#define SCL_LOW()   LL_GPIO_ResetOutputPin(I2C_SCL_GPIO_Port, LL_I2C_SCL_Pin)
#define SDA_HIGH()  LL_GPIO_SetOutputPin(I2C_SDA_GPIO_Port, LL_I2C_SDA_Pin)
#define SDA_LOW()   LL_GPIO_ResetOutputPin(I2C_SDA_GPIO_Port, LL_I2C_SDA_Pin)
#define SDA_READ()  LL_GPIO_IsInputPinSet(I2C_SDA_GPIO_Port, LL_I2C_SDA_Pin)


void TIM17_Delay_Init(void);

void AHT30_GPIO_Init(void);

uint8_t AHT30_Read_TempAndHumidity(int16_t *temperature, int16_t *humidity);




#endif 



