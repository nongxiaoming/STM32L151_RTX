#include "led.h"
#include "RTL.h"
#include "tasks.h"
#include "iwdg.h"
#include "beep.h"

OS_TID ledTask;




__task void led_task(void) {
 
	  os_itv_set(50); 

	  LED_Init();
	  /* 初始化看门狗 */
	  IWDG_Init();
    while(1) {
			
			 LED_Toggle(LED_BLUE|LED_GREEN);

			 /* Reload IWDG counter */
       IWDG_ReloadCounter();
       os_itv_wait();
    }
}

void led_task_init(void)
{
 ledTask = os_tsk_create(led_task, LED_TASK_PRIORITY);
}
