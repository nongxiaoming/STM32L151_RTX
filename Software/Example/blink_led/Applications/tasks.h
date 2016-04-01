#ifndef __TASKS_H_
#define __TASKS_H_
#include "RTL.h"

extern OS_TID ledTask;
#define LED_TASK_PRIORITY            (3)
void led_task_init(void);



#endif
