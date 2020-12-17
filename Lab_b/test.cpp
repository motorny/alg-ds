#include "pch.h"
#include <gtest/gtest.h>
#include "../project4/Lab-b.cpp"


TEST(NO_LEAKS_TEST, CORRECT_INPUT_OUTPUT_EXPECT_GOOD)
{
    char memory[1200];

    meminit(memory, 1200);
    int* arr[5];
    arr[0] = (int*)memalloc(100); //1000 in sum
    arr[1] = (int*)memalloc(150);
    arr[2] = (int*)memalloc(200);
    arr[3] = (int*)memalloc(250);
    arr[4] = (int*)memalloc(300);
    memfree(arr[4]);
    memfree(arr[1]);
    memfree(arr[2]);
    memfree(arr[0]);
    memfree(arr[3]);

    EXPECT_TRUE(CheckMemoryLeaks());
}

TEST(NO_LEAKS_TEST, CORRECT_INPUT_OUTPUT)
{
    char memory[1200];

    meminit(memory, 1200);
    int* arr[5];
    arr[0] = (int*)memalloc(100); //1200 in sum
    arr[1] = (int*)memalloc(150);
    arr[2] = (int*)memalloc(200);
    arr[3] = (int*)memalloc(250);
    arr[4] = (int*)memalloc(500);

    EXPECT_TRUE(arr[0] != NULL);
    EXPECT_TRUE(arr[1] != NULL);
    EXPECT_TRUE(arr[2] != NULL);
    EXPECT_TRUE(arr[3] != NULL);
    EXPECT_TRUE(arr[4] == NULL);

    memfree(arr[0]);
    memfree(arr[1]);
    memfree(arr[2]);
    memfree(arr[3]);
    memfree(NULL);

    EXPECT_TRUE(CheckMemoryLeaks());
}

TEST(NO_LEAKS_TEST, CORRECT_INPUT_OUTPUT2)
{
    char memory[1000 + 100 * 28];
    meminit(memory, 1000 + 100 * 28);
    int* mem[100];

    for (int i = 0; i < 100; i++)
        mem[i] = (int*)memalloc(1);

    for (int i = 0; i < 100; i++)
        if (i % 3)
            memfree(mem[i]);

    for (int i = 0; i < 100; i++)
        if (i % 2)
            memfree(mem[i]);

    for (int i = 0; i < 100; i++)
        if (!(i % 3))
            memfree(mem[i]);

    EXPECT_TRUE(CheckMemoryLeaks());
}

TEST(TOO_BIG_SIZE_REQUEST, RECUEST_MORE_THAN_INIT)
{
   char memory[36];

   meminit(memory, 36);   
   int* a = (int*)memalloc(400);
   ASSERT_EQ(a, nullptr);
}

TEST(TOO_BIG_SIZE_REQUEST, REQUEST_MORE_THAN_EXIST)
{
    char memory[60];

    meminit(memory, 60);
    void* a = memalloc(20);
    void* b = memalloc(60);
    EXPECT_EQ(b, nullptr);
    EXPECT_TRUE(a != nullptr);
}

TEST(NULL_PTR_FREE, NOTHING_AND_NO_LEAKS_EXPECTION)
{
    char memory[60];

    meminit(memory, 60);
    void* a = memalloc(60 - memgetblocksize());
    void* b = memalloc(40);
    memfree(a);
    memfree(b);
    EXPECT_TRUE(b == NULL);
    EXPECT_TRUE(CheckMemoryLeaks());
}
