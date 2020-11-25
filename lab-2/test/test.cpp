#include "pch.h"
#include "../Alg_Lab_B/memallocator.cpp"

TEST(meminitTest, NullInputTest)
{
	EXPECT_EQ(meminit(NULL, 100), FAILURE);
	memdone();
}

TEST(meminitTest, SmallSizeTest)
{
	void* test = malloc(memgetminimumsize() - 1);
	EXPECT_EQ(meminit(test, memgetminimumsize() - 1), FAILURE);
	free(test);
	memdone();
}

TEST(meminitTest, AllCorrectTest)
{
	void* test = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(meminit(test, memgetminimumsize() + 1), SUCCESS);
	EXPECT_EQ(memSize, memgetminimumsize() + 1);
	EXPECT_EQ((char*)firstBlock, test);
	EXPECT_EQ(firstBlock->size, 1);
	EXPECT_EQ(firstBlock->magicKey, MAGICKEY);
	free(test);
	memdone();
}

TEST(memallocTest, WithoutInit) {
	EXPECT_EQ(memalloc(10), (void*)NULL);
}

TEST(memallocTest, NotEnoughMemory) {
	char memory[10];
	meminit(memory, 10);
	char* test = (char*)memalloc(20);
	EXPECT_TRUE(test == NULL);
	memdone();
}

TEST(memallocTest, NegSize) {
	char memory[10];
	meminit(memory, 10);
	char* test = (char*)memalloc(-10);
	EXPECT_TRUE(test == NULL);
	memdone();
}

TEST(memallocTest, AllCorrectMemalloc)
{
	char memory[30];
	meminit(memory, 30);
	char* test = (char*)memalloc(30 - memgetminimumsize());

	EXPECT_EQ(((block_head_t*)(test - sizeof(block_head_t)))->size, 30 - memgetminimumsize());
	EXPECT_EQ(((block_head_t*)(test + 30 - memgetminimumsize()))->size, -1);
	EXPECT_EQ(((block_head_t*)(test - sizeof(block_head_t)))->magicKey, MAGICKEY);
	memdone();
}

TEST(memfreeTest, AllCorrectFree) {
	char memory[50];
	meminit(memory, 50);

	char* test1 = (char*)memalloc(20);
	char* test2 = (char*)memalloc(20);
	char* test3 = (char*)memalloc(20);

	memfree(test2);
	memfree(test1);
	memfree(test3);

	EXPECT_EQ((char*)firstBlock, (char*)memory);
	memdone();
}
