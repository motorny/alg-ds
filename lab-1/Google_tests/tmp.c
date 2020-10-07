#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//int s[11];
struct Node {
    char *element;
//    int element;
    unsigned long long linksXor;
};

struct List {
    struct Node *firstElement;
};

struct ListPosition {
    struct Node *curPtr;
    struct Node *prevPtr;
};
/*
struct ListPosition find(struct List list, int key) {
    struct Node *prevPtr = NULL;
    struct Node *curPtr = list.firstElement;//current
    while (curPtr != NULL) {
        if (curPtr->element == key) {
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

void delete_key(struct List *list, int  key) {
    struct ListPosition ans = find(*list, key);
    struct Node *prevPtr = ans.prevPtr;
    struct Node *curPtr = ans.curPtr;//current
    struct Node *nextPtr = (struct Node *) (curPtr->linksXor ^ (unsigned long long) prevPtr);
    if (nextPtr != NULL && prevPtr != NULL) {
        prevPtr->linksXor = (prevPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) nextPtr);
        nextPtr->linksXor = (nextPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) prevPtr);
        return;
    } else if (prevPtr == NULL) {
        nextPtr->linksXor = (nextPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) prevPtr);
    } else if (nextPtr == NULL) {
        prevPtr->linksXor = (prevPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) nextPtr);
    }
    free(&curPtr);
    return;
}
void delete_position(struct List *list, struct ListPosition pos) {
    struct Node *prevPtr = pos.prevPtr;
    struct Node *curPtr = pos.curPtr;//current
    struct Node *nextPtr = (struct Node *) (curPtr->linksXor ^ (unsigned long long) prevPtr);
    if (nextPtr != NULL && prevPtr != NULL) {
        prevPtr->linksXor = (prevPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) nextPtr);
        nextPtr->linksXor = (nextPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) prevPtr);
        return;
    } else if (prevPtr == NULL) {
        nextPtr->linksXor = (nextPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) prevPtr);
    } else if (nextPtr == NULL) {
        prevPtr->linksXor = (prevPtr->linksXor ^ (unsigned long long) curPtr ^ (unsigned long long) nextPtr);
    }
    free(&curPtr);
    return;
}


void show(struct List list) {
    printf("\n");
    struct Node *prevPtr = NULL;
    struct Node *curPtr = list.firstElement;//current
    while (curPtr != NULL) {
        printf("%d ", curPtr->element);
        struct Node *nextPtr = (struct Node *) (curPtr->linksXor ^ (unsigned long long) prevPtr);
        prevPtr = curPtr;
        curPtr = nextPtr;
    }
}
*/

// push_back -> (5, NULL)
// push_front -> (NULL, 1)
/// 1 -- 2 -- 3 -- 4 -- 5
// prevPtr - 2
// nextPtr - 3
/// 1 -- 2 <-- 2.5 --> 3 -- 4 -- 5
// curPtr - 2.5
//ptr== pointer
// prevPtr->linksXor == 1 ^ 3 ^ 2.5
void add(struct List *list, struct Node *prevPtr, struct Node *nextPtr, char * value ) {
    struct Node *curPtr = (struct Node*)malloc(sizeof(struct Node));
    curPtr->element = value;
    curPtr->linksXor = (unsigned long long) prevPtr ^ (unsigned long long) nextPtr;
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
 /*void test_delete(){
    struct List testList;
    struct Node testElement;
    testElement.element=422;
    testElement.linksXor=&testElement.element;
    testList.firstElement = &testElement;
    struct ListPosition first;
    first.curPtr=testList.firstElement;
    first.prevPtr=NULL;

    delete_position(&testList,first);
    assert(testList.firstElement->linksXor==NULL);
    show(testList);
}
void test_find(){
    struct List testList;
    struct Node testElement;
    testElement.element=422;
    testElement.linksXor=&testElement.element;
    testList.firstElement = &testElement;
    struct ListPosition result;
    result.prevPtr=NULL;
    result.curPtr=&testElement.element;
    assert((find(testList,422).curPtr==result.curPtr) && (find(testList,422).prevPtr==result.prevPtr));
}*/

// // list.c
 int my_super_add(int x, int y) {
     return x + y + 42;
 }


int main_2() {

    char a[8][10] = {"first", "aba", "caba"};
    printf("%s",a[1]);
    struct List mylist;
    mylist.firstElement = NULL;
    for (int i=0;i<8;i++)
        add(&mylist, NULL, mylist.firstElement, a[i]);
//    show(mylist);
    printf("\n");
    /*  delete_key(&mylist, 3);
      show(mylist)  /*
      struct ListPosition front,back;
      front.prevPtr=NULL;
      front.curPtr=(struct Node*) mylist.firstElement->linksXor;
      front=find(mylist,2);

      delete_position(&mylist,front);
      show(mylist);
  //    printf("\n");
  //    printf("%lld",front.curPtr);
  //    printf("\n");
  //    printf("%lld",front.prevPtr);
      front=find(mylist,23);
  //    printf("\n");
  //    printf("%lld",front.curPtr);
  //    printf("\n");
  //    printf("%lld",front.prevPtr);/не работает так как поиск промахивается на 64
      add(&mylist,front.prevPtr,front.curPtr,123);
      show(mylist);
  */
    return 0;
}

