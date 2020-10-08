#include "pch.h"
#include "framework.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "memallocator.h"

#define TRUE 1
#define FALSE 0

// Header type
typedef struct header_t {
  struct header_t* next;
  struct header_t* prev;
  int size;
} header_t;

// Information about memory system and its current state
static struct {
  header_t* buffer;
  header_t* cur;
  int totalSize;
} memSys = { (header_t*)NULL, (header_t*)NULL, 0 };

// Return minimum size in bytes of the memory pool to allocate 0-bytes block
int memgetminimumsize(void) {
  return 2 * (sizeof(header_t) + sizeof(int));
}

// Returns size in bytes of additional information per allocation
int memgetblocksize(void) {
  return sizeof(header_t) + sizeof(int);
}

// Init memory system with memory block pMemory
int meminit(void* buf, int size) {
  int minsize = memgetminimumsize();
  int addBlockSize = memgetblocksize();

  if (!buf || size < minsize)
    return FALSE;
  else {
    // Dummy block is used as a sign of the start of the buffer
    memSys.buffer = (header_t*)buf;
    memSys.totalSize = size;
    memSys.buffer->next = (header_t*)((char*)buf + addBlockSize);
    memSys.buffer->prev = (header_t*)((char*)buf + addBlockSize);
    memSys.buffer->size = 0;
    *(int*)(memSys.buffer + 1) = 0;
    // Real first element
    memSys.buffer->next->next = memSys.buffer;
    memSys.buffer->next->prev = memSys.buffer;
    memSys.buffer->next->size = size - minsize;
    *(int*)((char*)buf + size - sizeof(int)) = memSys.buffer->next->size;
    memSys.cur = memSys.buffer->next;
    return TRUE;
  }
}

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, NULL otherwise
void* memalloc(int size) {
  header_t* node;
  header_t* newNode;
  void* res = NULL;
  int addBlockSize = memgetblocksize();

  if (memSys.buffer) {
    node = memSys.cur;
    do {
      if (node->size < size) {
        node = node->next;
      }
      else if (node->size < size + addBlockSize) {
        // Don't add new header
        res = (void*)(node + 1);
        memset(res, 0, node->size);
        node->prev->next = node->next;
        node->next->prev = node->prev;
        memSys.cur = node->next;
        node->next = NULL;

        *(int*)((char*)(node + 1) + node->size) = node->size;

        break;
      }
      else {
        // Add new header
        newNode = (header_t*)((char*)node + size + addBlockSize);

        newNode->prev = node->prev;
        newNode->next = node->next;
        newNode->next->prev = newNode;
        newNode->prev->next = newNode;
        node->next = NULL;

        newNode->size = node->size - size - addBlockSize;
        *(int*)((char*)(newNode + 1) + newNode->size) = newNode->size;

        node->size = size;
        *(int*)((char*)(node + 1) + size) = size;

        res = (void*)(node + 1);
        memset(res, 0, size);
        memSys.cur = newNode;
        break;
      }
    } while (node != memSys.cur);
  }

  return res;
}

// Free memory previously allocated by memalloc
void memfree(void* pointer) {
  int addBlockSize = memgetblocksize();
  header_t* node;
  header_t* nextNode;
  header_t* prevNode;
  header_t* end = (header_t*)((char*)memSys.buffer + memSys.totalSize);

  if (pointer != NULL) {
    node = (header_t*)((char*)pointer - sizeof(header_t));
    nextNode = (header_t*)((char*)pointer + node->size + sizeof(int));
    prevNode = (header_t*)((char*)node - addBlockSize - *(int*)((char*)pointer - addBlockSize));

    // Merge with next
    if (nextNode != end && nextNode->next != NULL) {
      node->size += nextNode->size + addBlockSize;
      if (nextNode == memSys.cur)
        memSys.cur = nextNode->next;
      nextNode->prev->next = nextNode->next;
      nextNode->next->prev = nextNode->prev;
      *(int*)((char*)(node + 1) + node->size) = node->size;
    }
    // Merge with prev
    if (prevNode != memSys.buffer && prevNode->next != NULL) {
      prevNode->size += node->size + addBlockSize;
      if (node == memSys.cur)
        memSys.cur = prevNode;
      *(int*)((char*)(prevNode + 1) + prevNode->size) = prevNode->size;

      return;
    }
    // Add in list
    node->next = memSys.buffer->next;
    memSys.buffer->next->prev = node;
    node->prev = memSys.buffer;
    memSys.buffer->next = node;
  }
}

// Check memory leak
void memdone(void) {
  header_t* node;
  int minsize = memgetminimumsize();

  node = memSys.buffer->next;
  if (memSys.totalSize != node->size + minsize) {
    fprintf(stderr, "Detected memory leaks\n");
  }
}