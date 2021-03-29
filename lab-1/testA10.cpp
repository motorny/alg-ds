#include "pch.h"
#include "../alg-ds/lab-1/A10_Bolshakova.c"

#define START_STACK_SIZE 5
arrStack_t* ArrStackOnes(error_t* err) {
  arrStack_t* stack = (arrStack_t*)malloc(sizeof(arrStack_t));
  if (stack == NULL) {
    *err = OUT_OF_MEMORY;
    return NULL;
  }
  stack->size = 1;
  stack->data = (data_t*)malloc((stack->size) * sizeof(data_t));
  if (stack->data == NULL) {
    free(stack);
    *err = OUT_OF_MEMORY;
    return NULL;
  }
  stack->top = 0;
  stack->data[stack->top] = 1;
  stack->top = 1;
  return stack;
}

//функция создания стека из одного элемента , data == 1
void LinkListOneStack(node_t** head, error_t* err) {
  node_t* node = (node_t*)malloc(sizeof(node_t));
  data_t dat = 1;
  if (node == NULL) {
    *err = OUT_OF_MEMORY;
  }
  else {
    node->next = *head;
    node->data = &dat;
    *head = node;
  }
}

TEST(ArrStackDestroy_CreatedStack_ReturnsNull) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  ArrStackDestroy(&s);
  ASSERT_EQ(NULL, s);
}

TEST(ArrStackDestroy_NotCreatedStack_ReturnsNull) {
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
  ASSERT_EQ((s->size) * sizeof(data_t) - oldsize, sizeof(data_t));
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

TEST(ArrStackPop_OnesStack_PopEQ1) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackOnes(&err);
  ASSERT_EQ(ArrStackPop(s, &err), 1);
  ArrStackDestroy(&s);
}


TEST(ArrStackPeek_EmptyStack_returnNull) {
  error_t err = ERROR_NO;
  arrStack_t* s = ArrStackCreate(START_STACK_SIZE, &err);
  ASSERT_EQ(0, ArrStackPeek(s, &err));
  ArrStackDestroy(&s);
}


TEST(LinkListStackPush_1Integes_noerror) {
  error_t err = ERROR_NO;
  node_t* head = NULL;
  LinkListStackPush(&head, 1, &err);
  ASSERT_TRUE(err == ERROR_NO);
  LinkListStackDestroy(&head, &err);
}

TEST(LinkListStackPopTest__StackOfOnes_returncorrectData) {
  error_t err = ERROR_NO;
  node_t* head = NULL;
  LinkListOneStack(&head, &err);
  ASSERT_EQ(1, LinkListStackPopTest(&head, *(head->data), &err));
}

TEST(LinkListStackPeek_1Integer_Return1) {
  error_t err = ERROR_NO;
  node_t* head = NULL;
  LinkListOneStack(&head, &err);
  ASSERT_EQ(1, LinkListStackPeek(head, &err));
  LinkListStackDestroy(&head, &err);
}


TEST(LinkListStackPeek_EmptyStack_returnNull) {
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

