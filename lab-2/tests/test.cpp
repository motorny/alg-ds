#include "pch.h"
#include "../laba_2/memallocator.h"
#include "../laba_2/memallocator.c"

#define _CRT_SECURE_NO_WARNINGS
TEST(memInit, NullPtr_ERROR) {
	char* pointer = NULL;
	ASSERT_EQ(ERROR, meminit(pointer, 100));
	memdone();
}

TEST(memInit, NullSize_ERROR ){
	char a[100];
	ASSERT_EQ(ERROR, meminit(a, 0));
	memdone();
}

TEST(memInit, valid_OK)
{
	char a[100];
	ASSERT_EQ(OK, meminit(a, 100));
	memdone();
}

TEST(memInit, invlidSize_ERROR)
{
	char a[10];
	ASSERT_EQ(ERROR, meminit(a, 10));
	memdone();
}


TEST(memInit, reinit_ERROR)
{
	char a[20];
	char b[20];
	meminit(a, 20);
	ASSERT_EQ(ERROR, meminit(b, 20));
	memdone();
}

TEST(Memalloc, invalidSize_ERROR)
{
	char a[100];
	meminit(a, 100);
	ASSERT_EQ(NULL, memalloc(0));
	ASSERT_EQ(NULL, memalloc(-1));
	memdone();
}

TEST(Memalloc, validSize_OK)
{
	char a[100];
	char* b, * c;
	int size = sizeof(block_t);
	int size2 = size * 2 + 20;
	//int size1 = memgetminimumsize();
	meminit(a, 100);
	b = (char*)memalloc(20);
	c = (char*)memalloc(20);
	

	ASSERT_EQ(&a[size], b);
	ASSERT_EQ(&a[size2], c);
	memdone();
}

TEST(Memalloc, notEnoughMemory_ERROR)
{
	char a[20];
	char* b;
	meminit(a, 20);
	b = (char*)memalloc(40);

	ASSERT_EQ(NULL, b);
	memdone();
}

TEST(Memfree, checkCorrectWorking)
{
	char a[25];
	int size = sizeof(block_t);
	char* p1, * p2;
	meminit(a, 25);
	p1 = (char*)memalloc(1);
	memfree(p1);
	p2 = (char*)memalloc(1);
	ASSERT_EQ(&a[size], p2);
	memdone();
}

TEST(Memfree, mergeBlocksRightCheck)
{
	char a[100];
	int size = sizeof(block_t);
	char* d, * b, * c, * check;
	meminit(a, 100);
	b = (char*)memalloc(20);
	c = (char*)memalloc(20);
	d = (char*)memalloc(10);
	memfree(b);
	memfree(c);
	//ASSERT_EQ(memList->size, 52);
	check = (char*)memalloc(30);
	ASSERT_EQ(&a[size], check);
	memdone();
}

TEST(Memfree, mergeBlocksLeftCheck)
{
	char a[100];
	meminit(a, 100);
	int size = sizeof(block_t);
	char* d, * b, * c, * check;
	meminit(a, 100);
	b = (char*)memalloc(20);
	c = (char*)memalloc(20);
	d = (char*)memalloc(10);
	memfree(c);
	memfree(b);
	check = (char*)memalloc(30);
	ASSERT_EQ(&a[size], check);
	memdone();
}

TEST(Memfree, mergeBlocksFromTwoSidesCheck)
{
	char a[100];
	meminit(a, 100);
	int size = sizeof(block_t);
	char* d, * b, * c, * check;
	meminit(a, 100);
	b = (char*)memalloc(20);
	c = (char*)memalloc(20);
	d = (char*)memalloc(10);
	memfree(b);
	memfree(d);
	memfree(c);
	check = (char*)memalloc(60);
	ASSERT_EQ(&a[size], check);
	memdone();
}

TEST(Memgetminsize, Example) {
	// memgetminsize() + 1 = 13
	char ptr[13];
	char* p;
	meminit(ptr, memgetminimumsize() + 1);
	p = (char*)memalloc(1);// Success!
	ASSERT_EQ(&ptr[12], p);
	memfree(p);
	memdone();
}