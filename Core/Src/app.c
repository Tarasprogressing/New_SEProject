#include "app.h"




void App_Init(App_t *app)
{
		app->currentState = SYSTEM_LED_OFF;
		app->previousState = SYSTEM_LED_OFF;
		LED_Off(app->led);
}


void App_Process(App_t *app)
{
	Button_Update(app->button);


	/* Обробка подій */

	ButtonEvent_t event = Button_GetEvent(app->button);

	if(event == BUTTON_SHORT)
	{
		app->currentState = SYSTEM_LED_ON;
	}
	else if(event == BUTTON_LONG)
	{
		app->currentState = SYSTEM_LED_BLINK;
	}

	/* Обробка поточного стану */

	if(app->currentState != app->previousState)
	{
	if(app->currentState == SYSTEM_LED_OFF)
	{
		LED_StopBlink(app->led);
		LED_Off(app->led);
		uart_send("OFF\r\n");
	}
	else if(app->currentState == SYSTEM_LED_ON)
	{
		LED_StopBlink(app->led);
		LED_On(app->led);
		uart_send("ON\r\n");
	}
	else if(app->currentState == SYSTEM_LED_BLINK)
	{
		 LED_StartBlink(app->led, 0, 500);
	}

	app->currentState = app->previousState;
	}
	/*else if(app->currentState == SYSTEM_LED_BLINK)
	{
		LED_StartBlink(app->led, 0, 500);
		uart_send("BLINK\r\n");
	}*/

	else if(app->currentState == SYSTEM_LED_BLINK)
	{
	    LED_Toggle(app->led);
	    HAL_Delay(500);
	}
}
