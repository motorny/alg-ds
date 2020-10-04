#include <stdlib.h>
#include "skipList.h"

skipList* skipList_Get(int maxLevelCount) {
  skipList* sL;

  sL = (skipList*)malloc(sizeof(skipList));
  if (sL == NULL) {
    return NULL;
  }
  sL->maxLevelCount = maxLevelCount;
  sL->startItem.nextItem_array = (skipList_Item**)calloc(maxLevelCount, sizeof(skipList_Item*));
  if (sL->startItem.nextItem_array == NULL) {
    free(sL);
    return NULL;
  }

  return sL;
}

int skipList_Free(skipList* sL) {
  skipList_Item* item, * nextItem;

  //Проверка входных данных
  if (sL == NULL || sL->startItem.nextItem_array == NULL || sL->maxLevelCount < 1) {
    return SKIP_LIST_ERROR;
  }

  item = sL->startItem.nextItem_array[0];
  while (item != NULL) {
    nextItem = item->nextItem_array[0];
    free(item->nextItem_array);
    free(item);
    item = nextItem;
  }
  free(sL->startItem.nextItem_array);
  free(sL);
  return SKIP_LIST_OK;
}

static int skipList_GetRandLevelCount(int maxLevelCount) {
  int n = 1;
  while (n < maxLevelCount && rand()%2 == 1) {
    n++;
  }
  return n;
}

skipList_Item* _skipList_Add(skipList* sL, void* value, int key, int forceLevelOrZero) {
  int i, itemLevelCount, maxLevelCount;
  skipList_Item* item, * nextItem, * insertingItem;

  //Проверка входных данных
  if (sL == NULL || sL->startItem.nextItem_array == NULL || sL->maxLevelCount < 1) {
    return NULL;
  }
  maxLevelCount = sL->maxLevelCount;
  if (forceLevelOrZero < 0 || forceLevelOrZero > maxLevelCount) {
    return NULL;
  }

  //Уровень вставляемого элемента может задаваться вероятностно (при 0) или конкретно (если корректное число)
  if (forceLevelOrZero == 0) {
    itemLevelCount = skipList_GetRandLevelCount(maxLevelCount);
  }
  else {
    itemLevelCount = forceLevelOrZero;
  }

  //Инициализация
  insertingItem = (skipList_Item*)malloc(sizeof(skipList_Item));
  if (insertingItem == NULL) {
    return NULL;
  }
  insertingItem->value = value;
  insertingItem->key = key;
  insertingItem->levelCount = itemLevelCount;
  insertingItem->nextItem_array = NULL;
  insertingItem->nextItem_array = (skipList_Item**)calloc(itemLevelCount, sizeof(skipList_Item*));
  if (insertingItem->nextItem_array == NULL) {
    free(insertingItem);
    return NULL;
  }

  //Поиск
  item = &(sL->startItem);
  for (i = maxLevelCount - 1; i >= itemLevelCount; i--) {
    nextItem = item->nextItem_array[i];
    while (nextItem != NULL && nextItem->key < key) {
      item = nextItem;
      nextItem = nextItem->nextItem_array[i];
    }
  }

  //Поиск и вставка
  for (i = itemLevelCount - 1; i >= 0; i--) {
    nextItem = item->nextItem_array[i];
    while (nextItem != NULL && nextItem->key < key) {
      item = nextItem;
      nextItem = nextItem->nextItem_array[i];
    }
    item->nextItem_array[i] = insertingItem;
    insertingItem->nextItem_array[i] = nextItem;
  }

  return insertingItem;
}

skipList_Item* skipList_Add(skipList* sL, void* value, int key) {
  return _skipList_Add(sL, value, key, 0);
}


skipList_Item* skipList_Find(skipList* sL, int key)
{
  int i, maxLevelCount;
  skipList_Item* item, * nextItem = NULL;

  //Проверка входных данных
  if (sL == NULL || sL->startItem.nextItem_array == NULL || sL->maxLevelCount < 1) {
    return NULL;
  }

  maxLevelCount = sL->maxLevelCount;
  item = &(sL->startItem);
  for (i = maxLevelCount - 1; i >= 0; i--) {
    nextItem = item->nextItem_array[i];
    while (nextItem != NULL && nextItem->key < key) {
      item = nextItem;
      nextItem = nextItem->nextItem_array[i];
    }
  }

  if (nextItem != NULL && nextItem->key == key) {
    return nextItem;
  }
  else {
    return NULL;
  }
}

int skipList_DeleteByKey(skipList* sL, int key) {
  int i, itemLevelCount, maxLevelCount;
  skipList_Item* item, * nextItem = NULL, * deletingItem;

  //В этот массив записываются последние элементы каждого уровня перед искомомым элементом
  skipList_Item** endSearchItem_array;

  //Проверка входных данных
  if (sL == NULL || sL->startItem.nextItem_array == NULL || sL->maxLevelCount < 1) {
    return SKIP_LIST_ERROR;
  }

  //Инициализация
  maxLevelCount = sL->maxLevelCount;
  endSearchItem_array = (skipList_Item**)calloc(maxLevelCount, sizeof(skipList_Item*));
  if (endSearchItem_array == NULL) {
    return SKIP_LIST_ERROR;
  }

  //Поиск
  item = &(sL->startItem);
  for (i = maxLevelCount - 1; i >= 0; i--) {
    nextItem = item->nextItem_array[i];
    while (nextItem != NULL && nextItem->key < key) {
      item = nextItem;
      nextItem = nextItem->nextItem_array[i];
    }
    endSearchItem_array[i] = item;
  }

  if (nextItem != NULL && nextItem->key == key) {
    deletingItem = nextItem;
    itemLevelCount = deletingItem->levelCount;
  }
  else {
    free(endSearchItem_array);
    return SKIP_LIST_ERROR;
  }

  //Удаление
  for (i = 0; i < itemLevelCount; i++) {
    item = endSearchItem_array[i];
    nextItem = deletingItem->nextItem_array[i];
    item->nextItem_array[i] = nextItem;
  }
  free(deletingItem->nextItem_array);
  free(deletingItem);

  free(endSearchItem_array);
  return SKIP_LIST_OK;
}