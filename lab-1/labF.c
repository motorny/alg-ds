#include "labF.h"

int AtT(Node** tree, Node* father, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
        return FALSE;

    if (*tree == NULL) {
        newNode->numberOfNodes = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->key = key;
        newNode->father = father;
        (*tree) = newNode;
    }
    else {
        if (key < (*tree)->key) {
            if (AtT(&((*tree)->left), *tree, key))
                (*tree)->numberOfNodes += 1;
        }
        else if (key > (*tree)->key) {
            if (AtT(&((*tree)->right), *tree, key))
                (*tree)->numberOfNodes += 1;
        }
        else
            return FALSE;
    }
    return TRUE;
}

static int Size(Node* node) {
    if (node == NULL || node->left == NULL)
        return 0;
    return node->left->numberOfNodes;
}

static Node* FNiT(Node* tree, int key) {
    if (tree == NULL)
        return NULL;
    if (tree->key == key)
        return tree;
    else if (tree->key < key)
        return FNiT(tree->right, key);
    else if (tree->key > key)
        return FNiT(tree->left, key);
}

// return index of node from 1 to nodes count
int Number(Node* tree, Node* t, char isMain) {
    Node* f;
    int r = Size(t);

    while (t->father != NULL) {
        f = t->father;
        if (t == f->right) {
            r += Number(tree, f, 0) + 1;
            break;
        }
        t = t->father;
    }

    if (isMain)
        r++;

    return r;
}

// return node with index from 1 to nodes count
static Node* GetKLow(Node* tree, int k) {
    int r;

    if (tree->left) {
        r = tree->left->numberOfNodes + 1;
    }
    else
        r = 1;

    if (r != k) {
        if (k < r)
            tree = GetKLow(tree->left, k);
        else
            tree = GetKLow(tree->right, k - r);
    }

    return tree;
}

Node* FKLT(Node* tree, int key, int k) {
    int c;

    Node* currentNode = FNiT(tree, key);
    if (currentNode == NULL)
        return NULL;

    c = Number(tree, currentNode, 1);
    if (c - k <= 0 || c - k > tree->numberOfNodes)
        return NULL;

    return GetKLow(tree, c - k);
}

static void DFT(Node** tree) {
    Node* elemToDel, ** tmp;

    elemToDel = *tree;

    if ((*tree)->left == NULL && (*tree)->right == NULL)
        (*tree) = NULL;
    else if ((*tree)->left == NULL)
        (*tree) = (*tree)->right;
    else if ((*tree)->right == NULL)
        (*tree) = (*tree)->left;
    else {
        tmp = &(*tree)->left;
        while ((*tmp)->right != NULL)
            tmp = &(*tmp)->right;
        (*tree)->key = (*tmp)->key;
        elemToDel = *tmp;
        (*tmp) = (*tmp)->left;
    }

    free(elemToDel);
}

void ClearTree(Node** tree) {
    while ((*tree) != NULL)
        DFT(tree);
}
