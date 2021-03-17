#include <gtest/gtest.h>

#include "utils.h"
#include "../memallocator.h"

extern memBlock_t memBlock;

class MemFree : public ::testing::Test {
private:
    int _size{};
protected:
    char* c = nullptr;
    bool _checkMemory = false;

    MemFree() = default;

    ~MemFree() override { delete[] this->c; }

    void init(int size) {
        this->_size = size;
        this->c = new char[this->_size];
        meminit(c, this->_size);
    }

    static void memoryLeakCheck() {
        ASSERT_STREQ(captureMemDone().c_str(), NO_LEAK);
    }

    void TearDown() override {
        if (_checkMemory)
            memoryLeakCheck();
        memBlock.block = nullptr;
        memBlock.begin = nullptr;
        memBlock.size = 0;
        memBlock.curr = nullptr;
    }
};

TEST_F(MemFree, EmptyInit) {
    init(0);
    char* c = (char*) memalloc(0);
    memfree(c);
    _checkMemory = true;
}

TEST_F(MemFree, 1Block) {
    init(BYTE);
    char* c = (char*) memalloc(0);
    memfree(c);

    ASSERT_EQ(memBlock.begin, nullptr);
    ASSERT_EQ(memBlock.block, nullptr);
    ASSERT_EQ(memBlock.size, 0);
    ASSERT_EQ(memBlock.curr, nullptr);
    _checkMemory = true;
}

TEST_F(MemFree, 2BlockRight) {
    init(BYTE * 2);
    int size = 1;
    char* d0 = (char*) memalloc(size), * d1 = (char*) memalloc(size);
    memfree(d1);

    ASSERT_EQ(memBlock.block->next, nullptr);
    ASSERT_EQ(((char*) memBlock.begin + memBlock.size) - ((char*) memBlock.block + memBlock.block->size),
              memBlock.block->size);
}

TEST_F(MemFree, 2BlockLeft) {
    init(BYTE * 2);
    int size = 1;
    char* d0 = (char*) memalloc(size), * d1 = (char*) memalloc(size);
    memfree(d0);

    ASSERT_EQ((char*) memBlock.block, d1 - memgetblocksize());
    Block_t* b1 = memBlock.block;
    ASSERT_NE((void*) memBlock.block, memBlock.begin);
    ASSERT_EQ(memBlock.curr, b1);
    ASSERT_EQ(b1->next, nullptr);
}

TEST_F(MemFree, 3BlockMiddle) {
    init(BYTE * 3);
    int size = 1;
    char* d0 = (char*) memalloc(size), * d1 = (char*) memalloc(size),
            * d2 = (char*) memalloc(size);
    memfree(d1);

    ASSERT_EQ((char*)memBlock.block, (char*)memBlock.begin);
    ASSERT_EQ((char*) memBlock.block, d0 - memgetblocksize());
    Block_t* b0 = memBlock.block;
    ASSERT_EQ((char*) b0->next, d2 - memgetblocksize());
    Block_t* b2 = b0->next;
    ASSERT_EQ(b2->next, nullptr);
}

TEST_F(MemFree, 3BlockLeft) {
    init(BYTE * 3);
    int size = 1;
    char* d0 = (char*) memalloc(size), * d1 = (char*) memalloc(size),
            * d2 = (char*) memalloc(size);
    memfree(d0);

    ASSERT_NE((char*)memBlock.block, (char*)memBlock.begin);
    ASSERT_EQ((char*) memBlock.block, d1 - memgetblocksize());
    Block_t* b1 = memBlock.block;
    ASSERT_EQ((char*) b1->next, d2 - memgetblocksize());
    Block_t* b2 = b1->next;
    ASSERT_EQ(b2->next, nullptr);
}

TEST_F(MemFree, 3BlockRight) {
    init(BYTE * 3);
    int size = 1;
    char* d0 = (char*) memalloc(size), * d1 = (char*) memalloc(size),
            * d2 = (char*) memalloc(size);
    memfree(d2);

    ASSERT_EQ((char*)memBlock.block, (char*)memBlock.begin);
    ASSERT_EQ((char*) memBlock.block, d0 - memgetblocksize());
    Block_t* b0 = memBlock.block;
    ASSERT_EQ((char*) b0->next, d1 - memgetblocksize());
    Block_t* b1 = b0->next;
    ASSERT_EQ(b1->next, nullptr);
}