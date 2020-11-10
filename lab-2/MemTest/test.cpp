#include "pch.h"
#include "../B14_Fisyuk/memallocator.cpp"

#define TRUE 1
#define FALSE 0
#define ERROR NULL
#define NOTAVAILABLE -1
#define KEY 14

TEST(Meminit, Check_Null) {
    EXPECT_EQ(NULL, meminit(NULL, 10));
}

TEST(Meminit, ValidPtr_returnTRUE) {
    char ptr[30];

    EXPECT_EQ(TRUE, meminit(ptr, 20));
    EXPECT_TRUE((char*)ptr == start);
}

TEST(Meminit, ValidKEY_ValidPTR_returnKEY_PTR) {
    char ptr[30];
    meminit(ptr, 30);

    EXPECT_EQ(KEY, freeList->key);
    EXPECT_EQ(ptr, (char*)freeList);
}

TEST(Meminit, SizeOfEndList_returnTRUE) {
    char ptr[30];
    meminit(ptr, 30);
    NodeEnd_t* end = (NodeEnd_t*)((char*)ptr + 30 - sizeof(NodeEnd_t));

    EXPECT_EQ(end->size, 30 - sizeof(NodeEnd_t) - sizeof(NodeHead_t));
}

TEST(Memalloc, NegativeSIZE_returnERROR) {
    char ptr[30];
    meminit(ptr, 30);

    EXPECT_EQ(ERROR, memalloc(-1));
}

TEST(Memalloc, NotEnoughMemory_returnERROR) {
    char ptr[30];
    meminit(ptr, 30);

    EXPECT_EQ(ERROR, memalloc(40));
}

TEST(Memalloc, NotEnoughMemory_2_returnERROR) {
    char ptr[30];
    int size = 30 - sizeof(NodeHead_t) - sizeof(NodeEnd_t);
    meminit(ptr, 30);
    void* buf = memalloc(size);

    EXPECT_EQ(ERROR, memalloc(1));
}

TEST(Memalloc, ValidInput_returnValues) {
    char ptr[30];
    int size = 30 - sizeof(NodeEnd_t) - sizeof(NodeHead_t);
    meminit(ptr, 30);
    char* buf = (char*)memalloc(size);

    EXPECT_EQ(((NodeHead_t*)(buf - sizeof(NodeHead_t)))->size, size);
    EXPECT_EQ(((NodeHead_t*)(buf - sizeof(NodeHead_t)))->key, KEY);
    EXPECT_EQ(((NodeEnd_t*)(buf + size))->size, NOTAVAILABLE);
}

TEST(Memfree, ValidValues_returnTRUE) {
    char ptr[30];
    int size = 20 - sizeof(NodeEnd_t) - sizeof(NodeHead_t);
    meminit(ptr, 30);
    char* testPtr = (char*)memalloc(size);
    memfree(testPtr);

    EXPECT_TRUE((char*)freeList == (char*)ptr);
}

TEST(Memfree, CheckDefragmentation_returnTRUE) {
    char ptr[100];
    int size = 20 - sizeof(NodeEnd_t) - sizeof(NodeHead_t);
    meminit(ptr, 100);
    char* ptr1 = (char*)memalloc(size);
    char* ptr2 = (char*)memalloc(size);
    char* ptr3 = (char*)memalloc(size);

    memfree(ptr2);
    memfree(ptr3);
    memfree(ptr1);

    EXPECT_TRUE((char*)freeList == (char*)ptr);
}



