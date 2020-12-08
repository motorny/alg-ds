#include "pch.h"

extern "C" {
#include "..\Lab-F\Lab-F-20.c"
}

TEST(NodeAppend, NodeAppend_EmptyTree_ReturnTreeFromOneElement) {
  tree_t* tree = NULL;
  const int num = 1;
  NodeAppend2(&tree, num);

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_EQ(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, num);
  EXPECT_EQ(tree->order, 1);

  DestroyTree2(tree);
}

TEST(NodeAppend, NodeAppend_AppendToBothSides_ReturnsValidTree) {
  tree_t* tree = NULL, * temp = tree;
  NodeAppend2(&tree, 2);
  NodeAppend2(&tree, 1);
  NodeAppend2(&tree, 3);

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);
  EXPECT_EQ(tree->order, 2);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);
  EXPECT_EQ(temp->order, 1);

  temp = tree->right;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 3);
  EXPECT_EQ(temp->order, 3);

  DestroyTree2(tree);
}

TEST(NodeFind, NodeFind_NodeDoesntExist_ReturnNULL) {
  tree_t* tree = NULL;
  NodeAppend2(&tree, 2);
  NodeAppend2(&tree, 1);
  NodeAppend2(&tree, 3);

  EXPECT_EQ(NodeFind2(tree, 4), (tree_t*)NULL);
  DestroyTree2(tree);
}

TEST(NodeFind, NodeFind_NodeExists_ReturnValidAdress) {
  tree_t* tree = NULL;
  NodeAppend2(&tree, 2);
  NodeAppend2(&tree, 1);
  NodeAppend2(&tree, 3);

  EXPECT_NE(NodeFind2(tree, 3), (tree_t*)NULL);
  DestroyTree2(tree);
}

TEST(NodeRemove, NodeRemove_NodeDoesnotexist_DoNotTouchTree) {
  tree_t* tree = NULL, * temp = tree;
  NodeAppend2(&tree, 2);
  NodeAppend2(&tree, 1);
  NodeAppend2(&tree, 3);

  NodeRemove2(&tree, NodeFind2(tree, 4));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);
  EXPECT_EQ(tree->order, 2);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);
  EXPECT_EQ(temp->order, 1);

  temp = tree->right;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 3);
  EXPECT_EQ(temp->order, 3);

  DestroyTree2(tree);
}

TEST(NodeRemove, NodeRemove_NodeExists_Remove) {
  tree_t* tree = NULL, * temp = tree;
  NodeAppend2(&tree, 2);
  NodeAppend2(&tree, 1);
  NodeAppend2(&tree, 3);

  NodeRemove2(&tree, NodeFind2(tree, 3));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);
  EXPECT_EQ(tree->order, 2);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);
  EXPECT_EQ(temp->order, 1);

  DestroyTree2(tree);
}
