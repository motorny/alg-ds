#include <malloc.h>
#include <stdio.h>
#include "memallocator.h"

#define MEM_SUCCESS 1
#define MEM_FAIL 0

//#pragma pack(push, 1)
typedef struct block_t {
    int size;
    struct block_t* next;
    int validation;
} block_t;
//#pragma pack(pop)

void* pMemoryHead = NULL;
int fullSize = 0;
block_t* pStartBlock = NULL;

// Init memory system with memory block pMemory.
int meminit(void* pMemory, int size) {
    if (pMemory == NULL || size <= 0)
        return 1;

    pMemoryHead = pMemory;
    pStartBlock = (block_t*)pMemoryHead;
    fullSize = size;

    pStartBlock->next = NULL;
    pStartBlock->size = fullSize - memgetblocksize();
    *((int*)((char*)pMemoryHead + fullSize - sizeof(int))) = pStartBlock->size;

    return 0;
}

// You can implement memory leak checks here
void memdone() {
    block_t* block = (block_t*)pMemoryHead;
    while (block) {
        if (block->validation == MEM_FAIL)
            block->validation = MEM_SUCCESS;
        block = block->next;
    }
};

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, 0 otherwise
void* memalloc(int size) {
    block_t* pFreeBlock = pStartBlock;
    block_t** pPrevBlockToNext = &pStartBlock; // ��������� �� ���������� � ������� ��������� ������ ���������� �����
    void* pAlloc = NULL;

    if (size < 0)
        return NULL;

    // ����� ���������� ����� � ������ �������� 
    while (pFreeBlock ) {
        if (pFreeBlock->size >= size) break;
        pPrevBlockToNext = &pFreeBlock->next;
        pFreeBlock = pFreeBlock->next;
    }

    if (pFreeBlock == NULL)
        return NULL;

    // ��������� �� ���������� ������ 
    pAlloc = (char*)pFreeBlock + sizeof(block_t);

    // �������� ��� ������ ����� ��� ���������� ������ � �����
    if (pFreeBlock->size >= memgetblocksize() + size) {
        block_t* pNextFreeBlock = (block_t*)((char*)pFreeBlock + memgetblocksize() + size);
        pNextFreeBlock->size = pFreeBlock->size - (memgetblocksize() + size);
        *((int*)((char*)pNextFreeBlock + pNextFreeBlock->size + sizeof(block_t))) = pNextFreeBlock->size;
        pNextFreeBlock->next = pFreeBlock->next;
        *pPrevBlockToNext = pNextFreeBlock;

        pFreeBlock->size = size;
        *((int*)((char*)pFreeBlock + pFreeBlock->size + sizeof(block_t))) = pFreeBlock->size;
    }
    else {
        *pPrevBlockToNext = pFreeBlock->next;
    }

    pFreeBlock->next = NULL;

    return pAlloc;
}

// Free memory previously allocated by memalloc
void memfree(void* p) {
    int united = 0;
    block_t* pBlock;

    if (p == NULL || (char*)p - sizeof(block_t) < (char*)pMemoryHead || (char*)p > (char*)pMemoryHead + fullSize)
        return;

    pBlock = (block_t*)((char*)p - sizeof(block_t));

    // ����������� � ����� ������
    if ((char*)pBlock >= (char*)pMemoryHead + memgetblocksize()) {
        block_t* pPrevBlock = (block_t*)((char*)pBlock - memgetblocksize() - *((int*)((char*)pBlock - sizeof(int))));
        block_t* pFindBlock = pStartBlock;

        while (pFindBlock != NULL) {
            if (pFindBlock == pPrevBlock) break;
            pFindBlock = pFindBlock->next;
        }

        if (pFindBlock != NULL) {
            pPrevBlock->size += memgetblocksize() + pBlock->size;
            *((int*)((char*)pPrevBlock + pPrevBlock->size + sizeof(block_t))) = pPrevBlock->size;
            pBlock = pPrevBlock;
            united = 1;
        }
    }

    // ����������� � ������ ������
    if (pBlock + pBlock->size + memgetblocksize() + memgetblocksize() >= (block_t*)pMemoryHead + fullSize) {
        block_t* pNextBlock = (block_t*)((char*)pBlock + pBlock->size + memgetblocksize());
        block_t** pFindBlock = &pStartBlock;

        while (*pFindBlock != NULL) {
            if (*pFindBlock == pNextBlock) break;
            pFindBlock = &(*pFindBlock)->next;
        }

        if (*pFindBlock != NULL) {
            if (united) {
                *pFindBlock = pNextBlock->next;
            }
            else {
                *pFindBlock = pBlock;
            }
            pBlock->size += memgetblocksize() + pNextBlock->size;
            *((int*)((char*)pBlock + pBlock->size + memgetblocksize())) = pBlock->size;

            united = 1;
        }
    }

    if (united == 0) {
        pStartBlock = pBlock;
    }
}

// Return minimum size in bytes of the memory pool to allocate 0-bytes block
int memgetminimumsize() {
    return (int)sizeof(block_t) + sizeof(int);
}

// Returns size in bytes of additional information per allocation
int memgetblocksize() {
    return (int)sizeof(block_t) + sizeof(int);
}