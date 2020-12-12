typedef struct block_t {
	int size;
	int free;
	struct block_t* next;

} block_t;

int MemInit(void* Memory, int size);

void* Memalloc(int size);

void FreeMem(void* mem);

void clear();