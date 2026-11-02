#ifndef CLI_H
#define CLI_H

#include "main.h"
#include "LED.h"

extern UART_HandleTypeDef huart2;

void uart_send(const char *msg);
void command_processor(char* cmd, LED_t *led, LED_t *led_r);

#endif
