#ifndef __MYUSART_H
#define __MYUSART_H

#include "stm32f1xx_hal.h"


#define    INDEX_BAUDRATE_300   0
#define    INDEX_BAUDRATE_600   1
#define    INDEX_BAUDRATE_1200  2
#define    INDEX_BAUDRATE_2400  3
#define    INDEX_BAUDRATE_4800  4
#define    INDEX_BAUDRATE_9600  5
#define    INDEX_BAUDRATE_19200 6
#define    INDEX_BAUDRATE_38400 7
#define    INDEX_BAUDRATE_57600 8
#define    INDEX_BAUDRATE_115200    9


#define   INDEX_UART_WORDLENGTH_8B   0
#define   INDEX_UART_WORDLENGTH_9B    1


#define   INDEX_UART_PARITY_NONE 0
#define   INDEX_UART_PARITY_EVEN  1
#define   INDEX_UART_PARITY_ODD    2

#define   INDEX_UART_STOPBITS_1  0
#define   INDEX_UART_STOPBITS_2   1



//uart 1, console log port
#define MY_SERIAL_LOG  1 
// uart 2
#define SERIAL_PLC 0
// uart 3
#define SERIAL_HMI 0
//uart 4
#define SERIAL_485 0
//uart 5
#define SERIAL_WIRELESS 0


//extern static  uint32_t BAUDRATE;
//extern static  uint32_t WORDWIDTH;
//extern static  uint32_t PARITY;
//extern static  uint32_t STOPWIDTH;


void My_Usart_Init();
//void Config_Usart(UART_HandleTypeDef *huart, USART_TypeDef *Instance,uint32_t BaudRate, uint32_t WordLength, uint32_t StopBits, uint32_t Parity);

#endif