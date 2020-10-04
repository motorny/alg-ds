#pragma once

#define LIST_OK 0
#define LIST_ERROR -1

typedef struct list_Item {
  void* value;
  int key;
  struct list_Item* nextItem;
} list_Item;

typedef struct list {
  list_Item startItem;
} list;

list* list_Get();

int list_Free(list* lst);

list_Item* list_Add(list* lst, void* value, int key);

list_Item* list_Find(list* lst, int key);

int list_DeleteByKey(list* lst, int key);