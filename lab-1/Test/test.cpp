#include "pch.h"
extern "C" {
#include "../Laba_2_15/memallocator.h"
}

TEST(meminit_NULLptr, mem_error) {
	ASSERT_EQ(meminit(NULL, 50), -1);
	memdone();
}

TEST(meminit_negsize, mem_error) {
	void* p = malloc(100);
	ASSERT_EQ(meminit(p, -30), -1);
	memdone();
	free(p);
}

TEST(meminit_rightinput, mem_good) {
	void* p = malloc(1000);
	ASSERT_EQ(meminit(p, 100), 1);
	memdone();
	free(p);
}

TEST(meminit_doubleinit, mem_error) {
	void* p1 = malloc(100);
	void* p2 = malloc(50);
	meminit(p1, 100);
	EXPECT_EQ(meminit(p2, 50), 1);
	memdone();
	free(p1);
	free(p2);
}


TEST(memalloc_wronginput, mem_error) {
	void*p = malloc(100);
	meminit(p, 100);
	ASSERT_EQ(NULL, memalloc(0));
	ASSERT_EQ(NULL, memalloc(-1));
	memdone();
	free(p);
}

TEST(memalloc_notenoughmem, mem_Null) {
	void* p1 = 0, * p2 = 0;
	void* ptr = malloc(memgetminimumsize() + 1);
	meminit(ptr, memgetminimumsize() + 1);
	p1 = memalloc(1);
	p2 = memalloc(1);
	ASSERT_TRUE(p2 == NULL);
	memfree(p1);
	memdone();
	free(ptr);
}

TEST(memfree_valinput, mem_right) {
	int size = memgetminimumsize() + sizeof(int);
	void* p;
	void* p2 = malloc(1000);
	meminit(p2, size);
	p = memalloc(sizeof(int));
	memfree(p);
	memdone();
	free(p2);
}


