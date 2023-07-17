#include <stdio.h>
#include <string.h>
#include "circular_queue.h"

int main(void)
{
	circular_queue queue;
	uint8_t* buffer;
	uint8_t ret;
	
	circular_queue_init(&queue);
	buffer = (uint8_t*)malloc(sizeof(uint8_t) * BUFFER_SIZE);

	for (uint8_t i = 0; i < QUEUE_SIZE; i++)
	{
		sprintf(buffer, "%d", i);
		if ((ret = circular_queue_push(&queue, buffer, strlen(buffer)) == 0))
		{
			printf("Queue is full\r\n");

			return 0;
		}
	}

	for (uint8_t i = 0; i < QUEUE_SIZE; i++)
	{
		printf("Size=%d\r\n", queue.size);
		printf("%s\r\n", queue.buffer[(queue.front)]);
		circular_queue_pop(&queue);
	}

	return 0;
}