#pragma once

typedef char* type;

typedef struct {
  type* data;
  int n;
} hash_t;

hash_t* Create(int n);

int Insert(hash_t* t, const type key);

int Find(const hash_t* t, const type key);

int Delete(hash_t* t, const type key);

void Free(hash_t* t);