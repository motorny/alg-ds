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
  start = (char*)pMemory;
  list = (descriptor_t*)pMemory;
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
   
  bestFitSize = 2000000000;
  while (p != NULL) {
    if (p->size >= size + memgetblocksize() && p->size < bestFitSize) {
      bestFitSize = p->size;
      bestFitPtr = p;
    }
    p = p->next;
  }
  if (bestFitSize == 2000000000)
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
  descriptor_t* nextDes;
  descriptor_t* prevDes;
  descriptor_t* curDes;
  int* curEnd;
  int* nextEnd;
  int* prevEnd;

  if (p < (void*)start || p > (void*)(start + allmem))
    return;

  curDes = (descriptor_t*)((char*)p - sizeof(descriptor_t));
  curEnd = (int*)((char*)curDes + curDes->size - sizeof(int));

  // join with previous block
  prevEnd = (int*)((char*)curDes - sizeof(int));
  if (prevEnd > (int*)start && *prevEnd < 0) { // possible to join
    prevDes = (descriptor_t*)((char*)curDes + *prevEnd);
    prevDes->size += curDes->size;
    *curEnd = -prevDes->size; //block is free
    curDes = prevDes;
  }
  else { // impossibe to join
    *curEnd = -*curEnd; // block become free
    //add to the start of list
    if (list != NULL) { //list is not empty
      curDes->next = list;
      curDes->prev = NULL;
      list->prev = curDes;
      list = curDes;
    }
    else {
      list = curDes;
      list->prev = NULL;
      list->next = NULL;
    }
  }

  // join with next block
  nextDes = (descriptor_t*)((char*)curDes + curDes->size);
  if (nextDes < (descriptor_t*)(start + allmem)) { // next descriptor exist;
    nextEnd = (int*)((char*)nextDes + nextDes->size - sizeof(int));
    if (*nextEnd < 0) { // possible to join
      curDes->size += nextDes->size;
      *nextEnd = -curDes->size; //block is free
      //renove from list
      if (nextDes->next != NULL)
        (nextDes->next)->prev = nextDes->prev;
      if (nextDes->prev != NULL)
        (nextDes->prev)->next = nextDes->next;
      else 
        list = nextDes->next;
    }
  }
}

void memdone() {
  descriptor_t* p = list;
  int freemem = 0;
  while (p != NULL) {
    freemem += p->size;
    p = p->next;
  }
 // assert(freemem == allmem);

  list = NULL;
  start = NULL;
  allmem = 0;
}