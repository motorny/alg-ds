#pragma once

typedef struct bplus_t {
    int leaf;
    int keyCount;
    int key[8];
    struct bplus_t* parent;
    struct bplus_t* child[9];
    struct bplus_t* left;
    struct bplus_t* right;
} bplus_t;

bplus_t* TreeInit();

void Destroy(bplus_t** root);

int AddElement(bplus_t** root, int key);

int FindElement(bplus_t** root, int key);

void Split(bplus_t** root, bplus_t* node);

bplus_t* FindLeaf(bplus_t* root, int key);

int MinKey(bplus_t* node);

void Update(bplus_t* node, int key);

void Merge(bplus_t** root, bplus_t* node, int key);

void DeleteInNode(bplus_t** root, bplus_t* node, int key);

int RemoveElem(bplus_t** root, int key);

void PrintTree(bplus_t** root, int level);

void MainFun(bplus_t** root);