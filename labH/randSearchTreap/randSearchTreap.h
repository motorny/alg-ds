#pragma once

typedef struct _Treap_t Treap_t;

Treap_t* TreapGet();

void TreapFree(Treap_t* treap);

int TreapFind(Treap_t** treap_p, int key, int* val_p);

int TreapAdd(Treap_t** treap_p, int key, int priority, int val);

int TreapRSAdd(Treap_t** treap_p, int key, int val);

int TreapRemove(Treap_t** treap_p, int key, int* val_p);
