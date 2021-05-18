
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

//переменна€ дл€ ошибок
static int error_my = NOT_ERRORS;
//переменна€ дл€ сверки номеров
//static int error_num = NUMBER_NOT_REPEAT;

//читает слова из файла, сообщить об ошибке в случае одинаковых номеров
void Read_in_list(list** head, FILE*f);
//добавл€ет новый элемент
void Add_in_list(list** List, char* word, int number);
//добавл€ет первый элемент в список
void Create_list(list** List, char* word, int number);
//возвращает н-й указатель
list* get_Nth_list(list* List, int n);

//ѕроверка на повторение номеров
void Error_repeat_number(void);

//выводит все слова с соответсвующими номерамина экран
void Words_on_the_screen(list* head);
//»щет номер и выводит есть он или нет
void Search_number(list* head);




//чистит лист
void Clear_list(list** List);

#endif //HEADER_