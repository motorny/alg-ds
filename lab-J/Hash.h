#pragma once
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define FOUND 0
#define NOT_FOUND 1

typedef enum STATUS
{
	FREE,
	NOT_FREE,
	DELETED
} Status;

typedef struct CELL
{
	char* str;
	Status status;
} Cell;

typedef struct HASH_TABLE
{
	Cell* data;
	int size;
} HashTable;

HashTable* createHashTable(int size);
void add(HashTable* table, char* str);
void del(HashTable* table, char* str);
int find(HashTable* table, char* str);