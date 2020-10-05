#include "DLL.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
 
 #pragma warning(disable:4996)


list_t* createList() {
  list_t *tmp = (list_t*)malloc(sizeof(list_t));
  tmp->head = tmp->tail = NULL;
  return tmp;
}

void deleteList(list_t** list) {
  node_t* tmp = (*list)->head;
  node_t* next = NULL;
  while (tmp) {
    next = tmp->next;
    free(tmp);
    tmp = next;
  }
  free(*list);
  (*list) = NULL;
}

void pushFront(list_t* list, char *value) {
  node_t* tmp = (node_t*)malloc(sizeof(node_t));
  if (tmp == NULL)
    return;
  strcpy(tmp->value.value, value);
  tmp->next = list->head;
  tmp->prev = NULL;
  if (list->head)
    list->head->prev = tmp;
  list->head = tmp;
  if (list->tail == NULL)
    list->tail = list->head;
}

data_t popFront(list_t* list) {
  node_t* prev;
  data_t tmp = {0};
  if (list->head == NULL)
    return tmp;
  prev = list->head;
  list->head = list->head->next;
  if (list->head)
    list->head->prev = NULL;
  else
    list->tail = NULL;
  tmp = prev->value;
  free(prev);
  return tmp;
}

void pushBack(list_t* list, char* value) {
  node_t* newEl = (node_t*)malloc(sizeof(node_t));
  node_t* tmp1 = NULL;
  
  if (newEl == NULL) {
    exit(3);
  }
  if (list->head == NULL) {
    pushFront(list, value);
  }
  else {
    tmp1 = list->tail;
    
    newEl->prev = tmp1;
    newEl->next = NULL;
    strcpy(newEl->value.value, value);

    tmp1->next = newEl;
    list->tail = newEl;
  }
}

void insertBeforeElement(list_t* list, node_t* elm, char *value) {
  node_t* ins = NULL;
  if (elm == NULL) {
    return;
  }
  if (!elm->prev) {
    pushFront(list, value);
    return;
  }
  ins = (node_t*)malloc(sizeof(node_t));
  if (ins == NULL) {
    return;
  }
  strcpy(ins->value.value, value);
  ins->prev = elm->prev;
  ins->next = elm;

  elm->prev = ins;

  ins->prev->next = ins;
}

int insertionSort(list_t** List) {
  if ((*List)->head == NULL) {
    return 0;
  }
  list_t* out = createList();
  node_t* sorted = NULL;
  node_t* unsorted = NULL;
  data_t tmp_data = popFront(*List);
  pushFront(out, tmp_data.value);

  unsorted = (*List)->head;
  while (unsorted != NULL) {
    sorted = out->tail;
    int flag = strcmp(unsorted->value.value, sorted->value.value);

    while (sorted != NULL && sorted->prev != NULL && flag < 0) {
      sorted = sorted->prev;
      flag = strcmp(unsorted->value.value, sorted->value.value);
    }
    if (flag < 0)
      insertBeforeElement(out, sorted, unsorted->value.value);
    else if (sorted->next != NULL)
      insertBeforeElement(out, sorted->next, unsorted->value.value);
    else
      pushBack(out, unsorted->value.value);
    unsorted = unsorted->next;
  }
  free(*List);
  *List = out;
  return 1;
}
