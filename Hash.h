#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)

#define SUCCESS 1
#define FAIL -1
#define SIZE 500

typedef enum {
    FREE,
    NOT_FREE,
    DELETED
}STATUS;

typedef struct {
    char* str;
    int status;
}Hash_t;

Hash_t* Create(int size);

 int Hash(char* str, int size);

void Insert(Hash_t* table, char* elem, int size);

int Find(Hash_t* table, char* elem, int size);

void Delete(Hash_t* table, char* elem, int size);

void Free(Hash_t* table, int size);
