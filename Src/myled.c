#include "myled.h"
#include "gpio.h"

static uint16_t numPattern=0;



void LED_On(uint16_t pin)
{
  HAL_GPIO_WritePin(LED_PORT, pin, GPIO_PIN_SET); 
}

void LED_Off(uint16_t pin)
{
  HAL_GPIO_WritePin(LED_PORT, pin, GPIO_PIN_RESET); 
}

void LED_Toggle(uint16_t pin)
{
  HAL_GPIO_TogglePin(LED_PORT, pin);
}

//Todo:
void LED_Run_Pattern(){
    numPattern++;

    if((0x1 & numPattern ) != 0){
        LED1_Toggle();
    }

    if((0x2 & numPattern ) != 0){
        LED1_Off();
    }

    if((0x4 & numPattern ) != 0){
        LED1_Off();
    }
    if((0x8 & numPattern ) != 0){
        LED1_On();
    }
}

