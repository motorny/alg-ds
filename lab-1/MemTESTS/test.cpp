#include "pch.h"

#include "..\LAB-2\LAB-2.cpp"

extern MemSyst_t Mem;

#define TRUE 1
#define FALSE 0
#define MIN_SIZE (SIZE + 1)

TEST(ValidPointInvalidSize, meminit) {
	char* mem = (char*)malloc(SIZE);
	EXPECT_EQ(meminit(mem, SIZE), TRUE);
	free(mem);
}

TEST(NullPoint, meminit) {
	char* mem = NULL;
	EXPECT_EQ(meminit(mem, MIN_SIZE), TRUE);
}

TEST(NotEnoughSpace, memalloc) {
	char a[30];
	meminit(a, 30);
	void* p = memalloc(30);
	EXPECT_EQ(p, (void*)0);
}

TEST(EnoughSpace, memalloc) {
	char a[100];
	meminit(a, 20);
	void* p = memalloc(20);
	EXPECT_FALSE(p != (void*)0);
}

TEST(VallocWithoutInit, memalloc) {
	char* p = (char*)memalloc(1);
	EXPECT_EQ(p, (char*)nullptr);
}

TEST(PtrOutsideMemory, memfree) {
	char* mem = (char*)malloc(MIN_SIZE);
	meminit(mem, MIN_SIZE);
	memfree(mem - 1);
	memdone();
	free(mem);
}

TEST(ReturnValidVal,memdone) {
	char* head = (char*)malloc(2 * MIN_SIZE);
	meminit(head, 2 * MIN_SIZE);
	memdone();
	EXPECT_EQ(0, Mem.totalSize);
	EXPECT_EQ(NULL, Mem.bufBlock);
	EXPECT_EQ(NULL, Mem.curBlock);
	free(head);

}
