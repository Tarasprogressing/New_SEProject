#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"
#include "timer.h"

typedef enum
{
	BUTTON_NONE,
	BUTTON_SHORT,
	BUTTON_LONG
} ButtonEvent_t;

typedef struct
{
	GPIO_TypeDef* GPIO_Port;
	uint16_t GPIO_PIN;

	uint32_t currentState;
	uint32_t previousState;

	uint32_t pressTime;
	uint32_t pressDuration;
	uint32_t releaseTime;
	ButtonEvent_t buttonEvent;

	Timer_t debounceTimer;
	Timer_t longPressTimer;

} Button_t;

void Button_Init(Button_t* button, GPIO_TypeDef* port, uint16_t pin);

void Button_Update(Button_t* button);

uint32_t Button_GetPressDuration(Button_t* button);

ButtonEvent_t Button_GetEvent(Button_t* button);

#endif
