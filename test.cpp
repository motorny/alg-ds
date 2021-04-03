#include "pch.h"

#define SUCCESS 1
#define FAIL 0

#define T 3 // minimum degree of B-tree

typedef struct tree_t tree_t;

typedef enum {
  FALSE,
  TRUE
} bool_t;

typedef struct node_t {
  bool_t leaf;
  int keyNum;
  int key[2 * T];
  struct node_t* child[2 * T + 1];
  struct node_t* prev;
  struct node_t* left;
  struct node_t* right;
} node_t;

struct tree_t {
  node_t* root;
};

tree_t* TreeCreate();
int TreeInsert(tree_t* tree, const int key);
int TreeSearch(const tree_t* tree, const int key);
int TreeDelete(tree_t* tree, const int key);
void TreeFree(tree_t* tree);
tree_t* TreeMerge(tree_t* t1, tree_t* t2);
void TreeSplit(tree_t* tree, int key, tree_t* t1, tree_t* t2);
void TreePrint(tree_t* tree);


TEST(TreeInsert_InsertToEmpty_ReturnsSUCCESS) {
  tree_t* t = TreeCreate();
  int key = 1;

  EXPECT_EQ(TreeInsert(t, key), SUCCESS);

  free(t->root);
  free(t);
}

TEST(TreeInsert_InsertWithSplit_ReturnsSUCCESS) {
  tree_t* t = TreeCreate();
  int key1 = 1, key2 = 2, key3 = 3, key4 = 4, key5 = 5, key6 = 6;

  EXPECT_EQ(TreeInsert(t, key1), SUCCESS);
  EXPECT_EQ(TreeInsert(t, key2), SUCCESS);
  EXPECT_EQ(TreeInsert(t, key3), SUCCESS);
  EXPECT_EQ(TreeInsert(t, key4), SUCCESS);
  EXPECT_EQ(TreeInsert(t, key5), SUCCESS);
  EXPECT_EQ(TreeInsert(t, key6), SUCCESS);

  free(t->root->child[0]);
  free(t->root->child[1]);
  free(t);
}

TEST(TreeSearch_ElementExists_ReturnsSUCCESS) {
  tree_t* t = TreeCreate();
  int key = 1;
  TreeInsert(t, key);

  EXPECT_EQ(TreeSearch(t, key), SUCCESS);

  free(t->root);
  free(t);
}

TEST(TreeSearch_ElementNOTExists_ReturnsFAIL) {
  tree_t* t = TreeCreate();
  int key = 1;
  int badKey = 2;
  TreeInsert(t, key);

  EXPECT_EQ(TreeSearch(t, badKey), FAIL);

  free(t->root);
  free(t);
}

TEST(TreeDelete_EmptyTree_ReturnsFAIL) {
  tree_t* t = TreeCreate();
  int key = 1;

  EXPECT_EQ(TreeDelete(t, key), FAIL);

  free(t->root);
  free(t);
}

TEST(TreeDelete_ElementExists_ReturnsSUCCESS) {
  tree_t* t = TreeCreate();
  int key = 1;
  TreeInsert(t, key);

  EXPECT_EQ(TreeDelete(t, key), SUCCESS);

  free(t);
}

TEST(TreeDelete_ElementNOTExists_ReturnsFAIL) {
  tree_t* t = TreeCreate();
  int key = 1;
  int badKey = 2;
  TreeInsert(t, key);

  EXPECT_EQ(TreeDelete(t, badKey), FAIL);

  free(t->root);
  free(t);
}

TEST(TreeDelete_CheckDelete_ReturnsFAIL) {
  tree_t* t = TreeCreate();
  int key = 1;

  TreeInsert(t, key);
  TreeDelete(t, key);

  EXPECT_EQ(TreeSearch(t, key), FAIL);

  free(t);
}


TEST(TreeFree_TwoLvlTree_NotCrush) {
  tree_t* t = TreeCreate();
  int key1 = 1, key2 = 2, key3 = 3, key4 = 4, key5 = 5, key6 = 6;

  TreeInsert(t, key1);
  TreeInsert(t, key2);
  TreeInsert(t, key3);
  TreeInsert(t, key4);
  TreeInsert(t, key5);
  TreeInsert(t, key6);

  TreeFree(t);
}

TEST(TreeMerge_ValidTrees_ReturnsValid) {
  tree_t* t1 = TreeCreate();
  tree_t* t2 = TreeCreate();
  tree_t* res;
  int key1 = 1, key2 = 2;
  TreeInsert(t1, key1);
  TreeInsert(t2, key2);
  res = TreeMerge(t1, t2);

  EXPECT_EQ(TreeSearch(res, key1), SUCCESS);
  EXPECT_EQ(TreeSearch(res, key2), SUCCESS);

  free(t1->root);
  free(t2->root);
  free(t1);
  free(t2);
}

TEST(TreeSplit_ValidTree_ReturnsValid) {
  tree_t* t = TreeCreate();
  tree_t *t1, *t2;
  int key1 = 1, key2 = 3, median = 2;
  TreeInsert(t, key1);
  TreeInsert(t, key2);
  TreeSplit(t, median, t1, t2);

  EXPECT_EQ(TreeSearch(t1, key1), SUCCESS);
  EXPECT_EQ(TreeSearch(t2, key2), SUCCESS);
  EXPECT_EQ(TreeSearch(t1, key2), FAIL);
  EXPECT_EQ(TreeSearch(t2, key1), FAIL);

  free(t1->root);
  free(t2->root);
  free(t->root);
  free(t1);
  free(t2);
  free(t);
}
