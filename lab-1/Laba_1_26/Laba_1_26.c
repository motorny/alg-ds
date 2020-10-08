#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Header.h"
#pragma warning (disable: 4996)

list_p* head = NULL;

list_p* Sort(list_p* head) {
	int min = 0;
	list_p* list = (list_p*)malloc(sizeof(list_p));
	list_p* tmp = (list_p*)malloc(sizeof(list_p)), * newhead = (list_p*)malloc(sizeof(list_p)), * tmp2 = (list_p*)malloc(sizeof(list_p)), * tmp3 = (list_p*)malloc(sizeof(list_p)), * tmp4 = (list_p*)malloc(sizeof(list_p));
	list = head;
	newhead = NULL;
	while (list != NULL) {
		min = list->T;
		tmp = list;
		tmp3 = list;
		while (list->next != NULL) {
			tmp2 = list;
			list = tmp2->next;
			if (list->T > min) {
				min = list->T;
				tmp = list;
				tmp4 = tmp2;
			}
			else if (list->T == min) {
				if (list->year > tmp2->year) {
					min = list->T;
					tmp = list;
					tmp4 = tmp2;
				}
				else if (list->year == tmp2->year) {
					if (list->month > tmp2->month) {
						min = list->T;
						tmp = list;
						tmp4 = tmp2;
					}
					else	if (list->month == tmp2->month) {
						if (list->day > tmp2->day) {
							min = list->T;
							tmp = list;
							tmp4 = tmp2;
						}
					}
				}
			}
		}
		if (tmp3->T == min && tmp == tmp3) {
			head = tmp3->next;
			tmp3->next = newhead;
			newhead = tmp3;
		}
		else {
			tmp4->next = tmp->next;
			head = tmp3;
			tmp->next = newhead;
			newhead = tmp;
		}
		list = head;
	}
	return newhead;
}

void Print(list_p* list) {
	int flag = 0;
	while (list != NULL) {
		if (list->T < 0) {
			if (list->day < 10)
				flag = 1;
			if (list->month < 10)
				flag = 2;
			if (list->day < 10 && list->month < 10)
				flag = 3;
			if (flag == 0)
				printf("%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (flag == 1)
				printf("0%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (flag == 2)
				printf("%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (flag == 3)
				printf("0%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
			list = list->next;
			flag = 0;
		}
		else list = list->next;
	}
}

int FindTemp(list_p* list, int t, int fl) {
	int flag = 0, count = 0;
	while (list != NULL) {
		if (list->T == t) {
			if (fl != 0) {
				if (list->day < 10)
					flag = 1;
				if (list->month < 10)
					flag = 2;
				if (list->day < 10 && list->month < 10)
					flag = 3;
				if (flag == 0)
					printf("%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (flag == 1)
					printf("0%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (flag == 2)
					printf("%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (flag == 3)
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
		flag = 0;
	}
	return -1;
}

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

list_p* Add(list_p* head, char str[]) {
	list_p* tmp = (list_p*)malloc(sizeof(list_p));
	if (tmp == NULL)
		return NULL;
	tmp->day = head->day;
	tmp->month = head->month;
	tmp->year = head->year;
	tmp->T = head->T;
	tmp->next = head;
	head = tmp;
	return head;
}

list_p* Init(list_p* head, char str[]) {
	head->day = WhatDay(str);
	head->month = WhatMonth(str);
	head->year = WhatYear(str);
	head->T = WhatTemperature(str);
	return head;
}

list_p* Destroy(list_p* head) {
	while (head != NULL) {
		list_p* p = head;
		head = head->next;
		free(p);
	}
	return head;
}

list_p* CreateList(FILE* f) {
	list_p* list = (list_p*)malloc(sizeof(list_p));
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
		head = Add(head, str);
	}
	head = list;
	return head;
}

//int main(void) {
//	FILE* f;
//	int t = 0, fl = 0;
//	setlocale(LC_CTYPE, "russian");
//	f = fopen("temp.txt", "r");
//	if (f == NULL) {
//		printf("Не удалось открыть файл");
//		return -1;
//	}
//	head = CreateList(f);
//	head = Sort(head);
//	Print(head);
//	printf("\n");
//	printf("Введите температуру, которую хотите найти\n");
//	scanf_s("%d", &t);
//	printf("\nВот, что удалось найти:\n");
//	if (head == NULL) {
//		printf("Список пуст\n");
//	}
//	else
//		fl = FindTemp(head, t, fl);
//	head = Destroy(head);
//	fclose(f);
//	return 0;
//}