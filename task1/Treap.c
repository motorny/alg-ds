#include "Treap.h"

#include <stdlib.h>

Treap* GetNewNode(int x)
{
    Treap* node = (Treap*)malloc(sizeof(Treap));
    if (node != NULL)
    {
        node->x = x;
        node->y = rand();
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

Treap* Merge(Treap* L, Treap* R)
{
    if (L == NULL)
        return R;
    if (R == NULL)
        return L;

    if (L->y > R->y)
    {
        L->right = Merge(L->right, R);
        return L;
    }
    else
    {
        R->left = Merge(L, R->left);
        return R;
    }
}

void Split(Treap* node, int x, Treap** L, Treap** R)
{
    if (node == NULL)
    {
        (*L) = NULL;
        (*R) = NULL;
        return;
    }

    if (node->x <= x)
    {
        Split(node->right, x, &(node->right), R);
        (*L) = node;
    }
    else
    {
        Split(node->left, x, L, &(node->left));
        (*R) = node;
    }
}

void Insert(Treap** root, int x)
{
    if ((*root) == NULL)
    {
        (*root) = GetNewNode(x);
        return;
    }

    Treap* L = NULL;
    Treap* R = NULL;
    Split(*root, x, &L, &R);
    Treap* m = GetNewNode(x);

    (*root) = Merge(Merge(L, m), R);
}

void Remove(Treap** root, int x)
{
    Treap* L = NULL;
    Treap* R = NULL;
    Treap* m = NULL;

    Split(*root, x - 1, &L, &R);
    Split(R, x, &m, &R);

    free(m);

    (*root) = Merge(L, R);
}

Treap* Find(Treap* node, int x)
{
    if (node == NULL)
        return NULL;

    if (node->x == x)
        return node;

    if (node->x < x)
        return Find(node->right, x);
    else
        return Find(node->left, x);
}

void DestroyTreap(Treap* node)
{
    if (node != NULL)
    {
        DestroyTreap(node->left);
        DestroyTreap(node->right);
        free(node);
    }
}
