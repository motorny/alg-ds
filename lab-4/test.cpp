#include "pch.h"
extern "C"
{
  #include "tree.h"
}
tree CreateTree(void)
{
  node *a, *b, *c;
  tree t;

  a = (node*)malloc(sizeof(node));
  a->key = 1;
  a->number = 1;
  a->parent = NULL;
  a->width = 1;
  a->left = a->right = NULL;

  b = (node*)malloc(sizeof(node));
  b->key = 3;
  b->number = 1;
  b->parent = NULL;
  b->width = 1;
  b->left = b->right = NULL;

  c = (node*)malloc(sizeof(node));
  c->key = 2;
  c->number = 3;
  c->parent = NULL;
  c->width = 1;
  c->left = a;
  c->right = b;
  a->parent = c;
  b->parent = c;

  t.root = c;
  return t;
}

TEST(TreeAddElement_TreeNull_NotCrush) {
  ASSERT_EQ(TreeAddElement(NULL, 30), 0);
}

TEST(TreeAddElement_AddSame_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeAddElement(NULL, 2), 0);
  TreeFree(&t);
}
TEST(TreeAddElement_Correct_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeAddElement(&t, 30), 1);
  TreeFree(&t);
}

TEST(TreeDeleteElement_TreeNull_NotCrush) {
  ASSERT_EQ(TreeDeleteElement(NULL, 30), 0);
}
TEST(TreeDeleteElement_DelNotExist_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeDeleteElement(NULL, 30), 0);
  TreeFree(&t);
}
TEST(TreeDeleteElement_Correct_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeDeleteElement(&t, 2), 1);
  TreeFree(&t);
}
TEST(TreeFindElement_Exist_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeFindElement(t, 2), t.root);
  TreeFree(&t);
}
TEST(TreeFindElement_NotExist_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeFindElement(t, 300), (node *)NULL);
  TreeFree(&t);
}

TEST(TreePrint_Empty_NotCrush) {
  tree t = {0};
  TreePrint(t);
  TreeFree(&t);
}
TEST(TreePrint_NotEmpty_NotCrush) {
  tree t = CreateTree();
  TreePrint(t);
  TreeFree(&t);
}

TEST(TreeKLower_Exist_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeKLower(t, 2), t.root);
  TreeFree(&t);
}

TEST(TreeKLower_NotExist_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeKLower(t, 5), (node *)NULL);
  TreeFree(&t);
}

TEST(TreeKLower_Negative_NotCrush) {
  tree t = CreateTree();
  ASSERT_EQ(TreeKLower(t, -1), (node*)NULL);
  TreeFree(&t);
}