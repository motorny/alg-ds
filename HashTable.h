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

typedef struct table_t {
	char* str;
	int state;
} table_t;


table_t* CreateHash();
int Add(table_t* table, char* str);
int Delete(table_t* table, char* str);
int Find(table_t* table, char* str);