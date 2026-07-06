#include "bsp.h"

// I2C2 初始化配置
void I2C2_Configuration(void)
{
  LL_I2C_InitTypeDef I2C_InitStruct = {0};
  
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
  LL_I2C_DisableOwnAddress2(I2C2);
  LL_I2C_DisableGeneralCall(I2C2);
  LL_I2C_EnableClockStretching(I2C2);
  I2C_InitStruct.DigitalFilter = 0 ;
  I2C_InitStruct.OwnAddress1 = 0 ;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
  I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
  I2C_InitStruct.Timing = 4062315777;
  LL_I2C_Init(I2C2, &I2C_InitStruct);
}


