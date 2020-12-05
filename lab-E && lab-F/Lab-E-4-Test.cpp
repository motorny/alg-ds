#include "pch.h"

extern "C" {
#include "..\Lab-E-4\Lab-E-4.c"
}

TEST(NodeAppend1, NodeAppend1_EmptyTree_ReturnTreeFromOneElement) {
  tree_t* tree = NULL;
  char buff[] = "Hello";
  NodeAppend1(&tree, buff);

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_EQ(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 5);
  EXPECT_EQ(tree->subtreeWigth, 0);

  DestroyTree1(tree);
}

TEST(NodeAppend, NodeAppend_AppendToBothSides_ReturnsValidTree) {
  tree_t* tree = NULL, *temp = tree;
  NodeAppend1(&tree, "no");
  NodeAppend1(&tree, "m");
  NodeAppend1(&tree, "yes");

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);
  EXPECT_EQ(tree->subtreeWigth, 4);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);
  EXPECT_EQ(temp->subtreeWigth, 0);

  temp = tree->right;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 3);
  EXPECT_EQ(temp->subtreeWigth, 0);

  DestroyTree1(tree);
}

TEST(NodeFind, NodeFind_NodeDoesntExist_ReturnNULL) {
  tree_t* tree = NULL;
  NodeAppend1(&tree, "no");
  NodeAppend1(&tree, "m");
  NodeAppend1(&tree, "yes");

  EXPECT_EQ(NodeFind1(tree, "hello"), (tree_t*)NULL);
  DestroyTree1(tree);
}

TEST(NodeFind, NodeFind_NodeExists_ReturnValidAdress) {
  tree_t* tree = NULL;
  NodeAppend1(&tree, "no");
  NodeAppend1(&tree, "m");
  NodeAppend1(&tree, "yes");

  EXPECT_NE(NodeFind1(tree, "yes"), (tree_t*)NULL);
  DestroyTree1(tree);
}

TEST(NodeRemove, NodeRemove_NodeDoesnotexist_DoNotTouchTree) {
  tree_t* tree = NULL, * temp = tree;
  NodeAppend1(&tree, "no");
  NodeAppend1(&tree, "m");
  NodeAppend1(&tree, "yes");

  NodeRemove1(&tree, NodeFind1(tree, "hello"));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);
  EXPECT_EQ(tree->subtreeWigth, 4);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);
  EXPECT_EQ(temp->subtreeWigth, 0);

  temp = tree->right;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 3);
  EXPECT_EQ(temp->subtreeWigth, 0);

  DestroyTree1(tree);
}

TEST(NodeRemove, NodeRemove_NodeExists_Remove) {
  tree_t* tree = NULL, * temp = tree;
  NodeAppend1(&tree, "no");
  NodeAppend1(&tree, "m");
  NodeAppend1(&tree, "yes");

  NodeRemove1(&tree, NodeFind1(tree, "yes"));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);
  EXPECT_EQ(tree->subtreeWigth, 1);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->num, 1);
  EXPECT_EQ(temp->subtreeWigth, 0);

  DestroyTree1(tree);
}