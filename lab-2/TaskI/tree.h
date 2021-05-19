#pragma once

#ifndef __TREE_H_INCLUDED
#define __TREE_H_INCLUDED

#ifdef __cpluslpus
extern "C" {
#endif /* __cpluslpus */

typedef struct node_t node_t;

#define TREE_INSERT_NODE_ADDED 1
#define TREE_INSERT_NODE_ALREADY_EXIST 0
#define TREE_INSERT_NULL_TREE -1
#define TREE_INSERT_FAILED_ALLOC -2

int Insert(node_t **root, int key);

#define TREE_DELETE_NODE_DELETED 1
#define TREE_DELETE_NODE_DOESNT_EXIST 0
#define TREE_DELETE_NULL_TREE -1

int Delete(node_t **root, int key);

#define TREE_FIND_NODE_EXIST 1
#define TREE_FIND_NODE_DOESNT_EXIST 0

int Find(node_t *root, int key);

void Print(node_t *root);
void DeleteTree(node_t *root);

#ifdef __cpluslpus
}
#endif /* __cpluslpus */

#endif 
