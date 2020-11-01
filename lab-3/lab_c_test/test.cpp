#include "gtest/gtest.h"
#include "pch.h"

#include "..//lab_c3/func_for_test.c"

TEST(InitQueue_CorrectSize_returnSUCCESS) {
  queue_t q;

  EXPECT_EQ(InitQueue(&q, 1), M_SUCCESS);
  DelQueue(&q);
}

TEST(InitQueue_IncorrectSize_returnFAIL) {
  queue_t q;

  EXPECT_EQ(InitQueue(&q, 0), M_FAIL);
}

TEST(Get_CorrectState_returnSUCCESS) {
  int oldEl;
  int arr[1] = { 0 };
  queue_t q;

  q.arr = arr;
  q.size = 1;
  q.head = 0;
  q.tail = 1;

  EXPECT_EQ(Get(&q, &oldEl), M_SUCCESS);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
  EXPECT_EQ(oldEl, 0);
}

TEST(Get_EmptyQueue_returnFAIL) {
  int oldEl;
  int arr[1] = { 0 };
  queue_t q;

  q.arr = arr;
  q.size = 1;
  q.head = 1;
  q.tail = 1;

  EXPECT_EQ(Get(&q, &oldEl), M_FAIL);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
}

TEST(Get_UninitializedQueue_returnFAIL) {
  int oldEl;
  queue_t q;

  q.arr = NULL;
  q.size = 0;
  q.head = 0;
  q.tail = 0;

  EXPECT_EQ(Get(&q, &oldEl), M_FAIL);
}

TEST(Put_CorrectState_returnSUCCESS) {
  int arr[1];
  queue_t q;

  q.arr = arr;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  EXPECT_EQ(Put(&q, 0), M_SUCCESS);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(q.head, 0);
  EXPECT_EQ(q.tail, 1);
}

TEST(Put_FullQueue_returnFAIL) {
  int arr[1] = { 0 };
  queue_t q;

  q.arr = arr;
  q.size = 1;
  q.head = 0;
  q.tail = 1;

  EXPECT_EQ(Put(&q, 1), M_FAIL);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(q.head, 0);
  EXPECT_EQ(q.tail, 1);
}

TEST(Put_UninitializedQueue_returnFAIL) {
  queue_t q;

  q.arr = NULL;
  q.size = 0;
  q.head = 0;
  q.tail = 0;

  EXPECT_EQ(Put(&q, 0), M_FAIL);
}

TEST(BFS_CorrectState_returnSUCCESS) {
  int queue[1];
  int arrForNode[1];
  queue_t q;
  node_t nodes[1];
  adj_list_t list;

  q.arr = queue;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  nodes[0].numOfEdges = 0;
  nodes[0].edges = arrForNode;

  list.numOfVertex = 1;
  list.nodes = nodes;

  EXPECT_EQ(BFS(&list, &q), M_SUCCESS);
  EXPECT_EQ(queue[0], 0);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
}

TEST(BFS_IncorrectList_returnFAIL) {
  int queue[1];
  queue_t q;
  adj_list_t list;

  q.arr = queue;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  list.numOfVertex = 0;
  list.nodes = NULL;

  EXPECT_EQ(BFS(&list, &q), M_FAIL);
}

TEST(BFS_IncorrectQueue_returnFAIL) {
  int arrForNode[1];
  queue_t q;
  node_t nodes[1];
  adj_list_t list;

  q.arr = NULL;
  q.size = 0;
  q.head = 0;
  q.tail = 0;

  nodes[0].numOfEdges = 0;
  nodes[0].edges = arrForNode;

  list.numOfVertex = 1;
  list.nodes = nodes;

  EXPECT_EQ(BFS(&list, &q), M_FAIL);
}

TEST(BFS_SizeOfQueueLessThanNumOfVertex_returnFAIL) {
  int queue[1];
  queue_t q;
  node_t nodes[2];
  adj_list_t list;

  q.arr = queue;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  list.numOfVertex = 2;
  list.nodes = nodes;

  EXPECT_EQ(BFS(&list, &q), M_FAIL);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}