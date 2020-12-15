#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FAIL -1
#define SUCCESS 1

typedef struct DESCRIPTOR {
  int size;
  struct DESCRIPTOR* next;
} DESCRIPTOR;

typedef struct {
  DESCRIPTOR* descriptor1st;
} mSystem_t;

mSystem_t mSystem = {(DESCRIPTOR*)NULL};

int memgetminimumsize() {
  return sizeof(DESCRIPTOR);
}

int memgetblocksize() {
  return sizeof(DESCRIPTOR);
}

int meminit(void* pMemory, int size) { 
  if (pMemory == NULL || size <= memgetminimumsize())
  {
    return FAIL;
  }
  DESCRIPTOR desc;
  desc.next = NULL;
  desc.size = -(size-memgetminimumsize());
  *((DESCRIPTOR*)pMemory) = desc;
  mSystem.descriptor1st = (DESCRIPTOR*)pMemory;
  return SUCCESS;
}

void* memalloc(int size) {
  if (size <= 0 || mSystem.descriptor1st == NULL)
  {
    return NULL;
  }
  void* requiredPtr = NULL;
  int match = 0;
  DESCRIPTOR* desc = mSystem.descriptor1st,*newDesc=NULL;
  int prevSizeBlock;
  while(desc)
  {
    if (desc->size <0 && abs(desc->size) >= size) 
    { 
      match = 1;
      break;
    }
    desc = desc->next;
  }

  if (match) {
    prevSizeBlock = -(desc->size);
    requiredPtr = (void*)(desc + 1); 
    desc->size = size;
    if (prevSizeBlock - size > memgetblocksize()) {
      newDesc = (DESCRIPTOR*)((char*)requiredPtr + size);
      newDesc->next = desc->next; 
      newDesc->size = -(prevSizeBlock - size - memgetblocksize());
      desc->next = newDesc;
    }
    else
    {
        desc->size = prevSizeBlock;
    }
    return requiredPtr;
  }
  else 
    return NULL;
}

void memfree(void* p) 
{
  DESCRIPTOR* currentDesc = mSystem.descriptor1st, *prevDesc = NULL, *nextDesc = NULL;
  while (currentDesc) 
  {

    if ((char*)p - (char*)(currentDesc + 1) > 0) 
    {
      prevDesc = currentDesc;
      currentDesc = currentDesc->next;
    }
    else if ((char*)(currentDesc + 1) == (char*)p)
      break;
    else 
      return;
  }
  
  if (!currentDesc || currentDesc->size < 0) 
    return;
  
  currentDesc->size = -currentDesc->size; 

  if (prevDesc && prevDesc->size < 0) 
  { 
    prevDesc->size = -(abs(prevDesc->size) + memgetblocksize() + abs(currentDesc->size));
    prevDesc->next = currentDesc->next;
  }

  nextDesc = currentDesc->next;
  if (nextDesc && nextDesc->size < 0) 
  {
    if (prevDesc && prevDesc->size < 0)
    {
        currentDesc = prevDesc;
    } 
    currentDesc->size = -(abs(currentDesc->size) + memgetblocksize() + abs(nextDesc->size));
    currentDesc->next = nextDesc->next;    
  }
}

void memdone()
{
    mSystem = { (DESCRIPTOR*)NULL };
}