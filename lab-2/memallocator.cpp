#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memallocator.h"
#define FALSE 0
#define TRUE 1
#define FAIL 0
#define SUCCES 1
typedef unsigned char byte;

byte* allocatedMemory;
int allocSize;
char wasInit = FALSE;

typedef struct node node_t;
struct node {
  int size;
  char isAvalibale;     // 1 - is free, 0 - not
  int nodeKey;          // is 42; to check memory
  node_t* prev;
  node_t* next;
};

typedef struct nodeEnd {
  int size;
} nodeEnd_t;

node_t* freeMemory;

static int isInsideMemory(byte* ptr) {
  if (ptr < allocatedMemory || ptr >= allocatedMemory + allocSize)
    return 0;
  return 1;
}

int meminit(void* pMemory, int size) {
  int i = 0;
  if (pMemory == NULL || size < memgetminimumsize())
    return FAIL;

  memset(pMemory, 0, size);

  allocatedMemory = (byte*)pMemory;
  allocSize = size;
  freeMemory = (node_t*)pMemory;

  freeMemory->prev = NULL;
  freeMemory->next = NULL;
  freeMemory->isAvalibale = 1;
  freeMemory->nodeKey = 42;

  if (allocSize - sizeof(nodeEnd_t) - sizeof(node_t) < 0)
    return FAIL;
  else
    freeMemory->size = allocSize - sizeof(nodeEnd_t) - sizeof(node_t);

  ((nodeEnd_t*)(allocatedMemory + freeMemory->size + sizeof(node_t)))->size = freeMemory->size;
  wasInit = TRUE;
  return SUCCES;
}

static void memMakeDefragmentation(node_t** memoryBlock) {
  node_t* currFreeMemoryBlock = freeMemory, * next, * prev, * tmp,
    * tmpPrev, * tmpNext;
  nodeEnd_t* end;

  if (freeMemory == NULL || *memoryBlock == NULL)
    return;

  if (freeMemory->next == NULL || (*memoryBlock)->nodeKey != 42)
    return;

  if ((byte*)(*memoryBlock) + memgetblocksize() + (*memoryBlock)->size < allocatedMemory + allocSize)
    next = (node_t*)((byte*)(*memoryBlock) + memgetblocksize() + (*memoryBlock)->size);
  else
    next = NULL;
  if ((byte*)(*memoryBlock) > allocatedMemory) {
    end = (nodeEnd_t*)((byte*)(*memoryBlock) - sizeof(nodeEnd_t));
    if (end->size >= 0)
      prev = (node_t*)((byte*)(*memoryBlock) - sizeof(nodeEnd_t) - end->size - sizeof(node_t));
    else
      prev = NULL;
  }
  else
    prev = NULL;

  if (next != NULL && next->isAvalibale == 1 && next->nodeKey == 42) {
    next->nodeKey = 0; // make next invalid
    (*memoryBlock)->size += memgetblocksize() + next->size;
    end = (nodeEnd_t*)((byte*)(*memoryBlock) + sizeof(node_t) + (*memoryBlock)->size);
    end->size = (*memoryBlock)->size;

    tmp = next;
    tmpNext = tmp->next;
    tmpPrev = tmp->prev;

    if (tmpNext != NULL)
      tmpNext->prev = tmpPrev;
    if (tmpPrev != NULL)
      tmpPrev->next = tmpNext;
    else if (freeMemory != NULL)
      freeMemory = tmpNext;
  }

  if (prev != NULL && prev->isAvalibale == 1 && prev->nodeKey == 42) {
    (*memoryBlock)->nodeKey = 0; // make cur invalid
    end = (nodeEnd_t*)((byte*)(*memoryBlock) + sizeof(node_t) + (*memoryBlock)->size);
    prev->size += memgetblocksize() + (*memoryBlock)->size;
    end->size = prev->size;

    tmp = (*memoryBlock);
    tmpNext = tmp->next;
    tmpPrev = tmp->prev;

    if (tmpNext != NULL && tmpNext->nodeKey == 42)
      tmpNext->prev = tmpPrev;
    if (tmpPrev != NULL && tmpPrev->nodeKey == 42)
      tmpPrev->next = tmpNext;
    else
      freeMemory = tmpNext;
  }
}

void memdone() {
  memset(allocatedMemory, 0, allocSize);
  allocatedMemory = NULL;
  allocSize = 0;
  freeMemory = NULL;
  wasInit = FALSE;
}

void* memalloc(int size) {
  node_t** toFindInList = &freeMemory,
    * newFreeMemBlock, * prev, * next;
  nodeEnd_t* endOfBlock;
  byte* ptrToReturn;

  if (wasInit == FALSE || size <= 0 || freeMemory == NULL)
    return NULL;

  while (*toFindInList != NULL && (*toFindInList)->nodeKey == 42) {
    if (isInsideMemory((byte*)(*toFindInList)) == 0)
      return NULL;

    if ((*toFindInList)->size >= size && (*toFindInList)->isAvalibale == 1) {
      (*toFindInList)->isAvalibale = 0;
      prev = (*toFindInList)->prev;
      next = (*toFindInList)->next;

      // split mem block 
      if ((*toFindInList)->size > size + memgetblocksize()) {
        endOfBlock = (nodeEnd_t*)((byte*)(*toFindInList) + sizeof(node_t) + size);
        endOfBlock->size = size;

        newFreeMemBlock = (node_t*)((byte*)(endOfBlock)+sizeof(nodeEnd_t));
        newFreeMemBlock->isAvalibale = 1;
        newFreeMemBlock->nodeKey = 42;
        newFreeMemBlock->size = (*toFindInList)->size - size - memgetblocksize();
        endOfBlock = (nodeEnd_t*)((byte*)newFreeMemBlock + sizeof(node_t) + newFreeMemBlock->size);
        endOfBlock->size = newFreeMemBlock->size;
        ptrToReturn = (byte*)(*toFindInList) + sizeof(node_t);
        if (((node_t*)(ptrToReturn - sizeof(node_t)))->nodeKey != 42)
          return NULL;
        ((node_t*)(ptrToReturn - sizeof(node_t)))->size = size;
        ((node_t*)(ptrToReturn - sizeof(node_t)))->isAvalibale = 0;
        ((node_t*)(ptrToReturn - sizeof(node_t)))->next = NULL;
        ((node_t*)(ptrToReturn - sizeof(node_t)))->prev = NULL;
        if (next != NULL)
          next->prev = prev;
        if (prev != NULL)
          prev->next = next;
        else if (freeMemory != NULL)
          freeMemory = freeMemory->next;

        newFreeMemBlock->next = freeMemory;
        newFreeMemBlock->prev = NULL;
        if (freeMemory != NULL)
          freeMemory->prev = newFreeMemBlock;
        freeMemory = newFreeMemBlock;
      }
      else {
        if (prev != NULL)
          prev->next = next;
        if (next != NULL)
          next->prev = prev;
        ptrToReturn = (byte*)(*toFindInList) + sizeof(node_t);
        if (*toFindInList == freeMemory) // if we give back first block
          freeMemory = freeMemory->next;
      }
      ((node_t*)(ptrToReturn - sizeof(node_t)))->next = NULL;
      ((node_t*)(ptrToReturn - sizeof(node_t)))->prev = NULL;
      return ptrToReturn;
    }
    toFindInList = &((*toFindInList)->next);
  }

  return NULL;
}

void memfree(void* p) {
  node_t* ptrToDelete;
  node_t* findPosInFreeMemory = freeMemory;
  char oneElementInFree = 1;

  if (wasInit == FALSE || p == NULL)
    return;

  if ((byte*)p <= allocatedMemory || (byte*)p >= allocatedMemory + allocSize)
    return;

  ptrToDelete = (node_t*)((byte*)p - sizeof(node_t));

  if ((byte*)ptrToDelete < allocatedMemory || (byte*)ptrToDelete >= allocatedMemory + allocSize || ptrToDelete->nodeKey != 42)
    return;
  else {
    if (ptrToDelete->isAvalibale == 1)
      return;
    if (ptrToDelete->next != NULL && ptrToDelete->prev != NULL)
      return;

    ptrToDelete->isAvalibale = 1;

    if (freeMemory != NULL)
      freeMemory->prev = ptrToDelete;
    ptrToDelete->next = freeMemory;
    ptrToDelete->prev = NULL;

    freeMemory = ptrToDelete;
    memMakeDefragmentation(&freeMemory);
    return;
  }
}

int memgetminimumsize() {
  return sizeof(node_t) + sizeof(nodeEnd_t);
}

int memgetblocksize() {
  return sizeof(node_t) + sizeof(nodeEnd_t);
}