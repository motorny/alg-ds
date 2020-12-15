#include "pch.h"
#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

start_t StartNode = { NULL };

int WhatWidth(int key) {
    int width = 0;
    if (key < 0) {
        width++;
        key = abs(key);
    }
    while (key) {
        key /= 10;
        width++;
    }
    return width;
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

node_t** PlaceToAdd(int key, node_t** start)
{
    node_t** current = start;
    while (*current)
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

int Addnode(int key, int data)
{
    int width = WhatWidth(data);
    node_t** current = PlaceToAdd(key, &StartNode.node);
    if (!current)
        return 1;

    (*current)->data = data;
    (*current)->key = key;
    (*current)->width = 0;
    (*current)->left = NULL;
    (*current)->right = NULL;
    UpdateWidth((*current)->parent, width);
    return 0;
}

node_t** FindNode(int key)
{
    node_t** current = &StartNode.node;
    while ((*current))
    {
        if ((*current)->key == key)
            break;
        else if (key >= (*current)->key)
            current = &(*current)->right;
        else
            current = &(*current)->left;
    }
    return current;
}

void DeleteNode(int key)
{
    node_t** node = FindNode(key), ** helpnode = NULL, * add;

    if (!(*node))
        return;
    if ((*node)->parent && (*node)->left) {
        UpdateWidth((*node)->left->parent, - (WhatWidth((*node)->left->data)));
        UpdateWidth((*node)->parent, - (WhatWidth((*node)->data)));
    }
    if ((*node)->left == NULL)
    {
        *node = (*node)->right;
        return;
    }
    else if ((*node)->right == NULL)
    {
        *node = (*node)->left;
        return;
    }

    helpnode = PlaceToAdd((*node)->left->key, &(*node)->right);
    if (!helpnode)
        return;

    add = (*helpnode)->parent;
    free((*helpnode));
    *helpnode = (*node)->left;
    (*helpnode)->parent = add;

    UpdateWidth((*helpnode)->parent, WhatWidth((*helpnode)->data));
    (*node)->right->parent = (*node)->parent;
    add = (*node)->right;
    free(*node);
    *node = add;
}

void Printree(node_t* tree, int n) {
    if (!tree)
        return;
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

void DestroyTree(node_t* tree) {
    if (tree) {
        DestroyTree(tree->left);
        DestroyTree(tree->right);
        free(tree);
        StartNode.node = NULL;
    }
    return;
}

int main()
{
    node_t* root = NULL;
    Addnode(1, 5);
    Addnode(3, 19);
    Addnode(6, 100);
    Addnode(2, 1);
    Addnode(5, 8);
    Addnode(4, 9);
    Printree(StartNode.node, 1);
    DestroyTree(StartNode.node);
    return 0;
}