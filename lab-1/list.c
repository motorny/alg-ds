#include "list.h"
#include <stdlib.h>
#include <stdio.h>


list_t* CreateList() {
  list_t* newList = malloc(sizeof(list_t));
  if (!newList) {
    free(newList);
    return NULL;
  }
  newList->head = NULL;
  return newList;
}

int AddToList(list_t* list, T* data, int (*compare)(const T*, T*)) {
  node_t* p;
  node_t* next;
  node_t* new = malloc(sizeof(node_t));
  if (list == NULL || data == NULL || compare == NULL) {
    free(new);
    return ERROR;
  }

  p = list->head;

  if (!new) {
    free(new);
    return ERROR;
  }

  new->data = *data;

  if (list->head == NULL) {
    list->head = new;
    new->next = NULL;
    return SUCCESS;
  }

  if (compare(&list->head->data, data) > 0) {
    new->next = list->head;
    list->head = new;
    return SUCCESS;
  }

  next = p->next;
  while (next != NULL && compare(data, &next->data) > 0) {
    p = next;
    next = next->next;
  }
  new->next = next;
  p->next = new;
  return SUCCESS;
}

int DeleteList(list_t* list) {
  node_t* p;
  node_t* next;
  if (list == NULL) {
    return ERROR;
  }
  p = list->head;
  while (p != NULL) {
    next = p->next;
    free(p);
    p = next;
  }
  free(list);
  return SUCCESS;
}