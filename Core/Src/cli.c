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

void command_processor(char* cmd, LED_t *led)
{
	if(strcmp(cmd, "led on") == 0)
	{
		LED_StopBlink(led);
		LED_On(led);
	}

	else if(strcmp(cmd, "led off") == 0)
	{
		LED_StopBlink(led);
		LED_Off(led);
	}

	else if(strcmp(cmd, "help") == 0)
	{
		uart_send("Available commands: \r\n"
				"led on;\r\n"
				"led off;\r\n"
				"help;\r\n"
				"status;\r\n"
				"blink c d;\r\n");
	}

	else if(strcmp(cmd, "status") == 0)
	{
		uart_send("The System is in order \r\n");
	}

	else if(strncmp(cmd, "blink ", 6) == 0)
	{
		uart_send("BLINK COMMAND DETECTED\r\n");

		char *arg1;
		char *arg2;

		arg1 = strtok(cmd + strlen("blink "), " ");
		arg2 = strtok(NULL, " ");

		if(arg1 == NULL || arg2 == NULL)
		{
			uart_send("Invalid command\r\n");
			return;
		}

		int cnt = atoi(arg1);
		int delay = atoi(arg2);

		char msg[50];

		sprintf(msg, "Cnt=%d delay=%d\r\n", cnt, delay);

		uart_send(msg);

		if(cnt < 1 || cnt > 10)
		{
			uart_send("The first parameter is incorrect\r\n");
			return;
		}

		if(delay < 10 || delay > 5000)
		{
			uart_send("Second parameter is incorrect \r\n");
			return;
		}

		LED_StartBlink(led, cnt, delay);

		uart_send("Blink started\r\n");
	}
}
