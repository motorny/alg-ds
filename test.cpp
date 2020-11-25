#include "pch.h"

extern "C" {
#include"graph.h"
#include"queue.h"
}
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
TEST(createQueue, normalWork_returnValidPointer) {
  queue_t* queue = createQueue();
  ASSERT_TRUE(queue != NULL);
  ASSERT_TRUE(queue->head == NULL);
  ASSERT_TRUE(queue->tail == NULL);
  destroyQueue(queue);
}
TEST(pushQueue, nullPtr_returnFAIl) {
  queue_t* queue = NULL;
  ASSERT_EQ(pushQueue(queue, 1), FAIL);
}
TEST(pushQueue, normalWorkOneNode_returnSUCCESS) {
  queue_t* queue = createQueue();
  ASSERT_EQ(pushQueue(queue, 1), SUCCESS);
  ASSERT_EQ(queue->head->data, 1);
  ASSERT_EQ(queue->tail->data, 1);
  destroyQueue(queue);
}
TEST(pushQueue, normalWorkTwoNode_returnSUCCESS) {
  queue_t* queue = createQueue();
  ASSERT_EQ(pushQueue(queue, 1), SUCCESS);
  ASSERT_EQ(pushQueue(queue, 2), SUCCESS);
  ASSERT_EQ(queue->head->data, 1);
  ASSERT_EQ(queue->tail->data, 2);
  destroyQueue(queue);
}
TEST(popQueue, nullPtr_returnFAIL) {
  queue_t* queue = NULL;
  ASSERT_EQ(popQueue(queue), FAIL);
}
TEST(popQueue, emptyQueue_returnFAIL) {
  queue_t* queue = createQueue();
  ASSERT_EQ(popQueue(queue), FAIL);
  destroyQueue(queue);
}
TEST(popQueue, normalWork_returnCorrectNumber) {
  queue_t* queue = createQueue();
  pushQueue(queue, 10);
  int result = popQueue(queue);
  ASSERT_EQ(result, 10);
  destroyQueue(queue);
}