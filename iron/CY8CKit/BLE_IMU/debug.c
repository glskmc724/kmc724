#include "debug.h"

int _write(int file, char* ptr, int len)
{
    int x;
    file = file;
    for (x = 0; x < len; x++)
    {
        UART_DBG_UartPutChar(*ptr++);
    }
    return len;
}
