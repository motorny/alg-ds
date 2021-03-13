#include <gtest/gtest.h>

#include "utils.h"
#include "../memallocator.h"

extern memBlock_t memBlock;


TEST(MemInit, NULLPtr) {
    void* ptr = nullptr;
    ASSERT_EQ(meminit(ptr, 0), NULL_PTR_ALLOC);
}

TEST(MemInit, NotEnoughSize) {
    int size = sizeof(Block_t);
    char dummy[size];
    ASSERT_EQ(meminit(dummy, size), SMALL_MEM_ALLOC);
}

TEST(MemInit, EnoughSize) {
    int size = sizeof(Block_t) * 2;
    char dummy[size];
    ASSERT_EQ(meminit(dummy, size), MEM_INIT_SUCCESS);

    ASSERT_EQ(memBlock.begin, (void*)dummy);
    ASSERT_EQ(memBlock.size, size);
    ASSERT_EQ(memBlock.block, nullptr);
}

TEST(MemInit, MemDoneSuccess) {
    int size = sizeof(Block_t) * 2;
    char dummy[size];
    ASSERT_EQ(meminit(dummy, size), MEM_INIT_SUCCESS);
    ASSERT_STREQ(captureMemDone().c_str(), NO_LEAK);
}
