#pragma once
#ifndef HASH_TABLE_INCLUDED
#define HASH_TABLE_INCLUDED

#define SUCCESS 1
#define FAIL 0

typedef char* table;

typedef struct {
	table* data;
	int size;
} hash_t;

hash_t* HashCreate(int size);

int Hash(table key, int m);

int HashInsert(hash_t* t, const table key);

int HashSearch(const hash_t* t, const table key);

int HashDelete(hash_t* t, const table key);

void HashFree(hash_t* t);

#endif 