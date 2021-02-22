#pragma once

#ifndef __AATREE_H_INCLUDED
#define __AATREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define PTR_ERR -1
#define TRUE 1
#define FALSE 0
#define MEM_ERR -2

typedef struct aatree_t {
  int key;
  int level;
  struct aatree_t* parent;
  struct aatree_t* left;
  struct aatree_t* right;
} aatree_t;

int Insert(aatree_t** root, int data);
aatree_t* Find(aatree_t* root, int data);
int Delete(aatree_t** root, int data, aatree_t* tree);
void Clear(aatree_t** root);

#endif //__AATREE_H_INCLUDED