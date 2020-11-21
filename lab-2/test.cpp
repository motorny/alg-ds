#include "pch.h"

extern "C" {
#include "../memallocator/memallocator.h"
#include "../memallocator/memallocator.cpp"
}

#define TRUE 0
#define FALSE 1
#define MIN_SIZE (BLOCK_DESCRIPTOR_SIZE + 1)

TEST(memalloc, AllocWithoutInit_ReturnNULL) {
	char* p = (char*)memalloc(1);
	EXPECT_EQ(p, (char*)nullptr);
}
TEST(meminit, ValidPointerValidSize_ReturnTRUE) {
	char* Memory = (char*)malloc(MIN_SIZE);

	EXPECT_EQ(meminit(Memory, MIN_SIZE), TRUE);
	EXPECT_EQ(myMemory.memoryBeginning, Memory);
	EXPECT_EQ(myMemory.totalSize, MIN_SIZE);

	free(Memory);
} 
TEST(meminit, ValidPointerInvalidSize_ReturnFALSE) {
	char* Memory = (char*)malloc(MIN_SIZE - 1);

	EXPECT_EQ(meminit(Memory, MIN_SIZE - 1), FALSE);

	free(Memory);
}
TEST(meminit, NullPointr_ReturnFALSE) {
	char* Memory = NULL;

	EXPECT_EQ(meminit(Memory, MIN_SIZE), FALSE);
}


TEST(memalloc, NegativeSize_ReturnNULL) {
	char* Memory = (char*)malloc(MIN_SIZE);
	char* p;
	meminit(Memory, MIN_SIZE);
	p = (char*)memalloc(-1);

	EXPECT_EQ(p, (char*)nullptr);
	EXPECT_EQ(myMemory.firstFreeMemDescriptor->size, 1);

	memdone();
	free(Memory);
}
TEST(memalloc, AllocWithoutSplitOfBlocks_ReturnValidPointer) {
	char* Memory = (char*)malloc(MIN_SIZE);
	char* p;
	meminit(Memory, MIN_SIZE);
	p = (char*)memalloc(1);

	EXPECT_EQ(p, myMemory.memoryBeginning + sizeof(descriptor_t));
	EXPECT_EQ(((block_end_t*)((char*)p + ((descriptor_t*)((char*)p - sizeof(descriptor_t)))->size))->size, 1);
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), (char*)NULL);

	memdone();
	free(Memory);
}
TEST(memalloc, AllocWithSplitOfBlocks_ReturnValidPointer) {
	char* Memory = (char*)malloc(MIN_SIZE * 2);
	char* p;
	meminit(Memory, MIN_SIZE * 2);
	p = (char*)memalloc(1);

	EXPECT_EQ(p, myMemory.memoryBeginning + sizeof(descriptor_t));
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), (char*)p + 1 + sizeof(block_end_t));
	EXPECT_EQ(myMemory.firstFreeMemDescriptor->size, 1);
	EXPECT_EQ(((block_end_t*)((char*)p + ((descriptor_t*)((char*)p - sizeof(descriptor_t)))->size))->size, 1);

	memdone();
	free(Memory);
}
TEST(memalloc, NotEnoughMemory_ReturnNULL) {
	char* Memory = (char*)malloc(MIN_SIZE);
	char* p;
	meminit(Memory, MIN_SIZE);
	p = (char*)memalloc(2);

	EXPECT_EQ(p, (char*)nullptr);
	EXPECT_EQ(myMemory.firstFreeMemDescriptor->size, 1);

	memdone();
	free(Memory);
}


TEST(memfree, PtrOutsideMemory_ReturnNone) {
	char* Memory = (char*)malloc(MIN_SIZE);
	meminit(Memory, MIN_SIZE);

	memfree(Memory - 1);

	memdone();
	free(Memory);
}
TEST(memfree, PtrInsideMemoryButNotTheBegginingOfData_ReturnNone) {
	char* Memory = (char*)malloc(MIN_SIZE);
	char* p;
	meminit(Memory, MIN_SIZE);
	p = (char*)memalloc(1);
	memfree(Memory + 1);

	EXPECT_EQ(((block_end_t*)((char*)p + ((descriptor_t*)((char*)p - sizeof(descriptor_t)))->size))->size, 1);

	memdone();
	free(Memory);
}
TEST(memfree, MemoryDone_ReturnNone) {
	char* Memory = (char*)malloc(MIN_SIZE);
	char* p;
	meminit(Memory, MIN_SIZE);
	p = (char*)memalloc(1);
	memdone();

	memfree(p);
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), (char*)NULL);

	free(Memory);
}
TEST(memfree, FreeAlreadyEmptyPointer_ReturnNone) {
	char* Memory = (char*)malloc(MIN_SIZE);
	char* p;
	meminit(Memory, MIN_SIZE);
	p = (char*)memalloc(1);
	memfree(p);

	memfree(p);
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), p - sizeof(descriptor_t));
	EXPECT_EQ(((block_end_t*)((char*)p + ((descriptor_t*)((char*)p - sizeof(descriptor_t)))->size))->size, -1);
	EXPECT_EQ(myMemory.firstFreeMemDescriptor->size, 1);

	memdone();
	free(Memory);
}
TEST(memfree, FreeWithoutMerge_ReturnNone) {
	char* Memory = (char*)malloc(MIN_SIZE * 3);
	char* p1, * p2, * p3;
	meminit(Memory, MIN_SIZE * 3);
	p1 = (char*)memalloc(1);
	p2 = (char*)memalloc(1);
	p3 = (char*)memalloc(1);

	memfree(p2);

	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), p2 - sizeof(descriptor_t));
	EXPECT_EQ(((block_end_t*)((char*)p2 + ((descriptor_t*)((char*)p2 - sizeof(descriptor_t)))->size))->size, -1);
	EXPECT_EQ(myMemory.firstFreeMemDescriptor->size, 1);

	memdone();
	free(Memory);
}
TEST(memfree, FreeWithMergeWithNext_ReturnNone) {
	char* Memory = (char*)malloc(MIN_SIZE * 3);
	char* p1, * p2, * p3;
	meminit(Memory, MIN_SIZE * 3);
	p1 = (char*)memalloc(1);
	p2 = (char*)memalloc(1);
	p3 = (char*)memalloc(1);

	memfree(p3);
	memfree(p2);

	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), p2 - sizeof(descriptor_t));
	EXPECT_EQ(myMemory.firstFreeMemDescriptor->size, 2 + BLOCK_DESCRIPTOR_SIZE);

	memdone();
	free(Memory);
}
TEST(memfree, FreeWithMergeWithPrevious_ReturnNone) {
	char* Memory = (char*)malloc(MIN_SIZE * 3);
	char* p1, * p2, * p3;
	meminit(Memory, MIN_SIZE * 3);
	p1 = (char*)memalloc(1);
	p2 = (char*)memalloc(1);
	p3 = (char*)memalloc(1);
	memfree(p1);

	memfree(p2);
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), p1 - sizeof(descriptor_t));
	EXPECT_EQ(myMemory.firstFreeMemDescriptor->size, 2 + BLOCK_DESCRIPTOR_SIZE);

	memdone();
	free(Memory);
}
TEST(memfree, FreeWithMergeInBothDirections_ReturnNone) {
	char* Memory = (char*)malloc(MIN_SIZE * 3);
	char* p1, * p2, * p3;
	meminit(Memory, MIN_SIZE * 3);
	p1 = (char*)memalloc(1);
	p2 = (char*)memalloc(1);
	p3 = (char*)memalloc(1);
	memfree(p1);
	memfree(p3);

	memfree(p2);
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), p1 - sizeof(descriptor_t));
	EXPECT_EQ(myMemory.firstFreeMemDescriptor->size, 3 + 2 * BLOCK_DESCRIPTOR_SIZE);

	memdone();
	free(Memory);
}

TEST(ComplexTest, ComplexTest_Success) {
	char memory[10 + 10 * BLOCK_DESCRIPTOR_SIZE];
	meminit(memory, 10 + 10 * BLOCK_DESCRIPTOR_SIZE);
	char* ptr[10];

	for (int i = 0; i < 10; i++) {
		ptr[i] = (char*)memalloc(1);
	}

	memfree(ptr[2]);
	memfree(ptr[9]);
	memfree(ptr[0]);
	memfree(ptr[1]);
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), ptr[0] - sizeof(descriptor_t));
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor->next), ptr[9] - sizeof(descriptor_t));
	EXPECT_EQ(((myMemory.firstFreeMemDescriptor))->size, 3 + 2 * BLOCK_DESCRIPTOR_SIZE);

	memfree(ptr[3]);
	memfree(ptr[5]);
	memfree(ptr[4]);
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), ptr[0] - sizeof(descriptor_t));
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor->next), ptr[9] - sizeof(descriptor_t));
	EXPECT_EQ(((myMemory.firstFreeMemDescriptor))->size, 6 + 5 * BLOCK_DESCRIPTOR_SIZE);

	ptr[1] = (char*)memalloc(40);
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor->next), ptr[9] - sizeof(descriptor_t));
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), ptr[1] + 40 + sizeof(block_end_t));
	EXPECT_EQ(((myMemory.firstFreeMemDescriptor))->size, 6 + 4 * BLOCK_DESCRIPTOR_SIZE - 40);

	memfree(ptr[1]);
	memfree(ptr[6]);
	memfree(ptr[8]);
	memfree(ptr[7]);

	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), ptr[0] - sizeof(descriptor_t));
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor->next), (char*)NULL);
	EXPECT_EQ(((myMemory.firstFreeMemDescriptor))->size, myMemory.totalSize - BLOCK_DESCRIPTOR_SIZE);

	memdone();
}

TEST(StressTest, StressTest_Success) {
	char memory[100 + 100 * BLOCK_DESCRIPTOR_SIZE];
	meminit(memory, 100 + 100 * BLOCK_DESCRIPTOR_SIZE);
	char* ptr[100];
	
	for (int i = 0; i < 100; i++) {
		ptr[i] = (char*)memalloc(1);
	}
	for (int i = 0; i < 100; i += 2) {
		memfree(ptr[i]);
	}
	for (int i = 1; i < 100; i += 4) {
		memfree(ptr[i]);
	}
	for (int i = 0; i < 96; i += 2) {
		ptr[i] = (char*)memalloc(2);
	}
	for (int i = 99; i > 0; i -= 4) {
		memfree(ptr[i]);
	}
	for (int i = 0; i < 96; i += 2) {
		memfree(ptr[i]);
	}

	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor), ptr[0] - sizeof(descriptor_t));
	EXPECT_EQ((char*)(myMemory.firstFreeMemDescriptor->next), (char*)NULL);
	EXPECT_EQ(((myMemory.firstFreeMemDescriptor))->size, myMemory.totalSize - BLOCK_DESCRIPTOR_SIZE);

	memdone();
}