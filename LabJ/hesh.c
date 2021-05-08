#include "hesh.h"

int HashFunc(hash_table_t* table, int value) {
	return abs(value) % table->size;
}
hash_table_t* CreateTable(int size) {
	hash_table_t* table = malloc(sizeof(hash_table_t));
	if (!table) {
		return NULL;
	}
	table->size = size;
	table->mesh = malloc(sizeof(cell_t*) * size);
	if (!table->mesh) {
		free(table);
		return NULL;
	}
	for (int i = 0; i != size; i++) {
		table->mesh[i] = NULL;
	}
	return table;
}
void DeleteTable(hash_table_t* table) {
	if (!table)
		return;
	for (int i = 0; i != table->size; i++) {
		cell_t* field = table->mesh[i];
		while (field) {
			cell_t* buf = field;
			field = field->next;
			free(buf);
		}
	}
	free(table->mesh);
	free(table);
}
bool CreateNewNode(cell_t** field) {
	*field = malloc(sizeof(cell_t));
	if (!*field) {
		return false;
	}
	(*field)->next = NULL;
	(*field)->value = 0;
	return true;
}
bool FindInTable(hash_table_t* table, int value) {
	int index = HashFunc(table, value);
	cell_t* buf = table->mesh[index];

	while (buf) {
		if (buf->value == value)
			return true;
		buf = buf->next;
	}
	return false;
}
void AddInTable(hash_table_t* table, int value) {
	if (FindInTable(table, value)) {
		return;
	}
	int index = HashFunc(table, value);
	cell_t** cell = &table->mesh[index];
	cell_t** nextcell = cell;

	if (!(*nextcell)) {
		if (!CreateNewNode(nextcell)) {
			return;
		}
		(*nextcell)->value = value;
	}
	else {
		while (*nextcell) {
			cell = nextcell;
			nextcell = &(*nextcell)->next;
		}
		if (!CreateNewNode(nextcell)) {
			return;
		}
		(*nextcell)->value = value;
		(*cell)->next = *nextcell;
	}
}
void DeleteFromTable(hash_table_t* table, int value) {
	if (!FindInTable(table, value)) {
		return;
	}
	int index = HashFunc(table, value);
	cell_t* cell = table->mesh[index];
	cell_t* prevcell = cell;

	if (cell->value == value) {
		table->mesh[index] = cell->next;
		free(cell);
	}
	else {
		while (cell) {
			if (cell->value == value) {
				prevcell->next = cell->next;
				free(cell);
				return;
			}
			prevcell = cell;
			cell = cell->next;
		}
	}
}
void ConsoleTable(hash_table_t** table) {
	char buffer = getchar();
	int value = 0;

	while (buffer != EOF) {
		scanf("%d", &value);
		if (buffer == 'a') {
			AddInTable(*table, value);
		}
		else if (buffer == 'r') {
			DeleteFromTable(*table, value);
		}
		else if (buffer == 'f') {
			if (FindInTable(*table, value)) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
		}
		else {
			printf("Incorrect input");
			return;
		}
		buffer = getchar();
		if (buffer == '\r' || buffer == '\n')
			buffer = getchar();
	}
}