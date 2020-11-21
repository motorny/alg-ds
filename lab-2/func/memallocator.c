#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include "memallocator.h"

// pointer to the block list begin
block_t* memList;
int memSize = 0;
bool_t init = FALSE;

int memgetminimumsize() {
  return sizeof(block_t) + sizeof(int);
}

int memgetblocksize() {
  return sizeof(block_t); //+ sizeof(int);
}

int meminit(void *pMemory, int size){

    if (size < memgetminimumsize() || pMemory == NULL || init == TRUE)
        return ERROR;
    memList = (block_t*)pMemory;
    memSize = size;

    memList->prev = NULL;
    memList->next = NULL;
    memList->size = memSize - sizeof(block_t);
    init = TRUE;
    return OK;
}

void* memalloc(int size) {
  if (size <= 0 || memList == NULL)
    return NULL;

  block_t* block;
  block_t* best = NULL;
  int bestSize = INT_MAX;

  // find best block
  for (block = memList; block != NULL; block = block->next)
    if (block->size - size >= 0 && block->size - size < bestSize - size) {
      best = block;
      bestSize = best->size;
    }

  if (best == NULL)
    return NULL;

  // separate block
  block_t* returnToUser = best + 1;

  block_t* newBlock;
  newBlock = (block_t*)((char*)(best)+sizeof(block_t) + size);

  if (best == memList)
      memList = newBlock;

  newBlock->size = best->size - size - sizeof(block_t);
  if (newBlock->size <= 0)
  {
      if (newBlock == memList)
          memList = NULL;
      best->next = NULL;
      return returnToUser;
  }

  if (best->prev != NULL) {
    best->prev->next = newBlock;
  }
  newBlock->prev = best->prev;

  if (best->next != NULL)
    best->next->prev = newBlock;
  newBlock->next = best->next;

  best->size = size;

  return returnToUser;
}

void memfree(void* p) {
    block_t* block;

    block_t* newBlock = (block_t*)p - 1;

    if (memList == NULL)
    {
        memList = (block_t *)p - 1;
        memList->next = NULL;
        memList->prev = NULL;
        return;
    }

    // suppose that memList is the leftist free block
    if ((block_t*)p < memList)
    {
        block = memList;
        // reassign memList
        memList = (block_t *)p - 1;
        memList->next = block;
        assert(block->prev == NULL);
        memList->prev = NULL; // == block->prev
    }
    else
    {
        //search for previous block
        for (block = memList;
             block != NULL &&
             block->next != NULL &&
             (void*)block->next < p;
             block = block->next);

        // error
        if (block == NULL)
            return;

        block_t* oldNext = block->next;

        block->next = newBlock;
        newBlock->prev = block;

        newBlock->next = oldNext;
        if (oldNext != NULL)
            oldNext->prev = newBlock;

        // cannot be executed from the first `if` branch
        //(char*)newBlock->prev
        if ((char*)newBlock->prev + sizeof(block_t) + newBlock->prev->size == (char*)newBlock) {

          newBlock->prev->next = newBlock->next; // ok
          if (newBlock->next != NULL)
            newBlock->next->prev = newBlock->prev;
          newBlock->prev->size += sizeof(block_t) + newBlock->size; // ok
          newBlock = newBlock->prev;
        }
    }

    // free blocks merge
    // NULL checks

    if ((char*)newBlock + sizeof(block_t) + newBlock->size == (char*)newBlock->next) {
        if (newBlock->next->next != NULL)
            newBlock->next->next->prev = newBlock;
      newBlock->next = newBlock->next->next;
      newBlock->size += sizeof(block_t) + newBlock->next->size;
    }
}

void memdone() {
  memList = NULL;
  memSize = 0;
  init = FALSE;
}
