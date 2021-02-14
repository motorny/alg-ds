#include "gtest/gtest.h"
#include "../rst.h"

TEST(Insert_TreeWithInvalidPtr_ReturnMinus1) {
  EXPECT_EQ(Insert(NULL, 1), RST_INSERT_NULL_TREE);
}

TEST(Insert_EmptyTree_Return1) {
  rst_t *tree = GetTree();

  EXPECT_EQ(Insert(tree, 1), RST_INSERT_NODE_ADDED);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  free(tree->root);
  free(tree);
}

TEST(Insert_SuccessfulInsertWithoutRot_Return1) {
  rst_t *tree = GetTree();
  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.prior = -1;

  tree->root = &n1;

  EXPECT_EQ(Insert(tree, 2), RST_INSERT_NODE_ADDED);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t *)NULL);
  EXPECT_FALSE(tree->root->right == (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  EXPECT_EQ(tree->root->right->key, 2);
  EXPECT_EQ(tree->root->right->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->right->parent, &n1);

  free(tree->root->right);
  free(tree);
}

TEST(Insert_SuccessfulInsertWithRot_Return1) {
  rst_t *tree = GetTree();
  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.prior = RAND_MAX + 1;

  tree->root = &n1;

  EXPECT_EQ(Insert(tree, 2), RST_INSERT_NODE_ADDED);
  EXPECT_EQ(tree->root->key, 2);
  EXPECT_EQ(tree->root->left, &n1);
  EXPECT_EQ(tree->root->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  EXPECT_EQ(tree->root->left->key, 1);
  EXPECT_EQ(tree->root->left->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->left->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->left->parent, tree->root);

  free(tree->root);
  free(tree);
}

TEST(Insert_UnsuccessfulInsert_Return0) {
  rst_t *tree = GetTree();
  node_t n1;
  n1.key = 1;
  n1.prior = 0;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;

  tree->root = &n1;

  EXPECT_EQ(Insert(tree, 1), RST_INSERT_NODE_ALREADY_EXIST);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  free(tree);
}

TEST(Delete_TreeWithInvalidPtr_ReturnMinus1) {
  EXPECT_EQ(Delete(NULL, 1), RST_DELETE_NULL_TREE);
}

TEST(Delete_EmptyTree_Return0) {
  rst_t *tree = GetTree();

  EXPECT_EQ(Delete(tree, 1), RST_DELETE_NODE_DOESNT_EXIST);
  EXPECT_EQ(tree->root, (node_t *)NULL);

  free(tree);
}

TEST(Delete_TryToDeleteUnexistedElement_Return0) {
  rst_t *tree = GetTree();
  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.prior = 1;

  tree->root = &n1;

  EXPECT_EQ(Delete(tree, 2), RST_DELETE_NODE_DOESNT_EXIST);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  free(tree);
}

TEST(Delete_DeleteElementWithNullChilds_Return1) {
  rst_t *tree = GetTree();
  node_t *n1 = (node_t *)malloc(sizeof(node_t));
  n1->key = 1;
  n1->left = NULL;
  n1->right = NULL;
  n1->parent = NULL;
  n1->prior = 1;

  tree->root = n1;

  EXPECT_EQ(Delete(tree, 1), RST_DELETE_NODE_DELETED);
  EXPECT_EQ(tree->root, (node_t *)NULL);

  free(tree);
}

TEST(Delete_DeleteElementWith1NonNullChild_Return1) {
  rst_t *tree = GetTree();

  node_t *n1 = (node_t *)malloc(sizeof(node_t));
  n1->key = 1;
  n1->left = NULL;
  n1->parent = NULL;
  n1->prior = 1;

  node_t n2;
  n2.key = 2;
  n2.left = NULL;
  n2.right = NULL;
  n2.prior;

  n1->right = &n2;
  n2.parent = n1;

  tree->root = n1;

  EXPECT_EQ(Delete(tree, 1), 1);
  EXPECT_EQ(tree->root, &n2);
  EXPECT_EQ(tree->root->key, 2);
  EXPECT_EQ(tree->root->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  free(tree);
}

TEST(Delete_DeleteElementWith2NonNullChildsLeftUp_Return1) {
  rst_t *tree = GetTree();

  node_t *n2 = (node_t *)malloc(sizeof(node_t));
  n2->key = 2;
  n2->parent = NULL;
  n2->prior = 1;

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.prior = 2;

  node_t n3;
  n3.key = 3;
  n3.left = NULL;
  n3.right = NULL;
  n3.prior = 3;

  n2->left = &n1;
  n2->right = &n3;
  n1.parent = n2;
  n3.parent = n2;

  tree->root = n2;

  EXPECT_EQ(Delete(tree, 2), RST_DELETE_NODE_DELETED);
  EXPECT_EQ(tree->root, &n1);

  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right, &n3);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  EXPECT_EQ(tree->root->right->key, 3);
  EXPECT_EQ(tree->root->right->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->right->parent, &n1);

  free(tree);
}

TEST(Delete_DeleteElementWith2NonNullChildsRightUp_Return1) {
  rst_t *tree = GetTree();

  node_t *n2 = (node_t *)malloc(sizeof(node_t));
  n2->key = 2;
  n2->parent = NULL;
  n2->prior = 1;

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.prior = 3;

  node_t n3;
  n3.key = 3;
  n3.left = NULL;
  n3.right = NULL;
  n3.prior = 2;

  n2->left = &n1;
  n2->right = &n3;
  n1.parent = n2;
  n3.parent = n2;

  tree->root = n2;

  EXPECT_EQ(Delete(tree, 2), RST_DELETE_NODE_DELETED);
  EXPECT_EQ(tree->root, &n3);

  EXPECT_EQ(tree->root->key, 3);
  EXPECT_EQ(tree->root->left, &n1);
  EXPECT_EQ(tree->root->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  EXPECT_EQ(tree->root->left->key, 1);
  EXPECT_EQ(tree->root->left->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->left->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->left->parent, &n3);

  free(tree);
}

TEST(Find_TreeWithInvalidPtr_ReturnMinus1) {
  EXPECT_EQ(Find(NULL, 1), RST_FIND_NULL_TREE);
}

TEST(Find_EmptyTree_Return0) {
  rst_t *tree = GetTree();

  EXPECT_EQ(Find(tree, 1), RST_FIND_NODE_DOESNT_EXIST);
  EXPECT_EQ(tree->root, (node_t *)NULL);

  free(tree);
}

TEST(Find_FindExisted_Return1) {
  rst_t *tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.prior = 1;

  tree->root = &n1;

  EXPECT_EQ(Find(tree, 1), RST_FIND_NODE_EXIST);
  EXPECT_EQ(tree->root, &n1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  free(tree);
}

TEST(Find_FindUnexisted_Return0) {
  rst_t *tree = GetTree();

  node_t n1;
  n1.key = 1;
  n1.left = NULL;
  n1.right = NULL;
  n1.parent = NULL;
  n1.prior = 1;

  tree->root = &n1;

  EXPECT_EQ(Find(tree, 1 + 1), RST_FIND_NODE_DOESNT_EXIST);
  EXPECT_EQ(tree->root, &n1);
  EXPECT_EQ(tree->root->key, 1);
  EXPECT_EQ(tree->root->left, (node_t *)NULL);
  EXPECT_EQ(tree->root->right, (node_t *)NULL);
  EXPECT_EQ(tree->root->parent, (node_t *)NULL);

  free(tree);
}

TEST(DeleteTree_TreeWithInvalidPtr_CorrectProcessing) {
  DeleteTree(NULL);
}

TEST(DeleteTree_EmptyTree_CorrectProcessing) {
  rst_t *tree = GetTree();

  DeleteTree(tree);
}

TEST(Delete_CorrectTree_CorrectProcessing) {
  rst_t *tree = GetTree();

  node_t *n1 = (node_t *)malloc(sizeof(node_t));
  n1->key = 1;
  n1->left = NULL;
  n1->right = NULL;
  n1->parent = NULL;
  n1->prior = 1;

  tree->root = n1;

  DeleteTree(tree);
}
