#pragma once
#include <stdio.h>
#define SIZE 30		// Размер строковых полей в структуре

// Структура с данными
struct Data {
	char str_field1[SIZE];
	char str_field2[SIZE];
	int int_field;		// По этому полю будет происходить сортировка списка.
};
struct Node {
	struct Data data;	// Поле с данными
	struct Node* next;			// Указатель на следующий элемент в списке
};
struct List {
	struct Node* first;
	int size;
};
struct Data GenerateOne(struct Data* prev);
void WriteToFile(FILE* f, int n);
void Add(struct List* list, struct Data* data);
struct Data Get(struct List* list, int number);
struct List Join(struct List* list1, struct List* list2);
