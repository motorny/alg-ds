#include "pch.h"
#include "../b-tree/btree.c"
#include "../b-tree/btree.h"

TEST(BTreeInsert_EmptyTree_ReturnSuccess) {
  b_tree_t tree;

  tree.root = NULL;
  EXPECT_EQ(BTreeInsert(&tree, 1), SUCCESS);
  EXPECT_EQ(tree.root->count, 1);
  EXPECT_EQ(tree.root->key[0], 1);
  EXPECT_EQ(tree.root->leaf, TRUE);

  free(tree.root);
}

TEST(BTreeInsert_SuccessfulInsert_ReturnSuccess) {
  b_tree_t tree;

  tree.root = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  tree.root->key[0] = 1;
  tree.root->count = 1;
  tree.root->leaf = TRUE;

  EXPECT_EQ(BTreeInsert(&tree, 2), SUCCESS);
  EXPECT_EQ(tree.root->count, 2);
  EXPECT_EQ(tree.root->key[0], 1);
  EXPECT_EQ(tree.root->key[1], 2);
  EXPECT_EQ(tree.root->leaf, TRUE);

  free(tree.root);
}

TEST(BTreeInsert_InsertDuplicate_ReturnSuccess) {
  b_tree_t tree;

  tree.root = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  tree.root->key[0] = 1;
  tree.root->count = 1;
  tree.root->leaf = TRUE;

  EXPECT_EQ(BTreeInsert(&tree, 1), SUCCESS);
  EXPECT_EQ(tree.root->count, 1);
  EXPECT_EQ(tree.root->key[0], 1);
  EXPECT_EQ(tree.root->leaf, TRUE);

  free(tree.root);
}

TEST(BTreeRemove_EmptyTree_ReturnFail) {
  b_tree_t tree;

  tree.root = NULL;

  EXPECT_EQ(BTreeRemove(&tree, 1), MFAIL);
  EXPECT_EQ(tree.root, (b_tree_node_t*)NULL);
}

TEST(BTreeRemove_UnexistedElement_ReturnFail) {
  b_tree_t tree;

  tree.root = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  tree.root->key[0] = 1;
  tree.root->count = 1;
  tree.root->leaf = TRUE;

  EXPECT_EQ(BTreeRemove(&tree, 2), MFAIL);
  EXPECT_EQ(tree.root->count, 1);
  EXPECT_EQ(tree.root->key[0], 1);
  EXPECT_EQ(tree.root->leaf, TRUE);

  free(tree.root);
}

TEST(BTreeRemove_ExistedElement_ReturnSuccess) {
  b_tree_t tree;

  tree.root = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  tree.root->key[0] = 1;
  tree.root->count = 1;
  tree.root->leaf = TRUE;

  EXPECT_EQ(BTreeRemove(&tree, 1), SUCCESS);
  EXPECT_EQ(tree.root, (b_tree_node_t*)NULL);
}

TEST(BTreeRemove_WithNonNullChildren_ReturnSuccess) {
  b_tree_t tree;
  b_tree_node_t node1, *node2;

  tree.root = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  node2 = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  tree.root->key[0] = 1;
  tree.root->count = 1;
  tree.root->leaf = FALSE;

  node1.count = 1;
  node1.leaf = TRUE;
  node1.key[0] = 0;
  tree.root->children[0] = &node1;

  node2->count = 1;
  node2->leaf = TRUE;
  node2->key[0] = 2;
  tree.root->children[1] = node2;

  EXPECT_EQ(BTreeRemove(&tree, 1), SUCCESS);
  EXPECT_EQ(tree.root, &node1);
  EXPECT_EQ(tree.root->key[0], 0);
  EXPECT_EQ(tree.root->key[1], 2);
  EXPECT_EQ(tree.root->leaf, TRUE);
}

TEST(BTreeFind_EmptyTree_ReturnNULL) {
  b_tree_t tree;

  tree.root = NULL;
  EXPECT_EQ(BTreeFind(&tree, 1), (b_tree_node_t*)NULL);
}

TEST(BTreeFind_FindExisted_ReturnCorrectPtr) {
  b_tree_t tree;

  tree.root = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  tree.root->key[0] = 1;
  tree.root->count = 1;
  tree.root->leaf = TRUE;

  EXPECT_EQ(BTreeFind(&tree, 1), tree.root);
  EXPECT_EQ(tree.root->count, 1);
  EXPECT_EQ(tree.root->key[0], 1);
  EXPECT_EQ(tree.root->leaf, TRUE);

  free(tree.root);
}

TEST(BTreeFind_FindUnexisted_ReturnNULL) {
  b_tree_t tree;

  tree.root = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  tree.root->key[0] = 1;
  tree.root->count = 1;
  tree.root->leaf = TRUE;

  EXPECT_EQ(BTreeFind(&tree, 2), (b_tree_node_t*)NULL);
  EXPECT_EQ(tree.root->count, 1);
  EXPECT_EQ(tree.root->key[0], 1);
  EXPECT_EQ(tree.root->leaf, TRUE);

  free(tree.root);
}

TEST(BTreeClear_EmptyTree_CorrectProcessing) {
  b_tree_t tree;

  tree.root = NULL;

  BTreeClear(&tree);
}

TEST(BTreeClear_CorrectTree_CorrectProcessing) {
  b_tree_t tree;

  tree.root = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
  tree.root->key[0] = 1;
  tree.root->count = 1;
  tree.root->leaf = TRUE;

  BTreeClear(&tree);
  EXPECT_EQ(tree.root, (b_tree_node_t*)NULL);
}