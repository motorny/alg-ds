#include "pch.h"

extern "C" {
#include"../alg-lab1_attempt2/Lab-H.c"
}
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
TEST(KeyInsert, KeyInsert_EmptyTree_RemoveSuccess) {
  b_tree* tree = NULL;
  KeyInsert(1, &tree);
  ASSERT_EQ(tree->n, 1);
  ASSERT_EQ(tree->isLeaf, TRUE);
  ASSERT_EQ(tree->keys[0], 1);
}

TEST(KeyInsert, KeyInsert_FullNode_SuccessfulSplit) {
  b_tree* tree = NULL;
  KeyInsert(1, &tree);
  KeyInsert(2, &tree);
  KeyInsert(3, &tree);
  KeyInsert(4, &tree);
  KeyInsert(5, &tree);

  KeyInsert(6, &tree);

  ASSERT_EQ(tree->n, 1);
  ASSERT_EQ(tree->isLeaf, FALSE);
  ASSERT_EQ(tree->keys[0], 3);

  ASSERT_EQ(tree->c[0]->n, 2);
  ASSERT_EQ(tree->c[0]->isLeaf, TRUE);
  ASSERT_EQ(tree->c[0]->keys[0], 1);
  ASSERT_EQ(tree->c[0]->keys[1], 2);

  ASSERT_EQ(tree->c[1]->n, 3);
  ASSERT_EQ(tree->c[1]->isLeaf, TRUE);
  ASSERT_EQ(tree->c[1]->keys[0], 4);
  ASSERT_EQ(tree->c[1]->keys[1], 5);
  ASSERT_EQ(tree->c[1]->keys[2], 6);

  free(tree->c[0]);
  free(tree->c[1]);
  free(tree);
}

TEST(KeyFind, KeyFind_KeyExists_ReturnsTrue_KeyDoesNotExist_ReturnFalse) {
  b_tree* tree = NULL;
  KeyInsert(1, &tree);

  ASSERT_EQ(KeyFind(tree, 1), TRUE);
  ASSERT_EQ(KeyFind(tree, 2), FALSE);

  free(tree);
}

TEST(KeyRemove, KeyRemove_KeyExists_RemoveSuccessfully) {
  KeyInsert(1, &root); //global var
  KeyInsert(2, &root);

  KeyRemove(2);

  ASSERT_EQ(root->n, 1);
  ASSERT_EQ(root->isLeaf, TRUE);
  ASSERT_EQ(root->keys[0], 1);

  free(root);
}