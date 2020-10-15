#pragma once
typedef struct list_p {
	int day;
	int month;
	int year;
	int T;
	struct list_p* next;
}list_p;


list_p* CreateList(FILE* f);

void Print(list_p* list);

int FindTemp(list_p* list, int t, int fl);

int WhatDay(char str[]);

int WhatMonth(char str[]);

int WhatYear(char str[]);

int WhatTemperature(char str[]);

list_p* Add(list_p* head, char str[], list_p* list);

list_p* Init(list_p* head, char str[]);

list_p* Destroy(list_p* head);

