#include "pch.h"
#include "tree.h"

TEST(Function_Add, TreeNewElement_elementsInTree) {
  tree_t tree = {NULL};
  int key1 = 2, key2 = 1, key3 = 3;
  Add(&tree, key1);
  Add(&tree, key2);
  Add(&tree, key3);

  ASSERT_EQ(tree.root->key, key1);
  ASSERT_EQ(tree.root->left->key, key2);
  ASSERT_EQ(tree.root->right->key, key3);
}

TEST(Function_Find, findOneElement) {
  tree_t tree;
  node_t* finding;
  node_t node1 = { 0, 1, 1, NULL, NULL, NULL };
  node_t node2 = { 0, 1, 3, NULL, NULL, NULL };
  node_t node3 = { 0, 3, 2, &node1, &node2, NULL };
  node1.p = &node3;
  node2.p = &node3;
  tree.root = &node3;

  finding = Find(&tree, 3);
  ASSERT_EQ(finding, &node2);
}
TEST(Function_Delete, DeleteOneElement_elementNotInTree) {
  tree_t tree;
  node_t node1 = {0, 1, 1, NULL, NULL, NULL};
  node_t node2 = { 0, 1, 3, NULL, NULL, NULL};
  node_t node3 = { 0, 3, 2, &node1, &node2, NULL};
  node1.p = &node3;
  node2.p = &node3;
  tree.root = &node3;

  Delete(&tree, 2);
  ASSERT_EQ(tree.root->right, (node_t*)NULL);
}

TEST(Function_CountLeaves, Tree_countingLevesInTree) {
  tree_t tree;
  node_t node5_1 = { 0, 1, 15, NULL, NULL, NULL };
  node_t node5_2 = { 0, 1, 17, NULL, NULL, NULL };
  node_t node4_1 = { 0, 3, 16, &node5_1, &node5_2, NULL };
  node_t node3_1 = { 0, 4, 14, NULL, &node4_1, NULL };
  node_t node3_2 = { 0, 1, 19, NULL, NULL, NULL };
  node_t node2_1 = { 0, 6, 18, &node3_1, &node3_2, NULL };
  node_t node2_2 = { 0, 1, 25, NULL, NULL, NULL };
  node_t node1_1 = { 0, 8, 20, &node2_1, &node2_2, NULL };
  node5_1.p = &node4_1;
  node5_2.p = &node4_1;
  node4_1.p = &node3_1;
  node3_1.p = &node2_1;
  node3_2.p = &node2_1;
  node2_1.p = &node1_1;
  node2_2.p = &node1_1;
  tree.root = &node1_1;

  CountLeaves(&tree);

  ASSERT_EQ(tree.root->data, 4);
  ASSERT_EQ(tree.root->left->data, 3);
  ASSERT_EQ(tree.root->right->data, 0);
  ASSERT_EQ(tree.root->left->left->data, 2);
  ASSERT_EQ(tree.root->left->right->data, 0);
  ASSERT_EQ(tree.root->left->left->right->data, 2);
  ASSERT_EQ(tree.root->left->left->right->left->data, 0);
  ASSERT_EQ(tree.root->left->left->right->right->data, 0);
}

TEST(Function_FindShiftK, findShiftToKFromNElement) {
  tree_t tree;
  node_t node5_1 = { 0, 1, 15, NULL, NULL, NULL };
  node_t node5_2 = { 0, 1, 17, NULL, NULL, NULL };
  node_t node4_1 = { 0, 3, 16, &node5_1, &node5_2, NULL };
  node_t node3_1 = { 0, 4, 14, NULL, &node4_1, NULL };
  node_t node3_2 = { 0, 1, 19, NULL, NULL, NULL };
  node_t node2_1 = { 0, 6, 18, &node3_1, &node3_2, NULL };
  node_t node2_2 = { 0, 1, 25, NULL, NULL, NULL };
  node_t node1_1 = { 0, 8, 20, &node2_1, &node2_2, NULL };
  node5_1.p = &node4_1;
  node5_2.p = &node4_1;
  node4_1.p = &node3_1;
  node3_1.p = &node2_1;
  node3_2.p = &node2_1;
  node2_1.p = &node1_1;
  node2_2.p = &node1_1;
  tree.root = &node1_1;
  int finding;

  finding = FindShiftK(&tree, 1, 18);

  ASSERT_EQ(tree.root->left->left->right->right->key, finding);
}