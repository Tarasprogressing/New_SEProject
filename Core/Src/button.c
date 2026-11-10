#include "BUTTON.h"
#include "CLI.h"

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
			  Timer_Start(&button->longPressTimer, 1000);

			  button->pressTime = HAL_GetTick();

			  //uart_send("PRESS\r\n");
		  }

		  if(button->currentState && !button->previousState)
		  {
			  	  //uart_send("RELEASE\r\n");

				if(Timer_Expired(&button->longPressTimer))
				  {
					  button->buttonEvent = BUTTON_LONG;
					  //uart_send("LONG EVENT\r\n");
				  }
				  else
				  {
					  button->buttonEvent = BUTTON_SHORT;
					  //uart_send("SHORT EVENT\r\n");
				  }
			   }
		  }

ButtonEvent_t Button_GetEvent(Button_t* button)
{
	ButtonEvent_t event = button->buttonEvent;

	button->buttonEvent = BUTTON_NONE;

	return event;

}
