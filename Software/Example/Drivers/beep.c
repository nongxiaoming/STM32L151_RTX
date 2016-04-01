#include "beep.h"


static void RCC_Configuration(void)
{
  /* Enable BEEP GPIO clock */
  RCC_AHBPeriphClockCmd(BEEP_RCC , ENABLE);
	  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
  
	 /* BEEP Configuration */
  GPIO_InitStructure.GPIO_Pin =  BEEP_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;

  GPIO_Init(BEEP_PORT, &GPIO_InitStructure);
  GPIO_PinAFConfig(BEEP_PORT, GPIO_PinSource15, GPIO_AF_TIM2);

	
}
static void TIM_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t PrescalerValue = 0;
   /* -----------------------------------------------------------------------
    The TIM2CLK frequency is set to SystemCoreClock (Hz), to get TIM2 counter
    clock at 8 MHz the Prescaler is computed as following:
     - Prescaler = (TIM2CLK / TIM2 counter clock) - 1
    SystemCoreClock is set to 32 MHz for  Medium-density devices.

    The TIM2 is running at 5 KHz: TIM2 Frequency = TIM2 counter clock/(ARR + 1)
                                                  = 8 MHz / 3200 = 2.5 KHz
  ----------------------------------------------------------------------- */
  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 8000000) - 1;
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 2960;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM2, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}
/******************************************************************************************
*函数名：KEY_Init()
* 参数：void
* 返回值：void
* 功能：LED的管脚配置
*********************************************************************************************/
void BEEP_Init(void)
{
 RCC_Configuration();
 GPIO_Configuration();
 TIM_Configuration();
}

void BEEP_SetValue(uint32_t val)
{
TIM_SetCompare1(TIM2,val);
}

void BEEP_Toggle(void)
{
static uint8_t stat = 0;
if(stat)
{
TIM_SetCompare1(TIM2,1480);
}else
{
TIM_SetCompare1(TIM2,0);
}
stat = !stat;
}
