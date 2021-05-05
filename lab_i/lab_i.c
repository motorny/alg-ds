#include <stdio.h>
#include <stdlib.h>
#include "lab_i.h"

#define T 5
#define SPCS 4
#define MAX_LENGTH 100

#pragma warning (disable: 4996)

tree_t* InitTree() {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node) {
        node->leaf = true;
        node->key_num = 0;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        for (int i = 0; i < 2 * T + 1; i++) {
            node->child[i] = NULL;
        }
    }
    tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
    if (tree) {
        tree->root = node;
    }
    return tree;
}

void DestroyNode(node_t* node) {
    if (!node->leaf) {
        for (int i = 0; i < node->key_num + 1; i++) {
            DestroyNode(node->child[i]);
        }
    }
    free(node);
}

void DestroyTree(tree_t* tree) {
    if (tree) {
        DestroyNode(tree->root);
        free(tree);
    }
}

int WhatHeight(tree_t* tree) {
    node_t* node = tree->root;
    int height = 0;
    while (node != NULL && !node->leaf) {
        node = node->child[0];
        ++height;
    }
    return height;
}

int FindMinKey(node_t* node) {
    for (int i = 0; i < 2 * T; ++i) {
        if (node->child[i]) {
            return FindMinKey(node->child[i]);
        }
    }
    return node->key[0];
}

node_t* FindNode(node_t* node, int key) {
    int i = 0;
    if (node->leaf)
        return node;
    while (i < node->key_num && key >= node->key[i])
        ++i;
    return FindNode(node->child[i], key);
}

bool FindTree(const tree_t* tree, int key) {
    node_t* leaf;
    int i;
    if (!tree) {
        return false;
    }
    leaf = FindNode(tree->root, key);
    for (i = 0; i < leaf->key_num; ++i)
        if (leaf->key[i] == key)
            return true;
    return false;
}

void Update(node_t* node, int key) {
    node_t* prev = node->parent;
    int position = 0;
    while (prev) {
        while ((position < prev->key_num) && (prev->key[position] < key))
            ++position;
        if (position < prev->key_num) {
            if (prev->key[position] != FindMinKey(prev->child[position + 1])) {
                prev->key[position] = FindMinKey(prev->child[position + 1]);
            }
        }
        prev = prev->parent;
    }
}

bool Split(tree_t* tree, node_t* node) {
    node_t* newNode = malloc(sizeof(node_t));
    node_t* newRoot;
    node_t* prev;
    int middle;
    int i, j;
    if (!newNode)
        return false;
    for (int i = 0; i <= 2 * T; ++i) {
        newNode->child[i] = NULL;
    }
    newNode->right = node->right;
    if (node->right) {
        node->right->left = newNode;
    }
    node->right = newNode;
    newNode->left = node;
    middle = node->key[T];
    newNode->key_num = T - 1;
    node->key_num = T;
    for (i = 0; i < T - 1; ++i) {
        newNode->key[i] = node->key[T + i + 1];
        newNode->child[i] = node->child[T + i + 1];
        node->child[i + T + 1] = NULL;
    }
    newNode->child[newNode->key_num] = node->child[T * 2];
    node->child[T * 2] = NULL;
    if (node->leaf) {
        newNode->leaf = true;
        ++newNode->key_num;
        for (i = newNode->key_num - 1; i > 0; --i)
            newNode->key[i] = newNode->key[i - 1];
        newNode->key[0] = node->key[T];
    }

    if (node == tree->root) {
        newRoot = malloc(sizeof(node_t));
        if (!newRoot) {
            free(newNode);
            return false;
        }
        for (i = 0; i <= 2 * T; ++i) {
            if (newNode->child[i]) {
                newNode->child[i]->parent = newNode;
            }
            if (node->child[i]) {
                node->child[i]->parent = node;
            }
        }
        tree->root = newRoot;
        tree->root->key[0] = middle;
        tree->root->child[0] = node;
        tree->root->child[1] = newNode;
        tree->root->key_num = 1;
        tree->root->parent = NULL;
        tree->root->left = NULL;
        tree->root->right = NULL;
        tree->root->leaf = false;
        node->parent = tree->root;
        newNode->parent = tree->root;
        for (i = 2; i <= 2 * T; ++i) {
            tree->root->child[i] = NULL;
        }
    }
    else {
        newNode->parent = node->parent;
        prev = node->parent;
        i = 0;
        while (i < prev->key_num&& middle >= prev->key[i])
            ++i;

        for (j = prev->key_num; j > i; --j)
            prev->key[j] = prev->key[j - 1];

        for (j = prev->key_num + 1; j > i + 1; --j)
            prev->child[j] = prev->child[j - 1];

        for (j = 0; j < 2 * T; ++j)
            if (newNode->child[j])
                newNode->child[j]->parent = newNode;
        prev->key[i] = middle;
        prev->child[i + 1] = newNode;
        ++prev->key_num;

        if (prev->key_num == 2 * T)
            Split(tree, prev);
    }
    return true;
}

bool InsertTree(tree_t* tree, const int key) {
    node_t* node;
    int i = 0, j = 0;
    if (!tree)
        return false;
    node = FindNode(tree->root, key);
    while (i < node->key_num&& key >= node->key[i]) {
        if (key == node->key[i])
            return false;
        ++i;
    }
    for (j = node->key_num; j > i; --j) {
        node->key[j] = node->key[j - 1];
    }
    node->key[i] = key;
    ++node->key_num;
    return node->key_num == 2 * T ? Split(tree, node) : true;
}

tree_t* Merge(tree_t* tree1, tree_t* tree2) {
    int h1 = WhatHeight(tree1);
    int h2 = WhatHeight(tree2);
    int temp;
    int i;
    int flag = 0;
    node_t* n1 = h1 >= h2 ? tree1->root : tree2->root;
    node_t* n2 = h1 < h2 ? tree1->root : tree2->root;
    tree_t* tmp;
    if (h2 > h1) {
        flag = 1;
        tmp = tree1;
        tree1 = tree2;
        tree2 = tmp;

        temp = h1;
        h1 = h2;
        h2 = temp;
    }
    while (h1 > h2 + 1) {
        n1 = flag ? n1->child[0] : n1->child[n1->key_num - 1];
        --h1;
    }
    if (!flag)
        n1->child[n1->key_num] = n2;
    else {
        n1->child[n1->key_num + 1] = n1->child[n1->key_num];
        for (i = n1->key_num; i > 0; --i) {
            n1->key[i] = n1->key[i - 1];
            n1->child[i] = n1->child[i - 1];
        }
        n1->child[0] = n2;
    }
    ++n1->key_num;
    if (n1->key_num == 2 * T)
        Split(tree1, n1);
    return tree1;
}

void SplitTree(tree_t* tree, int key, tree_t* tree1, tree_t* tree2) {
    tree_t* left[MAX_LENGTH];
    tree_t* right[MAX_LENGTH];
    int left1 = 0;
    int right1 = 0;
    node_t* node = tree->root;
    int i, j;
    while (node && !node->leaf) {
        i = 0;
        while (node->key[i] < key) {
            left[left1++] = InitTree();
            left[left1 - 1]->root = node->child[i];
            ++i;
        }
        for (j = i + 1; i <= node->key_num; ++j) {
            right[right1++] = InitTree();
            right[right1 - 1]->root = node->child[i];
        }
        node = node->child[i];
    }
    tree1 = InitTree();
    tree2 = InitTree();
    if (!node)
        return;
    i = 0;
    left[left1++] = InitTree();
    while (node->key[i] < key) {
        InsertTree(left[left1 - 1], node->key[i]);
        ++i;
    }
    right[right1++] = InitTree();
    while (i < node->key_num) {
        InsertTree(right[right1 - 1], node->key[i]);
        ++i;
    }
    for (i = 0; i < left1; ++i) {
        tree1 = Merge(tree1, left[i]);
    }
    for (i = 0; i < right1; ++i) {
        tree2 = Merge(tree2, right[i]);
    }
}

void DeleteInNode(tree_t* tree, node_t* node, int key) {
    int position = 0, i = 0;
    node_t* right, * left;
    while (position < node->key_num && node->key[position] < key)
        ++position;
    for (i = position; i < node->key_num; ++i)
        node->key[i] = node->key[i + 1];
    for (i = position + 1; i <= node->key_num; ++i)
        node->child[i] = node->child[i + 1];
    for (i = node->key_num + 1; i <= 2 * T; ++i)
        node->child[i] = NULL;
    --node->key_num;
    if (node == tree->root) {
        for (i = 0; i <= 2 * T; ++i) {
            if (node->child[i]) {
                if (node->child[i]->key_num == 0) {
                    node->child[i] = NULL;
                }
            }
        }
        if (tree->root->key_num == 0 && node->child[0]) {
            tree->root = tree->root->child[0];
        }
        return;
    }
    if (node->key_num >= T / 2 - 1) {
        Update(node, key);
        return;
    }
    right = node->right;
    left = node->left;
    if (left && left->key_num > T - 1 && left->parent == node->parent) {
        --left->key_num;
        ++node->key_num;

        for (i = 1; i < node->key_num - 1; ++i) {
            node->key[i] = node->key[i - 1];
            node->child[i] = node->child[i - 1];
        }
        node->child[node->key_num] = node->child[node->key_num - 1];
        node->key[0] = left->key[left->key_num];
        node->child[0] = left->child[left->key_num + 1];
        left->child[left->key_num + 1] = NULL;
        if (node->child[0])
            node->child[0]->parent = node;
        Update(node, key);
    }
    else if (right && right->key_num > T - 1 && right->parent == node->parent) {
        --right->key_num;
        ++node->key_num;

        node->key[node->key_num - 1] = right->key[0];
        node->child[node->key_num] = right->child[0];
        if (node->child[node->key_num])
            node->child[node->key_num]->parent = node;
        for (i = 0; i < right->key_num - 1; ++i) {
            right->key[i] = right->key[i + 1];
            right->child[i] = right->child[i + 1];
        }
        right->child[i] = right->child[i + 1];
        for (i = 0; i < 2 * T; ++i) {
            if (right->child[i] == right->child[i + 1] && right->child[i] != NULL) {
                right->child[i + 1] = NULL;
                break;
            }
        }
        Update(node, key);
    }
    else {
        if (right && right->parent == node->parent) {
            for (i = 0; i < right->key_num; ++i) {
                node->key[node->key_num] = right->key[i];
                node->child[node->key_num + 1] = right->child[i];
                if (right->child[i])
                    right->child[i]->parent = node;
                ++node->key_num;
            }
            node->child[node->key_num + 1] = right->child[right->key_num];
            if (right->child[right->key_num])
                right->child[right->key_num]->parent = node;
            if (right->right)
                right->right->left = node;
            node->right = right->right;
            DeleteInNode(tree, node->parent, FindMinKey(right));
            Update(node, key);
        }
        else {
            for (i = 0; i < node->key_num; ++i) {
                left->key[left->key_num] = node->key[i];
                left->child[left->key_num + 1] = node->child[i];
                if (node->child[i])
                    node->child[i]->parent = left;
                left->key_num++;
            }
            left->child[left->key_num + 1] = node->child[node->key_num];
            if (node->child[node->key_num]) {
                node->child[node->key_num]->parent = left;
            }
            left->right = node->right;
            if (node->right)
                node->right->left = left;
            DeleteInNode(tree, left->parent, FindMinKey(node));
            Update(left, key);
        }
    }
}

bool DeleteTree(tree_t* tree, const int key) {
    node_t* leaf = FindNode(tree->root, key);
    int i;
    if (!leaf)
        return false;
    for (i = 0; i < leaf->key_num; ++i)
        if (leaf->key[i] == key) {
            DeleteInNode(tree, leaf, key);
            return true;
        }
    return false;
}

void PrintTree(node_t* tree, char* dr, int level) {
    if (tree) {
        for (int i = 0; i < tree->key_num; i++) {
            if (strcmp("child", dr) != 1)
                printf("level %d key = %d\n", level, tree->key[i]);
            else
                printf("level %d child = %d\n", level, tree->key[i]);
        }
        for (int i = 0; i < 2 * T; i++) {
            if (tree->child[i]) {
                printf("child %d\n", i);
                PrintTree(tree->child[i], "child", level + 1);
            }
        }
    }
}

void WhatToDo() {
    int key;
    char c = ' ';
    tree_t* tree = InitTree();
    while (true) {
        c = getchar();
        if (c == EOF) {
            break;
        }
        scanf("%d", &key);
        getchar();
        switch (c) {
        case 'a':
            InsertTree(tree, key);
            break;
        case 'f':
            if (FindTree(tree, key)) {
                printf("yes\n");
            }
            else {
                printf("no\n");
            }
            break;
        case 'r':
            DeleteTree(tree, key);
            break;
        }
    }
    DestroyTree(tree);
}