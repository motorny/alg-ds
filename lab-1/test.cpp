#include "pch.h"
#include "../FIRST/firstlab.c"

elem_t* CreateHeadforTests() {
  elem_t* head;
  head = (elem_t*)malloc(sizeof(elem_t));
  if (head) {
    head->numElements = 0;
    head->next = NULL;
    return head;
  }
  else {
    return NULL;
  }
}

TEST(TestGetCurrentNode, TestOne) {
  elem_t* head = CreateHeadforTests();
  ASSERT_EQ(head, GetCurrentNode(head));
}
TEST(TestGetCurrentNode, TestSecond) {
  elem_t* head = CreateHeadforTests();
  int i;
  for (i = 0; i < SIZE + 1; i++) {
    AddElement(head, i);
  }
  ASSERT_EQ(head->next, GetCurrentNode(head));
}
TEST(TestAddElement, TestOne) {
  elem_t* head = CreateHeadforTests();
  AddElement(head, 2);
  ASSERT_EQ(2, head->arr[0]);
}
TEST(TestAddElement, TestSecond) {
  elem_t* head = CreateHeadforTests();
  int i;
  for (i = 1; i <= SIZE + 1;i++) {
    AddElement(head, i);
  }
  ASSERT_EQ(5, head->next->arr[0]);
}
TEST(TestGetElementNum, TestOne) {
  elem_t* head = CreateHeadforTests();
  AddElement(head, 2);
  ASSERT_EQ(2, GetElementNum(head, 1));
}
TEST(TestGetElementNum, TestSecond) {
  elem_t* head = CreateHeadforTests();
  AddElement(head, 2);
  ASSERT_EQ(ERROR, GetElementNum(head, 2));
}
TEST(TestGetNumKey, TestOne) {
  elem_t* head = CreateHeadforTests();
  AddElement(head, 2);
  ASSERT_EQ(1, GetNumKey(head, 2));
}
TEST(TestGetNumKey, TestSecond) {
  elem_t* head = CreateHeadforTests();
  AddElement(head, 1);
  ASSERT_EQ(ERROR, GetNumKey(head, 2));
}
TEST(TestGetNextElementKey, TestOne) {
  elem_t* head = CreateHeadforTests();
  int i;
  for (i = 1; i < 3;i++) {
    AddElement(head, i);
  }
  ASSERT_EQ(2, GetNextElementKey(head, 1));
}
TEST(TestGetNextElementKey, TestSecond) {
  elem_t* head = CreateHeadforTests();
  int i;
  for (i = 1; i < 3; i++) {
    AddElement(head, i);
  }
  ASSERT_EQ(ERROR, GetNextElementKey(head, 3));
}
TEST(TestGetNextElementKey, TestThird) {
  elem_t* head = CreateHeadforTests();
  int i;
  for (i = 1; i < 3; i++) {
    AddElement(head, i);
  }
  ASSERT_EQ(ERROR, GetNextElementKey(head, 10));
}
TEST(TestGetCountElements, TestOne) {
  elem_t* head = CreateHeadforTests();
  AddElement(head, 2);
  ASSERT_EQ(1, GetCountElements(head));
}
TEST(TestGetCountElements, TestSecond) {
  elem_t* head = CreateHeadforTests();
  int i;
  for (i = 0; i < 2*SIZE + 1; i++) {
    AddElement(head, i);
  }
  ASSERT_EQ(i, GetCountElements(head));
}
TEST(TestDeleteElement, TestOne) {
  elem_t* head = CreateHeadforTests();
  AddElement(head, 2);
  DeleteElement(head, 1);
  ASSERT_EQ(0, head->numElements);
}
TEST(TestDeleteElement, TestSecond) {
  elem_t* head = CreateHeadforTests();
  AddElement(head, 2);
  DeleteElement(head, 1);
  ASSERT_EQ(ERROR, GetElementNum(head, 1));
}
TEST(TestDeleteElement, TestThird) {
  elem_t* head = CreateHeadforTests();
  int i;
  for (i = 0; i < SIZE + 1; i++) {
    AddElement(head, i+1);
  }
  DeleteElement(head, i-1);
  ASSERT_EQ(i, GetNextElementKey(head, i-2));
}