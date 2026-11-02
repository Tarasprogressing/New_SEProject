#include "timer.h"


void Timer_Start(Timer_t *timer, uint32_t timeout)
{
	timer->startTime = HAL_GetTick();
	timer->timeout = timeout;
	timer->active = 1;
}

void Timer_Stop(Timer_t *timer)
{
	timer->active = 0;
}
uint8_t Timer_Expired(Timer_t *timer)
{
	if(timer->active && HAL_GetTick() - timer->startTime >= timer->timeout)
		{
			timer->active = 0;

			return 1;
		}
	return 0;
}
