#include "pch.h"

extern "C" {
#include "E4.c"
}

TEST(Append, EmptyTree_ReturnTreeFromOneElement) {
  tree_t* tree = NULL;
  char buff[] = "Hello";
  Append(&tree, buff);

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_EQ(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->len, 5);
  EXPECT_EQ(tree->WigthOfSubtree, 0);

  DestroyTree(tree);
}

TEST(Append, AppendToBothSides_ReturnsValidTree) {
  tree_t* tree = NULL, * temp = tree;
  Append(&tree, "no");
  Append(&tree, "m");
  Append(&tree, "yes");

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->len, 2);
  EXPECT_EQ(tree->WigthOfSubtree, 4);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->len, 1);
  EXPECT_EQ(temp->WigthOfSubtree, 0);

  temp = tree->right;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->len, 3);
  EXPECT_EQ(temp->WigthOfSubtree, 0);

  DestroyTree(tree);
}

TEST(Find, NodeDoesntExist_ReturnNULL) {
  tree_t* tree = NULL;
  Append(&tree, "no");
  Append(&tree, "m");
  Append(&tree, "yes");

  EXPECT_EQ(Find(tree, "hello"), (tree_t*)NULL);
  DestroyTree(tree);
}

TEST(Find, NodeExists_ReturnValidAdress) {
  tree_t* tree = NULL;
  Append(&tree, "no");
  Append(&tree, "m");
  Append(&tree, "yes");

  EXPECT_NE(Find(tree, "yes"), (tree_t*)NULL);
  DestroyTree(tree);
}

TEST(Delete, NodeDoesnotExist_DoNotTouchTree) {
  tree_t* tree = NULL, * temp = tree;
  Append(&tree, "no");
  Append(&tree, "m");
  Append(&tree, "yes");

  Delete(&tree, Find(tree, "hello"));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_NE(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->len, 2);
  EXPECT_EQ(tree->WigthOfSubtree, 4);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->len, 1);
  EXPECT_EQ(temp->WigthOfSubtree, 0);

  temp = tree->right;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->len, 3);
  EXPECT_EQ(temp->WigthOfSubtree, 0);

  DestroyTree(tree);
}

TEST(Delete, NodeExists_Remove) {
  tree_t* tree = NULL, * temp = tree;
  Append(&tree, "no");
  Append(&tree, "m");
  Append(&tree, "yes");

  Delete(&tree, Find(tree, "yes"));

  EXPECT_NE(tree, (tree_t*)NULL);
  EXPECT_NE(tree->left, (tree_t*)NULL);
  EXPECT_EQ(tree->parent, (tree_t*)NULL);
  EXPECT_EQ(tree->right, (tree_t*)NULL);
  EXPECT_EQ(tree->len, 2);
  EXPECT_EQ(tree->WigthOfSubtree, 1);

  temp = tree->left;
  EXPECT_NE(temp, (tree_t*)NULL);
  EXPECT_EQ(temp->left, (tree_t*)NULL);
  EXPECT_EQ(temp->parent, tree);
  EXPECT_EQ(temp->right, (tree_t*)NULL);
  EXPECT_EQ(temp->len, 1);
  EXPECT_EQ(temp->WigthOfSubtree, 0);

  DestroyTree(tree);
}