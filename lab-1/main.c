#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include "ListBirthDay.h"
#pragma warning(disable:4996)

ListDays *g_days = NULL;

// Читаем по строчно
// В формате: Фамилия Имя Отчество дд/мм/гггг (Как прописано в задание)
ListDays *ReadFile(char *file_name) {
	char c, *fio;
	int i, n, numb;
	struct tm time_tm;
	time_t time;
	FILE *f = fopen(file_name, "r");
	fpos_t  fpos1, fpos2; // Позиция в файле
	ListDays *days = NULL;

	if ( ferror(f) || feof(f) ) {
		return NULL; 
	}
	fseek(f, SEEK_SET, 0);
	
	time_tm.tm_hour = 0;
	time_tm.tm_sec = 0;
	time_tm.tm_min = 0;
	time_tm.tm_isdst = -1;
	
	while ( !feof(f) && !ferror(f) ) {
		//// Выделяем ФИО
		// Считаем кол символова в ФИО
		fgetpos(f, &fpos1);
		i = 0;
		while ( (c = fgetc(f)) != '\n' ) {
			if ( c == ' ' ) i++;
			if ( i == 3 ) break;
		}
		fgetpos(f, &fpos2);
		n = (int)(fpos2 - fpos1);
		// Копируем ФИО
		fio = malloc(sizeof(char) * n);
		fsetpos(f, &fpos1);
		fgets(fio, n, f);
		fgetc(f);

		//// Выделяем Дату
		for ( numb = 0, i = 0; i < 2; i++ ) {
			c = fgetc(f);
			numb = numb * 10 + (int) (c - '0');
		}
		time_tm.tm_mday = numb;
		fgetc(f);
		for ( numb = 0, i = 0; i < 2; i++ ) {
			c = fgetc(f);
			numb = numb * 10 + (int) (c - '0');
		}
		time_tm.tm_mon = numb - 1;
		fgetc(f);
		for ( numb = 0, i = 0; i < 4; i++ ) {
			c = fgetc(f);
			numb = numb * 10 + (int) (c - '0');
		}
		time_tm.tm_year = numb - 1830;
		time = mktime(&time_tm);
		
		if ( time == -1 ){
			DestroyList(&days); // days = NULL;
			break;
		}
		//// Записываем ФИО и Дату в список
		AddDayToList(&days, time, fio);

		fgetc(f);
	}
	fclose(f);

	return days;
}

// Отображение всех др
void ShowAllDays(void) {
	struct tm *time_tm;
	ListDays *pDays = g_days;
	ListFIO *pName;
	
	printf("\n");
	while ( pDays != NULL ) {
		time_tm = localtime(&pDays->time);
		pName = pDays->fio;
		while ( pName != NULL ) {
			printf("%02i/%02i/%04i %s\n", time_tm->tm_mday, time_tm->tm_mon + 1, time_tm->tm_year + 1830, pName->fio);
			pName = pName->next;
		}
		pDays = pDays->next;
	}
	printf("\n");
}

// Отображение определенного дня
void ShowDay(void) {
	ListDays *day;
	ListFIO *name;

	struct tm time_tm;
	time_t time;
	int numb;
	
	time_tm.tm_hour = 0;
	time_tm.tm_sec = 0;
	time_tm.tm_min = 0;
	time_tm.tm_isdst = -1;

	printf("\n");

	printf("Введите день: ");
	scanf("%i", &numb);
	time_tm.tm_mday = numb;

	printf("Введите месяц: ");
	scanf("%i", &numb);
	time_tm.tm_mon = numb - 1;

	printf("Введите год: ");
	scanf("%i", &numb);
	time_tm.tm_year = numb - 1830;

	time = mktime(&time_tm);
	day = FindDay(time, g_days);

	printf("\n");
	if ( day == NULL ) {
		printf("В этот день никого нет в списке.\n");
	}
	else {
		name = day->fio;
		while ( name != NULL ) {
			printf("%s\n", name->fio);
			name = name->next;
		}
	}
	printf("\n");
}

// Отобраежение меню в консоль
int ShowMenu(void) {
	int i;
show:
	printf("Меню вывода др:\n");
	printf("1. Все дни\n");
	printf("2. Определённый день\n");
	printf("0. Выход\n");
	
	scanf("%i", &i);

	switch ( i ) {
	case 1:
		ShowAllDays();
		break;
	case 2:
		ShowDay();
		break;
	case 0:
		return 0;
	default:
		printf("Не верный пункт.\n");
		goto show;
	}

	return 1;
}

int main(void) {
	setlocale(LC_ALL, "RUS");

	g_days = ReadFile("file2.txt");
	if ( g_days == NULL )
		return 1;

	while ( ShowMenu() );

	DestroyList(&g_days);
	return 0;
}