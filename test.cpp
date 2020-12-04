#include "pch.h"
extern"C" {
#include"..\LabB.h\memallocator.cpp"
}

TEST(Test, Test_meminit_NULL_return0) {
	EXPECT_EQ(0, meminit(NULL, 1));
}

TEST(Test, Test_meminit_negativesize_return0) {
	void* fortest = malloc(memgetminimumsize() + 1);
	ASSERT_EQ(0, meminit(fortest, -1));
	free(fortest);
}

TEST(Test, Test_meminit_ok_return1) {
	void* fortest = malloc(memgetminimumsize() + 1);
	ASSERT_EQ(1, meminit(fortest, memgetminimumsize() + 1));
	free(fortest);
}

TEST(Test, Test_memalloc_negative_return0) {
	char* fortest = (char*)malloc(memgetminimumsize() + sizeof(int));
	char* rezult;
	meminit(fortest, memgetminimumsize() + sizeof(int));
	rezult = (char*)memalloc(-1);

	ASSERT_EQ(rezult, (char*)0);

	memdone();
	free(fortest);
}

TEST(Test, Test_memalloc_0_return0) {
	char* fortest = (char*)malloc(memgetminimumsize() + sizeof(int));
	char* rezult;
	meminit(fortest, memgetminimumsize() + sizeof(int));
	rezult = (char*)memalloc(0);

	ASSERT_EQ(rezult, (char*)0);

	memdone();
	free(fortest);
}

TEST(Test, Test_memalloc_toobigsize_return0) {
	char* fortest = (char*)malloc(memgetminimumsize() + sizeof(int));
	char* rezult;
	meminit(fortest, memgetminimumsize() + sizeof(int));
	rezult = (char*)memalloc(sizeof(int) + 1);

	ASSERT_EQ(rezult, (char*)0);

	memdone();
	free(fortest);
}


TEST(Test, Test_memalloc_maximum_0) {
	char* fortest = (char*)malloc(memgetminimumsize() + sizeof(int));
	int* rezult;
	meminit(fortest, memgetminimumsize() + sizeof(int));
	rezult = (int*)memalloc(sizeof(int));

	ASSERT_NE(rezult, (int*)0);

	memdone();
	free(fortest);
}