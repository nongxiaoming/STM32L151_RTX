#ifndef __BOARD_H
#define __BOARD_H

#include "stm32l1xx.h"
#include "led.h"
#include "usart.h"
#include "power.h"
#include "key.h"
#include "beep.h"

int board_init(void);
int board_deinit(void);

#endif /* endif __BOARD_H */
