#include "pch.h"
#include "../lab-C3/queue.c"

#define ERROR -1
#define TRUE 1
#define FALSE 0

TEST(TestQueue, Init_InvalidInput_returnFALSE) {
    queue_t q;
    EXPECT_TRUE(InitQ(&q, -1) == FALSE);
}

TEST(TestQueue, Init_ValidInput_returnTRUE) {
    queue_t q;
    EXPECT_TRUE(InitQ(&q, 1) == TRUE);
    EXPECT_TRUE(q.arr[0] != NULL);
}

TEST(TestQueue, Push_InvalidInput_returnFALSE) {
    queue_t q;
    q.last = 2;
    q.head = 0;
    q.size = 2;
    q.arr = (int*)malloc(2 * sizeof(int));
    EXPECT_TRUE(push(&q, 2) == FALSE);
}

TEST(TestQueue, Push_ValidInput_returnTRUE) {
    queue_t q;
    q.last = 0;
    q.head = 0;
    q.size = 2;
    q.arr = (int*)malloc(2 * sizeof(int));

    EXPECT_TRUE(push(&q, 12) == TRUE);
    EXPECT_TRUE(q.arr[0] == 12);
    EXPECT_TRUE(q.last == 1);
}

TEST(TestQueue, Pop_InvalidInput_returnFALSE) {
    int tmp;
    queue_t q;
    q.last = 0;
    q.head = 2;
    q.size = 2;
    q.arr = (int*)malloc(2 * sizeof(int));

    EXPECT_TRUE(pop(&q, &tmp) == FALSE);
}

TEST(TestQueue, Pop_ValidInput_returnTRUE) {
    int tmp;
    queue_t q;
    q.arr = (int*)malloc(2 * sizeof(int));
    q.head = 0;
    q.size = 2;
    q.arr[0] = 13; 
    q.last = 1;

    EXPECT_TRUE(pop(&q, &tmp) == TRUE);
    EXPECT_TRUE(tmp == 13);
    EXPECT_TRUE(q.head == 1);
}
