// Gabdushev_A14_SkipList.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"

#include <stdlib.h>
#include "skipList.h"

skipList* skipList_Get(void) {
  skipList* sL;

  sL = (skipList*)malloc(sizeof(skipList));
  if (sL == NULL) {
    return NULL;
  }

  sL->statrItem.nextItem_array = (skipList_Item**)calloc(SKIP_LIST_MAX_LEVEL_COUNT, sizeof(skipList_Item*));
  if (sL->statrItem.nextItem_array == NULL) {
    free(sL);
    return NULL;
  }

  return sL;
}

int skipList_Free(skipList* sL) {
  skipList_Item* item, * nextItem;

  //Проверка входных данных
  if (sL == NULL || sL->statrItem.nextItem_array == NULL) {
    return SKIP_LIST_ERROR;
  }

  item = sL->statrItem.nextItem_array[0];
  while (item != NULL) {
    nextItem = item->nextItem_array[0];
    free(item->nextItem_array);
    free(item);
    item = nextItem;
  }
  free(sL->statrItem.nextItem_array);
  free(sL);
  return SKIP_LIST_OK;
}

static char skipList_GetRandLevelCount(void) {
  char n = 1;
  while (n < SKIP_LIST_MAX_LEVEL_COUNT && rand()%2 == 1) {
    n++;
  }
  return n;
}

int skipList_Add(skipList* sL, void* value, int key, char forceLevelOrZero) {
  char i, itemLevelCount;
  skipList_Item* item, * nextItem, * insertingItem;

  //В этот массив записываются последние элементы каждого уровня перед искомомым элементом
  skipList_Item** endSearchItem_array;

  //Проверка входных данных
  if (sL == NULL || sL->statrItem.nextItem_array == NULL || 
      forceLevelOrZero < 0 || forceLevelOrZero > SKIP_LIST_MAX_LEVEL_COUNT) {
    return SKIP_LIST_ERROR;
  }

  //Уровень вставляемого элемента может задаваться вероятностно (при 0) или конкретно (если корректное число)
  if (forceLevelOrZero == 0) {
    itemLevelCount = skipList_GetRandLevelCount();
  }
  else {
    itemLevelCount = forceLevelOrZero;
  }

  //Инициализация
  endSearchItem_array = (skipList_Item**)calloc(SKIP_LIST_MAX_LEVEL_COUNT, sizeof(skipList_Item*));
  if (endSearchItem_array == NULL) {
    return SKIP_LIST_ERROR;
  }
  insertingItem = (skipList_Item*)malloc(sizeof(skipList_Item));
  if (insertingItem == NULL) {
    free(endSearchItem_array);
    return SKIP_LIST_ERROR;
  }
  *insertingItem = { value , key , itemLevelCount , NULL};
  insertingItem->nextItem_array = (skipList_Item**)calloc(itemLevelCount, sizeof(skipList_Item*));
  if (insertingItem->nextItem_array == NULL) {
    free(endSearchItem_array);
    free(insertingItem);
    return SKIP_LIST_ERROR;
  }

  //Поиск
  item = &(sL->statrItem);
  for (i = SKIP_LIST_MAX_LEVEL_COUNT - 1; i >= 0; i--) {
    nextItem = item->nextItem_array[i];
    while (nextItem != NULL && nextItem->key < key) {
      item = nextItem;
      nextItem = nextItem->nextItem_array[i];
    }
    endSearchItem_array[i] = item;
  }

  //Вставка
  for (i = 0; i < itemLevelCount; i++) {
    item = endSearchItem_array[i];
    nextItem = item->nextItem_array[i];
    item->nextItem_array[i] = insertingItem;
    insertingItem->nextItem_array[i] = nextItem;
  }
  
  free(endSearchItem_array);
  return SKIP_LIST_OK;
}

skipList_Item* skipList_Find(skipList* sL, int key)
{
  char i;
  skipList_Item* item, * nextItem = NULL;

  //Проверка входных данных
  if (sL == NULL || sL->statrItem.nextItem_array == NULL) {
    return NULL;
  }

  item = &(sL->statrItem);
  for (i = SKIP_LIST_MAX_LEVEL_COUNT - 1; i >= 0; i--) {
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

int skipList_DeleteItem(skipList* sL, skipList_Item* deletingItem) {
  char i, itemLevelCount;
  skipList_Item* item, * nextItem = NULL;

  //В этот массив записываются последние элементы каждого уровня перед искомомым элементом
  skipList_Item** endSearchItem_array;

  //Проверка входных данных
  if (sL == NULL || sL->statrItem.nextItem_array == NULL || deletingItem == NULL) {
    return SKIP_LIST_ERROR;
  }
  
  //Инициализация
  itemLevelCount = deletingItem->levelCount;
  endSearchItem_array = (skipList_Item**)calloc(SKIP_LIST_MAX_LEVEL_COUNT, sizeof(skipList_Item*));
  if (endSearchItem_array == NULL) {
    return SKIP_LIST_ERROR;
  }

  //Поиск
  item = &(sL->statrItem);
  for (i = SKIP_LIST_MAX_LEVEL_COUNT - 1; i >= 0; i--) {
    nextItem = item->nextItem_array[i];
    while (nextItem != NULL && nextItem != deletingItem) {
      item = nextItem;
      nextItem = nextItem->nextItem_array[i];
    }
    endSearchItem_array[i] = item;
  }

  if (nextItem != deletingItem) {
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

int skipList_DeleteByKey(skipList* sL, int key) {
  char i, itemLevelCount;
  skipList_Item* item, * nextItem = NULL, * deletingItem;

  //В этот массив записываются последние элементы каждого уровня перед искомомым элементом
  skipList_Item** endSearchItem_array;

  //Проверка входных данных
  if (sL == NULL || sL->statrItem.nextItem_array == NULL) {
    return SKIP_LIST_ERROR;
  }

  //Инициализация
  endSearchItem_array = (skipList_Item**)calloc(SKIP_LIST_MAX_LEVEL_COUNT, sizeof(skipList_Item*));
  if (endSearchItem_array == NULL) {
    return SKIP_LIST_ERROR;
  }

  //Поиск
  item = &(sL->statrItem);
  for (i = SKIP_LIST_MAX_LEVEL_COUNT - 1; i >= 0; i--) {
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