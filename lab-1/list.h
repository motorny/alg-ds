

#ifndef LABA1_LIST_H
#define LABA1_LIST_H
int main_2();
//////
struct Node {
    const char *element;
    unsigned long long linksXor;
};

struct List {
    struct Node *firstElement;
};

struct ListPosition {
    struct Node *curPtr;
    struct Node *prevPtr;
};
unsigned long long ptr_xor(struct Node *ptr1, struct Node *ptr2);
struct ListPosition find(struct List list, const char *key);
void show(struct List list);
//extern "C" {
void delete_position(struct List *list, struct ListPosition pos);

void delete_key(struct List *list, const char *key);
void add(struct List *list, struct Node *prevPtr, struct Node *nextPtr, const char *value);
//}
#endif //LABA1_LIST_H
