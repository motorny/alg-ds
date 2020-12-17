#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

extern "C" {
#include "F21.h"
}

TEST(TestAddNode, AddRoot_KeyIsSet_OtherFieldsEqZero) {
  tree_t* t = NULL;
  int flag;

  t = AddNode(t, 1, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(1, t->subnodesQ);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->right);
  ASSERT_EQ(NULL, t->father);

  DestroyTree(t);
}

TEST(TestAddNode, AddLeaf_TreeOrganizationMeetsExpectations) {
  tree_t* t = NULL;
  int flag;

  t = AddNode(t, 1, &flag);
  t = AddNode(t, 2, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(2, t->subnodesQ);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->father);

  ASSERT_EQ(2, t->right->key);
  ASSERT_EQ(1, t->right->subnodesQ);
  ASSERT_EQ(NULL, t->right->left);
  ASSERT_EQ(NULL, t->right->right);
  ASSERT_EQ(t, t->right->father);

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
  ASSERT_EQ(2, t->subnodesQ);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->father);

  ASSERT_EQ(2, t->right->key);
  ASSERT_EQ(1, t->right->subnodesQ);
  ASSERT_EQ(NULL, t->right->left);
  ASSERT_EQ(NULL, t->right->right);
  ASSERT_EQ(t, t->right->father);

  DestroyTree(t);
}

tree_t* CreateSimpleTree1(void) {
  tree_t* t = NULL;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 1;
  t->subnodesQ = 2;
  t->left = NULL;
  t->father = NULL;

  t->right = (tree_t*)malloc(sizeof(tree_t));
  t->right->key = 2;
  t->right->subnodesQ = 1;
  t->right->left = NULL;
  t->right->right = NULL;
  t->right->father = t;

  return t;
}

tree_t* CreateSimpleTree2(void) {
  tree_t* t = NULL;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 2;
  t->subnodesQ = 3;
  t->father = NULL;

  t->left = (tree_t*)malloc(sizeof(tree_t));
  t->left->key = 1;
  t->left->subnodesQ = 1;
  t->left->left = NULL;
  t->left->right = NULL;
  t->left->father = t;

  t->right = (tree_t*)malloc(sizeof(tree_t));
  t->right->key = 3;
  t->right->subnodesQ = 1;
  t->right->left = NULL;
  t->right->right = NULL;
  t->right->father = t;

  return t;
}

TEST(TestDelNode, DelLeaf_TreeOrganizationMeetsExpectations) {
  tree_t* t = CreateSimpleTree1();
  int flag;

  t = DelNode(t, 2, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(1, t->subnodesQ);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->right);
  ASSERT_EQ(NULL, t->father);

  DestroyTree(t);
}

TEST(TestDelNode, DelNodeWithOneSon_TreeOrganizationMeetsExpectations) {
  tree_t* t = CreateSimpleTree1();
  int flag;

  t = DelNode(t, 1, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(2, t->key);
  ASSERT_EQ(1, t->subnodesQ);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->right);
  ASSERT_EQ(NULL, t->father);

  DestroyTree(t);
}

TEST(TestDelNode, DelNodeWithTwoSons_TreeOrganizationMeetsExpectations) {
  tree_t* t = CreateSimpleTree2();
  int flag;

  t = DelNode(t, 2, &flag);

  ASSERT_EQ(1, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(2, t->subnodesQ);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->father);

  ASSERT_EQ(3, t->right->key);
  ASSERT_EQ(1, t->right->subnodesQ);
  ASSERT_EQ(NULL, t->right->left);
  ASSERT_EQ(NULL, t->right->right);
  ASSERT_EQ(t, t->right->father);

  DestroyTree(t);
}

TEST(TestDelNode, DelNonExistingNode_FlagDoneEqZero) {
  tree_t* t = CreateSimpleTree1();
  int flag;

  t = DelNode(t, 3, &flag);

  ASSERT_EQ(0, flag);

  ASSERT_EQ(1, t->key);
  ASSERT_EQ(2, t->subnodesQ);
  ASSERT_EQ(NULL, t->left);
  ASSERT_EQ(NULL, t->father);

  ASSERT_EQ(2, t->right->key);
  ASSERT_EQ(1, t->right->subnodesQ);
  ASSERT_EQ(NULL, t->right->left);
  ASSERT_EQ(NULL, t->right->right);
  ASSERT_EQ(t, t->right->father);

  DestroyTree(t);
}

TEST(TestFindNode, FindExistingNode_FlagDoneEqOne) {
  tree_t* t = NULL;
  tree_t* ans = NULL;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 1;
  t->subnodesQ = 1;
  t->left = t->right = NULL;
  t->father = NULL;

  FindNode(t, 1, &ans);

  ASSERT_EQ(t, ans);

  free(t);
}

TEST(TestFindNode, FindNonExistingNode_FlagDoneEqZero) {
  tree_t* t = NULL;
  tree_t* ans = NULL;

  t = (tree_t*)malloc(sizeof(tree_t));
  t->key = 1;
  t->subnodesQ = 1;
  t->left = t->right = NULL;
  t->father = NULL;

  FindNode(t, 2, &ans);

  ASSERT_EQ(NULL, ans);

  free(t);
}

TEST(TestFindNodeSmallerByK, SecondOfSimpleTree1_ReturnPtrToFirst) {
  tree_t* t = CreateSimpleTree1();
  tree_t* ans;

  ans = FindNodeSmallerByK(t, 2, 1);
  ASSERT_EQ(t, ans);

  DestroyTree(t);
}

TEST(TestFindNodeSmallerByK, ThirdOfSimpleTree2_ReturnPtrToFirst) {
  tree_t* t = CreateSimpleTree2();
  tree_t* ans;

  ans = FindNodeSmallerByK(t, 3, 2);
  ASSERT_EQ(t->left, ans);

  DestroyTree(t);
}

TEST(TestFindNodeSmallerByK, SetNonExistingStartingNode_ReturnNULL) {
  tree_t* t = CreateSimpleTree2();
  tree_t* ans;

  ans = FindNodeSmallerByK(t, 4, 2);
  ASSERT_EQ(NULL, ans);

  DestroyTree(t);
}

TEST(TestFindNodeSmallerByK, ShiftProvokesNonPositiveIndex_ReturnNULL) {
  tree_t* t = CreateSimpleTree2();
  tree_t* ans;

  ans = FindNodeSmallerByK(t, 1, 2);
  ASSERT_EQ(NULL, ans);

  DestroyTree(t);
}

int main(int argc, char** argv) {

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}