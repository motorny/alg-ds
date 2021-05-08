#pragma once

#define MAX_SIZE 100000

typedef enum bool_t {
    FALSE,
    TRUE
}bool_t;

typedef struct node_t {
    int value;
    struct node_t* next;
} node_t;

typedef struct hashtable_t {
    unsigned int size;
    struct node_t** table;
} hashtable_t;

hashtable_t* CreateTable(int size);

bool_t CreateNewNode(node_t** field);

int HashFunc(hashtable_t* table, int value);

bool_t HashTableFind(hashtable_t* hashtable, int value);

void HashTableAdd(hashtable_t* table, int value);

void HashTableRemove(hashtable_t* table, int value);

void HashTableDestroy(hashtable_t* table);

void WhatToDo();