#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct memory_block_t {
    int size, isFree;
    struct memory_block_t* next, * prev;
} memory_block_t;

typedef struct memory_block_end_t {
    int size;
} memory_block_end_t;

enum is_free_t {
    NOT_FREE,
    FREE
};

char* memory = NULL;
memory_block_t* memFirst = NULL;
int memSize = 0;

int memgetminimumsize() {
    return sizeof(memory_block_t) + sizeof(memory_block_end_t);
}

int memgetblocksize() {
    return sizeof(memory_block_t) + sizeof(memory_block_end_t);
}

int meminit(void* pMemory, int size) {
    int memMinimumSize = memgetminimumsize(), memBlockSize = memgetblocksize();
    if (!pMemory || size < memMinimumSize)
        return 0;

    memory = (char*)pMemory;
    memSize = size;
    memFirst = (memory_block_t*)pMemory;
    memFirst->next = NULL;
    memFirst->prev = NULL;
    memFirst->size = size - memBlockSize;
    memFirst->isFree = FREE;
    ((memory_block_end_t*)((char*)memFirst + memFirst->size + sizeof(memory_block_t)))->size = memFirst->size;
    return 1;
}

void memdone() {
    memory = NULL;
    memFirst = NULL;
    memSize = 0;
}

void* memalloc(int size) {
    memory_block_t* memBlock, * nextMemBlock;
    char* pAlloc;
    memory_block_end_t* memEnd;
    int memBlockSize = memgetblocksize();
    memBlock = memFirst;

    if (!memBlock || size <= 0 || !memory) 
        return NULL;

    while (memBlock) {
        if (memBlock->size >= size) {
            if (memBlock->size - size > memBlockSize) {
                if (memBlock->prev)
                    memBlock->prev->next = memBlock->next;
                else
                    memFirst = memFirst->next;

                if (memBlock->next)
                    memBlock->next->prev = memBlock->prev;

                memEnd = (memory_block_end_t*)(size + (char*)memBlock + sizeof(memory_block_t));
                memEnd->size = size;

                nextMemBlock = (memory_block_t*)((char*)(memEnd)+sizeof(memory_block_end_t));
                nextMemBlock->size = memBlock->size - memBlockSize - size;
                nextMemBlock->isFree = FREE;
                nextMemBlock->next = memFirst;
                nextMemBlock->prev = NULL;
                if (memFirst)
                    memFirst->prev = nextMemBlock;
                memFirst = nextMemBlock;

                memEnd = (memory_block_end_t*)((char*)nextMemBlock + nextMemBlock->size + sizeof(memory_block_t));
                memEnd->size = nextMemBlock->size;

                memBlock->size = size;
                memBlock->isFree = NOT_FREE;
                memBlock->next = NULL;
                memBlock->prev = NULL;
            }
            else {
                if (memBlock->prev)
                    memBlock->prev->next = memBlock->next;
                else
                    memFirst = memFirst->next;

                if (memBlock->next)
                    memBlock->next->prev = memBlock->prev;

                memBlock->isFree = NOT_FREE;
                memBlock->next = NULL;
                memBlock->prev = NULL;
            }

            pAlloc = (char*)memBlock + sizeof(memory_block_t);
            return pAlloc;
        }
        memBlock = memBlock->next;
    }
    return NULL;
}

void memfree(void* p) {
    if (!p || (char*)p - memory < 0 || (char*)p > memory + memSize || ((memory_block_t*)((char*)p - sizeof(memory_block_t)))->isFree != NOT_FREE)
        return;
    memory_block_t* deleteBlock, * rightBlock, * leftBlock;
    memory_block_end_t* endBlock, * endRight, * endLeft;
    int memBlockSize = memgetblocksize();

    deleteBlock = (memory_block_t*)((char*)p - sizeof(memory_block_t));
    deleteBlock->next = memFirst;
    deleteBlock->prev = NULL;
    deleteBlock->isFree = FREE;
    if (memFirst)
        memFirst->prev = deleteBlock;
    memFirst = deleteBlock;

    endBlock = (memory_block_end_t*)((char*)deleteBlock + deleteBlock->size + sizeof(memory_block_t));

    if ((char*)deleteBlock - sizeof(memory_block_end_t) > memory) {
        endLeft = (memory_block_end_t*)((char*)deleteBlock - sizeof(memory_block_end_t));
        leftBlock = (memory_block_t*)((char*)endLeft - endLeft->size - sizeof(memory_block_t));
    }
    else {
        endLeft = NULL;
        leftBlock = NULL;
    }

    if ((char*)endBlock + sizeof(memory_block_end_t) < memory + memSize - 2) {
        rightBlock = (memory_block_t*)((char*)endBlock + sizeof(memory_block_end_t));
        endRight = (memory_block_end_t*)((char*)rightBlock + rightBlock->size + sizeof(memory_block_t));
    }
    else {
        rightBlock = NULL;
        endRight = NULL;
    }

    if (rightBlock && rightBlock->isFree == FREE) {
        if (rightBlock->prev)
            rightBlock->prev->next = rightBlock->next;
        else
            memFirst = memFirst->next;

        if (rightBlock->next)
            rightBlock->next->prev = rightBlock->prev;

        deleteBlock->size += memBlockSize + rightBlock->size;
        endRight->size = deleteBlock->size;
        rightBlock->isFree = NOT_FREE;
        endBlock = endRight;
    }
    if (leftBlock && leftBlock->isFree == FREE) {
        if (deleteBlock->prev)
            deleteBlock->prev->next = deleteBlock->next;
        else
            memFirst = memFirst->next;

        if (deleteBlock->next)
            deleteBlock->next->prev = deleteBlock->prev;

        leftBlock->size += memBlockSize + deleteBlock->size;
        endBlock->size = leftBlock->size;
        deleteBlock->isFree = NOT_FREE;
        endLeft = endBlock;
    }
}