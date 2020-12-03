#pragma once

#ifndef __BST_H_INCLUDED
#define __BST_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct tree_t tree_t;

#define BST_NODE_INSERTED 1
#define BST_NODE_EXIST -1

#define BST_NODE_DELETED 1

#define BST_NODE_FINDED 1
#define BST_NODE_NOT_FINDED -1

#define BST_FAIL 0

tree_t* GetTree(void);
int Insert(tree_t* t, int key);
int Delete(tree_t* t, int key);
int Find(tree_t* t, int key);
void PrintKeys(tree_t* t);
int KeyKLess(tree_t* t, int key, int k);
void PrintNumOfLeaves(tree_t* t);
void DeleteTree(tree_t* t);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BST_H_INCLUDED */
