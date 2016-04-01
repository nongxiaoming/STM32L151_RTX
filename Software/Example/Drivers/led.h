#ifndef __LED_H
#define __LED_H
#include "stm32l1xx.h"


#define LED_RED_RCC        RCC_AHBPeriph_GPIOD
#define LED_RED_PORT       GPIOD
#define LED_RED_PIN        GPIO_Pin_0

#define LED_GREEN_RCC      RCC_AHBPeriph_GPIOE
#define LED_GREEN_PORT     GPIOE
#define LED_GREEN_PIN      GPIO_Pin_9

#define LED_BLUE_RCC       RCC_AHBPeriph_GPIOE
#define LED_BLUE_PORT      GPIOE
#define LED_BLUE_PIN       GPIO_Pin_10


#define LED_RED         0x01
#define LED_GREEN       0x02
#define LED_BLUE        0x04
#define LED_ALL         0x07



void LED_Init(void);
void LED_On(uint16_t leds);
void LED_Off(uint16_t leds);
void LED_Toggle(uint16_t leds);
#endif
