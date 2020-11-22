#include "memallocator.h"

#define TRUE 1
#define FALSE 0
#define NULL 0
typedef unsigned char byte;

typedef struct node_t node_t;
struct node_t {
  int size;
  char isAvalibale;
  int nodeKey;
  node_t* next;
  node_t* prev;
};

typedef struct nodeEnd_t {
  int size;
}nodeEnd_t;

byte* allocatedMemory = NULL;
int allocSize = 0;

node_t* freeMemory = NULL;

int meminit(void* pMemory, int size) {
  if (size <= 0 || size < memgetminimumsize() || pMemory == NULL)
    return FALSE;

  allocatedMemory = (byte*)pMemory;
  allocSize = size;
  freeMemory = (node_t*)pMemory;

  freeMemory->next = NULL;
  freeMemory->prev = NULL;
  freeMemory->size = size - memgetblocksize();
  freeMemory->nodeKey = 42;
  freeMemory->isAvalibale = TRUE;

  ((nodeEnd_t*)((byte*)freeMemory + freeMemory->size + sizeof(node_t)))->size = freeMemory->size;
  return TRUE;
}

void memdone() {
  allocatedMemory = NULL;
  allocSize = 0;
  freeMemory = NULL;
}

void deleteFromList(node_t* node)
{
  if (node->prev != NULL)
    node->prev->next = node->next;
  else
    freeMemory = freeMemory->next;
  if (node->next != NULL)
    node->next->prev = node->prev;
}

void makeDefragmentation(node_t* memoryBlock) {
  node_t* prev = NULL, * next = NULL;
  nodeEnd_t* endPrev = NULL, *endOfBlock = NULL, *endNext = NULL;

  if (memoryBlock == NULL || memoryBlock->nodeKey != 42)
    return;

  endOfBlock = (nodeEnd_t*)((byte*)memoryBlock + sizeof(node_t) + memoryBlock->size);
  if ((byte*)endOfBlock + sizeof(nodeEnd_t) < allocatedMemory + allocSize - 2) {
    next = (node_t*)((byte*)endOfBlock + sizeof(nodeEnd_t));
    endNext = (nodeEnd_t*)((byte*)next + next->size + sizeof(node_t));
  }
  if ((byte*)memoryBlock - sizeof(nodeEnd_t) > allocatedMemory) {
    endPrev = (nodeEnd_t*)((byte*)memoryBlock - sizeof(nodeEnd_t));
    prev = (node_t*)((byte*)endPrev - endPrev->size - sizeof(node_t));
  }

  if (next != NULL && next->nodeKey == 42 && next->isAvalibale) {
    deleteFromList(next);

    memoryBlock->size += sizeof(nodeEnd_t) + sizeof(node_t) + next->size;
    endNext->size = memoryBlock->size;
    next->nodeKey = 0;
    endOfBlock = endNext;
  }
  if (prev != NULL && prev->nodeKey == 42 && prev->isAvalibale) {
    deleteFromList(memoryBlock);

    prev->size += sizeof(nodeEnd_t) + sizeof(node_t) + memoryBlock->size;
    endOfBlock->size = prev->size;
    memoryBlock->nodeKey = 0;
    endPrev = endOfBlock;
  }
}

void* memalloc(int size) {
  node_t* toFindInList = freeMemory, * newMemoryBlock;
  nodeEnd_t* firstEnd, * secondEnd;

  if (allocatedMemory == NULL || size <= 0 || freeMemory == NULL)
    return NULL;

  while (toFindInList != NULL) {
    if (toFindInList->size >= size) {
      // split mem block
      if (toFindInList->size > size + sizeof(node_t) + sizeof(nodeEnd_t)) { 
        deleteFromList(toFindInList);
        
        firstEnd = (nodeEnd_t*)((byte*)toFindInList + sizeof(node_t) + size);
        firstEnd->size = size;

        node_t* newMemoryBlock = (node_t*)((byte*)firstEnd + sizeof(nodeEnd_t));
        newMemoryBlock->isAvalibale = TRUE;
        newMemoryBlock->nodeKey = 42;
        newMemoryBlock->next = freeMemory;
        newMemoryBlock->prev = NULL;
        newMemoryBlock->size = toFindInList->size - size - sizeof(nodeEnd_t) - sizeof(node_t);
        if (freeMemory)
          freeMemory->prev = newMemoryBlock;
        freeMemory = newMemoryBlock;

        secondEnd = (nodeEnd_t*)((byte*)newMemoryBlock + sizeof(node_t) + newMemoryBlock->size);
        secondEnd->size = newMemoryBlock->size;

        toFindInList->size = size;
        toFindInList->nodeKey = 42;
      }
      else
        deleteFromList(toFindInList);

      toFindInList->isAvalibale = FALSE;
      toFindInList->next = NULL;
      toFindInList->prev = NULL;

      return (void*)((byte*)toFindInList + sizeof(node_t));
    }
    toFindInList = toFindInList->next;
  }
  return NULL;
}

void memfree(void* p) {
  node_t* ptrToDelete;

  if (p == NULL || (byte*)p - allocatedMemory < 0 || (byte*)p - allocatedMemory > allocSize || ((node_t*)((byte*)p - sizeof(node_t)))->nodeKey != 42)
    return;

  ptrToDelete = (node_t*)((byte*)p - sizeof(node_t));
  ptrToDelete->isAvalibale = TRUE;
  ptrToDelete->next = freeMemory;
  ptrToDelete->prev = NULL;
  if (freeMemory)
    freeMemory->prev = ptrToDelete;
  freeMemory = ptrToDelete;
  makeDefragmentation(ptrToDelete);
}

int memgetblocksize() {
  return sizeof(node_t) + sizeof(nodeEnd_t);
}

int memgetminimumsize() {
  return sizeof(node_t) + sizeof(nodeEnd_t);
}
