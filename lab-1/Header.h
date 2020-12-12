
#ifndef HEADER_
#define HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable:4996)

#define NOT_ERRORS 0;
#define NOT_ENOUGH_MEMORY 1;
#define REPEAT_NUMBER 2;
#define ERROR_READ 3;


typedef struct list {
	char* word;
	int number;
	struct list* next;
}list;

//���������� ��� ������
static int error_my = NOT_ERRORS;
//���������� ��� ������ �������
//static int error_num = NUMBER_NOT_REPEAT;

//������ ����� �� �����, �������� �� ������ � ������ ���������� �������
void Read_in_list(list** head, FILE*f);
//��������� ����� �������
void Add_in_list(list** List, char* word, int number);
//��������� ������ ������� � ������
void Create_list(list** List, char* word, int number);
//���������� �-� ���������
list* get_Nth_list(list* List, int n);

//�������� �� ���������� �������
void Error_repeat_number(void);

//������� ��� ����� � ��������������� ���������� �����
void Words_on_the_screen(list* head);
//���� ����� � ������� ���� �� ��� ���
void Search_number(list* head);




//������ ����
void Clear_list(list** List);

#endif //HEADER_