#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct node_t
{
    struct node_t* next;
    int value;
} node;

typedef struct HashTable
{
    struct node_t** table;
    unsigned int size;
} *HashTable_ptr;

// Creating hash table
HashTable_ptr CreateHashTable(unsigned int size);
void DestroyHashTable(HashTable_ptr hashTable);

// Working with hash table
void HashTableAdd(HashTable_ptr hashTable, int value);
void HashTableRemove(HashTable_ptr hashTable, int value);
bool HashTableFind(HashTable_ptr hashTable, int value);
void HashTablePrint(HashTable_ptr hashTable);

#endif // HASHTABLE_H
