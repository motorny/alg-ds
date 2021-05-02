#include "pch.h"

extern "C" {
#include"tree.h"
}


TEST(insertKey, successInsert) {
  tree_t* tree = NULL;

  insertKey(&tree, 10);
  insertKey(&tree, 11);
  insertKey(&tree, 12);
  insertKey(&tree, 13);
  insertKey(&tree, 14);
  insertKey(&tree, 15);
  insertKey(&tree, 16);

  ASSERT_EQ(tree->keys[0], 10);
  ASSERT_EQ(tree->keys[1], 11);
  ASSERT_EQ(tree->keys[2], 12);
  ASSERT_EQ(tree->keys[3], 13);
  ASSERT_EQ(tree->keys[4], 14);
  ASSERT_EQ(tree->keys[5], 15);
  ASSERT_EQ(tree->keys[6], 16);

  deleteTree(tree);
}

TEST(insertKey, successSplit) {
  tree_t* tree = NULL;

  insertKey(&tree, 10);
  insertKey(&tree, 11);
  insertKey(&tree, 12);
  insertKey(&tree, 13);
  insertKey(&tree, 14);
  insertKey(&tree, 15);
  insertKey(&tree, 16);
  insertKey(&tree, 17);//split tree here

  ASSERT_EQ(tree->keys[0], 13);
  ASSERT_EQ(tree->nodes[0]->keys[0], 10);
  ASSERT_EQ(tree->nodes[0]->keys[1], 11);
  ASSERT_EQ(tree->nodes[0]->keys[2], 12);
  ASSERT_EQ(tree->nodes[1]->keys[0], 14);
  ASSERT_EQ(tree->nodes[1]->keys[1], 15);
  ASSERT_EQ(tree->nodes[1]->keys[2], 16);

  deleteTree(tree);
}

TEST(findKey, foundKey) {
  tree_t* tree = NULL;

  insertKey(&tree, 10);
  insertKey(&tree, 11);
  insertKey(&tree, 12);
  insertKey(&tree, 13);
  insertKey(&tree, 14);
  insertKey(&tree, 15);
  insertKey(&tree, 16);

  ASSERT_TRUE(findKey(tree, 13) != NULL);

  deleteTree(tree);
}

TEST(findKey, notFoundKey) {
  tree_t* tree = NULL;

  insertKey(&tree, 10);
  insertKey(&tree, 11);
  insertKey(&tree, 12);
  insertKey(&tree, 13);
  insertKey(&tree, 14);
  insertKey(&tree, 15);
  insertKey(&tree, 16);

  ASSERT_TRUE(findKey(tree, 17) == NULL);

  deleteTree(tree);
}

TEST(deleteKey, successDelete) {
  tree_t* tree = NULL;

  insertKey(&tree, 10);
  insertKey(&tree, 11);
  insertKey(&tree, 12);
  insertKey(&tree, 13);
  insertKey(&tree, 14);
  insertKey(&tree, 15);
  insertKey(&tree, 16);

  deleteKey(&tree, 13);

  ASSERT_EQ(tree->keys[0], 10);
  ASSERT_EQ(tree->keys[1], 11);
  ASSERT_EQ(tree->keys[2], 12);
  ASSERT_EQ(tree->keys[3], 14);
  ASSERT_EQ(tree->keys[4], 15);
  ASSERT_EQ(tree->keys[5], 16);

  deleteTree(tree);
}