#include "pch.h"
extern "C"{
#include"memallocator.h"
}

TEST(meminit_NULLpointer, return0) {
	EXPECT_EQ(0, meminit(NULL, 1));
}

TEST(meminit_NegativeSize, return0) {
	void* ptr = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(0, meminit(ptr, -1));
	free(ptr);
}

TEST(meminit_CorrectData, return1) {
	void* ptr = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(1, meminit(ptr, memgetminimumsize() + 1));
	free(ptr);
}

TEST(memalloc_NegativeSize, return0) {
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	EXPECT_EQ(0, memalloc(-1));
	free(ptr);
}

TEST(memalloc_CorrectData, returnValidPointer) {
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	void* p1 = memalloc(1);
	EXPECT_TRUE(p1 != NULL);
	memfree(p1);
	free(ptr);
}

TEST(memalloc_NotEnoughMem, returnNULL) {
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	void* p1 = memalloc(2);
	EXPECT_TRUE(p1 == NULL);
	memfree(p1);
	free(ptr);
}
