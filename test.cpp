#include "pch.h"
#include "../LabBMalloc.2/memallocator.c"

TEST(memInit, NULLpointer_Minus1)
{
	char* a = NULL;
	ASSERT_EQ(-1, meminit(a, 100));
	memdone();
}

TEST(memInit, NULLsize_Minus1)
{
	char a[100];
	ASSERT_EQ(-1, meminit(a, 0));
	memdone();
}

TEST(memInit, validArguments_1)
{
	char a[100];
	ASSERT_EQ(1, meminit(a, 100));
	memdone();
}

TEST(memInit, sizeLessMin_Minus1)
{
	char a[10];
	ASSERT_EQ(-1, meminit(a, 10));
	memdone();
}

TEST(memInit, reinitialization_Minus1)
{
	char a[20];
	char b[20];
	meminit(a, 20);
	ASSERT_EQ(-1, meminit(b, 20));
	memdone();
}

TEST(memalloc, NULLMinusBytes_NULL)
{
	char a[100];
	meminit(a, 100);
	ASSERT_EQ(NULL, memalloc(0));
	ASSERT_EQ(NULL, memalloc(-1));
	memdone();
}

TEST(memalloc, PositiveBytes_ValidPointer)
{
	char a[100];
	char* b, * c;
	meminit(a, 100);
	b = (char*)memalloc(20);
	c = (char*)memalloc(20);

	ASSERT_EQ(&a[8], b);
	ASSERT_EQ(&a[40], c);
	memdone();
}

TEST(memalloc, notEnoughMemory_NULL)
{
	char a[20];
	char* b;
	meminit(a, 20);
	b = (char*)memalloc(40);

	ASSERT_EQ(NULL, b);
	memdone();
}

TEST(memfree, freeFirstAndMallocSecond_Memory)
{
	char a[25];
	char* p1, * p2;
	meminit(a, 25);
	p1 = (char*)memalloc(1);
	memfree(p1);
	p2 = (char*)memalloc(1);
	ASSERT_EQ(&a[8], p2);
	memdone();
}

TEST(memfree, mergeBlocksRight)
{
	char a[100];
	char* d, * b, * c;
	meminit(a, 100);
	b = (char*)memalloc(20);
	c = (char*)memalloc(20);
	d = (char*)memalloc(10);
	memfree(b);
	memfree(c);
	ASSERT_EQ(52, *(int*)(a));
	memdone();
}

TEST(memfree, mergeBlocksLeft)
{
	char a[100];
	meminit(a, 100);
	char* d, * b, * c;
	meminit(a, 100);
	b = (char*)memalloc(20);
	c = (char*)memalloc(20);
	d = (char*)memalloc(10);
	memfree(c);
	memfree(b);
	ASSERT_EQ(52, *(int*)(a));
	memdone();
}

TEST(memfree, mergeBlocksTwoSides)
{
	char a[100];
	meminit(a, 100);
	char* d, * b, * c;
	meminit(a, 100);
	b = (char*)memalloc(20);
	c = (char*)memalloc(20);
	d = (char*)memalloc(10);
	memfree(b);
	memfree(d);
	memfree(c);
	ASSERT_EQ(88, *(int*)(a));
	memdone();
}