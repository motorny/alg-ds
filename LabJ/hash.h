#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)
#define FREE 2
#define DELETED 3
#define NOTFREE 4
#define SIZE 10000

#define TRUE 1
#define FALSE 0

typedef struct hashTable {
	char* str;
	int status;
} hashTable_t;


hashTable_t* CreateHashT();
int Add(hashTable_t* table, char* str);
int Delete(hashTable_t* table, char* str);
int Find(hashTable_t* table, char* str);