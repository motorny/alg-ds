#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "list.h"

unsigned long long ptr_xor(struct Node *ptr1, struct Node *ptr2) {
    return (unsigned long long) ptr1 ^ (unsigned long long) ptr2;
}

struct ListPosition find(struct List list, const char *key) {
    struct Node *prevPtr = NULL;
    struct Node *curPtr = list.firstElement;//current
    while (curPtr != NULL) {
        if (strcmp(curPtr->element, key) == 0) {
            struct ListPosition ans;
            ans.curPtr = curPtr;
            ans.prevPtr = prevPtr;
            return ans;
        }
        struct Node *nextPtr = (struct Node *) (curPtr->linksXor ^ (unsigned long long) prevPtr);
        prevPtr = curPtr;
        curPtr = nextPtr;
    }
    struct ListPosition ans;
    ans.curPtr = NULL;
    ans.prevPtr = NULL;
    return ans;
}


void delete_key(struct List *list, const char *key) {
    struct ListPosition ans = find(*list, key);
    delete_position(list, ans);

}

void delete_position(struct List *list, struct ListPosition pos) {
    if (pos.curPtr == NULL) {
        return;
    }
    struct Node *prevPtr = pos.prevPtr;
    struct Node *curPtr = pos.curPtr;//current
    struct Node *nextPtr = (struct Node *) (curPtr->linksXor ^ (unsigned long long) prevPtr);

    if (nextPtr != NULL) {
        nextPtr->linksXor = (nextPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) prevPtr);
    }
    if (prevPtr != NULL) {
        prevPtr->linksXor = (prevPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) nextPtr);
    }
    if (prevPtr == NULL) {
        assert(list->firstElement == curPtr);
        list->firstElement = nextPtr;
    }
    printf("free %lld ", (unsigned long long) curPtr);
    free(curPtr);

}


void show(struct List list) {


//    printf(" %s ", "(unsigned long long) curPtr");
    struct Node *prevPtr = NULL;
    struct Node *curPtr = list.firstElement;//current

//    printf(" %lld ", (unsigned long long) curPtr);
    while (curPtr != NULL) {
        printf(" (%s) ", curPtr->element);
        struct Node *nextPtr = (struct Node *) (curPtr->linksXor ^ (unsigned long long) prevPtr);
        prevPtr = curPtr;
        curPtr = nextPtr;
    }
    printf("\n");
}


// push_back -> (5, NULL)
// push_front -> (NULL, 1)
/// 1 -- 2 -- 3 -- 4 -- 5
// prevPtr - 0
// nextPtr - 1
/// <0>--1 -- 2 <-- 2.5 --> 3 -- 4 -- 5
// curPtr - 2.5
//ptr== pointer
// prevPtr->linksXor == 1 ^ 3 ^ 2.5
void add(struct List *list, struct Node *prevPtr, struct Node *nextPtr, const char *value) {
    struct Node *curPtr = (struct Node *) malloc(sizeof(struct Node));
//    printf("%lld ", (unsigned long long) curPtr);
    curPtr->element = value;
    curPtr->linksXor = ptr_xor(prevPtr, nextPtr);
    if (prevPtr != NULL) {
        prevPtr->linksXor ^= (unsigned long long) curPtr ^ (unsigned long long) nextPtr;
    }
    if (nextPtr != NULL) {
        nextPtr->linksXor ^= (unsigned long long) curPtr ^ (unsigned long long) prevPtr;
    }
    if (prevPtr == NULL) {
        list->firstElement = curPtr;
    }

}


int main_2() {

    char a[3][10] = {"first", "aba", "caba"};
//    printf("%s",a[1]);
    struct List mylist;
    mylist.firstElement = NULL;
    for (int i = 0; i < 3; i++)
        add(&mylist, NULL, mylist.firstElement, a[i]);
    show(mylist);
    printf("\n");
    struct ListPosition front, back;

//    int x[10]; // stack
//    int * y = malloc(sizeof(int) * 10) ;// heap  new
//
//    vector<int> vec;
//    char * z = "first"; // string literal
//    z[0] = 'd'
//    front = find(mylist, "first");
//    printf("")
    front.prevPtr = NULL;
    front.curPtr = (struct Node *) mylist.firstElement->linksXor;
    front = find(mylist, "caba");
    printf("\n");
//    printf("%lld", front.curPtr);
//    printf("\n");
//    printf("%lld", front.prevPtr);
    show(mylist);
    delete_key(&mylist, "caba");
//    delete_position(&mylist,front);
    delete_key(&mylist, "aba");
    printf(" \n%s  \n", "______________________");
    add(&mylist, NULL, mylist.firstElement, "3");
    show(mylist);
    add(&mylist, NULL, mylist.firstElement, "4");
    show(mylist);
    add(&mylist, NULL, mylist.firstElement, "5");
    show(mylist);
    puts("");
    add(&mylist, NULL, mylist.firstElement, "6");
    printf("Before last show!!/n");
    show(mylist);
    return 0;
}

