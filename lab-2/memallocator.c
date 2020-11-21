#include <malloc.h>
#include <stdio.h>
#include "memallocator.h"

#define MEM_SUCCESS 0
#define MEM_FAIL 1

typedef struct block_t {
  int size;
  struct block_t *next;
} block_t;

void *pMemHead = NULL;
int memSize = 0;
block_t *pStartBlock = NULL;

int meminit(void *pMemory, int size) {
    if ( pMemory == NULL || size <= 0 )
        return MEM_FAIL;

    pMemHead = pMemory;
    pStartBlock = (block_t *)pMemHead;
    memSize = size;

    pStartBlock->next = NULL;
    pStartBlock->size = memSize - memgetblocksize();
    *((int *) ((char *) pMemHead + memSize - sizeof(int))) = pStartBlock->size;
    
    return MEM_SUCCESS;
}

void memdone() {
    void *pMemoryEnd;
    block_t *pPrevFree = pStartBlock, *pCheckBlock = (block_t *) pMemHead;

    if ( pMemHead == NULL || memSize <= 0 || pStartBlock != NULL && memSize == pStartBlock->size + memgetblocksize() )
        return;
    
    pMemoryEnd = (char *) pMemHead + memSize;
    if( pPrevFree != NULL)
        while ( pPrevFree->next != NULL ) {
            pPrevFree = pPrevFree->next;
        }

    printf("Detected memory leaks!\n");
}

void *memalloc(int size) {
    block_t *pFreeBlock = pStartBlock, *pTempFreeBlock;
    block_t **ppNextBlock = &pStartBlock;
    void *pAlloc = NULL;

    if ( size < 0 || pMemHead == NULL || pStartBlock == NULL )
        return NULL;

    while ( pFreeBlock != NULL ) {
        if ( pFreeBlock->size >= size ) break;
        ppNextBlock = &pFreeBlock->next;
        pFreeBlock = pFreeBlock->next;
    }

    if ( pFreeBlock == NULL )
        return NULL;
    
    pTempFreeBlock = pFreeBlock;

    pFreeBlock = pFreeBlock->next;
    while ( pFreeBlock != NULL ) {
        if ( pFreeBlock->size >= size ) break;
        ppNextBlock = &pFreeBlock->next;
        pFreeBlock = pFreeBlock->next;
    }

    if ( pFreeBlock == NULL )
        pFreeBlock = pTempFreeBlock;

    pAlloc = (char *) pFreeBlock + sizeof(block_t);

    if ( pFreeBlock->size >= memgetblocksize() + size ) {
        block_t *pNextFreeBlock = (block_t *)((char *)pFreeBlock + memgetblocksize() + size);
        pNextFreeBlock->size = pFreeBlock->size - (memgetblocksize() + size);
        *((int *) ((char *) pNextFreeBlock + pNextFreeBlock->size + sizeof(block_t))) = pNextFreeBlock->size;
        pNextFreeBlock->next = pFreeBlock->next;
        *ppNextBlock = pNextFreeBlock;

        pFreeBlock->size = size;
        *((int *) ((char *) pFreeBlock + pFreeBlock->size + sizeof(block_t))) = pFreeBlock->size;
    }
    else {
        *ppNextBlock = pFreeBlock->next;
    }

    pFreeBlock->next = NULL;

    return pAlloc;
}

void memfree(void *p) {
    int united = 0;
    block_t *pBlock;

    if ( p == NULL || (char *)p - sizeof(block_t) < (char *) pMemHead || (char *) p > (char *)pMemHead + memSize )
        return;

    pBlock = (block_t *)((char *) p - sizeof(block_t));

    if ( (char *) pBlock >= (char *) pMemHead + memgetblocksize() ) {
        block_t *pPrevBlock = (block_t *) ((char *) pBlock - memgetblocksize() - *((int *) ((char *) pBlock - sizeof(int))));
        block_t *pFindBlock = pStartBlock;

        while ( pFindBlock != NULL ) {
            if ( pFindBlock == pPrevBlock ) break;
            pFindBlock = pFindBlock->next;
        }

        if ( pFindBlock != NULL ) {
            pPrevBlock->size += memgetblocksize() + pBlock->size;
            *((int *) ((char *) pPrevBlock + pPrevBlock->size + sizeof(block_t))) = pPrevBlock->size;
            pBlock = pPrevBlock;
            united = 1;
        }
    }

    if ( pBlock + pBlock->size + memgetblocksize() + memgetblocksize() >= (block_t *) pMemHead + memSize ) {
        block_t *pNextBlock = (block_t *) ((char *)pBlock + pBlock->size + memgetblocksize());
        block_t **pFindBlock = &pStartBlock;

        while ( *pFindBlock != NULL ) {
            if ( *pFindBlock == pNextBlock ) break;
            pFindBlock = &(*pFindBlock)->next;
        }

        if ( *pFindBlock != NULL ) {
            if ( united ) {
                *pFindBlock = pNextBlock->next;
            }
            else {
                *pFindBlock = pBlock;
            }
            pBlock->size += memgetblocksize() + pNextBlock->size;
            *((int *) ((char *) pBlock + pBlock->size + memgetblocksize())) = pBlock->size;

            united = 1;
        }
    }

    if ( united == 0 ) {
        pStartBlock = pBlock;
    }
}

int memgetminimumsize() {
    return (int) sizeof(block_t) + sizeof(int);
}

int memgetblocksize() {
    return (int) sizeof(block_t) + sizeof(int);
}