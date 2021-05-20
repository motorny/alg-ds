#pragma once

#ifndef AA_TREE_H__
#define AA_TREE_H__ 1

typedef struct aanode_ {
    int key;
    void* val;
    int lv;
    struct aanode_* l, * r;
} aanode;

typedef struct {
    aanode* root;
    aanode* nullnode;
    aanode* deleted;
    aanode* last;
    void(*valfree_fun)(void*);
    unsigned int num_entries;
} aatree;

aatree* new_aatree(void(*valfree_fun)(void*));
void  delete_aatree(aatree* t);
void* aa_search(const aatree* t, const int key);

void  aa_insert(aatree* t, const int key, void* val);
void  aa_remove(aatree* t, const int key);

typedef void (*AAForeach)(const aanode*, void* args);
void aa_foreach(const aatree* t, AAForeach callback, void* arg);
typedef void* (*AAMap)(const aanode*);
void aa_map(const aatree* t, AAMap callback);

#endif