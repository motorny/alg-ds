#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

typedef enum {
	NOT_INTENTED = 0,
	NOT_FREE,
	FREE
}codes;

typedef struct Htable {
	char str[100];
	unsigned size;
	codes status;  
}Htable;

int Init(Htable** ht, int htSize);

int AddTable(Htable* ht, char* str);
int FindTable(Htable* ht, char* str);
int RemoveTable(Htable* ht, char* str);

int DeleteTable(Htable** ht);
