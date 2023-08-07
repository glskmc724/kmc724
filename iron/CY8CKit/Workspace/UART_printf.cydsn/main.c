#include <stdio.h>

#include "project.h"

int _write(int file, char* ptr, int len);

int main(void)
{
    uint32 cnt;
    
    CyGlobalIntEnable; 
    UART_DBG_Start();
    
    cnt = 0;
    
    while (1)
    {
        printf("Hello World (cnt=%d)\r\n", cnt++);
        CyDelay(1000);
    }
}

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
