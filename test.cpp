#include "pch.h"
extern "C"
{
#include "tree.h"
}

node_t* testTree() {
  node_t* tree;
  tree = (node_t*)malloc(sizeof(node_t));
  if (tree == NULL)
    return NULL;
  tree->key = 10;
  tree->left = (node_t*)malloc(sizeof(node_t));
  if (tree->left == NULL)
    return NULL;
  tree->left->key = 5;
  tree->left->left = NULL;
  tree->left->right = NULL;

  tree->right = (node_t*)malloc(sizeof(node_t));
  tree->right->key = 19;

  tree->right->right = NULL;

  tree->right->left = (node_t*)malloc(sizeof(node_t));
  if (tree->right->left == NULL)
    return NULL;

  tree->right->left->key = 17;

  tree->right->left->right = NULL;

  tree->right->left->left = (node_t*)malloc(sizeof(node_t));
  if (tree->right->left->left == NULL)
    return NULL;
  tree->right->left->left->key = 15;
  tree->right->left->left->left = NULL;
  tree->right->left->left->right = NULL;

  return tree;
}
TEST(addNode, TreeNULL_returnTrue) {
  node_t* tree = NULL;
  ASSERT_EQ(addNode(&tree, 9), 1);
  ASSERT_TRUE(tree != NULL);
  ASSERT_EQ(tree->key, 9);
  ASSERT_TRUE(tree->left == NULL);
  ASSERT_TRUE(tree->right == NULL);
  deleteTree(tree);
}

TEST(addNode, TreeWithElem_returnTree) {
  node_t* tree = testTree();
  ASSERT_EQ(addNode(&tree, 21), 1);
  ASSERT_EQ(tree->right->right->key, 21);
  ASSERT_TRUE(tree->right->right->left == NULL);
  ASSERT_TRUE(tree->right->right->right == NULL);
  deleteTree(tree);
}

TEST(deleteElem, TreeNULL_returnFalse) {
  node* tree = NULL;
  ASSERT_EQ(deleteElem(&tree, 1), 0);
  deleteTree(tree);
}

TEST(deleteElem, TreeOneParentsElem_returnTrue) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));
  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  ASSERT_EQ(deleteElem(&tree, 1), 1);
  ASSERT_TRUE(tree == NULL);
  deleteTree(tree);
}

TEST(deleteElem, TreeLeftorRightChild_returnTrue) {
  node_t* tree = testTree();
  ASSERT_EQ(deleteElem(&tree, 5), 1);
  ASSERT_TRUE(tree->left == NULL);
  deleteTree(tree);
}

TEST(deleteElem, SubtreeRootWithChild_returnTrue) {
  node_t* tree = testTree();
  ASSERT_EQ(deleteElem(&tree, 19), 1);
  ASSERT_TRUE(tree->key == 10);
  ASSERT_TRUE(tree->left->key == 5);
  ASSERT_TRUE(tree->right->key == 17);
  ASSERT_TRUE(tree->right->left->key == 15);
  deleteTree(tree);
}

TEST(deleteElem, DeleteRoot_returnTrue) {
  node_t* tree = testTree();
  ASSERT_EQ(deleteElem(&tree, 10), 1);
  ASSERT_TRUE(tree->key == 5);
  ASSERT_TRUE(tree->left == NULL);
  ASSERT_TRUE(tree->right->key == 19);
  ASSERT_TRUE(tree->right->left->key == 17);
  ASSERT_TRUE(tree->right->left->left->key == 15);
  deleteTree(tree);
}

TEST(findElem, NULLTree_returnFalse) {
  node_t* tree = NULL;
  ASSERT_EQ(findElem(tree, 1), 0);
  deleteTree(tree);
}

TEST(findElem, ElemDoesntExist_returnFalse) {
  node_t* tree = testTree();
  ASSERT_TRUE(findElem(tree, 1) == 0);
  deleteTree(tree);
}

TEST(findElem, TreeElemExist_returnTrue) {
  node_t* tree = testTree();
  ASSERT_TRUE(findElem(tree, 19) == 1);
  deleteTree(tree);
}

TEST(minSubtree, NULLTree_returnFalse) {
  node_t* tree = NULL;
  ASSERT_EQ(minSubtree(tree), 0);
  deleteTree(tree);
}

TEST(minSubtree, OneElemTree_returnTrue) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));
  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  ASSERT_TRUE(minSubtree(tree) == tree->height);
  ASSERT_TRUE(tree->height == 1);
  deleteTree(tree);
}

TEST(minSubtree, TreeWithElem_returnTrue) {
  node_t* tree = testTree();
  ASSERT_TRUE(minSubtree(tree) == tree->height);

  ASSERT_TRUE(tree->height == 2);
  ASSERT_TRUE(tree->left->height == 1);
  ASSERT_TRUE(tree->right->height == 3);
  ASSERT_TRUE(tree->right->left->height == 2);
  ASSERT_TRUE(tree->right->left->left->height == 1);

  deleteTree(tree);
 }
