#ifndef J20_H_INCLUDED__
#define J20_H_INCLUDED__

#pragma once

#define N 3

typedef struct list_t {
  char* str;
  struct list_t* next;
} list_t;

typedef struct htable_t {
  char* str;
  struct list_t* list;
  struct list_t* end;
  int num;
} htable_t;

int FindElem(htable_t ht[], char* str, int* destInd, list_t** destList);

void AddElem(htable_t ht[], char* strNew);

void DelElem(htable_t ht[], char* strDel);

void DestroyHTable(htable_t ht[]);

void Run(void);

#endif
