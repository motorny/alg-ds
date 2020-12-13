#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef struct _Node {
    int value;
    struct _Node* next;
    struct _Node* prev;
} Node;

typedef struct _DblLinkedList {
    size_t size;
    Node* head;
    Node* tail;
} DblLinkedList;

DblLinkedList* CreateList(void);
void DeleteList(DblLinkedList* list);
int AddData(DblLinkedList* list,int  data);//
//int popFront(DblLinkedList* list);
//int popBack(DblLinkedList* list);
void PrintList(DblLinkedList* list);
void SortList(DblLinkedList* list);//