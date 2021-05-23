#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable:4996)

#define TABLE_SIZE 100000
#define STR_SIZE 10
#define ISDIGIT(ch) (( (ch) >= '0' && (ch) <= '9')?1:0)

enum {
	NOT_FINISHED = 0,
	FINISHED,
	FREE,
	DELETED,
	NOTFREE,
};

typedef struct hashTable {
	char* str;
	int status;
} hashTable_t;


hashTable_t* CreateHashTable();
int AddStr(hashTable_t* table, char* str);
int DeleteStr(hashTable_t* table, char* str);
int FindStr(hashTable_t* table, char* str);
void DestroyTable(hashTable_t* hashTable);
