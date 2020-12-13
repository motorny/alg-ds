#include "pch.h"

extern "C"
{
#include "memallocator.h"
}
#pragma warning(disable:4996)

TEST(meminit, TestTrue) {

	char* pMemory = NULL;
	int size = memgetminimumsize() + 1;
	int ind;

	pMemory = (char*)malloc(size);
	ind = meminit(pMemory, size);
	EXPECT_EQ(ind, NOT_ERRORS);
	free(pMemory);
}

TEST(meminit, TestFalse) {

	char* pMemory = NULL;
	int ind = meminit(pMemory, 1);

	EXPECT_EQ(ind, ERROR_INIT);
}

TEST(meminit, TestMinsizeTrue) {

	int size = memgetminimumsize() + 1;
	char* pMemory = (char*)malloc(size);
	int ind = meminit(pMemory, size);

	EXPECT_EQ(ind, NOT_ERRORS);
	free(pMemory);
}

TEST(memalloc, TestNotNULL) {

	int size = memgetminimumsize() + 1;

	char* pMemory = (char*)malloc(size);
	meminit(pMemory, size);

	char* temp = (char*)memalloc(1);

	EXPECT_NE(temp, (char*)NULL);

	memfree(temp);
	free(pMemory);
}

TEST(memalloc, TestErrorMemory) {

	int size = memgetminimumsize() + 1;

	char* pMemory = (char*)malloc(size);
	meminit(pMemory, size);

	void* temp = memalloc(2);
	EXPECT_TRUE(!temp);


	memfree(temp);
	free(pMemory);
}

TEST(memalloc, TestSizeLessThanZero) {

	int size = memgetminimumsize() + 1;

	char* pMemory = (char*)malloc(size);
	meminit(pMemory, size);

	char* temp = (char*)memalloc(-1);
	EXPECT_EQ(temp, (char*)NULL);

	free(pMemory);
}

int main(void) {

	return RUN_ALL_TESTS();
}