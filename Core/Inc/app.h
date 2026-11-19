#ifndef APP_H
#define APP_H

#include "main.h"
#include "BUTTON.h"
#include "LED.h"
#include "timer.h"

typedef enum
{
	SYSTEM_LED_OFF,
	SYSTEM_LED_ON,
	SYSTEM_LED_BLINK
} SystemState_t;

typedef struct
{
	LED_t *led;
	Button_t *button;

	SystemState_t currentState;
	SystemState_t previousState;

	uint32_t blinkCount;
	uint32_t blinkDelay;
	uint32_t remainingBlink;

} App_t;

void App_Init(App_t *app);
void App_Process(App_t *app);
void App_SetState(App_t *app, SystemState_t state);
SystemState_t App_GetState(App_t *app);
void App_StartBlink(App_t *app, uint32_t count, uint32_t delay);


#endif
