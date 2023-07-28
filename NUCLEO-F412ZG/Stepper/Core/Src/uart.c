#include "config.h"

extern STM_HandlesTypeDef handles;

int _write(int32_t file, uint8_t* ptr, int32_t len)
{
	for (int32_t x = 0; x < len; x++)
	{
		if (HAL_UART_Transmit(handles.huart, ptr, len, len) == HAL_OK)
		{
			return len;
		}
		else
		{
			return 0;
		}
	}
}
