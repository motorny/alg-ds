#include "pch.h"
#include "gtest/gtest.h"

extern "C" {
#include"../LabB10/memallocator.c"
}
TEST(meminit_NULLpointer, return1) {
	EXPECT_EQ(1, meminit(NULL, 1));
}
TEST(meminit_CorrectData, return0) {
	void* p = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(0, meminit(p, memgetminimumsize() + 1));
	free(p);
}
TEST(meminit_NegativeSize, return1) {
	void* p = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(1, meminit(p, -1));
	free(p);
}
TEST(memalloc_NegativeSize, return0) {
	void* p = malloc(memgetminimumsize() + 1);
	meminit(p, memgetminimumsize() + 1);
	EXPECT_EQ(0, memalloc(-1));
	free(p);
}
TEST(memalloc_NotEnoughMem, returnNULL) {
	void* p = malloc(memgetminimumsize() + 1);
	meminit(p, memgetminimumsize() + 1);
	void* p1 = memalloc(2);
	EXPECT_TRUE(p1 == NULL);
	memfree(p1);
	free(p);
}
TEST(memalloc_CorrectData, returnValidPointer) {
	void* p = malloc(memgetminimumsize() + 1);
	meminit(p, memgetminimumsize() + 1);
	void* p1 = memalloc(1);
	EXPECT_TRUE(p1 != NULL);
	memfree(p1);
	free(p);
}