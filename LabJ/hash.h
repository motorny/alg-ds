#pragma once

#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#define SUCCESS 1
#define FAIL 0

typedef char* T;

typedef struct {
  T* data;
  int size;
} hash_table_t;

hash_table_t* HashCreate(int size);
int HashInsert(hash_table_t* t, const T key);
int HashSearch(const hash_table_t* t, const T key);
int HashDelete(hash_table_t* t, const T key);
void HashFree(hash_table_t* t);

#endif // TABLE_H_INCLUDED
