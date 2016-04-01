#include "led.h"
/******************************************************************************************
*函数名：LED_Init()
* 参数：void
* 返回值：void
* 功能：LED的管脚配置
*********************************************************************************************/
void LED_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 /* LED GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(LED_RED_RCC | LED_GREEN_RCC | LED_BLUE_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = LED_RED_PIN;
  GPIO_Init(LED_RED_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = LED_GREEN_PIN ;
	GPIO_Init(LED_GREEN_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LED_BLUE_PIN;
	GPIO_Init(LED_BLUE_PORT, &GPIO_InitStructure);
  LED_Off(LED_GREEN |LED_BLUE);
	LED_On(LED_RED);
}

void LED_On(uint16_t leds)
{

	 if(leds&LED_RED)
  {
	GPIO_SetBits(LED_RED_PORT,LED_RED_PIN);
	}
		if(leds&LED_BLUE)
  {
	GPIO_SetBits(LED_BLUE_PORT,LED_BLUE_PIN);
	}
  if(leds&LED_GREEN)
  {
	GPIO_SetBits(LED_GREEN_PORT,LED_GREEN_PIN);
	}
}

void LED_Off(uint16_t leds)
{

		if(leds&LED_RED)
  {
	GPIO_ResetBits(LED_RED_PORT,LED_RED_PIN);
	}
			if(leds&LED_BLUE)
  {
	GPIO_ResetBits(LED_BLUE_PORT,LED_BLUE_PIN);
	}
  if(leds&LED_GREEN)
  {
	GPIO_ResetBits(LED_GREEN_PORT,LED_GREEN_PIN);
	}
}

void LED_Toggle(uint16_t leds)
{
		if(leds&LED_RED)
  {
	LED_RED_PORT->ODR ^= LED_RED_PIN;
	}
			if(leds&LED_BLUE)
  {
	 LED_BLUE_PORT->ODR ^= LED_BLUE_PIN;
	}
  if(leds&LED_GREEN)
  {
	 LED_GREEN_PORT->ODR ^= LED_GREEN_PIN;
	}
}
