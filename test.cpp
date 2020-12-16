#include "pch.h"
#include"../GraphBFS/Graph.c"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(createGraph, NegSize_ReturnNULL) {
    ASSERT_EQ(createGraph(-1), (struct Graph*)NULL);
}


TEST(createQueue, normalWork_returnValidPointer) {
    struct queue* queue = createQueue();
    ASSERT_TRUE(queue != NULL);
    ASSERT_TRUE(queue->head == NULL);
    ASSERT_TRUE(queue->tail == NULL);
    destroyQueue(queue);
}


TEST(pushQueue, normalWorkTwoNode_returnSUCCESS) {
   struct queue* queue = createQueue();
    ASSERT_EQ(pushQueue(queue, 1), SUCCESS);
    ASSERT_EQ(pushQueue(queue, 2), SUCCESS);
    ASSERT_EQ(queue->head->vertex, 1);
    ASSERT_EQ(queue->tail->vertex, 2);
    destroyQueue(queue);
}
TEST(popQueue, nullPtr_returnFAIL) {
    struct queue* queue = NULL;
    ASSERT_EQ(popQueue(queue), FAIL);
}
TEST(popQueue, emptyQueue_returnFAIL) {
    struct queue* queue = createQueue();
    ASSERT_EQ(popQueue(queue), FAIL);
    destroyQueue(queue);
}
TEST(popQueue, normalWork_returnCorrectNumber) {
    struct queue* queue = createQueue();
    pushQueue(queue, 10);
    int result = popQueue(queue);
    ASSERT_EQ(result, 10);
    destroyQueue(queue);
}