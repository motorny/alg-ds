#include "pch.h"
extern "C" {
#include"F22.h"
}
tree_t* createModelTree(tree_t* tree) {
  tree = (tree_t*)malloc(sizeof(tree_t));
  if (tree == NULL)
    return NULL;
  tree->low = 15;
  tree->high = 20;
  tree->max = 30;
  tree->left = NULL;
  tree->right = NULL;
  tree->left = (tree_t*)malloc(sizeof(tree_t));
  if (tree->left == NULL)
    return NULL;
  tree->right = (tree_t*)malloc(sizeof(tree_t));
  if (tree->right == NULL)
    return NULL;
  tree->left->low = 10;
  tree->left->high = 30;
  tree->left->max = 30;
  tree->right->low = 17;
  tree->right->high = 19;
  tree->right->max = 19;
  tree->left->left = NULL;
  tree->left->right = NULL;
  tree->right->left = NULL;
  tree->right->right = NULL;
  return tree;
  //       [15, 20]
  //          30
  //  [10, 30]    [17, 19]
  //     30          19
}
TEST(addTree, TreeNullPtr_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = addTree(tree, 1, 2);
  ASSERT_TRUE(tree != NULL);
  ASSERT_EQ(tree->low, 1);
  ASSERT_EQ(tree->high, 2);
  ASSERT_EQ(tree->max, 2);
  ASSERT_TRUE(tree->right == NULL);
  ASSERT_TRUE(tree->left == NULL);
  freeTree(tree);
}
TEST(addTree, TreeAddingNewInterval_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = addTree(tree, 30, 40);
  ASSERT_EQ(tree->max, 40);
  ASSERT_EQ(tree->right->max, 40);
  ASSERT_TRUE(tree->right->right != NULL);
  ASSERT_EQ(tree->right->right->low, 30);
  ASSERT_EQ(tree->right->right->high, 40);
  ASSERT_EQ(tree->right->right->max, 40);
  ASSERT_TRUE(tree->right->right->right == NULL);
  ASSERT_TRUE(tree->right->right->left == NULL);
  freeTree(tree);
}
TEST(addTree, TreeAddingSameInterval_notChangeTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = addTree(tree, 17, 19);
  //compare to model tree
  ASSERT_TRUE(tree != NULL);
  ASSERT_EQ(tree->low, 15);
  ASSERT_EQ(tree->high, 20);
  ASSERT_EQ(tree->max, 30);
  ASSERT_TRUE(tree->left != NULL);
  ASSERT_EQ(tree->left->low, 10);
  ASSERT_EQ(tree->left->high, 30);
  ASSERT_EQ(tree->left->max, 30);
  ASSERT_TRUE(tree->left->left == NULL);
  ASSERT_TRUE(tree->left->right == NULL);
  ASSERT_TRUE(tree->right != NULL);
  ASSERT_EQ(tree->right->low, 17);
  ASSERT_EQ(tree->right->high, 19);
  ASSERT_EQ(tree->right->max, 19);
  ASSERT_TRUE(tree->right->left == NULL);
  ASSERT_TRUE(tree->right->right == NULL);
  freeTree(tree);
}
TEST(delTree, DeleteIntervak_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = delTree(tree, 17, 19);
  ASSERT_TRUE(tree->right == NULL);
  freeTree(tree);
}
TEST(delTree, DeleteIntervalThatDoesNotExist_returnCorrectTree) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  tree = delTree(tree, 1, 2);
  //compare to model tree
  ASSERT_TRUE(tree != NULL);
  ASSERT_EQ(tree->low, 15);
  ASSERT_EQ(tree->high, 20);
  ASSERT_EQ(tree->max, 30);
  ASSERT_TRUE(tree->left != NULL);
  ASSERT_EQ(tree->left->low, 10);
  ASSERT_EQ(tree->left->high, 30);
  ASSERT_EQ(tree->left->max, 30);
  ASSERT_TRUE(tree->left->left == NULL);
  ASSERT_TRUE(tree->left->right == NULL);
  ASSERT_TRUE(tree->right != NULL);
  ASSERT_EQ(tree->right->low, 17);
  ASSERT_EQ(tree->right->high, 19);
  ASSERT_EQ(tree->right->max, 19);
  ASSERT_TRUE(tree->right->left == NULL);
  ASSERT_TRUE(tree->right->right == NULL);
  freeTree(tree);
}
TEST(delTree, DeleteNullPtr_returnNull) {
  tree_t* tree = NULL;
  tree = delTree(tree, 1, 2);
  ASSERT_TRUE(tree == NULL);
}
TEST(findTree, NullTree_returnNotFound) {
  tree_t* tree = NULL;
  ASSERT_EQ(findTree(tree, 1, 2), NOTFOUND);
}
TEST(findTree, IntervalThatExist_returnFound) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  ASSERT_EQ(findTree(tree, 17, 19), FOUND);
  freeTree(tree);
}
TEST(findTree, NodeThatExist_returnNotFound) {
  tree_t* tree = NULL;
  tree = createModelTree(tree);
  ASSERT_EQ(findTree(tree, 1, 2), NOTFOUND);
  freeTree(tree);
}