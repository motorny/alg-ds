#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <string.h>

extern "C" {
#include "H10.h"
}

TEST(TestFindKey, NULLTree_ReturnFalse) {
  AVL_t* root = NULL;
  int isFound;


  FindKey(root, 1, &isFound);
  ASSERT_EQ(0, isFound);
}

TEST(TestFindKey, KeyExists_ReturnTrue) {
  AVL_t* root = NULL;
  int isFound;

  root = (AVL_t*)malloc(sizeof(AVL_t));
  root->key = 2;
  root->h = 2;

  root->l = (AVL_t*)malloc(sizeof(AVL_t));
  root->l->key = 1;
  root->l->l = root->l->r = NULL;
  root->l->h = 1;

  root->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->key = 3;
  root->r->l = root->r->r = NULL;
  root->r->h = 1;


  FindKey(root, 1, &isFound);
  ASSERT_EQ(1, isFound);

  free(root->l);
  free(root->r);
  free(root);
}

TEST(TestFindKey, KeyDoesNotExist_ReturnFalse) {
  AVL_t* root = NULL;
  int isFound;

  root = (AVL_t*)malloc(sizeof(AVL_t));
  root->key = 2;
  root->h = 2;

  root->l = (AVL_t*)malloc(sizeof(AVL_t));
  root->l->key = 1;
  root->l->l = root->l->r = NULL;
  root->l->h = 1;

  root->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->key = 3;
  root->r->l = root->r->r = NULL;
  root->r->h = 1;

  FindKey(root, 5, &isFound);
  ASSERT_EQ(0, isFound);

  free(root->l);
  free(root->r);
  free(root);
}


TEST(TestAddKey, SimpleAdd_StructureIsCorrect) {
  AVL_t* root = NULL;
  int isFound;

  root = (AVL_t*)malloc(sizeof(AVL_t));
  root->key = 2;
  root->h = 2;

  root->l = (AVL_t*)malloc(sizeof(AVL_t));
  root->l->key = 1;
  root->l->l = root->l->r = NULL;
  root->l->h = 1;

  root->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->key = 3;
  root->r->l = root->r->r = NULL;
  root->r->h = 1;

  root = AddKey(root, 3);

  ASSERT_TRUE(root->r != NULL);
  ASSERT_EQ(2, root->h);
  ASSERT_EQ(3, root->r->key);
  ASSERT_EQ(NULL, root->r->l);
  ASSERT_EQ(NULL, root->r->r);
  ASSERT_EQ(1, root->r->h);

  free(root->l);
  free(root->r);
  free(root);
}

TEST(TestAddKey, AddWithRotation_StructureIsCorrect) {
  AVL_t* root = NULL;
  int isFound;

  root = (AVL_t*)malloc(sizeof(AVL_t));
  root->key = 1;
  root->h = 2;

  root->l = NULL;
  root->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->key = 2;
  root->r->l = root->r->r = NULL;
  root->r->h = 1;

  root = AddKey(root, 3);

  ASSERT_EQ(2, root->key);
  ASSERT_TRUE(root->l != NULL);
  ASSERT_TRUE(root->r != NULL);
  ASSERT_EQ(2, root->h);

  ASSERT_EQ(1, root->l->key);
  ASSERT_EQ(NULL, root->l->l);
  ASSERT_EQ(NULL, root->l->r);
  ASSERT_EQ(1, root->l->h);

  ASSERT_EQ(3, root->r->key);
  ASSERT_EQ(NULL, root->r->l);
  ASSERT_EQ(NULL, root->r->r);
  ASSERT_EQ(1, root->r->h);

  free(root->l);
  free(root->r);
  free(root);
}

TEST(TestAddKey, AddWithDoubleRotation_StructureIsCorrect) {
  AVL_t* root = NULL;
  int isFound;

  root = (AVL_t*)malloc(sizeof(AVL_t));
  root->key = 1;
  root->h = 2;

  root->l = NULL;
  root->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->key = 3;
  root->r->l = root->r->r = NULL;
  root->r->h = 1;

  root = AddKey(root, 2);

  ASSERT_EQ(2, root->key);
  ASSERT_TRUE(root->l != NULL);
  ASSERT_TRUE(root->r != NULL);
  ASSERT_EQ(2, root->h);

  ASSERT_EQ(1, root->l->key);
  ASSERT_EQ(NULL, root->l->l);
  ASSERT_EQ(NULL, root->l->r);
  ASSERT_EQ(1, root->l->h);

  ASSERT_EQ(3, root->r->key);
  ASSERT_EQ(NULL, root->r->l);
  ASSERT_EQ(NULL, root->r->r);
  ASSERT_EQ(1, root->r->h);

  free(root->l);
  free(root->r);
  free(root);
}


TEST(TestRemoveKey, SimpleRemove_StructureIsCorrect) {
  AVL_t* root = NULL;
  int isFound;

  root = (AVL_t*)malloc(sizeof(AVL_t));
  root->key = 2;
  root->h = 2;

  root->l = (AVL_t*)malloc(sizeof(AVL_t));
  root->l->key = 1;
  root->l->l = root->l->r = NULL;
  root->l->h = 1;

  root->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->key = 3;
  root->r->l = root->r->r = NULL;
  root->r->h = 1;

  root = RemoveKey(root, 3);

  ASSERT_EQ(2, root->key);
  ASSERT_TRUE(root->l != NULL);
  ASSERT_EQ(NULL, root->r);
  ASSERT_EQ(2, root->h);

  ASSERT_EQ(1, root->l->key);
  ASSERT_EQ(NULL, root->l->l);
  ASSERT_EQ(NULL, root->l->r);
  ASSERT_EQ(1, root->l->h);

  free(root->l);
  free(root);
}

TEST(TestRemoveKey, RemoveWithRotation_StructureIsCorrect) {
  AVL_t* root = NULL;
  int isFound;

  root = (AVL_t*)malloc(sizeof(AVL_t));
  root->key = 2;
  root->h = 3;

  root->l = (AVL_t*)malloc(sizeof(AVL_t));
  root->l->key = 1;
  root->l->l = root->l->r = NULL;
  root->l->h = 1;

  root->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->key = 3;
  root->r->l = NULL;
  root->r->h = 2;

  root->r->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->r->key = 4;
  root->r->r->l = root->r->r->r = NULL;
  root->r->r->h = 1;

  root = RemoveKey(root, 1);

  ASSERT_EQ(3, root->key);
  ASSERT_TRUE(root->l != NULL);
  ASSERT_TRUE(root->r != NULL);
  ASSERT_EQ(2, root->h);

  ASSERT_EQ(2, root->l->key);
  ASSERT_EQ(NULL, root->l->l);
  ASSERT_EQ(NULL, root->l->r);
  ASSERT_EQ(1, root->l->h);

  ASSERT_EQ(4, root->r->key);
  ASSERT_EQ(NULL, root->r->l);
  ASSERT_EQ(NULL, root->r->r);
  ASSERT_EQ(1, root->r->h);

  free(root->l);
  free(root->r);
  free(root);
}

TEST(TestRemoveKey, RemoveWithDoubleRotation_StructureIsCorrect) {
  AVL_t* root = NULL;
  int isFound;

  root = (AVL_t*)malloc(sizeof(AVL_t));
  root->key = 2;
  root->h = 3;

  root->l = (AVL_t*)malloc(sizeof(AVL_t));
  root->l->key = 1;
  root->l->l = root->l->r = NULL;
  root->l->h = 1;

  root->r = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->key = 4;
  root->r->r = NULL;
  root->r->h = 2;

  root->r->l = (AVL_t*)malloc(sizeof(AVL_t));
  root->r->l->key = 3;
  root->r->l->l = root->r->l->r = NULL;
  root->r->l->h = 1;

  root = RemoveKey(root, 1);

  ASSERT_EQ(3, root->key);
  ASSERT_TRUE(root->l != NULL);
  ASSERT_TRUE(root->r != NULL);
  ASSERT_EQ(2, root->h);

  ASSERT_EQ(2, root->l->key);
  ASSERT_EQ(NULL, root->l->l);
  ASSERT_EQ(NULL, root->l->r);
  ASSERT_EQ(1, root->l->h);

  ASSERT_EQ(4, root->r->key);
  ASSERT_EQ(NULL, root->r->l);
  ASSERT_EQ(NULL, root->r->r);
  ASSERT_EQ(1, root->r->h);

  free(root->l);
  free(root->r);
  free(root);
}

int main(int argc, char** argv) {

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}