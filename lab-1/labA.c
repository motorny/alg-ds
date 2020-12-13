#include"list.h"
#include<stdio.h>
#include<stdlib.h>

int main(void) {
    DblLinkedList* list = CreateList();
    AddData(list, 5);
    AddData(list, 1);
    AddData(list, 3);
    AddData(list, 2);
    AddData(list, 4);
    AddData(list, 9);
    PrintList(list);
    SortList(list);
    PrintList(list);

    return 0;
}
