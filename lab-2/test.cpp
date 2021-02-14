#include "pch.h"
#include "gtest/gtest.h"

extern "C" {
#include "memallocator.h"
}

TEST(meminit_test, null_input)
{
	EXPECT_EQ(meminit(NULL, 100), NULL_INPUT);
	memdone();
}

TEST(meminit_test, right_input)
{
	char ptr[100];

	EXPECT_EQ(meminit(ptr, 100), 0);
	EXPECT_EQ(firstHead->size, 100 - memgetblocksize());
	EXPECT_EQ((char*)firstHead, ptr);
	memdone();
}

TEST(memalloc_test, not_enought_memory)
{
	char ptr[40];
	meminit(ptr, 40);
	char* testPtr1 = (char*)memalloc(100);
	char* testPtr2 = (char*)memalloc(40);
	EXPECT_TRUE(testPtr1 == NULL);
	EXPECT_TRUE(testPtr2 == NULL);
	memdone();
}

TEST(memalloc_test, no_free_block)
{
	char ptr[30];
	meminit(ptr, 30);
	((End*)((char*)firstHead + firstHead->size + sizeof(Head)))->size = -1;
	firstHead = NULL;
	char* testPtr = (char*)memalloc(1);
	EXPECT_TRUE(testPtr == NULL);
	memdone();
}

TEST(memfree_test, defragmentation)
{
	char* ptr[500];

	meminit(ptr, 500);
	char* testPtr1 = (char*)memalloc(100 - memgetminimumsize());
	char* testPtr2 = (char*)memalloc(100 - memgetminimumsize());
	char* testPtr3 = (char*)memalloc(100 - memgetminimumsize());
	char* testPtr4 = (char*)memalloc(100 - memgetminimumsize());
	char* testPtr5 = (char*)memalloc(100 - memgetminimumsize());

	memfree(testPtr3);
	memfree(testPtr1);
	memfree(testPtr2);
	memfree(testPtr5);
	memfree(testPtr4);

	EXPECT_TRUE((char*)firstHead == memory && (char*)firstHead + firstHead->size + memgetminimumsize() == memory + memsize);
	memdone();
}

TEST(memalloc_test, right_input)
{
	char ptr[30];
	int size = 30 - memgetminimumsize();
	meminit(ptr, 30);
	char* buf = (char*)memalloc(size);

	EXPECT_EQ(((Head*)(buf - sizeof(Head)))->size, size);
	EXPECT_EQ(((Head*)(buf + size))->size, -1);
	EXPECT_EQ(((Head*)(buf - sizeof(Head)))->check, CHECK_NUMBER);
	memdone();
}

TEST(memfree_test, right_input)
{
	char ptr[30];
	int size = 20 - sizeof(End) - sizeof(Head);
	meminit(ptr, 30);
	char* testPtr = (char*)memalloc(size);
	memfree(testPtr);

	EXPECT_TRUE((char*)firstHead == (char*)ptr);
	memdone();
}

TEST(memalloc, not_right_zise)
{
	char ptr[30];
	meminit(ptr, 30);

	EXPECT_EQ(NULL, memalloc(-1));
	memdone();
}