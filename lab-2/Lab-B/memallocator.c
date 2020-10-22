#include <stdlib.h>
#include <stdio.h>
#include "memallocator.h"

typedef struct descriptor_t {
  int size;
  struct descriptor_t* next;
  struct descriptor_t* prev;
} descriptor_t;

static struct {
  descriptor_t* descriptor;
  int totalSize;
  void* begin;
} s_memSystem = { (descriptor_t*)NULL, 0, NULL };

int memgetminimumsize() {
  return sizeof(descriptor_t) + sizeof(int);
}

int memgetblocksize() {
  return sizeof(descriptor_t) + sizeof(int);
}

int meminit(void* pMemory, int size) {
  if (!pMemory || size < memgetminimumsize()) {
    return 0;
  }
  else {
    s_memSystem.descriptor = (descriptor_t*)pMemory;
    s_memSystem.descriptor->next = NULL;
    s_memSystem.descriptor->prev = NULL;
    s_memSystem.descriptor->size = size;
    s_memSystem.totalSize = size;
    s_memSystem.begin = pMemory;
    *(int*)((char*)s_memSystem.descriptor + size - sizeof(int)) = size;
    return 1;
  }
}

void* memalloc(int size) {
  descriptor_t* currentBlock;
  descriptor_t* bestFit = NULL;
  descriptor_t* newBlock;
  void* result = NULL;
  if (s_memSystem.descriptor) {
    currentBlock = s_memSystem.descriptor;
    do {
      if (currentBlock->size >= (size + memgetblocksize())) {
        if (bestFit == NULL) {
          bestFit = currentBlock;
        }
        else if (bestFit->size > currentBlock->size) {
          bestFit = currentBlock;
        }
      }
      currentBlock = currentBlock->next;
    } while (currentBlock);
    if (bestFit) {
      if (bestFit->size > size + memgetblocksize() * 2) {
        newBlock = (descriptor_t*)((char*)bestFit + memgetblocksize() + size);
        newBlock->next = bestFit->next;
        newBlock->prev = bestFit->prev;
        newBlock->size = bestFit->size - memgetblocksize() - size;
        *(int*)((char*)newBlock + newBlock->size - sizeof(int)) = newBlock->size;
        if (bestFit->next) {
          bestFit->next->prev = newBlock;
        }
        if (bestFit->prev) {
          bestFit->prev->next = newBlock;
        }
        else {
          s_memSystem.descriptor = newBlock;
        }
        bestFit->size = bestFit->size - newBlock->size;
      }
      else {
        if (bestFit->next) {
          bestFit->next->prev = bestFit->prev;
        }
        if (bestFit->prev) {
          bestFit->prev->next = bestFit->next;
        }
        else {
          s_memSystem.descriptor = bestFit->next;
        }
      }
      bestFit->next = NULL;
      bestFit->prev = NULL;
      bestFit->size = -(bestFit->size);
      *(int*)((char*)bestFit + (-bestFit->size) - sizeof(int)) = bestFit->size;
      result = (void*)((char*)bestFit + sizeof(descriptor_t));
    }
  }
  return result;
}

void memfree(void* p) {
  descriptor_t* nextBlock;
  descriptor_t* prevBlock;
  descriptor_t* newBlock;

  if (p) {
    newBlock = (descriptor_t*)((char*)p - sizeof(descriptor_t));
    newBlock->prev = NULL;
    newBlock->size = -(newBlock->size);

    // Merge with prev
    if ((char*)newBlock != (char*)s_memSystem.begin) {
      if (*(int*)((char*)newBlock - sizeof(int)) > 0) {
        prevBlock = (descriptor_t*)((char*)newBlock - *(int*)((char*)newBlock - sizeof(int)));
        if (prevBlock->prev != NULL) {
          if (prevBlock->next != NULL) {
            prevBlock->next->prev = prevBlock->prev;
          }
          prevBlock->prev->next = prevBlock->next;
        }
        else if (prevBlock->next != NULL) {
          s_memSystem.descriptor = prevBlock->next;
          s_memSystem.descriptor->prev = NULL;
        }
        else {
          s_memSystem.descriptor = NULL;
        }
        prevBlock->next = NULL;
        prevBlock->prev = NULL;
        prevBlock->size += newBlock->size;
        newBlock = prevBlock;      
      }
    }
    // Merge with next
    if ((char*)newBlock + newBlock->size != (char*)s_memSystem.begin + s_memSystem.totalSize) {
      if (*(int*)((char*)newBlock + newBlock->size) > 0) {
        nextBlock = (descriptor_t*)((char*)newBlock + newBlock->size);
        if (nextBlock->prev != NULL) {
          if (nextBlock->next != NULL) {
            nextBlock->next->prev = nextBlock->prev;
          }
          nextBlock->prev->next = nextBlock->next;
        }
        else if (nextBlock->next != NULL) {
          s_memSystem.descriptor = nextBlock->next;
          s_memSystem.descriptor->prev = NULL;
        }
        else {
          s_memSystem.descriptor = NULL;
        }
        newBlock->size += nextBlock->size;
      }
    }
    if (s_memSystem.descriptor) {
      s_memSystem.descriptor->prev = newBlock;
      newBlock->next = s_memSystem.descriptor;
    }
    else {
      newBlock->next = NULL;
    }
    s_memSystem.descriptor = newBlock;
    *(int*)((char*)newBlock + newBlock->size - sizeof(int)) = newBlock->size;
  }
}

void memdone() {
  if (s_memSystem.descriptor == NULL) {
    fprintf(stderr, "Detected memory leaks\n");
  }
  else if (s_memSystem.totalSize != s_memSystem.descriptor->size) {
    fprintf(stderr, "Detected memory leaks\n");
  }
}