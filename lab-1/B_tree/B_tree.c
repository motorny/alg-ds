#include "pch.h"
#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

#pragma warning (disable:4996)

node_t* root = NULL;

node_t* InitNewNode() {
    node_t* newnode = (node_t*)malloc(sizeof(node_t));
    if (!newnode)
        return NULL;
    newnode->n = 0;
    newnode->Isleaf = TRUE;

    for (int i = 0; i < (2 * m); i++)
        newnode->kids[i] = NULL;

    return newnode;
}

flag_t FindKey(node_t* tree, int key) {
    int i = 0;
    if (!tree)
        return FALSE;
    while (i < tree->n && key > tree->key[i])
        i++;
    if (i < tree->n && key == tree->key[i])
        return TRUE;
    else if (tree->Isleaf)
        return FALSE;

    return FindKey(tree->kids[i], key);
}

int Split(node_t* node, int index) {
    if (index > 2 * m - 1)
        return NOT_FOUND;
    else if (node == NULL)
        return ERR;

    node_t* helpnode = (node_t*)malloc(sizeof(helpnode));
    if (!helpnode)
        return ERR;
    node_t* child = node->kids[index];

    helpnode->Isleaf = child->Isleaf;
    helpnode->n = m - 1;
    memcpy(&helpnode->key[0], &child->key[m], (m - 1) * sizeof(int));

    if (child->Isleaf == FALSE)
        memcpy(&helpnode->kids[0], &child->kids[m], (m) * sizeof(node_t*));
    child->n = m - 1;

    if (node->n > index)
        memmove(&node->kids[index + 2], &node->kids[index + 1], (node->n - index) * sizeof(node_t*));
    node->kids[index + 1] = helpnode;

    if (node->n > index)
        memmove(&node->key[index + 1], &node->key[index], (node->n - index) * sizeof(int));
    node->key[index] = child->key[m - 1];
    node->n++;

    return OK;
}


//inserts the key "k" into the node, which should be empty when called
void Nonfull_Insert(node_t* tree, int k) {
    int i = (tree->n) - 1;

    if (tree->Isleaf) {
        while (i >= 0 && k < tree->key[i]) {
            tree->key[i + 1] = tree->key[i];
            i--;
        }
        tree->key[i + 1] = k;
        tree->n++;
    }

    else {
        while (i >= 0 && k < tree->key[i])
            i = i - 1;
        i = i + 1;

        if (tree->kids[i]->n == 2 * m - 1) {
            Split(tree, i);
            if (k > tree->key[i])
                i = i + 1;
        }
        Nonfull_Insert(tree->kids[i], k);
    }
}

node_t* Insert(node_t* root, int key) {
    node_t* addnode = root, * helpnode = NULL;

    if (FindKey(root, key)) //the key already exists
        return root;

    if (!root) {
        root = InitNewNode();
        root->key[0] = key;
        root->n++;
        return;
    }

    if (addnode->n == 2 * m - 1) {
        helpnode = InitNewNode();
        root = helpnode;
        helpnode->Isleaf = FALSE;
        helpnode->n = 0;
        helpnode->kids[0] = addnode;
        Split(helpnode, 0);
        Nonfull_Insert(helpnode, key);
    }
    else
        Nonfull_Insert(addnode, key);
    return root;
}


//find the place to delete
int Positiontodelete(int key, int* keys, int n) {
    int position = 0;
    while (position < n && key > keys[position])
        position++;
    return position;
}



int Remove(node_t* tree, int key) {
    node_t** kids, * left, * right, * node_1, * node_2;
    int place, i, k, n, min_elems, n_2, cond;
    int* keys;

    if (!tree)
        return NOT_FOUND;

    n = tree->n;
    keys = tree->key;
    kids = tree->kids;
    min_elems = (m - 1) / 2;

    place = Positiontodelete(key, keys, n);
    // kids is a leaf
    if (kids[0] == NULL) {
        if (place == n || key < keys[place])
            return NOT_FOUND;

        for (i = place + 1; i < n; i++) {
            keys[i - 1] = keys[i];
            kids[i] = kids[i + 1];
        }
        tree->n--;

        //if tree is root, there can be 1 key
        if (tree == root)
            min_elems = 1;

        if (tree->n >= min_elems)
            return OK;
        else
            return ERR;
    }

    //kids is not a leaf
    if (place < n && key == keys[place]) {
        node_1 = kids[place];
        while (TRUE) {
            n_2 = node_1->n;
            node_2 = node_1->kids[n_2];
            if (node_2 == NULL)
                break;
            node_1 = node_2;
        }
        keys[place] = node_1->key[n_2 - 1];
        node_1->key[n_2 - 1] = key;
    }
    cond = Remove(kids[place], key);
    if (cond != ERR)
        return cond;

    //if not enough keys in node, add
    if (place > 0 && kids[place - 1]->n > min_elems) {
        k = place - 1;
        left = kids[k];
        right = kids[place];
        right->kids[right->n + 1] = right->kids[right->n];
        for (i = right->n; i > 0; i--) {
            right->key[i] = right->key[i - 1];
            right->kids[i] = right->kids[i - 1];
        }
        right->n++;
        right->key[0] = keys[k];
        right->kids[0] = left->kids[left->n];
        keys[k] = left->key[--left->n];
        return OK;
    }

    if (place < n && kids[place + 1]->n > min_elems) {
        k = place;
        left = kids[k];
        right = kids[k + 1];
        left->key[left->n] = keys[k];
        left->kids[left->n + 1] = right->kids[0];
        keys[k] = right->key[0];
        left->n++;
        right->n--;
        for (i = 0; i < right->n; i++) {
            right->key[i] = right->key[i + 1];
            right->kids[i] = right->kids[i + 1];
        }
        right->kids[right->n] = right->kids[right->n + 1];
        return OK;
    }

    if (place == n)
        k = place - 1;
    else
        k = place;

    left = kids[k];
    right = kids[k + 1];

    //merging
    left->key[left->n] = keys[k];
    left->kids[left->n + 1] = right->kids[0];
    for (i = 0; i < right->n; i++) {
        left->key[left->n + 1 + i] = right->key[i];
        left->kids[left->n + 2 + i] = right->kids[i + 1];
    }
    left->n = left->n + right->n + 1;

    free(right);
    for (i = place + 1; i < n; i++) {
        keys[i - 1] = keys[i];
        kids[i] = kids[i + 1];
    }
    if (tree == root)
        min_elems = 1;
    tree->n--;
    if (tree->n >= min_elems)
        return OK;
    else
        return ERR;
}

void DeleteKey(int key) {
    node_t* node;
    int cond = Remove(root, key);
    if (cond == ERR) {
        node = root;
        root = root->kids[0];
        free(node);
    }
}

void Print(tree_t* tree, int h) {
    if (!tree)
        return;
    int i, j;
    for (i = 0; i <= tree->root->n - 1; i++) {
        Print(tree->root->kids[i], h + 1);
        for (j = 0; j <= h; j++)
            printf("   ");
        printf("%d\n", tree->root->key[i]);
    }
    Print(tree->root->kids[i], h + 1);
}