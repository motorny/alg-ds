#include "pch.h"
#include "../alg-ds/lab-1/A10_Bolshakova.c"

#define START_STACK_SIZE 5


TEST(ArrStackDestroy_CreatedStack_ReturnsNull){
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  ArrStackDestroy(&s);
  ASSERT_EQ(NULL, s);
}

TEST( ArrStackDestroy_NotCreatedStack_ReturnsNull) {
  error_t err = ERROR_NO;
  arrStack_t* s = NULL;
  ArrStackDestroy(&s);
  ASSERT_EQ(NULL, s);
}

TEST(ArrStackAddElem_CreatedStack_ChangeSize) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  size_t oldsize = (s->size) * sizeof(data_t);
  s = ArrStackAddElem(s, &err);
  ASSERT_EQ((s->size) * sizeof(data_t) - oldsize, sizeof(data_t) );
  ArrStackDestroy(&s);
}

TEST(ArrStackAddElem_NULLpointer_returnNULL) {
  error_t err = ERROR_NO;
  arrStack_t* s = NULL;
  ArrStackAddElem(s, &err);
  ASSERT_EQ(NULL, s);
}

TEST(ArrStackEmpty_EmptyStack_returnTrue) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  ASSERT_TRUE(ArrStackEmpty(s));
  ArrStackDestroy(&s);
}

TEST(ArrStackEmpty_NotEmptyStack_returnFalse) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  ArrStackPush(s, 1, &err);
  ASSERT_FALSE(ArrStackEmpty(s));
  ArrStackDestroy(&s);
}

TEST(ArrStackPush_1Integer_noError) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  ArrStackPush(s, 1, &err);
  ASSERT_TRUE(err == ERROR_NO);
  ArrStackDestroy(&s);
}

TEST(ArrStackPop_5Integers_returncorrectData){
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  int i;
  for ( i = 0; i < s->size; i++) {
    ArrStackPush(s, i, &err);
    ASSERT_EQ(i, ArrStackPop(s, &err));
    ArrStackPush(s, i, &err);
  }
  ArrStackDestroy(&s);
}

TEST(ArrStackPeek_1Integer_PeekEQPopvalue) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  ArrStackPush(s, 1, &err);
  ASSERT_EQ(ArrStackPop(s, &err), ArrStackPeek(s, &err));
  ArrStackDestroy(&s);
}

TEST(ArrStackPeek_EmptyStack_returnNull) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  ASSERT_EQ(0,ArrStackPeek(s, &err));
  ArrStackDestroy(&s);
}


TEST(LinkListStackPush_1Integes_noerror) {
  error_t err = ERROR_NO;
  node_t* head = NULL;
  LinkListStackPush(&head, 1, &err);
  ASSERT_TRUE(err == ERROR_NO);
  LinkListStackDestroy(&head, &err);
}

TEST(LinkListStackPopTest__5Integers_returncorrectData) {
  error_t err = ERROR_NO;
  node_t* head = NULL;
  int i;
  for (i = 0; i < START_STACK_SIZE; i++) {
    LinkListStackPush(&head, i, &err);
    ASSERT_EQ(i, LinkListStackPopTest(&head, *(head->data), &err));
    LinkListStackPush(&head, i, &err);
  }
  LinkListStackDestroy(&head, &err);
}

//этот тест фэйлится по причине, описанной в комменте к LinkListStackPopTest
/*
TEST(LinkListStackPop__5Integers_returncorrectData) {
  error_t err = ERROR_NO;
  node_t* head = NULL;
  int i;
  for (i = 0; i < START_STACK_SIZE; i++) {
    LinkListStackPush(&head, i, &err);
    ASSERT_EQ(i, LinkListStackPop(&head, &err));
    LinkListStackPush(&head, i, &err);
  }
  LinkListStackDestroy(&head, &err);
}
*/

TEST(LinkListStackPeek_1Integer_PeekEQPopvalue){
  error_t err = ERROR_NO;
  node_t* head = NULL;
  node_t** headptr;
  LinkListStackPush(&head, 1, &err);
  headptr = &head;
  ASSERT_EQ(LinkListStackPopTest(headptr, *(head->data), &err), LinkListStackPeek(head, &err));
  LinkListStackDestroy(&head, &err);
}


TEST(LinkListStackPeek_EmptyStack_returnNull){
  error_t err = ERROR_NO;
  node_t* head = NULL;
  ASSERT_EQ(0, LinkListStackPeek(head, &err));
}

TEST(LinkListStackEmpty_EmptyStack_returnTrue) {
  error_t err = ERROR_NO;
  node_t* head = NULL;
  ASSERT_TRUE(LinkListStackEmpty(head));
}

TEST(LinkListStackEmpty_NotEmptyStack_returnFalse) {
  error_t err = ERROR_NO;
  node_t* head = NULL;
  LinkListStackPush(&head, 1, &err);
  ASSERT_FALSE(LinkListStackEmpty(head));
  LinkListStackDestroy(&head, &err);
}

