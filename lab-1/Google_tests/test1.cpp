//
// Created by alex4 on 03.10.2020.
//
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include "../list.hpp"

TEST(MyFirstTestSuite, MyFirstTest) {
    ASSERT_EQ(2 + 2,4);
}
TEST (MyFirstTestSuite,test_Add){
    List testList;
    testList.firstElement = NULL;
//    char * word = "second"
    add(&testList,NULL,NULL,"second" );
    ASSERT_TRUE(strcmp(testList.firstElement->element,"second")==0 );
    free(testList.firstElement);
}

TEST (MyFirstTestSuite,test_delete_position){
    List testList;
    Node* testElement = (Node*) malloc(sizeof(Node));
    const char *b = "first";
    testElement->element=b;
    testElement->linksXor = (unsigned long long) NULL ^ (unsigned long long) NULL;
    testList.firstElement = testElement;
    ListPosition first;
    first.curPtr=testList.firstElement;
    first.prevPtr=NULL;
    delete_position(&testList,first);
    ASSERT_EQ(testList.firstElement, nullptr);
    show(testList);

}
TEST (MyFirstTestSuite,test_delete_key){
    List testList;
    Node* testElement = (Node*) malloc(sizeof(Node));
    const char *b = "first";
    testElement->element=b;
    testElement->linksXor = (unsigned long long) NULL ^ (unsigned long long) NULL;
    testList.firstElement = testElement;
    delete_key(&testList,b);
    ASSERT_EQ(testList.firstElement, nullptr);
    show(testList);
}
TEST (MyFirstTestSuite,test_find){
    List testList;
    const char * word="first";
    Node* testElement = (Node*) malloc(sizeof(Node));
    testElement->element=word;
    testElement->linksXor=0;
    testList.firstElement=testElement;
    struct  ListPosition pos= find(testList,word);
    ASSERT_TRUE((unsigned long long) testList.firstElement==(unsigned long long) pos.curPtr) ;
    free(testElement);
}