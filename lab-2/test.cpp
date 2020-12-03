#include "pch.h"

extern "C" {
#include "../Best Fit/memallocator.h"
#include "../Best Fit/memallocator.cpp"
}

TEST(meminit,Null_ptr_to_the_block) {
    char* pMemory = NULL;
    EXPECT_EQ(meminit(pMemory, memgetminimumsize()), 1);
}

TEST(meminit, Small_size) {
    char* pMemory = (char*)malloc(memgetminimumsize() - 1);
    EXPECT_EQ(meminit(pMemory, memgetminimumsize() - 1), 1);
    free(pMemory);
}

TEST(meminit, Usual_case) {
    char* pMemory = (char*)malloc(memgetminimumsize() + 1);
    EXPECT_EQ(meminit(pMemory, memgetminimumsize() + 1), 0);
    EXPECT_EQ((char*)list.head, pMemory);
    EXPECT_EQ(list.blockSize, memgetminimumsize() + 1);
    EXPECT_EQ(list.wholeBlockPtr, pMemory);
    free(pMemory);
}

TEST(memalloc, Allocate_negative_size) {
    char* pMemory = (char*)malloc(memgetminimumsize() + 1);
    meminit(pMemory, memgetminimumsize() + 1);
    char* ptr = (char*)memalloc(-10);
    EXPECT_EQ(ptr, (char*)NULL);
    free(pMemory);
}

//TEST(memalloc, Allocate_without_initialize) {
//    char* ptr = (char*)memalloc(10);
//    EXPECT_EQ(ptr, (char*)NULL);
//}

TEST(memalloc, Allocate_memory_without_creating_newdesc) {
    char* pMemory = (char*)malloc(memgetminimumsize() + 1);
    meminit(pMemory, memgetminimumsize() + 1);
    char* ptr = (char*)memalloc(1);
    EXPECT_NE(ptr, (char*)NULL);
    EXPECT_EQ(ptr, list.wholeBlockPtr + sizeof(descriptor_t));
    EXPECT_EQ(((end_of_block_t*)((char*)ptr + ((descriptor_t*)((char*)ptr - sizeof(descriptor_t)))->size))->fullness, 1);
    EXPECT_EQ((char*)(list.head), (char*)NULL);

    free(pMemory);
}

TEST(memalloc, Allocate_memory_creating_newdesc) {
    char* pMemory = (char*)malloc(memgetminimumsize() * 2 + 2);
    meminit(pMemory, memgetminimumsize() * 2 + 2);
    char* ptr = (char*)memalloc(1);

    EXPECT_EQ(ptr, list.wholeBlockPtr + sizeof(descriptor_t));
    EXPECT_EQ(((end_of_block_t*)((char*)ptr + ((descriptor_t*)((char*)ptr - sizeof(descriptor_t)))->size))->fullness, 1);
    EXPECT_EQ((char*)(list.head), (char*)ptr + 1 + sizeof(end_of_block_t));
    EXPECT_EQ(list.head->size, 1);
    EXPECT_EQ(((end_of_block_t*)((char*)list.head + sizeof(descriptor_t) + list.head->size))->fullness, -1);

    free(pMemory);
}

TEST(memalloc, Not_enough_memory) {
    char* pMemory = (char*)malloc(memgetminimumsize() + 1);
    meminit(pMemory, memgetminimumsize() + 1);
    char* ptr = (char*)memalloc(2);

    EXPECT_EQ(ptr, (char*)NULL);
    EXPECT_EQ((char*)list.head, list.wholeBlockPtr);
    EXPECT_EQ(list.head->size, 1);
    EXPECT_EQ(((end_of_block_t*)((char*)list.head + sizeof(descriptor_t) + list.head->size))->fullness, -1);

    free(pMemory);
}

TEST(memfree, Free_already_empty_ptr) {
    char* Memory = (char*)malloc(memgetminimumsize() + 1);
    meminit(Memory, memgetminimumsize() + 1);
    char* ptr = (char*)memalloc(1);
    memfree(ptr);

    memfree(ptr);
    EXPECT_EQ((char*)(list.head), ptr - sizeof(descriptor_t));
    EXPECT_EQ(((end_of_block_t*)((char*)ptr + ((descriptor_t*)((char*)ptr - sizeof(descriptor_t)))->size))->fullness, -1);
    EXPECT_EQ(list.head->size, 1);

    free(Memory);
}

TEST(memfree, Free_without_merge) {
    char* Memory = (char*)malloc(memgetminimumsize() * 2 + 2);
    char* ptr1, * ptr2;
    meminit(Memory, memgetminimumsize() * 2 + 2);
    ptr1 = (char*)memalloc(1);
    ptr2 = (char*)memalloc(1);

    memfree(ptr2);

    EXPECT_EQ((char*)(list.head), ptr2 - sizeof(descriptor_t));
    EXPECT_EQ(((end_of_block_t*)((char*)ptr2 + ((descriptor_t*)((char*)ptr2 - sizeof(descriptor_t)))->size))->fullness, -1);
    EXPECT_EQ(list.head->size, 1);

    free(Memory);
}

TEST(memfree, Merge_blocks) {
    char* pMemory = (char*)malloc(memgetminimumsize() + 2 * memgetblocksize() + 3);
    char* ptr1, * ptr2, * ptr3;
    meminit(pMemory, memgetminimumsize() + 2 * memgetblocksize() + 3);
    ptr1 = (char*)memalloc(1);
    ptr2 = (char*)memalloc(1);
    ptr3 = (char*)memalloc(1);

    memfree(ptr1);
    memfree(ptr3);
    memfree(ptr2);

    EXPECT_EQ((char*)list.head, list.wholeBlockPtr);
    EXPECT_EQ(((end_of_block_t*)((char*)list.head + sizeof(descriptor_t) + list.head->size))->fullness, -(memgetminimumsize() + memgetblocksize() + 3));
    EXPECT_EQ(list.head->next, (descriptor_t*)NULL);
    free(pMemory);
}

