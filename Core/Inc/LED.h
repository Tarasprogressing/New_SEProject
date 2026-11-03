#ifndef LED_H
#define LED_H

#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "timer.h"

typedef struct
{
	GPIO_TypeDef* GPIO_Port;
	uint16_t GPIO_Pin;

	uint16_t state;
	uint32_t blinkInterval;
	uint32_t lastToggleTime;
	uint32_t blinking;
	uint32_t blinkCount;
	uint32_t currentBlink;

	Timer_t blinkTmer;




} LED_t;

void LED_Init(LED_t* led, GPIO_TypeDef* port, uint16_t pin);
void LED_On(LED_t* led);
void LED_Off(LED_t* led);
void LED_Toggle(LED_t* led);
void LED_StartBlink(LED_t* led, uint32_t count, uint32_t interval);
void LED_StopBlink(LED_t* led);
void LED_Update(LED_t* led);

#endif
