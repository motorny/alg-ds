#pragma once

#define SKIP_LIST_OK 0
#define SKIP_LIST_ERROR -1

typedef struct skipList_Item {
  void* value;
  int key;
  int levelCount;
  struct skipList_Item** nextItem_array;
} skipList_Item;

typedef struct skipList {
  skipList_Item statrItem;
  int maxLevelCount;
} skipList;

skipList* skipList_Get(int maxLevelCount);

int skipList_Free(skipList* sL);

skipList_Item* skipList_Add(skipList* sL, void* value, int key, int forceLevelOrZero);

skipList_Item* skipList_Find(skipList* sL, int key);

int skipList_DeleteByKey(skipList* sL, int key);