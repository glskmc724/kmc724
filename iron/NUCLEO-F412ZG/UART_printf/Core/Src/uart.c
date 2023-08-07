#include "main.h"

extern UART_HandleTypeDef huart3;

int _write(int32_t file, uint8_t* ptr, int32_t len)
{
	for (int32_t x = 0; x < len; x++)
	{
		if (HAL_UART_Transmit(&huart3, ptr, len, len) == HAL_OK)
		{
			return len;
		}
		else
		{
			return 0;
		}
	}
}
