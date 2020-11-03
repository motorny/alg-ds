#include "concat_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)


// Функция, пищущая в конец списка.
void Push(char* string, list_t* list, error_t* err) {

	// Если список пустой, то выделяем память под первый элемент
	// и ставим на него оба указателя head и tail.
	if (list->tail == NULL) {
		list->tail = (node_t*)malloc(sizeof(node_t));
		if (list->tail) {
			list->head = list->tail;
			list->tail->data = string;
			list->tail->next = NULL;
		}
		else
			*err = NO_MEMORY_ERROR;
	}
	// Если список не пустой, то выделяем память на новый элемент.
	// Сдвигаем tail.
	else {
		list->tail->next = (node_t*)malloc(sizeof(node_t));
		if (list->tail->next) {
			list->tail = list->tail->next;
			list->tail->data = string;
			list->tail->next = NULL;
		}
		else
			*err = NO_MEMORY_ERROR;
	}
	// Если память выделилась, то записываем в хвост данные
	// и присваиваем последнему указателю NULL.
}

// Функция, возвращающая указатель на строку.
// len - длина строки, не учитывает символ завершения.
char* ReadStr(FILE* stream, error_t* err) {
	int i = 0, maxSize = 25, length = 0, mult = 1, a = 0;
	char sym = 0;
	char* string = NULL;
	char* reserve = NULL;
	string = (char*)malloc(maxSize * sizeof(char));
	if (string == NULL) {
		*err = NO_MEMORY_ERROR;
		return NULL;
	}
	else {
		fgets(string, maxSize * mult * sizeof(char), stream);
		if (string[0] == '0') {
			*err = END_OF_STREAM;
			free(string);
			return NULL;
		}
		//	a = fscanf(stream, "%s", string);
		length = strlen(string);

		while (length >= ((maxSize * mult) - 1)) {
			mult++;
			reserve = (char*)realloc(string, sizeof(char) * maxSize * mult);
			if (reserve == NULL) {
				free(string);
				*err = NO_MEMORY_ERROR;
				return NULL;
			}
			else {
				string = reserve;
				//		fseek(stream, (maxSize * (mult - 1) * (-1)), SEEK_CUR);
				printf("Ooops, something went wrong, please, enter your string again!\n");
				fgets(string, maxSize * mult * sizeof(char), stream);

				length = strlen(string);
			}
		}

		return string;
	}
}

// Функция, которая формирует список.
void CreateList(list_t* list, int* len, error_t* err) {
	int lengthOfString = 0;
	//int* length = &lengthOfString;
	char* string = NULL;

	while (1) {
		string = ReadStr(stdin, err);

		if (*err != NO_ERRORS)
			break;

		lengthOfString = strlen(string);
		*len = *len + (lengthOfString);
		Push(string, list, err);
		if (*err != NO_ERRORS)
			break;
	}
}

void DestoyList(list_t* list, error_t* err) {
	node_t* reserve = list->head;
	if (list->head == NULL) {
		*err = EMPTY_LIST_ERROR;
	}
	else {
		while (reserve->next) {
			list->head = reserve->next;
			free(reserve->data);
			free(reserve);
			reserve = list->head;
		}
		free(reserve->data);
		free(reserve);
	}
}

// Функция, объединяющая строки в одну.
char* Concat(list_t* list, int* len, error_t* err) {
	if (*len == 0) {
		*err = EMPTY_LIST_ERROR;
		return NULL;
	}

	char* result = (char*)malloc((*len + 1) * sizeof(char));
	if (result == NULL) {
		*err = NO_MEMORY_ERROR;
		return NULL;
	}

	node_t* reserve = list->head;
	int num = 0;
	int counter = 0;

	while (reserve->next) {
		num = strlen(reserve->data) - 1;
		memcpy((result + counter), reserve->data, num);
		counter = counter + num;
		reserve = reserve->next;
	}
	num = strlen(reserve->data) - 1;
	memcpy((result + counter), reserve->data, num);
	result[counter + num] = '\0';

	return result;
}

void PrintError(error_t* err) {
	if (*err == NO_MEMORY_ERROR)
		printf("No memory!\n");
	else if (*err == EMPTY_LIST_ERROR)
		printf("The list is empty!\n");
	else
		printf("No errors found!\n");
}
