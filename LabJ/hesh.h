#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#pragma warning (disable:4996)

typedef struct cell_t {
	struct cell_t* next;
	int value;
} cell_t;
typedef struct hash_table_t {
	cell_t** mesh;
	int size;
}hash_table_t;

int HashFunc(hash_table_t* table, int value);
hash_table_t* CreateTable(int size);
void DeleteTable(hash_table_t* table);
bool CreateNewNode(cell_t** field);
bool FindInTable(hash_table_t* table, int value);
void AddInTable(hash_table_t* table, int value);
void DeleteFromTable(hash_table_t* table, int value);
void ConsoleTable(hash_table_t** table);