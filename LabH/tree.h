#pragma once
#ifndef TREE_65327
#define TREE_65327

typedef int data_t;
typedef struct tree_t tree_t;
typedef int compare_t(const data_t a, const data_t b);

void SetCompareFunc(compare_t* f);
tree_t* TreeCreate();
int TreeInsert(tree_t* tree, const data_t data);
int TreeSearch(tree_t* tree, const data_t key);
int TreeDelete(tree_t* tree, const data_t key);
void TreeFree(tree_t* tree);

#endif // TREE_65327 included