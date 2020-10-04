#include "ListBirthDay.h"
#include <stdlib.h>
#include <malloc.h>


// Добавляет дату с фио в список
int AddDayToList(ListDays **q, time_t time, char *fio)
{
	ListDays *p1 = NULL, *p2 = *q;
	ListFIO *name;

	if ( time == -1 || fio == NULL )
		return ERROR;

	while ( p2 != NULL ) {
		if ( p2->time >= time )
			break;
		else {
			p1 = p2;
			p2 = p2->next;
		}
	}

	if ( p1 != NULL ) {
		if ( p2 == NULL ) { // Если нет подходящей даты, но при этом в конце списка
			p2 = (ListDays *) malloc(sizeof(ListDays));
			if ( p2 == NULL ) return ERROR;

			p2->fio = NULL;
			p2->time = time;
			p2->next = NULL;
			p1->next = p2;
		}
		else if ( p2->time > time ) { // Если нет подходящей даты
			p2 = (ListDays *) malloc(sizeof(ListDays));
			if ( p2 == NULL ) return ERROR;

			p2->fio = NULL;
			p2->time = time;
			p2->next = p1->next;
			p1->next = p2;
		}
		// Иначе есть дата
	}
	else { // Если нет подходящей даты, но в начале списка
		(*q) = (ListDays *) malloc(sizeof(ListDays));
		if ( (*q) == NULL ) return ERROR;

		(*q)->next = p2;
		p1 = p2 = *q;
		p2->fio = NULL;
		p2->time = time;
	}

	// Добавляем ФИО
	name = (ListFIO *) malloc(sizeof(ListFIO));
	if ( name == NULL ) {
		if ( p2->fio == NULL ) {
			p1->next = p2->next;
			free(p2);
		}
		return ERROR;
	}

	name->fio = fio;
	name->next = p2->fio;
	p2->fio = name;
	
	return SUCCESS;
}

//Находит нужный день
ListDays *FindDay(time_t time, ListDays *q) {
	ListDays *p = q;

	if ( time == -1 )
		return NULL;

	while ( p != NULL ) {
		if ( p->time == time )
			break;
		else
			p = p->next;
	}
	return p;
}

// Уничтожает список
void DestroyList(ListDays **q) {
	ListDays *pDays2, *pDays1 = *q;
	ListFIO *pName1, *pName2;
	*q = NULL;

	while ( pDays1 != NULL ) {
		pName1 = pDays1->fio;
		while ( pName1 != NULL ) {
			pName2 = pName1;
			pName1 = pName1->next;
			free(pName2->fio);
			free(pName2);
		}
		pDays2 = pDays1;
		pDays1 = pDays1->next;
		free(pDays2);
	}
}