#ifndef AATREE_H
#define AATREE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef enum{
  ERROR = -1,
  OK,
  FOUND, 
  NOT_FOUND
}ERR_STATUS;

typedef struct _aanode_t {
  int key;
  int level;
  struct _aanode_t* l;
  struct _aanode_t* r;
}aanode_t;

typedef struct {
  aanode_t* root;
  aanode_t* bottom;
  aanode_t* last;
  aanode_t* todel;
}aatree_t;

aatree_t* Create();
void Delete(aatree_t* tree);

void Add(aatree_t* tree, const int key);
void Remove(aatree_t* tree, const int key);
ERR_STATUS Search(const aatree_t* tree, const int key);

void PrintTree(aanode_t* node, aanode_t* btm, int n);

#endif //AATREE_H