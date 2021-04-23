#include "pch.h"
extern "C"
{
#include "Lab_H.h"
}

AATree CreateTree(void)
{
  node* a, * b, * c;
  AATree t;

  a = (node*)malloc(sizeof(node));
  a->value = 1;
  a->level = 1;
  a->left = a->right = NULL;

  b = (node*)malloc(sizeof(node));
  b->value = 3;
  b->level = 1;
  b->left = b->right = NULL;

  c = (node*)malloc(sizeof(node));
  c->value = 2;
  c->level = 2;
  c->left = a;
  c->right = b;

  t.Root = c;
  return t;
}

TEST(TreeAddElement_TreeNull_NotCrush) {
  ASSERT_EQ(AATreeAddElement(NULL, 30), 0);
}

TEST(TreeAddElement_AddSame_NotCrush) {
  AATree t = CreateTree();
  ASSERT_EQ(AATreeAddElement(&t, 2), 0);
  AATreeFree(&t);
}
TEST(TreeAddElement_Correct_NotCrush) {
  AATree t = CreateTree();
  ASSERT_EQ(AATreeAddElement(&t, 30), 1);
  AATreeFree(&t);
}

TEST(TreeDeleteElement_TreeNull_NotCrush) {
  ASSERT_EQ(AATreeDeleteElement(NULL, 30), 0);
}
TEST(TreeDeleteElement_DelNotExist_NotCrush) {
  AATree t = CreateTree();
  ASSERT_EQ(AATreeDeleteElement(&t, 30), 0);
  AATreeFree(&t);
}
TEST(TreeDeleteElement_Correct_NotCrush) {
  AATree t = CreateTree();
  ASSERT_EQ(AATreeDeleteElement(&t, 2), 1);
  AATreeFree(&t);
}
TEST(TreeFindElement_Exist_NotCrush) {
  AATree t = CreateTree();
  ASSERT_EQ(AATreeFindElement(t, 2), TRUE);
  AATreeFree(&t);
}
TEST(TreeFindElement_NotExist_NotCrush) {
  AATree t = CreateTree();
  ASSERT_EQ(AATreeFindElement(t, 300), FALSE);
  AATreeFree(&t);
}

TEST(TreeAdd_StressTest_NotCrush) {
  AATree t = { 0 };
  for (int i = 0; i < 3000000; i++)
    switch (rand() % 3)
    {
    case 0:
      AATreeFindElement(t, rand());
      break;
    case 1:
      AATreeAddElement(&t, rand());
      break;
    case 2:
      AATreeDeleteElement(&t, rand());
      break;
    default:
      break;
    }
  AATreeFree(&t);
}
