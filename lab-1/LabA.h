#pragma once

#define N 100

int count;

typedef struct list_t {
  char str[N];
  struct list_t* prev;
} list_t;

void AddList(list_t* start, list_t* NEW);

int ReadList(list_t* start);

list_t* SortTwo(list_t* elem);

void PrintList(list_t* el);

int SortList(list_t* start);
