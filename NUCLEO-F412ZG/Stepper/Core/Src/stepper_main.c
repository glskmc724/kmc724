#include <stdlib.h>
#include <string.h>


#include "main.h"
#include "config.h"

STM_HandlesTypeDef handles;
static uint32_t PWM_Count = 0;

int main(void)
{
	handles.htim = (TIM_HandleTypeDef*)calloc(1, sizeof(TIM_HandleTypeDef));

	HAL_Init();

	Sysclk_Config();
	GPIO_Config();
	PWM_Config(&handles);
//	UART_Config(&handles);

	HAL_TIM_PWM_Start_IT(handles.htim, TIM_CHANNEL_1);

	while (1)
	{
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		HAL_Delay(100);
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim)
{
	if (htim->Instance == handles.htim->Instance)
	{
		if (PWM_Count == 0)
		{
			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		}
		PWM_Count = (PWM_Count + 1) % 1000;
	}
}
