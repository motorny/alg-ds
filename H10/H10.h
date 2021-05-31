#ifndef H10_H_INCLUDED__
#define H10_H_INCLUDED__

#pragma once

typedef struct AVL_t {
  int key;
  struct AVL_t* l;
  struct AVL_t* r;
  int h;
} AVL_t;

AVL_t* AddKey(AVL_t* node, int key);

AVL_t* RemoveKey(AVL_t* node, int key);

AVL_t* FindKey(AVL_t* node, int key, int* flagDone);

void DestroyTree(AVL_t* node);

void Run(void);

#endif
