#ifndef CONFIG_H
#define CONFIG_H

#include "main.h"

typedef struct
{
	TIM_HandleTypeDef* 	htim;
	UART_HandleTypeDef* huart;
} STM_HandlesTypeDef;

void Sysclk_Config(void);
void GPIO_Config(void);
void PWM_Config(STM_HandlesTypeDef* handles);
void UART_Config(STM_HandlesTypeDef* handles);

#endif
