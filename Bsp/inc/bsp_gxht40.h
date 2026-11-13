#ifndef __BSP_GXHT40_H
#define __BSP_GXHT40_H
#include "main.h"




/* 引入汇春科技 YS32T031 系列的 LL 库头文件 */
/* 请根据您工程中的实际头文件名称进行微调，通常为 ys32t031xx_ll_gpio.h 等 */
//#include "ys32t031xx_ll_gpio.h"
//#include "ys32t031xx_ll_bus.h" 

// GXHT40-AD 默认 7 位 I2C 地址为 0x44[cite: 1]
#define GXHT40_I2C_ADDR         0x44

// 功能命令定义
#define GXHT40_CMD_MEAS_HIGH    0xFD  // 高重复率测量温湿度[cite: 1]
#define GXHT40_CMD_SOFT_RESET   0x94  // 软复位[cite: 1]



/* 引脚定义 */


/* AHT30 I2C 协议常量 */
#define AHT30_ADDR_WRITE        0x70
#define AHT30_ADDR_READ         0x71


/* 函数声明 */
void GXHT40_Init(void);
//uint8_t GXHT40_Read_TempHumi(int16_t *temperature, int16_t *humidity);

uint8_t AHT30_Read_TempHumi(float *temperature, float *humidity);



#endif /* __GXHT40_H */











