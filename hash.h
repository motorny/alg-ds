#ifndef HASH_H_INCLUDED__
#define HASH_H_INCLUDED__
#pragma once

#include<stdio.h>
#include<stdlib.h>

#define FOUND 1
#define NOTFOUND -1
#define DELETED 2
#define NOTFREE 3
#define FREE 4

//hash table
typedef struct hashTable {
  char* str;
  int status;
} hashTable_t;

hashTable_t* hashCreate(int size);
void hashInsert(hashTable_t* hashTable, char* elem, int size);
int hashFind(hashTable_t* hashTable, char* elem, int size);
void hashDelete(hashTable_t* hashTable, char* elem, int size);
void hashDestroy(hashTable_t* hashTable, int size);

#endif