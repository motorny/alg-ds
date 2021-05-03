#include "pch.h"
extern"C" {
#include "memallocator.h"
}

int minimumSize = memgetminimumsize() + 1;

TEST(meminit, NullData) {
    char* arr = NULL;
    int num = meminit(arr, 1);
    ASSERT_EQ(num, 0);
    memdone();
}

TEST(meminit, NegativeSize) {
    char* arr = (char*)malloc(minimumSize);
    int num = meminit(arr, -1);
    ASSERT_EQ(num, 0);
    memdone();
    free(arr);
}

TEST(meminit, CorrectData) {
    char* arr = (char*)malloc(minimumSize);
    int num = meminit(arr, minimumSize);
    ASSERT_EQ(num, 1);
    free(arr);
    memdone();
}

TEST(memalloc, NegativeSize) {
    char* arr1 = (char*)malloc(minimumSize);
    meminit(arr1, minimumSize);
    char* arr2 = (char*)memalloc(-1);
    ASSERT_EQ(arr2, (char*)NULL);
    free(arr1);
    memdone();
}

TEST(memalloc, NotEnoughMemory) {
    char* arr1 = (char*)malloc(minimumSize);
    meminit(arr1, minimumSize);
    char* arr2 = (char*)memalloc(2);
    ASSERT_EQ(arr2, (char*)NULL);
    memfree(arr2);
    free(arr1);
    memdone();
}

TEST(memalloc, CorrectData) {
    char* arr1 = (char*)malloc(minimumSize);
    meminit(arr1, minimumSize);
    char* arr2 = (char*)memalloc(1);
    ASSERT_NE(arr2, (char*)NULL);
    memfree(arr2);
    free(arr1);
    memdone();
}

TEST(memfree, NullData) {
    char* arr = (char*)memalloc(minimumSize);
    memfree(arr);
    memdone();
}

TEST(memfree, NotOurMemory) {
    char* arr = (char*)malloc(minimumSize);
    meminit(arr, minimumSize);
    memfree(arr + 100);
    free(arr);
    memdone();
}

TEST(memfree, CorrectData) {
    char* arr1 = (char*)malloc(10 * minimumSize);
    meminit(arr1, 10 * minimumSize);
    char* arr2 = (char*)memalloc(1);
    memfree(arr2);
    free(arr1);
    memdone();
}
