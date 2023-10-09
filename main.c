

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "Platform_Types.h"
#include "student_management.h"
#include "GUI.h"

void welcome_message();
void main_menu(uint8_t pointing);
void update_menu(uint8_t pointing);
void course_update_menu(uint8_t pointing);
void choice();

void add_student_file();
void add_student_manually();
void find_rl();
void find_fn();
void find_c();
void tot_s();
void del_s();
void up_s();
void show_s();

#define TOTAL 		50

int main()
{
	hide_cursor();
	welcome_message();

	eStatus_t status = DB_Init(TOTAL);

	if(status == DB_NOK)
		exit(0);


	choice();

	return 0;
}


void add_student_file()
{
	FILE *p2File;
	p2File = fopen("database.txt", "r");

	if(p2File == NULL)
		exit(0);

	eStatus_t status = DB_Add(p2File);
	fclose(p2File);

	if(status == DB_NOK)
		exit(0);

	if(status == DB_FULL)
		printf("\n\n[ERROR] Database is full.\n\n");

	if(status == DB_OK)
	{
		printf("\n\n[INFO] Students added Successfully\n\n");
		tot_s();
	}
}

void add_student_manually()
{
	eStatus_t status = DB_Add(stdin);
	if(status == DB_NOK)
	{
		printf("\n\n[Error]\n\n");
		exit(0);
	}

	if(status == DB_FULL)
		printf("\n\n[ERROR] Database is full.\n\n");

	if(status == DB_OK)
	{
		printf("\n\n[INFO] Student added Successfully\n\n");
		tot_s();
	}
}

void find_rl()
{
	uint32_t rNumber;
	printf("Enter Student roll number: ");
	
	fflush(stdin), fflush(stdout);
	scanf("%u", &rNumber);

	eStatus_t status = DB_Find_rollNumber(rNumber);

	if(status == DB_NOK)
		exit(0);

	if(status == DB_EMPTY)
		printf("\n\n[ERROR] Database is empty.\n\n");

	if(status == DB_NOT_FOUND)
		printf("\n\n[INFO] Student has roll number %u does not exist.\n\n", rNumber);
}

void find_fn()
{
	uint8_t fName[32];
	printf("Enter Student first name: ");

	fflush(stdin), fflush(stdout);
	scanf("%s", fName);

	eStatus_t status = DB_Find_fName(fName);

	if(status == DB_NOK)
		exit(0);

	if(status == DB_EMPTY)
		printf("\n\n[ERROR] Database is empty.\n\n");

	if(status == DB_NOT_FOUND)
		printf("\n\n[INFO] Student has first name %s does not exist.\n\n", fName);
}

void find_c()
{
	uint32_t cID;
	printf("Enter Student course ID: ");

	fflush(stdin), fflush(stdout);
	scanf("%u", &cID);

	eStatus_t status = DB_Find_courseID(cID);

	if(status == DB_NOK)
		exit(0);

	if(status == DB_EMPTY)
		printf("\n\n[ERROR] Database is empty.\n\n");

	if(status == DB_NOT_FOUND)
		printf("\n\n[INFO] Student has course ID %u does not exist.\n\n", cID);
}

void tot_s()
{
	uint32_t tNumber;

	eStatus_t status = DB_totalNumberOfStudents(&tNumber);
	if(status == DB_NOK)
		exit(0);

	if(status == DB_EMPTY)
	{
		printf("\n\n[INFO] Database is empty.\n");
		return;
	}

	printf("[INFO] The Total Number Of Students is %u.\n", tNumber);
	printf("[INFO] You can add up to %u.\n", TOTAL);
	printf("[INFO] You can add %u more students.\n\n", TOTAL-tNumber);
}

void del_s()
{
	uint32_t rNumber;
	printf("Enter Student roll number: ");
	
	fflush(stdin), fflush(stdout);
	scanf("%u", &rNumber);

	eStatus_t status = DB_deleteStudent(rNumber);

	if(status == DB_NOK)
		exit(0);

	if(status == DB_EMPTY)
	{
		printf("\n\n[ERROR] Database is empty.\n\n");
		return;
	}

	if(status == DB_NOT_FOUND)
	{
		printf("\n\n[INFO] Student has course ID %u does not exist.\n\n", rNumber);
		return;
	}

	printf("\n\n[INFO] Student is deleted Successfully.\n\n");
}

void up_s()
{
	uint32_t rNumber;
	uint8_t updateOption;
	printf("Enter Student roll number: ");
	
	fflush(stdin), fflush(stdout);
	scanf("%u", &rNumber);


	uint8_t pointer = 1;
    uint8_t pressedKey = 0;

    while(1)
    {
        update_menu(pointer);
        while(1)
        {
            pressedKey = getch();
            if(pressedKey == 72)
            {
                pointer--;
                if(pointer == 0)
                    pointer = 6;

                break;
            }
            else if(pressedKey == 80)
            {
                pointer++;
                if(pointer == 7)
                    pointer = 1;

                break;
            }
            else if(pressedKey == VK_RETURN)
            {
            	system("cls");
                show_cursor();
                updateOption = pointer;
            }

            break;
        }

        if ((pressedKey == VK_RETURN))
            break;
    }

    if(updateOption == 5)
    {
    	pointer = 1;
    	pressedKey = 0;
    	while(1)
    	{
        	course_update_menu(pointer);
        	while(1)
        	{
            	pressedKey = getch();
            	if(pressedKey == 72)
            	{
                	pointer--;
                	if(pointer == 0)
                    	pointer = 6;

                	break;
            	}
            	else if(pressedKey == 80)
            	{
                	pointer++;
                	if(pointer == 7)
                    	pointer = 1;

                	break;
            	}
            	else if(pressedKey == VK_RETURN)
            	{
            		system("cls");
                	show_cursor();
                	updateOption += (pointer+1);
            	}

            	break;
        	}

        	if ((pressedKey == VK_RETURN))
            	break;
    	}
    }

	eStatus_t status = DB_updateStudent(rNumber, updateOption);

	if(status == DB_NOK)
		exit(0);

	if(status == DB_EMPTY)
	{
		printf("\n\n[ERROR] Database is empty.\n\n");
		return;
	}

	if(status == DB_NOT_FOUND)
	{
		printf("\n\n[INFO] Student has ID %u does not exist.\n\n", rNumber);
		return;
	}

	printf("\n\n[INFO] Student is updated Successfully.\n\n");
}

void show_s()
{
	eStatus_t status = DB_showAll();

	if(status == DB_NOK)
		exit(0);

	if(status == DB_EMPTY)
		printf("\n\n[INFO] Database is empty.\n\n");
}


void welcome_message()
{
    set_cursor_position(32, 8);
    print_line();

    set_cursor_position(32, 9), printf("Welcome to project * Student Database Based on Queue *");
    set_cursor_position(32, 11), printf("Author: Ahmed Mohammed Hussanein.");
    set_cursor_position(32, 13), printf("Under supervisor: Eng.Keroles Shenouda.");
    set_cursor_position(32, 15), printf("Press any key to continue...");

    set_cursor_position(32, 16);
    print_line();

    getch();
}


void choice( )
{
    uint8_t pointer = 1;
    uint8_t pressedKey = 0;

    while(1)
    {
        main_menu(pointer);
        while(1)
        {
            pressedKey = getch();
            if(pressedKey == 72)
            {
                pointer--;
                if(pointer == 0)
                    pointer = 10;

                break;
            }
            else if(pressedKey == 80)
            {
                pointer++;
                if(pointer == 11)
                    pointer = 1;

                break;
            }
            else if(pressedKey == VK_RETURN)
            {
            	system("cls");
                show_cursor();

                switch(pointer)
                {
                case 1:
                    add_student_manually();
                    break;

                case 2:
                    add_student_file();
                    break;

                case 3:
                    find_rl();
                    break;

                case 4:
                    find_fn();
                    break;

                case 5:
                    find_c();
                    break;

                case 6:
                    tot_s();
                    break;

                case 7:
                    del_s();
                    break;

                case 8:
                    up_s();
                    break;

                case 9:
                    show_s();
                    break;

                case 10:
                	delete_database();
                    exit(0);
                    break;
                }
                system("pause");
            }

            Sleep(100);
            break;
        }

        if ((pointer == 10) && (pressedKey == VK_RETURN))
            break;

    }
}

void main_menu(uint8_t pointing)
{
	system("cls");
    hide_cursor();

    set_cursor_position(32, 8);
    print_line();

    set_cursor_position(32, 9);  point_here(pointing, 0);  printf("What do you want to do?");
    set_cursor_position(32, 10); point_here(pointing, 1);  printf("1. Add Student Details Manually.");
    set_cursor_position(32, 11); point_here(pointing, 2);  printf("2. Add Student Details From Text File.");
    set_cursor_position(32, 12); point_here(pointing, 3);  printf("3. Find Student Details by Roll Number.");
    set_cursor_position(32, 13); point_here(pointing, 4);  printf("4. Find Student Details by First Name.");
    set_cursor_position(32, 14); point_here(pointing, 5);  printf("5. Find Student Details by Course ID.");
    set_cursor_position(32, 15); point_here(pointing, 6);  printf("6. Find Total Number Of Students.");
    set_cursor_position(32, 16); point_here(pointing, 7);  printf("7. Delete Student Details by Roll Number.");
    set_cursor_position(32, 17); point_here(pointing, 8);  printf("8. Update Student Details by Roll Number.");
    set_cursor_position(32, 18); point_here(pointing, 9);  printf("9. Show all Information.");
    set_cursor_position(32, 19); point_here(pointing, 10); printf("10. Exit.");

    point_here(pointing, 0);
    set_cursor_position(32, 20);
    print_line();
}

void update_menu(uint8_t pointing)
{
    system("cls");
    hide_cursor();

    set_cursor_position(32, 8);
    print_line();

    set_cursor_position(32, 9);  point_here(pointing, 0);  printf("What do you want to update?");
    set_cursor_position(32, 10); point_here(pointing, 1);  printf("1. First Name.");
    set_cursor_position(32, 11); point_here(pointing, 2);  printf("2. Last Name.");
    set_cursor_position(32, 12); point_here(pointing, 3);  printf("3. Roll Number.");
    set_cursor_position(32, 13); point_here(pointing, 4);  printf("4. GPA.");
    set_cursor_position(32, 14); point_here(pointing, 5);  printf("5. Courses.");
    set_cursor_position(32, 15); point_here(pointing, 6);  printf("6. ALL.");

    point_here(pointing, 0);
    set_cursor_position(32, 16);
    print_line();
}

void course_update_menu(uint8_t pointing)
{
	system("cls");
    hide_cursor();

    set_cursor_position(32, 8);
    print_line();

    set_cursor_position(32, 9);  point_here(pointing, 0);  printf("Which course do you want to update?");
    set_cursor_position(32, 10); point_here(pointing, 1);  printf("1. Course 1.");
    set_cursor_position(32, 11); point_here(pointing, 2);  printf("2. Course 2.");
    set_cursor_position(32, 12); point_here(pointing, 3);  printf("3. Course 3.");
    set_cursor_position(32, 13); point_here(pointing, 4);  printf("4. Course 4.");
    set_cursor_position(32, 14); point_here(pointing, 5);  printf("5. Course 5.");
    set_cursor_position(32, 15); point_here(pointing, 6);  printf("6. ALL.");

    point_here(pointing, 0);
    set_cursor_position(32, 16);
    print_line();
}
