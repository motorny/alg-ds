#include "pch.h"
#include "../Pavlov Lab3 V4/queue.h"
#include "../Pavlov Lab3 V4/graph.h"

TEST(QueuePush, PushToNullQueue_ReturnsFail) {
  EXPECT_EQ(QueuePush(NULL, 1), FAIL);
}

TEST(QueuePush, PushToEmptyQueue_ReturnsSuccess) {
  queue_t* q = CreateQueue();
  EXPECT_EQ(QueuePush(q, 1), SUCCESS);
  free(q->start);
  free(q);
}

TEST(QueuePush, PushToQueueWithOneNode_ReturnsSuccess) {
  queue_t* q = CreateQueue();
  EXPECT_EQ(QueuePush(q, 1), SUCCESS);
  EXPECT_EQ(QueuePush(q, 2), SUCCESS);
  free(q->start->next);
  free(q->start);
  free(q);
}

TEST(QueuePop, PopFromNullQueue_Death) {
  EXPECT_DEATH(QueuePop(NULL), "");
}

TEST(QueuePop, PopFromEmptyQueue_Death) {
  queue_t* q = CreateQueue();
  EXPECT_DEATH(QueuePop(q), "");
  free(q);
}

TEST(QueuePop, AllRight_Returns1) {
  queue_t* q = CreateQueue();
  QueuePush(q, 1);
  EXPECT_EQ(QueuePop(q), 1);
  free(q->start);
  free(q);
}

TEST(RemoveQueue, NoMemoryLeaks) {
  queue_t* q = CreateQueue();
  QueuePush(q, 1);
  QueuePush(q, 2);
  RemoveQueue(q);
  EXPECT_EQ(_CrtDumpMemoryLeaks(), 0);
}



int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}