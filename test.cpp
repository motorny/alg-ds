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
  tree->left_border = 5;
  tree->right_border = 9;
  tree->left = (node_t*)malloc(sizeof(node_t));
  if (tree->left == NULL)
    return NULL;
  tree->left->left_border = 0;
  tree->left->right_border = 1;
  tree->left->left = NULL;
  tree->left->right = NULL;

  tree->right = (node_t*)malloc(sizeof(node_t));

  tree->right->left_border = 6;
  tree->right->right_border = 10;

  tree->right->right = (node_t*)malloc(sizeof(node_t));

  tree->right->right->left_border = 8;
  tree->right->right->right_border = 12;

  tree->right->right->left = NULL;
  tree->right->right->right == NULL;

  tree->right->left = (node_t*)malloc(sizeof(node_t));
  if (tree->right->left == NULL)
    return NULL;

  tree->right->left->left_border = 4;
  tree->right->left->right_border = 10;

  tree->right->left->right = NULL;

  tree->right->left->left = (node_t*)malloc(sizeof(node_t));
  if (tree->right->left->left == NULL)
    return NULL;
  tree->right->left->left->left_border = 3;
  tree->right->left->left->right_border = 7;
  tree->right->left->left->left = NULL;
  tree->right->left->left->right = NULL;

  return tree;
}

node_t* testLittleTree() {
  node_t* tree;
  tree = (node_t*)malloc(sizeof(node_t));
  if (tree == NULL)
    return NULL;
  tree->left_border = 4;
  tree->right_border = 8;
  tree->left = (node_t*)malloc(sizeof(node_t));
  if (tree->left == NULL)
    return NULL;
  tree->left->left_border = 0;
  tree->left->right_border = 1;
  tree->left->left = NULL;
  tree->left->right = NULL;

  tree->right = (node_t*)malloc(sizeof(node_t));

  tree->right->left_border = 6;
  tree->right->right_border = 10;
  tree->right->left = NULL;
  tree->right->right = NULL;

  return tree;
}
void deleteTree(node_t* tree) {
  if (tree != NULL) {
    tree->left = NULL;
    tree->right = NULL;
  }
}

TEST(addInter, treeNULL_returnTrue) {
  node_t* tree = NULL;
  ASSERT_EQ(addInter(&tree, 0, 1), 1);
  ASSERT_TRUE(tree->left_border == 0);
  ASSERT_TRUE(tree->right_border == 1);
  deleteTree(tree);
}

TEST(addInter, treeRootLeftSubtree_returnTrue) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));
  tree->left_border = 4;
  tree->right_border = 8;
  tree->left = NULL;
  tree->right = NULL;
  ASSERT_EQ(addInter(&tree, 3, 7), 1);
  ASSERT_TRUE(tree->left->left_border == 3);
  ASSERT_TRUE(tree->left->right_border == 7);
  ASSERT_TRUE(tree->right == NULL);
  deleteTree(tree);
}

TEST(addInter, treeWithElem_returnTrue) {
  node_t* tree = testTree();
  ASSERT_EQ(addInter(&tree, 7, 11), 1);
  ASSERT_TRUE(tree->right->right->left->left_border == 7);
  ASSERT_TRUE(tree->right->right->left->right_border == 11);
  deleteTree(tree);
}

TEST(addInter, treeRootRightSubtree_returnTrue) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));
  tree->left_border = 4;
  tree->right_border = 8;
  tree->left = NULL;
  tree->right = NULL;
  ASSERT_EQ(addInter(&tree, 5, 9), 1);
  ASSERT_TRUE(tree->right->left_border == 5);
  ASSERT_TRUE(tree->right->right_border == 9);
  ASSERT_TRUE(tree->left == NULL);
  deleteTree(tree);
}

TEST(deleteInter, treeNULL_returnFalse) {
  node_t* tree = NULL;
  ASSERT_EQ(deleteInter(&tree, 0, 1), 0);
  deleteTree(tree);
}

TEST(deleteInter, treeWithElem_returnTrue) {
  node_t* tree = testTree();
  ASSERT_EQ(deleteInter(&tree, 0, 1), 1);
  ASSERT_TRUE(tree->left == NULL);
  deleteTree(tree);
 }

TEST(deleteInter, treeRootSubtree_return) {
  node_t* tree = testTree();
  ASSERT_EQ(deleteInter(&tree, 6, 10), 1);

  ASSERT_TRUE(tree->right->left_border == 4);
  ASSERT_TRUE(tree->right->right_border == 10);
  
  ASSERT_TRUE(tree->right->left->left_border == 3);
  ASSERT_TRUE(tree->right->left->right_border = 7);

  ASSERT_TRUE(tree->right->right->left_border = 8);
  ASSERT_TRUE(tree->right->right->right_border = 12);

  deleteTree(tree);
 }

TEST(findInter, treeNULL_returnFALSE) {
  node_t* tree = NULL;
  ASSERT_EQ(findInter(tree, 0, 1), 0);
  deleteTree(tree);
 }

TEST(findInter, treeWithElem_returnFALSE) {
  node_t* tree = testTree();
  ASSERT_EQ(findInter(tree, 0, 1), 1);
  deleteTree(tree);
}

TEST(findInter, treeDoesntExistInter_returnFALSE) {
  node_t* tree = testTree();
  ASSERT_EQ(findInter(tree, 7, 11), 0);
  deleteTree(tree);
}

TEST(intersectInterval, correctIntersect_returnFalse) {
  inter_t arr[SIZE];
  int level = 0;
  node_t* tree = testLittleTree();
  intersectInterval(tree, 5, 7, &arr, &level);
  ASSERT_EQ(4, arr[0].left_border);
  ASSERT_EQ(8, arr[0].right_border);
  ASSERT_EQ(6, arr[1].left_border);
  ASSERT_EQ(10, arr[1].right_border);
  ASSERT_EQ(2, level);
  deleteTree(tree);
}

TEST(intersectInterval, notIntersect_returnFalse) {
  inter_t arr[SIZE];
  int level = 0;
  node_t* tree = testLittleTree();
  intersectInterval(tree, -5, -1, &arr, &level);
  ASSERT_EQ(0, level);
  deleteTree(tree);
}