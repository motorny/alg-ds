#include "pch.h"
#include "../aa-tree/aatree.c"
#include "../aa-tree/aatree.h"

TEST(Skew_IncorrectPtrOnPtr_ReturnPtrErr) {
  EXPECT_EQ(skew(NULL), PTR_ERR);
}

TEST(Skew_IncorrectPtr_ReturnPtrErr) {
  aatree_t* tree = NULL;

  EXPECT_EQ(skew(&tree), PTR_ERR);
}

TEST(Skew_WithNoLeftChild_ReturnFalse) {
  aatree_t tree;
  aatree_t* treeptr = &tree;

  tree.key = 0;
  tree.parent = NULL;
  tree.level = 1;
  tree.left = NULL;
  tree.right = NULL;

  EXPECT_EQ(skew(&treeptr), FALSE);
  EXPECT_EQ(treeptr, &tree);

  EXPECT_EQ(tree.key, 0);
  EXPECT_EQ(tree.left, (aatree_t*)NULL);
  EXPECT_EQ(tree.right, (aatree_t*)NULL);
  EXPECT_EQ(tree.parent, (aatree_t*)NULL);
  EXPECT_EQ(tree.level, 1);
}

TEST(Skew_WithLeftChildWithSmallerLevel_ReturnFalse) {
  aatree_t tree, node;
  aatree_t* treeptr = &tree;

  tree.key = 1;
  tree.parent = NULL;
  tree.level = 2;
  tree.left = &node;
  tree.right = NULL;

  node.key = 0;
  node.parent = &tree;
  node.level = 1;
  node.left = NULL;
  node.right = NULL;

  EXPECT_EQ(skew(&treeptr), FALSE);
  EXPECT_EQ(treeptr, &tree);

  EXPECT_EQ(tree.key, 1);
  EXPECT_EQ(tree.left, &node);
  EXPECT_EQ(tree.right, (aatree_t*)NULL);
  EXPECT_EQ(tree.parent, (aatree_t*)NULL);
  EXPECT_EQ(tree.level, 2);

  EXPECT_EQ(node.key, 0);
  EXPECT_EQ(node.left, (aatree_t*)NULL);
  EXPECT_EQ(node.right, (aatree_t*)NULL);
  EXPECT_EQ(node.parent, &tree);
  EXPECT_EQ(node.level, 1);
}

TEST(Skew_WithLeftChildWithSameLevel_ReturnTrue) {
  aatree_t tree, node;
  aatree_t* treeptr = &tree;

  tree.key = 1;
  tree.parent = NULL;
  tree.level = 1;
  tree.left = &node;
  tree.right = NULL;

  node.key = 0;
  node.parent = &tree;
  node.level = 1;
  node.left = NULL;
  node.right = NULL;

  EXPECT_EQ(skew(&treeptr), TRUE);
  EXPECT_EQ(treeptr, &node);

  EXPECT_EQ(tree.key, 1);
  EXPECT_EQ(tree.left, (aatree_t*)NULL);
  EXPECT_EQ(tree.right, (aatree_t*)NULL);
  EXPECT_EQ(tree.parent, &node);
  EXPECT_EQ(tree.level, 1);

  EXPECT_EQ(node.key, 0);
  EXPECT_EQ(node.left, (aatree_t*)NULL);
  EXPECT_EQ(node.right, &tree);
  EXPECT_EQ(node.parent, (aatree_t*)NULL);
  EXPECT_EQ(node.level, 1);
}

TEST(Split_IncorrectPtrOnPtr_ReturnPtrErr) {
  EXPECT_EQ(split(NULL), PTR_ERR);
}

TEST(Split_IncorrectPtr_ReturnPtrErr) {
  aatree_t* tree = NULL;

  EXPECT_EQ(split(&tree), PTR_ERR);
}

TEST(Split_WithNoRightChild_ReturnFalse) {
  aatree_t tree;
  aatree_t* treeptr = &tree;

  tree.key = 0;
  tree.parent = NULL;
  tree.level = 1;
  tree.left = NULL;
  tree.right = NULL;

  EXPECT_EQ(split(&treeptr), FALSE);
  EXPECT_EQ(treeptr, &tree);

  EXPECT_EQ(tree.key, 0);
  EXPECT_EQ(tree.left, (aatree_t*)NULL);
  EXPECT_EQ(tree.right, (aatree_t*)NULL);
  EXPECT_EQ(tree.parent, (aatree_t*)NULL);
  EXPECT_EQ(tree.level, 1);
}

TEST(Split_WithRightChildWithSmallerLevel_ReturnFalse) {
  aatree_t tree, node;
  aatree_t* treeptr = &tree;

  tree.key = 0;
  tree.parent = NULL;
  tree.level = 2;
  tree.left = NULL;
  tree.right = &node;

  node.key = 1;
  node.parent = &tree;
  node.level = 1;
  node.left = NULL;
  node.right = NULL;

  EXPECT_EQ(split(&treeptr), FALSE);
  EXPECT_EQ(treeptr, &tree);

  EXPECT_EQ(tree.key, 0);
  EXPECT_EQ(tree.left, (aatree_t*)NULL);
  EXPECT_EQ(tree.right, &node);
  EXPECT_EQ(tree.parent, (aatree_t*)NULL);
  EXPECT_EQ(tree.level, 2);

  EXPECT_EQ(node.key, 1);
  EXPECT_EQ(node.left, (aatree_t*)NULL);
  EXPECT_EQ(node.right, (aatree_t*)NULL);
  EXPECT_EQ(node.parent, &tree);
  EXPECT_EQ(node.level, 1);
}

TEST(Split_OneRightWithSameLevel_ReturnFalse) {
  aatree_t tree, node;
  aatree_t* treeptr = &tree;

  tree.key = 0;
  tree.parent = NULL;
  tree.level = 1;
  tree.left = NULL;
  tree.right = &node;

  node.key = 1;
  node.parent = &tree;
  node.level = 1;
  node.left = NULL;
  node.right = NULL;

  EXPECT_EQ(split(&treeptr), FALSE);
  EXPECT_EQ(treeptr, &tree);

  EXPECT_EQ(tree.key, 0);
  EXPECT_EQ(tree.left, (aatree_t*)NULL);
  EXPECT_EQ(tree.right, &node);
  EXPECT_EQ(tree.parent, (aatree_t*)NULL);
  EXPECT_EQ(tree.level, 1);

  EXPECT_EQ(node.key, 1);
  EXPECT_EQ(node.left, (aatree_t*)NULL);
  EXPECT_EQ(node.right, (aatree_t*)NULL);
  EXPECT_EQ(node.parent, &tree);
  EXPECT_EQ(node.level, 1);
}

TEST(Split_TwoRightWithSameLevel_ReturnTrue) {
  aatree_t tree, node1, node2;
  aatree_t* treeptr = &tree;

  tree.key = 0;
  tree.parent = NULL;
  tree.level = 1;
  tree.left = NULL;
  tree.right = &node1;

  node1.key = 1;
  node1.parent = &tree;
  node1.level = 1;
  node1.left = NULL;
  node1.right = &node2;

  node2.key = 2;
  node2.parent = &node1;
  node2.level = 1;
  node2.left = NULL;
  node2.right = NULL;

  EXPECT_EQ(split(&treeptr), TRUE);
  EXPECT_EQ(treeptr, &node1);

  EXPECT_EQ(tree.key, 0);
  EXPECT_EQ(tree.left, (aatree_t*)NULL);
  EXPECT_EQ(tree.right, (aatree_t*)NULL);
  EXPECT_EQ(tree.parent, &node1);
  EXPECT_EQ(tree.level, 1);

  EXPECT_EQ(node1.key, 1);
  EXPECT_EQ(node1.left, &tree);
  EXPECT_EQ(node1.right, &node2);
  EXPECT_EQ(node1.parent, (aatree_t*)NULL);
  EXPECT_EQ(node1.level, 2);

  EXPECT_EQ(node2.key, 2);
  EXPECT_EQ(node2.left, (aatree_t*)NULL);
  EXPECT_EQ(node2.right, (aatree_t*)NULL);
  EXPECT_EQ(node2.parent, &node1);
  EXPECT_EQ(node2.level, 1);
}

TEST(Insert_EmptyTree_ReturnTrue) {
  aatree_t* tree = NULL;

  EXPECT_EQ(Insert(&tree, 1), TRUE);
  EXPECT_EQ(tree->level, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (aatree_t*)NULL);
  EXPECT_EQ(tree->right, (aatree_t*)NULL);
  EXPECT_EQ(tree->parent, (aatree_t*)NULL);

  free(tree);
}

TEST(Insert_SuccessfulInsert_ReturnTrue) {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->level = 1;

  EXPECT_EQ(Insert(&tree, 2), TRUE);
  EXPECT_EQ(tree->level, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (aatree_t*)NULL);
  EXPECT_FALSE(tree->right == (aatree_t*)NULL);
  EXPECT_EQ(tree->parent, (aatree_t*)NULL);

  EXPECT_EQ(tree->right->key, 2);
  EXPECT_EQ(tree->right->left, (aatree_t*)NULL);
  EXPECT_EQ(tree->right->right, (aatree_t*)NULL);
  EXPECT_EQ(tree->right->parent, tree);
  EXPECT_EQ(tree->right->level, 1);

  free(tree->right);
  free(tree);
}

TEST(Insert_UnsuccessfulInsert_ReturnFalse) {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->level = 1;

  EXPECT_EQ(Insert(&tree, 1), FALSE);
  EXPECT_EQ(tree->level, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (aatree_t*)NULL);
  EXPECT_EQ(tree->right, (aatree_t*)NULL);
  EXPECT_EQ(tree->parent, (aatree_t*)NULL);

  free(tree);
}

TEST(Delete_EmptyTree_ReturnFalse) {
  aatree_t* tree = NULL;

  EXPECT_EQ(Delete(&tree, 1, tree), FALSE);
  EXPECT_EQ(tree, (aatree_t*)NULL);
}

TEST(Delete_UnexistedElement_ReturnFalse) {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->level = 1;

  EXPECT_EQ(Delete(&tree, 2, tree), FALSE);
  EXPECT_EQ(tree->level, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (aatree_t*)NULL);
  EXPECT_EQ(tree->right, (aatree_t*)NULL);
  EXPECT_EQ(tree->parent, (aatree_t*)NULL);

  free(tree);
}

TEST(Delete_WithNullChilds_ReturnTrue) {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->level = 1;

  EXPECT_EQ(Delete(&tree, 1, tree), TRUE);
  EXPECT_EQ(tree, (aatree_t*)NULL);
}

TEST(Delete_With1NonNullChild_ReturnTrue) {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));
  aatree_t node2;

  tree->key = 1;
  tree->left = NULL;
  tree->parent = NULL;
  tree->level = 1;

  node2.key = 2;
  node2.left = NULL;
  node2.right = NULL;
  node2.level = 1;

  tree->right = &node2;
  node2.parent = tree;

  EXPECT_EQ(Delete(&tree, 1, tree), TRUE);
  EXPECT_EQ(tree->level, 1);
  EXPECT_EQ(tree, &node2);
  EXPECT_EQ(tree->key, 2);
  EXPECT_EQ(tree->left, (aatree_t*)NULL);
  EXPECT_EQ(tree->right, (aatree_t*)NULL);
  EXPECT_EQ(tree->parent, (aatree_t*)NULL);
}

TEST(Delete_With2NonNullChilds_ReturnTrue) {
  aatree_t tree;
  aatree_t* node2 = (aatree_t*)malloc(sizeof(aatree_t)), *treeptr = &tree;
  aatree_t node3;

  tree.key = 2;
  tree.parent = NULL;
  tree.level = 2;
  tree.left = node2;
  tree.right = &node3;

  node2->key = 1;
  node2->left = NULL;
  node2->right = NULL;
  node2->level = 1;

  node3.key = 3;
  node3.left = NULL;
  node3.right = NULL;
  node3.level = 1;

  node2->parent = treeptr;
  node3.parent = treeptr;

  EXPECT_EQ(Delete(&treeptr, 2, treeptr), TRUE);
  EXPECT_EQ(tree.level, 2);
  EXPECT_EQ(treeptr, &tree);

  EXPECT_EQ(tree.key, 1);
  EXPECT_EQ(tree.left, (aatree_t*)NULL);
  EXPECT_EQ(tree.right, &node3);
  EXPECT_EQ(tree.parent, (aatree_t*)NULL);

  EXPECT_EQ(tree.right->key, 3);
  EXPECT_EQ(tree.right->left, (aatree_t*)NULL);
  EXPECT_EQ(tree.right->right, (aatree_t*)NULL);
  EXPECT_EQ(tree.right->parent, &tree);
  EXPECT_EQ(tree.right->level, 1);
}

TEST(Find_EmptyTree_ReturnNULL) {
  aatree_t* tree = NULL;

  EXPECT_EQ(Find(tree, 1), (aatree_t*)NULL);
}

TEST(Find_FindExisted_ReturnCorrectPtr) {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->level = 1;

  EXPECT_EQ(Find(tree, 1), tree);
  EXPECT_EQ(tree->level, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (aatree_t*)NULL);
  EXPECT_EQ(tree->right, (aatree_t*)NULL);
  EXPECT_EQ(tree->parent, (aatree_t*)NULL);

  free(tree);
}

TEST(Find_FindUnexisted_ReturnNULL) {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->level = 1;

  EXPECT_EQ(Find(tree, 2), (aatree_t*)NULL);
  EXPECT_EQ(tree->level, 1);
  EXPECT_EQ(tree->key, 1);
  EXPECT_EQ(tree->left, (aatree_t*)NULL);
  EXPECT_EQ(tree->right, (aatree_t*)NULL);
  EXPECT_EQ(tree->parent, (aatree_t*)NULL);

  free(tree);
}

TEST(Clear_EmptyTree_CorrectProcessing) {
  aatree_t* tree = NULL;

  Clear(&tree);
}

TEST(Clear_CorrectTree_CorrectProcessing) {
  aatree_t* tree = (aatree_t*)malloc(sizeof(aatree_t));

  tree->key = 1;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;
  tree->level = 1;

  Clear(&tree);
  EXPECT_EQ(tree, (aatree_t*)NULL);
}

TEST(findMax_EmptyTree_ReturnNULL) {
  aatree_t* tree = NULL;

  EXPECT_EQ(findMax(tree), (aatree_t*)NULL);
}

TEST(findMax_CorrectTree_ReturnCorrectPtr) {
  aatree_t tree, node2;

  tree.key = 1;
  tree.left = NULL;
  tree.parent = NULL;
  tree.level = 1;

  node2.key = 2;
  node2.left = NULL;
  node2.right = NULL;
  node2.level = 1;

  tree.right = &node2;
  node2.parent = &tree;

  EXPECT_EQ(findMax(&tree), &node2);
}