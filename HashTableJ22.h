#pragma once

typedef char* type;

typedef struct {
	type* data;
	int n;
} Hashtable;

Hashtable* Create(int n);

int Insert(Hashtable* t, const type key);

int Find(const Hashtable* t, const type key);

int Delete(Hashtable* t, const type key);

void Free(Hashtable* t);