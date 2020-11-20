#include"memallocator.h"

#include "gtest/gtest.h"

#define FALSE 0
#define TRUE 1

//meminit
TEST(meminit, nullptr_return) {

    EXPECT_EQ(0, meminit(nullptr, 1));

}

TEST(meminit, NegativeSize_return1) {
    void *ptr = malloc(memgetminimumsize() + 1);

    EXPECT_EQ(0, meminit(ptr, -1));

    free(ptr);
}

TEST(meminit, CorrectData_return0) {
    void *ptr = malloc(memgetminimumsize() + 1);

    EXPECT_EQ(1, meminit(ptr, memgetminimumsize() + 1));

    free(ptr);
}

TEST(memalloc, NegativeSize_return0) {
    void *ptr = malloc(memgetminimumsize() + 1);
    meminit(ptr, memgetminimumsize() + 1);

    EXPECT_EQ(0, memalloc(-1));

    free(ptr);
}

TEST(memalloc, CorrectData_returnValidPointer) {
    void *ptr = malloc(memgetminimumsize() + 1);
    meminit(ptr, memgetminimumsize() + 1);

    void *p1 = memalloc(1);
    EXPECT_TRUE(p1 != NULL);

    memfree(p1);
    free(ptr);
}

TEST(memalloc, NotEnoughMem_returnNULL) {
    void *ptr = malloc(memgetminimumsize() + 1);
    meminit(ptr, memgetminimumsize() + 1);
    void *p1 = memalloc(2);
    EXPECT_TRUE(p1 == NULL);
    memfree(p1);
    free(ptr);
}