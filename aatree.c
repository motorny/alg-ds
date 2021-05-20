#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "aatree.h"

static aanode* new_aanode(const int key, void* val, aanode* nullnode) {
    aanode* n = (aanode*)malloc(sizeof(aanode));
    if (n == NULL) return NULL;
    n->key = key;
    n->val = val;
    n->lv = 1;
    n->l = n->r = nullnode;
    return n;
}

aatree* new_aatree(void(*valfree_fun)(void*)) {
    aatree* t = (aatree*)malloc(sizeof(aatree));
    if (t == NULL) return NULL;
    aanode* nn = (aanode*)malloc(sizeof(aanode));
    if (nn == NULL) {
        free(t);
        return NULL;
    }
    nn->lv = 0;
    nn->l = nn->r = nn;
    t->root = t->nullnode = nn;
    t->deleted = NULL;
    t->num_entries = 0;
    t->valfree_fun = valfree_fun;
    return t;
}

static void delete_aatree_(aatree* t, aanode* n) {
    assert(n);
    if (n == t->nullnode) return;
    if (n->l != t->nullnode) delete_aatree_(t, n->l);
    if (n->r != t->nullnode) delete_aatree_(t, n->r);
    if (n->val) (t->valfree_fun)(n->val);
    free(n);
}
void delete_aatree(aatree* t) {
    assert(t && t->root);
    delete_aatree_(t, t->root);
    free(t->nullnode);
    free(t);
}

static aanode* aa_skew(aanode* n) {
    assert(n && n->l);
    if (n->lv != n->l->lv) return n;
    aanode* left = n->l;
    n->l = left->r;
    left->r = n;
    n = left;
    return n;
}

static aanode* aa_split(aanode* n) {
    assert(n && n->r && n->r->r);
    if (n->r->r->lv != n->lv) return n;
    aanode* right = n->r;
    n->r = right->l;
    right->l = n;
    n = right;
    n->lv++;
    return n;
}

static aanode* aa_search_(const aanode* nn, aanode* n, const int key) {
    if (n == nn) return NULL;
    else if (n->key > key) return aa_search_(nn, n->l, key);
    else if (n->key < key) return aa_search_(nn, n->r, key);
    else return n;
}
void* aa_search(const aatree* t, const int key) {
    return aa_search_(t->nullnode, t->root, key)->val;
}

static aanode* aa_insert_(aatree* t, aanode* n, const int key, void* val) {
    if (n == t->nullnode) {
        n = new_aanode(key, val, t->nullnode);
        t->num_entries++;
        return n;
    }
    if (key < n->key) {
        n->l = aa_insert_(t, n->l, key, val);
    }
    else if (key > n->key) {
        n->r = aa_insert_(t, n->r, key, val);
    }
    else return n;
    n = aa_skew(n);
    n = aa_split(n);
    return n;
}
void aa_insert(aatree* t, const int key, void* val) {
    t->root = aa_insert_(t, t->root, key, val);
}

static aanode* aa_remove_(aatree* t, aanode* n, const int key) {
    if (n == t->nullnode) return n;
    t->last = n;
    if (key < n->key) {
        n->l = aa_remove_(t, n->l, key);
    }
    else {
        t->deleted = n;
        n->r = aa_remove_(t, n->r, key);
    }
    if (n == t->last && t->deleted != t->nullnode && key == t->deleted->key) {
        t->deleted->key = n->key;
        t->deleted = t->nullnode;
        n = n->r;
        free(t->last->val);
        free(t->last);
        t->num_entries--;
    }
    else if (n->l->lv < n->lv - 1 || n->r->lv < n->lv - 1) {
        n->lv--;
        if (n->r->lv > n->lv) n->r->lv = n->lv;
        n = aa_skew(n);
        n->r = aa_skew(n->r);
        n->r->r = aa_skew(n->r->r);
        n = aa_split(n);
        n->r = aa_split(n->r);
    }
    return n;
}
void aa_remove(aatree* t, const int key) {
    t->root = aa_remove_(t, t->root, key);
}

static void aa_foreach_(const aanode* nn, const aanode* n, AAForeach cb, void* arg) {
    if (n == nn) return;
    (*cb)(n, arg);
    aa_foreach_(nn, n->l, cb, arg);
    aa_foreach_(nn, n->r, cb, arg);
}
void aa_foreach(const aatree* t, AAForeach callback, void* arg) {
    aa_foreach_(t->nullnode, t->root, callback, arg);
}
static void aa_map_(const aanode* nn, aanode* n, AAMap cb) {
    if (n == nn) return;
    void* tmp = (*cb)(n);
    free(n->val);
    n->val = tmp;
    aa_map_(nn, n->l, cb);
    aa_map_(nn, n->r, cb);
}
void aa_map(const aatree* t, AAMap callback) {
    aa_map_(t->nullnode, t->root, callback);
}
