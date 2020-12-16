#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

extern "C" {
#include "E3.h"
}

TEST(TestAddNode, AddRoot_KeyIsSet_OtherFieldsEqZero) {
  tree_t* t = NULL;
  int flag;

  t = AddNode(t, 1, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(0, t->lH);
  ASSERT_EQ(0, t->rH);
  ASSERT_EQ(0, t->minH);
  ASSERT_EQ(0, t->maxH);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->right);

  DestroyTree(t);
}

TEST(TestAddNode, AddLeaf_TreeOrganizationMeetsExpectations) {
  tree_t* t = NULL;
  int flag;

  t = AddNode(t, 1, &flag);
  t = AddNode(t, 2, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(0, t->lH);
  ASSERT_EQ(1, t->rH);
  ASSERT_EQ(0, t->minH);
  ASSERT_EQ(1, t->maxH);
  ASSERT_EQ(NULL, t->left);

  ASSERT_EQ(2, t->right->key);
  ASSERT_EQ(0, t->right->lH);
  ASSERT_EQ(0, t->right->rH);
  ASSERT_EQ(0, t->right->minH);
  ASSERT_EQ(0, t->right->maxH);
  ASSERT_EQ(NULL, t->right->left);
  ASSERT_EQ(NULL, t->right->right);

  DestroyTree(t);
}

TEST(TestAddNode, AddExistingNode_FlagDoneEqZero) {
  tree_t* t = NULL;
  int flag;

  t = AddNode(t, 1, &flag);
  t = AddNode(t, 2, &flag);
  t = AddNode(t, 2, &flag);

  ASSERT_EQ(0, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(0, t->lH);
  ASSERT_EQ(1, t->rH);
  ASSERT_EQ(0, t->minH);
  ASSERT_EQ(1, t->maxH);
  ASSERT_EQ(NULL, t->left);

  ASSERT_EQ(2, t->right->key);
  ASSERT_EQ(0, t->right->lH);
  ASSERT_EQ(0, t->right->rH);
  ASSERT_EQ(0, t->right->minH);
  ASSERT_EQ(0, t->right->maxH);
  ASSERT_EQ(NULL, t->right->left);
  ASSERT_EQ(NULL, t->right->right);

  DestroyTree(t);
}

tree_t* CreateSimpleTree1(void) {
  tree_t* t = NULL;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 1;
  t->lH = 0;
  t->rH = 1;
  t->minH = 0;
  t->maxH = 1;
  t->left = NULL;

  t->right = (tree_t*)malloc(sizeof(tree_t));
  t->right->key = 2;
  t->right->lH = 0;
  t->right->rH = 0;
  t->right->minH = 0;
  t->right->maxH = 0;
  t->right->left = NULL;
  t->right->right = NULL;

  return t;
}

tree_t* CreateSimpleTree2(void) {
  tree_t* t = NULL;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 2;
  t->lH = 1;
  t->rH = 1;
  t->minH = 1;
  t->maxH = 1;

  t->left = (tree_t*)malloc(sizeof(tree_t));
  t->left->key = 1;
  t->left->lH = 0;
  t->left->rH = 0;
  t->left->minH = 0;
  t->left->maxH = 0;
  t->left->left = NULL;
  t->left->right = NULL;

  t->right = (tree_t*)malloc(sizeof(tree_t));
  t->right->key = 3;
  t->right->lH = 0;
  t->right->rH = 0;
  t->right->minH = 0;
  t->right->maxH = 0;
  t->right->left = NULL;
  t->right->right = NULL;

  return t;
}

TEST(TestDelNode, DelLeaf_TreeOrganizationMeetsExpectations) {
  tree_t* t = CreateSimpleTree1();
  int flag;

  t = DelNode(t, 2, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(0, t->lH);
  ASSERT_EQ(0, t->rH);
  ASSERT_EQ(0, t->minH);
  ASSERT_EQ(0, t->maxH);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->right);

  DestroyTree(t);
}

TEST(TestDelNode, DelNodeWithOneSon_TreeOrganizationMeetsExpectations) {
  tree_t* t = CreateSimpleTree1();
  int flag;

  t = DelNode(t, 1, &flag);

  ASSERT_EQ(1, flag);
  ASSERT_EQ(2, t->key);
  ASSERT_EQ(0, t->lH);
  ASSERT_EQ(0, t->rH);
  ASSERT_EQ(0, t->minH);
  ASSERT_EQ(0, t->maxH);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->right);

  DestroyTree(t);
}

TEST(TestDelNode, DelNodeWithTwoSons_TreeOrganizationMeetsExpectations) {
  tree_t* t = CreateSimpleTree2();
  int flag;

  t = DelNode(t, 2, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(0, t->lH);
  ASSERT_EQ(1, t->rH);
  ASSERT_EQ(0, t->minH);
  ASSERT_EQ(1, t->maxH);
  ASSERT_EQ(NULL, t->left);

  ASSERT_EQ(3, t->right->key);
  ASSERT_EQ(0, t->right->lH);
  ASSERT_EQ(0, t->right->rH);
  ASSERT_EQ(0, t->right->minH);
  ASSERT_EQ(0, t->right->maxH);
  ASSERT_EQ(NULL, t->right->left);
  ASSERT_EQ(NULL, t->right->right);

  DestroyTree(t);
}

TEST(TestDelNode, DelNonExistingNode_FlagDoneEqZero) {
  tree_t* t = CreateSimpleTree1();
  int flag;

  t = DelNode(t, 3, &flag);

  ASSERT_EQ(0, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(0, t->lH);
  ASSERT_EQ(1, t->rH);
  ASSERT_EQ(0, t->minH);
  ASSERT_EQ(1, t->maxH);
  ASSERT_EQ(NULL, t->left);

  ASSERT_EQ(2, t->right->key);
  ASSERT_EQ(0, t->right->lH);
  ASSERT_EQ(0, t->right->rH);
  ASSERT_EQ(0, t->right->minH);
  ASSERT_EQ(0, t->right->maxH);
  ASSERT_EQ(NULL, t->right->left);
  ASSERT_EQ(NULL, t->right->right);

  DestroyTree(t);
}

TEST(TestFindNode, FindExistingNode_FlagDoneEqOne) {
  tree_t* t = NULL;
  int flag;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 1;
  t->lH = t->rH = 0;
  t->minH = t->maxH = 0;
  t->left = t->right = NULL;

  t = FindNode(t, 1, &flag);

  ASSERT_EQ(1, flag);

  free(t);
}

TEST(TestFindNode, FindNonExistingNode_FlagDoneEqZero) {
  tree_t* t = NULL;
  int flag;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 1;
  t->lH = t->rH = 0;
  t->minH = t->maxH = 0;
  t->left = t->right = NULL;

  t = FindNode(t, 2, &flag);

  ASSERT_EQ(0, flag);

  free(t);
}

TEST(TestFillCells, TreeOfRootOnly_MatrixIsCorrect) {
  tree_t* t = NULL;
  cell_t* a = (cell_t*)malloc(sizeof(cell_t));
  int x = 0, y = 0;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 1;
  t->lH = t->rH = 0;
  t->minH = t->maxH = 0;
  t->left = t->right = NULL;

  FillCells(t, a, 1, &x, y);

  ASSERT_EQ(0, a[0].data);
  ASSERT_EQ(1, a[0].flagFilled);

  free(t);
  free(a);
}

TEST(TestFillCells, SimpleTree2_MatrixIsCorrect) {
  tree_t* t = CreateSimpleTree2();
  cell_t* a = (cell_t*)malloc(sizeof(cell_t) * 2 * 3);
  int x = 0, y = 0;

  FillCells(t, a, 3, &x, y);

  ASSERT_NE(1, a[0].flagFilled);
  ASSERT_NE(1, a[2].flagFilled);
  ASSERT_NE(1, a[4].flagFilled);

  ASSERT_EQ(1, a[1].data);
  ASSERT_EQ(1, a[1].flagFilled);
  ASSERT_EQ(0, a[3].data);
  ASSERT_EQ(1, a[3].flagFilled);
  ASSERT_EQ(0, a[5].data);
  ASSERT_EQ(1, a[5].flagFilled);

  DestroyTree(t);
  free(a);
}

int main(int argc, char** argv) {

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}