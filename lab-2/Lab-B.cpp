#ifdef __cplusplus
extern "C" {
#endif

#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#define ABS(x) ((x)>=0?(x):(-x))
#define ONE_DESCRIPTOR 1 //for pointer arithmetic

enum {
  FAIL = 0,
  SUCCESS = 1,
};

enum {
  NO_MATCH = 0,
  FIRST_MATCH = 1,
  SECOND_MATCH = 2,
};

enum {
  NO_LEAKS = 0,
  LEAKS = 1,
};

//descriptor for every block
typedef struct descriptor_t {
  int size;
  struct descriptor_t* next;
} descriptor_t;

//memory system for the whole block
typedef struct {
  descriptor_t* descriptor1st; //1st descriptor
} mSystem_t;

mSystem_t mSystem = {(descriptor_t*)NULL};

int memgetminimumsize() {
  return sizeof(descriptor_t);
}

int memgetblocksize() {
  return sizeof(descriptor_t);
}

int meminit(void* pMemory, int size) { 
  if (!pMemory || size<=memgetminimumsize()) 
    return FAIL;
  descriptor_t descrip;
  descrip.next = NULL;
  descrip.size = -(size-memgetminimumsize()); //negative size means that block is free
  *((descriptor_t*)pMemory) = descrip; //put descriptor at the beggining of block
  mSystem.descriptor1st = (descriptor_t*)pMemory; //push pointer to memory into memory manager
  return SUCCESS;
}

void* memalloc(int size) {
  if (size <= 0 || !mSystem.descriptor1st)
    return NULL;

  void* requiredPtr = NULL;
  int matchNumber = NO_MATCH;//match in blocks. Need second suiting block
  descriptor_t* desc = mSystem.descriptor1st, *desc1=NULL,*newdesc=NULL, *firstfitdesc=NULL;
  int blockprevsize;
  
  while(desc){
    if (desc->size <0 && ABS(desc->size) >= size) { //match, negative size means empty block

      if (matchNumber == NO_MATCH) {
        matchNumber = FIRST_MATCH;
        firstfitdesc = desc;
      }

      else if (matchNumber == FIRST_MATCH) {
        matchNumber = SECOND_MATCH;
        break;
      }
    }
    desc1 = desc;
    desc = desc->next;
  }

  if (matchNumber) {//if match, return it

    //desc1 - descriptor of required memory, newdesc - next descriptor
    if (matchNumber == FIRST_MATCH)
      desc1 = firstfitdesc; //if first match
    else //second match
      desc1 = desc;

    blockprevsize = -(desc1->size);
    requiredPtr = (void*)(desc1 + ONE_DESCRIPTOR); //start of descriptor + 1 descriptor
    desc1->size = size;

    //put next descriptor after descriptor and given memory if enough memory for it
    if (blockprevsize - size > memgetblocksize()) {
      newdesc = (descriptor_t*)((char*)requiredPtr + size);
      newdesc->next = desc1->next; //NULL or valid descriptor
      newdesc->size = -(blockprevsize - size - memgetblocksize());
      desc1->next = newdesc;
    }
    else  //not enough memory for new descriptor, so remember not used bytes
      desc1->size = blockprevsize; // >0 because descriptor is used

    return requiredPtr;
  }
  else //no match, cannot give memory
    return NULL;
}

void memfree(void* p) {

  //need to find descriptor that refers to 'p'
  descriptor_t* currentDesc = mSystem.descriptor1st, *prevDesc = NULL, *nextDesc = NULL;
  while (currentDesc) {

    if ((char*)p - (char*)(currentDesc + ONE_DESCRIPTOR) > 0) {
      prevDesc = currentDesc;
      currentDesc = currentDesc->next;
    }

    else if ((char*)(currentDesc + ONE_DESCRIPTOR) == (char*)p)//found
      break;

    else //went away from pointer, so pointer is invalid
      return;
  }
  
  if (!currentDesc || currentDesc->size < 0) //pointer is free
    return;
  
  currentDesc->size = -currentDesc->size; //size is negative, so memory is free

  //check if left and right neibours are free. If free, merge it into one big block
  if (prevDesc && prevDesc->size < 0) { //if prevDesc exists, check if it free
   
    //free block
    prevDesc->size = -(ABS(prevDesc->size) + memgetblocksize() + ABS(currentDesc->size));
                    //previous block's size   next descriptor     next block's size
    prevDesc->next = currentDesc->next;
  }

  nextDesc = currentDesc->next;
  if (nextDesc && nextDesc->size < 0) { //if nextDesc exists and free

    //if desc was merged with prevDesc, should merge it with nextDesc from begin of prevDesc
    if (prevDesc && prevDesc->size < 0)
      currentDesc = prevDesc;

    //free this block
    currentDesc->size = -(ABS(currentDesc->size) + memgetblocksize() + ABS(nextDesc->size));
            //previous block's size   next descriptor     next block's size
    currentDesc->next = nextDesc->next;    
  }
}

void memdone() {

  descriptor_t* desc = mSystem.descriptor1st;
  int leaks=NO_LEAKS; 
  while (desc) {

    if (desc->size > 0) {//some memory is not empty

      if (leaks == NO_LEAKS) {
        leaks = LEAKS;
        printf("\nDetected memory leaks!\n");
        printf("at %p, %i bytes long\n", desc, desc->size);
      }

      else //leaks == LEAKS
        printf("at %p, %i bytes long\n", desc, desc->size);
    }   
    desc = desc->next;
  }
}

#ifdef __cplusplus
}
#endif