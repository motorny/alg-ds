#include "lab_F.h"

int Add(node_t** t, node_t* father, int key) {
    int flag;

    if (*t == NULL) {
        node_t* newNode = (node_t*)malloc(sizeof(node_t));
        if (newNode == NULL)
            return -1;

        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->number = 1;
        newNode->father = father;
        (*t) = newNode;
        flag = 1;
    }
    else {
        if (key < (*t)->key) {
            flag = Add(&((*t)->left), *t, key);
            if (flag)
                (*t)->number++;
        }
        else if (key > (*t)->key) {
            flag = Add(&((*t)->right), *t, key);
            if (flag)
                (*t)->number++;
        }
        else
            flag = 0;

    }
    return flag;
}
node_t* Find(node_t* t, int key) {
    node_t* temp = NULL;

    if (t == NULL)
        return NULL;

    if (t->key == key)
        return t;
    else {
        if (key < t->key)
            temp = Find(t->left, key);
        else
            temp = Find(t->right, key);
    }
    return temp;
}
static int Size(node_t* t) {
    if (t == NULL || t->left == NULL)
        return 0;
    return t->left->number;
}
static int Number(node_t* t) {
    node_t* f;
    int r = Size(t);

    while (t->father != NULL) {
        f = t->father;
        if (t == f->right)
            r += Size(f->left) + 1;
        t = t->father;
    }
    r++;
    return r;
}
static node_t* FindTreeLowerOnKHelp(node_t* t, int k) {
    if (t == NULL)
        return NULL;
    if (k < 0)
        return NULL;
    if (k > t->number)
        return NULL;

    int r;

    if (t->left != NULL) {
        r = t->left->number + 1;
    }
    else
        r = 1;

    if (r != k) {
        if (k < r)
            t = FindTreeLowerOnKHelp(t->left, k);
        else
            t = FindTreeLowerOnKHelp(t->right, k - r);
    }
    return t;
}
node_t* FindTreeLowerOnK(node_t* t, int key, int k) {
    node_t* temp = Find(t, key);
    if (temp == NULL)
        return NULL;

    int n = Number(temp);

    temp = FindTreeLowerOnKHelp(t, n - k);

    return temp;
}
void FreeTree(node_t* t) {
    if (t == NULL)
        return;
    FreeTree(t->left);
    FreeTree(t->right);
    free(t);
}