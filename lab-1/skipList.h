#pragma once

#define SKIP_LIST_MAX_LEVEL_COUNT 4
#define SKIP_LIST_OK 0
#define SKIP_LIST_ERROR -1

typedef struct skipList_Item {
  void* value;
  int key;
  char levelCount;
  struct skipList_Item** nextItem_array;
} skipList_Item;

typedef struct skipList {
  skipList_Item statrItem;
} skipList;

skipList* skipList_Get();

int skipList_Free(skipList* sL);

int skipList_Add(skipList* sL, void* value, int key, char forceLevelOrZero);

skipList_Item* skipList_Find(skipList* sL, int key);