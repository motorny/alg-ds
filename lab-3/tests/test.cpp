#include "gtest/gtest.h"

#include "../queue.h"
#include "../bfs.h"

TEST(InitQueue_CorrectSize_return1) {
  queue_t q;

  EXPECT_EQ(InitQueue(&q, 1), 1);
  CloseQueue(&q);
}

TEST(InitQueue_IncorrectSize_return0) {
  queue_t q;

  EXPECT_EQ(InitQueue(&q, 0), 0);
}

TEST(Push_CorrectPush_return1) {
  int array[1];
  queue_t q;

  q.array = array;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  EXPECT_EQ(Push(&q, 1), 1);
  EXPECT_EQ(q.head, 0);
  EXPECT_EQ(q.tail, 1);
  EXPECT_EQ(array[0], 1);
}

TEST(Push_PushToOverflowingQueue_return0) {
  int array[1] = {1};
  queue_t q;

  q.array = array;
  q.size = 1;
  q.head = 0;
  q.tail = 1;

  EXPECT_EQ(Push(&q, 1 + 1), 0);
  EXPECT_EQ(q.head, 0);
  EXPECT_EQ(q.tail, 1);
  EXPECT_EQ(array[0], 1);
}

TEST(Push_UninitializedQueue_return0) {
  queue_t q;

  q.array = NULL;
  q.size = 0;
  q.head = 0;
  q.tail = 0;

  EXPECT_EQ(Push(&q, 1), 0);
}

TEST(Pop_CorrectPop_return1) {
  int oldEl;
  int array[1] = {1};
  queue_t q;

  q.array = array;
  q.size = 1;
  q.head = 0;
  q.tail = 1;

  EXPECT_EQ(Pop(&q, &oldEl), 1);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
  EXPECT_EQ(array[0], 1);
  EXPECT_EQ(oldEl, 1);
}

TEST(Pop_PopFromEmptyQueue_return0) {
  int oldEl;
  int array[1] = {1};
  queue_t q;

  q.array = array;
  q.size = 1;
  q.head = 1;
  q.tail = 1;

  EXPECT_EQ(Pop(&q, &oldEl), 0);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
  EXPECT_EQ(array[0], 1);
}

TEST(Pop_UninitializedQueue_return0) {
  int oldEl; 
  queue_t q;

  q.array = NULL;
  q.size = 0;
  q.head = 0;
  q.tail = 0;

  EXPECT_EQ(Pop(&q, &oldEl), 0);
}

TEST(BFS_CorrectAdj_return1) {
  int arrayForQueue[1], arrayForNode[1];
  queue_t q;
  node_t n[1];
  adj_list_t al;

  q.array = arrayForQueue;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  n[0].numOfList = 0;
  n[0].adjNodes = arrayForNode;
  n[0].wasVisit = 0;

  al.n = 1;
  al.nodes = n;

  EXPECT_EQ(BFS(&al, &q), 1);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
  EXPECT_EQ(arrayForQueue[0], 0);
}

TEST(BFS_IncorrectAdj_return0) {
  int arrayForQueue[1];
  queue_t q;
  adj_list_t al;

  q.array = arrayForQueue;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  al.n = 0;
  al.nodes = NULL;

  EXPECT_EQ(BFS(&al, &q), 0);
}

TEST(BFS_IncorrectQueue_return0) {
  int arrayForNode[1];
  queue_t q;
  node_t n[1];
  adj_list_t al;

  q.array = NULL;
  q.size = 0;
  q.head = 0;
  q.tail = 0;

  n[0].numOfList = 0;
  n[0].adjNodes = arrayForNode;
  n[0].wasVisit = 0;

  al.n = 1;
  al.nodes = n;

  EXPECT_EQ(BFS(&al, &q), 0);
}

TEST(BFS_DifferentSizesOfQueueAndList_return0) {
  int arrayForQueue[1], arrayForNode[1];
  queue_t q;
  node_t n[2];
  adj_list_t al;

  q.array = arrayForQueue;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  al.n = 2;
  al.nodes = n;

  EXPECT_EQ(BFS(&al, &q), 0);
}
