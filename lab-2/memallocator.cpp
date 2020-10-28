#include <stdio.h>
#include <stdlib.h>
#include "memallocator.h"

#define UNAVAILIBLE - 1
#define FAIL 0
#define SUCCESS 1

typedef struct descriptor descriptor_t;

struct descriptor{
  int magicNumber; // to see if pointer is valid
  int size;
  descriptor_t* next;
};

typedef struct block_end{
  int size;
} block_end_t;

struct {
  descriptor_t* list;
  int totalSize;
  char* begin;
} s_memControl = { (descriptor_t*)NULL, 0, NULL };

#define ADDITIONAL_BLOCK_SIZE sizeof(descriptor_t) + sizeof(block_end_t)

int memgetminimumsize() {// Return minimum size in bytes of the memory pool to allocate 0-bytes block
  return (int)ADDITIONAL_BLOCK_SIZE;
}

int memgetblocksize() {// Returns size in bytes of additional information per allocation
  return (int)ADDITIONAL_BLOCK_SIZE;
}

int meminit(void* pMemory, int size) {// Init memory system with memory block pMemory.
  if (pMemory == NULL || size < memgetminimumsize())
    return FAIL;
  s_memControl.totalSize = size;
  s_memControl.begin = (char*)pMemory;
  s_memControl.list = (descriptor_t*)pMemory;
  s_memControl.list->magicNumber = 1984;
  s_memControl.list->size = s_memControl.totalSize + ((-1) * (int)(ADDITIONAL_BLOCK_SIZE));
  s_memControl.list->next = NULL;
  ((block_end_t*)(s_memControl.begin + sizeof(descriptor_t) + s_memControl.list->size))->size = s_memControl.list->size;
  return SUCCESS;
}

void* memalloc(int size) {// Allocate memory block of size 'size'. Returns pointer to memory block is success, 0 otherwise
  descriptor_t* newBlock;
  descriptor_t** bufBlock = NULL;
  descriptor_t** toFind = &s_memControl.list;
  int blockSize;

  if (size <= 0 || s_memControl.list == NULL || s_memControl.begin == NULL)
    return NULL;

  //find first fitting block
  while ((*toFind) != NULL) {
      if ((*toFind)->size >= size) {
        bufBlock = toFind;
        break;
      }
    toFind = &(*toFind)->next;
  }

  //if did not find
  if (bufBlock == NULL)
    return NULL;

  //save to our block
  blockSize = (*bufBlock)->size;
  newBlock = *bufBlock;

  //we will add more memory to block because there is no point not to
  if (blockSize <= (int)((int)ADDITIONAL_BLOCK_SIZE + size)) {
    ((block_end_t*)((char*)*bufBlock + sizeof(descriptor_t) + blockSize))->size = UNAVAILIBLE;
    *bufBlock = (*bufBlock)->next;
    newBlock->next = NULL;
    return (char*)newBlock + sizeof(descriptor_t);
  }

  //update end
  ((block_end_t*)((char*)*bufBlock + sizeof(descriptor_t) + blockSize))->size = blockSize + ((-1) * (int)(ADDITIONAL_BLOCK_SIZE)) - size;

  //update descriptor
  *bufBlock = (descriptor_t*)((char*)*bufBlock + ADDITIONAL_BLOCK_SIZE + size);
  (*bufBlock)->size = blockSize  + ((-1) * (int)(ADDITIONAL_BLOCK_SIZE)) - size;
  (*bufBlock)->magicNumber = 1984;
  (*bufBlock)->next = newBlock->next;

  //add block to list
  newBlock->size = size;
  newBlock->magicNumber = 1984;
  newBlock->next = NULL;
  ((block_end_t*)((char*)newBlock + sizeof(descriptor_t) + size))->size = UNAVAILIBLE;
  return (char*)newBlock + sizeof(descriptor_t);
}


void memfree(void* p) {// Free memory previously allocated by memalloc

  if ((char*)p < (char*)s_memControl.begin || (char*)p >= (char*)s_memControl.begin + s_memControl.totalSize || p == NULL)
    return;

  //check if descriptor is invalid
  descriptor_t* curDesc = (descriptor_t*)((char*)p - sizeof(descriptor_t));
  if (curDesc->magicNumber != 1984)
    return;

  //find pointers to right and left descriptor and end
  block_end_t* curEnd = (block_end_t*)((char*)p + curDesc->size);

  //  defragmentation
  //  check left block
  block_end_t* prevEnd = (block_end_t*)((char*)p + ((-1) * (int)(ADDITIONAL_BLOCK_SIZE)));
  if ((char*)prevEnd < (char*)s_memControl.begin || prevEnd->size == UNAVAILIBLE) {//  left block is not an option
    curDesc->next = s_memControl.list;
    curEnd->size = curDesc->size;
    s_memControl.list = curDesc;
  }
  else {// unite with left block
    descriptor_t* prevDesc = (descriptor_t*)((char*)p + ((-1) * (int)(ADDITIONAL_BLOCK_SIZE)) - prevEnd->size - sizeof(descriptor_t));
    prevDesc->size +=  ADDITIONAL_BLOCK_SIZE + curDesc->size;
    curEnd->size = prevDesc->size;
    curDesc = prevDesc;
  }
  //  check right block
  descriptor_t* nextDesc = (descriptor_t*)((char*)curEnd + sizeof(block_end_t));
  if ((char*)nextDesc < (char*)(s_memControl.begin + s_memControl.totalSize) && nextDesc->magicNumber == 1984) {
    block_end_t* nextEnd = (block_end_t*)((char*)nextDesc + sizeof(descriptor_t) + nextDesc->size);
    if(nextEnd->size != UNAVAILIBLE) {//if can unite
      descriptor_t** bufBlock = &s_memControl.list;
      curDesc->size += ADDITIONAL_BLOCK_SIZE + nextDesc->size;
      nextDesc->magicNumber = 0;
      nextEnd->size = curDesc->size;
      while (*bufBlock != NULL && (*bufBlock) != nextDesc)
        bufBlock = &(*bufBlock)->next;
      if (*bufBlock == nextDesc)
        *bufBlock = (*bufBlock)->next;
    }
  }
}

void memdone() {// You can implement memory leak checks here
  s_memControl.begin = NULL;
  s_memControl.totalSize = 0;
  s_memControl.list = NULL;
}