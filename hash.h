#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#pragma warning (disable:4996)

typedef struct cell_t {
	int value;
	struct cell_t* next;
} cell_t;

typedef struct hash_table_t {
	int size;
	cell_t** mesh;
}hash_table_t;

int HashFunc(hash_table_t* table, int val);
hash_table_t* Create(int size);
void Destroy(hash_table_t* table);
int CreateNode(cell_t** node);
int Find(hash_table_t* table, int val);
void Add(hash_table_t* table, int val);
void Remove(hash_table_t* table, int val);
void ToDo(hash_table_t** table);