#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define deg 4
#pragma warning(disable: 4996)

typedef enum bool_t {
  FALSE,
  TRUE
}bool_t;

typedef struct Bplus {
  bool_t leaf;
  int key_count;
  int key[2 * deg];
  //int* data;//if is leaf
  struct Bplus* parent;
  struct Bplus* child[2 * deg + 1];
  struct Bplus* left;
  struct Bplus* right;
} Bplus;

Bplus* Init();
void Destroy(Bplus** root);
void Split(Bplus** root, Bplus* node);
Bplus* FindLeaf(Bplus* root, int key);
bool_t Insert(Bplus** root, int key);
int MinKey(Bplus* node);
void Update(Bplus* node, int key);
void Merge(Bplus** root, Bplus* node, int key);
void DeleteInNode(Bplus** root, Bplus* node, int key);
bool_t Delete(Bplus** root, int key);
void PrintTree(Bplus** root, int level);
bool_t FindElement(Bplus** root, int key);
void GetTreeFromConsole(Bplus** root);