#include "pch.h"
#include "../lab-E-F/tree.h"
#include "../lab-E-F/tree.c"

TEST(TreeAdd_EmptyTree_ReturnTrue) {
  node_t* tree = NULL;

  EXPECT_EQ(TreeAdd(&tree, 1), TRUE);
  EXPECT_EQ(tree->num, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (node_t*)NULL);
  EXPECT_EQ(tree->right, (node_t*)NULL);
  EXPECT_EQ(tree->parent, (node_t*)NULL);

  free(tree);
}

TEST(TreeAdd_SuccessfulTreeAdd_ReturnTrue) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(TreeAdd(&tree, 2), TRUE);
  EXPECT_EQ(tree->num, 2);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (node_t*)NULL);
  EXPECT_FALSE(tree->right == (node_t*)NULL);
  EXPECT_EQ(tree->parent, (node_t*)NULL);

  EXPECT_EQ(tree->right->key, 2);
  EXPECT_EQ(tree->right->left, (node_t*)NULL);
  EXPECT_EQ(tree->right->right, (node_t*)NULL);
  EXPECT_EQ(tree->right->parent, tree);
  EXPECT_EQ(tree->right->num, 1);

  free(tree->right);
  free(tree);
}

TEST(TreeAdd_UnsuccessfulTreeAdd_ReturnFalse) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(TreeAdd(&tree, 1), FALSE);
  EXPECT_EQ(tree->num, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (node_t*)NULL);
  EXPECT_EQ(tree->right, (node_t*)NULL);
  EXPECT_EQ(tree->parent, (node_t*)NULL);

  free(tree);
}

TEST(TreeDel_EmptyTree_ReturnFalse) {
  node_t* tree = NULL;

  EXPECT_EQ(TreeDel(&tree, 1), FALSE);
  EXPECT_EQ(tree, (node_t*)NULL);
}

TEST(TreeDel_UnexistedElement_ReturnFalse) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(TreeDel(&tree, 2), FALSE);
  EXPECT_EQ(tree->num, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (node_t*)NULL);
  EXPECT_EQ(tree->right, (node_t*)NULL);
  EXPECT_EQ(tree->parent, (node_t*)NULL);

  free(tree);
}

TEST(TreeDel_WithNullChilds_ReturnTrue) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(TreeDel(&tree, 1), TRUE);
  EXPECT_EQ(tree, (node_t*)NULL);
}

TEST(TreeDel_With1NonNullChild_ReturnTrue) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));
  node_t node2;

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 2;

  node2.key = 2;
  node2.left = NULL;
  node2.right = NULL;
  node2.num = 1;

  tree->right = &node2;
  node2.parent = tree;

  EXPECT_EQ(TreeDel(&tree, 1), TRUE);
  EXPECT_EQ(tree->num, 1);
  EXPECT_EQ(tree, &node2);
  EXPECT_EQ(tree->key, 2);
  EXPECT_EQ(tree->left, (node_t*)NULL);
  EXPECT_EQ(tree->right, (node_t*)NULL);
  EXPECT_EQ(tree->parent, (node_t*)NULL);
}

TEST(TreeDel_With2NonNullChilds_ReturnTrue) {
  node_t tree;
  node_t* node2 = (node_t*)malloc(sizeof(node_t)), *treeptr = &tree;
  node_t node3;

  tree.key = 2;
  tree.parent = NULL;
  tree.num = 3;
  tree.left = node2;
  tree.right = &node3;

  node2->key = 1;
  node2->left = NULL;
  node2->right = NULL;
  node2->num = 1;

  node3.key = 3;
  node3.left = NULL;
  node3.right = NULL;
  node3.num = 1;

  node2->parent = treeptr;
  node3.parent = treeptr;

  EXPECT_EQ(TreeDel(&treeptr, 2), TRUE);
  EXPECT_EQ(tree.num, 2);
  EXPECT_EQ(treeptr, &tree);

  EXPECT_EQ(tree.key, 1);
  EXPECT_EQ(tree.left, (node_t*)NULL);
  EXPECT_EQ(tree.right, &node3);
  EXPECT_EQ(tree.parent, (node_t*)NULL);

  EXPECT_EQ(tree.right->key, 3);
  EXPECT_EQ(tree.right->left, (node_t*)NULL);
  EXPECT_EQ(tree.right->right, (node_t*)NULL);
  EXPECT_EQ(tree.right->parent, &tree);
  EXPECT_EQ(tree.right->num, 1);
}

TEST(TreeFind_EmptyTree_ReturnNULL) {
  node_t* tree = NULL;

  EXPECT_EQ(TreeFind(tree, 1), (node_t*)NULL);
}

TEST(TreeFind_FindExisted_ReturnCorrectPtr) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(TreeFind(tree, 1), tree);
  EXPECT_EQ(tree->num, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (node_t*)NULL);
  EXPECT_EQ(tree->right, (node_t*)NULL);
  EXPECT_EQ(tree->parent, (node_t*)NULL);

  free(tree);
}

TEST(TreeFind_FindUnexisted_ReturnNULL) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(TreeFind(tree, 2), (node_t*)NULL);
  EXPECT_EQ(tree->num, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (node_t*)NULL);
  EXPECT_EQ(tree->right, (node_t*)NULL);
  EXPECT_EQ(tree->parent, (node_t*)NULL);

  free(tree);
}

TEST(TreeDel_EmptyTree_CorrectProcessing) {
  node_t* tree = NULL;

  TreeClear(&tree);
}

TEST(TreeDel_CorrectTree_CorrectProcessing) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  TreeClear(&tree);
  EXPECT_EQ(tree, (node_t*)NULL);
}

TEST(findMax_EmptyTree_ReturnNULL) {
  node_t* tree = NULL;

  EXPECT_EQ(findMax(tree), (node_t*)NULL);
}

TEST(findMax_CorrectTree_ReturnCorrectPtr) {
  node_t tree, node2;

  tree.key = 1;
  tree.left = NULL;
  tree.parent = NULL;
  tree.num = 2;

  node2.key = 2;
  node2.left = NULL;
  node2.right = NULL;
  node2.num = 1;

  tree.right = &node2;
  node2.parent = &tree;

  EXPECT_EQ(findMax(&tree), &node2);
}

TEST(TreePrint_EmptyTree_CorrectProcessing) {
  node_t* tree = NULL;

  TreePrint(tree);
}

TEST(TreePrint_CorrectTree_CorrectProcessing) {
  node_t tree, node2;

  tree.key = 1;
  tree.left = NULL;
  tree.parent = NULL;
  tree.num = 2;

  node2.key = 2;
  node2.left = NULL;
  node2.right = NULL;
  node2.num = 1;

  tree.right = &node2;
  node2.parent = &tree;

  TreePrint(&tree);
}

TEST(treeHeight_EmptyTree_Return0) {
  node_t* tree = NULL;

  EXPECT_EQ(treeHeight(tree), 0);
}

TEST(treeHeight_CorrectTree_CorrectHeight) {
  node_t tree, node2;

  tree.key = 1;
  tree.left = NULL;
  tree.parent = NULL;
  tree.num = 2;

  node2.key = 2;
  node2.left = NULL;
  node2.right = NULL;
  node2.num = 1;

  tree.right = &node2;
  node2.parent = &tree;

  EXPECT_EQ(treeHeight(&tree), 2);
}

TEST(printLvl_EmptyTree_CorrectProcessing) {
  node_t** cur = NULL;

  printLvl(1, 1, 1, cur);
}

TEST(printLvl_Incorrectlvl_CorrectProcessing) {
  node_t** cur = (node_t**)malloc(sizeof(node_t*));

  cur[0] = NULL;

  printLvl(-1, 1, 1, cur);

  free(cur);
}

TEST(printLvl_IncorrectHeight_CorrectProcessing) {
  node_t** cur = (node_t**)malloc(sizeof(node_t*));

  cur[0] = NULL;

  printLvl(1, 0, 1, cur);

  free(cur);
}

TEST(printLvl_Correct_CorrectProcessing) {
  node_t* cur = (node_t*)malloc(sizeof(node_t));

  cur->key = 1;
  cur->left = NULL;
  cur->right = NULL;
  cur->parent = NULL;
  cur->num = 1;

  printLvl(1, 1, 1, &cur);

  free(cur);
}

TEST(TreePrettyPrint_EmptyTree_CorrectProcessing) {
  node_t* tree = NULL;

  TreePrettyPrint(tree);
}

TEST(TreePrettyPrint_Correct_CorrectProcessing) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  TreePrettyPrint(tree);

  free(tree);
}

TEST(size_EmptyTree_Return1) {
  node_t* tree = NULL;

  EXPECT_EQ(size(tree), 1);
}

TEST(size_NullLeft_Return1) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(size(tree), 1);

  free(tree);
}

TEST(size_LeftChild_Return2) {
  node_t tree, node2;

  tree.key = 1;
  tree.left = &node2;
  tree.parent = NULL;
  tree.num = 2;
  tree.right = NULL;

  node2.key = 2;
  node2.left = NULL;
  node2.right = NULL;
  node2.num = 1;
  node2.parent = &tree;

  EXPECT_EQ(size(&tree), 2);
}

TEST(number_nullptr_ReturnFalse) {
  node_t* tree = NULL;

  EXPECT_EQ(number(tree), FALSE);
}

TEST(number_Correct_Return1) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(number(tree), 1);

  free(tree);
}

TEST(getKMin_EmptyTree_ReturnNULL) {
  node_t* tree = NULL;

  EXPECT_EQ(getKMin(tree, 1), (node_t*)NULL);
}

TEST(getKMin_IncorrectK_ReturnNULL) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(getKMin(tree, 2), (node_t*)NULL);

  free(tree);
}

TEST(getKMin_CorrectK_ReturnPtr) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(getKMin(tree, 1), tree);

  free(tree);
}

TEST(FindKLower_EmptyTree_ReturnNULL) {
  node_t* tree = NULL;

  EXPECT_EQ(FindKLower(tree, 1, 1), (node_t*)NULL);
}

TEST(FindKLower_IncorrectK_ReturnNULL) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(FindKLower(tree, 1, 2), (node_t*)NULL);

  free(tree);
}

TEST(FindKLower_IncorrectKey_ReturnNULL) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(FindKLower(tree, 2, 0), (node_t*)NULL);

  free(tree);
}

TEST(FindKLower_Correct_ReturnPtr) {
  node_t* tree = (node_t*)malloc(sizeof(node_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->num = 1;

  EXPECT_EQ(FindKLower(tree, 1, 0), tree);

  free(tree);
}