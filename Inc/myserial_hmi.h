#ifndef __MYSERIAL_HMI_H_
#define __MYSERIAL_HMI_H_

#include "stm32f1xx_hal.h"
#include "main.h"
#include "cmsis_os.h"

//#define 

void Serial_Hmi_Init();
void Serial_Hmi_MspInit();
void Serial_Hmi_MspDeInit();
void  UART_Hmi_receive();



#endif