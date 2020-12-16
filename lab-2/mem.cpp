//#include "memallocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mem.h"
#define FAILED 1
#define SUCCESS 0
mem_t myMem = { 0, NULL, NULL };

int memgetminimumsize(void) {
    return 2 * sizeof(block_t) + 2 * sizeof(int);
}

int memgetblocksize(void) {
    return sizeof(block_t) + sizeof(int);
}


int meminit(void* pMemory, int size) {
    int minSize;
    int sizeOfBlock;
    sizeOfBlock = memgetblocksize();
    minSize = memgetminimumsize();
    if (pMemory == NULL || size < minSize) {
        return FAILED;
    }
    myMem.pToHead = (block_t*)pMemory;
    myMem.sizeInSum = size;
    myMem.pToHead->next = (block_t*)((char*)pMemory + sizeOfBlock);
    myMem.pToHead->prev = (block_t*)((char*)pMemory + sizeOfBlock);
    myMem.pToHead->size = 0;
    *(int*)(myMem.pToHead + 1) = 0;
    myMem.pToHead->next->next = myMem.pToHead;
    myMem.pToHead->next->prev = myMem.pToHead;
    myMem.pToHead->next->size = size - minSize;
    *(int*)((char*)pMemory + size - sizeof(int)) = myMem.pToHead->next->size;
    myMem.pToLast = myMem.pToHead->next;
    return SUCCESS;
}

void* memalloc(int size) {
    if (myMem.pToHead == NULL)
        return NULL;
    block_t* block;
    block_t* newB;
    void* pToMem;
    int sizeOfBlock;
    sizeOfBlock = memgetblocksize();
    block = myMem.pToLast;
    pToMem = NULL;
    do {
        if (block->size < size)
            block = block->next;
        else if (block->size < size + sizeOfBlock) {
            pToMem = (void*)(block + 1);         
            memset(pToMem, 0, block->size);      
            block->prev->next = block->next;
            block->next->prev = block->prev;   
            myMem.pToLast = block->next;
            block->next = NULL;     
            *(int*)((char*)(block + 1) + block->size) = block->size;
            break;
        }
        else {
            newB = (block_t*)((char*)block + size + sizeOfBlock);
            newB->prev = block->prev;
            newB->next = block->next;
            newB->next->prev = newB;
            newB->prev->next = newB;
            block->next = NULL;
            newB->size = block->size - size - sizeOfBlock;
            *(int*)((char*)(newB + 1) + newB->size) = newB->size;
            block->size = size;
            *(int*)((char*)(block + 1) + size) = size;
            pToMem = (void*)(block + 1);
            memset(pToMem, 0, size);
            myMem.pToLast = newB;
            break;
        }
    } while (block != myMem.pToLast);
    return pToMem;
}








void memfree(void* p) {
    if (p == NULL || myMem.sizeInSum == 0 || (char*)p >= (char*)myMem.pToHead + myMem.sizeInSum)
        return;

    int sizeOfBlock;
    block_t* block;
    block_t* nextB;
    block_t* prevB;
    block_t* end;
    sizeOfBlock = memgetblocksize();
    end = (block_t*)((char*)myMem.pToHead + myMem.sizeInSum);
    block = (block_t*)((char*)p - sizeof(block_t));
    nextB = (block_t*)((char*)p + block->size + sizeof(int));
    prevB = (block_t*)((char*)block - sizeOfBlock - *(int*)((char*)p - sizeOfBlock));
    if (nextB != end && nextB->next != NULL) { 
        block->size += nextB->size + sizeOfBlock;

        if (nextB == myMem.pToLast)
            myMem.pToLast = nextB->next;
        nextB->prev->next = nextB->next;
        nextB->next->prev = nextB->prev;
        *(int*)((char*)(block + 1) + block->size) = block->size;
    }

    if (prevB != myMem.pToHead && prevB->next != NULL) { 
        prevB->size += block->size + sizeOfBlock;

        if (block == myMem.pToLast)
            myMem.pToLast = prevB;
        *(int*)((char*)(prevB + 1) + prevB->size) = prevB->size;

        return;
    }

    block->next = myMem.pToHead->next;
    myMem.pToHead->next->prev = block;
    block->prev = myMem.pToHead;
    myMem.pToHead->next = block;

}








void memdone(void) {


    memset(myMem.pToHead, 0, myMem.sizeInSum);
    myMem.pToHead = NULL;
    myMem.pToLast = NULL;
    myMem.sizeInSum = 0;
}