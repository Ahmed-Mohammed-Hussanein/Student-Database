/* Ahmed Mohammed Hussanein Ali 
	Implementation of FIFO */

#include "FIFO.h"
#include "Platform_Types.h"

#define NULL (void*)0

FIFO_STATUS FIFO_Init(FIFO_t *FIFO_buffer, element_type *buffer, uint32_t length)
{
	/* NULL pointer passed */
	if ( NULL == buffer || NULL == FIFO_buffer || 0 >= length)
		return FIFO_null;

	/* every thing is ok */
	FIFO_buffer->base = buffer;
	FIFO_buffer->head = buffer;
	FIFO_buffer->tail = buffer;
	FIFO_buffer->length = length;
	FIFO_buffer->count = 0;

	return FIFO_no_errors;
}

FIFO_STATUS FIFO_Enqueue(FIFO_t *FIFO_buffer, element_type *item)
{
	/* check if there is an error */
	FIFO_STATUS status = FIFO_Is_full(FIFO_buffer);
	if (status != FIFO_not_full)
		return status;

	/* no errors */
	*(FIFO_buffer->head) = *item;
	FIFO_buffer->count++;

	if (FIFO_buffer->head >= (FIFO_buffer->base + FIFO_buffer->length))
		FIFO_buffer->head = FIFO_buffer->base;

	else
		FIFO_buffer->head++;

	return FIFO_no_errors;
}

FIFO_STATUS FIFO_Dequeue(FIFO_t *FIFO_buffer, element_type *item)
{
	/* check if there is an error */
	FIFO_STATUS status = FIFO_Is_empty(FIFO_buffer);
	if (status != FIFO_not_empty)
		return status;

	/* no errors */
	*(item) = *(FIFO_buffer->tail);
	FIFO_buffer->count--;

	if (FIFO_buffer->tail >= (FIFO_buffer->base + FIFO_buffer->length))
		FIFO_buffer->tail = FIFO_buffer->base;

	else
		FIFO_buffer->tail++;

	return FIFO_no_errors;
}

FIFO_STATUS FIFO_Is_empty(FIFO_t *FIFO_buffer)
{
	/* buffer is not found */
	if (NULL == FIFO_buffer->base)
		return FIFO_null;

	/* buffer is empty */
	if (0 == FIFO_buffer->count)
		return FIFO_empty;

	return FIFO_not_empty;
}

FIFO_STATUS FIFO_Is_full(FIFO_t *FIFO_buffer)
{
	/* buffer is not found */
	if (NULL == FIFO_buffer->base)
		return FIFO_null;

	/* buffer is full */
	if (FIFO_buffer->count == FIFO_buffer->length)
		return FIFO_full;

	return FIFO_not_full;
}