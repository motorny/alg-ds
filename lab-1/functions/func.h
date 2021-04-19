#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
  char* data;
  struct node_t* next;
}node_t;

typedef struct {
  node_t* head;
}list_t;

int Mystrlen(char* str);
int LengthOfList(list_t* list);
char* ListToArray(list_t* list);

#endif /* FUNC_H */