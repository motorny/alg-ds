#include "func.h"

int Mystrlen(char* str) {
  return strlen(str);
}

int LengthOfList(list_t* list) {
  int length = 0;
  node_t* counter = (node_t*)malloc(sizeof(node_t));

  if (list->head == NULL)
    return 0;

  counter = list->head;
  while (counter->next) {
    length += Mystrlen(counter->data);
    counter = counter->next;
  }
  length += Mystrlen(counter->data);

  return ++length;  //because of "/0"
}

char* ListToArray(list_t* list) {
  int len = LengthOfList(list);
  if (len == 0)
    return NULL;

  char* arr = (char*)malloc(len * sizeof(char));
  if (arr == NULL) 
    return NULL;

  int i = 0;
  int numbyt = 0;

  node_t* counter = (node_t*)malloc(sizeof(node_t));
  counter = list->head;

  while (counter->next) {
    numbyt = Mystrlen(counter->data);
    memcpy((arr + i), counter->data, numbyt);
    i += numbyt;
    counter = counter->next;
  }
  numbyt = Mystrlen(counter->data);
  memcpy((arr + i), counter->data, numbyt);
  arr[i + numbyt] = '\0';

  return arr;
}