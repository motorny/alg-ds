#include "memallocator.h"

#define TRUE 1
#define FALSE 0

#define NULL 0

#define MAGIC 1488

typedef struct desc_t desc_t;
typedef unsigned char byte;

struct desc_t {
  desc_t *next, *prev;
  int size;
  int magicNum;
  char isFree;
};

typedef struct ender_t {
  int size;
}ender_t;

byte* gMemory = NULL;
int gMemSize = 0;

desc_t* freeSpace = NULL;

int meminit(void* pMemory, int size) {
  if (size < memgetminimumsize() || pMemory == NULL) {
    return FALSE;
  }

  gMemory = (byte*)pMemory;
  gMemSize = size;
  freeSpace = (desc_t*)pMemory;

  freeSpace->next = NULL;
  freeSpace->prev = NULL;
  freeSpace->size = size - sizeof(desc_t) - sizeof(ender_t);
  freeSpace->magicNum = MAGIC;
  freeSpace->isFree = TRUE;
  
  ((ender_t*)((byte*)freeSpace + freeSpace->size + sizeof(desc_t)))->size = freeSpace->size;
  return TRUE;
}

void memdone() {
  gMemory = NULL;
  gMemSize = 0;
  freeSpace = NULL;
}

int memgetblocksize() {
  return sizeof(desc_t) + sizeof(ender_t);
}

int memgetminimumsize() {
  return sizeof(desc_t) + sizeof(ender_t);
}

void memdeletelistelem(desc_t* Elem)
{
  if (Elem->prev != NULL)
    Elem->prev->next = Elem->next;
  else
    freeSpace = freeSpace->next;
  if (Elem->next != NULL)
    Elem->next->prev = Elem->prev;
}

void memdefragmentation(desc_t* middleD) {
  ender_t* prevE;
  desc_t* prevD;
  ender_t* middleE;
  desc_t* nextD;
  ender_t* nextE;
  if (middleD->magicNum != MAGIC)
    return;
  middleE = (ender_t*)((byte*)middleD + sizeof(desc_t) + middleD->size);
  if ((byte*)middleD - sizeof(ender_t) > gMemory)
  { 
    prevE = (ender_t*)((byte*)middleD - sizeof(ender_t));
    prevD = (desc_t*)((byte*)prevE - prevE->size - sizeof(desc_t));
  }
  else
  {
    prevE = NULL;
    prevD = NULL;
  }
  if ((byte*)middleE + sizeof(ender_t) < gMemory + gMemSize - 2)
  { 
    nextD = (desc_t*)((byte*)middleE + sizeof(ender_t));
    nextE = (ender_t*)((byte*)nextD + nextD->size +  sizeof(desc_t));
  }
  else
  {
    nextD = NULL;
    nextE = NULL;
  }
  if (nextD != NULL && nextD->magicNum == MAGIC && nextD->isFree) { //удаление next слияние с middle 
    memdeletelistelem(nextD);
    middleD->size += sizeof(ender_t) + sizeof(desc_t) + nextD->size;
    nextE->size = middleD->size;
    nextD->magicNum = 0;
    middleE = nextE;
  }
  if (prevD != NULL && prevD->magicNum == MAGIC && prevD->isFree) { //удаление middle и слияние с prev и ыыыыыыыыы все удаляется из списка свободного пространства
    memdeletelistelem(middleD);
    prevD->size += sizeof(ender_t) + sizeof(desc_t) + middleD->size;
    middleE->size = prevD->size;
    middleD->magicNum = 0;
    prevE = middleE;
  }
}

void* memalloc(int size) {
  if (gMemory == NULL || size <= 0 || freeSpace == NULL) {
    return NULL;
  }

  desc_t* tmpMemory = freeSpace;
  while (tmpMemory != NULL) {
    if (tmpMemory->size >= size) {
      if (tmpMemory->size > size + sizeof(desc_t) + sizeof(ender_t)) { //деление памяти 
        memdeletelistelem(tmpMemory);
        ender_t* firstEnd = (ender_t*)((byte*)tmpMemory + sizeof(desc_t) + size);
        firstEnd->size = size;
        desc_t* secondDesc = (desc_t*)((byte*)firstEnd + sizeof(ender_t));

        secondDesc->isFree = TRUE;
        secondDesc->magicNum = MAGIC;
        secondDesc->next = freeSpace;
        secondDesc->prev = NULL;
        secondDesc->size = tmpMemory->size - size - sizeof(ender_t) - sizeof(desc_t);
        if (freeSpace)
          freeSpace->prev = secondDesc;
        freeSpace = secondDesc;

        ender_t* secondEnd =(ender_t*)((byte*)secondDesc + sizeof(desc_t) + secondDesc->size);
        secondEnd->size = secondDesc->size;

        tmpMemory->isFree = FALSE;
        tmpMemory->magicNum = MAGIC;
        tmpMemory->next = NULL;
        tmpMemory->prev = NULL;
        tmpMemory->size = size;

        return (void*)((byte*)tmpMemory + sizeof(desc_t));
      }
      else { //выдать, что есть 
      //удаление их списка свободного пространства
        memdeletelistelem(tmpMemory);
        tmpMemory->isFree = FALSE;
        tmpMemory->next = NULL;
        tmpMemory->prev = NULL;
        return (void*)((byte*)tmpMemory + sizeof(desc_t));
      }
    }
    tmpMemory = tmpMemory->next;
  }
  return NULL;
}

void memfree(void* p) {
  if (p == NULL || 
  (byte*)p - gMemory < 0 ||
  (byte*)p - gMemory > gMemSize ||
  ((desc_t*)((byte*)p - sizeof(desc_t)))->magicNum != MAGIC) {
    return;
  }
  desc_t* myDesc = (desc_t*)((byte*)p - sizeof(desc_t));
  myDesc->isFree = TRUE;
  myDesc->next = freeSpace;
  myDesc->prev = NULL;
  if (freeSpace)
    freeSpace->prev = myDesc;
  freeSpace = myDesc; 
  memdefragmentation(myDesc);
}