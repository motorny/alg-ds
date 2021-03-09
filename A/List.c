#include <stdlib.h>

#include "List.h"

Node_t* newNode(int data) {
    Node_t* node = (Node_t*) malloc(sizeof(Node_t));
    if (node) {
        node->data = data;
        node->next = NULL;
        return node;
    }
    return NULL;
}

Node_t* insert(Node_t* last, int data) {
    Node_t* node = newNode(data);
    if (node == NULL)
        return last;

    if (last != NULL) {
        node->next = last;
        last = node;
    } else
        last = node;
    return last;
}

Node_t* pop(Node_t* last) {
    Node_t* curr = last;
    if (last == NULL)
        return NULL;
    if (last->next == NULL) {
        free(last);
        return NULL;
    }

    while (curr->next->next != NULL)
        curr = curr->next;
    free(curr->next);
    curr->next = NULL;

    return last;
}

void freeList(Node_t* last) {
    while (last != NULL)
        last = pop(last);
}