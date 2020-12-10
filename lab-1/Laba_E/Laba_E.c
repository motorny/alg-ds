#include "pch.h"
#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

#pragma warning(disable:4996)

#define FAIL 1

node_t* startnode = NULL;

int Getwidth(int key) {
    int result = 0;
    if (key < 0) {
        result = result + 1;
        key = abs(key);
    }
    while (key) {
        key = key / 10;
        result++;
    }
    return result;
}

void UpdateWidth(node_t* start, int value)
{
    node_t* current = start;
    while (current)
    {
        current->width += value;
        current = current->parent;
    }
}

node_t** FindPlaceAdd(int key, node_t** start)
{
    node_t** current = start;
    while ((*current))
    {
        if (key < (*current)->key)
        {
            if ((*current)->left == NULL)
            {
                if (!((*current)->left = (node_t*)malloc(sizeof(node_t))))
                    return NULL;

                (*current)->left->parent = *current;
                current = &(*current)->left;
                break;
            }
            else
                current = &(*current)->left;
        }
        else if ((*current)->key == key)
            return 0;
        else
        {
            if ((*current)->right == NULL)
            {
                if (!((*current)->right = (node_t*)malloc(sizeof(node_t))))
                    return NULL;

                (*current)->right->parent = *current;
                current = &(*current)->right;
                break;
            }
            else
                current = &(*current)->right;
        }
    }

    if (!(*current))
        if (*current = (node_t*)malloc(sizeof(node_t)))
            (*current)->parent = NULL;
        else
            return NULL;
    return current;
}

node_t* Addnode(int key, int data)
{
    int width = Getwidth(data);
    node_t** current = FindPlaceAdd(key, &startnode);


    if (!current)
        return FAIL;

    (*current)->key = key;
    (*current)->left = NULL;
    (*current)->right = NULL;
    (*current)->width = 0;
    (*current)->data = data;
    UpdateWidth((*current)->parent, width);
    return startnode;
}

node_t** Findnode(int key)
{
    node_t** current = &startnode;
    while ((*current))
    {
        if ((*current)->key == key)
            break;
        else if (key < (*current)->key)
            current = &(*current)->left;
        else
            current = &(*current)->right;
    }
    return current;
}

void Deletenode(int key)
{
    node_t** current = Findnode(key), ** helpnode = NULL, * add;

    if (!(*current))
        return;
    if ((*current)->left && (*current)->parent) {
        UpdateWidth((*current)->left->parent, 0 - Getwidth((*current)->left->data));
        UpdateWidth((*current)->parent, 0 - Getwidth((*current)->data));
    }
    if ((*current)->left == NULL)
    {
        *current = (*current)->right;
        return;
    }
    else if ((*current)->right == NULL)
    {
        *current = (*current)->left;
        return;
    }

    helpnode = FindPlaceAdd((*current)->left->key, &(*current)->right);
    if (!helpnode)
        return;

    add = (*helpnode)->parent;
    free((*helpnode));
    *helpnode = (*current)->left;
    (*helpnode)->parent = add;

    UpdateWidth((*helpnode)->parent, Getwidth((*helpnode)->data));
    (*current)->right->parent = (*current)->parent;
    add = (*current)->right;
    free(*current);
    *current = add;
}

void Printree(node_t* tree, int n) {
    if (!tree)
        return;
    else {
        int i = 0;
        Printree(tree->left, n + tree->key);
        for (i = 0; i < n; i++)
            printf("  ");
        printf("%d\n", tree->key);
        for (i = 0; i < n; i++)
            printf("  ");
        printf("%d\n", tree->width);
        Printree(tree->right, n + tree->key);

    }
}

void DestroyTree(node_t* tree) {
    if (!tree)
        return;
    else {
        DestroyTree(tree->left);
        DestroyTree(tree->right);
        free(tree);
        startnode = NULL;
    }
}

int main()
{
    int offset = 1;
    Addnode(2, 5);
    Addnode(3, 10);
    Addnode(4, 15);
    Addnode(1, 1);
    Printree(startnode, offset);
    DestroyTree(startnode);
    return 0;
}