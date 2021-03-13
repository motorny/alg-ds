#include <gtest/gtest.h>

#include "utils.h"
#include "../memallocator.h"

extern memBlock_t memBlock;

#define SMALL memgetblocksize() * 2

class MemAlloc : public ::testing::Test {
private:
    int _size{};
protected:
    char* c = nullptr;

    MemAlloc() = default;

    ~MemAlloc() override { delete[] this->c; }

    void init(int size) {
        this->_size = size;
        this->c = new char[this->_size];
        meminit(c, this->_size);
    }

    void TearDown() override {
        memBlock.block = nullptr;
        memBlock.begin = nullptr;
        memBlock.size = 0;
        memBlock.curr = nullptr;
    }

};

TEST_F(MemAlloc, 1Block0Bytes) {
    init(memgetminimumsize());
    int size = 0;
    char* dummy = (char*) memalloc(size);

    ASSERT_EQ(memBlock.begin, this->c);

    ASSERT_EQ((char*) memBlock.block, this->c);
    ASSERT_EQ(memBlock.block->size, 1 + memgetblocksize());
    ASSERT_EQ(memBlock.block->next, nullptr);

    ASSERT_EQ(dummy, (char*) memBlock.begin + memgetblocksize());

    ASSERT_STREQ(captureMemDone().c_str(), LEAK);
}

TEST_F(MemAlloc, 1BlockNegMemory) {
    init(memgetminimumsize());
    int size = -1;
    char* dummy = (char*) memalloc(size);

    ASSERT_EQ(dummy, nullptr);
}

TEST_F(MemAlloc, 1Block1Byte) {
    init(memgetminimumsize());
    int size = 1;
    char* dummy = (char*) memalloc(size);

    ASSERT_EQ(memBlock.begin, this->c);

    ASSERT_EQ((char*) memBlock.block, this->c);
    ASSERT_EQ(memBlock.block->size, size + memgetblocksize());
    ASSERT_EQ(memBlock.block->next, nullptr);

    ASSERT_EQ(dummy, (char*) memBlock.begin + memgetblocksize());
    ASSERT_EQ(memBlock.curr, memBlock.block);

    ASSERT_STREQ(captureMemDone().c_str(), LEAK);
}

TEST_F(MemAlloc, 1BlockSMALLBytes) {
    init(memgetminimumsize());
    int size = SMALL;
    char* dummy = (char*) memalloc(size);

    ASSERT_EQ(memBlock.begin, this->c);

    ASSERT_EQ(memBlock.block, nullptr);
    ASSERT_EQ(dummy, nullptr);
}

TEST_F(MemAlloc, 1BlockNotEnoughInitMem) {
    init(1);
    int size = 1;
    char* dummy = (char*) memalloc(size);

    ASSERT_EQ(dummy, nullptr);
}

TEST_F(MemAlloc, 2Block1Bytes) {
    init(memgetminimumsize() * 2);
    int size = 1;
    char* dummy = (char*) memalloc(size);
    *dummy = 'a';
    char* ddummy = (char*) memalloc(size);

    ASSERT_EQ(*dummy, 'a');

    ASSERT_EQ((char*) memBlock.block, this->c);
    ASSERT_EQ(memBlock.block->size, size + memgetblocksize());
    ASSERT_EQ(memBlock.block, memBlock.begin);
    ASSERT_NE(memBlock.block->next, nullptr);

    ASSERT_EQ(memBlock.block->next->size, size + memgetblocksize());
    ASSERT_EQ((char*) memBlock.block->next,
              (char*) memBlock.block + memBlock.block->size);
    ASSERT_EQ(memBlock.block->next->next, nullptr);

    ASSERT_EQ(memBlock.curr, memBlock.block->next);
}

// 1B = 1Byte, NE = Not Enough memory in the init for allocation
TEST_F(MemAlloc, 3Block1B1BNE) {
    init(memgetminimumsize() * 2 + memgetminimumsize() / 2);
    int size = 1;
    char* dummy = (char*) memalloc(size), * dummy_1 = (char*) memalloc(size),
            * dummy_2 = (char*) memalloc(size);

    ASSERT_EQ((char*) memBlock.block, this->c);
    ASSERT_EQ(memBlock.block->size, size + memgetblocksize());
    ASSERT_EQ(memBlock.block, memBlock.begin);
    ASSERT_NE(memBlock.block->next, nullptr);

    ASSERT_EQ(memBlock.block->next->size, size + memgetblocksize());
    ASSERT_EQ((char*) memBlock.block->next,
              (char*) memBlock.block + memBlock.block->size);
    ASSERT_EQ(memBlock.block->next->next, nullptr);

    ASSERT_EQ(memBlock.curr, memBlock.block->next);
}

// init for 3 blocks, delete in the middle (by hand),
// place the 4th block in between
TEST_F(MemAlloc, 4Block1BE1B) {
    init(memgetminimumsize() * 3);
    int size = 1;
    char* dummy = (char*) memalloc(size), * dummy_1 = (char*) memalloc(size),
            * dummy_2 = (char*) memalloc(size);

    // checking everything lies as planned
    ASSERT_NE(memBlock.block->next->next, nullptr);
    ASSERT_EQ((char*) memBlock.block->next->next + memgetminimumsize(),
              (char*) memBlock.begin + memBlock.size);

    // delete the middle block
    Block_t* first = memBlock.block, * middle = first->next, * last = middle->next;
    first->next = last;
    middle->next = nullptr;
    middle->size = 0;
    middle = nullptr;

    // get new partition
    char* dummy_3 = (char*) memalloc(size);

    // check whether the new block is in the middle
    ASSERT_EQ(memBlock.block, first);
    ASSERT_NE(first->next, nullptr);
    ASSERT_EQ((char*) first->next, dummy_3 - memgetblocksize());
    ASSERT_EQ((char*) last, dummy_3 + size);
    ASSERT_EQ(memBlock.curr, first->next);
}

// init for 3 blocks, delete the left one (by hand),
// place the 4th block instead
TEST_F(MemAlloc, 4BlockE1B1B) {
    init(memgetminimumsize() * 3);
    int size = 1;
    char* dummy = (char*) memalloc(size), * dummy_1 = (char*) memalloc(size),
            * dummy_2 = (char*) memalloc(size);

    // checking everything lies as planned
    ASSERT_NE(memBlock.block->next->next, nullptr);
    ASSERT_EQ((char*) memBlock.block->next->next + memgetminimumsize(),
              (char*) memBlock.begin + memBlock.size);

    // delete the first block
    Block_t* first = memBlock.block, * middle = first->next, * last = middle->next;
    memBlock.block = middle;
    first->next = nullptr;
    first->size = 0;
    first = nullptr;

    // get new partition
    char* dummy_3 = (char*) memalloc(size);

    // check whether the new block is first
    ASSERT_EQ((char*) memBlock.block, dummy_3 - memgetblocksize());
    first = (Block_t*) (dummy_3 - memgetblocksize());
    ASSERT_NE(first->next, nullptr);
    ASSERT_EQ(first->next, middle);
    ASSERT_EQ((char*) middle, dummy_3 + size);
    ASSERT_EQ(memBlock.curr, first);
}

// 0, 1, 4, 6, 7, 8, 9 are freed, 2, 3, 5, 10 remains
// first insertion - 3 bytes (6, 7, 8)
// second insertion - 2 bytes (0, 1)
// third insertion - 2 bytes (NULL)
// forth insertion - 1 byte (4)
TEST_F(MemAlloc, 11BlockEE1B1BE1BEEEE1B) {
    init(memgetminimumsize() * 11);
    int size = 1;
    char* d0 = (char*) memalloc(size), * d1 = (char*) memalloc(size),
            * d2 = (char*) memalloc(size), * d3 = (char*) memalloc(size),
            * d4 = (char*) memalloc(size), * d5 = (char*) memalloc(size),
            * d6 = (char*) memalloc(size), * d7 = (char*) memalloc(size),
            * d8 = (char*) memalloc(size), * d9 = (char*) memalloc(size),
            * d10 = (char*) memalloc(size);

    ASSERT_EQ((char*) memBlock.block, d0 - memgetblocksize());
    ASSERT_EQ((char*) memBlock.begin + memBlock.size, d10 + size);

    Block_t* b0 = memBlock.block, * b1 = b0->next, * b2 = b1->next, * b3 = b2->next, * b4 = b3->next,
            * b5 = b4->next, * b6 = b5->next, * b7 = b6->next, * b8 = b7->next, * b9 = b8->next, * b10 = b9->next;

    memBlock.block = b2;
    b0 = nullptr;
    b1 = nullptr;
    b3->next = b5;
    b4 = nullptr;
    b5->next = b10;
    b6 = nullptr;
    b7 = nullptr;
    b8 = nullptr;
    b9 = nullptr;

    char* b_3 = (char*) memalloc(memgetminimumsize() * 2);
    ASSERT_NE(b5->next, b10);
    Block_t* blockB_3 = b5->next;
    // -2 is since the memory was occupied by 17*4, now 16+17*2, the diff 17+1
    // 17 - memgetminimumsize(), 16 - memgetblocksize()
    ASSERT_EQ((char*) blockB_3 + blockB_3->size, (char*) b10 - memgetblocksize() - 2);
    ASSERT_EQ(memBlock.curr, (void*) blockB_3);

    char* b_2 = (char*) memalloc(memgetminimumsize());
    ASSERT_EQ((void*) memBlock.block, memBlock.begin);
    Block_t* blockB_2 = memBlock.block;
    ASSERT_EQ(blockB_2->next, b2);
    ASSERT_EQ(memBlock.curr, (void*) blockB_2);
    ASSERT_EQ((char*) blockB_2 + blockB_2->size, (char*) b2 - 1);

    char* b_2_1 = (char*) memalloc(memgetminimumsize());
    ASSERT_EQ(b_2_1, nullptr);
    ASSERT_EQ(memBlock.curr, (void*)blockB_2);

    char* b_1 = (char*) memalloc(size);
    ASSERT_EQ((char*)b3->next, b_1 - memgetblocksize());
    Block_t* blockB_1 = b3->next;
    ASSERT_EQ(memBlock.curr, (void*)blockB_1);
    ASSERT_EQ(blockB_1->next, b5);
}