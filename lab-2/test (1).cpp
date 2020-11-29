#include "pch.h"
extern"C" {
#include"memallocator.h"
}

int size = memgetminimumsize() + sizeof(int);

TEST(TestMeminit, NULLPointer) {
	EXPECT_EQ(0, meminit(NULL, 1));
}

TEST(TestMeminit, NegativeSize) {
	void* pMemory = malloc(memgetminimumsize() + 1);
	ASSERT_EQ(0, meminit(pMemory, -1));
	free(pMemory);
}

TEST(TestMeminit, GoodData) {
	void* pMemory = malloc(memgetminimumsize() + 1);
	ASSERT_EQ(1, meminit(pMemory, memgetminimumsize() + 1));
	free(pMemory);
}

TEST(TestMemalloc, NegativeSize){
	char* a = (char*)malloc(size);
	char* rez;

	meminit(a, size);

	rez = (char*)memalloc(-1);

	ASSERT_EQ(rez, (char*)NULL);

	memdone();
	free(a);
}

TEST(TestMemalloc, Size0){
	char* rez;
	char* a = (char*)malloc(size);
	meminit(a, size);

	rez = (char*)memalloc(0);

	ASSERT_EQ(rez, (char*)NULL);

	memdone();
	free(a);
}

TEST(TestMemalloc, SizeBiggerThanMemory){
	char* rez;
	char* a = (char*)malloc(size);
	meminit(a, size);

	rez = (char*)memalloc(sizeof(int) + 1);

	ASSERT_EQ(rez, (char*)NULL);

	memdone();
	free(a);
}


TEST(TestMemalloc, MaxSize){
	int* rez;
	char* a = (char*)malloc(size);
	meminit(a, size);

	rez = (int*)memalloc(sizeof(int));

	ASSERT_NE(rez, (int*)NULL);

	*rez = 30; 

	memdone();
	free(a);
}

TEST(TestMemfree, NULLPointer){
	char* a = (char*)malloc(size);
	meminit(a, size);

	memfree(NULL);

	memdone();
	free(a);
}

TEST(TestMemfree, PtrNotFromMemoryRange){
	char* a = (char*)malloc(size);
	meminit(a, size);

	memfree(a - 1);

	memdone();
	free(a);
}

TEST(TestMemfree, InvalidPtr){

	char* rez;
	char* a = (char*)malloc(size);
	meminit(a, size);

	rez = (char*)memalloc(sizeof(int));
	memfree(rez - 1);

	memdone();
	free(a);
}

TEST(TestMemfree, MemDoned){
	char* a = (char*)malloc(size);
	meminit(a, size);
	memdone();

	memfree(a + 1);

	free(a);
}

TEST(TestMemfree, ValidPtr){

	char* a = (char*)malloc(size);
	int* rez;

	meminit(a, size);

	rez = (int*)memalloc(sizeof(int));
	*rez = 30;
	memfree(rez);
	rez = (int*)memalloc(sizeof(int));
	*rez = 3030;

	memdone();
	free(a);
}