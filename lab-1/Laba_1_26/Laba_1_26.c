#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Header.h"
#pragma warning (disable: 4996)

enum flag {
	START,
	FORMATPRINTTEMP,
	FORMATPRINTMONTH,
	FORMATPRINTTEMPMONTH
};

//Указатель на начало списка
list_p* head = NULL;


//Печать информации тех дней, температура которых меньше нуля
void Print(list_p* list) {
	enum flag n = START;
	while (list != NULL) {
		if (list->T < 0) {
			if (list->day < 10)
				n = FORMATPRINTTEMP;
			if (list->month < 10)
				n = FORMATPRINTMONTH;
			if (list->day < 10 && list->month < 10)
				n = FORMATPRINTTEMPMONTH;
			if (n == START)
				printf("%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (n == FORMATPRINTTEMP)
				printf("0%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (n == FORMATPRINTMONTH)
				printf("%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
			if (n == FORMATPRINTTEMPMONTH)
				printf("0%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
			list = list->next;
		}
		else list = list->next;
	}
}

//Поиск заданной температуры в списке и вывод информации о ней, если она есть в списке
int FindTemp(list_p* list, int t, int fl) {
	enum flag n = START, count = 0;
	while (list != NULL) {
		if (list->T == t) {
			if (fl != 0) {
				if (list->day < 10)
					n = FORMATPRINTTEMP;
				if (list->month < 10)
					n = FORMATPRINTMONTH;
				if (list->day < 10 && list->month < 10)
					n = FORMATPRINTTEMPMONTH;
				if (n == START)
					printf("%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (n == FORMATPRINTTEMP)
					printf("0%d.%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (n == FORMATPRINTMONTH)
					printf("%d.0%d.%d  %d\n", list->day, list->month, list->year, list->T);
				if (n == FORMATPRINTTEMPMONTH)
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

//Добавление нового узла в список так, чтобы он сразу вставал на нужное место
list_p* Add(list_p* head, char str[], list_p* list) {
	list_p* current = (list_p*)malloc(sizeof(list_p)), * newhead = (list_p*)malloc(sizeof(list_p)), * startlist = (list_p*)malloc(sizeof(list_p)), * listprev = (list_p*)malloc(sizeof(list_p));
	list = head;
	int isinsertion = 0, count = 0, max = 0;
	newhead = NULL;
	list_p* add = (list_p*)malloc(sizeof(list_p));
	if (str[0] == '\n')
		return list;
	if (add == NULL)
		return NULL;
	add = Init(add, str);
	current = head;
	if (head == NULL) {
		add->next = head;
		list = add;
		return list;
	}

	else
	{

		while (list != NULL) {
			if (add == NULL)
				max = list->T;
			else
				max = add->T;
			current = list;
			startlist = list;
			listprev = list;
			while (list != NULL) {

				if (list->T > max) {
					max = list->T;
					current = list;

				}

				if (list->T == max && add == NULL) {
					if (list->year > listprev->year) {
						max = list->T;
						current = list;

					}
					else if (list->year == listprev->year) {
						if (list->month > listprev->month) {
							max = list->T;
							current = list;

						}
						else	if (list->month == listprev->month) {
							if (list->day > listprev->day) {
								max = list->T;
								current = list;

							}
						}
					}
				}

				else if (list->T == max && add != NULL) {
					if (list->year > add->year) {
						max = list->T;
						current = list;
						isinsertion++;
					}
					else if (list->year == add->year) {
						if (list->month > add->month) {
							max = list->T;
							current = list;
							isinsertion++;
						}
						else	if (list->month == add->month) {
							if (list->day > add->day) {
								max = list->T;
								current = list;
								isinsertion++;
							}
						}
					}
				}
				if (list->next != NULL)
					listprev = list;
				list = list->next;
			}



			if (count == 0) {
				if (add->T == max && isinsertion == 0) {
					add->next = newhead;
					newhead = add;
					head = startlist;
					add = NULL;
					count++;
				}
			}

			if (startlist->T == max && current == startlist) {
				head = startlist->next;
				startlist->next = newhead;
				newhead = startlist;
			}
			else if (startlist->T != max && current != startlist) {
				listprev->next = current->next;
				head = startlist;
				current->next = newhead;
				newhead = current;
			}
			list = head;
			isinsertion = 0;
		}
		if (newhead->next == NULL) {
			add->next = newhead;
			newhead = add;
		}
		return newhead;

	}
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
	char* a;
	char str[50];
	int n = 0;
	list->day = 0;
	list->month = 0;
	list->T = 0;
	list->year = 0;
	list->next = NULL;
	head = NULL;
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
		list = Add(head, str, list);
		head = list;
	}
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