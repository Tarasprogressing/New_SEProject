#include "LED.h"



void LED_Init(LED_t* led, GPIO_TypeDef* port, uint16_t pin)
{
	led->GPIO_Port = port;
	led->GPIO_Pin = pin;

	led->state = 0;
	led->lastToggleTime = 0;

	led->blinkInterval = 0;
	led->blinking = 0;

	led->blinkCount = 0;
	led->currentBlink = 0;
}

void LED_On(LED_t* led)
{
	HAL_GPIO_WritePin(led->GPIO_Port, led->GPIO_Pin, GPIO_PIN_SET);
}

void LED_Off(LED_t* led)
{
	HAL_GPIO_WritePin(led->GPIO_Port, led->GPIO_Pin, GPIO_PIN_RESET);
}

void LED_Toggle(LED_t* led)
{
	HAL_GPIO_TogglePin(led->GPIO_Port, led->GPIO_Pin);
}

void LED_StartBlink(LED_t* led, uint32_t count, uint32_t interval)
{
	led->blinkCount = count * 2;

	led->currentBlink = 0;
	led->blinking = 1;
	led->blinkInterval = interval;
	led->lastToggleTime = HAL_GetTick();
}

void LED_StopBlink(LED_t* led)
{
	led->blinking = 0;
}

void LED_Update(LED_t* led)
{
	if(led->blinking)
	{
		if(HAL_GetTick() - led->lastToggleTime >= led->blinkInterval)
		{
			LED_Toggle(led);
			led->lastToggleTime = HAL_GetTick();

			led->currentBlink++;

			if(led->currentBlink >= led->blinkCount)
			{
				led->blinking = 0;
			}
		}
	}
}

