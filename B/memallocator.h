#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif

#define NO_LEAK "\nNo Memory Leakage\n"
#define LEAK "\nMemory Leakage\n"

#define mem_offset(block) ((char*)(block) + memgetblocksize())
#define block_end(block) ((char*)(block) + (block->size))
#define max(a, b) ((a) > (b) ? a : b)
#define new_block_size(size) (max((size) + memgetblocksize(), memgetminimumsize()))
#define BYTE (memgetminimumsize() + 1)

typedef struct Block {
    int size; // full block size (header + data)
    struct Block* next;
} Block_t;

typedef struct memBlock {
    Block_t* block; // the beginning block

    void* begin; // the beginning of the allocated memory
    int size; // size of the allocated memory
    void* curr; // pointer to the beginning of the block, which took the memory
} memBlock_t;

enum ErrorCodes {
    MEM_ALLOC_SUCCESS,
    MEM_ALLOC_FAIL,
    SMALL_MEM_ALLOC,
    NULL_PTR_ALLOC,
    MEM_INIT_SUCCESS,
};

char* newBlock(void* place, Block_t* before, int size, Block_t* after);

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