#include <stdlib.h>
#include <stdio.h>
#include "LabB.h"

void* head = NULL;
list_t* firstMemPart = NULL;
int globalSize = 0;

int memGetMinSize() {

  return sizeof(int) + (int)sizeof(list_t);
}

int memGetBlockSize() {

  return sizeof(int) + (int)sizeof(list_t);
}

// инициализируем память
int memInit(void* memory, int size) {

  if (!memory || size <= 0)
    return 0;

  else {
    head = memory;
    globalSize = size;
    firstMemPart = (list_t*)memory;
    firstMemPart->size = globalSize - memGetBlockSize();
    firstMemPart->next = NULL;
    *((int*)((char*)head + globalSize - sizeof(int))) = globalSize - memGetBlockSize();
    return 1;
  }
}

void* meMalloc(int size) {

  void* memory = NULL;
  list_t* freeMemPart = firstMemPart;
  list_t** nextMemPart = &firstMemPart;
  list_t* t;

  if (!head || size < 0 || !firstMemPart)
    return NULL;

  // ищем подходящий по размеру свободный блок
  while (freeMemPart) {
    if (freeMemPart->size >= size) 
      break;
    nextMemPart = &freeMemPart->next;
    freeMemPart = freeMemPart->next;
  }
  // если не нашлось свободного блока
  if (!freeMemPart)
    return NULL;

  // ищем следующий подходящий блок
  t = freeMemPart;
  freeMemPart = freeMemPart->next;
  while (freeMemPart) {
    if (freeMemPart->size >= size) 
      break;
    nextMemPart = &freeMemPart->next;
    freeMemPart = freeMemPart->next;
  }
  // если не нашли, то используем предыдущий
  if (!freeMemPart)
    freeMemPart = t;

  // связь предыдущего и следующего блока
  if (freeMemPart->size >= size + memGetBlockSize()) {
    list_t* nextFreeMemPart = (list_t*)((char*)freeMemPart + size + memGetBlockSize());
    nextFreeMemPart->size = freeMemPart->size - size - memGetBlockSize();
    *((int*)((char*)nextFreeMemPart + nextFreeMemPart->size + sizeof(list_t))) = nextFreeMemPart->size;
    nextFreeMemPart->next = freeMemPart->next;
    *nextMemPart = nextFreeMemPart;

    freeMemPart->size = size;
    *((int*)((char*)freeMemPart + freeMemPart->size + sizeof(list_t))) = freeMemPart->size;
  }
  else
    *nextMemPart = freeMemPart->next;

  freeMemPart->next = NULL;
  memory = sizeof(list_t) + (char*)freeMemPart;
  return memory;
}

// проверка на утечку памяти
void memDone() {

  if (!head || globalSize <= 0 || firstMemPart && globalSize == firstMemPart->size + memGetBlockSize())
    return;
  else 
    printf("Memory leaks!\n");
}

void memFree(void* memory) {

  int indicator = 0;
  list_t* memPart;

  if (!memory || (char*)memory - sizeof(list_t) < (char*)head || (char*)memory > globalSize + (char*)head)
    return;

  memPart = (list_t*)((char*)memory - sizeof(list_t));

  // связь с предыдущим блоком
  if ((char*)memPart >= (char*)head + memGetBlockSize()) {
    list_t* prevMemPart = (list_t*)((char*)memPart - memGetBlockSize() - *((int*)((char*)memPart - sizeof(int))));
    list_t* findMemPart = firstMemPart;

    while (findMemPart) {
      if (findMemPart == prevMemPart) 
        break;
      findMemPart = findMemPart->next;
    }

    if (findMemPart) {
      indicator = 1;
      prevMemPart->size += memGetBlockSize() + memPart->size;
      *((int*)((char*)prevMemPart + prevMemPart->size + sizeof(list_t))) = prevMemPart->size;
      memPart = prevMemPart;
    }
  }

  // связь со следующим блоком
  if (memPart + memPart->size + 2 * memGetBlockSize() >= globalSize + (list_t*)head) {
    list_t* nextMemPart = (list_t*)((char*)memPart + memPart->size + memGetBlockSize());
    list_t** findMemPart = &firstMemPart;

    while (*findMemPart) {
      if (*findMemPart == nextMemPart) 
        break;
      findMemPart = &(*findMemPart)->next;
    }

    if (*findMemPart) {
      indicator = 1;
      if (indicator) 
        *findMemPart = nextMemPart->next;
      else 
        *findMemPart = memPart;
      memPart->size += memGetBlockSize() + nextMemPart->size;
      *((int*)((char*)memPart + memPart->size + memGetBlockSize())) = memPart->size;
    }
  }

  if (!indicator)
    firstMemPart = memPart;
}