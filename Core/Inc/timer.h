#ifndef TIMER_H
#define TIMER_H

#include "main.h"


typedef struct
{
	uint32_t startTime;
	uint32_t timeout;
	uint8_t active;

} Timer_t;

void Timer_Start(Timer_t *timer, uint32_t timeout);
void Timer_Stop(Timer_t *timer);
uint8_t Timer_Expired(Timer_t *timer);

#endif
