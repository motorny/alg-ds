#include "../memallocator.h"
#include "../memallocator.c"

extern "C" {

void SetListStart(void* ptr) {
  s_memInfo.startList = (descriptor_t*)ptr;
}

void SetListEnd(void* ptr) {
  s_memInfo.endList = (descriptor_t*)ptr;
}

void SetBeforeLastAlloc(void* ptr) {
  s_memInfo.beforeLastAlloc = (descriptor_t*)ptr;
}

void InitNoCheck(void *pMemory, int size) {
  descriptor_t descr;

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
  *(int*)((char*)pMemory + size - sizeof(int)) = descr.blockSize;
}

}
