
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "list.h"
int main(){
    char a[3][10] = {"first", "aba", "caba"};
//    printf("%s",a[1]);
    struct List mylist;
    mylist.firstElement = NULL;
    for (int i = 0; i < 3; i++)
        add(&mylist, NULL, mylist.firstElement, a[i]);
    show(mylist);
    printf("\n");
    struct ListPosition front, back;
    front.prevPtr = NULL;
    front.curPtr = mylist.firstElement;
    delete_position(&mylist,front);
    show(mylist);
    front = find(mylist, "caba");
    printf("\n");
    show(mylist);
    delete_key(&mylist, "caba");
    delete_key(&mylist, "aba");

    show(mylist);
    return 0;
}
