#include "bsp.h"


/**
 * @brief  初始化 TIM17 用于微秒级延时 (系统时钟 64MHz)
 */
void TIM17_Delay_Init(void)
{
    LL_TIM_InitTypeDef TIM_InitStruct = {0};

    /* 1. 使能 TIM17 时钟 (与您的芯片工程总线保持一致) */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM17);

    /* 2. 配置定时器参数: 
       计数器时钟 = 64MHz / (Prescaler 63 + 1) = 1MHz 
       即：计数 1 次刚好为 1us 
    */
    LL_TIM_StructInit(&TIM_InitStruct);
    TIM_InitStruct.Prescaler = 63;
    TIM_InitStruct.Autoreload = 0xFFFF; // 16位定时器最大重载值（支持最大 65535us 延时）
    TIM_InitStruct.ClockDivision = 0;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(TIM17, &TIM_InitStruct);

    /* 3. 启动定时器（微秒延时通过轮询计数器实现，无需开启更新中断） */
    LL_TIM_EnableCounter(TIM17);
}


/**
 * @brief  微秒级延时函数
 * @param  us: 需要延时的微秒数 (最大支持 65535 us)
 */
void delay_us(uint32_t us)
{
    if (us == 0) return;

    /* 清零计数器 */
    LL_TIM_SetCounter(TIM17, 0);

    /* 等待计数器达到指定的微秒数 */
    while (LL_TIM_GetCounter(TIM17) < us);
}


/**
 * @brief  毫秒级延时函数（基于微秒延时叠加）
 */
void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}


///-----------------------------------------------


/* I2C 时序延时 */
static void I2C_Delay(void)
{
    delay_us(5); // 约 100kHz - 400kHz 通信速率
}

/* 启动信号 */
static void I2C_Start(void)
{
    SDA_HIGH();
    SCL_HIGH();
    I2C_Delay();
    SDA_LOW();
    I2C_Delay();
    SCL_LOW();
    I2C_Delay();
}

/* 停止信号 */
static void I2C_Stop(void)
{
    SDA_LOW();
    I2C_Delay();
    SCL_HIGH();
    I2C_Delay();
    SDA_HIGH();
    I2C_Delay();
}

/* 发送一个字节 */
static void I2C_SendByte(uint8_t dat)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (dat & 0x80)
            SDA_HIGH();
        else
            SDA_LOW();
        dat <<= 1;
        I2C_Delay();
        SCL_HIGH();
        I2C_Delay();
        SCL_LOW();
        I2C_Delay();
    }
}

/* 读取一个字节 */
static uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t i, dat = 0;
    SDA_HIGH(); // 释放SDA，准备读取
    for (i = 0; i < 8; i++)
    {
        dat <<= 1;
        SCL_HIGH();
        I2C_Delay();
        if (SDA_READ())
        {
            dat |= 0x01;
        }
        SCL_LOW();
        I2C_Delay();
    }
    
    if (ack)
        SDA_LOW();  // 发送 ACK
    else
        SDA_HIGH(); // 发送 NACK
    
    I2C_Delay();
    SCL_HIGH();
    I2C_Delay();
    SCL_LOW();
    I2C_Delay();
    SDA_HIGH(); // 释放SDA
    return dat;
}

/* 等待应答 */
static uint8_t I2C_WaitAck(void)
{
    uint8_t timeout = 0;
    SDA_HIGH(); // 释放SDA
    I2C_Delay();
    SCL_HIGH();
    I2C_Delay();
    while (SDA_READ())
    {
        timeout++;
        if (timeout > 250)
        {
            I2C_Stop();
            return 1; // ACK超时/失败
        }
    }
    SCL_LOW();
    I2C_Delay();
    return 0; // 收到ACK
}

/* CRC8 校验函数（基于AHT30规格书提供源码） */
static uint8_t Calc_CRC8(uint8_t *message, uint8_t Num)
{
    uint8_t i;
    uint8_t byte;
    uint8_t crc = 0xFF;
    for (byte = 0; byte < Num; byte++)
    {
        crc ^= (message[byte]);
        for (i = 8; i > 0; --i)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc = (crc << 1);
        }
    }
    return crc;
}

/**
 * @brief  初始化 AHT30 对应的 GPIOF 引脚 (使用 LL库)
 */
void AHT30_GPIO_Init(void)
{
    /* 1. 使能 GPIOF 时钟 (根据具体芯片系列选择对应的AHB/IOP时钟使能函数) */
   // LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);

    /* 2. 配置 SCL (PF7) 和 SDA (PF6) 为开漏或推挽输出模式（推荐开漏加外部上拉电阻） */
    LL_GPIO_SetPinMode(GPIOF, LL_I2C_SCL_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOF, LL_I2C_SCL_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinSpeed(GPIOF, LL_I2C_SCL_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinPull(GPIOF, LL_I2C_SCL_Pin, LL_GPIO_PULL_UP);

    LL_GPIO_SetPinMode(GPIOF, LL_I2C_SDA_Pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOF, LL_I2C_SDA_Pin, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinSpeed(GPIOF, LL_I2C_SDA_Pin, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinPull(GPIOF, LL_I2C_SDA_Pin, LL_GPIO_PULL_UP);

    /* 3. 初始状态拉高总线 */
    SCL_HIGH();
    SDA_HIGH();
    
    /* 传感器上电后需等待5ms以上才能开始通信 */
    delay_ms(10);
}
#if 0
/**
 * @brief  读取 AHT30 温湿度数据
 * @param  temperature: 存放温度指针 (单位: ℃)
 * @param  humidity: 存放湿度指针 (单位: %RH)
 * @return 0: 成功, 1: I2C通信错误, 2: 传感器忙, 3: CRC校验失败
 */
uint8_t AHT30_Read_TempAndHumidity(float *temperature, float *humidity)
{
    uint8_t data[6];
    uint8_t crc_val;
    uint32_t raw_hum = 0, raw_temp = 0;

    /* 1. 发送测量命令: 0x70 (写地址) -> 0xAC 0x33 0x00 */
    I2C_Start();
    I2C_SendByte(0x70); 
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }
    
    I2C_SendByte(0xAC); 
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }
    
    I2C_SendByte(0x33); 
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }
    
    I2C_SendByte(0x00); 
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }
    I2C_Stop();

    /* 2. 等待测量完成，说明书要求至少延时 80ms[cite: 1] */
    delay_ms(80);

    /* 3. 读取 6 字节数据及 1 字节 CRC[cite: 1] */
    I2C_Start();
    I2C_SendByte(0x71); // 读地址[cite: 1]
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }

    data[0] = I2C_ReadByte(1); // 状态字 Status[cite: 1]
    data[1] = I2C_ReadByte(1); // SRH[19:12][cite: 1]
    data[2] = I2C_ReadByte(1); // SRH[11:4][cite: 1]
    data[3] = I2C_ReadByte(1); // SRH[3:0] & ST[19:16][cite: 1]
    data[4] = I2C_ReadByte(1); // ST[15:8][cite: 1]
    data[5] = I2C_ReadByte(1); // ST[7:0][cite: 1]
    crc_val = I2C_ReadByte(0); // 最后的 CRC 字节，发送 NACK 结束[cite: 1]
    I2C_Stop();

    /* 4. 检查状态字的 Bit[7] 是否为忙状态（1表示忙）[cite: 1] */
    if (data[0] & 0x80)
    {
        return 2; 
    }

    /* 5. CRC8 校验检查[cite: 1] */
    if (Calc_CRC8(data, 6) != crc_val)
    {
        return 3; 
    }

    /* 6. 按照规格书公式计算温湿度[cite: 1] */
    raw_hum = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((uint32_t)data[3] >> 4);
    raw_temp = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | (uint32_t)data[5];

    /* 公式: RH% = (SRH / 2^20) * 100%[cite: 1] */
    *humidity = ((float)raw_hum / 1048576.0f) * 100.0f;     
    /* 公式: T℃ = (ST / 2^20) * 200 - 50[cite: 1] */
    *temperature = ((float)raw_temp / 1048576.0f) * 200.0f - 50.0f;

    return 0; // 读取并计算成功
}
#else 

/**
 * @brief  读取 AHT30 温湿度数据（纯整数输出，带四舍五入）
 * @param  temperature: 存放温度指针 (单位: ℃，例如 25 表示 25℃，支持负数)
 * @param  humidity: 存放湿度指针 (单位: %RH，例如 55 表示 55%RH)
 * @return 0: 成功, 1: I2C通信错误, 2: 传感器忙, 3: CRC校验失败
 */
uint8_t AHT30_Read_TempAndHumidity(int16_t *temperature, int16_t *humidity)
{
    uint8_t data[6];
    uint8_t crc_val;
    uint32_t raw_hum = 0, raw_temp = 0;

    /* 1. 发送测量命令: 0x70 (写地址) -> 0xAC 0x33 0x00[cite: 1] */
    I2C_Start();
    I2C_SendByte(0x70); 
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }
    
    I2C_SendByte(0xAC); 
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }
    
    I2C_SendByte(0x33); 
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }
    
    I2C_SendByte(0x00); 
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }
    I2C_Stop();

    /* 2. 等待测量完成，说明书要求至少延时 80ms[cite: 1] */
    delay_ms(80);

    /* 3. 读取 6 字节数据及 1 字节 CRC[cite: 1] */
    I2C_Start();
    I2C_SendByte(0x71); // 读地址[cite: 1]
    if (I2C_WaitAck()) { I2C_Stop(); return 1; }

    data[0] = I2C_ReadByte(1); // 状态字 Status[cite: 1]
    data[1] = I2C_ReadByte(1); // SRH[19:12][cite: 1]
    data[2] = I2C_ReadByte(1); // SRH[11:4][cite: 1]
    data[3] = I2C_ReadByte(1); // SRH[3:0] & ST[19:16][cite: 1]
    data[4] = I2C_ReadByte(1); // ST[15:8][cite: 1]
    data[5] = I2C_ReadByte(1); // ST[7:0][cite: 1]
    crc_val = I2C_ReadByte(0); // 最后的 CRC 字节，发送 NACK 结束[cite: 1]
    I2C_Stop();

    /* 4. 检查状态字的 Bit[7] 是否为忙状态（1表示忙）[cite: 1] */
    if (data[0] & 0x80)
    {
        return 2; 
    }

    /* 5. CRC8 校验检查[cite: 1] */
    if (Calc_CRC8(data, 6) != crc_val)
    {
        return 3; 
    }

    /* 6. 拼接 20 位原始数据 */
    raw_hum = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((uint32_t)data[3] >> 4);
    raw_temp = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | (uint32_t)data[5];

    /* 
     * 7. 依据 AHT30 官方转换公式变换为整数[cite: 1]：
     * 湿度公式: RH% = (raw_hum / 2^20) * 100[cite: 1]
     * 温度公式: T℃  = (raw_temp / 2^20) * 200 - 50[cite: 1]
     * 
     * 注：此处加上 524288（即 2^20 的一半）是为了实现整数除法的“四舍五入”效果
     */
    *humidity = (int16_t)(((uint64_t)raw_hum * 100 + 524288) / 1048576); 
    *temperature = (int16_t)(((int64_t)raw_temp * 200 + 524288) / 1048576) - 50;

    return 0; // 读取并计算成功
}





#endif 

