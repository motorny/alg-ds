#include "hash.h"

int HashFunc(hash_table_t* table, int val) {
	return abs(val) % table->size;
}

hash_table_t* Create(int size) {
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

void Destroy(hash_table_t* table) {
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

int CreateNode(cell_t** node) {
	*node = malloc(sizeof(cell_t));
	if (!*node) {
		return 0;
	}
	(*node)->next = NULL;
	(*node)->value = 0;
	return 1;
}

int Find(hash_table_t* table, int val) {
	int index = HashFunc(table, val);
	cell_t* buf = table->mesh[index];

	while (buf) {
		if (buf->value == val)
			return 1;
		buf = buf->next;
	}
	return 0;
}

void Add(hash_table_t* table, int val) {
	if (Find(table, val)) 
		return;

	int index = HashFunc(table, val);
	cell_t** cell = &table->mesh[index];
	cell_t** nextcell = cell;

	if (!(*nextcell)) {
		if (!CreateNode(nextcell)) 
			return;
		(*nextcell)->value = val;
	}
	else {
		while (*nextcell) {
			cell = nextcell;
			nextcell = &(*nextcell)->next;
		}
		if (!CreateNode(nextcell)) 
			return;
		(*nextcell)->value = val;
		(*cell)->next = *nextcell;
	}
}
void Remove(hash_table_t* table, int val) {
	if (!Find(table, val)) 
		return;
	
	int index = HashFunc(table, val);
	cell_t* cell = table->mesh[index];
	cell_t* prevcell = cell;

	if (cell->value == val) {
		table->mesh[index] = cell->next;
		free(cell);
	}
	else {
		while (cell) {
			if (cell->value == val) {
				prevcell->next = cell->next;
				free(cell);
				return;
			}
			prevcell = cell;
			cell = cell->next;
		}
	}
}
void ToDo(hash_table_t** table) {
	char sym;
	int val;

	while ((sym = getchar())!= EOF) {
		scanf("%d", &val);
		if (sym == 'a') 
			Add(*table, val);
		
		else if (sym == 'r') 
			Remove(*table, val);
		
		else if (sym == 'f') {
			if (Find(*table, val)) 
				printf("yes\n");
			
			else 
				printf("no\n");
			
		}
		else 
			return;
		getchar();
	}
}

int main() {
	int size = 10000;
	hash_table_t* table = Create(size);
	ToDo(&table);
	return 0;
}