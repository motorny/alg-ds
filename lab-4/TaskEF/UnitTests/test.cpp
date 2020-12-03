#include <stdlib.h>
#include "gtest/gtest.h"
#include "../bst.h"

typedef struct node_t {
  struct node_t *left, *right, *parent;
  int key, numOfLeaves, numOfNodes;
} node_t;

typedef struct tree_t {
  node_t *root;
  int numOfNodes;
} tree_t;

TEST(Insert_TreeWithInvalidPtr_Return0) {
  EXPECT_EQ(Insert(NULL, 1), 0);
}

TEST(Insert_EmptyTree_Return1) {
  tree_t* tree = GetTree();

  EXPECT_EQ(Insert(tree, 1), 1);
  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);

  free(tree->root);
  free(tree);
}

TEST(Insert_SuccessfulInsert_Return1) {
  tree_t* tree = GetTree();
  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  EXPECT_EQ(Insert(tree, 2), 1);
  EXPECT_EQ(tree->numOfNodes, 2);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_FALSE(tree->root->right == (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 2);

  EXPECT_EQ(tree->root->right->key, 2);
  EXPECT_EQ(tree->root->right->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->parent, &n1);
  EXPECT_EQ(tree->root->right->numOfNodes, 1);

  free(tree->root->right);
  free(tree);
}

TEST(Insert_UnsuccessfulInsert_ReturnMinus1) {
  tree_t* tree = GetTree();
  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  EXPECT_EQ(Insert(tree, 1), -1);
  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);

  free(tree);
}

TEST(Delete_TreeWithInvalidPtr_Return0) {
  EXPECT_EQ(Delete(NULL, 1), 0);
}

TEST(Delete_EmptyTree_ReturnMinus1) {
  tree_t* tree = GetTree();

  EXPECT_EQ(Delete(tree, 1), -1);
  EXPECT_EQ(tree->numOfNodes, 0);
  EXPECT_EQ(tree->root, (node_t*)NULL);

  free(tree);
}

TEST(Delete_TryToDeleteUnexistedElement_ReturnMinus1) {
  tree_t* tree = GetTree();
  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  EXPECT_EQ(Delete(tree, 2), -1);
  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);

  free(tree);
}

TEST(Delete_DeleteElementWithNullChilds_Return1) {
  tree_t* tree = GetTree();
  node_t *n1 = (node_t*)malloc(sizeof(node_t));
  n1->key = 1;
  n1->left = NULL;
  n1->right = NULL;
  n1->parent = NULL;
  n1->numOfLeaves = 0;
  n1->numOfNodes = 1;

  tree->root = n1;
  tree->numOfNodes = 1;

  EXPECT_EQ(Delete(tree, 1), 1);
  EXPECT_EQ(tree->numOfNodes, 0);
  EXPECT_EQ(tree->root, (node_t*)NULL);

  free(tree);
}

TEST(Delete_DeleteElementWith1NonNullChild_Return1) {
  tree_t* tree = GetTree();

  node_t* n1 = (node_t*)malloc(sizeof(node_t));
  n1->key = 1;
  n1->left = NULL;
  n1->parent = NULL;
  n1->numOfLeaves = 0;
  n1->numOfNodes = 2;

  node_t n2;
  n2.key = 2;
  n2.left = NULL;
  n2.right = NULL;
  n2.numOfLeaves = 0;
  n2.numOfNodes = 1;

  n1->right = &n2;
  n2.parent = n1;

  tree->root = n1;
  tree->numOfNodes = 2;

  EXPECT_EQ(Delete(tree, 1), 1);
  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root, &n2);
  EXPECT_EQ(tree->root->key, 2);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);

  free(tree);
}

TEST(Delete_DeleteElementWith2NonNullChilds_Return1) {
  tree_t* tree = GetTree();

  node_t n2;
  n2.key = 2;
  n2.parent = NULL;
  n2.numOfLeaves = 0;
  n2.numOfNodes = 3;

  node_t *n1 = (node_t*)malloc(sizeof(node_t));
  n1->key = 1;
  n1->left = NULL;
  n1->right = NULL;
  n1->numOfLeaves = 0;
  n1->numOfNodes = 1;

  node_t n3;
  n3.key = 3;
  n3.left = NULL;
  n3.right = NULL;
  n3.numOfLeaves = 0;
  n3.numOfNodes = 1;

  n2.left = n1;
  n2.right = &n3;
  n1->parent = &n2;
  n3.parent = &n2;

  tree->root = &n2;
  tree->numOfNodes = 3;

  EXPECT_EQ(Delete(tree, 2), 1);
  EXPECT_EQ(tree->numOfNodes, 2);
  EXPECT_EQ(tree->root, &n2);

  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, &n3);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 2);

  EXPECT_EQ(tree->root->right->key, 3);
  EXPECT_EQ(tree->root->right->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->parent, &n2);
  EXPECT_EQ(tree->root->right->numOfNodes, 1);

  free(tree);
}

TEST(Find_TreeWithInvalidPtr_Return0) {
  EXPECT_EQ(Find(NULL, 1), 0);
}

TEST(Find_EmptyTree_ReturnMinus1) {
  tree_t* tree = GetTree();

  EXPECT_EQ(Find(tree, 1), -1);
  EXPECT_EQ(tree->numOfNodes, 0);
  EXPECT_EQ(tree->root, (node_t*)NULL);

  free(tree);
}

TEST(Find_FindExisted_Return1) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  EXPECT_EQ(Find(tree, 1), 1);
  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root, &n1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);

  free(tree);
}

TEST(Find_FindUnexisted_ReturnMinus1) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  EXPECT_EQ(Find(tree, 1 + 1), -1);
  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root, &n1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);

  free(tree);
}

TEST(DeleteTree_TreeWithInvalidPtr_CorrectProcessing) {
  DeleteTree(NULL);
}

TEST(DeleteTree_EmptyTree_CorrectProcessing) {
  tree_t* tree = GetTree();

  DeleteTree(tree);
}

TEST(Delete_CorrectTree_CorrectProcessing) {
  tree_t* tree = GetTree();

  node_t *n1 = (node_t*)malloc(sizeof(node_t));
  n1->key = 1;
  n1->left = NULL;
  n1->right = NULL;
  n1->parent = NULL;
  n1->numOfLeaves = 0;
  n1->numOfNodes = 1;

  tree->root = n1;
  tree->numOfNodes = 1;

  DeleteTree(tree);
}

TEST(PrintKeys_TreeWithInvalidPtr_CorrectProcessing) {
  PrintKeys(NULL);
}

TEST(PrintKeys_EmptyTree_CorrectProcessing) {
  tree_t* tree = GetTree();

  PrintKeys(tree);
  EXPECT_EQ(tree->numOfNodes, 0);
  EXPECT_EQ(tree->root, (node_t*)NULL);

  free(tree);
}

TEST(PrintKeys_CorrectTree_CorrectProcessing) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  PrintKeys(tree);

  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root, &n1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);

  free(tree);
}

TEST(PrintNumOfLeaves_TreeWithInvalidPtr_CorrectProcessing) {
  PrintNumOfLeaves(NULL);
}

TEST(PrintNumOfLeaves_EmptyTree_CorrectProcessing) {
  tree_t* tree = GetTree();

  PrintNumOfLeaves(tree);
  EXPECT_EQ(tree->numOfNodes, 0);
  EXPECT_EQ(tree->root, (node_t*)NULL);

  free(tree);
}

TEST(PrintNumOfLeaves_CorrectTree_CorrectProcessing) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  PrintNumOfLeaves(tree);

  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root, &n1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);
  EXPECT_EQ(tree->root->numOfLeaves, 0);

  free(tree);
}

TEST(PrintNumOfLeaves_NodeWith1Leaf_CorrectProcessing) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 2;

  node_t n2;
  n2.key = 2;
  n2.left = NULL;
  n2.right = NULL;
  n2.numOfLeaves = 0;
  n2.numOfNodes = 1;

  n1.right = &n2;
  n2.parent = &n1;

  tree->root = &n1;
  tree->numOfNodes = 2;

  PrintNumOfLeaves(tree);

  EXPECT_EQ(tree->numOfNodes, 2);
  EXPECT_EQ(tree->root, &n1);

  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, &n2);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 2);
  EXPECT_EQ(tree->root->numOfLeaves, 1);

  EXPECT_EQ(tree->root->right->key, 2);
  EXPECT_EQ(tree->root->right->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->parent, &n1);
  EXPECT_EQ(tree->root->right->numOfNodes, 1);
  EXPECT_EQ(tree->root->right->numOfLeaves, 0);

  free(tree);
}

TEST(PrintNumOfLeaves_NodeWith2Leaves_CorrectProcessing) {
  tree_t* tree = GetTree();

  node_t n2;
  n2.key = 2;
  n2.parent = NULL;
  n2.numOfLeaves = 0;
  n2.numOfNodes = 3;

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  node_t n3;
  n3.key = 3;
  n3.left = NULL;
  n3.right = NULL;
  n3.numOfLeaves = 0;
  n3.numOfNodes = 1;

  n2.left = &n1;
  n2.right = &n3;
  n1.parent = &n2;
  n3.parent = &n2;

  tree->root = &n2;
  tree->numOfNodes = 3;

  PrintNumOfLeaves(tree);

  EXPECT_EQ(tree->numOfNodes, 3);
  EXPECT_EQ(tree->root, &n2);

  EXPECT_EQ(tree->root->key, 2);
  EXPECT_EQ(tree->root->left, &n1);
  EXPECT_EQ(tree->root->right, &n3);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 3);
  EXPECT_EQ(tree->root->numOfLeaves, 2);

  EXPECT_EQ(tree->root->left->key, 1);
  EXPECT_EQ(tree->root->left->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->left->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->left->parent, &n2);
  EXPECT_EQ(tree->root->left->numOfNodes, 1);
  EXPECT_EQ(tree->root->left->numOfLeaves, 0);

  EXPECT_EQ(tree->root->right->key, 3);
  EXPECT_EQ(tree->root->right->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->parent, &n2);
  EXPECT_EQ(tree->root->right->numOfNodes, 1);
  EXPECT_EQ(tree->root->right->numOfLeaves, 0);

  free(tree);
}

TEST(KeyKLess_TreeWithInvalidPtr_Return0) {
  EXPECT_EQ(KeyKLess(NULL, 1, 1), 0);
}

TEST(KeyKLess_EmptyTree_ReturnMinus1) {
  tree_t* tree = GetTree();

  EXPECT_EQ(KeyKLess(tree, 1, 1), -1);
  EXPECT_EQ(tree->numOfNodes, 0);
  EXPECT_EQ(tree->root, (node_t*)NULL);

  free(tree);
}

TEST(PrintNumOfLeaves_UnexistedKey_ReturnMinus1) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  EXPECT_EQ(KeyKLess(tree, 2, 1), -1);
  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root, &n1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);
  EXPECT_EQ(tree->root->numOfLeaves, 0);

  free(tree);
}

TEST(PrintNumOfLeaves_0Less_Return1) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  tree->root = &n1;
  tree->numOfNodes = 1;

  EXPECT_EQ(KeyKLess(tree, 1, 0), 1);
  EXPECT_EQ(tree->numOfNodes, 1);
  EXPECT_EQ(tree->root, &n1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 1);
  EXPECT_EQ(tree->root->numOfLeaves, 0);

  free(tree);
}

TEST(PrintNumOfLeaves_GoUpFromKey_Return1) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.parent = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 2;

  node_t n2;
  n2.key = 2;
  n2.left = NULL;
  n2.right = NULL;
  n2.numOfLeaves = 0;
  n2.numOfNodes = 1;

  n1.right = &n2;
  n2.parent = &n1;

  tree->root = &n1;
  tree->numOfNodes = 2;

  EXPECT_EQ(KeyKLess(tree, 2, 1), 1);

  EXPECT_EQ(tree->numOfNodes, 2);
  EXPECT_EQ(tree->root, &n1);

  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right, &n2);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 2);
  EXPECT_EQ(tree->root->numOfLeaves, 0);

  EXPECT_EQ(tree->root->right->key, 2);
  EXPECT_EQ(tree->root->right->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->right->parent, &n1);
  EXPECT_EQ(tree->root->right->numOfNodes, 1);
  EXPECT_EQ(tree->root->right->numOfLeaves, 0);

  free(tree);
}

TEST(PrintNumOfLeaves_GoDownFromKey_Return1) {
  tree_t* tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.numOfLeaves = 0;
  n1.numOfNodes = 1;

  node_t n2;
  n2.key = 2;
  n2.right = NULL;
  n2.parent = NULL;
  n2.numOfLeaves = 0;
  n2.numOfNodes = 2;

  n2.left = &n1;
  n1.parent = &n2;

  tree->root = &n2;
  tree->numOfNodes = 2;

  EXPECT_EQ(KeyKLess(tree, 2, 1), 1);

  EXPECT_EQ(tree->numOfNodes, 2);
  EXPECT_EQ(tree->root, &n2);

  EXPECT_EQ(tree->root->key, 2);
  EXPECT_EQ(tree->root->left, &n1);
  EXPECT_EQ(tree->root->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->parent, (node_t*)NULL);
  EXPECT_EQ(tree->root->numOfNodes, 2);
  EXPECT_EQ(tree->root->numOfLeaves, 0);

  EXPECT_EQ(tree->root->left->key, 1);
  EXPECT_EQ(tree->root->left->left, (node_t*)NULL);
  EXPECT_EQ(tree->root->left->right, (node_t*)NULL);
  EXPECT_EQ(tree->root->left->parent, &n2);
  EXPECT_EQ(tree->root->left->numOfNodes, 1);
  EXPECT_EQ(tree->root->left->numOfLeaves, 0);

  free(tree);
}
