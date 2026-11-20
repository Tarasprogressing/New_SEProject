#include "CLI.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "LED.h"

uint32_t commandsCount = 0;

void uart_send(const char* msg)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

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

static void Cmd_LedOn(App_t *app);
static void Cmd_LedOff(App_t *app);
static void Cmd_Status(App_t *app);
static void Cmd_Version(App_t *app);
static void Cmd_Help(App_t *app);
static void Cmd_Uptime(App_t *app);

Command_t commandsTable[] =
{
		{"led on", Cmd_LedOn},
		{"led off", Cmd_LedOff},
		{"status", Cmd_Status},
		{"version", Cmd_Version},
		{"help", Cmd_Help},
		{"uptime", Cmd_Uptime}

};

static void Cmd_Version(App_t *app)
{
	uart_send("Version: 3; \r\n");
}

static void Cmd_Help(App_t *app)
{
	commandsCount = sizeof(commandsTable) / sizeof(commandsTable[0]);

   for(int i = 0; i < commandsCount; i++)
   {
	   uart_send(commandsTable[i].name);
	   uart_send("\r\n");
   }
}

static void Cmd_Uptime(App_t *app)
{
	unsigned long uptimeSec = HAL_GetTick() / 1000;
	char msg[50];
	sprintf(msg, "Uptime: %lu seconds;\r\n", uptimeSec);
	uart_send(msg);

}


void command_processor(char* cmd, App_t *app)
{

	if(strncmp(cmd, "blink", 5) == 0)
		{
		 uart_send("ENTER BLINK\r\n");
			char *arg1;
			char *arg2;
			char *arg3;

			arg1 = strtok(cmd, " ");
			arg2 = strtok(NULL, " ");
			arg3 = strtok(NULL, " ");

			if(arg1 == NULL || arg2 == NULL || arg3 == NULL)
			{
				uart_send("Invalid command\r\n");
				return;
			}

			int cnt = atoi(arg2);
			int delay = atoi(arg3);

			app->blinkCount = cnt;
			app->blinkDelay = delay;

			App_StartBlink(app, app->blinkCount, app->blinkDelay);

			uart_send("Blink Started \r\n");

			return;

			if(cnt < 1 || cnt > 10)
			{
				uart_send("Invalid the first parameter\r\n");
				return;
			}

			if(delay < 10 || delay > 5000)
			{
				uart_send("Invalid second parameter\r\n");
				return;
			}

			uart_send("Blink started\r\n");
			return;
			}

	uint32_t commandCount = sizeof(commandsTable) / sizeof(commandsTable[0]);

	for(uint32_t i = 0; i < commandCount; i++)
	{
		if(strcmp(cmd, commandsTable[i].name) == 0)
		{
			commandsTable[i].handler(app);
			return;
		}
	}

	uart_send("Unknown command\r\n");


	}




