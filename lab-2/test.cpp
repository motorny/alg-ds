#include "pch.h"

extern "C" {
#include "..\LAB_B10\memallocator.h"
#include "..\LAB_B10\memallocator.cpp"
}


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(memalloc, NoMemory_retNULL) {
	void* heap = malloc(memgetminimumsize() + 1);
	meminit(heap, memgetminimumsize() + 1);
	void* p = memalloc(2);
	EXPECT_TRUE (p == NULL);
	memfree(p);
	free(heap);
}

TEST(memalloc, WrongSize_ret0) {
	void* heap = malloc(memgetminimumsize() + 1);
	meminit(heap, memgetminimumsize() + 1);
	EXPECT_EQ(0, memalloc(-3));
	free(heap);
}

TEST(memalloc, ValidData_retNoNullPointer) {
	void* heap = malloc(memgetminimumsize() + 1);
	meminit(heap, memgetminimumsize() + 1);
	void* p = memalloc(1);
	EXPECT_TRUE(p != NULL);
	memfree(p);
	free(heap);
}

TEST(meminit, InputNullPointer_ret0) {
	EXPECT_EQ(0, meminit(NULL, 1));
}

TEST(meminit, WrongSize_ret0) {
	void* heap = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(0, meminit(heap, -1));
	free(heap);
}

TEST(meminit, ValidData_ret1) {
	void* heap = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(1, meminit(heap, memgetminimumsize() + 1));
	free(heap);
}

TEST(memfree, NullPointer_DoNotCrush) {
	void* heap = malloc(memgetminimumsize() + 1);
	meminit(heap, memgetminimumsize() + 1);
	memfree(NULL);
	memdone();
	free(heap);
}

TEST(memfree, InvalidPointer_DoNotCrush) {
	void* heap = malloc(memgetminimumsize() + 1);
	void* output = memalloc(1);
	meminit(heap, memgetminimumsize() + 1);
	memfree(output);
	memdone();
	free(heap);
}

TEST(memfree, Ok_DoNotCrush) {
	void* heap = malloc(memgetminimumsize() + 1);
	meminit(heap, memgetminimumsize() + 1);
	memdone();
	memfree(heap);
	free(heap);
}