/*
 * D8  = PF_12: RST
 * D9  = PD_15: ENABLE
 * D10 = PD_14: DIR
 * D11 = PA_7 : PULSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "config.h"

STM_HandlesTypeDef handles;

static uint32_t PWM_Count = 0;
static uint16_t loop = 0;

int main(void)
{
	uint8_t data[4];
	uint16_t value;

	HAL_Init();

	Sysclk_Config();
	GPIO_Config();
	PWM_Config(&handles);
	UART_Config(&handles);

	HAL_TIM_PWM_Start_IT(handles.htim, TIM_CHANNEL_1);

	HAL_GPIO_WritePin(L297_ENA_GPIO_Port, L297_ENA_Pin, 1);
	HAL_GPIO_WritePin(L297_DIR_GPIO_Port, L297_DIR_Pin, 0);
	HAL_GPIO_WritePin(L297_RST_GPIO_Port, L297_RST_Pin, 1);

	while (1)
	{
		if (HAL_UART_Receive(handles.huart, data, 4, 1000) == HAL_OK)
		{
			if (data[0] == 0x07 && data[3] == 0x24)
			{
				value = (data[1] << 8) | data[2];
				loop = value * 2;
//				printf("Loop=%d\r\n", loop);
			}
		}
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim)
{
	if (htim->Instance == handles.htim->Instance)
	{
		if (PWM_Count == 0)
		{
			if (loop != 0)
			{
				HAL_GPIO_TogglePin(L297_PULSE_GPIO_Port, L297_PULSE_Pin);
				loop -= 1;
			}
		}
		PWM_Count = (PWM_Count + 1) % 10;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	if (pin == BLUE_BTN_Pin)
	{
		loop = 2;
	}
}
