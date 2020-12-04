#include <stdio.h>
#include "memallocator.h"

#define MEMORY_INITIALIZE_SUCCESS 1
#define MEMORY_INITIALIZE_FAILED 0
#define COULD_NOT_FIND_SUITABLE_BLOCK NULL

int FULLSIZE;
void* FIRST;

typedef enum{
  FALSE,
  TRUE
} bool_t;

typedef struct memBlock{
  bool_t boolEmty;
  struct memBlock* nextBlock;
  int size;
} memBlock;


int memgetminimumsize(){
  return sizeof(memBlock);
}
int memgetblocksize(){
  return sizeof(memBlock);
}

/////////////////////////////////////
int meminit(void* pMemory, int size){
  memBlock* block = NULL;

  if ((pMemory == NULL) || (size < memgetminimumsize())) {
    return MEMORY_INITIALIZE_FAILED;
  }

  FIRST = pMemory;
  FULLSIZE = size;
  block = (memBlock*)FIRST;
  block->size = FULLSIZE;
  block->boolEmty = TRUE;
  block->nextBlock = NULL;
  return MEMORY_INITIALIZE_SUCCESS;
}

memBlock* findBlock(int size){
  memBlock* block = (memBlock*)FIRST;
  while (block != NULL){
    if ((block->boolEmty == TRUE) && ((block->size) >= size)){
      return block;
    }
    block = block->nextBlock;
  }
  return COULD_NOT_FIND_SUITABLE_BLOCK;
}

/////////////////////////////////////
void* memalloc(int size){
  memBlock* block = NULL;

  if (size <= 0){
    return NULL;
  }

  size = size + memgetblocksize();

  block = findBlock(size);
  if (block == NULL){
    return COULD_NOT_FIND_SUITABLE_BLOCK;
  }

  block->boolEmty = FALSE;

  if ((block->size - size) <= memgetblocksize()) {    //если размер оставшейся памяти в найденом блоке после заполнения меньше, чем минимальный блок, то
    return (void*)((char*)block + memgetblocksize()); //возвращаем указатель на блок со смещением в размер минимального блока
  }

  int freeSpaceSize = block->size - size;
  block->size = size;
  memBlock* next = (memBlock*)((char*)block + size);
  next->boolEmty = TRUE;
  next->size = freeSpaceSize;
  next->nextBlock = NULL;
  block->nextBlock = next;
  return (void*)((char*)block + memgetblocksize());
}

/////////////////////////////////////
void memfree(void* p){
  if ((p == NULL) || (p == FIRST)){
    return;
  }
  else{
    p = (memBlock*)((char*)p - memgetblocksize());
  }

  memBlock* free = (memBlock*)p;
  memBlock* previous = (memBlock*)FIRST;
  memBlock* next = NULL;
  memBlock* tmp = NULL;

  tmp = (memBlock*)FIRST;
  while ((tmp != free) && (tmp != NULL)){
    tmp = tmp->nextBlock;
  }

  if ((tmp == NULL) || (free->boolEmty == TRUE)){
    return;
  }

  while ((previous != free) && (previous->nextBlock != free)){
    previous = previous->nextBlock;
  }

  if (free->nextBlock != NULL){
    next = free->nextBlock;
  }

  if ((next != NULL) && (next->boolEmty == TRUE)){
    tmp = next;
    free->nextBlock = next->nextBlock;
    free->size = free->size + next->size;
    tmp->size = -1;
    tmp->boolEmty = TRUE;
    tmp->nextBlock = NULL;
  }

  if ((previous != free) && (previous->boolEmty == TRUE)){
    tmp = free;
    previous->nextBlock = free->nextBlock;
    previous->size = previous->size + free->size;
    tmp->size = -1;
    tmp->boolEmty = TRUE;
    tmp->nextBlock = NULL;
    free = previous;
  }
  free->boolEmty = TRUE;
}

/////////////////////////////////////
void memdone(){
  memBlock* block = (memBlock*)FIRST;
  while (block != NULL){
    if (block->boolEmty == FALSE) {
      block->boolEmty = TRUE;
    }
    block = block->nextBlock;
  }
}