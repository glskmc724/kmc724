#include <stdio.h>

#include "main.h"
#include "config.h"

int main(void)
{
	HAL_Init();

	Sysclk_Config();
	GPIO_Config();
	UART_Config();

	while (1)
	{
		printf("Test\r\n");
		HAL_Delay(1000);
	}
}
