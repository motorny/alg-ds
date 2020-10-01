#include "pch.h"
#include "../Lab_A_Fisyuk/stack.c"


// stack
TEST(StackArrTest, CheckNullTest_returnTrue) {
    stack_t* stackArr = NULL;
    ASSERT_EQ(true, CheckNullStack(stackArr));
}

TEST(StackArrTest, PushTest_return2) {
    stack_t* stackArr = CreateStack(1);
    Push(stackArr, 2.0);
    ASSERT_EQ(2.0, Peek(stackArr));
}

TEST(StackArrTest, PopTest_return2) {
    stack_t* stackArr = CreateStack(1);
    Push(stackArr, 2.0);
    ASSERT_EQ(2.0, Pop(stackArr));
}

TEST(StackArrTest, PeekTest_return2) {
    stack_t* stackArr = CreateStack(1);
    Push(stackArr, 2.0);
    ASSERT_EQ(2.0, Peek(stackArr));
}

TEST(StackArrTest, ReallocTest_return1) {
    stack_t* stackArr = CreateStack(1);
    Push(stackArr, 2.0);
    ASSERT_EQ(1, ReallocAndCheckNull(stackArr));
}

TEST(StackArrTest, EnoughMemRealloc_return1) {
    stack_t* stackArr = CreateStack(3);
    Push(stackArr, 2.0);
    ASSERT_EQ(1, ReallocAndCheckNull(stackArr));
}

// list
TEST(StackListTest, CheckNullHead_returnTrue) {
    stackList_t* head = NULL;
    ASSERT_EQ(true, CheckNullHead(head));
}

TEST(StackListTest, PushListTest_return30) {
    stackList_t* head;
    PushList(&head, 30);
    ASSERT_EQ(30, head->value);
}

TEST(StackListTest, PopListTest_returnNumbers) {
    stackList_t* head;
    PushList(&head, 20);
    PushList(&head, 30);
    ASSERT_EQ(30, PopList(&head));
    ASSERT_EQ(20, head->value);
}

TEST(StackListTest, PeekListTest_return30) {
    stackList_t* head;
    PushList(&head, 30);
    ASSERT_EQ(30, PeekList(head));
}

TEST(StackListTest, IsEmptyPeekListTest_return0) {
    stackList_t* head = NULL;
    ASSERT_EQ(0, PeekList(head));
}

TEST(StackListTest, IsNotEmpty_return1) {
    stackList_t* head;
    PushList(&head, 30);
    ASSERT_EQ(1, IsEmptyList(head));
}

