#pragma once
#include <stdlib.h>
#define CR struct List* CreateTestList(int a, int b, int c){\
struct List* list = malloc(sizeof(struct List));\
struct Node* el1 = (struct Node*)malloc(sizeof(struct Node));\
struct Node* el2 = (struct Node*)malloc(sizeof(struct Node));\
struct Node* el3 = (struct Node*)malloc(sizeof(struct Node));\
list->first = el1;\
el1->next = el2;\
el2->next = el3;\
el3->next = NULL;\
el1->data.int_field = a;\
el2->data.int_field = b;\
el3->data.int_field = c;\
return list;\
}
#define RC