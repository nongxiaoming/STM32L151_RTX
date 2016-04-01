#ifndef __POWER_H
#define __POWER_H
#include "stm32l1xx.h"

typedef enum 
{
 POWER_GLOB =0x01,
 POWER_RF433=0x02,
 POWER_OEM=0x04,
 POWER_OEM_LNA=0x08,
 POWER_BT = 0x10,
 POWER_SIM = 0x20,
}PowerTypeDef;

#define EN_POW_RF433_PORT  GPIOC
#define EN_POW_RF433_RCC   RCC_AHBPeriph_GPIOC
#define EN_POW_RF433_PIN   GPIO_Pin_2

#define EN_POW_OEM_PORT      GPIOC
#define EN_POW_OEM_RCC       RCC_AHBPeriph_GPIOC
#define EN_POW_OEM_PIN       GPIO_Pin_3

#define EN_POW_OEM_LNA_PORT  GPIOC
#define EN_POW_OEM_LNA_RCC   RCC_AHBPeriph_GPIOC
#define EN_POW_OEM_LNA_PIN   GPIO_Pin_0

#define EN_POW_BT_PORT      GPIOA
#define EN_POW_BT_RCC       RCC_AHBPeriph_GPIOA
#define EN_POW_BT_PIN       GPIO_Pin_1

#define EN_POW_SIM_PORT      GPIOB
#define EN_POW_SIM_RCC       RCC_AHBPeriph_GPIOB
#define EN_POW_SIM_PIN       GPIO_Pin_14

#define EN_POW_GLOB_PORT      GPIOD
#define EN_POW_GLOB_RCC       RCC_AHBPeriph_GPIOD
#define EN_POW_GLOB_PIN       GPIO_Pin_10

#define EN_POW_RF433_RX_PORT  GPIOC
#define EN_POW_RF433_RX_RCC   RCC_AHBPeriph_GPIOC
#define EN_POW_RF433_RX_PIN   GPIO_Pin_4

void POWER_Init(void);
void POWER_Enable(uint8_t power_channel);
void POWER_Disable(uint8_t power_channel);



#endif  /* __POWER_H */
