/* Ahmed Mohammed Hussanein Ali 
	Implementation of FIFO */

#ifndef FIFO_H_
#define FIFO_H_

#include "Platform_Types.h"


typedef struct
{
	uint8_t 	FirstName[32];
	uint8_t 	LastName[32];
	uint16_t 	CourseId[5];
	uint32_t	Roll_Id;
	float32_t 	GPA;
	
} sStudent_Data_t;


#define element_type sStudent_Data_t

/* Type definitions */
typedef struct
{
	uint32_t  length;
	element_type* base;		/* Pointer to the first of the buffer */
	element_type* head;		/* Increases with adding items */
	element_type* tail;		/* Moves towards head pointer with removing items */
	uint32_t  count;	
} FIFO_t;

typedef enum
{
	FIFO_no_errors,
	FIFO_full,
	FIFO_not_full,
	FIFO_empty,
	FIFO_not_empty,
	FIFO_null

} FIFO_STATUS;

/* APIs */
FIFO_STATUS FIFO_Init(FIFO_t *FIFO_buffer, element_type *buffer, uint32_t length);
FIFO_STATUS FIFO_Enqueue(FIFO_t *FIFO_buffer, element_type *item);
FIFO_STATUS FIFO_Dequeue(FIFO_t *FIFO_buffer, element_type *item);
FIFO_STATUS FIFO_Is_empty(FIFO_t *FIFO_buffer);
FIFO_STATUS FIFO_Is_full(FIFO_t *FIFO_buffer);

#endif
