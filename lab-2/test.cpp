#include "pch.h"
#include "C:\Users\79523\source\repos\ALG2\ALG2\memallocator.c"

TEST(meminit, NULL_POINTER) {
    EXPECT_EQ(meminit(NULL, 1), FAIL);
}

TEST(meminit, SMALL_SIZE) {
	void* ptr = malloc(memgetminimumsize() - 1);
	EXPECT_EQ(meminit(ptr, memgetminimumsize() - 1), FAIL);
	free(ptr);
}

TEST(meminit, SUCCESSFUL_INIT) {
	void* ptr = malloc(memgetminimumsize() + 1);
	EXPECT_EQ(meminit(ptr, memgetminimumsize() + 1), SUCCESS);
	EXPECT_EQ(memory_system.total_size, memgetminimumsize() + 1);
	EXPECT_EQ((char*)memory_system.list, ptr);
	EXPECT_EQ(memory_system.list->size, 1);
	EXPECT_EQ(memory_system.list->key, MAGICKEY);
	free(ptr);
	memdone();
}

TEST(memalloc, NO_INIT) {
	EXPECT_EQ(memalloc(50), (void*)NULL);
}

TEST(memalloc, NEGATIVE_SIZE) {
	char memory[50];
	meminit(memory, 50);
	char* ptr = (char*)memalloc(-1);
	EXPECT_TRUE(ptr == NULL);
	memdone();
}

TEST(memalloc, NOT_ENOUGH_MEMORY) {
	char memory[50];
	meminit(memory, 50);
	char* ptr = (char*)memalloc(100);
	EXPECT_TRUE(ptr == NULL);
	memdone();
}

TEST(memalloc, SUCCESSFUL_ALLOC_WITHOUT_BLOCK_DIVISION) {
	char memory[50];
	meminit(memory, 50);
	char* ptr = (char*)memalloc(50 - memgetminimumsize());

	DESCR* test_descr = (DESCR*)((char*)ptr - sizeof(DESCR));
	END_DESCR* end_test = (END_DESCR*)((char*)test_descr + test_descr->size + sizeof(DESCR));

	EXPECT_EQ((char*)test_descr, memory_system.start);
	EXPECT_EQ(test_descr->key, MAGICKEY);
	EXPECT_TRUE(test_descr->next == NULL);
	EXPECT_EQ(end_test->size, BLOCK_USED);
	memdone();
}

TEST(memalloc, SUCCESSFUL_ALLOC_WITH_BLOCK_DIVISION) {
	char memory[100];
	meminit(memory, 100);
	char* ptr = (char*)memalloc(20);

	DESCR* new_descr = (DESCR*)((char*)ptr - sizeof(DESCR));
	END_DESCR* end_new = (END_DESCR*)((char*)new_descr + new_descr->size + sizeof(DESCR));

	EXPECT_EQ(new_descr->key, MAGICKEY);
	EXPECT_EQ(new_descr->size, 20);
	EXPECT_TRUE(new_descr->next == NULL);
	EXPECT_EQ(end_new->size, BLOCK_USED);

	DESCR* after_new = (DESCR*)((char*)end_new + sizeof(END_DESCR));

	EXPECT_EQ(after_new->key, MAGICKEY);
	EXPECT_EQ(after_new->size, 100 - 2 * memgetminimumsize() - 20);
	memdone();
}

TEST(memfree, FREE_CORRECTLY) {
	char memory[100];
	meminit(memory, 100);

	char* ptr1 = (char*)memalloc(20 - memgetminimumsize());
	char* ptr2 = (char*)memalloc(20 - memgetminimumsize());
	char* ptr3 = (char*)memalloc(20 - memgetminimumsize());

	memfree(ptr2);
	memfree(ptr1);
	memfree(ptr3);

	EXPECT_EQ((char*)memory_system.list, (char*)memory);
}