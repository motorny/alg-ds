#include "pch.h"
#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

#define TRUE 1

typedef enum {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
}way_t;

typedef struct node_t {
    int key;
    struct node_t* left;
    struct node_t* parent;
    struct node_t* right;
} node_t;

node_t* futher(node_t* tree) {
    return tree->parent;
}

node_t* grandfuther(node_t* tree) {
    return futher(futher(tree));
}

node_t* Rotateleft(node_t* tree) {
    node_t* parent = NULL, * middle = NULL, * left = NULL, * right = NULL;
    left = tree;
    parent = left->parent;
    right = left->right;
    if (right == NULL)
        return;
    middle = right->left;
    right->left = left;
    left->right = middle;
    if (middle)
        middle->parent = left;
    right->parent = parent;
    if (parent)
    {
        if (parent->left == left)
            parent->left = right;
        else
            parent->right = right;
    }
    left->parent = right;
    if (!parent)
        tree = tree->parent;
    return tree;
}

node_t* Rotateright(node_t* tree) {
    node_t* parent = NULL, * middle = NULL, * left = NULL, * right = NULL;
    right = tree;
    parent = right->parent;
    left = right->left;
    if (left == NULL)
        return;
    middle = left->right;
    left->right = right;
    right->left = middle;
    if (middle)
        middle->parent = right;
    left->parent = parent;
    if (parent)
    {
        if (parent->left == right)
            parent->left = left;
        else
            parent->right = left;
    }
    right->parent = left;
    if (!parent)
        tree = tree->parent;
    return tree;
}



//do rotations to get a finded node in root of tree 
node_t* splay(node_t* tree) {
    node_t* help;
    while (futher(tree) != NULL) {
        if (tree == tree->parent->left) {
            if (grandfuther(tree) == NULL)
                tree = Rotateright(futher(tree));
            else if (tree->parent == tree->parent->parent->left) {
                help = tree->parent;
                tree = Rotateright(tree->parent->parent);
                tree = Rotateright(help);
            }
            else {
                help = tree->parent;
                tree = Rotateright(tree->parent);
                tree = Rotateleft(help);
            }
        }
        else {
            if (grandfuther(tree) == NULL)
                tree = Rotateleft(tree->parent);
            else if (tree->parent == tree->parent->parent->right) {
                help = tree->parent;
                tree = Rotateleft(tree->parent->parent);
                tree = Rotateleft(help);
            }
            else
            {
                help = tree->parent;
                tree = Rotateleft(tree->parent);
                tree = Rotateright(help);
            }
        }
    }
    return tree;
}

node_t* Findnode(node_t* tree, int num) {
    node_t* temp = tree;
    while (temp) {

        if (num < temp->key)
            temp = temp->left;

        else if (num > temp->key)
            temp = temp->right;

        //node is found
        else {
            return temp;
        }
    }
    return NULL;
}

void Add(node_t** tree, int num) {
    node_t* temp = (*tree), * newnode, * ptr = (*tree);

    newnode = (node_t*)malloc(sizeof(node_t));
    if (!newnode)
        return;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    newnode->key = num;

    if (!(*tree)) {
        (*tree) = newnode;
        return;
    }

    while (ptr) {
        if (num < ptr->key) {
            if (ptr->left)
                ptr = ptr->left;
            else
                break;
        }

        else if (num > ptr->key) {
            if (ptr->right)
                ptr = ptr->right;
            else
                break;
        }

        else {//such node exists
            free(newnode);
            return;
        }
    }

    //put new node
    if (num < ptr->key)
        ptr->left = newnode;
    else
        ptr->right = newnode;

    newnode->parent = ptr;
}

void Delete(node_t** tree, node_t* vertex) {
    if (!vertex)
        return;
    int temp;
    node_t* max = vertex, * parent, * child; //go to left child of vertex and then to right 
    way_t parentway;

    //no childs, free the element
    if (vertex->left == NULL && vertex->right == NULL) {
        if ((vertex == (*tree))) {
            free(vertex);
            (*tree) = NULL;
            return;
        }

        parent = vertex->parent;
        parentway = parent->left == vertex ? LEFT : RIGHT;

        if (parentway == LEFT)
            parent->left = NULL;
        else
            parent->right = NULL;

        free(vertex);
        return;
    }


    //has one child, put child instead of itself
    if ((vertex->left != NULL && vertex->right == NULL) || (vertex->left == NULL && vertex->right != NULL)) {

        if (vertex == (*tree)) { //no parent
            if (vertex->left)
                (*tree) = vertex->left;
            else
                (*tree) = vertex->right;
            (*tree)->parent = NULL;
            free(vertex);
            return;
        }

        parent = vertex->parent;
        parentway = parent->left == vertex ? LEFT : RIGHT;

        if (vertex->left) //only left child
            child = vertex->left;
        else //only right child
            child = vertex->right;

        child->parent = vertex->parent;

        if (parentway == LEFT)
            parent->left = child;
        else
            parent->right = child;

        free(vertex);
        return;
    }

    //node has two childs
    max = max->right;

    while (max->left)
        max = max->left;

    temp = max->key;
    max->key = vertex->key;
    vertex->key = temp;

    //no need to delete max

    //max can have one child on the right
    if (max->right) {
        child = max->right;
        parent = max->parent;
        parentway = parent->left == max ? LEFT : RIGHT;

        if (parentway == LEFT)
            parent->left = child;
        else
            parent->right = child;

        child->parent = parent;
    }

    //max has no childs
    else {
        parent = max->parent;
        parentway = parent->left == max ? LEFT : RIGHT;

        if (parentway == LEFT)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    free(max);
    return;
}

//int main(void) {
//    char comand;
//    int key = 0;
//    node_t* tree = NULL;
//
//    while (TRUE) {
//        comand = fgetc(stdin);
//
//        if (comand == EOF || comand == '\n')
//            break;
//
//        scanf("%i", &key);
//
//        //comands
//        if (comand == 'a') //append
//            Add(&tree, key);
//
//        //adress as bool type. Is adress not NULL -> TRUE. Otherwise, FALSE
//        else if (comand == 'f') { //find
//            if (Findnode(tree, key))
//            {
//                tree = splay(Findnode(tree, key));
//                printf("yes\n");
//            }
//            else
//                printf("no\n");
//        }
//
//        else if (comand == 'r')//remove
//            Delete(&tree, Findnode(tree, key));
//
//        key = 0;
//        comand = fgetc(stdin); //get '\n' from stdin
//    }
//    return 0;
//}