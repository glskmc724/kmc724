#include "main.h"
#include "config.h"

int main(void)
{
	HAL_Init();
	Sysclk_Config();
	GPIO_Config();

	while (1)
	{
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

		HAL_Delay(1000);
	}
}
