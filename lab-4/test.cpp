#include "pch.h"
#include "../FOURTH/mytree.cpp"

TEST(Create, One) {
  Node* root = CreateFreeNode(2, NULL);
  EXPECT_EQ(2, root->value);
  EXPECT_EQ(NULL, root->parent);
  EXPECT_EQ(NULL, root->left);
  EXPECT_EQ(NULL, root->right);
}

TEST(Destroy, One) {
  Node* root = NULL;
  InsertInTree(&root, 3);
  DestroyTree(&root);
  EXPECT_EQ(NULL, root);
}
TEST(Insert, One) {
  Node* root = NULL;
  InsertInTree(&root, 3);
  EXPECT_EQ(3, root->value);
  EXPECT_EQ(NULL, root->parent);
  EXPECT_EQ(NULL, root->left);
  EXPECT_EQ(NULL, root->right);
  DestroyTree(&root);
}
TEST(GetbyValue, One) {
  Node* root = NULL;
  Node* tmp = NULL;
  InsertInTree(&root, 3);
  tmp = GetNodeByValue(root, 3);
  EXPECT_EQ(root, tmp);
  DestroyTree(&root);
}
TEST(GetbyValue, Two) {
  Node* root = NULL;
  Node* tmp = NULL;
  InsertInTree(&root, 3);
  tmp = GetNodeByValue(root, 2);
  EXPECT_EQ(NULL, tmp);
  DestroyTree(&root);
}
TEST(RemoveNode, One) {
  Node* root = NULL;
  Node* tmp = NULL;
  InsertInTree(&root, 1);
  InsertInTree(&root, 2);
  InsertInTree(&root, 3);
  tmp = GetNodeByValue(root, 2);
  RemoveNodeByPtr(tmp);
  EXPECT_EQ(3, root->right->value);
  DestroyTree(&root);
}
TEST(Delete, One) {
  Node* root = NULL;
  Node* tmp = NULL;
  InsertInTree(&root, 1);
  InsertInTree(&root, 2);
  DeleteValue(root, 2);
  tmp = GetNodeByValue(root, 2);
  EXPECT_EQ(NULL, tmp);
  DestroyTree(&root);
}

TEST(MinLeaves, One) {
  Node* root = NULL;
  InsertInTree(&root, 2);
  InsertInTree(&root, 1);
  InsertInTree(&root, 6);
  InsertInTree(&root, 0);
  InsertInTree(&root, 4);
  InsertInTree(&root, 8);
  InsertInTree(&root, 3);
  InsertInTree(&root, 5);
  MinHeightLeaves(root);
  EXPECT_EQ(2, root->value);
  EXPECT_EQ(1, root->left->value);
  EXPECT_EQ(0, root->left->left->value);
  EXPECT_EQ(1, root->right->value);
  EXPECT_EQ(1, root->right->left->value);
  EXPECT_EQ(0, root->right->right->value);
  EXPECT_EQ(0, root->right->left->left->value);
  EXPECT_EQ(0, root->right->left->right->value);
  DestroyTree(&root);
}
