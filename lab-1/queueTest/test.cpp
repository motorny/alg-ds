#include "pch.h"
#include "queue.h"
TEST(EmptyQueueArr, NotEmptyQueue_ReturnsNotEmpty){
  elem_t arr[5];
  queueArr_t queue = {arr, 5, 4, 3};
  ASSERT_EQ(0, EmptyQueueArr(queue));
}

TEST(EmptyQueueArr, EmptyQueue_ReturnsEmpty) {
  elem_t arr[5];
  queueArr_t queue = {arr, 5, 0, 0};
  ASSERT_EQ(1, EmptyQueueArr(queue));
}
TEST(SizeQueueArr, NotEmptyQueue_ReturnsSize) {
  elem_t arr[5];
  queueArr_t queue = {arr, 5, 0, 4};
  ASSERT_EQ(4, SizeQueueArr(queue));
}

TEST(SizeQueueArr, EmptyOrOwerflowQueue_ReturnsZero) {
  elem_t arr[5];
  queueArr_t queue = {arr, 5, 2, 2};
  ASSERT_EQ(0, SizeQueueArr(queue));
}
TEST(PushQueueArr, PushOneElement_ElementInQueue) {
  elem_t arr[3];
  queueArr_t queue = {arr, 3, 0, 0};
  elem_t newElem = 5;
  int a, b;

  a = queue.tail;
  PushQueueArr(newElem, &queue);
  b = queue.tail;
  ASSERT_EQ(newElem, queue.data[queue.tail - 1]);
  ASSERT_NE(a, b);
}

TEST(PushQueueArr, OverflowAttempt_NotEmptyQueue){
  elem_t arr[3] = { 1, 2, 3 };
  queueArr_t queue = { arr, 3, 0, 2 };
  elem_t newElem = 5;
  int a, b;

  a = queue.tail;
  PushQueueArr(newElem, &queue);
  b = queue.tail;
  ASSERT_EQ(a, b);
}

TEST(PopQueueArr, PopTest_ReturnTailElement) {
  elem_t arr[5] = { 1, 2 , 3, 4 };
  queueArr_t queue = { arr, 5, 0, 4 };
  elem_t elem;
  elem = *PopQueueArr(&queue);
  ASSERT_EQ(arr[0], elem);
}
TEST(PopQueueArr, PopPushInteraction_ReturтOfPushedElement) {
  elem_t arr[5];
  queueArr_t queue1 = {arr, 5, 0, 0};
  elem_t newElem = 5, oldElem;
  PushQueueArr(newElem, &queue1);
  oldElem = *PopQueueArr(&queue1);
  ASSERT_EQ(newElem, oldElem);
}
TEST(EmptyQueueList, NotEmptyQueue_ReturnsNotEmpty) {
  node_t elem3 = {3, NULL};
  node_t elem2 = {2, &elem3};
  node_t elem1 = {1, &elem2};
  queueList_t queue = {&elem1, &elem3, 3};
  ASSERT_EQ(0, EmptyQueueList(queue));
}

TEST(EmptyQueueList, EmptyQueue_ReturnsEmpty) {
  queueList_t queue = {NULL, NULL, 0};
  ASSERT_EQ(1, EmptyQueueList(queue));
}

TEST(PushQueueList, PushOneElement_ElementInQueue) {
  node_t elem3 = { 3, NULL };
  node_t elem2 = { 2, &elem3 };
  node_t elem1 = { 1, &elem2 };
  queueList_t queue = { &elem1, &elem3, 3 };
  PushQueueList(4, &queue);
  ASSERT_EQ(elem3.next->data, queue.tail->data);
}

TEST(PopQueueList, PopPushInteraction_ReturтOfPushedElement) {
  queueList_t queue = {NULL, NULL, 0 };
  elem_t elem1 = 1;
  elem_t elem2 = 2;
  elem_t elem3 = 3;
  elem_t elem;
  PushQueueList(elem1, &queue); //Функция протестирована ранее иное тетстирование невозможно без нарушения иных условий
  PushQueueList(elem2, &queue);
  PushQueueList(elem3, &queue);
  elem = *PopQueueList(&queue);
  ASSERT_EQ(elem1, elem);
}