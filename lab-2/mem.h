#define FAILED 1
#define SUCCESS 0
typedef struct block_t {
    int size;
    struct block_t* next;
    struct block_t* prev;
}block_t;
typedef struct {
    int sizeInSum;
    block_t* pToHead;
    block_t* pToLast;
}mem_t;
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
