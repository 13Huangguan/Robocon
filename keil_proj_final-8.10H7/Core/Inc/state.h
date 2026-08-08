#ifndef __STATE_H
#define __STATE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "led.h"
typedef enum
{
	STATE_IDLE=0,
	STATE_RUN,
	STATE_ALARM,
	STATE_COUNT
}MODE;
typedef void (*state_func)(void);
void led_run();





#ifdef __cplusplus
}
#endif

#endif /* __STATE_H */