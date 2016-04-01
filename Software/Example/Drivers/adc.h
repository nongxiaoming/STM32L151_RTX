#ifndef __KEY_H
#define __KEY_H
#include "stm32l1xx.h"

#define ADC_CHANNEL_NUM     1
#define ADC_SAMPLIE_TIMES   1

//typedef struct
//{
// uint16_t value;
// uint16_t vref;
//}__attribute__((packed)) adc_data_t ;

void ADC_Config(void);
void ADC_StartConver(void);
void ADC_ConverFinishHandler(uint16_t value);
//void ADC_ConverFinishHandler(uint16_t adc_value);
uint16_t get_adc(void);

#endif
