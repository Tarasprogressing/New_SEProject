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

void command_processor(char* cmd, LED_t *led, LED_t *led_r)
{
	uart_send("CMD=");
	uart_send(cmd);
	uart_send("\r\n");

	if(strcmp(cmd, "led on") == 0)
	{
		LED_StopBlink(led);
		LED_On(led);
	}

	else if(strcmp(cmd, "led on read") == 0)
	{
		LED_StopBlink(led_r);
		LED_On(led_r);
	}

	else if(strcmp(cmd, "led off") == 0)
	{
		LED_StopBlink(led);
		LED_Off(led);
	}

	else if(strcmp(cmd, "led off read") == 0)
	{
		LED_StopBlink(led_r);
		LED_Off(led_r);
	}

	else if(strcmp(cmd, "help") == 0)
	{
		uart_send("Available commands: \r\n");
		uart_send("led on;\r\n");
		uart_send("led off;\r\n");
		uart_send("toggle;\r\n");
		uart_send("help;\r\n");
		uart_send("status;\r\n");
		uart_send("blink c d;\r\n");
	}

	else if(strcmp(cmd, "status") == 0)
	{

		char msg[200];

		snprintf(msg, sizeof(msg), "LED state: %s\r\n" "Blinking: %s\r\n" "Interval: %lu\r\n" "Current blink: %lu\r\n" "Target blink: %lu\r\n",
				led->state ? "ON" : "OFF", led->blinking ? "YES" : "NO", led->blinkInterval, led->currentBlink, led->blinkCount);

		uart_send(msg);

	}

	else if(strcmp(cmd, "status read") == 0)
	{

		char msgr[200];

		snprintf(msgr, sizeof(msgr), "LED state: %s\r\n" "Blinking: %s\r\n" "Interval: %lu\r\n" "Current blink: %lu\r\n" "Target blink: %lu\r\n",
				led_r->state ? "ON" : "OFF", led_r->blinking ? "YES" : "NO", led_r->blinkInterval, led_r->currentBlink, led_r->blinkCount);

		uart_send(msgr);

	}

	else if(strcmp(cmd, "toggle") == 0)
	{
		LED_StopBlink(led);
		LED_Toggle(led);
	}

	else if(strcmp(cmd, "toggle read") == 0)
		{
			LED_StopBlink(led_r);
			LED_Toggle(led_r);
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

	else if(strncmp(cmd, "blink_r ", 8) == 0)
		{
			uart_send("BLINK COMMAND DETECTED\r\n");

			char *arg3;
			char *arg4;

			arg3 = strtok(cmd + strlen("blink_r "), " ");
			arg4 = strtok(NULL, " ");

			if(arg3 == NULL || arg4 == NULL)
			{
				uart_send("Invalid command\r\n");
				return;
			}

			int cntr = atoi(arg3);
			int delayr = atoi(arg4);

			char msgr[50];

			sprintf(msgr, "Cnt=%d delay=%d\r\n", cntr, delayr);

			uart_send(msgr);

			if(cntr < 1 || cntr > 10)
			{
				uart_send("The first parameter is incorrect\r\n");
				return;
			}

			if(delayr < 10 || delayr > 5000)
			{
				uart_send("Second parameter is incorrect \r\n");
				return;
			}

			LED_StartBlink(led_r, cntr, delayr);

			uart_send("Blink started\r\n");
		}
}
