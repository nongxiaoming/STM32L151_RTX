#include "power.h"

/******************************************************************************************
*函数名：POWER_Init()
* 参数：void
* 返回值：void
* 功能：LED的管脚配置
*********************************************************************************************/
void POWER_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	 /* LED GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(EN_POW_RF433_RCC | EN_POW_OEM_RCC |EN_POW_OEM_LNA_RCC | EN_POW_BT_RCC |EN_POW_SIM_RCC | EN_POW_GLOB_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_InitStructure.GPIO_Pin = EN_POW_GLOB_PIN;
	GPIO_SetBits(EN_POW_GLOB_PORT,EN_POW_GLOB_PIN);
  GPIO_Init(EN_POW_GLOB_PORT, &GPIO_InitStructure);
  
	
  GPIO_InitStructure.GPIO_Pin = EN_POW_RF433_PIN;
  GPIO_Init(EN_POW_RF433_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = EN_POW_OEM_PIN;
  GPIO_Init(EN_POW_OEM_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = EN_POW_OEM_LNA_PIN;
  GPIO_Init(EN_POW_OEM_LNA_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = EN_POW_BT_PIN;
  GPIO_Init(EN_POW_BT_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = EN_POW_SIM_PIN;
  GPIO_Init(EN_POW_SIM_PORT, &GPIO_InitStructure);
  
	POWER_Enable(POWER_GLOB);
	POWER_Disable(POWER_RF433|POWER_OEM|POWER_OEM_LNA|POWER_BT|POWER_SIM);

}

void POWER_Enable(uint8_t power_channel)
{
  if(power_channel&POWER_GLOB)
	{
	 GPIO_SetBits(EN_POW_GLOB_PORT,EN_POW_GLOB_PIN);
	}
	  if(power_channel&POWER_RF433)
	{
	 GPIO_SetBits(EN_POW_RF433_PORT,EN_POW_RF433_PIN);
	}
	 if(power_channel&POWER_OEM)
	{
	 GPIO_SetBits(EN_POW_OEM_PORT,EN_POW_OEM_PIN);
	}
	if(power_channel&POWER_OEM_LNA)
	{
	 GPIO_SetBits(EN_POW_OEM_LNA_PORT,EN_POW_OEM_LNA_PIN);
	}
	if(power_channel&POWER_BT)
	{
	 GPIO_SetBits(EN_POW_BT_PORT,EN_POW_BT_PIN);
	}
	if(power_channel&POWER_SIM)
	{
	 GPIO_SetBits(EN_POW_SIM_PORT,EN_POW_SIM_PIN);
	}
}

void POWER_Disable(uint8_t power_channel)
{
  if(power_channel&POWER_GLOB)
	{
	 GPIO_ResetBits(EN_POW_GLOB_PORT,EN_POW_GLOB_PIN);
	}
	  if(power_channel&POWER_RF433)
	{
	 GPIO_ResetBits(EN_POW_RF433_PORT,EN_POW_RF433_PIN);
	}
	 if(power_channel&POWER_OEM)
	{
	 GPIO_ResetBits(EN_POW_OEM_PORT,EN_POW_OEM_PIN);
	}
	if(power_channel&POWER_OEM_LNA)
	{
	 GPIO_ResetBits(EN_POW_OEM_LNA_PORT,EN_POW_OEM_LNA_PIN);
	}
	if(power_channel&POWER_BT)
	{
	 GPIO_ResetBits(EN_POW_BT_PORT,EN_POW_BT_PIN);
	}
	if(power_channel&POWER_SIM)
	{
	 GPIO_ResetBits(EN_POW_SIM_PORT,EN_POW_SIM_PIN);
	}

}





