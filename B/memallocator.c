#include <stdio.h>
#include <assert.h>

#include "memallocator.h"

memBlock_t memBlock = {NULL, NULL, 0, NULL};

int memgetblocksize() {
    return sizeof(Block_t);
}

int memgetminimumsize() {
    return memgetblocksize();
}

int meminit(void* ptr, int size) {
    if (ptr == NULL)
        return NULL_PTR_ALLOC;
    if (size < memgetminimumsize())
        return SMALL_MEM_ALLOC;

    memBlock.begin = ptr;
    memBlock.size = size;

    return MEM_INIT_SUCCESS;
}

void memdone() { // apparently, the testing system doesn't like output :'(
    if (memBlock.block == NULL || memBlock.size - memgetblocksize() == memBlock.block->size)
        printf(NO_LEAK);
    else
        printf(LEAK);
    memBlock = (memBlock_t){NULL, NULL, 0, NULL};
}

char* newBlock(void* place, Block_t* before, int size, Block_t* after) {
    Block_t* next = (Block_t*) place;
    next->size = new_block_size(size);
    next->next = after;
    // block should be the leftmost partition
    if (memBlock.block == NULL || memBlock.block > next)
        memBlock.block = next;
    else
        // if the insert is to the head, ptr points to the head, hence circular pointers
        // if it is not, we need the previous pointer to point to the inserted one
        before->next = next;
    memBlock.curr = next;
    return mem_offset(next);
}

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, 0 otherwise
void* memalloc(int size) {
    // not enough memory was initialized
    if (memBlock.begin == NULL)
        return NULL;
    // first memory allocation (first block partition)
    if (memBlock.block == NULL) {
        if (memBlock.size - memgetblocksize() < size || size < 0)
            return NULL;
        return newBlock(memBlock.begin, NULL, size, NULL);
    }
    Block_t* curr = (Block_t*) memBlock.curr, * ptr = curr;

    do {
        if (ptr->next == NULL) {
            // if ptr is the last block, check if there is not enough space to fit another block
            if (memBlock.size - (block_end(ptr) - (char*) memBlock.begin) < (new_block_size(size))) {
                // if there is enough space between the beginning of the initialized memory
                // and the first block, let's fit in
                if ((char*) memBlock.block - (char*) memBlock.begin >= (new_block_size(size)))
                    return newBlock(memBlock.begin, NULL, size, memBlock.block);
                else
                    // gosh, have to find the place from the first block
                    ptr = memBlock.block;
            } else
                return newBlock(block_end(ptr), ptr, size, NULL);
            // if the ptr became the first block and the first block is curr, ptr has to go through the comparison
            // before it would be able to enter this branch
        } else {
            // if the new block can be fit in-between the beginning of the next one and
            // the end of the current one, let's place it!
            if ((char*) ptr->next - block_end(ptr) >= (new_block_size(size)))
                return newBlock(block_end(ptr), ptr, size, ptr->next);
            // if it cannot, proceed searching
            ptr = ptr->next;
        }
    } while (ptr != curr);

    // we did all we could, but there is no memory :(
    return NULL;
}

// Free memory previously allocated by memalloc
void memfree(void* p) {
    if (memBlock.begin == NULL || memBlock.block == NULL || p == NULL ||
        (char*) p - (char*) memBlock.begin < 0 || (char*) p - (char*) memBlock.begin > memBlock.size)
        return;

    Block_t* ptr = memBlock.block, * next = ptr->next;

    // leftmost partition
    if (p == (void*) mem_offset(ptr)) {
        if (next == NULL) {
            memBlock.block = NULL;
            memBlock.curr = NULL;
        } else {
            memBlock.block = next;
            if (memBlock.curr == (void*)ptr)
                memBlock.curr = next;
        }
        return;
    }

    // middle or last
    // next cannot be NULL on the first iteration, because in this case,
    // it would mean, that ptr is the leftmost partition, which was the previous step
    while (next != NULL) {
        if (p == (void*) mem_offset(next)) {
            if (memBlock.curr == (void*)next)
                memBlock.curr = ptr;
            ptr->next = next->next;
            return;
        }
        ptr = next;
        next = next->next;
    }
}
