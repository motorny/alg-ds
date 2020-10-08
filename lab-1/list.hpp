//
// Created by alex4 on 03.10.2020.
//

#ifndef LABA1_LIST_HPP
#define LABA1_LIST_HPP
int main_2();
//////
struct Node {
    const char *element;
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

extern "C" {
    struct ListPosition find(struct List list, const char *key);
unsigned long long ptr_xor(struct Node *ptr1, struct Node *ptr2);
void show(struct List list);
void delete_position(struct List *list, struct ListPosition pos);
void delete_key(struct List *list, const char *key);
void add(struct List *list, struct Node *prevPtr, struct Node *nextPtr, const char *value);
}
#endif //LABA1_LIST_HPP
