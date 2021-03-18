#include "pch.h"

TEST(addElem, TreeEmpty_returnTrue) {
  tree_t tree;
  tree.root = NULL;
  ASSERT_EQ(addElem(&tree, 1), TRUE);
  deleteTree(&tree);
}
TEST(addElem, TreeExist_returnFalse) {
  tree_t tree;
  node_t a;
  a.value = 1;
  a.left = NULL;
  a.right = NULL;
  tree.root = &a;
  ASSERT_EQ(addElem(&tree, 1), FALSE);
  deleteTree(&tree);
}
TEST(addElem, TreeWithElem_returnTrue) {
  tree_t tree;
  node_t a;
  a.value = 1;
  a.left = NULL;
  a.right = NULL;
  tree.root = &a;
  ASSERT_EQ(addElem(&tree, -1), TRUE);
  ASSERT_TRUE(a.left->value == -1);
  ASSERT_TRUE(a.right == NULL);
  deleteTree(&tree);
}

TEST(deleteElem, TreeEmpty_returnFalse) {
  tree_t tree;
  tree.root = NULL;
  ASSERT_EQ(deleteElem(&tree, 1), FALSE);
  deleteTree(&tree);
}
TEST(deleteElem, TreeNotExistElem_returnFalse) {
  tree_t tree;
  node_t a;
  a.value = 1;
  a.left = NULL;
  a.right = NULL;
  tree.root = &a;
  ASSERT_EQ(deleteElem(&tree, -1), FALSE);
  deleteTree(&tree);
}
TEST(deleteElem, TreeExistElemRoot_returnTrue) {
  tree_t tree;
  node_t a;
  tree.root = &a;
  a.parent = NULL;
  a.left = NULL;
  a.right = NULL;
  a.value = 5;
  ASSERT_EQ(deleteElem(&tree, 5), TRUE);
  deleteTree(&tree);
}
TEST(deleteElem, TreeExistElem_returnTrue) {
  tree_t tree;
  node_t a;
  node_t b;
  node_t c;
  node_t d;
  node_t e;

  a.value = 5;
  b.value = 6;
  c.value = -1;
  d.value = 14;
  e.value = 17;

  a.parent = NULL;
  a.right = &b;
  a.left = &c;
  b.parent = &a;
  c.parent = &a;
  c.left = NULL;
  c.right = NULL;
  b.right = &d;
  b.left = NULL;
  d.parent = &b;
  d.right = &e;
  d.left = NULL;
  e.parent = &d;
  e.left = NULL;
  e.right = NULL;

  tree.root = &a;
  ASSERT_EQ(deleteElem(&tree, 14), TRUE);
  ASSERT_TRUE(tree.root->value = 5);
  ASSERT_TRUE(tree.root->left->value = -1);
  ASSERT_TRUE(tree.root->right->value = 6);
  ASSERT_TRUE(tree.root->right->right->value = 17);
  deleteTree(&tree);
}

TEST(searchElem, TreeEmpty_returnFalse) {
  tree_t tree;
  tree.root = NULL;
  ASSERT_EQ(searchElem(&tree, 1), FALSE);
  deleteTree(&tree);
}
TEST(searchElem, TreeNotExistElem_returnFalse) {
  tree_t tree;
  node_t a;
  node_t b;
  node_t c;
  node_t d;
  node_t e;

  a.value = 5;
  b.value = 6;
  c.value = -1;
  d.value = 14;
  e.value = 17;

  a.parent = NULL;
  a.right = &b;
  a.left = &c;
  b.parent = &a;
  c.parent = &a;
  c.left = NULL;
  c.right = NULL;
  b.right = &d;
  b.left = NULL;
  d.parent = &b;
  d.right = &e;
  d.left = NULL;
  e.parent = &d;
  e.left = NULL;
  e.right = NULL;

  tree.root = &a;
  ASSERT_EQ(searchElem(&tree, 42), FALSE);
  deleteTree(&tree);
}
TEST(searchElem, TreeExistElem_returnTrue) {
  tree_t tree;
  node_t a;
  node_t b;
  node_t c;
  node_t d;
  node_t e;

  a.value = 5;
  b.value = 6;
  c.value = -1;
  d.value = 14;
  e.value = 17;

  a.parent = NULL;
  a.right = &b;
  a.left = &c;
  b.parent = &a;
  c.parent = &a;
  c.left = NULL;
  c.right = NULL;
  b.right = &d;
  b.left = NULL;
  d.parent = &b;
  d.right = &e;
  d.left = NULL;
  e.parent = &d;
  e.left = NULL;
  e.right = NULL;

  tree.root = &a;
  ASSERT_EQ(searchElem(&tree, 14), TRUE);
  ASSERT_TRUE(tree.root->value = 14);
  ASSERT_TRUE(tree.root->left->value = 6);
  ASSERT_TRUE(tree.root->right->value = 17);
  ASSERT_TRUE(tree.root->left->left->value = 5);
  ASSERT_TRUE(tree.root->left->left->left->value = -1);
  deleteTree(&tree);
}