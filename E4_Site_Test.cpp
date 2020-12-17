#include "pch.h"

extern "C" {
#include "E4_Site.c"
}


TEST(Append, EmptyTree_ReturnTreeFromOneElement) {
  tree_t* tree = NULL;
  const int num = 1;
  Append(&tree, num);

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_EQ(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->num, num);

  DestroyTree(tree);
}

TEST(Append, AppendToBothSides_ReturnsValidTree) {
  tree_t* tree = NULL, * tmp = tree;
  Append(&tree, 2);
  Append(&tree, 1);
  Append(&tree, 3);

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->num, 2);

  tmp = tree->left;
  EXPECT_NE(tmp, (tree_t*)NULL);
  EXPECT_EQ(tmp->left, (tree_t*)NULL);
  EXPECT_EQ(tmp->right, (tree_t*)NULL);
  EXPECT_EQ(tmp->parent, tree);
  EXPECT_EQ(tmp->num, 1);

  tmp = tree->right;
  EXPECT_NE(tmp, (tree_t*)NULL);
  EXPECT_EQ(tmp->left, (tree_t*)NULL);
  EXPECT_EQ(tmp->right, (tree_t*)NULL);
  EXPECT_EQ(tmp->parent, tree);
  EXPECT_EQ(tmp->num, 3);

  DestroyTree(tree);
}


TEST(Find, NodeDoesntExist_ReturnNULL) {
  tree_t* tree = NULL;
  Append(&tree, 2);
  Append(&tree, 1);
  Append(&tree, 3);

  EXPECT_EQ(Find(tree, 4), (tree_t*)NULL);
  DestroyTree(tree);
}

TEST(NodeFind, NodeFind_NodeExists_ReturnAdress) {
  tree_t* tree = NULL;
  Append(&tree, 2);
  Append(&tree, 1);
  Append(&tree, 3);

  EXPECT_NE(Find(tree, 3), (tree_t*)NULL);
  DestroyTree(tree);
}


TEST(Delete, NodeDoesnotExist_DoNotTouchTree) {
  tree_t* tree = NULL, * temp = tree;
  Append(&tree, 2);
  Append(&tree, 1);
  Append(&tree, 3);

  Delete(&tree, Find(tree, 4));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
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
  Append(&tree, 2);
  Append(&tree, 1);
  Append(&tree, 3);

  Delete(&tree, Find(tree, 3));

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