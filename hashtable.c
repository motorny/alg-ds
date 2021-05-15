#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#pragma warning(disable:4996)

int insertInList(list_t* list, char* key) {

  elem_t* insElem = (elem_t*)malloc(sizeof(elem_t));
  if (insElem == NULL)
    return 0;
  elem_t** currElem = &(list->head);
  strcpy(insElem->key, key);
  //insElem->key = key;
  insElem->isDeleted = 0;
  insElem->next = NULL;

  while (*currElem != NULL && strcmp((*currElem)->key, key) < 0) {
    currElem = &((*currElem)->next);
  }

  if (*currElem != NULL && strcmp((*currElem)->key, key) == 0 && !((*currElem)->isDeleted)) {
    free(insElem);
    return 0;
  }

  if (*currElem != NULL && (*currElem)->isDeleted) {
    free(insElem);
    (*currElem)->isDeleted = 0;
    strcpy((*currElem)->key, key);
    return 1;
  }

  insElem->next = (*currElem);
  (*currElem) = insElem;

  return 1;
}

int findInList(list_t* list, char* key) {
  elem_t* elem = list->head;
  while (elem != NULL) {
    if (strcmp(elem->key, key) == 0 && !elem->isDeleted)
      return 1;
    elem = elem->next;
  }
  return 0;
}

int deleteInList(list_t* list, char* key) {
  elem_t* elem = list->head;
  while (elem != NULL) {
    if (strcmp(elem->key, key) == 0 && !elem->isDeleted) {
      elem->isDeleted = 1;
      return 1;
    }
    elem = elem->next;
  }
  return 0;
}

void clearList(list_t* list) {
  elem_t* tmp = list->head;
  while (tmp != NULL) {
    elem_t* next = tmp->next;
    free(tmp);
    tmp = next;
  }
}

unsigned hashfunction(char* key, unsigned table_size) {
  unsigned hash = 0;
  for (int i = 0; i < 100; i++)
  {
    hash += strlen(key) * i;
    hash %= table_size;
  }
  return hash;
}

void createHashtable(hash_table* table, unsigned size) {
  table->size = size;
  table->table = malloc(sizeof(list_t) * size);
  for (unsigned i = 0; i < size; i++)
    table->table[i].head = NULL;
}

void clearHashtable(hash_table* table) {
  for (unsigned i = 0; i < table->size; i++)
    if (table->table[i].head == NULL)
      clearList(&(table->table[i]));
  free(table->table);
  table->size = 0;
}

int insertInHashtable(hash_table* table, char* key) {
  unsigned hash = hashfunction(key, table->size);
  return insertInList(&(table->table[hash]), key);
}

int deleteInHashtable(hash_table* table, char* key) {
  unsigned hash = hashfunction(key, table->size);
  return deleteInList(&(table->table[hash]), key);
}

int findInHashtable(hash_table* table, char* key) {
  unsigned hash = hashfunction(key, table->size);
  return findInList(&(table->table[hash]), key);
}