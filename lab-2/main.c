#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

//#define MIN_SIZE_MEM 3
#define TRUE 1
#define FALSE 0

typedef enum {
  CORRECT,
  ERROR
} error_t;

typedef struct node {
  int size;
  struct node* next;
  struct node* prev;
  int isFree;
} descriptor_t;

static struct {
  descriptor_t* list;
  int totalSize;
} s_memSystem = { (descriptor_t*)NULL, 0 };

int memgetminimumsize() {
  return  sizeof(descriptor_t);
}

int memgetblocksize() {
  return sizeof(descriptor_t);
}

int meminit(void* pMemory, int size) {
  int minsize = memgetminimumsize();
  int blockSize = memgetblocksize();
  if (pMemory == NULL || size < minsize + 1) //|| s_memSystem.list)
    return 0;
  else {
    //инициализация
    s_memSystem.list = (descriptor_t*)pMemory;
    s_memSystem.list->isFree = TRUE;
    s_memSystem.list->next = NULL;
    s_memSystem.list->prev = NULL;
    s_memSystem.list->size = size - blockSize;
    s_memSystem.totalSize = size;
    return 1;
  }
}

void* memalloc(int size) {
  descriptor_t* cur;
  descriptor_t* newB;
  descriptor_t* pBestFit = NULL;
  int blockSize = memgetblocksize();
  void* res = NULL;
  if (size <= 0 || s_memSystem.list == NULL) {
    return NULL;
  }
  //если память инициализирована
  if (s_memSystem.list) {
    cur = s_memSystem.list;

    //выбор лучшего блока
    do {
      //лучшим подходящим считаем минимальный подходящий блок.
      if ((cur->size >= size) && (pBestFit == NULL || (cur->size < pBestFit->size)) && (cur->isFree == TRUE)) {
        pBestFit = cur;
      }
      cur = cur->next;
    } while (cur);

    //если нашли блок
    if (pBestFit) {
      //первый случай: размер совпадает с запрашиваемым или нет возможности записать дескриптор на остаток блока: нужно просто выделить блок
      if (pBestFit->size <= size + memgetminimumsize()) {
        pBestFit->isFree = FALSE;
      }
      //второй случай: создаем новый дескриптор
      else {
        //Добавление
        newB = (descriptor_t*)((char*)pBestFit + size + blockSize);
        newB->prev = pBestFit;
        newB->next = pBestFit->next;
        if (pBestFit->next)
          pBestFit->next->prev = newB;
        pBestFit->next = newB;
        pBestFit->isFree = FALSE;
        //инициализация
        newB->isFree = TRUE;
        newB->size = pBestFit->size - size - blockSize;
        //
        pBestFit->size = size;
      }
      res = (void*)((char*)pBestFit + blockSize);
    }
    else {
      res = NULL;
    }
  }
  return res;
}

void memfree(void* p) {
  descriptor_t* firstFree = NULL, * newFree = NULL;
  int blockSize = memgetblocksize();
  //дали указатель
  //проверка на не NULL 
  if (p && s_memSystem.list) {
    //идем в дескриптор 
    newFree = (descriptor_t*)((char*)p - blockSize);
    //проверка на наличие его в области 
    if (newFree >= s_memSystem.list && newFree <= s_memSystem.list + s_memSystem.totalSize && (newFree->isFree == FALSE)) {
      //говорим что блок свободен и радуемся жизни
      newFree->isFree = TRUE;

      //а нет, еще рано
      //слияние соседних блоков

      // со следующим
      if (newFree->next) {
        if (newFree->next->isFree) {
          firstFree = newFree;
          //c концом
          firstFree->size += firstFree->next->size + blockSize;
          if (firstFree->next->next) {
            firstFree->next->next->prev = firstFree;
            firstFree->next = firstFree->next->next;
          }
          else {
            firstFree->next = NULL;
          }
          if (firstFree->prev) {
            firstFree->prev->next = firstFree;
          }
          else {
            firstFree->prev = NULL;
          }
        }
      }
      // с предыдущим
      if (newFree->prev) {
        if (newFree->prev->isFree) {
          firstFree = newFree->prev;
          if (firstFree->next)
            firstFree->size += firstFree->next->size + blockSize;
          if (firstFree->next) {
            if (firstFree->next->next) {
              firstFree->next->next->prev = firstFree;
              firstFree->next = firstFree->next->next;
            }
            else {
              firstFree->next = NULL;
            }
          }
        }
      }
    }

  }

}

void memdone() {
  s_memSystem.list = NULL;
  s_memSystem.totalSize = 0;
}

