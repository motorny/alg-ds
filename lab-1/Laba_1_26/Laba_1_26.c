#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Header.h"
#pragma warning (disable: 4996)

enum flag {
	NO,
	OK,
	OK_2,
	OK_3
};

//Указатель на начало списка
list_p* head = NULL;

//Сортировка списка по температуре 
list_p* Sort(list_p* head) {
	int min = 0;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	list_p* currentlist = (list_p*)malloc(sizeof(list_p)), *newhead = (list_p*)malloc(sizeof(list_p)), * currentlist2 = (list_p*)malloc(sizeof(list_p)), * current = (list_p*)malloc(sizeof(list_p)), * nextfromcurrent = (list_p*)malloc(sizeof(list_p));
	if (list == NULL || currentlist2 == NULL|| current == NULL|| nextfromcurrent == NULL)
		return NULL;
	list = head;
	newhead = NULL;
	while (list != NULL) {
		//В начале каждого цикла принимаем за минимум текущую температуру и отталкиваемся от неё и проверяем следующий элемент
		min = list->T;
		currentlist = list;
		current = list;
		while (list->next != NULL) {
			currentlist2 = list;
			list = currentlist2->next;
			if (list->T > min) {
				min = list->T;
				currentlist = list;
				nextfromcurrent = currentlist2;
			}
			else if (list->T == min) {
				if (list->year > currentlist2->year) {
					min = list->T;
					currentlist = list;
					nextfromcurrent = currentlist2;
				}
				else if (list->year == currentlist2->year) {
					if (list->month > currentlist2->month) {
						min = list->T;
						currentlist = list;
						nextfromcurrent = currentlist2;
					}
					else	if (list->month == currentlist2->month) {
						if (list->day > currentlist2->day) {
							min = list->T;
							currentlist = list;
							nextfromcurrent = currentlist2;
						}
					}
				}
			}
		}
		//Данное условие нужно, если первый элемент и есть минимум
		if (current->T == min && currentlist == current) {
			head = current->next;
			current->next = newhead;
			newhead = current;
		}
		else {
			nextfromcurrent->next = currentlist->next;
			head = current;
			currentlist->next = newhead;
			newhead = currentlist;
		}
		list = head;
	}
	return newhead;
}

//Печать информации тех дней, температура которых меньше нуля
void Print(list_p* list) {
	enum flag n = NO;
	while (list != NULL) {
		if (list->T < 0) {
			if (list->day < 10)
				n = OK;
			if (list->month < 10)
				n = OK_2;
			if (list->day < 10 && list->month < 10)
				n = OK_3;
			if (n == NO)
				printf("%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (n == OK)
				printf("0%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (n == OK_2)
				printf("%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (n == OK_3)
				printf("0%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
			list = list->next;
		}
		else list = list->next;
	}
}

//Поиск заданной температуры в списке и вывод информации о ней, если она есть в списке
int FindTemp(list_p* list, int t, int fl) {
	enum flag n = NO, count = 0;
	while (list != NULL) {
		if (list->T == t) {
			if (fl != 0) {
				if (list->day < 10)
					n = OK;
				if (list->month < 10)
					n = OK_2;
				if (list->day < 10 && list->month < 10)
					n = OK_3;
				if (n == NO)
					printf("%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (n == OK)
					printf("0%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (n == OK_2)
					printf("%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (n == OK_3)
					printf("0%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
				count++;
			}
			else return t;
		}
		list = list->next;
		if (list == NULL && count == 0) {
			printf("Заданной температуры нет в списке\n");
			break;
		}
	}
	return -1;
}

//Конвертация символьного типа в численный
int WhatDay(char str[]) {
	int x, y;
	x = str[0] - 48;
	y = str[1] - 48;
	x = 10 * x + y;
	return x;
}

int WhatMonth(char str[]) {
	int x, y;
	x = str[3] - 48;
	y = str[4] - 48;
	x = 10 * x + y;
	return x;
}

int WhatYear(char str[]) {
	int x, y, z, h;
	x = str[6] - 48;
	y = str[7] - 48;
	z = str[8] - 48;
	h = str[9] - 48;
	x = 1000 * x + 100 * y + 10 * z + h;
	return x;
}

int WhatTemperature(char str[]) {
	int x = 0, y = 0, z = 0, flag = 0;
	if (str[11] == '-')
		flag = 1;
	x = str[12] - 48;
	y = str[13] - 48;
	z = str[14] - 48;
	if (str[13] == 10 || str[13] == '\0') {
		y = 0;
		return x;
	}
	if (str[14] == 10 || str[14] == '\0') {
		z = 0;
	}
	x = 10 * x + y + z;
	if (flag == 1)
		return -x;
	else
		return x;
}

//Добавление нового узла в список
list_p* Add(list_p* head, char str[]) {
	list_p* next = (list_p*)malloc(sizeof(list_p));
	if (next == NULL)
		return NULL;
	next->day = head->day;
	next->month = head->month;
	next->year = head->year;
	next->T = head->T;
	next->next = head;
	head = next;
	return head;
}

//Инициализация элемента списка по входящим данным
list_p* Init(list_p* head, char str[]) {
	head->day = WhatDay(str);
	head->month = WhatMonth(str);
	head->year = WhatYear(str);
	head->T = WhatTemperature(str);
	return head;
}

//Уничтожение списка
list_p* Destroy(list_p* head) {
	while (head != NULL) {
		list_p* p = head;
		head = head->next;
		free(p);
	}
	return head;
}


//Создание списка так, что после каждого добавления он остается отсортированным
list_p* CreateList(FILE* f) {
	list_p* list = (list_p*)malloc(sizeof(list_p));
	if (list == NULL)
		return NULL;
	char* a;
	char str[50];
	int n = 0;
	list->day = 0;
	list->month = 0;
	list->T = 0;
	list->year = 0;
	list->next = NULL;
	head = list;
	while (1) {
		n++;
		a = fgets(str, sizeof(str), f);
		if (a == NULL || a == "\n") {
			if (n == 1) {
				list = NULL;
				break;
			}
			else
				break;
		}
		head = Init(head, str);
		list = head;
		list = Sort(list);
		head = Add(list, str);
	}
	list = Sort(list);
	head = list;
	return head;
}

int main(void) {
	FILE* f;
	int t = 0, fl = 1;
	setlocale(LC_CTYPE, "russian");
	f = fopen("temp.txt", "r");
	if (f == NULL) {
		printf("Не удалось открыть файл");
		return -1;
	}
	head = CreateList(f);
	Print(head);
	printf("\n");
	printf("Введите температуру, которую хотите найти\n");
	scanf_s("%d", &t);
	printf("\nВот, что удалось найти:\n");
	if (head == NULL) {
		printf("Список пуст\n");
	}
	else
		fl = FindTemp(head, t, fl);
	head = Destroy(head);
	fclose(f);
	return 0;
}