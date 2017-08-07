#include "gpio.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "spi.h"
#include "myusart.h"
#include "myled.h"
#include "myspi.h"

void Periph_Init(){

  MX_GPIO_Init();
  
/*
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();

  */
  My_Usart_Init();

  //MX_SPI1_Init();
  //My_Spi_Init();

}
