#include "myusart.h"
#include "myserial_log.h"

uint8_t cUartLog, cUartPlc, cUartHmi, cUartRuff1, cUartRuff2;


void My_Usart_Init(){
#if(MY_SERIAL_LOG == 1)
    Serial_Log_Init();

#endif

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  //GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==UART4)
  {

  }
  else if(uartHandle->Instance==USART1)
  {
    Serial_Log_MspInit();
  }
  else if(uartHandle->Instance==USART2)
  {

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {

  }
}
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==UART4)
  {

  }
  else if(uartHandle->Instance==USART1)
  {
    Serial_Log_MspDeInit();
  }
  else if(uartHandle->Instance==USART2)
  {

  }
  else if(uartHandle->Instance==USART3)
  {

  }
} 



void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    // uart_ruff1
    if(UartHandle->Instance==UART4)
    {

    }
    // uart ruff2
    else if(UartHandle->Instance==UART5){

    }
    // uart log
    else if(UartHandle->Instance==USART1)
    {

    }
    // uart plc
    else if(UartHandle->Instance==USART2)
    {

    }
    // uart hmi
    else if(UartHandle->Instance==USART3)
    {

    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    // uart_ruff1
    if(UartHandle->Instance==UART4)
    {
        //UART_Ruff1_Handle_Byte(cUartRuff1);
        //UART_Ruff1_receive();
    }
    // uart ruff2
    else if(UartHandle->Instance==UART5){
        //UART_Ruff2_Handle_Byte(cUartRuff2);
        //UART_Ruff2_receive();
    }
    // uart log
    else if(UartHandle->Instance==USART1)
    {
        UART_Log_Handle_Byte(cUartLog);
        UART_Log_receive();
    }
    // uart plc
    else if(UartHandle->Instance==USART2)
    {
        //UART_Plc_Handle_Byte(cUartPlc);
        //UART_Plc_receive();        
    }
    // uart hmi
    else if(UartHandle->Instance==USART3)
    {
        //UART_Hmi_Handle_Byte(cUartHmi);
        //UART_Hmi_receive();    
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
    // uart_ruff1
    if(UartHandle->Instance==UART4)
    {

    }
    // uart ruff2
    else if(UartHandle->Instance==UART5){

    }    
    // uart log
    else if(UartHandle->Instance==USART1)
    {

    }
    // uart plc
    else if(UartHandle->Instance==USART2)
    {

    }
    // uart hmi
    else if(UartHandle->Instance==USART3)
    {

    }
}
