#include "BUTTON.h"

#define DEBOUNCE_TIME 50
#define LONG_PRESS_TIME 1000

void Button_Init(Button_t* button, GPIO_TypeDef* button_port, uint16_t button_pin)
{
	button->GPIO_Port = button_port;
	button->GPIO_PIN = button_pin;

	button->currentState = 0;
	button->previousState = 0;

	button->pressTime = 0;
	button->pressDuration = 0;
	button->releaseTime = 0;

	button->currentState = HAL_GPIO_ReadPin(button_port, button_pin);

	button->buttonEvent = BUTTON_NONE;

	button->previousState = button->currentState;
}

void Button_Update(Button_t* button)
{
	 button->previousState = button->currentState;

		  button->currentState = HAL_GPIO_ReadPin(button->GPIO_Port, button->GPIO_PIN);

		  if(!button->currentState && button->previousState)
		  {
			  HAL_Delay(DEBOUNCE_TIME);

			  button->currentState = HAL_GPIO_ReadPin(button->GPIO_Port, button->GPIO_PIN);

			  if(!button->currentState)
			  {
				  button->pressTime = HAL_GetTick();
			  }
		  }

		  if(button->currentState && !button->previousState)
		  {
			  HAL_Delay(DEBOUNCE_TIME);

			  button->currentState = HAL_GPIO_ReadPin(button->GPIO_Port, button->GPIO_PIN);

			  if(button->currentState)
			  {
				  button->releaseTime = HAL_GetTick();
			  }

			  button->pressDuration = button->releaseTime - button->pressTime;

			  if(button->pressDuration < LONG_PRESS_TIME)
			  {
				  button->buttonEvent = BUTTON_SHORT;
			  }
			  else
			  {
				  button->buttonEvent = BUTTON_LONG;

			  }
		  }
}

uint32_t Button_GetPressDuration(Button_t* button)
{
	return button->pressDuration;
}

ButtonEvent_t Button_GetEvent(Button_t* button)
{
	ButtonEvent_t event = button->buttonEvent;

	button->buttonEvent = BUTTON_NONE;

	return event;

}
