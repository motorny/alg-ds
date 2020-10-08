//
// Created by alex4 on 03.10.2020.
//
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include "../list.hpp"

TEST(MyFirstTestSuite, MyFirstTest) {
    ASSERT_EQ(2 + 2, 4) << "MyFirstTest is failed ";
}

TEST (MyFirstTestSuite, ptrXor_AB_returnValidVal) {
    Node *ptr1 = (Node *) malloc(sizeof(Node));
    Node *ptr2 = (Node *) malloc(sizeof(Node));
    ASSERT_EQ(ptr_xor(ptr1, ptr2), ((unsigned long long) ptr1 ^ (unsigned long long) ptr2)) << "addOnly is failed";
    free(ptr1);
    free(ptr2);
}

TEST (MyFirstTestSuite, add_addOnly_returnValidVal) {
    List testList;
    testList.firstElement = NULL;
//    char * word = "second"
    add(&testList, NULL, NULL, "second");
    ASSERT_TRUE(strcmp(testList.firstElement->element, "second") == 0) << "addOnly is failed";
    free(testList.firstElement);

}

TEST (MyFirstTestSuite, add_addFront_returnValidVal) {
    List testList;
    testList.firstElement = NULL;
//    char * word = "second"
    add(&testList, NULL, NULL, "second");
    add(&testList, NULL, testList.firstElement, "first");
    ASSERT_TRUE(strcmp(testList.firstElement->element, "first") == 0) << "addFront is failed";
//    free(&testList.firstElement->linksXor);
    free(testList.firstElement);
}

TEST (MyFirstTestSuite, add_addBack_returnValidVal) {
    List testList;
    testList.firstElement = NULL;
    add(&testList, NULL, NULL, "first");
    add(&testList, testList.firstElement, NULL, "second");
    ASSERT_TRUE(strcmp(testList.firstElement->element, "first") == 0) << "addBack is failed";
    free(testList.firstElement);

}


TEST (MyFirstTestSuite, deletePositin_onlyElement_returnValidVal) {
    List testList;
    Node *testElement = (Node *) malloc(sizeof(Node));
    const char *b = "first";
    testElement->element = b;
    testElement->linksXor = (unsigned long long) NULL ^ (unsigned long long) NULL;
    testList.firstElement = testElement;
    ListPosition first;
    first.curPtr = testList.firstElement;
    first.prevPtr = NULL;
    delete_position(&testList, first);
    ASSERT_EQ(testList.firstElement, nullptr) << "delete by position only element failed";
    show(testList);

}

TEST (MyFirstTestSuite, deletePositin_firstElement_returnValidVal) {
    List testList;
    Node *firstElement = (Node *) malloc(sizeof(Node));
    Node *secondElement = (Node *) malloc(sizeof(Node));
    const char *b = "first";
    firstElement->element = b;
    const char *c = "second";
    secondElement->element = c;
    firstElement->linksXor = (unsigned long long) NULL ^ (unsigned long long) secondElement;
    testList.firstElement = firstElement;
    ListPosition first;
    first.curPtr = testList.firstElement;
    first.prevPtr = NULL;
    secondElement->linksXor = (unsigned long long) testList.firstElement ^ (unsigned long long) NULL;
    delete_position(&testList, first);
    ASSERT_EQ(testList.firstElement, secondElement) << "delete by position first element failed";
    show(testList);
}
TEST (MyFirstTestSuite, deletePositin_secondElement_returnValidVal) {
    List testList;
    Node *firstElement = (Node *) malloc(sizeof(Node));
    Node *secondElement = (Node *) malloc(sizeof(Node));
    const char *c = "second";
    secondElement->element = c;
    const char *b = "first";
    firstElement->element = b;
    firstElement->linksXor = (unsigned long long) NULL ^ (unsigned long long) secondElement;
    testList.firstElement = firstElement;
    secondElement->linksXor = (unsigned long long) testList.firstElement ^ (unsigned long long) NULL;
    ListPosition second;
    second.curPtr = secondElement;
    second.prevPtr = testList.firstElement;
    delete_position(&testList, second);
    ASSERT_EQ(testList.firstElement->linksXor, 0) << "delete by position second element failed";
    free(firstElement);
}
//this is covered by two functions "find" and " delete position
TEST (MyFirstTestSuite, deleteKey_onlyElement_returnValidVal) {
    List testList;
    Node *testElement = (Node *) malloc(sizeof(Node));
    const char *b = "first";
    testElement->element = b;
    testElement->linksXor = (unsigned long long) NULL ^ (unsigned long long) NULL;
    testList.firstElement = testElement;
    delete_key(&testList, b);
    ASSERT_EQ(testList.firstElement, nullptr) << "delete by key element failed";
    show(testList);
}

TEST (MyFirstTestSuite, find_onlyElement_returnValidVal) {
    List testList;
    const char *word = "first";
    Node *testElement = (Node *) malloc(sizeof(Node));
    testElement->element = word;
    testElement->linksXor = 0;
    testList.firstElement = testElement;
    struct ListPosition pos = find(testList, word);
    ASSERT_TRUE((unsigned long long) testList.firstElement == (unsigned long long) pos.curPtr)
                                << "find only element failed";
    free(testElement);
}
TEST (MyFirstTestSuite, find_firstElement_returnValidVal) {
    List testList;
    Node *firstElement = (Node *) malloc(sizeof(Node));
    Node *secondElement = (Node *) malloc(sizeof(Node));
    const char *c = "second";
    secondElement->element = c;
    const char *b = "first";
    firstElement->element = b;
    firstElement->linksXor = (unsigned long long) NULL ^ (unsigned long long) secondElement;
    testList.firstElement = firstElement;
    secondElement->linksXor = (unsigned long long) testList.firstElement ^ (unsigned long long) NULL;
    struct ListPosition pos = find(testList, b);
    ASSERT_TRUE((unsigned long long) testList.firstElement == (unsigned long long) pos.curPtr)
                                << "find first element failed";
    free(firstElement);
    free(secondElement);
}
TEST (MyFirstTestSuite, find_secondElement_returnValidVal) {
    List testList;
    Node *firstElement = (Node *) malloc(sizeof(Node));
    Node *secondElement = (Node *) malloc(sizeof(Node));
    const char *c = "second";
    secondElement->element = c;
    const char *b = "first";
    firstElement->element = b;
    firstElement->linksXor = (unsigned long long) NULL ^ (unsigned long long) secondElement;
    testList.firstElement = firstElement;
    secondElement->linksXor = (unsigned long long) testList.firstElement ^ (unsigned long long) NULL;
    struct ListPosition pos = find(testList, c);
    ASSERT_TRUE((unsigned long long) secondElement == (unsigned long long) pos.curPtr)
                                << "find second element failed";
    free(firstElement);
    free(secondElement);
}
