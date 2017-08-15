#ifndef __MYLCD_H_
#define __MYLCD_H_


#define LCD_MODEL_NAME  "1602"

#define LCD_PORT  GPIOE

#define LCD_PIN_RS    GPIO_PIN_0
#define LCD_PIN_RW   GPIO_PIN_1
#define LCD_PIN_EN    GPIO_PIN_2
#define LCD_PIN_D0    GPIO_PIN_3
#define LCD_PIN_D1    GPIO_PIN_4
#define LCD_PIN_D2    GPIO_PIN_5
#define LCD_PIN_D3    GPIO_PIN_6
#define LCD_PIN_D4    GPIO_PIN_7
#define LCD_PIN_D5    GPIO_PIN_8
#define LCD_PIN_D6    GPIO_PIN_9
#define LCD_PIN_D7    GPIO_PIN_10


void LCD_Init(void);


#endif

