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
    free(curPtr);

}


void show(struct List list) {

    struct Node *prevPtr = NULL;
    struct Node *curPtr = list.firstElement;//current
    while (curPtr != NULL) {
        printf(" (%s) ", curPtr->element);
        struct Node *nextPtr = (struct Node *) (curPtr->linksXor ^ (unsigned long long) prevPtr);
        prevPtr = curPtr;
        curPtr = nextPtr;
    }
    printf("\n");
}

void add(struct List *list, struct Node *prevPtr, struct Node *nextPtr, const char *value) {
    struct Node *curPtr = (struct Node *) malloc(sizeof(struct Node));
    curPtr->element = value;
    curPtr->linksXor = ptr_xor(prevPtr, nextPtr);
    if (prevPtr != NULL) {
        prevPtr->linksXor ^= ptr_xor(curPtr, nextPtr);
    }
    if (nextPtr != NULL) {
        nextPtr->linksXor ^= ptr_xor(curPtr, prevPtr);
    }
    if (prevPtr == NULL) {
        list->firstElement = curPtr;
    }

}



