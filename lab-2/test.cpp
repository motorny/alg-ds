#include "pch.h"
#include "../Lab2_Kungurov_13/mem.h"
extern mem_t myMem;
TEST(TestMemoryInitialise, NullPtrReturnFailed) {
	char* pMemory = NULL;
	EXPECT_EQ(FAILED, meminit(pMemory, 2));
}
TEST(TestMemoryInitialise, SizeLessThenMinReturnFailed) {
	char* pMemory = (char*)malloc(2 * sizeof(block_t) + 2 * sizeof(int) - 1);
	EXPECT_EQ(FAILED, meminit(pMemory, 2 * sizeof(block_t) + 2 * sizeof(int) - 1));
	free(pMemory);
}

TEST(TestMemoryInitialise, ValidInputReturnSuccess) {
	char* pMemory = (char*)malloc(2 * sizeof(block_t) + 2 * sizeof(int) + 1);
	EXPECT_EQ(SUCCESS, meminit(pMemory, 2 * sizeof(block_t) + 2 * sizeof(int) + 1));
	memdone();
	free(pMemory);
}


TEST(TestMemoryAllocation, UninitializedMemSystemReturnNull) {
	char* pMemory = (char*)memalloc(2);

	EXPECT_EQ(NULL, pMemory);
}

TEST(TestMemoryAllocation, NotEnoughMemoryReturnNull) {
	char* pHead = (char*)malloc(2 * sizeof(block_t) + 2 * sizeof(int) + 1);
	meminit(pHead, 2 * sizeof(block_t) + 2 * sizeof(int) + 1);
	char* pMemory = (char*)memalloc(2);

	EXPECT_EQ(NULL, pMemory);
	memdone();
	free(pHead);
}

TEST(TestMemoryAllocation, InitializedMemSystemReturnValidVal) {
	char* pHead = (char*)malloc(2 * sizeof(block_t) + 2 * sizeof(int) + 2);
	meminit(pHead, 2 * sizeof(block_t) + 2 * sizeof(int) + 2);
	char* pMemory = (char*)memalloc(1);

	EXPECT_NE((char*)NULL, pMemory);
	memfree(pMemory);
	memdone();
	free(pHead);
}

TEST(TestMemDone, ReturnValidVal) {
	char* pHead = (char*)malloc(2 * sizeof(block_t) + 2 * sizeof(int) + 2);
	meminit(pHead, 2 * sizeof(block_t) + 2 * sizeof(int) + 2);

	memdone();

	EXPECT_EQ(NULL, myMem.pToHead);
	EXPECT_EQ(NULL, myMem.pToLast);
	EXPECT_EQ(0, myMem.sizeInSum);
	free(pHead);

}
