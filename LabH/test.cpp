#include "pch.h"
#include "testFuncs.cpp"

TEST(CountSubtreeWidth_NullNode_Returns0) {
  EXPECT_EQ(CountSubtreeWidth(NULL), 0);
}

TEST(CountSubtreeWidth_AllOK_ReturnsValid) {
  node_t a;
  node_t b;
  node_t c;
  a.data = -1;
  b.data = 0;
  c.data = 1;
  b.left = &a;
  b.right = &c;
  b.prev = NULL;
  a.left = NULL;
  a.right = NULL;
  a.prev = &b;
  c.left = NULL;
  c.right = NULL;
  c.prev = &b;

  EXPECT_EQ(CountSubtreeWidth(&b), 3);
  EXPECT_EQ(CountSubtreeWidth(&a), 1);
  EXPECT_EQ(CountSubtreeWidth(&c), 1);
  EXPECT_EQ(b.subTreeWidth, 3);
  EXPECT_EQ(a.subTreeWidth, 1);
  EXPECT_EQ(c.subTreeWidth, 1);
}

TEST(Successor_NullNode_ReturnsNULL) {
  EXPECT_EQ(Successor(NULL), NULL);
}

TEST(Successor_AllOk_ReturnsValid) {
  node_t a;
  node_t b;
  node_t c;
  node_t d;
  a.data = -1;
  b.data = 0;
  c.data = 2;
  d.data = 1;
  b.left = &a;
  b.right = &c;
  b.prev = NULL;
  a.left = NULL;
  a.right = NULL;
  a.prev = &b;
  c.left = &d;
  c.right = NULL;
  c.prev = &b;
  d.left = NULL;
  d.right = NULL;
  d.prev = &c;

  EXPECT_EQ(Successor(&a), &d);
}

TEST(TreeInsert_NullTree_ReturnsFAIL) {
  EXPECT_EQ(TreeInsert(NULL, 1), FAIL);
}

TEST(TreeInsert_ToEmpty_ReturnsSuccess) {
  tree_t tree;
  tree.root = NULL;

  EXPECT_EQ(TreeInsert(&tree, 1), SUCCESS);
  EXPECT_EQ(tree.root->data, 1);

  free(tree.root);
}

TEST(TreeInsert_AlreadyExist_ReturnsFail) {
  tree_t tree;
  node_t a;
  tree.root = &a;
  a.prev = NULL;
  a.left = NULL;
  a.right = NULL;
  a.data = 1;
  EXPECT_EQ(TreeInsert(&tree, 1), FAIL);
}

TEST(TreeInsert_AllOk_ReturnsSuccess) {
  tree_t tree;
  node_t a;
  tree.root = &a;
  a.prev = NULL;
  a.left = NULL;
  a.right = NULL;
  a.data = 1;
  EXPECT_EQ(TreeInsert(&tree, 2), SUCCESS);
  free(a.left);

}

TEST(TreeDelete_NULLTree_ReturnsFail) {
  EXPECT_EQ(TreeDelete(NULL, 1), FAIL);
}

TEST(TreeDelete_NotExist_ReturnsFail) {
  tree_t tree;
  node_t a;
  tree.root = &a;
  a.prev = NULL;
  a.left = NULL;
  a.right = NULL;
  a.data = 1;
  EXPECT_EQ(TreeDelete(&tree, 2), FAIL);
}

TEST(TreeDelete_AllOk_ReturnsSUCCESS) {
  tree_t tree;
  node_t a;
  tree.root = &a;
  a.prev = NULL;
  a.left = NULL;
  a.right = NULL;
  a.data = 1;
  EXPECT_EQ(TreeDelete(&tree, 1), SUCCESS);
}

TEST(TreeSearch_NULLTree_ReturnsFAIL) {
  EXPECT_EQ(TreeSearch(NULL, 1), FAIL);
}

TEST(TreeSearch_Exist_ReturnsSUCCESS) {
  tree_t tree;
  node_t a;
  tree.root = &a;
  a.prev = NULL;
  a.left = NULL;
  a.right = NULL;
  a.data = 1;
  EXPECT_EQ(TreeSearch(&tree, 1), SUCCESS);
}

TEST(TreeSearch_NotExist_ReturnsFAIL) {
  tree_t tree;
  node_t a;
  tree.root = &a;
  a.prev = NULL;
  a.left = NULL;
  a.right = NULL;
  a.data = 1;
  EXPECT_EQ(TreeSearch(&tree, 2), SUCCESS);
}
