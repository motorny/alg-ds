#pragma once
#define DEGREE 4

typedef struct Bplus {
    int leaf;
    int key_count;
    int key[2 * DEGREE];
    struct Bplus* parent;
    struct Bplus* child[2 * DEGREE + 1];
    struct Bplus* left;
    struct Bplus* right;
} bplus_t;

bplus_t* InitTree();
void Destroy(bplus_t** root);
void Split(bplus_t** root, bplus_t* node);
bplus_t* FindLeaf(bplus_t* root, int key);
int AddElem(bplus_t** root, int key);
int MinKey(bplus_t* node);
void Update(bplus_t* node, int key);
void Merge(bplus_t** root, bplus_t* node, int key);
void DeleteInNode(bplus_t** root, bplus_t* node, int key);
int RemoveElem(bplus_t** root, int key);
void PrintTree(bplus_t** root, int level);
int FindElem(bplus_t** root, int key);
void ToDo(bplus_t** root);