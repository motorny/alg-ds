#include "pch.h"

extern "C"
{
#include "23plus_trees.h"
}

ttTree_t* Create1NodeTtTree(double elem1) {
  ttTree_t* node1 = (ttTree_t*)malloc(sizeof(ttTree_t));

  node1->isLeaf = 1;
  node1->data = elem1;

  node1->childsCnt = 0;
  node1->leftNum = node1->rightNum = 0;
  node1->maxSubtreeData = elem1;
  node1->parent = NULL;
  node1->right = NULL;
  node1->middle = NULL;
  node1->left = NULL;

  return node1;
}

ttTree_t* Create2NodeTtTree(double elem1, double elem2) {
  ttTree_t* node1 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* node2 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* parentNode = (ttTree_t*)malloc(sizeof(ttTree_t));

  parentNode->isLeaf = 0;
  parentNode->rightNum = 0;
  parentNode->data = 0;
  parentNode->parent = parentNode->right = NULL;
  parentNode->maxSubtreeData = elem2;
  parentNode->leftNum = elem1;
  parentNode->left = node1;
  parentNode->middle = node2;
  parentNode->childsCnt = 2;

  node1->isLeaf = 1;
  node1->data = elem1;
  node1->childsCnt = 0;
  node1->leftNum = node1->rightNum = 0;
  node1->maxSubtreeData = elem1;
  node1->parent = parentNode;
  node1->right = NULL;
  node1->middle = NULL;
  node1->left = NULL;

  node2->isLeaf = 1;
  node2->data = elem2;
  node2->childsCnt = 0;
  node2->leftNum = node2->rightNum = 0;
  node2->maxSubtreeData = elem2;
  node2->parent = parentNode;
  node2->right = NULL;
  node2->middle = NULL;
  node2->left = NULL;

  return parentNode;
}

ttTree_t* Create3NodeTtTree(double elem1, double elem2, double elem3) {
  ttTree_t* node1 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* node2 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* node3 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* parentNode = (ttTree_t*)malloc(sizeof(ttTree_t));

  parentNode->isLeaf = 0;
  parentNode->data = 0;
  parentNode->parent = NULL;
  parentNode->maxSubtreeData = elem3;
  parentNode->rightNum = elem2;
  parentNode->leftNum = elem1;
  parentNode->left = node1;
  parentNode->middle = node2;
  parentNode->right = node3;
  parentNode->childsCnt = 3;

  node1->isLeaf = 1;
  node1->data = elem1;
  node1->childsCnt = 0;
  node1->leftNum = node1->rightNum = 0;
  node1->maxSubtreeData = elem1;
  node1->parent = parentNode;
  node1->right = NULL;
  node1->middle = NULL;
  node1->left = NULL;

  node2->isLeaf = 1;
  node2->data = elem2;
  node2->childsCnt = 0;
  node2->leftNum = node2->rightNum = 0;
  node2->maxSubtreeData = elem2;
  node2->parent = parentNode;
  node2->right = NULL;
  node2->middle = NULL;
  node2->left = NULL;

  node3->isLeaf = 1;
  node3->data = elem3;
  node3->childsCnt = 0;
  node3->leftNum = node3->rightNum = 0;
  node3->maxSubtreeData = elem3;
  node3->parent = parentNode;
  node3->right = NULL;
  node3->middle = NULL;
  node3->left = NULL;

  return parentNode;
}

ttTree_t* Create4NodeTtTree(double elem1, double elem2, double elem3, double elem4) {
  ttTree_t* node1 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* node2 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* node3 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* node4 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* parentNode = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* subTree1 = (ttTree_t*)malloc(sizeof(ttTree_t));
  ttTree_t* subTree2 = (ttTree_t*)malloc(sizeof(ttTree_t));

  parentNode->isLeaf = 0;
  parentNode->data = 0;
  parentNode->parent = NULL;
  parentNode->maxSubtreeData = elem4;
  parentNode->rightNum = 0;
  parentNode->leftNum = elem2;
  parentNode->left = subTree1;
  parentNode->middle = subTree2;
  parentNode->right = NULL;
  parentNode->childsCnt = 2;

  subTree1->isLeaf = 0;
  subTree1->data = 0;
  subTree1->parent = parentNode;
  subTree1->maxSubtreeData = elem2;
  subTree1->rightNum = 0;
  subTree1->leftNum = elem1;
  subTree1->left = node1;
  subTree1->middle = node2;
  subTree1->right = NULL;
  subTree1->childsCnt = 2;

  subTree2->isLeaf = 0;
  subTree2->data = 0;
  subTree2->parent = parentNode;
  subTree2->maxSubtreeData = elem4;
  subTree2->rightNum = 0;
  subTree2->leftNum = elem3;
  subTree2->left = node3;
  subTree2->middle = node4;
  subTree2->right = NULL;
  subTree2->childsCnt = 2;

  node1->isLeaf = 1;
  node1->data = elem1;
  node1->childsCnt = 0;
  node1->leftNum = node1->rightNum = 0;
  node1->maxSubtreeData = elem1;
  node1->parent = subTree1;
  node1->right = NULL;
  node1->middle = NULL;
  node1->left = NULL;

  node2->isLeaf = 1;
  node2->data = elem2;
  node2->childsCnt = 0;
  node2->leftNum = node2->rightNum = 0;
  node2->maxSubtreeData = elem2;
  node2->parent = subTree1;
  node2->right = NULL;
  node2->middle = NULL;
  node2->left = NULL;

  node3->isLeaf = 1;
  node3->data = elem3;
  node3->childsCnt = 0;
  node3->leftNum = node3->rightNum = 0;
  node3->maxSubtreeData = elem3;
  node3->parent = subTree2;
  node3->right = NULL;
  node3->middle = NULL;
  node3->left = NULL;

  node4->isLeaf = 1;
  node4->data = elem4;
  node4->childsCnt = 0;
  node4->leftNum = node4->rightNum = 0;
  node4->maxSubtreeData = elem4;
  node4->parent = subTree2;
  node4->right = NULL;
  node4->middle = NULL;
  node4->left = NULL;

  return parentNode;
}

/*******************/
/****    ADD    ****/
/*******************/

TEST(AddToEmptyTree, AddToTtTree_AddToEmptyTtTree_notCrush) {
  ttTree_t* tree = NULL;
  int res = AddToTTTree(&tree, 2);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 1, 1);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->childsCnt == 0, 1);
  ASSERT_EQ(tree->leftNum == 0, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 2, 1);
  ASSERT_EQ(tree->left == NULL, 1);
  ASSERT_EQ(tree->middle == NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
}

TEST(AddToOneElemTree, AddToTtTree_AddToOneElementTtTreeExistedElem_notCrush) {
  ttTree_t* tree;
  int res;

  // add already existed tree
  tree = Create1NodeTtTree(2);
  res = AddToTTTree(&tree, 2);

  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(tree->isLeaf == 1, 1);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->childsCnt == 0, 1);
  ASSERT_EQ(tree->leftNum == 0, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 2, 1);
  ASSERT_EQ(tree->left == NULL, 1);
  ASSERT_EQ(tree->middle == NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
}

TEST(AddToOneElemTree, AddToTtTree_AddToOneElementTtTreeSmallerElem_notCrush) {
  ttTree_t* tree, * parentNode, * node1, * node2;
  int res;

  // add smaller element in tree
  tree = Create1NodeTtTree(2);
  res = AddToTTTree(&tree, 1);
  parentNode = tree;
  node1 = tree->left;
  node2 = tree->middle;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 2, 1);
  ASSERT_EQ(parentNode->leftNum == 1, 1);
  ASSERT_EQ(parentNode->rightNum == 0, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 2, 1);
  ASSERT_EQ(parentNode->left == node1, 1);
  ASSERT_EQ(parentNode->middle == node2, 1);
  ASSERT_EQ(parentNode->right == NULL, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 1, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 1, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == parentNode, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 2, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 2, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == parentNode, 1);
}

TEST(AddToOneElemTree, AddToTtTree_AddToOneElementTtTreeBiggerElem_notCrush) {
  ttTree_t* tree, * parentNode, * node1, * node2;
  int res;

  // add bigger element in tree
  tree = Create1NodeTtTree(2);
  res = AddToTTTree(&tree, 3);
  parentNode = tree;
  node1 = tree->left;
  node2 = tree->middle;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 2, 1);
  ASSERT_EQ(parentNode->leftNum == 2, 1);
  ASSERT_EQ(parentNode->rightNum == 0, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 3, 1);
  ASSERT_EQ(parentNode->left == node1, 1);
  ASSERT_EQ(parentNode->middle == node2, 1);
  ASSERT_EQ(parentNode->right == NULL, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 2, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 2, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == parentNode, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 3, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 3, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == parentNode, 1);
}

TEST(AddToTwoElemTree, AddToTtTree_AddToTwoElementsTtTreeExistedElem_notCrush) {
  ttTree_t* tree;
  int res;

  // add already existed tree
  tree = Create2NodeTtTree(2, 4);
  res = AddToTTTree(&tree, 2);

  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 2, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 4, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
}

TEST(AddToTwoElemTree, AddToTtTree_AddToTwoElementTtTreeSmallerElem_notCrush) {
  ttTree_t* tree, * parentNode, * node1, * node2, * node3;
  int res;

  // add smaller element in tree
  tree = Create2NodeTtTree(2, 4);
  res = AddToTTTree(&tree, 1);
  parentNode = tree;
  node1 = tree->left;
  node2 = tree->middle;
  node3 = tree->right;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 3, 1);
  ASSERT_EQ(parentNode->leftNum == 1, 1);
  ASSERT_EQ(parentNode->rightNum == 2, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 4, 1);
  ASSERT_EQ(parentNode->left == node1, 1);
  ASSERT_EQ(parentNode->middle == node2, 1);
  ASSERT_EQ(parentNode->right == node3, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 1, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 1, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == parentNode, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 2, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 2, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == parentNode, 1);

  ASSERT_EQ(node3->isLeaf == 1, 1);
  ASSERT_EQ(node3->data == 4, 1);
  ASSERT_EQ(node3->childsCnt == 0, 1);
  ASSERT_EQ(node3->leftNum == 0, 1);
  ASSERT_EQ(node3->rightNum == 0, 1);
  ASSERT_EQ(node3->maxSubtreeData == 4, 1);
  ASSERT_EQ(node3->left == NULL, 1);
  ASSERT_EQ(node3->middle == NULL, 1);
  ASSERT_EQ(node3->right == NULL, 1);
  ASSERT_EQ(node3->parent == parentNode, 1);
}

TEST(AddToTwoElemTree, AddToTtTree_AddToTwoElementTtTreeMediumElem_notCrush) {
  ttTree_t* tree, * parentNode, * node1, * node2, * node3;
  int res;

  // add medium element in tree
  tree = Create2NodeTtTree(2, 4);
  res = AddToTTTree(&tree, 3);
  parentNode = tree;
  node1 = tree->left;
  node2 = tree->middle;
  node3 = tree->right;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 3, 1);
  ASSERT_EQ(parentNode->leftNum == 2, 1);
  ASSERT_EQ(parentNode->rightNum == 3, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 4, 1);
  ASSERT_EQ(parentNode->left == node1, 1);
  ASSERT_EQ(parentNode->middle == node2, 1);
  ASSERT_EQ(parentNode->right == node3, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 2, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 2, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == parentNode, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 3, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 3, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == parentNode, 1);

  ASSERT_EQ(node3->isLeaf == 1, 1);
  ASSERT_EQ(node3->data == 4, 1);
  ASSERT_EQ(node3->childsCnt == 0, 1);
  ASSERT_EQ(node3->leftNum == 0, 1);
  ASSERT_EQ(node3->rightNum == 0, 1);
  ASSERT_EQ(node3->maxSubtreeData == 4, 1);
  ASSERT_EQ(node3->left == NULL, 1);
  ASSERT_EQ(node3->middle == NULL, 1);
  ASSERT_EQ(node3->right == NULL, 1);
  ASSERT_EQ(node3->parent == parentNode, 1);
}

TEST(AddToTwoElemTree, AddToTtTree_AddToTwoElementTtTreeBiggerElem_notCrush) {
  ttTree_t* tree, * parentNode, * node1, * node2, * node3;
  int res;

  // add bigger element in tree
  tree = Create2NodeTtTree(2, 4);
  res = AddToTTTree(&tree, 5);
  parentNode = tree;
  node1 = tree->left;
  node2 = tree->middle;
  node3 = tree->right;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 3, 1);
  ASSERT_EQ(parentNode->leftNum == 2, 1);
  ASSERT_EQ(parentNode->rightNum == 4, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 5, 1);
  ASSERT_EQ(parentNode->left == node1, 1);
  ASSERT_EQ(parentNode->middle == node2, 1);
  ASSERT_EQ(parentNode->right == node3, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 2, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 2, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == parentNode, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 4, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 4, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == parentNode, 1);

  ASSERT_EQ(node3->isLeaf == 1, 1);
  ASSERT_EQ(node3->data == 5, 1);
  ASSERT_EQ(node3->childsCnt == 0, 1);
  ASSERT_EQ(node3->leftNum == 0, 1);
  ASSERT_EQ(node3->rightNum == 0, 1);
  ASSERT_EQ(node3->maxSubtreeData == 5, 1);
  ASSERT_EQ(node3->left == NULL, 1);
  ASSERT_EQ(node3->middle == NULL, 1);
  ASSERT_EQ(node3->right == NULL, 1);
  ASSERT_EQ(node3->parent == parentNode, 1);
}

TEST(AddToThreeElemTree, AddToTtTree_AddToThreeElementsTtTreeExistedElem_notCrush) {
  ttTree_t* tree;
  int res;

  // add already existed tree
  tree = Create3NodeTtTree(2, 4, 6);
  res = AddToTTTree(&tree, 2);

  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 3, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 4, 1);
  ASSERT_EQ(tree->maxSubtreeData == 6, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right != NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
}

TEST(AddToThreeElemTree, AddToTtTree_AddToThreeElementTtTreeSmallElem_notCrush) {
  ttTree_t* tree, * parentNode, * subParent1, * subParent2,
    * node1, * node2, * node3, * node4;
  int res;

  // add smaller element in tree
  tree = Create3NodeTtTree(2, 4, 6);
  res = AddToTTTree(&tree, 3);
  parentNode = tree;
  subParent1 = parentNode->left;
  subParent2 = parentNode->middle;
  node1 = subParent1->left;
  node2 = subParent1->middle;
  node3 = subParent2->left;
  node4 = subParent2->middle;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 2, 1);
  ASSERT_EQ(parentNode->leftNum == 3, 1);
  ASSERT_EQ(parentNode->rightNum == 0, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 6, 1);
  ASSERT_EQ(parentNode->left == subParent1, 1);
  ASSERT_EQ(parentNode->middle == subParent2, 1);
  ASSERT_EQ(parentNode->right == NULL, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(subParent1->isLeaf == 0, 1);
  ASSERT_EQ(subParent1->data == 0, 1);
  ASSERT_EQ(subParent1->childsCnt == 2, 1);
  ASSERT_EQ(subParent1->leftNum == 2, 1);
  ASSERT_EQ(subParent1->rightNum == 0, 1);
  ASSERT_EQ(subParent1->maxSubtreeData == 3, 1);
  ASSERT_EQ(subParent1->left == node1, 1);
  ASSERT_EQ(subParent1->middle == node2, 1);
  ASSERT_EQ(subParent1->right == NULL, 1);
  ASSERT_EQ(subParent1->parent == parentNode, 1);

  ASSERT_EQ(subParent2->isLeaf == 0, 1);
  ASSERT_EQ(subParent2->data == 0, 1);
  ASSERT_EQ(subParent2->childsCnt == 2, 1);
  ASSERT_EQ(subParent2->leftNum == 4, 1);
  ASSERT_EQ(subParent2->rightNum == 0, 1);
  ASSERT_EQ(subParent2->maxSubtreeData == 6, 1);
  ASSERT_EQ(subParent2->left == node3, 1);
  ASSERT_EQ(subParent2->middle == node4, 1);
  ASSERT_EQ(subParent2->right == NULL, 1);
  ASSERT_EQ(subParent2->parent == parentNode, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 2, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 2, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == subParent1, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 3, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 3, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == subParent1, 1);

  ASSERT_EQ(node3->isLeaf == 1, 1);
  ASSERT_EQ(node3->data == 4, 1);
  ASSERT_EQ(node3->childsCnt == 0, 1);
  ASSERT_EQ(node3->leftNum == 0, 1);
  ASSERT_EQ(node3->rightNum == 0, 1);
  ASSERT_EQ(node3->maxSubtreeData == 4, 1);
  ASSERT_EQ(node3->left == NULL, 1);
  ASSERT_EQ(node3->middle == NULL, 1);
  ASSERT_EQ(node3->right == NULL, 1);
  ASSERT_EQ(node3->parent == subParent2, 1);

  ASSERT_EQ(node4->isLeaf == 1, 1);
  ASSERT_EQ(node4->data == 6, 1);
  ASSERT_EQ(node4->childsCnt == 0, 1);
  ASSERT_EQ(node4->leftNum == 0, 1);
  ASSERT_EQ(node4->rightNum == 0, 1);
  ASSERT_EQ(node4->maxSubtreeData == 6, 1);
  ASSERT_EQ(node4->left == NULL, 1);
  ASSERT_EQ(node4->middle == NULL, 1);
  ASSERT_EQ(node4->right == NULL, 1);
  ASSERT_EQ(node4->parent == subParent2, 1);
}

TEST(AddToThreeElemTree, AddToTtTree_AddToThreeElementTtTreeBigElem_notCrush) {
  ttTree_t* tree, * parentNode, * subParent1, * subParent2,
    * node1, * node2, * node3, * node4;
  int res;

  // add bigger element in tree
  tree = Create3NodeTtTree(2, 3, 6);
  res = AddToTTTree(&tree, 4);
  parentNode = tree;
  subParent1 = parentNode->left;
  subParent2 = parentNode->middle;
  node1 = subParent1->left;
  node2 = subParent1->middle;
  node3 = subParent2->left;
  node4 = subParent2->middle;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 2, 1);
  ASSERT_EQ(parentNode->leftNum == 3, 1);
  ASSERT_EQ(parentNode->rightNum == 0, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 6, 1);
  ASSERT_EQ(parentNode->left == subParent1, 1);
  ASSERT_EQ(parentNode->middle == subParent2, 1);
  ASSERT_EQ(parentNode->right == NULL, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(subParent1->isLeaf == 0, 1);
  ASSERT_EQ(subParent1->data == 0, 1);
  ASSERT_EQ(subParent1->childsCnt == 2, 1);
  ASSERT_EQ(subParent1->leftNum == 2, 1);
  ASSERT_EQ(subParent1->rightNum == 0, 1);
  ASSERT_EQ(subParent1->maxSubtreeData == 3, 1);
  ASSERT_EQ(subParent1->left == node1, 1);
  ASSERT_EQ(subParent1->middle == node2, 1);
  ASSERT_EQ(subParent1->right == NULL, 1);
  ASSERT_EQ(subParent1->parent == parentNode, 1);

  ASSERT_EQ(subParent2->isLeaf == 0, 1);
  ASSERT_EQ(subParent2->data == 0, 1);
  ASSERT_EQ(subParent2->childsCnt == 2, 1);
  ASSERT_EQ(subParent2->leftNum == 4, 1);
  ASSERT_EQ(subParent2->rightNum == 0, 1);
  ASSERT_EQ(subParent2->maxSubtreeData == 6, 1);
  ASSERT_EQ(subParent2->left == node3, 1);
  ASSERT_EQ(subParent2->middle == node4, 1);
  ASSERT_EQ(subParent2->right == NULL, 1);
  ASSERT_EQ(subParent2->parent == parentNode, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 2, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 2, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == subParent1, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 3, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 3, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == subParent1, 1);

  ASSERT_EQ(node3->isLeaf == 1, 1);
  ASSERT_EQ(node3->data == 4, 1);
  ASSERT_EQ(node3->childsCnt == 0, 1);
  ASSERT_EQ(node3->leftNum == 0, 1);
  ASSERT_EQ(node3->rightNum == 0, 1);
  ASSERT_EQ(node3->maxSubtreeData == 4, 1);
  ASSERT_EQ(node3->left == NULL, 1);
  ASSERT_EQ(node3->middle == NULL, 1);
  ASSERT_EQ(node3->right == NULL, 1);
  ASSERT_EQ(node3->parent == subParent2, 1);

  ASSERT_EQ(node4->isLeaf == 1, 1);
  ASSERT_EQ(node4->data == 6, 1);
  ASSERT_EQ(node4->childsCnt == 0, 1);
  ASSERT_EQ(node4->leftNum == 0, 1);
  ASSERT_EQ(node4->rightNum == 0, 1);
  ASSERT_EQ(node4->maxSubtreeData == 6, 1);
  ASSERT_EQ(node4->left == NULL, 1);
  ASSERT_EQ(node4->middle == NULL, 1);
  ASSERT_EQ(node4->right == NULL, 1);
  ASSERT_EQ(node4->parent == subParent2, 1);
}

TEST(AddToThreeElemTree, AddToTtTree_AddToThreeElementTtTreeTheSmallestElem_notCrush) {
  ttTree_t* tree, * parentNode, * subParent1, * subParent2,
    * node1, * node2, * node3, * node4;
  int res;

  // add the smallest element in tree
  tree = Create3NodeTtTree(3, 4, 6);
  res = AddToTTTree(&tree, 2);
  parentNode = tree;
  subParent1 = parentNode->left;
  subParent2 = parentNode->middle;
  node1 = subParent1->left;
  node2 = subParent1->middle;
  node3 = subParent2->left;
  node4 = subParent2->middle;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 2, 1);
  ASSERT_EQ(parentNode->leftNum == 3, 1);
  ASSERT_EQ(parentNode->rightNum == 0, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 6, 1);
  ASSERT_EQ(parentNode->left == subParent1, 1);
  ASSERT_EQ(parentNode->middle == subParent2, 1);
  ASSERT_EQ(parentNode->right == NULL, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(subParent1->isLeaf == 0, 1);
  ASSERT_EQ(subParent1->data == 0, 1);
  ASSERT_EQ(subParent1->childsCnt == 2, 1);
  ASSERT_EQ(subParent1->leftNum == 2, 1);
  ASSERT_EQ(subParent1->rightNum == 0, 1);
  ASSERT_EQ(subParent1->maxSubtreeData == 3, 1);
  ASSERT_EQ(subParent1->left == node1, 1);
  ASSERT_EQ(subParent1->middle == node2, 1);
  ASSERT_EQ(subParent1->right == NULL, 1);
  ASSERT_EQ(subParent1->parent == parentNode, 1);

  ASSERT_EQ(subParent2->isLeaf == 0, 1);
  ASSERT_EQ(subParent2->data == 0, 1);
  ASSERT_EQ(subParent2->childsCnt == 2, 1);
  ASSERT_EQ(subParent2->leftNum == 4, 1);
  ASSERT_EQ(subParent2->rightNum == 0, 1);
  ASSERT_EQ(subParent2->maxSubtreeData == 6, 1);
  ASSERT_EQ(subParent2->left == node3, 1);
  ASSERT_EQ(subParent2->middle == node4, 1);
  ASSERT_EQ(subParent2->right == NULL, 1);
  ASSERT_EQ(subParent2->parent == parentNode, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 2, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 2, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == subParent1, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 3, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 3, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == subParent1, 1);

  ASSERT_EQ(node3->isLeaf == 1, 1);
  ASSERT_EQ(node3->data == 4, 1);
  ASSERT_EQ(node3->childsCnt == 0, 1);
  ASSERT_EQ(node3->leftNum == 0, 1);
  ASSERT_EQ(node3->rightNum == 0, 1);
  ASSERT_EQ(node3->maxSubtreeData == 4, 1);
  ASSERT_EQ(node3->left == NULL, 1);
  ASSERT_EQ(node3->middle == NULL, 1);
  ASSERT_EQ(node3->right == NULL, 1);
  ASSERT_EQ(node3->parent == subParent2, 1);

  ASSERT_EQ(node4->isLeaf == 1, 1);
  ASSERT_EQ(node4->data == 6, 1);
  ASSERT_EQ(node4->childsCnt == 0, 1);
  ASSERT_EQ(node4->leftNum == 0, 1);
  ASSERT_EQ(node4->rightNum == 0, 1);
  ASSERT_EQ(node4->maxSubtreeData == 6, 1);
  ASSERT_EQ(node4->left == NULL, 1);
  ASSERT_EQ(node4->middle == NULL, 1);
  ASSERT_EQ(node4->right == NULL, 1);
  ASSERT_EQ(node4->parent == subParent2, 1);
}

TEST(AddToThreeElemTree, AddToTtTree_AddToThreeElementTtTreeTheBiggestElem_notCrush) {
  ttTree_t* tree, * parentNode, * subParent1, * subParent2,
    * node1, * node2, * node3, * node4;
  int res;

  // add the biggest element in tree
  tree = Create3NodeTtTree(2, 3, 4);
  res = AddToTTTree(&tree, 6);
  parentNode = tree;
  subParent1 = parentNode->left;
  subParent2 = parentNode->middle;
  node1 = subParent1->left;
  node2 = subParent1->middle;
  node3 = subParent2->left;
  node4 = subParent2->middle;

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(parentNode->isLeaf == 0, 1);
  ASSERT_EQ(parentNode->data == 0, 1);
  ASSERT_EQ(parentNode->childsCnt == 2, 1);
  ASSERT_EQ(parentNode->leftNum == 3, 1);
  ASSERT_EQ(parentNode->rightNum == 0, 1);
  ASSERT_EQ(parentNode->maxSubtreeData == 6, 1);
  ASSERT_EQ(parentNode->left == subParent1, 1);
  ASSERT_EQ(parentNode->middle == subParent2, 1);
  ASSERT_EQ(parentNode->right == NULL, 1);
  ASSERT_EQ(parentNode->parent == NULL, 1);

  ASSERT_EQ(subParent1->isLeaf == 0, 1);
  ASSERT_EQ(subParent1->data == 0, 1);
  ASSERT_EQ(subParent1->childsCnt == 2, 1);
  ASSERT_EQ(subParent1->leftNum == 2, 1);
  ASSERT_EQ(subParent1->rightNum == 0, 1);
  ASSERT_EQ(subParent1->maxSubtreeData == 3, 1);
  ASSERT_EQ(subParent1->left == node1, 1);
  ASSERT_EQ(subParent1->middle == node2, 1);
  ASSERT_EQ(subParent1->right == NULL, 1);
  ASSERT_EQ(subParent1->parent == parentNode, 1);

  ASSERT_EQ(subParent2->isLeaf == 0, 1);
  ASSERT_EQ(subParent2->data == 0, 1);
  ASSERT_EQ(subParent2->childsCnt == 2, 1);
  ASSERT_EQ(subParent2->leftNum == 4, 1);
  ASSERT_EQ(subParent2->rightNum == 0, 1);
  ASSERT_EQ(subParent2->maxSubtreeData == 6, 1);
  ASSERT_EQ(subParent2->left == node3, 1);
  ASSERT_EQ(subParent2->middle == node4, 1);
  ASSERT_EQ(subParent2->right == NULL, 1);
  ASSERT_EQ(subParent2->parent == parentNode, 1);

  ASSERT_EQ(node1->isLeaf == 1, 1);
  ASSERT_EQ(node1->data == 2, 1);
  ASSERT_EQ(node1->childsCnt == 0, 1);
  ASSERT_EQ(node1->leftNum == 0, 1);
  ASSERT_EQ(node1->rightNum == 0, 1);
  ASSERT_EQ(node1->maxSubtreeData == 2, 1);
  ASSERT_EQ(node1->left == NULL, 1);
  ASSERT_EQ(node1->middle == NULL, 1);
  ASSERT_EQ(node1->right == NULL, 1);
  ASSERT_EQ(node1->parent == subParent1, 1);

  ASSERT_EQ(node2->isLeaf == 1, 1);
  ASSERT_EQ(node2->data == 3, 1);
  ASSERT_EQ(node2->childsCnt == 0, 1);
  ASSERT_EQ(node2->leftNum == 0, 1);
  ASSERT_EQ(node2->rightNum == 0, 1);
  ASSERT_EQ(node2->maxSubtreeData == 3, 1);
  ASSERT_EQ(node2->left == NULL, 1);
  ASSERT_EQ(node2->middle == NULL, 1);
  ASSERT_EQ(node2->right == NULL, 1);
  ASSERT_EQ(node2->parent == subParent1, 1);

  ASSERT_EQ(node3->isLeaf == 1, 1);
  ASSERT_EQ(node3->data == 4, 1);
  ASSERT_EQ(node3->childsCnt == 0, 1);
  ASSERT_EQ(node3->leftNum == 0, 1);
  ASSERT_EQ(node3->rightNum == 0, 1);
  ASSERT_EQ(node3->maxSubtreeData == 4, 1);
  ASSERT_EQ(node3->left == NULL, 1);
  ASSERT_EQ(node3->middle == NULL, 1);
  ASSERT_EQ(node3->right == NULL, 1);
  ASSERT_EQ(node3->parent == subParent2, 1);

  ASSERT_EQ(node4->isLeaf == 1, 1);
  ASSERT_EQ(node4->data == 6, 1);
  ASSERT_EQ(node4->childsCnt == 0, 1);
  ASSERT_EQ(node4->leftNum == 0, 1);
  ASSERT_EQ(node4->rightNum == 0, 1);
  ASSERT_EQ(node4->maxSubtreeData == 6, 1);
  ASSERT_EQ(node4->left == NULL, 1);
  ASSERT_EQ(node4->middle == NULL, 1);
  ASSERT_EQ(node4->right == NULL, 1);
  ASSERT_EQ(node4->parent == subParent2, 1);
}

/**********************/
/****    DELETE    ****/
/**********************/

TEST(DeleteInEmptyTree, DeleteInTtTree_DeleteInEmptyTtTree_notCrush) {
  ttTree_t* tree = NULL;
  int res = DeleteInTTTree(&tree, 2);

  ASSERT_EQ(res == LABI_FALSE, 1);
}

TEST(DeleteInOneElemTree, DeleteInTtTree_DeleteInOneElementTtTree_notCrush) {
  ttTree_t* tree;
  int res;

  // delete not existed node
  tree = Create1NodeTtTree(2);
  res = DeleteInTTTree(&tree, 3);

  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(tree->isLeaf == 1, 1);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->childsCnt == 0, 1);
  ASSERT_EQ(tree->leftNum == 0, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 2, 1);
  ASSERT_EQ(tree->left == NULL, 1);
  ASSERT_EQ(tree->middle == NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);

  // delete existed node
  tree = Create1NodeTtTree(2);
  res = DeleteInTTTree(&tree, 2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree== NULL, 1);
}

TEST(DeleteInTwoElemTree, DeleteInTtTree_DeleteInTwoElementTtTree_notCrush) {
  ttTree_t* tree;
  int res;

  // delete not existed element
  tree = Create2NodeTtTree(2, 4);
  res = DeleteInTTTree(&tree, 3);

  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 2, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 4, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);

  // delete left element
  tree = Create2NodeTtTree(2, 4);
  res = DeleteInTTTree(&tree, 2);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 1, 1);
  ASSERT_EQ(tree->data == 4, 1);
  ASSERT_EQ(tree->childsCnt == 0, 1);
  ASSERT_EQ(tree->leftNum == 0, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 4, 1);
  ASSERT_EQ(tree->left == NULL, 1);
  ASSERT_EQ(tree->middle == NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);

  // delete right element
  tree = Create2NodeTtTree(2, 4);
  res = DeleteInTTTree(&tree, 4);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 1, 1);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->childsCnt == 0, 1);
  ASSERT_EQ(tree->leftNum == 0, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 2, 1);
  ASSERT_EQ(tree->left == NULL, 1);
  ASSERT_EQ(tree->middle == NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
}

TEST(DeleteInThreeElemTree, DeleteInTtTree_DeleteInThreeElementsTtTree_notCrush) {
  ttTree_t* tree;
  int res;

  // delete not existed tree
  tree = Create3NodeTtTree(2, 4, 6);
  res = DeleteInTTTree(&tree, 3);

  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 3, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 4, 1);
  ASSERT_EQ(tree->maxSubtreeData == 6, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right != NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);

  // delete left elem
  tree = Create3NodeTtTree(2, 4, 6);
  res = DeleteInTTTree(&tree, 2);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 2, 1);
  ASSERT_EQ(tree->leftNum == 4, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 6, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);

  // delete middle elem
  tree = Create3NodeTtTree(2, 4, 6);
  res = DeleteInTTTree(&tree, 4);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 2, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 6, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);

  // delete right elem
  tree = Create3NodeTtTree(2, 4, 6);
  res = DeleteInTTTree(&tree, 6);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 2, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 4, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
}

TEST(DeleteInFourElemTree, DeleteInTtTree_DeleteInFourlementsTtTree_notCrush) {
  ttTree_t* tree;
  int res;

  // delete not existed tree
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = DeleteInTTTree(&tree, 1);

  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 2, 1);
  ASSERT_EQ(tree->leftNum == 4, 1);
  ASSERT_EQ(tree->rightNum == 0, 1);
  ASSERT_EQ(tree->maxSubtreeData == 8, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);

  // delete first from left subtree
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = DeleteInTTTree(&tree, 2);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 3, 1);
  ASSERT_EQ(tree->leftNum == 4, 1);
  ASSERT_EQ(tree->rightNum == 6, 1);
  ASSERT_EQ(tree->maxSubtreeData == 8, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right != NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
  ASSERT_EQ(tree->left->isLeaf == 1, 1);
  ASSERT_EQ(tree->middle->isLeaf == 1, 1);
  ASSERT_EQ(tree->right->isLeaf == 1, 1);

  // delete second from left subtree
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = DeleteInTTTree(&tree, 4);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 3, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 6, 1);
  ASSERT_EQ(tree->maxSubtreeData == 8, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right != NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
  ASSERT_EQ(tree->left->isLeaf == 1, 1);
  ASSERT_EQ(tree->middle->isLeaf == 1, 1);
  ASSERT_EQ(tree->right->isLeaf == 1, 1);

  // delete first from middle subtree
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = DeleteInTTTree(&tree, 6);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 3, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 4, 1);
  ASSERT_EQ(tree->maxSubtreeData == 8, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right != NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
  ASSERT_EQ(tree->left->isLeaf == 1, 1);
  ASSERT_EQ(tree->middle->isLeaf == 1, 1);
  ASSERT_EQ(tree->right->isLeaf == 1, 1);

  // delete second from middle subtree
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = DeleteInTTTree(&tree, 8);

  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(tree->isLeaf == 0, 1);
  ASSERT_EQ(tree->data == 0, 1);
  ASSERT_EQ(tree->childsCnt == 3, 1);
  ASSERT_EQ(tree->leftNum == 2, 1);
  ASSERT_EQ(tree->rightNum == 4, 1);
  ASSERT_EQ(tree->maxSubtreeData == 6, 1);
  ASSERT_EQ(tree->left != NULL, 1);
  ASSERT_EQ(tree->middle != NULL, 1);
  ASSERT_EQ(tree->right != NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
  ASSERT_EQ(tree->left->isLeaf == 1, 1);
  ASSERT_EQ(tree->middle->isLeaf == 1, 1);
  ASSERT_EQ(tree->right->isLeaf == 1, 1);
}

/****************/
/**** SEARCH ****/
/****************/

TEST(SearchTest, SearchInTtTree_SearchTtTree_notCrush) {
  ttTree_t* tree;

  // empty tree
  tree = NULL;
  ASSERT_EQ(SearchInTTTree(tree, 1) == LABI_FALSE, 1);

  // one node tree
  tree = Create1NodeTtTree(2);
  ASSERT_EQ(SearchInTTTree(tree, 1) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 2) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 3) == LABI_FALSE, 1);

  // two node tree
  tree = Create2NodeTtTree(2, 4);
  ASSERT_EQ(SearchInTTTree(tree, 1) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 2) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 3) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 4) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 5) == LABI_FALSE, 1);

  // three node tree
  tree = Create3NodeTtTree(2, 4, 6);
  ASSERT_EQ(SearchInTTTree(tree, 1) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 2) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 3) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 4) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 5) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 6) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 7) == LABI_FALSE, 1);

  // four node tree
  tree = Create4NodeTtTree(2, 4, 6, 8);
  ASSERT_EQ(SearchInTTTree(tree, 1) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 2) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 3) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 4) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 5) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 6) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 7) == LABI_FALSE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 8) == LABI_TRUE, 1);
  ASSERT_EQ(SearchInTTTree(tree, 9) == LABI_FALSE, 1);
}

/***************/
/**** UNION ****/
/***************/

TEST(UnionTest, UnionTtTrees_UnionTtTreeWithDiffLenghtsLessInRight_notCrush) {
  ttTree_t* tree1, * tree2, * treeRes;
  int res;

  /* union to left */
  // empty + one elem tree
  tree1 = NULL;
  tree2 = Create1NodeTtTree(2);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 1, 1);
  ASSERT_EQ(treeRes->data == 2, 1);
  ASSERT_EQ(treeRes->childsCnt == 0, 1);
  ASSERT_EQ(treeRes->leftNum == 0, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 2, 1);
  ASSERT_EQ(treeRes->left == NULL, 1);
  ASSERT_EQ(treeRes->middle == NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // empty + two elem tree
  tree1 = NULL;
  tree2 = Create2NodeTtTree(2, 4);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 2, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 4, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // one elem + two elem tree
  tree1 = Create1NodeTtTree(2);
  tree2 = Create2NodeTtTree(4, 6);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 3, 1);
  ASSERT_EQ(treeRes->leftNum == 2, 1);
  ASSERT_EQ(treeRes->rightNum == 4, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 6, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right != NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // empty + three elem tree
  tree1 = NULL;
  tree2 = Create3NodeTtTree(2, 4, 6);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 3, 1);
  ASSERT_EQ(treeRes->leftNum == 2, 1);
  ASSERT_EQ(treeRes->rightNum == 4, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 6, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right != NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // one elem + three elem tree
  tree1 = Create1NodeTtTree(2);
  tree2 = Create3NodeTtTree(4, 6, 8);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // empty + four elem tree
  tree1 = NULL;
  tree2 = Create4NodeTtTree(2, 4, 6, 8);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // one elem + four elem tree
  tree1 = Create1NodeTtTree(2);
  tree2 = Create4NodeTtTree(4, 6, 8, 10);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 6, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 10, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // two elem + four elem tree
  tree1 = Create2NodeTtTree(2, 4);
  tree2 = Create4NodeTtTree(6, 8, 10, 12);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 3, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 8, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 12, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right != NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);
}

TEST(UnionTest, UnionTtTrees_UnionTtTreeWithDiffLenghtsLessInLeft_notCrush) {
  ttTree_t* tree1, * tree2, * treeRes;
  int res;

  /* union to right */
  // one elem + empty tree
  tree1 = Create1NodeTtTree(2);
  tree2 = NULL;
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 1, 1);
  ASSERT_EQ(treeRes->data == 2, 1);
  ASSERT_EQ(treeRes->childsCnt == 0, 1);
  ASSERT_EQ(treeRes->leftNum == 0, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 2, 1);
  ASSERT_EQ(treeRes->left == NULL, 1);
  ASSERT_EQ(treeRes->middle == NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // two elem + empty tree
  tree1 = Create2NodeTtTree(2, 4);
  tree2 = NULL;
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 2, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 4, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // two elem + one elem tree
  tree1 = Create2NodeTtTree(2, 4);
  tree2 = Create1NodeTtTree(6);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 3, 1);
  ASSERT_EQ(treeRes->leftNum == 2, 1);
  ASSERT_EQ(treeRes->rightNum == 4, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 6, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right != NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // three elem + empty tree
  tree1 = Create3NodeTtTree(2, 4, 6);
  tree2 = NULL;
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 3, 1);
  ASSERT_EQ(treeRes->leftNum == 2, 1);
  ASSERT_EQ(treeRes->rightNum == 4, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 6, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right != NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // three elem + one elem tree
  tree1 = Create3NodeTtTree(2, 4, 6);
  tree2 = Create1NodeTtTree(8);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // four elem + empty tree
  tree1 = Create4NodeTtTree(2, 4, 6, 8);
  tree2 = NULL;
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // four elem + one elem tree
  tree1 = Create4NodeTtTree(2, 4, 6, 8);
  tree2 = Create1NodeTtTree(10);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 10, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // four elem + two elem tree
  tree1 = Create4NodeTtTree(2, 4, 6, 8);
  tree2 = Create2NodeTtTree(10, 12);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 3, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 8, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 12, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right != NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);
}

TEST(UnionTest, UnionTtTrees_UnionTtTreeWithSameLenghts_notCrush) {
  ttTree_t* tree1, * tree2, * treeRes;
  int res;

  // empty + empty
  tree1 = NULL;
  tree2 = NULL;
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_FALSE, 1);

  // one elem + one elem
  tree1 = Create1NodeTtTree(2);
  tree2 = Create1NodeTtTree(4);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 2, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 4, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // two elem + three elem
  tree1 = Create2NodeTtTree(2, 4);
  tree2 = Create3NodeTtTree(6, 7, 8);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // three elem + two elem
  tree1 = Create3NodeTtTree(2, 4, 6);
  tree2 = Create2NodeTtTree(8, 10);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 6, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 10, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // two elem + two elem
  tree1 = Create2NodeTtTree(2, 4);
  tree2 = Create2NodeTtTree(6, 8);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 4, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);

  // three elem + three elem
  tree1 = Create3NodeTtTree(2, 4, 6);
  tree2 = Create3NodeTtTree(8, 10, 12);
  res = UnionTTTree(&treeRes, tree1, tree2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes->isLeaf == 0, 1);
  ASSERT_EQ(treeRes->data == 0, 1);
  ASSERT_EQ(treeRes->childsCnt == 2, 1);
  ASSERT_EQ(treeRes->leftNum == 6, 1);
  ASSERT_EQ(treeRes->rightNum == 0, 1);
  ASSERT_EQ(treeRes->maxSubtreeData == 12, 1);
  ASSERT_EQ(treeRes->left != NULL, 1);
  ASSERT_EQ(treeRes->middle != NULL, 1);
  ASSERT_EQ(treeRes->right == NULL, 1);
  ASSERT_EQ(treeRes->parent == NULL, 1);
}

/***************/
/**** SPLIT ****/
/***************/

TEST(SplitTest, SplitTtTrees_SplitTtTree_notCrush) {
  ttTree_t* tree, * treeRes1, * treeRes2;
  int res;

  // split empty tree
  tree = NULL;
  res = SplitTTTree(tree, &treeRes1, &treeRes2, 10);
  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(treeRes1 == NULL, 1);
  ASSERT_EQ(treeRes2 == NULL, 1);

  // split tree with not existed element
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = SplitTTTree(tree, &treeRes1, &treeRes2, 7);
  ASSERT_EQ(res == LABI_FALSE, 1);
  ASSERT_EQ(treeRes1 == NULL, 1);
  ASSERT_EQ(treeRes2 == NULL, 1);

  // split tree for left element
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = SplitTTTree(tree, &treeRes1, &treeRes2, 2);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes1->isLeaf == 1, 1);
  ASSERT_EQ(treeRes1->data == 2, 1);
  ASSERT_EQ(treeRes1->childsCnt == 0, 1);
  ASSERT_EQ(treeRes1->leftNum == 0, 1);
  ASSERT_EQ(treeRes1->rightNum == 0, 1);
  ASSERT_EQ(treeRes1->maxSubtreeData == 2, 1);
  ASSERT_EQ(treeRes1->right == NULL, 1);
  ASSERT_EQ(treeRes1->middle == NULL, 1);
  ASSERT_EQ(treeRes1->left == NULL, 1);
  ASSERT_EQ(treeRes1->parent == NULL, 1);

  ASSERT_EQ(treeRes2->isLeaf == 0, 1);
  ASSERT_EQ(treeRes2->data == 0, 1);
  ASSERT_EQ(treeRes2->childsCnt == 3, 1);
  ASSERT_EQ(treeRes2->leftNum == 4, 1);
  ASSERT_EQ(treeRes2->rightNum == 6, 1);
  ASSERT_EQ(treeRes2->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes2->right != NULL, 1);
  ASSERT_EQ(treeRes2->middle != NULL, 1);
  ASSERT_EQ(treeRes2->left != NULL, 1);
  ASSERT_EQ(treeRes2->parent == NULL, 1);

  // split tree for right element
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = SplitTTTree(tree, &treeRes1, &treeRes2, 8);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes2== NULL, 1);

  ASSERT_EQ(treeRes1->isLeaf == 0, 1);
  ASSERT_EQ(treeRes1->data == 0, 1);
  ASSERT_EQ(treeRes1->childsCnt == 2, 1);
  ASSERT_EQ(treeRes1->leftNum == 4, 1);
  ASSERT_EQ(treeRes1->rightNum == 0, 1);
  ASSERT_EQ(treeRes1->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes1->right == NULL, 1);
  ASSERT_EQ(treeRes1->middle != NULL, 1);
  ASSERT_EQ(treeRes1->left != NULL, 1);
  ASSERT_EQ(treeRes1->parent == NULL, 1);

  // split tree for middle element
  tree = Create4NodeTtTree(2, 4, 6, 8);
  res = SplitTTTree(tree, &treeRes1, &treeRes2, 4);
  ASSERT_EQ(res == LABI_TRUE, 1);
  ASSERT_EQ(treeRes1->isLeaf == 0, 1);
  ASSERT_EQ(treeRes1->data == 0, 1);
  ASSERT_EQ(treeRes1->childsCnt == 2, 1);
  ASSERT_EQ(treeRes1->leftNum == 2, 1);
  ASSERT_EQ(treeRes1->rightNum == 0, 1);
  ASSERT_EQ(treeRes1->maxSubtreeData == 4, 1);
  ASSERT_EQ(treeRes1->right == NULL, 1);
  ASSERT_EQ(treeRes1->middle != NULL, 1);
  ASSERT_EQ(treeRes1->left != NULL, 1);
  ASSERT_EQ(treeRes1->parent == NULL, 1);

  ASSERT_EQ(treeRes2->isLeaf == 0, 1);
  ASSERT_EQ(treeRes2->data == 0, 1);
  ASSERT_EQ(treeRes2->childsCnt == 2, 1);
  ASSERT_EQ(treeRes2->leftNum == 6, 1);
  ASSERT_EQ(treeRes2->rightNum == 0, 1);
  ASSERT_EQ(treeRes2->maxSubtreeData == 8, 1);
  ASSERT_EQ(treeRes2->right == NULL, 1);
  ASSERT_EQ(treeRes2->middle != NULL, 1);
  ASSERT_EQ(treeRes2->left != NULL, 1);
  ASSERT_EQ(treeRes2->parent == NULL, 1);
}
