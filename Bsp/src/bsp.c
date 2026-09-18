#include "bsp.h"
#define UID_ADDR   (0x1FFF1E00UL)
#define YS32_UID_BASE    0x1FFF1E00


uint8_t time_3s_flag;
uint8_t time_200ms_run_flag;
uint8_t counter_1m;




uint8_t counter_2s,tim_2s_f;

main_ref gpro_t;


/**************************************************************************************
*
*Function Name:  void bsp_init(void)
*Function: initial of base reference 
*
*
**************************************************************************************/
 void bsp_init(void)
 {
  gpro_t.g_power_flag=0;
  //GXHT40_Init();
  TIM17_Delay_Init();
   AHT30_GPIO_Init();


	
#if(Enable_EventRecorder == 1)  
	/* 0…60‹10‡80†40†30…4EventRecorder0…50„40†70„90‡40‹0 */
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();
#endif
	
  
}












/**
*@brief:  totall task
*@param:
#@notice

**/
/*---------------------------------------------------------------------------------
---�� �� ����-Task_beep_called_100ms
---��    �ܣ�- 
---��    ����- 
---�� �� ֵ��-
---��    �ã�- �ڴ�ѭ������100ms����һ��
---ǰ��������-
---˵    ����- 
---------------------------------------------------------------------------------*/




#if 0
/**
 * @brief  读取 YS32 芯片的前 12 字节 (96位) 唯一 ID
 * @param  uid_buf: 外部传入的缓冲区，长度必须 >= 12
 */
void Read_YS32_UID_12Bytes(uint8_t *uid_buf)
{
    // 1. 定义 UID 基地址指针 (根据手册为 0x1FFF1E00)
    // 使用 volatile 确保每次都从硬件地址读取，而不是从寄存器缓存读取
    volatile uint32_t *p_uid = (uint32_t *)0x1FFF1E00;

    // 2. 分三次读取 32 位数据（4字节 * 3 = 12字节）
    uint32_t temp_id[3];
    temp_id[0] = p_uid[0];
    temp_id[1] = p_uid[1];
    temp_id[2] = p_uid[2];

    // 3. 将 32 位数据拆分到 8 位字节数组中 (小端模式)
    for (int i = 0; i < 3; i++)
    {
        uid_buf[i * 4 + 0] = (uint8_t)(temp_id[i] & 0xFF);         // 低字节
        uid_buf[i * 4 + 1] = (uint8_t)((temp_id[i] >> 8) & 0xFF);
        uid_buf[i * 4 + 2] = (uint8_t)((temp_id[i] >> 16) & 0xFF);
        uid_buf[i * 4 + 3] = (uint8_t)((temp_id[i] >> 24) & 0xFF); // 高字节
    }
}

#endif 



// 模仿 HAL 库读取第一个字
uint32_t YS32_GetUIDw0(void)
{
    return (*(volatile uint32_t *)(YS32_UID_BASE));
}

// 读取全部 96 位并合成一个 uint32_t (异或方式)
uint32_t Get_Unique_ID_32bit(void)
{
    uint32_t w0 = *(volatile uint32_t *)(YS32_UID_BASE);
    uint32_t w1 = *(volatile uint32_t *)(YS32_UID_BASE + 0x04);
    uint32_t w2 = *(volatile uint32_t *)(YS32_UID_BASE + 0x08);

	uint32_t mix = (w0 ^ w1 ^ w2);
    
    //return (w0 ^ w1 ^ w2); // 异或合成，最大程度保留唯一性
    return (mix % 10000000);         // 压缩成 7 位十进制（0~9999999）
}

/**********************************************************************
    *
    *Function Name:uint8_t bcc_check(const unsigned char *data, int len) 
    *Function: BCC????
    *Input Ref:NO
    *Return Ref:NO
    *
**********************************************************************/
uint8_t bcc_check(const unsigned char *data, int len) 
{
    unsigned char bcc = 0;
    for (int i = 0; i < len; i++) {
        bcc ^= data[i];
    }
    return bcc;
}




