
#include <stdlib.h>
#include "pch.h" 
#include "../List_Kungurov_23/FunsForList.c"
TEST(Test, Compare) {
	ASSERT_EQ(0, Compare("a","b"));
    ASSERT_EQ(1, Compare("aasdasd", "b"));
    ASSERT_EQ(1, Compare("aasdasd", "aasdasA"));
    ASSERT_EQ(1, Compare("a",""));
    ASSERT_EQ(1, Compare("a", "a"));
    ASSERT_EQ(1, Compare("a", "0"));
}
TEST(Test, PushFront) { //если список не пустой if(size != 0)
    DoubleLinkedList* List = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    Node* HEAD = (Node*)malloc(sizeof(Node));
    Node* TAIL = (Node*)malloc(sizeof(Node));
    HEAD->value = "2";
    TAIL->value = "3";
    List->head = HEAD;
    List->tail = TAIL;
    List->head->prev = NULL;
    List->tail->next = NULL;
    List->head->next = List->tail;
    List->tail->prev = List->head;
    PushFront(List, "1");
    ASSERT_STREQ("1", (List->head->value));
    free(HEAD);
    free(List);
    free(TAIL);
}

TEST(Test, PPushFront) {// if size == 0
    //если список пустой (если длина списка равна нулю, то вход есть только в эту функцию)
    DoubleLinkedList* List = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    Node* HEAD = NULL;
    Node* TAIL = NULL;
    List->size = 0;
    List->head = HEAD;
    List->tail = TAIL;
    //PushFront(List, "A");
    ASSERT_EQ(0, PushFront(List, "A")); //SUCCESS
    ASSERT_STREQ("A", (List->head->value));
    free(HEAD);
    free(List);
    free(TAIL);
}
TEST(Test, PushBack) { // the same 
    DoubleLinkedList* List = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    Node* HEAD = (Node*)malloc(sizeof(Node));
    Node* TAIL = (Node*)malloc(sizeof(Node));
    HEAD->value = "2";
    TAIL->value = "3";
    List->head = HEAD;
    List->tail = TAIL;
    List->head->prev = NULL;
    List->tail->next = NULL;
    List->head->next = List->tail;
    List->tail->prev = List->head;
    PushBack(List, "4");
    ASSERT_STREQ("4", (List->tail->value));
    free(HEAD);
    free(List);
    free(TAIL);
}
TEST(Test, PPushBack) { // if (size == 1) && number of (head->value) > number of word
    DoubleLinkedList* List = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    Node* HEAD = (Node*)malloc(sizeof(Node));
    Node* TAIL = NULL;
    HEAD->value = "4";
    List->size = 1;
    List->head = HEAD;
    List->tail = TAIL;
    List->head->prev = NULL;
    List->head->next = List->tail;
    ASSERT_EQ(0,(PushBack(List, "2"))); //SUCCESS
    ASSERT_STREQ("2", (List->head->value));
    ASSERT_STREQ("4", (List->tail->value));
    free(HEAD);
    free(List);
    free(TAIL);
}
TEST(Test, PPPushBack) { // if (size == 1) && number of (head->value) < number of word
    DoubleLinkedList* List = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    Node* HEAD = (Node*)malloc(sizeof(Node));
    Node* TAIL = NULL;
    HEAD->value = "4";
    List->size = 1;
    List->head = HEAD;
    List->tail = TAIL;
    List->head->prev = NULL;
    List->head->next = List->tail;
    ASSERT_EQ(0, (PushBack(List, "6"))); //SUCCESS
    ASSERT_STREQ("4", (List->head->value));
    ASSERT_STREQ("6", (List->tail->value));
    free(HEAD);
    free(List);
    free(TAIL);
}
TEST(Test, PutBeforeElement) {
    DoubleLinkedList* List = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    Node* HEAD = (Node*)malloc(sizeof(Node));
    Node* TAIL = (Node*)malloc(sizeof(Node));
    HEAD->value = "2";
    TAIL->value = "3";
    List->head = HEAD;
    List->tail = TAIL;
    List->head->prev = NULL;
    List->tail->next = NULL;
    List->head->next = List->tail;
    List->tail->prev = List->head;
    ASSERT_EQ(0,((PutBeforeElement(List, List->tail, "2.5")))); //SUCCESS
    ASSERT_STREQ("2.5", (List->tail->prev->value));
}

TEST(Test, PutOnTheRightPlace) {
    DoubleLinkedList* List = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    Node* HEAD = (Node*)malloc(sizeof(Node));
    Node* TAIL = (Node*)malloc(sizeof(Node));
    HEAD->value = "A";
    TAIL->value = "D";
    List->head = HEAD;
    List->tail = TAIL;
    List->head->prev = NULL;
    List->tail->next = NULL;
    List->head->next = List->tail;
    List->tail->prev = List->head;
    List->size = 2;
    ASSERT_EQ(0,(PutOnTheRightPlace("B", List)));
    ASSERT_STREQ("A", List->head->value);
    ASSERT_STREQ("D", List->tail->value);
    ASSERT_STREQ("B", List->head->next->value);
    ASSERT_STREQ("B", List->tail->prev->value);
    ASSERT_EQ(3, List->size);
}
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
