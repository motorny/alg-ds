#include "pch.h"
#include "..\Lab2_3sem\memallocator.h"
#include "..\Lab2_3sem\memallocator.cpp"


TEST(BaseTests, MemInitTest) {
	void* ptrForAll = malloc(memgetminimumsize() + 1);
	ASSERT_TRUE(meminit(ptrForAll, memgetminimumsize() + 1) == 1);
	ASSERT_TRUE(g_allMemory != NULL);
	ASSERT_TRUE(g_allMemory->size == memgetminimumsize() + 1);
	ASSERT_TRUE((char*)(g_allMemory->startFree) == (char*)g_allMemory+sizeof(all_mem_info_t));

	free(ptrForAll);
}

TEST(BaseTests, MemFreeTest) {
	void* ptrForAll = malloc(memgetminimumsize() + 1);
	char* ptr = NULL;
	meminit(ptrForAll, memgetminimumsize() + 1);

	ptr = (char*)memalloc(1);
	ASSERT_TRUE(((memory_block_t*)(ptr - sizeof(memory_block_t)))->size == 1);
	EXPECT_TRUE(((memory_block_t*)(ptr - sizeof(memory_block_t)))->next == NULL);
	EXPECT_TRUE(((memory_block_t*)(ptr - sizeof(memory_block_t)))->prev == NULL);
	ptr[0] = '4';
	memfree(ptr);
	memdone();
	free(ptrForAll);
}

TEST(MemFuncTests, 2blocksFreeThenTake) {
	char *ptr1 = NULL, *ptr2 = NULL;
	int memSize = memgetminimumsize() + memgetblocksize() + 2;
	void* ptrForAll = malloc(memSize);

	meminit(ptrForAll, memSize);

	ptr1 = (char*)memalloc(1);

	ptr2 = (char*)memalloc(1);

	ASSERT_TRUE(ptr1 - sizeof(memory_block_t) != NULL);
	ASSERT_TRUE(ptr2 - sizeof(memory_block_t) != NULL);
	EXPECT_TRUE(((memory_block_t*)(ptr1 - sizeof(memory_block_t)))->size == 1);
	EXPECT_TRUE(((memory_block_t*)(ptr2 - sizeof(memory_block_t)))->size == 1);
	
	memfree(ptr2);

	ptr2 = (char*)memalloc(1);

	memfree(ptr1);
	memfree(ptr2);
	memdone();

	free(ptrForAll);

}
TEST(MotornyCases, TestMinSizePlusOne) {
	char* ptr = NULL;
	void* ptrForAll = malloc(memgetminimumsize() + 1);

	meminit(ptrForAll, memgetminimumsize() + 1);
	ASSERT_TRUE(g_allMemory != NULL);
	ASSERT_TRUE(g_allMemory->size == memgetminimumsize() + 1);
	
	ptr = (char*)memalloc(1);

	memfree(ptr);
	memdone();
	free(ptrForAll);
}


TEST(MotornyCases, TestMinPlBlockPl2) {
	memory_block_t* ptr1 = NULL, * ptr2 = NULL;
	int memSize = memgetminimumsize() + memgetblocksize() + 2;
	void* ptrForAll = malloc(memSize);

	meminit(ptrForAll, memSize);

	ptr1 = (memory_block_t*)memalloc(1);
	ptr2 = (memory_block_t*)memalloc(1);
	memfree(ptr2);
	memfree(ptr1);
	memdone();

	free(ptrForAll);
}

TEST(HardTests, 10blocksFreeFromBegin) {
	char memory[10 + sizeof(all_mem_info_t) + 10 * (sizeof(memory_block_t) + sizeof(int))];
	meminit(memory, 10 + sizeof(all_mem_info_t) + 10 * (sizeof(memory_block_t) + sizeof(int)));
	char* ptr[10];
	for (int i = 0; i < 10; i++) {
		ptr[i] = (char*)memalloc(1);
	}
	for (int i = 0; i < 10; i++) {
		memfree(ptr[i]);
	}
	EXPECT_TRUE((g_allMemory->startFree)->size == g_allMemory->size - sizeof(all_mem_info_t) - memgetblocksize());
	memdone();
}


TEST(HardTests, 10blocksFreeFromEnd) {
	char memory[10 + sizeof(all_mem_info_t) + 10 * (sizeof(memory_block_t) + sizeof(int))];
	meminit(memory, 10 + sizeof(all_mem_info_t) + 10 * (sizeof(memory_block_t) + sizeof(int)));
	char* ptr[10];
	for (int i = 0; i < 10; i++) {
		ptr[i] = (char*)memalloc(1);
	}
	for (int i = 9; i >= 0; i--) {
		memfree(ptr[i]);
	}
	EXPECT_TRUE((g_allMemory->startFree)->size == g_allMemory->size - sizeof(all_mem_info_t) - memgetblocksize());
	memdone();
}


TEST(HardTests, blockConnection) {
	char memory[10 + sizeof(all_mem_info_t) + 10 * (sizeof(memory_block_t) + sizeof(int))];
	meminit(memory, 10 + sizeof(all_mem_info_t) + 10 * (sizeof(memory_block_t) + sizeof(int)));
	char* ptr[10];
	for (int i = 0; i < 10; i++) {
		ptr[i] = (char*)memalloc(1);
	}
	memfree(ptr[2]);
	memfree(ptr[3]);

	EXPECT_TRUE((char*)g_allMemory->startFree == ptr[2] - sizeof(memory_block_t));
	EXPECT_TRUE((g_allMemory->startFree)->size == 2 + memgetblocksize());

	memfree(ptr[1]);
	EXPECT_TRUE((char*)g_allMemory->startFree == ptr[1] - sizeof(memory_block_t));
	EXPECT_TRUE((g_allMemory->startFree)->size == 3 + 2 * memgetblocksize());

	memfree(ptr[7]);
	memfree(ptr[6]);
	EXPECT_TRUE((char*)(g_allMemory->startFree->next) == ptr[6] - sizeof(memory_block_t));
	EXPECT_TRUE(((g_allMemory->startFree->next))->size == 2 + memgetblocksize());

	memfree(ptr[8]);
	EXPECT_TRUE((char*)(g_allMemory->startFree->next) == ptr[6] - sizeof(memory_block_t));
	EXPECT_TRUE(((g_allMemory->startFree->next))->size == 3 + 2*memgetblocksize());

	memfree(ptr[4]);
	EXPECT_TRUE((g_allMemory->startFree)->size == 4 + 3 * memgetblocksize());

	memfree(ptr[5]);
	EXPECT_TRUE((g_allMemory->startFree)->size == 8 + 7 * memgetblocksize());

	ptr[0] = (char*)memalloc(8 + 7 * memgetblocksize() + 1);
	EXPECT_TRUE(ptr[0] == NULL);
	ptr[1] = (char*)g_allMemory->startFree;
	ptr[0] = (char*)memalloc(8 + 7 * memgetblocksize());
	EXPECT_TRUE(g_allMemory->startFree == NULL);
	EXPECT_TRUE(ptr[0] == ptr[1] + sizeof(memory_block_t));

	memdone();
}