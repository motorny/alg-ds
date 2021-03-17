#include"treap.h"
#pragma warning(disable:4996)
Treap* Merge(Treap* L, Treap* R) {
  if (L == NULL) return R;
  if (R == NULL) return L;
  if (L->y > R->y) {
    L->right = Merge(L->right, R);
    return L;
  }
  else {
    R->left = Merge(L, R->left);
    return R;
  }
}

void Split(Treap* T, Treap** outL, Treap** outR, int x) {
  if (T == NULL) {
    (*outL) = NULL;
    (*outR) = NULL;
    return;
  }
  else if (T->x <= x) {
    Split(T->right, &(T->right), outR, x);
    (*outL) = T;
  }
  else {
    Split(T->left, outL, &(T->left), x);
    (*outR) = T;
  }
}

void Add(Treap** T, int x) {
  Treap* L = NULL, * R = NULL, * newT = NULL;
  if ((*T) != NULL) {
    Split(*T, &L, &R, x);
  }
  newT = (Treap*)malloc(sizeof(Treap));
  newT->x = x;
  newT->y = rand();
  newT->left = NULL;
  newT->right = NULL;
  (*T) = Merge(Merge(L, newT), R);
}

void Remove(Treap** T, int x) {
  Treap* L = NULL, * R = NULL, * newT = NULL;
  Split(*T, &L, &R, x - 1);
  Split(R, &newT, &R, x);
  if (newT) {
    free(newT);
  }
  (*T) = Merge(L, R);
}