#pragma once

#include <stdint.h>

typedef struct _HashTable_t HashTable_t;

HashTable_t* HashTableGet(uint32_t size, uint32_t mod);

void HashTableFree(HashTable_t* table);

int HashTableFind(HashTable_t* table, char* key, void** value_p);

int HashTableAdd(HashTable_t* table, char* key, void* value);

int HashTableRemove(HashTable_t* table, char* key, void** value_p);