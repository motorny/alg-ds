#include "pch.h"
extern "C"
{
#include "BTree.h"
}

static BNode* CreateNode(int BTreeDegree)
{
  BNode* tmp = (BNode*)malloc(sizeof(BNode));
  tmp->n = 0;
  tmp->keys = (int *)malloc(sizeof(int) * (BTreeDegree - 1));
  tmp->child = (BNode **)malloc(sizeof(BNode*) * (BTreeDegree));
  return tmp;
}

BTree CreateTree(void)
{
  BNode* a, * b, * c;
  BTree t;
  t.M = 3;

  a = CreateNode(t.M);
  a->n = 1;
  a->keys[0] = 1;
  a->child[0] = NULL;
  a->child[1] = NULL;

  b = CreateNode(t.M);
  b->n = 1;
  b->keys[0] = 3;
  b->child[0] = NULL;
  b->child[1] = NULL;

  c = CreateNode(t.M);
  c->n = 1;
  c->keys[0] = 2;
  c->child[0] = a;
  c->child[1] = b;

  t.root = c;
  return t;
}

TEST(TreeAddElement_TreeNull_NotCrush) {
  ASSERT_EQ(BTreeInsert(NULL, 30), 0);
}

TEST(TreeAddElement_AddSame_NotCrush) {
  BTree t = CreateTree();
  ASSERT_EQ(BTreeInsert(&t, 2), 0);
  BTreeClear(&t);
}
TEST(TreeAddElement_Correct_NotCrush) {
  BTree t = CreateTree();
  ASSERT_EQ(BTreeInsert(&t, 30), 1);
  BTreeClear(&t);
}

TEST(TreeDeleteElement_TreeNull_NotCrush) {
  ASSERT_EQ(BTreeDelete(NULL, 30), 0);
}
TEST(TreeDeleteElement_DelNotExist_NotCrush) {
  BTree t = CreateTree();
  ASSERT_EQ(BTreeDelete(&t, 30), 0);
  BTreeClear(&t);
}
TEST(TreeDeleteElement_Correct_NotCrush) {
  BTree t = CreateTree();
  ASSERT_EQ(BTreeDelete(&t, 2), 1);
  BTreeClear(&t);
}
TEST(TreeFindElement_Exist_NotCrush) {
  BTree t = CreateTree();
  ASSERT_EQ(BTreeSearch(t, 2), TRUE);
  BTreeClear(&t);
}
TEST(TreeFindElement_NotExist_NotCrush) {
  BTree t = CreateTree();
  ASSERT_EQ(BTreeSearch(t, 300), FALSE);
  BTreeClear(&t);
}

TEST(TreeAdd_StressTest_NotCrush) {
  BTree t = { 0 };
  t.M = 30;
  for (int i = 0; i < 3000000; i++)
    switch (rand() % 3)
    {
    case 0:
      BTreeSearch(t, rand());
      break;
    case 1:
      BTreeInsert(&t, rand());
      break;
    case 2:
      BTreeDelete(&t, rand());
      break;
    default:
      break;
    }
  BTreeClear(&t);
}
