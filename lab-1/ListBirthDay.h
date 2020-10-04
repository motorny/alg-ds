#pragma once
#ifndef LISTBIRTHDAY_H_
#define LISTBIRTHDAY_H_

#include <time.h>

#define SUCCESS 0
#define ERROR 1

typedef struct ListFIO {
	char *fio; // ФИО - Фамилия Имя Отчество
	struct ListFIO *next;
}ListFIO;

typedef struct ListDays {
	time_t time;  // Дата Рождения
	ListFIO *fio; // ФИО - Фамилия Имя Отчество
	struct ListDays *next;
}ListDays;

// Добавляет дату с фио в список
// **q - указатель на начало списка
// time - дата в формате UNIX
// *fio - указатель на ФИО
int AddDayToList(ListDays **q, time_t time, char *fio);

// Находит нужный день
// time - дата в формате UNIX
// *q - указатель на начало списка
ListDays *FindDay(time_t time, ListDays *q);

// Уничтожает список
void DestroyList(ListDays **q);

#endif // ! LISTBIRTHDAY_H_
