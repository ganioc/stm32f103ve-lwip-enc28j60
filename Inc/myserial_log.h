#ifndef __SERIAL_LOG_H
#define __SERIAL_LOG_H

#include "stm32f1xx_hal.h"
#include "main.h"
#include "cmsis_os.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small 
printf
     set to 'Yes') calls __io_putchar() */
     
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

#endif

#define RX_BUFFER_SIZE 128

#define MAIN_STATE_LOG                  0
#define COMM_TO_PLC_STATE_LOG   1



//extern UART_HandleTypeDef huart1;
//extern osMailQId  mailLog;

void StartConsoleTask(void const * argument);
void UART_Log_Handle_Byte(uint8_t c);

void Serial_Log_Init();
void Serial_Log_MspInit();
void Serial_Log_MspDeInit();
void  UART_Log_receive();

void Log_Task_Init();
#endif

