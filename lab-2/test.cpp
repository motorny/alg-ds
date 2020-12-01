#include "pch.h"
extern"C" {
#include"../memallocator/memallocator.h"
}


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(memgetminimumsize, check_output) {
    ASSERT_EQ(memgetminimumsize(), sizeof(nodeEnder_t) + sizeof(nodeHeader_t));
}

TEST(meminit, null_pointer) {
    ASSERT_EQ(NULL_MEM, meminit(NULL, 1));
    memdone();
}

TEST(meminit, small_size_of_block) {
    char mem[10];
    ASSERT_EQ(TOO_SMALL_SIZE, meminit(mem, 10));
    memdone();
}

TEST(meminit, input_data_correct) {
    char mem[150];
    ASSERT_EQ(ALL_IS_OK, meminit(mem, 100));
    memdone();
}

TEST(meminit, comparison_output_data) {
    char mem[200];
    ASSERT_EQ(ALL_IS_OK, meminit(mem, 100));
    ASSERT_EQ((char*)theFirst, mem);
    memdone();
}

TEST(memalloc, input_size_0) {
    char mem[200];
    int size = 0;
    meminit(mem, 100);
    char* test = (char*)memalloc(size);
    ASSERT_EQ(NULL, test);
    memdone();
}

TEST(memalloc, mem_was_allocated) {
    char mem[200];
    int size = 20;

    meminit(mem, 100);
    char* test = (char*)memalloc(size);
    EXPECT_TRUE(test != NULL);
    memdone();
}

TEST(memalloc, not_enough_memory) {
    char mem[40];

    meminit(mem, 40);
    char* test = (char*)memalloc(30);
    ASSERT_EQ(NULL, test);
    memdone();
}

TEST(memfree, valid_values) {
    char ptr[100];
    meminit(ptr, 100);
    int size = 40 - memgetminimumsize();
    char* ptr1 = (char*)memalloc(size);
    char* ptr2 = (char*)memalloc(size);

    memfree(ptr2);
    memfree(ptr1);
    ASSERT_EQ((char*)theFirst, (char*)ptr);
}
