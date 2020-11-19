//#ifdef __cplusplus
//extern "C" {
//#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memallocator.h"

typedef enum {
    SUCCESS,
    FAILED
} result;

// block of memory type
typedef struct block_t {
    struct block_t* next;
    struct block_t* prev;
    int size;
} block_t;

// Information about memory system and its current state
typedef struct {
    block_t* headBlock; // pointer to head block, contains size of memory available
    block_t* curAvailBlock; // pointer to block which was allocated last time
    int totalSize; // size of memory which system was initiliazed with
} system_t;


system_t mSys = { NULL, NULL, 0 };




// Return minimum size in bytes of the memory pool to allocate 0-bytes block
int memgetminimumsize(void) {

    return 2 * sizeof(block_t) + 2 * sizeof(int);
}

// Returns size in bytes of additional information per allocation
int memgetblocksize(void) {

    return sizeof(block_t) + sizeof(int);
}


// Init memory system with memory block pMemory
int meminit(void* pMemory, int size) {
    int minSize ;
    int blockSize;

    blockSize  = memgetblocksize();
    minSize =  memgetminimumsize();
    if (pMemory == NULL || size < minSize) {
        return FAILED;
    }


    mSys.headBlock = (block_t*)pMemory;
    mSys.totalSize = size;

    // kind of a loop created at the head of memory manager
    // needed cuz of doubly linked list structure 
    mSys.headBlock->next = (block_t*)((char*)pMemory + blockSize);
    mSys.headBlock->prev = (block_t*)((char*)pMemory + blockSize);
    mSys.headBlock->size = 0;
    *(int*)(mSys.headBlock + 1) = 0;
    mSys.headBlock->next->next = mSys.headBlock;
    mSys.headBlock->next->prev = mSys.headBlock;

    // actual available memory
    mSys.headBlock->next->size = size - minSize;
    *(int*)((char*)pMemory + size-sizeof(int)) = mSys.headBlock->next->size;


    // writing p to currently available block
    mSys.curAvailBlock = mSys.headBlock->next;
    return SUCCESS;

}


// Allocate memory block of size 'size'.
// Returns pointe to memory block is success, NULL otherwise
void* memalloc(int size) {

    // uninitialised memory system, cant allocate 
    if (mSys.headBlock == NULL)
        return NULL;

    block_t* block;
    block_t* newBlock;
    void* pMemory;
    int blockSize;

    blockSize = memgetblocksize();
    block = mSys.curAvailBlock;
    pMemory = NULL;

    do {
        // if currently available block doesnt match
        // skip to next block
        if (block->size < size)
            block = block->next;


        else if (block->size < size + blockSize) {
            // fitting block already exists, just gotta fix pointers
            pMemory = (void*)(block + 1);

            // clearing garbage in block that's gonna be allocated
            memset(pMemory, 0, block->size);

            // removing allocating block from list
            block->prev->next = block->next;
            block->next->prev = block->prev;
            // updating available block for memory system
            mSys.curAvailBlock = block->next;
            block->next = NULL;

            // changed block+1 to pMemory
            *(int*)((char*)(block + 1) + block->size) = block->size;

            break;
        }
        else {
            // enough memory to allocate, but no existing blocks fit
            // creating new one
            newBlock = (block_t*)((char*)block + size + blockSize);

            // copying pointers to created block
            newBlock->prev = block->prev;
            newBlock->next = block->next;
            newBlock->next->prev = newBlock;
            newBlock->prev->next = newBlock;
            block->next = NULL;

            // memory left available after allocating at newBlock 
            newBlock->size = block->size - size - blockSize;
            *(int*)((char*)(newBlock + 1) + newBlock->size) = newBlock->size;

            block->size = size;
            *(int*)((char*)(block + 1) + size) = size;

            pMemory = (void*)(block + 1);
            memset(pMemory, 0, size);
            mSys.curAvailBlock = newBlock;
            break;
        }

    } while (block != mSys.curAvailBlock);


    return pMemory;
}








// Free memory previously allocated by memalloc
void memfree(void* p) {
   
        
        // checks if p actually points to memory allocated by our memory system
        if (p == NULL || mSys.totalSize == 0 || (char*)p >= (char*)mSys.headBlock + mSys.totalSize)
        return;
        
        
        int blockSize;
        block_t* block;
        block_t* nextBlock;
        block_t* prevBlock;
        block_t* end;
        
        
        blockSize = memgetblocksize();
        end = (block_t*)((char*)mSys.headBlock + mSys.totalSize);//pointer to end of all memory available
        block = (block_t*)((char*)p - sizeof(block_t));
        nextBlock = (block_t*)((char*)p + block->size + sizeof(int));// pointer to following block
        prevBlock = (block_t*)((char*)block - blockSize - *(int*)((char*)p - blockSize));// pointer to prev block
        
        
        // if we have memory available after the p block, gotta merge it w/ p
        if (nextBlock != end && nextBlock->next != NULL) { 
            block->size += nextBlock->size + blockSize;// merging next block including descriptor size
        
            if (nextBlock == mSys.curAvailBlock)
                mSys.curAvailBlock = nextBlock->next;
            // fixing pointers
            nextBlock->prev->next = nextBlock->next;
            nextBlock->next->prev = nextBlock->prev;
            *(int*)((char*)(block + 1) + block->size) = block->size;
        }
        
        // if p block isn't the first in memory system, gotta merge it /w p 
        if (prevBlock != mSys.headBlock && prevBlock->next != NULL) {
            prevBlock->size += block->size + blockSize;
        
            if (block == mSys.curAvailBlock)
                mSys.curAvailBlock = prevBlock;
            // fixing pointers
            *(int*)((char*)(prevBlock + 1) + prevBlock->size) = prevBlock->size;
        
            return;
        }

        // adding new block to list
        block->next = mSys.headBlock->next;
        mSys.headBlock->next->prev = block;
        block->prev = mSys.headBlock;
        mSys.headBlock->next = block;
        
}





// clears all allocated memory
void memdone(void) {
    
  
    memset(mSys.headBlock, 0, mSys.totalSize);
    mSys.headBlock = NULL;
    mSys.curAvailBlock = NULL;
    mSys.totalSize = 0;
}
//
//
//#ifdef __cplusplus
//}
//#endif 