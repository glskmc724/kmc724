#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdlib.h>
#include <stdint.h>

#define QUEUE_SIZE 16
#define BUFFER_SIZE	128

typedef struct
{
	uint8_t size;
	uint8_t front;
	uint8_t rear;
	uint8_t** buffer;
} circular_queue;

void circular_queue_init(circular_queue* queue);
uint8_t circular_queue_push(circular_queue* queue, uint8_t* buffer, uint8_t len);
uint8_t circular_queue_pop(circular_queue* queue);
uint8_t circular_queue_empty(circular_queue* queue);
uint8_t circular_queue_full(circular_queue* queue);

#endif