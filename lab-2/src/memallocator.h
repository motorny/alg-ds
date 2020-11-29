
// Init memory system with memory block pMemory.
int meminit(void *pMemory,int size);

// You can implement memory leak checks here
void memdone();

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, 0 otherwise
void *memalloc(int size);

// Free memory previously allocated by memalloc
void memfree(void *p);

int memgetminimumsize();

int memgetblocksize();

