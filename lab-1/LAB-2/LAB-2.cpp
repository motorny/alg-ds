#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "memallocator.h"
#include "pch.h"
#include "framework.h"
#pragma warning(disable: 4996)

#define TRUE 1
#define FALSE 0

#define SIZE (sizeof(header_t) + sizeof(int))

// Memory block
typedef struct header_t {
    int size;
    struct header_t* next;
    struct header_t* prev;
} header_t;

// Memory system, current state
typedef struct MemSyst_t {
    int totalSize;
    header_t* bufBlock;
    header_t* curBlock;
} MemSyst_t;

MemSyst_t Mem = { 0, NULL, NULL };

// Returns minimum size of the memory pool
int memgetminimumsize(void) {
    return 2 * SIZE;
}

// Returns size of additional information
int memgetblocksize(void) {
    return SIZE;
}

// Inits memory system with memory block
int meminit(void* block, int size) {
    int minSize = memgetminimumsize();
    int blockSize = memgetblocksize();

    if (size >= minSize && block) {
        Mem.bufBlock = (header_t*)block;
        Mem.totalSize = size;
        Mem.bufBlock->next = (header_t*)((char*)block + blockSize);
        Mem.bufBlock->prev = (header_t*)((char*)block + blockSize);
        Mem.bufBlock->size = 0;
        *(int*)(Mem.bufBlock + 1) = 0;
        Mem.bufBlock->next->next = Mem.bufBlock;
        Mem.bufBlock->next->prev = Mem.bufBlock;
        Mem.bufBlock->next->size = size - minSize;
        *(int*)((char*)block - sizeof(int) + size) = Mem.bufBlock->next->size;
        Mem.curBlock = Mem.bufBlock->next;
        return FALSE;
    }
    else
        return TRUE;
}

// Allocates memory block of size
// Returns pointer to memory block is success, NULL otherwise
void* memalloc(int size) {
    header_t* block;
    header_t* newBlock;
    void* buffer = NULL;
    int blockSize = memgetblocksize();

    if (Mem.bufBlock == NULL)
        return NULL;
    if (Mem.bufBlock) {
        block = Mem.curBlock;
        while (block == Mem.curBlock) {
            if (block->size < size)
                block = block->next;
            else if (block->size < size + blockSize) {
                buffer = (void*)(block + 1);
                memset(buffer, 0, block->size);
                block->prev->next = block->next;
                block->next->prev = block->prev;
                Mem.curBlock = block->next;
                block->next = NULL;

                *(int*)((char*)(block + 1) + block->size) = block->size;

                break;
            }
            else {
                // Add new block
                newBlock = (header_t*)((char*)block + blockSize + size);

                newBlock->prev = block->prev;
                newBlock->next = block->next;
                newBlock->next->prev = newBlock;
                newBlock->prev->next = newBlock;
                block->next = NULL;

                newBlock->size = block->size - blockSize - size;
                *(int*)((char*)(newBlock + 1) + newBlock->size) = newBlock->size;

                block->size = size;
                *(int*)((char*)(block + 1) + size) = size;

                buffer = (void*)(block + 1);
                memset(buffer, 0, size);
                Mem.curBlock = newBlock;
                break;
            }
        }
    }
    return buffer;
}

// Free memory previously allocated
void memfree(void* point) {

    int blockSize = memgetblocksize();
    header_t* block;
    header_t* nextBlock;
    header_t* prevBlock;
    header_t* end = (header_t*)((char*)Mem.bufBlock + Mem.totalSize);

    // Merge with next
    if (point != NULL && Mem.totalSize != 0 && (char*)point < (char*)Mem.bufBlock + Mem.totalSize) {
        block = (header_t*)((char*)point - sizeof(header_t));
        nextBlock = (header_t*)((char*)point + sizeof(int) + block->size);
        prevBlock = (header_t*)((char*)block - *(int*)((char*)point - blockSize) - blockSize);
        if (nextBlock != end && nextBlock->next != NULL) {
            block->size = block->size + nextBlock->size + blockSize;
            if (nextBlock == Mem.curBlock)
                Mem.curBlock = nextBlock->next;
            nextBlock->prev->next = nextBlock->next;
            nextBlock->next->prev = nextBlock->prev;
            *(int*)((char*)(block + 1) + block->size) = block->size;
        }
        // Merge with prev
        if (prevBlock != Mem.bufBlock && prevBlock->next != NULL) {
            prevBlock->size = prevBlock->size + block->size + blockSize;
            if (block == Mem.curBlock)
                Mem.curBlock = prevBlock;
            *(int*)((char*)(prevBlock + 1) + prevBlock->size) = prevBlock->size;
            return;
        }
        // Add new block
        block->next = Mem.bufBlock->next;
        Mem.bufBlock->next->prev = block;
        block->prev = Mem.bufBlock;
        Mem.bufBlock->next = block;
    }
}

// Clears memory
void memdone(void) {
    Mem.totalSize = 0;
    Mem.bufBlock = NULL;
    Mem.curBlock = NULL;
}

