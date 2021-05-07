#pragma once
#include <stdbool.h>

typedef unsigned int uint;

typedef struct node {
	struct node* next;
	int value;
} node_t;

typedef struct {
	node_t** table;
	uint size;
}hashTable_t;

bool FindInTable(hashTable_t* hashTable, int value);
void AddInTable(hashTable_t* hashTable, int value);
void RemoveFromTable(hashTable_t* hashTable, int value);
hashTable_t* CreateTable(uint size);
void DeleteTable(hashTable_t* hashTable);


