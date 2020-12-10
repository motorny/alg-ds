#include "pch.h"
extern"C" {
#include"../Stack/stack.h"
}

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(PushArrayStack, AddingElem) {
    error_t err = ERROR_NO;
    int arr[3];
    ArrayStack_t stek = { arr, 0, 3 };
    PushArrayStack(&stek, 5, &err);
    int b;
    b = stek.data[stek.top - 1];
    ASSERT_EQ(5, b);
}

TEST(PushArrayStack, AddingFewElements) {
    error_t err = ERROR_NO;
    int arr[3] = {2, 3};
    ArrayStack_t stek = { arr, 2, 3 };
    PushArrayStack(&stek, 5, &err);
    int b;
    b = stek.data[stek.top - 1];
    ASSERT_EQ(5, b);
}

TEST(PopArrayStack, PopTest_RetunsLastElem) {
    error_t err = ERROR_NO;
    int arr[3] = { 2, 3, 4 };
    ArrayStack_t stek = { arr, 3, 3 };
  
    int b = PopArrayStack(&stek, &err);
    ASSERT_EQ(4, b);
}

TEST(PopArrayStack, PopTest_UnderflowAttempt) {
    int arr[1] = { 2 };
    error_t err = ERROR_NO;
    ArrayStack_t stek = { arr, 1, 1 };
    int a = PopArrayStack(&stek, &err);
    int b = PopArrayStack(&stek, &err);
    ASSERT_EQ(0, b);
}

TEST(PushArrayList, AddingElem) {
    ListStack_t *stek = NULL;
    error_t err = ERROR_NO;
    stek = CreateListStack(&err);
    PushListStack(&stek, 23, &err);
    int elem = stek->data;
    ASSERT_EQ(23, elem);
}

TEST(PushListStack, AddingFewElem) {
    error_t err = ERROR_NO;
    ListStack_t* stek = NULL;
    stek = CreateListStack(&err);
    PushListStack(&stek, 23, &err);
    PushListStack(&stek, 433, &err);
    PushListStack(&stek, 54, &err);
    int elem = stek->data;
    ASSERT_EQ(54, elem);
}



TEST(PopListStack, PopPushInteraction_ReturnPushedElement) {
    error_t err = ERROR_NO;
    ListStack_t* stek = CreateListStack(&err);
    ListStack_t* newElem = CreateListStack(&err);
    newElem->data = 1;
    newElem->prev = stek;
    stek = newElem;
    EXPECT_TRUE(PopListStack(&stek, &err) == 1);
    EXPECT_TRUE(stek->prev == NULL);
}

