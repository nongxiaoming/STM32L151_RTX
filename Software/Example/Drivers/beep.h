#ifndef __BEEP_H
#define __BEEP_H
#include "stm32l1xx.h"



#define BEEP_PORT GPIOA
#define BEEP_RCC RCC_AHBPeriph_GPIOA
#define BEEP_PIN GPIO_Pin_15



void BEEP_Init(void);
void BEEP_SetValue(uint32_t val);
void BEEP_Toggle(void);
#endif
