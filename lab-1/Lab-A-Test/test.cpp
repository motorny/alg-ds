#include "pch.h"
#include "../Lab_A_Fisyuk/stack.c"
#define ERROR_STACK_TEST NULL


stack_t* CreateStackForTest(int size) {
    stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
    if (CheckNullStack(stack)) {
        return ERROR_STACK_TEST;
    }
    stack->data_size = size;
    stack->last = 0;
    stack->data = (type_t*)malloc(sizeof(type_t) * stack->data_size);
    if (stack->data == NULL) {
        free(stack);
        return ERROR_STACK_TEST;
    }
    return stack;
}

// array
TEST(StackArrTest, CheckNullTest_returnTrue) {
    stack_t* stackArr = NULL;
    ASSERT_EQ(true, CheckNullStack(stackArr));
}

TEST(StackArrTest, PushTest_return2) {
    stack_t* stackArr = CreateStackForTest(1);
    Push(stackArr, 2.0);
    ASSERT_EQ(2.0, stackArr->data[0]);
    ASSERT_EQ(1, stackArr->last);
}

TEST(StackArrTest, PopTest_returnNumbers) {
    stack_t* stackArr = CreateStackForTest(1);
    stackArr->data[0] = 4;
    stackArr->last++;
    ASSERT_EQ(4.0, Pop(stackArr));
    ASSERT_EQ(0, stackArr->last);
}

TEST(StackArrTest, ErrorPopTest_returnError) {
    stack_t* stackArr = NULL;
    ASSERT_EQ(ERROR_EMPTY_STACK, Pop(stackArr));
}

TEST(StackArrTest, PeekTest_return5) {
    stack_t* stackArr = CreateStackForTest(1);
    stackArr->data[0] = 5;
    stackArr->last++;
    ASSERT_EQ(5, Peek(stackArr));
}

TEST(StackArrTest, ReallocTest_return1) {
    stack_t* stackArr = CreateStackForTest(1);
    stackArr->data[0] = 5;
    stackArr->last++;
    ASSERT_EQ(1, ReallocAndCheckNull(stackArr));
}

TEST(StackArrTest, EnoughMemRealloc_return1) {
    stack_t* stackArr = CreateStack(2);
    stackArr->data[0] = 5;
    stackArr->last++;
    ASSERT_EQ(1, ReallocAndCheckNull(stackArr));
}

TEST(StackArrTest, PushTest_Realloc_return2andTrue) {
    stack_t* stackArr = CreateStackForTest(1);
    stackArr->data[0] = 4;
    stackArr->last++;
    Push(stackArr, 2.0);
    ASSERT_EQ(2.0, stackArr->data[1]);
    EXPECT_TRUE(stackArr->last == 2);
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

TEST(StackListTest, PopListTest_return7andNULL) {
    stackList_t* head = (stackList_t*)malloc(sizeof(stackList_t));
    head->value = 7;
    head->next = NULL;
    ASSERT_EQ(7, PopList(&head));
    ASSERT_EQ(NULL, head);
}

TEST(StackListTest, PeekListTest_return30) {
    stackList_t* head = (stackList_t*)malloc(sizeof(stackList_t));
    head->value = 30;
    ASSERT_EQ(30, PeekList(head));
}

TEST(StackListTest, PeekEmptyListTest_Error) {
    stackList_t* head = NULL;
    ASSERT_EQ(ERROR_EMPTY_STACK, PeekList(head));
}

TEST(StackListTest, IsEmptyPeekListTest_return0) {
    stackList_t* head = NULL;
    ASSERT_EQ(0, PeekList(head));
}

TEST(StackListTest, IsNotEmpty_return1) {
    stackList_t* head = (stackList_t*)malloc(sizeof(stackList_t));
    head->value = 7;
    head->next = NULL;
    ASSERT_EQ(1, IsEmptyList(head));
}

