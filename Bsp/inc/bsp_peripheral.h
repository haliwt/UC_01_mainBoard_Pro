#ifndef __BSP_PERIPHERAL_H
#define __BSP_PERIPHERAL_H
#include "main.h"
#include <stdbool.h>
#include "gpio.h"




void ai_set_status(bool idata);    // 1--开启, 0- 关闭


void Heat_Process(void);

void Fan_Current_Det(void);

void power_on_run_handler(void);

void poower_on_init_handler(void);
void power_off_ctrl_handler(void);



#endif 



