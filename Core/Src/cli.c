#include "CLI.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t ledMode = 0;


void uart_send(const char* msg)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

void command_processor(char* cmd, LED_t *led)
{
	if(strcmp(cmd, "mode 0") == 0)
	{
		ledMode = 0;
	}

	else if(strcmp(cmd, "mode 1") == 0)
		{
			ledMode = 1;
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
