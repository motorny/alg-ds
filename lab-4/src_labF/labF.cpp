//
// Created by ikuzin on 16.12.2020.
//

#include <cstdio>
#include <cstdlib>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node_t;


void printTree(Node_t *node) {
    if (node == NULL)
        return;
    printTree(node->left);
    printf("---------");
    printf("\n%d", node->key);
    printTree(node->right);
}

int kthSmallest(Node_t *pivot, int k) {
    if (pivot == NULL)
        return k;
    k = kthSmallest(pivot->left, k);
    k--;
    if (k == 0) {

        printf("%d", pivot->key);
        if (pivot->key % 2 == 0)
            printTree(pivot);
    }
    k = kthSmallest(pivot->right, k);
    return k;
}

Node_t *Add(Node_t *node, int key) {
    if (node == NULL) {
        node = (Node_t *) malloc(sizeof(Node_t));
        if (node == NULL)
            return NULL;
        node->key = key;
        node->left = node->right = NULL;
    } else {
        if (key < node->key)
            node->left = Add(node->left, key);
        else {
            if (key > node->key)
                node->right = Add(node->right, key);
        }
    }
    return node;
}

Node_t *Find(Node_t *node, int key) {
    Node_t *temp = NULL;

    if (node == NULL)
        return NULL;

    if (node->key == key)
        return node;
    else {
        if (key < node->key)
            temp = Find(node->left, key);
        else
            temp = Find(node->right, key);
    }
    return temp;
}

Node_t *MaxNodeByKey(Node_t *node) {
    while (node->right != NULL)
        node = node->right;
    return node;
}

void Del(Node_t **node, int key) {
    if ((*node) == NULL)
        return;

    Node_t *max = NULL;

    if (key < (*node)->key)
        Del(&((*node)->left), key);
    else {
        if (key > (*node)->key)
            Del(&((*node)->right), key);
        else {
            if ((*node)->right == NULL)
                (*node) = (*node)->left;
            else {
                if ((*node)->left == NULL)
                    (*node) = (*node)->right;
                else {
                    max = MaxNodeByKey((*node)->left);
                    (*node)->key = max->key;
                    Del(&((*node)->left), max->key);
                }
            }
        }
    }
}

int ReadAction(FILE *fp, int *key) {
    char c, n;
    int check;
    check = fscanf(fp, "%c", &c);
    if (check == -1)
        return 0;

    fscanf(fp, " %d", key);
    fscanf(fp, "%c", &n);

    switch (c) {
        case 'a':
            return 1;
        case 'r':
            return 2;
        case 'f':
            return 3;
        case 's':
            return 4;
        default:
            return 0;
    }
}

void DestroyTree(Node_t *t) {
    if (t == NULL)
        return;
    DestroyTree(t->left);
    DestroyTree(t->right);
    free(t);
}

int labF() {
    int mode, num = 0;
    Node_t *tree = NULL;

    mode = ReadAction(stdin, &num);
    if (mode == 0)
        return -1;

    do {
        switch (mode) {
            case 1:
                tree = Add(tree, num);
                break;
            case 2:
                Del(&tree, num);
                break;
            case 3:
                if (Find(tree, num) != NULL)
                    printf("yes\n");
                else
                    printf("no\n");
                break;
            case 4:
                kthSmallest(tree, num);
            default:
                break;
        }
        mode = ReadAction(stdin, &num);

    } while (mode != 0);

    return 0;
}
