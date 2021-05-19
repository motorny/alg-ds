#pragma once

typedef struct node {
    int value;
    struct node* next;
} node;

typedef struct hashtable {
    unsigned int size;
    struct node** table;
} hashtable;

hashtable* CreateTable(int size);

int CreateNode(node** field);

void Add(hashtable* table, int value);

int Search(hashtable* hashtable, int value);

void Remove(hashtable* table, int value);

void DeleteAll(hashtable* table);
