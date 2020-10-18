
#include <stdlib.h>
#include "pch.h" 
#include "../List_Kungurov_23/FunsForList.c"
TEST(Test, Compare) {
	ASSERT_EQ(0,Compare("a","b"));
    ASSERT_EQ(1, Compare("aasdasd", "b"));
    ASSERT_EQ(1, Compare("aasdasd", "aasdasA"));
}
TEST(Test, Push) {
    DoubleLinkedList* List = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    Push(List, "1");
    ASSERT_STREQ("1", (List->head->value));
    free(List);
}
TEST(Test, PushFront) {
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
TEST(Test, PushBack) {
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
    PutBeforeElement(List, List->tail, "2.5");
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
    PutOnTheRightPlace("B", List);
    ASSERT_STREQ("B", List->head->next->value);
}
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
