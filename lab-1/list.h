#pragma once
#ifndef LIST_H_45612
#define LIST_H_45612

#define SUCCESS 1
#define ERROR 0

typedef struct {
  struct {
    int day;
    int month;
    int year;
  } date;
  double temperature;
} data_t;

typedef data_t T;

typedef struct node_t {
  T data;
  struct node_t* next;
} node_t;

typedef struct {
  node_t* head;
} list_t;

list_t* CreateList();
int AddToList(list_t* list, T* data, int (*compare)(const T*, const T*));
int DeleteList(list_t* list);


#endif // LIST_H_45612 included