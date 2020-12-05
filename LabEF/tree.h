#pragma once
#ifndef TREE_65327
#define TREE_65327

#define LabE
//#define LabF

typedef struct {
  double left;
  double right;
} interval_t;

#ifdef LabF
typedef interval_t data_t;
#endif
#ifdef LabE
typedef char* data_t;
#endif

typedef struct tree_t tree_t;
typedef int compare_t(const data_t a, const data_t b);
typedef void printData_t(const data_t data);
typedef int dataWidthCounter_t(const data_t data);
typedef data_t copyFunc_t(data_t);
typedef void freeFunc_t(data_t);

void SetCompareFunc(compare_t* f);
void SetPrintDataFunc(printData_t* f);
void SetDataWidthCounter(dataWidthCounter_t* f);
void SetDataCopyFunc(copyFunc_t* f);
void SetFreeDataFunc(freeFunc_t* f);
tree_t* TreeCreate();
int TreeInsert(tree_t* tree, const data_t data);
int TreeSearch(const tree_t* tree, const data_t key);
int TreeDelete(tree_t* tree, const data_t key);
void TreeFree(tree_t* tree);
void TreePrint(tree_t* tree);

#ifdef LabF
void FindIntersect(tree_t* tree, interval_t inter);
#endif

#endif // TREE_65327 included