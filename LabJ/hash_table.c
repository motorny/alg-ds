#include"hash_table.h"
#include<math.h>
#include<stdlib.h>

static uint HashFunc(hashTable_t* hashTable, int value);
static bool CreateNewNode(node_t** field);

void AddInTable(hashTable_t* hashTable, int value) {
	if (FindInTable(hashTable, value))
		return;
	uint index = HashFunc(hashTable, value);
	node_t** field = &hashTable->table[index];
	node_t** nextField = field;

	if (!*nextField) {
		if (!CreateNewNode(nextField))
			return;
		(*nextField)->value = value;
	}
	else {
		while (*nextField) {
			field = nextField;
			nextField = &(*nextField)->next;
		}
		if (!CreateNewNode(nextField)) 
			return;
		(*nextField)->value = value;
		(*field)->next = *nextField;
	}

}

bool FindInTable(hashTable_t* hashTable, int value) {
	uint index = HashFunc(hashTable, value);
	node_t* toCompare = hashTable->table[index];

	while (toCompare) {
		if (toCompare->value == value)
			return true;
		toCompare = toCompare->next;
	}
	return false;
}

void RemoveFromTable(hashTable_t* hashTable, int value) {
	if (!FindInTable(hashTable, value))
		return;
	uint index = HashFunc(hashTable, value);
	node_t* field = hashTable->table[index];
	node_t* prevField = field;

	if (field->value == value) {
		//Case when we should delete first el of chain
		hashTable->table[index] = field->next;
		free(field);
	}
	else {
		while (field) {
			if (field->value == value) {
				prevField->next = field->next;
				free(field);
				return;
			}
			prevField = field;
			field = field->next;
		}
	}
}

hashTable_t* CreateTable(uint size) {
	hashTable_t* hashTable = malloc(sizeof(hashTable_t));
	if (!hashTable)
		return NULL;

	hashTable->size = size;

	hashTable->table = malloc(sizeof(node_t*) * size);
	if (!hashTable->table) {
		free(hashTable);
		return NULL;
	}
	for (uint i = 0; i != size; i++)
		hashTable->table[i] = NULL;

	return hashTable;
}

void DeleteTable(hashTable_t* hashTable) {
	if (!hashTable)
		return;
	for (uint i = 0; i != hashTable->size; i++) {
		node_t* field = hashTable->table[i];
		while (field) {
			node_t* toDel = field;
			field = field->next;
			free(toDel);
		}
	}
	free(hashTable->table);
	free(hashTable);
}

static uint HashFunc(hashTable_t* hashTable, int value) {
	return abs(value) % hashTable->size;
}

static bool CreateNewNode(node_t** field) {
	*field = malloc(sizeof(node_t));
	if (!*field)
		return false;
	(*field)->next = NULL;
	(*field)->value = 0;
	return true;
}
