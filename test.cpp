#include "pch.h"

extern "C" {
#include "queue.h"
#include "BFS.h"
}


TEST(InitialisationOfQueue, CorrectSize_returnSUCCESS) {
  queue_t q;

  EXPECT_EQ(InitialisationOfQueue(&q, 1), SUCCESS);
  DeletQueue(&q);
}

TEST(InitialisationOfQueue, IncorrectSize_returnFAIL) {
  queue_t q;

  EXPECT_EQ(InitialisationOfQueue(&q, 0), FAIL);
}


TEST(Pop, CorrectRequest_returnSUCCESS) {
  int oldElem;
  int arr[1] = { 0 };
  queue_t q;

  q.array = arr;
  q.size = 1;
  q.head = 0;
  q.tail = 1;

  EXPECT_EQ(Pop(&q, &oldElem), SUCCESS);

  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
  EXPECT_EQ(oldElem, 0);
}

TEST(Pop, EmptyQueue_returnFAIL) {
  int oldElem;
  int arr[1] = { 0 };
  queue_t q;

  q.array = arr;
  q.size = 1;
  q.head = 1;
  q.tail = 1;

  EXPECT_EQ(Pop(&q, &oldElem), FAIL);

  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
}


TEST(Push, CorrectRequest_returnSUCCESS) {
  int arr[1];
  queue_t q;

  q.array = arr;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  EXPECT_EQ(Push(&q, 0), SUCCESS);

  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(q.head, 0);
  EXPECT_EQ(q.tail, 1);
}

TEST(Push, FullQueue_returnFAIL) {
  int array[1] = { 0 };
  queue_t q;

  q.array = array;
  q.size = 1;
  q.head = 0;
  q.tail = 1;

  EXPECT_EQ(Push(&q, 1), FAIL);

  EXPECT_EQ(array[0], 0);
  EXPECT_EQ(q.head, 0);
  EXPECT_EQ(q.tail, 1);
}


TEST(BFS, CorrectRequest_returnSUCCESS) {
  int queue[1];
  int arr[1];
  queue_t q;
  node_t nodes[1];
  adjlist_t list;

  q.array = queue;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  nodes[0].numOfAdj = 0;
  nodes[0].adjacency = arr;

  list.numOfVert = 1;
  list.nodes = nodes;

  EXPECT_EQ(BFS(&list, &q), SUCCESS);

  EXPECT_EQ(queue[0], 0);
  EXPECT_EQ(q.head, 1);
  EXPECT_EQ(q.tail, 1);
}

TEST(BFS, IncorrectQueue_returnFAIL) {
  int arr[1];
  queue_t q;
  node_t nodes[1];
  adjlist_t list;

  q.array = NULL;
  q.size = 0;
  q.head = 0;
  q.tail = 0;

  nodes[0].numOfAdj = 0;
  nodes[0].adjacency = arr;

  list.numOfVert = 1;
  list.nodes = nodes;

  EXPECT_EQ(BFS(&list, &q), FAIL);
}

TEST(BFS, IncorrectList_returnFAIL) {
  int queue[1];
  queue_t q;
  adjlist_t list;

  q.array = queue;
  q.size = 1;
  q.head = 0;
  q.tail = 0;

  list.numOfVert = 0;
  list.nodes = NULL;

  EXPECT_EQ(BFS(&list, &q), FAIL);
}