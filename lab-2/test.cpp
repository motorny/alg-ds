#include "pch.h"
#include "../../Lab-Bh/Lab-Bh/memallocator.c"


TEST(MemInitTests, MemInitNull) {
	int tmp = MemInit(NULL, 1);
	ASSERT_EQ(0, tmp);
}

TEST(MemInitTests, MemInitOk) {
	void* tmp = malloc(sizeof(block_t) + sizeof(int));
	ASSERT_EQ(1, MemInit(tmp, sizeof(block_t) + 1));
	free(tmp);
}

TEST(MemInitTests, MemInitNotOk) {
	void* tmp = malloc(sizeof(block_t) + sizeof(int));
	ASSERT_EQ(1, MemInit(tmp, -1));
	free(tmp);
}

TEST(MemallocTests, MemallocNotOk_Negative) {
	char* tmp = (char*)malloc(sizeof(block_t) + sizeof(int));
	char* tmp1;
	MemInit(tmp, sizeof(block_t) + sizeof(int));
	tmp1 = (char*)Memalloc(-1);

	ASSERT_EQ(tmp1, (char*)0);
	
	clear();
	free(tmp);
}

TEST(MemallocTests, MemallocNotOk) {
	char* tmp = (char*)malloc(sizeof(block_t) + sizeof(int));
	int* tmp1;
	MemInit(tmp, sizeof(block_t) + sizeof(int));
	tmp1 = (int*)Memalloc(sizeof(int*)+1);

	ASSERT_EQ(tmp1, (int*)0);

	clear();
	free(tmp);
}

TEST(MemallocTests, MemallocOk) {
	char* tmp = (char*)malloc(sizeof(block_t) + sizeof(int));
	int* tmp1;
	MemInit(tmp, sizeof(block_t) + sizeof(int));
	tmp1 = (int*)Memalloc(sizeof(int*));

	ASSERT_NE(tmp1, (int*)0);

	clear();
	free(tmp);
}