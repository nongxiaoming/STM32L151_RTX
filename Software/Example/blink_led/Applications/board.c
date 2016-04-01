#include "board.h"



static void NVIC_Configuration(void)
{
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}

int board_init(void)
{
	  POWER_Init();
	
    /* Configure the NVIC Group */
    NVIC_Configuration();

    /* init led driver */
    LED_Init();
	
	  /* beep init */
	  BEEP_Init();
    return 0;
}

int board_deinit(void)
{
//led_hw_deinit();
//uart_hw_deinit();
 return 0;
}
