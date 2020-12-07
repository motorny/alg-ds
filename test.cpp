#include "pch.h"
extern "C" {
#include"E1.h"
}
tree_t* createModelTree(tree_t* tree) {
  tree = (tree_t*)malloc(sizeof(tree_t));
  if (tree == NULL)
    return NULL;
  tree->height = 0;
  tree->key = 8;
  tree->left = NULL;
  tree->right = NULL;
  tree->left = (tree_t*)malloc(sizeof(tree_t));
  if (tree->left == NULL)
    return NULL;
  tree->right = (tree_t*)malloc(sizeof(tree_t));
  if (tree->right == NULL)
    return NULL;
  tree->left->key = 3;
  tree->left->height = 0;
  tree->right->key = 10;
  tree->right->height = 0;
  tree->left->left = NULL;
  tree->left->right = NULL;
  tree->right->left = NULL;
  tree->right->right = NULL;
  return tree;
  //       8
  //    3     10
}
TEST(addTree, TreeNullPtr_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = addTree(tree, 1);
  ASSERT_TRUE(tree != NULL);
  ASSERT_EQ(tree->height, 0);
  ASSERT_EQ(tree->key, 1);
  ASSERT_TRUE(tree->right == NULL);
  ASSERT_TRUE(tree->left == NULL);
  freeTree(tree);
}
TEST(addTree, TreeAddingNewElem_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = addTree(tree, 4);
  ASSERT_EQ(tree->height, 1);
  ASSERT_TRUE(tree->left->right != NULL);
  ASSERT_EQ(tree->left->right->height, 0);
  ASSERT_EQ(tree->left->right->key, 4);
  ASSERT_TRUE(tree->left->right->right == NULL);
  ASSERT_TRUE(tree->left->right->left == NULL);
  freeTree(tree);
}
TEST(addTree, TreeAddingSameElem_notChangeTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = addTree(tree, 3);
  //compare to model tree
  ASSERT_TRUE(tree != NULL);
  ASSERT_EQ(tree->key, 8);
  ASSERT_EQ(tree->height, 0);
  ASSERT_TRUE(tree->left != NULL);
  ASSERT_EQ(tree->left->key, 3);
  ASSERT_EQ(tree->left->height, 0);
  ASSERT_TRUE(tree->left->left == NULL);
  ASSERT_TRUE(tree->left->right == NULL);
  ASSERT_TRUE(tree->right != NULL);
  ASSERT_EQ(tree->right->key, 10);
  ASSERT_EQ(tree->right->height, 0);
  ASSERT_TRUE(tree->right->left == NULL);
  ASSERT_TRUE(tree->right->right == NULL);
  freeTree(tree);
}
TEST(delTree, DeleteNode_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = delTree(tree, 3);
  ASSERT_TRUE(tree->left == NULL);
  freeTree(tree);
}
TEST(delTree, DeleteNodeThatDoesNotExist_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = delTree(tree, 4);
  //compare to model tree
  ASSERT_TRUE(tree != NULL);
  ASSERT_EQ(tree->key, 8);
  ASSERT_EQ(tree->height, 0);
  ASSERT_TRUE(tree->left != NULL);
  ASSERT_EQ(tree->left->key, 3);
  ASSERT_EQ(tree->left->height, 0);
  ASSERT_TRUE(tree->left->left == NULL);
  ASSERT_TRUE(tree->left->right == NULL);
  ASSERT_TRUE(tree->right != NULL);
  ASSERT_EQ(tree->right->key, 10);
  ASSERT_EQ(tree->right->height, 0);
  ASSERT_TRUE(tree->right->left == NULL);
  ASSERT_TRUE(tree->right->right == NULL);
  freeTree(tree);
}
TEST(delTree, DeleteNodeWithTwoChilds_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = delTree(tree, 8);
  ASSERT_TRUE(tree != NULL);
  ASSERT_EQ(tree->key, 10);
  ASSERT_EQ(tree->height, 0);
  ASSERT_TRUE(tree->left != NULL);
  ASSERT_EQ(tree->left->key, 3);
  ASSERT_TRUE(tree->left->right == NULL);
  ASSERT_TRUE(tree->left->left == NULL);
  ASSERT_TRUE(tree->right == NULL);
  freeTree(tree);
}
TEST(findTree, NullTree_returnNotFound) {
  tree_t* tree = NULL;
  ASSERT_EQ(findTree(tree, 1), NOTFOUND);
}
TEST(findTree, NodeThatExist_returnFound) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  ASSERT_EQ(findTree(tree, 10), FOUND);
  freeTree(tree);
}
TEST(findTree, NodeThatExist_returnNotFound) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  ASSERT_EQ(findTree(tree, 4), NOTFOUND);
  freeTree(tree);
}