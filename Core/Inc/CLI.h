#ifndef CLI_H
#define CLI_H

#include "main.h"
#include "LED.h"
#include "app.h"

extern UART_HandleTypeDef huart2;

void uart_send(const char *msg);
void command_processor(char* cmd, App_t *app);

#endif
