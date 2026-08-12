#ifndef _KEY_H
#define _KEY_H

#include "stm32f4xx_hal.h"


#ifdef __cplusplus
extern "C" {
#endif

#define KEY_GPIO_PORT GPIOC
#define KEY_PIN      GPIO_PIN_11

#define KEY_WAIT_LONG_PRESS_TIME 10
#define KEY_DELAY_TIME 20
#define KEY_LONG_PRESS_counter 100
#define KEY_SHORT_PRESS_counter 5   

typedef enum{
    KEY_STATE_IDLE = 0,
    KEY_STATE_LONGP = 1,
    KEY_STATE_SHORTP = 2,
}KEY_STATE;

typedef enum{
    KEY_PROC_IDLE=0,
    KEY_PROC_CHECK=1,
    KEY_PROC_HOLDING=2,
    KEY_PROC_RELEASE=3,
}KEY_PROC_STATE;

int Key_get_state(void);


#ifdef __cplusplus
}
#endif

#endif