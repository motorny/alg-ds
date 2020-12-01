#include "pch.h"

extern "C"
{
#include "tree.h"
}

node_t * Create1NodeTree() {
  node_t* node1 = (node_t*)malloc(sizeof(node_t));
  node1->key = 2;
  node1->father = NULL;
  node1->numberOfNodes = 1;
  node1->right = NULL;
  node1->left = NULL;

  return node1;
}

node_t* Create2NodeLeftTree() {
  node_t* node1 = (node_t*)malloc(sizeof(node_t));
  node_t* node2 = (node_t*)malloc(sizeof(node_t));

  node2->key = 1;
  node2->father = node1;
  node2->numberOfNodes = 1;
  node2->right = NULL;
  node2->left = NULL;

  node1->key = 2;
  node1->father = NULL;
  node1->numberOfNodes = 2;
  node1->right = NULL;
  node1->left = node2;

  return node1;
}

node_t* Create2NodeRightTree() {
  node_t* node1 = (node_t*)malloc(sizeof(node_t));
  node_t* node2 = (node_t*)malloc(sizeof(node_t));

  node2->key = 3;
  node2->father = node1;
  node2->numberOfNodes = 1;
  node2->right = NULL;
  node2->left = NULL;

  node1->key = 2;
  node1->father = NULL;
  node1->numberOfNodes = 2;
  node1->left = NULL;
  node1->right = node2;

  return node1;
}

node_t* Create3NodeTree() {
  node_t* node1 = (node_t*)malloc(sizeof(node_t));
  node_t* node2 = (node_t*)malloc(sizeof(node_t));
  node_t* node3 = (node_t*)malloc(sizeof(node_t));

  node3->key = 1;
  node3->father = node1;
  node3->numberOfNodes = 1;
  node3->right = NULL;
  node3->left = NULL;

  node2->key = 3;
  node2->father = node1;
  node2->numberOfNodes = 1;
  node2->right = NULL;
  node2->left = NULL;

  node1->key = 2;
  node1->father = NULL;
  node1->numberOfNodes = 3;
  node1->left = node3;
  node1->right = node2;

  return node1;
}

TEST(AddToTree_AddToEmptyTree_notCrush) {
  node_t* tree = NULL;
  int res = AddToTree(&tree, tree, 2);

  ASSERT_EQ(res == TRUE, 1);
  ASSERT_EQ(tree->key == 2, 1);
  ASSERT_EQ(tree->left == NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->father == NULL, 1);
  ASSERT_EQ(tree->numberOfNodes == 1, 1);
}

TEST(AddToTree_AddNotToEmptyTree_notCrush) {
  node_t* tree = Create1NodeTree();
  // добавляем уже существующий и проверим что res=false;
  int res = AddToTree(&tree, tree, 2);
  ASSERT_EQ(res == FALSE, 1);

  // добавляем справа
  res = AddToTree(&tree, tree, 3);
  ASSERT_EQ(res == TRUE, 1);
  ASSERT_EQ(tree->right->key == 3, 1);
  ASSERT_EQ(tree->right->left == NULL, 1);
  ASSERT_EQ(tree->right->right == NULL, 1);
  ASSERT_EQ(tree->right->father == tree, 1);
  ASSERT_EQ(tree->right->numberOfNodes == 1, 1);

  ASSERT_EQ(tree->key == 2, 1);
  ASSERT_EQ(tree->left == NULL, 1);
  ASSERT_EQ(tree->right == NULL, 0);
  ASSERT_EQ(tree->father == NULL, 1);
  ASSERT_EQ(tree->numberOfNodes == 2, 1);

  // добавляем слева
  res = AddToTree(&tree, tree, 1);
  ASSERT_EQ(res == TRUE, 1);
  ASSERT_EQ(tree->left->key == 1, 1);
  ASSERT_EQ(tree->left->left == NULL, 1);
  ASSERT_EQ(tree->left->right == NULL, 1);
  ASSERT_EQ(tree->left->father == tree, 1);
  ASSERT_EQ(tree->left->numberOfNodes == 1, 1);

  ASSERT_EQ(tree->key == 2, 1);
  ASSERT_EQ(tree->left == NULL, 0);
  ASSERT_EQ(tree->right == NULL, 0);
  ASSERT_EQ(tree->father == NULL, 1);
  ASSERT_EQ(tree->numberOfNodes == 3, 1);
}



TEST(FindKLowerTree_emptyTree_notCrush) {
  node_t* tree = NULL, *currentNode;

  currentNode = FindKLowerTree(tree, 1, 1);
  ASSERT_EQ(currentNode == NULL, 1);
}

TEST(FindKLowerTree_1NodeTree_notCrush) {
  node_t* tree = Create1NodeTree(), * currentNode;

  // check for each node each 'k'
  currentNode = FindKLowerTree(tree, 1, -1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 2, -1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 3, -1);
  ASSERT_EQ(currentNode == NULL, 1);

  currentNode = FindKLowerTree(tree, 1, 0);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 2, 0);
  ASSERT_EQ(currentNode == tree, 1);
  currentNode = FindKLowerTree(tree, 3, 0);
  ASSERT_EQ(currentNode == NULL, 1);

  currentNode = FindKLowerTree(tree, 1, 1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 2, 1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 3, 1);
  ASSERT_EQ(currentNode == NULL, 1);
}

TEST(FindKLowerTree_2NodeLeft_notCrush) {
  node_t* tree = Create2NodeLeftTree(), * currentNode;

  currentNode = FindKLowerTree(tree, 1, -1);
  ASSERT_EQ(currentNode == tree, 1);
  currentNode = FindKLowerTree(tree, 2, -1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 3, -1);
  ASSERT_EQ(currentNode == NULL, 1);

  currentNode = FindKLowerTree(tree, 1, 0);
  ASSERT_EQ(currentNode == tree->left, 1);
  currentNode = FindKLowerTree(tree, 2, 0);
  ASSERT_EQ(currentNode == tree, 1);
  currentNode = FindKLowerTree(tree, 3, 0);
  ASSERT_EQ(currentNode == NULL, 1);

  currentNode = FindKLowerTree(tree, 1, 1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 2, 1);
  ASSERT_EQ(currentNode == tree->left, 1);
  currentNode = FindKLowerTree(tree, 3, 1);
  ASSERT_EQ(currentNode == NULL, 1);
}

TEST(FindKLowerTree_2NodeRight_notCrush) {
  node_t* tree = Create2NodeRightTree(), * currentNode;

  currentNode = FindKLowerTree(tree, 1, -1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 2, -1);
  ASSERT_EQ(currentNode == tree->right, 1);
  currentNode = FindKLowerTree(tree, 3, -1);
  ASSERT_EQ(currentNode == NULL, 1);

  currentNode = FindKLowerTree(tree, 1, 0);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 2, 0);
  ASSERT_EQ(currentNode == tree, 1);
  currentNode = FindKLowerTree(tree, 3, 0);
  ASSERT_EQ(currentNode == tree->right, 1);

  currentNode = FindKLowerTree(tree, 1, 1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 2, 1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 3, 1);
  ASSERT_EQ(currentNode == tree, 1);
}

TEST(FindKLowerTree_3Node_notCrush) {
  int k = 1;
  node_t* tree = Create3NodeTree(), * currentNode;

  currentNode = FindKLowerTree(tree, 1, -1);
  ASSERT_EQ(currentNode == tree, 1);
  currentNode = FindKLowerTree(tree, 2, -1);
  ASSERT_EQ(currentNode == tree->right, 1);
  currentNode = FindKLowerTree(tree, 3, -1);
  ASSERT_EQ(currentNode == NULL, 1);

  currentNode = FindKLowerTree(tree, 1, 0);
  ASSERT_EQ(currentNode == tree->left, 1);
  currentNode = FindKLowerTree(tree, 2, 0);
  ASSERT_EQ(currentNode == tree, 1);
  currentNode = FindKLowerTree(tree, 3, 0);
  ASSERT_EQ(currentNode == tree->right, 1);

  currentNode = FindKLowerTree(tree, 1, 1);
  ASSERT_EQ(currentNode == NULL, 1);
  currentNode = FindKLowerTree(tree, 2, 1);
  ASSERT_EQ(currentNode == tree->left, 1);
  currentNode = FindKLowerTree(tree, 3, 1);
  ASSERT_EQ(currentNode == tree, 1);
}

TEST(ClearTree_AllVariants_notCrush) {
  node_t* tree = NULL;
  ClearTree(&tree);
  ASSERT_EQ(tree == NULL, 1);
  tree = Create1NodeTree();
  ClearTree(&tree);
  ASSERT_EQ(tree == NULL, 1);
  tree = Create2NodeLeftTree();
  ClearTree(&tree);
  ASSERT_EQ(tree == NULL, 1);
  tree = Create2NodeRightTree();
  ClearTree(&tree);
  ASSERT_EQ(tree == NULL, 1);
  tree = Create3NodeTree();
  ClearTree(&tree);
  ASSERT_EQ(tree == NULL, 1);
}
