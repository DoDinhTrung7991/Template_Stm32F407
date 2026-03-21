#include <string.h>
#include "queue.h"

void queue_init(queue_t* queue_ptr)
{
    memset(queue_ptr, 0, sizeof(queue_t));
    queue_ptr->isEmpty = true;
}

void queue_enqueue(queue_t* queue_ptr, uint16_t arg)
{
    if (queue_ptr->isFull)
    {
        queue_ptr->overrun = true;
        queue_ptr->front = (queue_ptr->front + 1) % ARR_SIZE;
    }

    queue_ptr->buf[queue_ptr->rear] = arg;
    queue_ptr->rear = (queue_ptr->rear + 1) % ARR_SIZE;
    queue_ptr->isEmpty = false;

    if (queue_ptr->rear == queue_ptr->front)
    {
        queue_ptr->isFull = true;
    }
}

uint8_t queue_dequeue(queue_t* queue_ptr, uint16_t* buffer_ptr, uint8_t numToDequeue)
{
    if (queue_ptr->isEmpty || numToDequeue == 0)
    {
        return 0;
    }

    uint8_t index = 0;
    while(index < numToDequeue && !queue_ptr->isEmpty)
    {
        buffer_ptr[index] = queue_ptr->buf[queue_ptr->front];
        queue_ptr->front = (queue_ptr->front + 1) % ARR_SIZE;
        index++;

        if (queue_ptr->front == queue_ptr->rear)
        {
            queue_ptr->isEmpty = true;
        }
        
        queue_ptr->isFull = false;
        queue_ptr->overrun = false;
    }

    return index;
}

uint8_t queue_get_size(queue_t* queue_ptr)
{
    if (queue_ptr->isEmpty)
    {
        return 0;
    }
    if (queue_ptr->isFull)
    {
        return ARR_SIZE;
    }
    if (queue_ptr->rear > queue_ptr->front)
    {
        return queue_ptr->rear - queue_ptr->front;
    }
    // Wraparound case
    return (ARR_SIZE - queue_ptr->front) + queue_ptr->rear;
}
