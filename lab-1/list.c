#include <stdlib.h>
#include "list.h"

list* list_Get() {
  list* lst;

  lst = (list*)malloc(sizeof(list));
  if (lst == NULL) {
    return NULL;
  }
  lst->startItem.nextItem = NULL;
  return lst;
}

int list_Free(list* lst) {
  list_Item* item, * nxtItem;

  //Проверка входных данных
  if (lst == NULL) {
    return LIST_ERROR;
  }

  item = lst->startItem.nextItem;
  while (item != NULL) {
    nxtItem = item->nextItem;
    free(item);
    item = nxtItem;
  }
  free(lst);
  return LIST_OK;
}

list_Item* list_Add(list* lst, void* value, int key) {
  list_Item* item, * nxtItem, * insertingItem;

  //Проверка входных данных
  if (lst == NULL) {
    return NULL;
  }

  //Инициализация
  insertingItem = (list_Item*)malloc(sizeof(list_Item));
  if (insertingItem == NULL) {
    return NULL;
  }
  insertingItem->value = value;
  insertingItem->key = key;
  insertingItem->nextItem = NULL;

  //Поиск
  item = &(lst->startItem);
  for (nxtItem = item->nextItem; nxtItem != NULL && nxtItem->key < key; nxtItem = nxtItem->nextItem) {
    item = nxtItem;
  }

  //Вставка
  item->nextItem = insertingItem;
  insertingItem->nextItem = nxtItem;

  return insertingItem;
}

list_Item* list_Find(list* lst, int key) {
  list_Item* item;

  //Проверка входных данных
  if (lst == NULL) {
    return NULL;
  }

  //Поиск
  for (item = lst->startItem.nextItem; item != NULL && item->key < key; item = item->nextItem);

  //Проверка результатов
  if (item != NULL && item->key == key) {
    return item;
  }
  else {
    return NULL;
  }
}

int list_DeleteByKey(list* lst, int key) {
  list_Item* item, * nxtItem;

  //Проверка входных данных
  if (lst == NULL) {
    return LIST_ERROR;
  }

  //Поиск
  item = &(lst->startItem);
  for (nxtItem = item->nextItem; nxtItem != NULL && nxtItem->key < key; nxtItem = nxtItem->nextItem) {
    item = nxtItem;
  }

  //Проверка результатов
  if (nxtItem != NULL && nxtItem->key == key) {
    item->nextItem = nxtItem->nextItem;
    free(nxtItem);
    return LIST_OK;
  }
  else {
    return LIST_ERROR;
  }
}
