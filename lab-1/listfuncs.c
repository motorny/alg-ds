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
	NODE* current_node = list->first;
	NODE* next_node;

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
	
	next_node = current_node->next;

	while (next_node != NULL) {
		if (add->temperature < next_node->temperature)
			break;
		if (add->temperature == next_node->temperature) {
			if (add->year < next_node->year)
				break;
			if (add->year == next_node->year) {
				if (add->month < next_node->month)
					break;
				if (add->month == next_node->month) {
					if (add->day < next_node->day)
						break;
					if (add->day == next_node->day)
						return;
				}
			}
		}
		current_node = next_node;
		next_node = next_node->next;
	}
	add->next = next_node;
	current_node->next = add;
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
