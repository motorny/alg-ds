#include "memallocator.h"
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define FAIL 0

typedef struct descriptor_t {
  int size;
  struct descriptor_t* next;
  struct descriptor_t* prev;
} descriptor_t;


int memgetminimumsize() {
  return sizeof(descriptor_t) + sizeof(int);
}

int memgetblocksize() {
  return sizeof(descriptor_t) + sizeof(int);
}

descriptor_t* list = NULL; // list of free blocks
char* start = NULL; // to stop in time when join blocks
int allmem = 0; // to check memory leaks
int meminit(void* pMemory, int size) {
  if (pMemory == NULL || size < memgetminimumsize() || start != NULL)
    return FAIL;
  
  allmem = size;
  start = pMemory;
  list = pMemory;
  list->size = size;
  list->next = NULL;
  list->prev = NULL;

  return SUCCESS;
}

void* memalloc(int size) {
  int bestFitSize;
  descriptor_t* bestFitPtr = list;
  descriptor_t* p = list;
  int* endDescriptor; // +- size in the end of block

  if (list == NULL || size <= 0) // no free memory or memory didn't initializate
    return NULL;
   
  bestFitSize = INT_MAX;
  while (p != NULL) {
    if (p->size >= size + memgetblocksize() && p->size < bestFitSize) {
      bestFitSize = p->size;
      bestFitPtr = p;
    }
    p = p->next;
  }
  if (bestFitSize == INT_MAX)
    return NULL;

  // change list of free memory;
  if (bestFitSize < size + 2 * memgetblocksize()) { // remove from list because there isn't enough memory to shift descriptor
    // allocate all block memory to not loss it
    // so not change size: bestFitPtr->size = bestFitPtr->size;
    // and change the end descriptor
    endDescriptor = (int*)((char*)bestFitPtr + bestFitPtr->size - sizeof(int));
    *endDescriptor = bestFitPtr->size;

    // remove from list
    if (bestFitPtr->prev != NULL)
      (bestFitPtr->prev)->next = bestFitPtr->next;
    else // it was the first element so change main list pointer
      list = bestFitPtr->next;
    if (bestFitPtr->next != NULL)
      (bestFitPtr->next)->prev = bestFitPtr->prev;
    if (bestFitPtr->prev == NULL && bestFitPtr->next == NULL) // it was last free element
      list = NULL;
  }
  else { // replace descriptor to the end of block and change size
    // write end descriptor of allocated block
    endDescriptor = (int*)((char*)bestFitPtr + sizeof(descriptor_t) + size);
    *endDescriptor = size + memgetblocksize();

    // write size
    bestFitPtr->size = size + memgetblocksize();
    // shift descriptor
    p = (descriptor_t*)((char*)bestFitPtr + memgetblocksize() + size);
    p->size = bestFitSize - size - memgetblocksize();
    p->next = bestFitPtr->next;
    p->prev = bestFitPtr->prev;
    // write new free memory to the end descriptor (-size)
    endDescriptor = (int*)((char*)p + p->size - sizeof(int));
    *endDescriptor = -p->size;
    
    // add to list
    if (p->prev != NULL)
      (p->prev)->next = p;
    else //it was the first element
      list = p;
    if (p->next != NULL)
      (p->next)->prev = p;
  }

  return (char*)bestFitPtr + sizeof(descriptor_t);
}

void memfree(void* p) {
  int freemem;
  descriptor_t* tmp;
  char isInList = 0; // when we join free blocks into one, it doesn't need to be added to the list
  assert(p != NULL);
  p = (char*)p - sizeof(descriptor_t);

  // join free blocks if possible
  freemem = ((descriptor_t*)p)->size;
  while ((char*)p > start && *((int*)p - 1) < 0) {
    freemem -= *((int*)p - 1);
    p = (char*)p + *((int*)p - 1);
    isInList = 1; // block have already been in the list 
  }

  // change size
  ((descriptor_t*)p)->size = freemem;

  //write -size to the end of block
  *(int*)((char*)p + freemem - sizeof(int)) = -freemem;
  
  // add to start of the list(if need)
  if (isInList)
    return;
  ((descriptor_t*)p)->next = list;
  ((descriptor_t*)p)->prev = NULL;
  if (list != NULL)
    list->prev = (descriptor_t*)p;
  tmp = (descriptor_t*)p;
  (descriptor_t*)p = list;
  list = tmp;
}

void memdone() {
  descriptor_t* p = list;
  int freemem = 0;
  while (p != NULL) {
    freemem += p->size;
    p = p->next;
  }
  assert(freemem == allmem);

  list = NULL;
  start = NULL;
  allmem = 0;
}