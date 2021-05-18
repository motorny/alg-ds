
#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <malloc.h>

#pragma warning (disable:4996)

#define ERROR_INIT 1
#define ERROR_MEMORY_LEAK 2
#define NOT_ERRORS 0

#define HAVE_RELATION 1
#define NOT_RELATION 0
typedef struct block_t {
	int size;
	struct block_t* next;
} block_t;

static int error_my = NOT_ERRORS; //переменная для передачи ошибок

static void* pHead = NULL;  //голова
static int wholeSize = 0; //сколько всего памяти мы взяли для осуществления локатора           
static block_t* startBlock = NULL; //указатель на место с которого начинаем искать память

// Init memory system with memory block pMemory.
int meminit(void* pMemory, int size);

// You can implement memory leak checks here
void memdone();

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, 0 otherwise
void* memalloc(int size);

// Free memory previously allocated by memalloc
void memfree(void* p);

// Return minimum size in bytes of the memory pool to allocate 0-bytes block
// use case:
// void *p   = 0;
// void *ptr = malloc(memgetminimumsize() + 1);
// meminit(ptr, memgetminimumsize() + 1)
// p = memalloc(1); // Success!
// memfree(p);
// memdone();
// free(ptr);
int memgetminimumsize();


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
int memgetblocksize();


#ifdef __cplusplus
}
#endif

#endif