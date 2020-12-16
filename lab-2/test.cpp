#include "pch.h"


extern "C" {
#include "C:/Users/Lenovo/source/repos/AlgB12/memallocator.h"
#include "C:/Users/Lenovo/source/repos/AlgB12/my.cpp"
}


TEST(meminit, meminit_NullPointerToMemory_ReturnZero) {
	char* memory = NULL;
	EXPECT_EQ(meminit(memory, 1), 0);
}

TEST(meminit, meminit_Smallsize_ReturnZero) {
	char* memory = (char*)malloc(memgetminimumsize() - 1);
	EXPECT_EQ(meminit(memory, memgetminimumsize() - 1), 0);
	free(memory);
}

TEST(meminit, meminit_SuccessCase_ReturnsOne) {
	char* memory = (char*)malloc(memgetminimumsize() + 1);
	EXPECT_EQ(meminit(memory, memgetminimumsize() + 1), 1);
	free(memory);
}

TEST(memalloc, memalloc_AllocateNegativeSize_ReturnsNULL) {
	char* memory = (char*)malloc(memgetminimumsize() + 1);
	meminit(memory, memgetminimumsize() + 1);
	char* ptr = (char*)memalloc(-1);
	EXPECT_EQ(ptr, (char*)NULL);
	free(memory);
}

TEST(memalloc, memalloc_AllocateValidMemory_ReturnPtr) {
	char* memory = (char*)malloc(memgetminimumsize() + 1);
	meminit(memory, memgetminimumsize() + 1);
	char* ptr = (char*)memalloc(1);
	EXPECT_NE(ptr, (char*)NULL);
	free(memory);
}

TEST(memfree, memfree_FreeValidPtr_ReturnSuccess) {
	char* memory = (char*)malloc(memgetminimumsize() + 1);
	meminit(memory, memgetminimumsize() + 1);
	char* ptr = (char*)memalloc(1);
	memfree(ptr);
	EXPECT_EQ(Allocator.desc->size, -1);
	EXPECT_EQ(Allocator.desc->next, (descriptor*)NULL);
	free(memory);
}

TEST(memfree, memfree_NeedToMergeNeighbourBlocks_SuccessfulMerging) {
	char* memory = (char*)malloc(memgetminimumsize() + 2 * memgetblocksize() + 3);
	char* ptr1, *ptr2, *ptr3;
	meminit(memory, memgetminimumsize() + 2 * memgetblocksize() + 3);
	ptr1 = (char*)memalloc(1);
	ptr2 = (char*)memalloc(1);
	ptr3 = (char*)memalloc(1);
	memfree(ptr1);
	memfree(ptr3);
	memfree(ptr2);
	EXPECT_EQ(Allocator.desc->size, -(memgetminimumsize() + memgetblocksize() + 3));
	EXPECT_EQ(Allocator.desc->next, (descriptor*)NULL);
	free(memory);
}

TEST(memfree, memfree_TryToFreeEmptyPointer_ReturnSuccess) {
	char* memory = (char*)malloc(memgetminimumsize() + 1);
	char* ptr;
	meminit(memory, memgetminimumsize() + 1);
	ptr = (char*)memalloc(1);
	memfree(ptr);
	memfree(ptr); //attempt to free empty pointer
	EXPECT_EQ(Allocator.desc->size, -1); //negative size means free memory
	EXPECT_EQ(Allocator.desc->next, (descriptor*)NULL);
}