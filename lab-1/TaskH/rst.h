#pragma once

#ifndef __RST_H_INCLUDED
#define __RST_H_INCLUDED

#ifdef cplusplus
extren "C" {
#endif

typedef struct node_t {
  int key;
  int prior;
  struct node_t *right, *left, *parent;
} node_t;

typedef struct {
  node_t *root;
} rst_t;

#define RST_INSERT_NODE_ADDED 1
#define RST_INSERT_NODE_ALREADY_EXIST 0
#define RST_INSERT_NULL_TREE -1
#define RST_INSERT_FAILED_ALLOC -2

#define RST_DELETE_NODE_DELETED 1
#define RST_DELETE_NODE_DOESNT_EXIST 0
#define RST_DELETE_NULL_TREE -1

#define RST_FIND_NODE_EXIST 1
#define RST_FIND_NODE_DOESNT_EXIST 0
#define RST_FIND_NULL_TREE -1

rst_t * GetTree(void);
void DeleteTree(rst_t *tree);
int Insert(rst_t *tree, int key);
int Delete(rst_t *tree, int key);
int Find(rst_t *tree, int key);

#ifdef cplusplus
}
#endif

#endif
