#include "pch.h"
#include"../library/list.c"
#include <stdlib.h>
TEST(AddDataTest,NULL_list_return_error) {
  EXPECT_EQ(AddData(NULL,5), 1);
}
TEST(AddData_Test, NULL_list_return_error1) {
    DblLinkedList* list = (DblLinkedList*)malloc(sizeof(DblLinkedList));
    list->size = 0;
    list->head = list->tail = NULL;
    EXPECT_EQ(AddData(list, 5), 0);
}
TEST(DeleteList_Test, DeleteList_e) {
    DblLinkedList* list = (DblLinkedList*)malloc(sizeof(DblLinkedList));
    list->size = 0;
    list->head = list->tail = NULL;
    DeleteList(list);
    EXPECT_TRUE(list);
    //EXPECT_EQ(list, NULL);

}

TEST(CreateList_Test, CreateList_e) {
    DblLinkedList* list_nul = NULL;
    DblLinkedList* list = CreateList();
    EXPECT_NE(list, list_nul);
}
TEST(SortList_Test,SorList_e) {
    Node* tmp = NULL;
    int i;
    int min = INT_MIN;
    DblLinkedList* list = CreateList();
    for(i=0;i<5;i++)
    AddData(list, rand());
    
    SortList(list);
    tmp = list->head;
    while (tmp) {
        EXPECT_GE(tmp->value,min);
        min = tmp->value;
        tmp = tmp->next;
    }

}
