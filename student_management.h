#ifndef _STUDENT_MANAGEMENT_H_
#define _STUDENT_MANAGEMENT_H_

#include "FIFO.h"
#include "Platform_Types.h"

typedef enum
{
	DB_NOK,
	DB_OK,
	DB_FULL,
	DB_EMPTY,
	DB_NOT_FOUND

} eStatus_t;

extern FIFO_t dataBase;

eStatus_t DB_Init(uint32_t initSize);
eStatus_t DB_Add(FILE *p2File);
eStatus_t DB_updateStudent(uint32_t rollNumber, uint8_t updateOption);
eStatus_t DB_deleteStudent(uint32_t rollNumber);
eStatus_t DB_Find_rollNumber(uint32_t rollNumber);
eStatus_t DB_Find_fName(uint8_t fname[]);
eStatus_t DB_Find_courseID(uint32_t courseID);
eStatus_t DB_totalNumberOfStudents(uint32_t *tNumber);
eStatus_t DB_showAll();
void delete_database();

#endif
