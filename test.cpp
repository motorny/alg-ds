#include "pch.h"
extern "C"

{
#include "memallocator.h"
}

#pragma warning(disable:4996)


TEST(TestMeminit, TriggeringConditions) {
	void* testm;
	int additive = 1;

	testm = malloc(memgetminimumsize() + additive);
	int testperem;
	testperem = meminit(testm, -1);
	ASSERT_EQ(0, testperem);

	testperem = meminit(testm, memgetminimumsize() + additive);
	ASSERT_EQ(1, testperem);
	free(testm);
}

TEST(TestMeminit, NULLed) {
	int testperem = meminit(NULL, 1);
	ASSERT_EQ(0, testperem);
}

TEST(TestMemalloc, TooSmallSize) {
	int additive = sizeof(int);
	char* testm = (char*)malloc(memgetminimumsize() + additive);
	char* testperem;

	meminit(testm, memgetminimumsize() + additive);

	testperem = (char*)memalloc(-3);

	ASSERT_EQ(testperem, (char*)NULL);

	testperem = (char*)memalloc(0);

	ASSERT_EQ(testperem, (char*)NULL);

	memdone();
	free(testm);
}

TEST(TestMemalloc, TooBigSize) {
	int additive = sizeof(int);
	char* testm = (char*)malloc(memgetminimumsize() + additive);
	char* testperem;

	meminit(testm, memgetminimumsize() + additive);

	testperem = (char*)memalloc(additive + 1);

	ASSERT_EQ(testperem, (char*)NULL);

	memdone();
	free(testm);
}

TEST(TestMemfree, NULLed) {
	int additive = sizeof(int);
	char* testm = (char*)malloc(memgetminimumsize() + additive);

	meminit(testm, memgetminimumsize() + additive);

	memfree(NULL);

	memdone();
	free(testm);
}

TEST(TestMemfree, IncorrectPointer) {
	int additive = sizeof(int);
	char* testm = (char*)malloc(memgetminimumsize() + additive);
	char* testperem;

	meminit(testm, memgetminimumsize() + additive);

	testperem = (char*)memalloc(additive);

	memfree(testperem - 1);

	memdone();
	free(testm);
}

int main(void) {

	return RUN_ALL_TESTS();
}