#include "header.h"

LIST* InitList(void) {
	LIST* list = (LIST*)malloc(sizeof(LIST));
	list->first = NULL;
	return list;
}

void ReadFile(FILE* f, LIST* list) {
	int dd, mm, yy, temp;
	while (!feof(f)) {
		fscanf_s(f, "%d.%d.%d %d degrees of Cel.", &dd, &mm, &yy, &temp);
		AddToList(list, dd, mm, yy, temp);
	}
}

void AddToList(LIST* list, int dd, int mm, int yy, int temp) {
	NODE* add = (NODE*)malloc(sizeof(NODE));
	NODE* current1 = list->first;
	NODE* current2;

	if (add == NULL) {
		puts("Addition error");
		return;
	}

	add->day = dd;
	add->month = mm;
	add->year = yy;
	add->temperature = temp;

	if (list->first == NULL) {
		list->first = add;
		list->first->next = NULL;
		return;
	}

	if (add->temperature < list->first->temperature) {
		add->next = list->first;
		list->first = add;
		return;
	}
	if (add->temperature == list->first->temperature) {
		if (add->year < list->first->year) {
			add->next = list->first;
			list->first = add;
			return;
		}
		if (add->year == list->first->year) {
			if (add->month < list->first->month) {
				add->next = list->first;
				list->first = add;
				return;
			}
			if (add->month == add->month) {
				if (add->day < list->first->day) {
					add->next = list->first;
					list->first = add;
					return;
				}
			}
		}
	}
	
	current2 = current1->next;

	while (current2 != NULL) {
		if (add->temperature < current2->temperature)
			break;
		if (add->temperature == current2->temperature) {
			if (add->year < current2->year)
				break;
			if (add->year == current2->year) {
				if (add->month < current2->month)
					break;
				if (add->month == current2->month) {
					if (add->day < current2->day)
						break;
					if (add->day == current2->day)
						return;
				}
			}
		}
		current1 = current2;
		current2 = current2->next;
	}
	add->next = current2;
	current1->next = add;
	return;
}

void Print(LIST* list) {
	NODE* current = list->first;
	while (current != NULL) {
		if (current->temperature < 0)
			printf("%d.%d.%d %d degrees of Cel.\n", current->day, current->month, current->year, current->temperature);
		current = current->next;
	}
}

int Search(LIST* list, int temp) {
	NODE* current;
	int count = 0;
	current = list->first;
	while (current != NULL) {
		if (current->temperature == temp)
			count++;
		current = current->next;
	}
	return count;
}

void FreeList(LIST* list) {
	NODE* current = list->first;
	NODE* buffer;
	while (current != NULL) {
		buffer = current->next;
		free(current);
		current = buffer;
	}
	free(list);
}
