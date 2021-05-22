#include "pch.h"
#include <stdlib.h>

extern "C" {
#include "..//LAB_I//2-3_tree.c"
}

tree_t* CreateTree1() {
  tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
  tree->parent = tree->child[0] = tree->child[1] = tree->child[2] = tree->child[3] = NULL;
  tree->count = 1;
  tree->keys[0] = 0;
  return tree;
}

tree_t* CreateTree2() {
  tree_t tree = (tree_t *)malloc(sizeof(tree_t));
  tree->parent = tree->child[0] = tree->child[1] = tree->child[2] = tree->child[3] = NULL;
  tree->count = 2;
  tree->keys[0] = 0;
  tree->keys[1] = 1;
  return tree;
}

TEST(Root, InsertFunction) {
  tree_t *tree = NULL;
  tree = Add(tree, 1);

  EXPECT_EQ(tree->count, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, (tree_t *)NULL);
  EXPECT_EQ(tree->child[0], (tree_t *)NULL);
  free(tree);
}

TEST(SimpleAdd, InsertFunction) {
  tree_t *tree = CreateTree1();

  tree = Add(tree, 1);

  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->keys[1], 1);
  EXPECT_EQ(tree->count, 2);
  EXPECT_EQ(tree->parent, NULL);
  EXPECT_EQ(tree->child[0], NULL);
  free(tree);
}

TEST(NormalAdd, InsertFunction) {
  tree_t *tree = CreateTree2();

  tree = Add(tree, 2);

  EXPECT_EQ(tree->count, 1);
  EXPECT_EQ(tree->keys[0], 1);
  EXPECT_EQ(tree->parent, NULL);

  EXPECT_EQ(tree->child[0]->count, 1);
  EXPECT_EQ(tree->child[0]->keys[0], 0);
  EXPECT_EQ(tree->child[0]->parent, tree);
  EXPECT_EQ(tree->child[0]->child[0], NULL);

  EXPECT_EQ(tree->child[1]->count, 1);
  EXPECT_EQ(tree->child[1]->keys[0], 2);
  EXPECT_EQ(tree->child[1]->parent, tree);
  EXPECT_EQ(tree->child[1]->child[0], NULL);

  free(tree->child[0]);
  free(tree->child[1]);
  free(tree);
}

TEST(Normal, FindFunction) {
  tree_t *tree = CreateTree1();

  EXPECT_EQ(Find(tree, 0), 1);
  free(tree);
}

TEST(Unexisted, FindFunction) {
  tree_t *tree = CreateTree1();

  EXPECT_EQ(Find(tree, 1), 0);
  free(tree);
}


TEST(Unexisted, DeleteFunction) {
  tree_t *tree = CreateTree1();

  EXPECT_EQ(Del(tree, 1), 0);
  free(tree);
}

TEST(RootCase, DeleteFunction) {
  tree_t *tree = CreateTree1();

  tree = Del(tree, 0);

  EXPECT_EQ(tree, NULL);
  free(tree);
}

TEST(SimpleCase, DeleteFunction) {
  tree_t *tree = CreateTree2();

  tree = Del(tree, 1);

  EXPECT_EQ(tree->count, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, NULL);
  EXPECT_EQ(tree->child[0], NULL);
  free(tree);
}

TEST(NormalCase, DeleteFunction) {
  tree_t *tree = CreateTree1();

  tree->child[0] = CreateTree2();

  tree = Del(tree, 1);

  EXPECT_EQ(tree->count, 2);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->keys[1], 1);
  EXPECT_EQ(tree->parent, NULL);
  EXPECT_EQ(tree->child[0], NULL);
  free(tree);
}