#include "bsp.h"

//IC: GXHT40-AD 
//#include "gxht40.h"
#define MS_TO_TICKS(ms)  (((ms) * TX_TIMER_TICKS_PER_SECOND) / 1000)


/* GPIO 引脚及端口宏定义（在此处修改为您实际连接的引脚） */
#define GXHT40_SCL_PORT         GPIOF
#define GXHT40_SCL_PIN          LL_GPIO_PIN_6

#define GXHT40_SDA_PORT         GPIOF
#define GXHT40_SDA_PIN          LL_GPIO_PIN_7

/* 软件 I2C 信号控制宏 */
#define SCL_H()                 LL_GPIO_SetOutputPin(GXHT40_SCL_PORT, GXHT40_SCL_PIN)
#define SCL_L()                 LL_GPIO_ResetOutputPin(GXHT40_SCL_PORT, GXHT40_SCL_PIN)
#define SDA_H()                 LL_GPIO_SetOutputPin(GXHT40_SDA_PORT, GXHT40_SDA_PIN)
#define SDA_L()                 LL_GPIO_ResetOutputPin(GXHT40_SDA_PORT, GXHT40_SDA_PIN)
#define SDA_READ()              LL_GPIO_IsInputPinSet(GXHT40_SDA_PORT, GXHT40_SDA_PIN)

static void I2C_Stop(void);

static void SDA_Mode_Input(void)
{
    LL_GPIO_SetPinMode(GXHT40_SDA_PORT, GXHT40_SDA_PIN, LL_GPIO_MODE_INPUT);
}

static void SDA_Mode_Output(void)
{
    LL_GPIO_SetPinMode(GXHT40_SDA_PORT, GXHT40_SDA_PIN, LL_GPIO_MODE_OUTPUT);
}

/**
 * @brief 软件 I2C 微秒级延时
 * @note  YS32T031 运行在不同主频时，可通过调整循环次数来控制 I2C 速率（建议保持在 100kHz 左右）
 */
static void I2C_Delay(void)
{
    volatile uint32_t i = 150; 
    while(i--);
}

/**
 * @brief 毫秒级延时函数（驱动内部等待温湿度转换使用）
 */
static void Delay_ms(uint32_t ms)
{
   // 放弃 tx_thread_sleep，改用绝对不依赖操作系统的裸机死等延时
    // 在 YS32T031 运行在 64MHz 主频下，每毫秒大约需要 16000 次循环
    volatile uint32_t count = ms * 16000; 
    while(count--);
}

/**
 * @brief 初始化 GXHT40 所需的 GPIO 引脚
 */
void GXHT40_Init(void)
{
    // 1. 开启对应 GPIO 端口的时钟 
    // 注意：请根据 YS32 具体的总线映射选择外设使能宏（如：LL_IOP_GRP1_EnableClock 或 LL_AHB_GRP1_EnableClock）
    //LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA); 

    uint8_t i;
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);

    // 2. 配置 SCL 和 SDA 为 开漏输出（OUTPUT_OPENDRAIN）
    // 开漏输出模式配合外部/内部上拉电阻，无需频繁切换输入输出方向即可直接读取引脚电平
    GPIO_InitStruct.Pin = GXHT40_SCL_PIN | GXHT40_SDA_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    
    LL_GPIO_Init(GXHT40_SCL_PORT, &GPIO_InitStruct);

    // 3. 释放总线
   // 3. 【核心救命代码】：I2C 总线强制解锁（九脉冲释放 SDA）
    SDA_H(); // 释放 SDA 
    for ( i = 0; i < 9; i++)
    {
        SCL_L();
        I2C_Delay();
        SCL_H();
        I2C_Delay();
    }
    
    // 4. 发送一个 Stop 信号，让总线彻底复位
    I2C_Stop();
}

/* ==========================================
   软件 I2C 底层时序实现
   ========================================== */

static void I2C_Start(void)
{
    SDA_H();
    SCL_H();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
}

static void I2C_Stop(void)
{
    SDA_L();
    I2C_Delay(); // 👈 【救命延时】：必须等 SDA 稳定在低电平后，才能去动 SCL！
    SCL_H();
    I2C_Delay(); // 👈 确保 SCL 稳定在高电平
    SDA_H();     // 👈 在 SCL 为高时，SDA 由低变高，这才是完美的 STOP 信号
    I2C_Delay();
}

static uint8_t I2C_WriteByte(uint8_t byte)
{
    uint8_t ack;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (byte & 0x80) SDA_H();
        else SDA_L();
        byte <<= 1;
        I2C_Delay();
        SCL_H();
        I2C_Delay();
        SCL_L();
		I2C_Delay(); // 👈 增加这一句，确保每个时钟低电平周期完整，并给数据线留出切换时间
    }
    
    // 读取应答信号 (ACK)
    #if 0
    SDA_H(); 
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    ack = SDA_READ(); // 0: ACK, 1: NACK
    SCL_L();
    I2C_Delay();
	#else
			// 释放 SDA，让从机能拉低
		SDA_Mode_Input();  
		I2C_Delay();

		SCL_H();
		I2C_Delay();

		ack = SDA_READ();   // 0 = ACK, 1 = NACK

		SCL_L();
		I2C_Delay();

		// 切回输出模式
		SDA_Mode_Output();



	#endif 
    
    return ack;
}

static uint8_t I2C_ReadByte(uint8_t send_ack)
{
    uint8_t byte = 0;
    //SDA_H(); 
    SDA_Mode_Input();  
    for (uint8_t i = 0; i < 8; i++)
    {
        byte <<= 1;
        I2C_Delay();
        SCL_H();
        I2C_Delay();
        if (SDA_READ()) byte |= 0x01;
        SCL_L();
    }
    SDA_Mode_Output();
    // 发送应答或非应答
    if (send_ack) SDA_L(); // ACK
    else SDA_H();          // NACK
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SCL_L();
    SDA_H(); 
    I2C_Delay();
    
    return byte;
}

/**
 * @brief  CRC-8 校验函数
 * @note   多项式: 0x31 (X8 + X5 + X4 + 1), 初始值: 0xFF[cite: 1]
 */
static uint8_t GXHT40_CheckCrc(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0xFF; //[cite: 1]
    for (uint8_t i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31; //[cite: 1]
            else
                crc <<= 1;
        }
    }
    return crc;
}

/* ==========================================
   GXHT40 传感器读取核心逻辑
   ========================================== */

/**
 * @brief  读取 GXHT40 的温度和湿度数据
 * @param  temperature: 输出温度值 (单位: ℃)
 * @param  humidity:    输出湿度值 (单位: %RH)
 * @return 0: 成功; 其他: 失败
 */
uint8_t GXHT40_Read_TempHumi(int16_t *temperature, int16_t *humidity)
{
    uint8_t buf[6];

    // 1. 发送高重复率测量命令
    I2C_Start();
    if (I2C_WriteByte((GXHT40_I2C_ADDR << 1) | 0) != 0) 
    {
        I2C_Stop();
        return 1; 
    }
    if (I2C_WriteByte(GXHT40_CMD_MEAS_HIGH) != 0) //[cite: 1]
    {
        I2C_Stop();
        return 2;
    }
    I2C_Stop();

    // 2. 等待模数转换完成（高重复率测量典型时间为 6.9ms，此处安全延时 10ms）[cite: 1]
    Delay_ms(10); 

    // 3. 连续读取 6 字节返回数据[cite: 1]
    I2C_Start();
    if (I2C_WriteByte((GXHT40_I2C_ADDR << 1) | 1) != 0) 
    {
        I2C_Stop();
        return 3;
    }

    buf[0] = I2C_ReadByte(1); // Temp MSB[cite: 1]
    buf[1] = I2C_ReadByte(1); // Temp LSB[cite: 1]
    buf[2] = I2C_ReadByte(1); // Temp CRC[cite: 1]
    buf[3] = I2C_ReadByte(1); // Humi MSB[cite: 1]
    buf[4] = I2C_ReadByte(1); // Humi LSB[cite: 1]
    buf[5] = I2C_ReadByte(0); // Humi CRC (最后一个字节答复 NACK)[cite: 1]
    I2C_Stop();

    // 4. CRC-8 校验[cite: 1]
    if (GXHT40_CheckCrc(&buf[0], 2) != buf[2]) return 4; // 温度校验失败
    if (GXHT40_CheckCrc(&buf[3], 2) != buf[5]) return 5; // 湿度校验失败

    // 5. 数据合成
    uint16_t raw_temp = (buf[0] << 8) | buf[1];
    uint16_t raw_humi = (buf[3] << 8) | buf[4];

    // 6. 物理公式换算[cite: 1]
    #if 0
    *temperature = -45.0f + 175.0f * ((float)raw_temp / 65535.0f); //[cite: 1]
    *humidity    = -6.0f + 125.0f * ((float)raw_humi / 65535.0f);   //[cite: 1]
	#else 

	// 原始公式：T = -45 + 175 * (raw_temp / 65535)
    // 整数整除四舍五入原理：(A + B/2) / B -> (A + 65535/2) / 65535 -> (A + 32767) / 65535
    int32_t temp_calc = -45 + (175 * (int32_t)raw_temp + 32767) / 65535;
    int32_t humi_calc = -6 + (125 * (int32_t)raw_humi + 32767) / 65535;


	#endif 

    // 湿度边界限制（0% ~ 100%）[cite: 1]
    #if 0
    if (*humidity < 0.0f)   *humidity = 0.0f;
    if (*humidity > 100.0f) *humidity = 100.0f;
	#else
	if (humi_calc < 0)   humi_calc = 0;
    if (humi_calc > 100) humi_calc = 100;

	#endif 

	// 8. 传出整数结果
    *temperature = (int16_t)temp_calc;
    *humidity    = (int16_t)humi_calc;

    return 0; // 读取成功
}




