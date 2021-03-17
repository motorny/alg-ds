#include <gtest/gtest.h>

#include "utils.h"
#include "../memallocator.h"

extern memBlock_t memBlock;


class MemAllocFree : public ::testing::Test {
private:
    int _size{};
protected:
    char* c = nullptr;

    MemAllocFree() = default;

    ~MemAllocFree() override { delete[] this->c; }

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

// init for 3 blocks, delete in the middle (by memfree),
// place the 4th block in between
TEST_F(MemAllocFree, 4Block1BE1BFree) {
    init(BYTE * 3);
    int size = 1;
    char* dummy = (char*) memalloc(size), * dummy_1 = (char*) memalloc(size),
            * dummy_2 = (char*) memalloc(size);

    // checking everything lies as planned
    ASSERT_NE(memBlock.block->next->next, nullptr);
    ASSERT_EQ((char*) memBlock.block->next->next + BYTE,
    (char*) memBlock.begin + memBlock.size);


    // delete the middle block
    Block_t* first = memBlock.block, * middle = first->next, * last = middle->next;
    memfree(dummy_1);

    // get new partition
    char* dummy_3 = (char*) memalloc(size);

    // check whether the new block is in the middle
    ASSERT_EQ(memBlock.block, first);
    ASSERT_NE(first->next, nullptr);
    ASSERT_EQ((char*) first->next, dummy_3 - memgetblocksize());
    ASSERT_EQ((char*) last, dummy_3 + size);
    ASSERT_EQ(memBlock.curr, first->next);
}

// init for 3 blocks, delete the left one (by memFree),
// place the 4th block instead
TEST_F(MemAllocFree, 4BlockE1B1BFree) {
    init(BYTE * 3);
    int size = 1;
    char* dummy = (char*) memalloc(size), * dummy_1 = (char*) memalloc(size),
            * dummy_2 = (char*) memalloc(size);

    // checking everything lies as planned
    ASSERT_NE(memBlock.block->next->next, nullptr);
    ASSERT_EQ((char*) memBlock.block->next->next + BYTE,
    (char*) memBlock.begin + memBlock.size);

    // delete the first block
    Block_t* first = memBlock.block, * middle = first->next, * last = middle->next;
    memfree(dummy);

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

// init for 3 blocks, delete the right one (by memFree),
// place the 4th block instead
TEST_F(MemAllocFree, 4Block1B1BEFree) {
    init(BYTE * 3);
    int size = 1;
    char* dummy = (char*) memalloc(size), * dummy_1 = (char*) memalloc(size),
            * dummy_2 = (char*) memalloc(size);

    // checking everything lies as planned
    ASSERT_NE(memBlock.block->next->next, nullptr);
    ASSERT_EQ((char*) memBlock.block->next->next + BYTE,
    (char*) memBlock.begin + memBlock.size);

    // delete the last block
    Block_t* first = memBlock.block, * middle = first->next, * last = middle->next;
    memfree(dummy_2);

    // get new partition
    char* dummy_3 = (char*) memalloc(size);

    // check whether the new block is first
    ASSERT_EQ((char*) memBlock.block + memBlock.size - size, dummy_3);
    last = (Block_t*) (dummy_3 - memgetblocksize());
    ASSERT_EQ(middle->next, last);
    ASSERT_EQ(last->next, nullptr);
    ASSERT_EQ(memBlock.curr, last);
}
