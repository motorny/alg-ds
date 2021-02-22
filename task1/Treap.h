#ifndef TREAP_H
#define TREAP_H

typedef struct Treap
{
    int x;
    int y;
    struct Treap* left;
    struct Treap* right;
} Treap;

Treap* GetNewNode(int x);

Treap* Merge(Treap* L, Treap* R);

void Split(Treap* node, int x, Treap** L, Treap** R);

void Insert(Treap** root, int x);

void Remove(Treap** root, int x);

Treap* Find(Treap* node, int x);

void DestroyTreap(Treap* node);

#endif // TREAP_H
