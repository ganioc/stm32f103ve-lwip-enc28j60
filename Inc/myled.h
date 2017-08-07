#ifndef __MYLED_H
#define __MYLED_H

#include "gpio.h"

#define LED1   GPIO_PIN_12
#define LED2   GPIO_PIN_13
#define LED3   GPIO_PIN_14
#define LED4   GPIO_PIN_15
#define LED_PORT            GPIOB



#define  LED1_On() do{LED_On(LED1);}while(0)
#define  LED2_On() do{LED_On(LED2);}while(0)
#define  LED3_On() do{LED_On(LED3);}while(0)
#define  LED4_On() do{LED_On(LED4);}while(0)

#define  LED1_Off() do{LED_Off(LED1);}while(0)
#define  LED2_Off() do{LED_Off(LED2);}while(0)
#define  LED3_Off() do{LED_Off(LED3);}while(0)
#define  LED4_Off() do{LED_Off(LED4);}while(0)

#define  LED1_Toggle() do{LED_Toggle(LED1);}while(0)
#define  LED2_Toggle() do{LED_Toggle(LED2);}while(0)
#define  LED3_Toggle() do{LED_Toggle(LED3);}while(0)
#define  LED4_Toggle() do{LED_Toggle(LED4);}while(0)

void LED_On(uint16_t pin);
void LED_Off(uint16_t pin);
void LED_Toggle(uint16_t pin);

void LED_Run_Pattern();


#endif
