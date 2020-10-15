#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memallocator.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)
// block descriptor type. blockSize < 0 - user is using block, blockSize > 0 - otherwise
typedef struct descriptor_t {
  int blockSize;
  struct descriptor_t *next;
} descriptor_t;
#pragma pack(pop)

// macro for block info. Block consist of: blockSize, next, data, blockSize
#define BLOCK_INFO_SIZE (int)(sizeof(descriptor_t) + sizeof(int))

// variable for memory manager data
static struct {
  void *memBlock;      // beginning of block
  descriptor_t
    *startList,        // start of list
    *endList,          // end of list
    *beforeLastAlloc;  // list element to start searching for block to allocate
  int totalSize;       // total block size
} s_memInfo;

#define MEM_SUCCESS 1
#define MEM_FAIL 0

// Init memory system with memory block pMemory.
int meminit(void *pMemory, int size) {
  descriptor_t descr;

  // check size and pointer
  if (size < memgetminimumsize() || pMemory == NULL)
    return MEM_FAIL;
  // fill global variable
  s_memInfo.beforeLastAlloc =
    s_memInfo.startList =
    (descriptor_t*)pMemory;
  s_memInfo.memBlock = pMemory;
  s_memInfo.endList = (descriptor_t*)((char*)pMemory + BLOCK_INFO_SIZE);
  s_memInfo.totalSize = size;

  // create unusable block with 0 size
  descr.blockSize = 0;
  descr.next = (descriptor_t *)((char*)pMemory + BLOCK_INFO_SIZE);
  memcpy(pMemory, &descr, sizeof(descr));
  *(int*)(s_memInfo.startList + 1) = 0;

  // mark other part of memory block
  descr.blockSize = size - 2 * BLOCK_INFO_SIZE;
  descr.next = (descriptor_t*)pMemory;
  memcpy((char*)pMemory + BLOCK_INFO_SIZE, &descr, sizeof(descr));
  memset((char*)pMemory + BLOCK_INFO_SIZE + sizeof(descr), 0, size - 2 * BLOCK_INFO_SIZE);
  *(int*)((char*)pMemory + size - sizeof(int)) = descr.blockSize;

  return MEM_SUCCESS;
}

// You can implement memory leak checks here
void memdone() {
  // in the end list must have 2 nodes, that contains all memory block
  int size;

  // check is manager initizlised
  if (s_memInfo.memBlock == NULL)
    return;

  // evaluate size
  size = s_memInfo.startList->blockSize + s_memInfo.startList->next->blockSize + 2 * BLOCK_INFO_SIZE;
  if (size != s_memInfo.totalSize)
    fprintf(stderr, "Memory leaks");
  // make manager uninitialized
  memset(s_memInfo.memBlock, 0, s_memInfo.totalSize);
  memset(&s_memInfo, 0, sizeof(s_memInfo));
}

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, 0 otherwise
void* memalloc(int size) {
  descriptor_t *beforeNewAlloc, *newAlloc;

  // check memory manager
  if (s_memInfo.memBlock == NULL)
    return NULL;
  // check size
  if (size <= 0)
    return NULL;

  beforeNewAlloc = s_memInfo.beforeLastAlloc;
  newAlloc = beforeNewAlloc->next;

  // search suitable block
  while (newAlloc->blockSize < size) {
    beforeNewAlloc = newAlloc;
    newAlloc = newAlloc->next;
    // root if not find
    if (beforeNewAlloc == s_memInfo.beforeLastAlloc)
      return NULL;
  }
  s_memInfo.beforeLastAlloc = beforeNewAlloc;

  // root if block splits
  if (newAlloc->blockSize > size + BLOCK_INFO_SIZE) {
    descriptor_t *splitedBlock = (descriptor_t*)((char*)newAlloc + size + BLOCK_INFO_SIZE);

    // set global values
    if (s_memInfo.startList == newAlloc)
      s_memInfo.startList = splitedBlock;
    if (s_memInfo.endList == newAlloc)
      s_memInfo.endList = splitedBlock;

    // fill splited block
    beforeNewAlloc->next = splitedBlock;
    splitedBlock->blockSize = newAlloc->blockSize - BLOCK_INFO_SIZE - size;
    splitedBlock->next = newAlloc->next;
    *((int*)((char*)newAlloc + sizeof(descriptor_t) + newAlloc->blockSize)) = splitedBlock->blockSize;

    // fill allocated block
    newAlloc->next = NULL;
    newAlloc->blockSize = -size;
    *((int*)splitedBlock - 1) = -size;

    return newAlloc + 1;
  }

  // root if block doesn't split
  // set global values
  if (s_memInfo.startList == newAlloc)
    s_memInfo.startList = newAlloc->next;
  if (s_memInfo.endList == newAlloc)
    s_memInfo.endList = beforeNewAlloc;
  // pop block from list
  beforeNewAlloc->next = newAlloc->next;
  // fill new allocation block
  newAlloc->next = NULL;
  newAlloc->blockSize = -newAlloc->blockSize;
  *((int*)((char*)newAlloc + sizeof(descriptor_t) - newAlloc->blockSize)) = newAlloc->blockSize;
  return newAlloc + 1;
}

// Free memory previously allocated by memalloc
void memfree(void *p) {
  descriptor_t *blockDescr;

  // check pointer valid
  if ((char*)p < (char*)s_memInfo.memBlock + BLOCK_INFO_SIZE ||
    (char*)p > (char*)s_memInfo.memBlock + s_memInfo.totalSize - sizeof(int))
    return;

  blockDescr = (descriptor_t*)p - 1;

  if (blockDescr->blockSize > 0)
    return;
  // root to unite with forward block
  if ((char*)p - (char*)s_memInfo.memBlock - blockDescr->blockSize + (int)sizeof(int) < s_memInfo.totalSize &&
    ((descriptor_t*)((char*)p - blockDescr->blockSize + sizeof(int)))->blockSize > 0) {
    descriptor_t
      *prev = s_memInfo.endList,
      *next = s_memInfo.startList,
      *realNext = (descriptor_t*)((char*)p + sizeof(int) - blockDescr->blockSize);

    // find forward block in list
    do {
      prev = next;
      next = next->next;
    } while (next != realNext);
    prev->next = next->next;
    blockDescr->blockSize -= next->blockSize + BLOCK_INFO_SIZE;
    // replace forward block
    if (s_memInfo.endList == next)
      s_memInfo.endList = prev;
    if (s_memInfo.startList == next)
      s_memInfo.startList = next->next;
    if (s_memInfo.beforeLastAlloc == next)
      s_memInfo.beforeLastAlloc = next->next;
  }
  // root to find with backward block
  if (*(int*)((char*)p - BLOCK_INFO_SIZE) > 0) {
    // include block in backward block
    descriptor_t *descr = (descriptor_t*)((char*)p - sizeof(descriptor_t) - BLOCK_INFO_SIZE - *(int*)((char*)p - BLOCK_INFO_SIZE));
    descr->blockSize -= blockDescr->blockSize - BLOCK_INFO_SIZE;
    *((int*)((char*)p - blockDescr->blockSize)) = descr->blockSize;
    memset(descr + 1, 0, descr->blockSize);
    return;
  }

  // fill block to place it
  blockDescr->next = s_memInfo.startList;
  blockDescr->blockSize = -blockDescr->blockSize;
  *(int*)((char*)blockDescr + blockDescr->blockSize + sizeof(descriptor_t)) = blockDescr->blockSize;
  memset(blockDescr + 1, 0, blockDescr->blockSize);
  s_memInfo.endList->next = blockDescr;
  s_memInfo.startList = blockDescr;
}

// Return minimum size in bytes of the memory pool to allocate 0-bytes block
// use case:
// void *p   = 0;
// void *ptr = malloc(memgetminimumsize() + 1);
// meminit(ptr, memgetminimumsize() + 1)
// p = memalloc(1); // Success!
// memfree(p);
// memdone();
// free(ptr);
int memgetminimumsize() {
  return 2 * BLOCK_INFO_SIZE;
}

// Returns size in bytes of additional information per allocation
// use case:
// void *p1 = 0, *p2 = 0;
// int  memsize = memgetminimumsize() + memgetblocksize() + 2;
// void *ptr = malloc(memsize);
// meminit(ptr, memsize())
// p1 = memalloc(1); // Success!
// p2 = memalloc(1); // Success!
// memfree(p2);
// memfree(p1);
// memdone();
// free(ptr);
int memgetblocksize() {
  return BLOCK_INFO_SIZE;
}

#ifdef __cplusplus
}
#endif
