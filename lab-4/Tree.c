#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct node{
    struct node *left;
    struct node *right;
    struct node *parent;
    int key, width, size;
    char data[200];
}node_t;

node_t *firstNode = NULL;

void ChangeWidth(node_t *start, int value){
    node_t *node = start;
    while ( node ) {
        node->width += value;
        node = node->parent;
    }
}

void ChangeSize(node_t *start, int value){
    node_t *node = start;
    while ( node ) {
        node->size += value;
        node = node->parent;
    }
}

node_t **SearchPlace(int key, node_t **start){
    node_t **node = start;
    while ( (*node) ) {
        if ( (*node)->key > key ){
            if ( (*node)->left == NULL ){
                if ( !((*node)->left = (node_t *) malloc(sizeof(node_t))) )
                    return NULL;

                (*node)->left->parent = *node;
                node = &(*node)->left;
                break;
            }
            else
                node = &(*node)->left;
        }
        else if ( (*node)->key == key )
            return 0;
        else{
            if ( (*node)->right == NULL ){
                if ( !((*node)->right = (node_t *) malloc(sizeof(node_t))) )
                    return NULL;

                (*node)->right->parent = *node;
                node = &(*node)->right;
                break;
            }
            else
                node = &(*node)->right;
        }
    }

    if ( !(*node) )
        if ( *node = (node_t *) malloc(sizeof(node_t)) )
            (*node)->parent = NULL;
        else
            return NULL;
    return node;
}

int AddNode(int key, const char *data){
    int width = strlen(data);
    node_t **node = SearchPlace(key, &firstNode);

    if ( !node )
        return 1;

    (*node)->key = key;
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->width = 0;
    (*node)->size = 0;
    strcpy((*node)->data, data);
    ChangeSize((*node)->parent, 1);
    ChangeWidth((*node)->parent, width);
    return 0;
}

node_t **FindNode(int key) {
    node_t **node = &firstNode;
    while ( (*node) ) {
        if ( (*node)->key == key )
            break;
        else if ( key < (*node)->key )
            node = &(*node)->left;
        else
            node = &(*node)->right;
    }
    return node;
}

int SearchNodeKLower(node_t *start, int delta){
    if ( !delta )
        return start->key;

    if ( delta > start->size || start->left == NULL )
        return 0;

    return SearchNodeKLower(start->left, delta - 1);
}

int FindNodeKLower(node_t *start, int delta){
    int key;

    if ( start->left && start->size >= delta && (key = SearchNodeKLower(start->left, delta - 1)) )
        return key;

    if ( !start->parent )
        return 0;

    if ( start->parent->left == start )
        return  FindNodeKLower(start->parent, delta + 1);
    else
        return FindNodeKLower(start->parent, delta - 1);
}

void DeleteNode(int key) {
    node_t **node = FindNode(key), **newNode = NULL, *buf;

    if ( !(*node) ) return;

    ChangeWidth((*node)->parent, 0 - strlen((*node)->data));
    ChangeSize((*node)->parent, -1);

    if ( (*node)->left == NULL ){
        if ( (*node)->right )
            (*node)->right->parent = *node;
        *node = (*node)->right;
        return;
    }
    else if ( (*node)->right == NULL ){
        if ( (*node)->left )
            (*node)->left->parent = *node;
        *node = (*node)->left;
        return;
    }

    ChangeWidth((*node)->left->parent, 0 - (strlen((*node)->left->data) + (*node)->left->width));
    ChangeSize((*node)->parent, -(1 + (*node)->size));


    newNode = SearchPlace((*node)->left->key, &(*node)->right);
    if ( !newNode )
        return;

    buf = (*newNode)->parent;
    free((*newNode));
    *newNode = (*node)->left;
    (*newNode)->parent = buf;

    ChangeWidth((*newNode)->parent, strlen((*newNode)->data));
    ChangeSize((*newNode)->parent, 1);

    (*node)->right->parent = (*node)->parent;
    buf = (*node)->right;
    free(*node);
    *node = buf;
}
//
//int main(void){
//    char c = getchar();
//    int number;
//
//    while ( c != EOF ){
//        scanf("%d", &number);
//        switch ( c ) {
//        case 'a':
//            AddNode(number, "hello");
//            break;
//        case 'r':
//            DeleteNode(number);
//            break;
//        case 'f':
//            if ( *FindNode(number) )
//                printf("yes\n");
//            else
//                printf("no\n");
//            break;
//        default:
//            return 0;
//        }
//
//        c = getchar();
//        if ( c == '\r' )
//            c = getchar();
//        if ( c == '\n' )
//            c = getchar();
//    }
//
//    return 0;
//}
