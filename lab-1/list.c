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

  //�������� ������� ������
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

  //�������� ������� ������
  if (lst == NULL) {
    return NULL;
  }

  //�������������
  insertingItem = (list_Item*)malloc(sizeof(list_Item));
  if (insertingItem == NULL) {
    return NULL;
  }
  insertingItem->value = value;
  insertingItem->key = key;
  insertingItem->nextItem = NULL;

  //�����
  item = &(lst->startItem);
  for (nxtItem = item->nextItem; nxtItem != NULL && nxtItem->key < key; nxtItem = nxtItem->nextItem) {
    item = nxtItem;
  }

  //�������
  item->nextItem = insertingItem;
  insertingItem->nextItem = nxtItem;

  return insertingItem;
}

list_Item* list_Find(list* lst, int key) {
  list_Item* item;

  //�������� ������� ������
  if (lst == NULL) {
    return NULL;
  }

  //�����
  for (item = lst->startItem.nextItem; item != NULL && item->key < key; item = item->nextItem);

  //�������� �����������
  if (item != NULL && item->key == key) {
    return item;
  }
  else {
    return NULL;
  }
}

int list_DeleteByKey(list* lst, int key) {
  list_Item* item, * nxtItem;

  //�������� ������� ������
  if (lst == NULL) {
    return LIST_ERROR;
  }

  //�����
  item = &(lst->startItem);
  for (nxtItem = item->nextItem; nxtItem != NULL && nxtItem->key < key; nxtItem = nxtItem->nextItem) {
    item = nxtItem;
  }

  //�������� �����������
  if (nxtItem != NULL && nxtItem->key == key) {
    item->nextItem = nxtItem->nextItem;
    free(nxtItem);
    return LIST_OK;
  }
  else {
    return LIST_ERROR;
  }
}
