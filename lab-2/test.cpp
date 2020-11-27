#include "pch.h"

extern "C" {
#include "../LAB_B/memallocator.h"
#include "../LAB_B/lab_b_11.cpp"
}

TEST(MeminitFunction, Not_Enough_Space) {
    char a[10];
    int i = meminit(a, 10);
    EXPECT_EQ(i, -1);
}

TEST(MeminitFunction, Enough_Space) {
    char a[30];
    int i = meminit(a, 30);
    EXPECT_EQ(i, 0);
}

TEST(AllocFunction, WithoutFun_meminit) {
    void* p = memalloc(1);
    EXPECT_EQ(p, (void*)0);
}

TEST(AllocFunction, Not_Enough_Space) {
    char a[30];
    meminit(a, 30);
    void* p = memalloc(30);
    EXPECT_EQ(p, (void*)0);
}

TEST(AllocFunction, Enough_Space) {
    char a[200];
    meminit(a, 30);
    void* p = memalloc(30);
    EXPECT_TRUE(p != (void*)0);
}

TEST(AllocFunction, Main_Test) {
    char a[200];
    meminit(a, 30);
    void* p = memalloc(30);
    void* q = memalloc(5);
    EXPECT_TRUE(a + SIZE_PART_BLOCK == p);
    EXPECT_TRUE(*(int*)(a + SIZE_PART_BLOCK + 30 - sizeof(int)) == -30);
    EXPECT_TRUE(a + SIZE_PART_BLOCK + 30 + SIZE_PART_BLOCK == q);
}

TEST(FreeFunction, Main_Test) {
    char a[200];
    meminit(a, 30);
    void* p = memalloc(30);
    memfree(p);
    void* q = memalloc(5);
    memfree(q);
    EXPECT_TRUE(q == p);
}
