#include "CLI.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "LED.h"

uint32_t ledMode = 0;


void uart_send(const char* msg)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

void command_processor(char* cmd, App_t *app)
{
	char *stateStr = "Unknown";

	if(strcmp(cmd, "led on") == 0)
	{
		App_SetState(app, SYSTEM_LED_ON);
		stateStr = "On";
		uart_send("LED ON CMD\r\n");
	}

	else if(strcmp(cmd, "led off") == 0)
	{
		App_SetState(app, SYSTEM_LED_OFF);
		stateStr = "Off";
		uart_send("LED OFF CMD\r\n");
	}

	else if(strcmp(cmd, "status") == 0)
	{
		stateStr = "The system is in order";
		uart_send("The system is in order\r\n");
	}


	else if(strcmp(cmd, "blink") == 0)
	{
		App_SetState(app, SYSTEM_LED_BLINK);
		stateStr = "Blink";
		uart_send("BLINK CMD\r\n");
	}
}
