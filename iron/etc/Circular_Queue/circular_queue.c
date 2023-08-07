#include "circular_queue.h"

void circular_queue_init(circular_queue* queue)
{
	queue->front = 0;
	queue->rear = 0;
	queue->size = 0;
	queue->buffer = (uint8_t**)malloc(sizeof(uint8_t*) * QUEUE_SIZE);

	for (uint8_t i = 0; i < QUEUE_SIZE; i++)
	{
		queue->buffer[i] = (uint8_t*)malloc(sizeof(uint8_t) * BUFFER_SIZE);
	}
}

uint8_t circular_queue_push(circular_queue* queue, uint8_t* buffer, uint8_t len)
{
	if (circular_queue_full(queue))
	{
		return 0;
	}
	else
	{
		queue->size += 1;
		memcpy(queue->buffer[queue->rear], buffer, len);
		queue->rear = (queue->rear + 1) % QUEUE_SIZE;

		return 1;
	}
}

uint8_t circular_queue_pop(circular_queue* queue)
{
	if (circular_queue_empty(queue))
	{
		return 0;
	}
	else
	{
		queue->size -= 1;
		queue->front = (queue->front + 1) % QUEUE_SIZE;

		return 1;
	}
}

uint8_t circular_queue_empty(circular_queue* queue)
{
	if (queue->size == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t circular_queue_full(circular_queue* queue)
{
	if (queue->size == QUEUE_SIZE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}