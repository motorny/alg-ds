#include "pch.h"
#include"../MallocFree/MallocFree.c"


TEST(meminit, return1) 
{

	EXPECT_EQ(1, meminit(NULL, 1));

}

TEST(meminit, NegativeSizeReturn1)
{
	void* ptr = malloc(memgetminimumsize() + 1);

	EXPECT_EQ(1, meminit(ptr, -1));
	

	free(ptr);
}

TEST(meminit, CorrectDataReturn1)
{
	void* ptr = malloc(memgetminimumsize() + 1);

	EXPECT_EQ(1, meminit(ptr, memgetminimumsize() + 1));

	free(ptr);
}

TEST(memalloc, return0) 
{
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);

	EXPECT_EQ(0, memalloc(-1));

	free(ptr);
}

TEST(memalloc, returnValidPointer)
{
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);

	void* p1 = memalloc(1);
	EXPECT_TRUE(p1 != NULL);

	memfree(p1);
	free(ptr);
}

TEST(memalloc, returnNULL)
{
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	void* p1 = memalloc(2);
	EXPECT_TRUE(p1 == NULL);
	memfree(p1);
	free(ptr);
}

TEST(memfree, freeNULL) 
{
    void* p = malloc(memgetminimumsize() + sizeof(int));
    meminit(p, memgetminimumsize() + sizeof(int));
    char* s = (char*)memalloc(memgetminimumsize());
    memfree(s);
    memdone();
    free(p);
}

TEST(memfree, freeNotOurMemory) 
{
    char* p = (char*)malloc(memgetminimumsize() + sizeof(int));
    meminit(p, memgetminimumsize() + sizeof(int));
    memfree(p + 100);
    memdone();
    free(p);
}

TEST(memfree, freeNotOurAllocatedMemory)
{
    char* p = (char*)malloc(10 * memgetminimumsize());
    meminit(p, 10 * memgetminimumsize());
    char* s = (char*)memalloc(1);
    memfree(p + 5 * memgetminimumsize() + sizeof(char));
    memdone();
    free(p);
}


