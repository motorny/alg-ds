#include "pch.h"

extern "C" {
#include "..\Lab-E\Lab-E.c"
}

TEST(NodeAppend, NodeAppend_EmptyTree_ReturnTreeFromOneElement) {
  tree_t* tree = NULL;
  const int num = 1;
  NodeAppend(&tree, num);

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_EQ(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, num);

  DestroyTree(tree);
}

TEST(NodeAppend, NodeAppend_AppendToBothSides_ReturnsValidTree) {
  tree_t* tree = NULL, *temp = tree;
  NodeAppend(&tree, 2);
  NodeAppend(&tree, 1);
  NodeAppend(&tree, 3);

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);

  temp = tree->right;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 3);

  DestroyTree(tree);
}

TEST(NodeFind, NodeFind_NodeDoesntExist_ReturnNULL) {
  tree_t* tree = NULL;
  NodeAppend(&tree, 2);
  NodeAppend(&tree, 1);
  NodeAppend(&tree, 3);

  EXPECT_EQ(NodeFind(tree, 4), (tree_t*)NULL);
  DestroyTree(tree);
}

TEST(NodeFind, NodeFind_NodeExists_ReturnAdress) {
  tree_t* tree = NULL;
  NodeAppend(&tree, 2);
  NodeAppend(&tree, 1);
  NodeAppend(&tree, 3);

  EXPECT_NE(NodeFind(tree, 3), (tree_t*)NULL);
  DestroyTree(tree);
}

TEST(NodeRemove, NodeRemove_NodeDoesnotexist_DoNotTouchTree) {
  tree_t* tree = NULL, * temp = tree;
  NodeAppend(&tree, 2);
  NodeAppend(&tree, 1);
  NodeAppend(&tree, 3);

  NodeRemove(&tree, NodeFind(tree, 4));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);

  temp = tree->right;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 3);

  DestroyTree(tree);
}

TEST(NodeRemove, NodeRemove_NodeExists_Remove) {
  tree_t* tree = NULL, * temp = tree;
  NodeAppend(&tree, 2);
  NodeAppend(&tree, 1);
  NodeAppend(&tree, 3);

  NodeRemove(&tree, NodeFind(tree, 3));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);

  DestroyTree(tree);
}
