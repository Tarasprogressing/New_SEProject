#include "CLI.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "LED.h"


static void Cmd_LedOn(App_t *app)
{
	App_SetState(app, SYSTEM_LED_ON);
	uart_send("LED ON\r\n");
}

static void Cmd_LedOff(App_t *app)
{
	App_SetState(app, SYSTEM_LED_OFF);
	uart_send("LED OFF\r\n");
}

static void Cmd_Blink(App_t *app)
{
	App_SetState(app, SYSTEM_LED_BLINK);
	uart_send("LED BLINK\r\n");
}

static void Cmd_Status(App_t *app)
{
	SystemState_t state = App_GetState(app);

	if(state == SYSTEM_LED_ON)
	{
		uart_send("State: On\r\n");
	}

	if(state == SYSTEM_LED_OFF)
	{
		uart_send("State: Off\r\n");
	}

	if(state == SYSTEM_LED_BLINK)
	{
		uart_send("State: Blink\r\n");
	}
}

typedef struct
{
    const char *name;
    void (*handler)(App_t *app);

} Command_t;



void uart_send(const char* msg)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

void command_processor(char* cmd, App_t *app)
{

	if(strcmp(cmd, "led on") == 0)
	{
		Cmd_LedOn(app);
	}

	else if(strcmp(cmd, "led off") == 0)
	{
		Cmd_LedOff(app);
	}

	else if(strcmp(cmd, "status") == 0)
	{
		Cmd_Status(app);
	}

	else if(strcmp(cmd, "blink") == 0)
	{
		Cmd_Blink(app);
	}

	else if(strcmp(cmd, "help") == 0)
	{
		uart_send("Available commands:\r\n"
					"help\r\n"
					"status\r\n"
					"led on\r\n"
					"led off\r\n"
					"blink\r\n");
	}

	else if(strcmp(cmd, "version") == 0)
	{
		uart_send("Firmware v1.0\r\n");
	}

	else if(strcmp(cmd, "Up time") == 0)
	{
		uart_send("12 s\r\n");
	}
}
