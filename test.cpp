#include "pch.h"
#include "memallocator.h"


TEST(Init, Not_Enough_Space) {
	char pMemory[1000];
	EXPECT_EQ(meminit(pMemory, memgetminimumsize() - 1), 0);
}

TEST(Init, Enough_Space) {
	char pMemory[1000];
	EXPECT_EQ(meminit(pMemory, memgetminimumsize()+1), 1);
}

TEST(Init, Null_Ptr) {
	char* pMemory = NULL;
	EXPECT_EQ(meminit(pMemory, memgetminimumsize()),0);
}


TEST(Mem_Alloc, Null_Size_Block) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = 0;
	void* ptr = memalloc(size);
	EXPECT_EQ(ptr, (void*) 0);
}

TEST(Mem_Alloc, Negative_Size) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = -100;
	void* ptr = memalloc(size);
	EXPECT_EQ(ptr, (void*)NULL);
}

TEST(Mem_Alloc, Not_Null_Size_Block) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = 100;
	void* ptr = memalloc(size);
	EXPECT_EQ(ptr, pMemory + sizeof(int) + sizeof(int) + sizeof(void*));
}


TEST(Mem_Alloc, Not_Enough_Space) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = 1000;
	char* ptr = (char*)memalloc(size);
	EXPECT_TRUE(ptr == NULL);
}

TEST(Mem_Free, Union_Right) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = 100;
	char* ptr = (char*)memalloc(size);
	memfree(ptr);

	int pMemSize = *((int*)pMemory);		
	EXPECT_EQ(pMemSize, 1000);
}

TEST(Mem_Free, Union_Right_Left) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = 100;
	char* ptr1 = (char*)memalloc(size);
	char* ptr2 = (char*)memalloc(size);
	memfree(ptr1);
	memfree(ptr2);

	int pMemSize = *((int*)pMemory);
	EXPECT_EQ(pMemSize, 1000);
}

TEST(Mem_Free, Union_Left) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = 100;
	char* ptr1 = (char*)memalloc(size);
	char* ptr2 = (char*)memalloc(size);
	char* ptr3 = (char*)memalloc(size);
	memfree(ptr1);
	memfree(ptr2);

	int pMemSize = *((int*)pMemory);
	EXPECT_EQ(pMemSize, 2 * (size + memgetminimumsize()));
}

TEST(Mem_Free, No_Union) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = 100;
	char* ptr1 = (char*)memalloc(size);
	char* ptr2 = (char*)memalloc(size);

	memfree(ptr1);

	int pMemSize = *((int*)pMemory);
	EXPECT_EQ(pMemSize,  (size + memgetminimumsize()));
}

TEST(Example, Example0) {
		char pMemory[1000];
		meminit(pMemory, 1000);
		int size = 100;
		char* ptr1 = (char*)memalloc(size);
		char* ptr2 = (char*)memalloc(size);
		char* ptr3 = (char*)memalloc(size);
		memfree(ptr1);
		memfree(ptr2);
		memfree(ptr3);

		int pMemSize = *((int*)pMemory);
		EXPECT_EQ(pMemSize, 1000);
	}


TEST(Example, Example) {
	char pMemory[1000];
	meminit(pMemory, 1000);
	int size = 50;
	char* ptr1 = (char*)memalloc(size);
	char* ptr2 = (char*)memalloc(size);
	char* ptr3 = (char*)memalloc(size);
	char* ptr4 = (char*)memalloc(size);
	char* ptr5 = (char*)memalloc(size);

	memfree(ptr2);
	memfree(ptr3);
	memfree(ptr5);
	memfree(ptr4);
	memfree(ptr1);

	int pMemSize = *((int*)pMemory);
	EXPECT_EQ(pMemSize, 1000);
}
	
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}