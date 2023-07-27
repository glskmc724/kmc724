/*
 * D10 = PD_14: ENABLE
 * D11 = PA_7 : DIR
 * D12 = PA_6 : Pulse
 * D13 = PA_5 : RST
 */

#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "config.h"

STM_HandlesTypeDef handles;
static uint32_t PWM_Count = 0;

int main(void)
{
	HAL_Init();

	Sysclk_Config();
	GPIO_Config();
	PWM_Config(&handles);
	UART_Config(&handles);

	HAL_TIM_PWM_Start_IT(handles.htim, TIM_CHANNEL_1);

	// ENA = LD1
	// DIR = LD2 (BLUE)
	// RST = LD3

	HAL_GPIO_WritePin(L207_ENA_GPIO_Port, L207_ENA_Pin, 1);
	HAL_GPIO_WritePin(L207_DIR_GPIO_Port, L207_DIR_Pin, 0);
	HAL_GPIO_WritePin(L207_RST_GPIO_Port, L207_RST_Pin, 1);

	while (1)
	{
		if (HAL_GPIO_ReadPin(L207_ENA_GPIO_Port, L207_ENA_Pin) == 1)
		{
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 0);
		}

		if (HAL_GPIO_ReadPin(L207_RST_GPIO_Port, L207_RST_Pin) == 1)
		{
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 1);
		}
		else
		{
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 0);
		}
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim)
{
	if (htim->Instance == handles.htim->Instance)
	{
		if (PWM_Count == 0)
		{
			HAL_GPIO_TogglePin(L297_Test_GPIO_Port, L297_Test_Pin);
		}
		PWM_Count = (PWM_Count + 1) % 1;
	}
}
