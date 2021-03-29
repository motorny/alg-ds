#include "pch.h"
#include "pch.h"
#include "../PROECT_LAB1/avl.cpp"

//test tree
//        1
//   -1       2
tree_t* TestTree(void)
{
  node_t* key1, * key2, * keym1;
  tree_t* t;
  t = (tree_t*)malloc(sizeof(tree_t));
  key1 = (node_t*)malloc(sizeof(node_t));
  keym1 = (node_t*)malloc(sizeof(node_t));
  key2 = (node_t*)malloc(sizeof(node_t));
  if (!key1 || !key2 || !keym1 || !t) {
    return NULL;
  }

  key1->key = key1->data = 1;
  key1->parent = NULL;
  key1->right = key2;
  key1->left = keym1;
  key1->height = 1;

  keym1->key = keym1->data = -1;
  keym1->parent = key1;
  keym1->left = keym1->right = NULL;
  keym1->height = key2->height = 0;

  key2->key = key2->data = 2;
  key2->parent = key1;
  key2->left = key2->right = NULL;
  t->root = key1;
  return t;
}

tree_t* TestRightTree() {
  node_t* k1, * k2, *k3, *k4, *k5;
  tree_t* t;
  t = (tree_t*)malloc(sizeof(tree_t));              //        2
  k1 = (node_t*)malloc(sizeof(node_t));             //       /  \ 
  k2 = (node_t*)malloc(sizeof(node_t));             //      1    4       
  k3 = (node_t*)malloc(sizeof(node_t));             //          / \    
  k4 = (node_t*)malloc(sizeof(node_t));             //         3   5
  k5 = (node_t*)malloc(sizeof(node_t));             //
  if (!k1 || !k3 || !k2 || !k4 || !k5 || !t) {
    return NULL;
  }
  
  k2->height = 2;
  k2->key = 2;
  k2->left = k1;
  k2->right = k4;
  k2->parent = NULL;

  k1->height = 0;
  k1->key = 1;
  k1->left = NULL;
  k1->right = NULL;
  k1->parent = k2;

  k4->height = 1;
  k4->key = 4;
  k4->left = k3;
  k4->right = k5;
  k4->parent = k2;

  k3->height = 0;
  k3->key = 3;
  k3->left = NULL;
  k3->right = NULL;
  k3->parent = k4;

  k5->height = 0;
  k5->key = 5;
  k5->left = NULL;
  k5->right = NULL;
  k5->parent = k4;

  t->root = k2;
}

tree_t* TestLeftTree() {
  node_t* k1, * k2, * k3, * k4, * k5;
  tree_t* t;
  t = (tree_t*)malloc(sizeof(tree_t));              //         4
  k1 = (node_t*)malloc(sizeof(node_t));             //       /  \ 
  k2 = (node_t*)malloc(sizeof(node_t));             //      2    5
  k3 = (node_t*)malloc(sizeof(node_t));             //     / \     
  k4 = (node_t*)malloc(sizeof(node_t));             //    1   3  
  k5 = (node_t*)malloc(sizeof(node_t));             //
  if (!k1 || !k3 || !k2 || !k4 || !k5 || !t) {
    return NULL;
  }

  k4->height = 2;
  k4->key = 4;
  k4->left = k2;
  k4->right = k5;
  k4->parent = NULL;

  k2->height = 1;
  k2->key = 2;
  k2->left = k1;
  k2->right = k3;;
  k2->parent = k4;

  k1->height = 0;
  k1->key = 1;
  k1->left = NULL;
  k1->right = NULL;
  k1->parent = k2;

  k3->height = 0;
  k3->key = 3;
  k3->left = NULL;
  k3->right = NULL;
  k3->parent = k2;

  k5->height = 0;
  k5->key = 5;
  k5->left = NULL;
  k5->right = NULL;
  k5->parent = k4;

  t->root = k4;
}

TEST(AddVertex, NULLTree_Returns_0) {
  ASSERT_EQ(AddVertex(NULL, 30, 1), 0);
}

TEST(AddVertex, SameKey_Returns_0) {
  tree_t* tree = TestTree();
  ASSERT_EQ(AddVertex(tree, tree->root->key, 0), 0);
  TreeFree(tree);
}

TEST(AddVertex, NewKey_Returnes_1) {
  tree_t* tree = TestTree();
  ASSERT_EQ(AddVertex(tree, 3, 1), 1);
  TreeFree(tree);
}

TEST(DeleteVertex, NULLTree_Returnes_0) {
  ASSERT_EQ(DeleteVertex(NULL,NULL, 30), 0);
}

TEST(DeleteVertex, StrangerKey_Returns_0) {
  tree_t* tree = TestTree();
  ASSERT_EQ(DeleteVertex(tree,NULL, 30), 0);
  TreeFree(tree);
}
TEST(DeleteVertex, OurKey_Returns_1) {
  tree_t* tree = TestTree();
  ASSERT_EQ(DeleteVertex(tree,&tree->root, 2), 1);
  TreeFree(tree);
}

TEST(FindVertex, StrangerKey_Returns_0) {
  tree_t* tree = TestTree();
  ASSERT_EQ(FindVertex(*tree, -10), (node_t*)NULL);
  TreeFree(tree);
}
TEST(FindVertex, OurKey_Returns_CorrectPtr) {
  tree_t* tree = TestTree();
  ASSERT_EQ(FindVertex(*tree, 1), tree->root);
  TreeFree(tree);
}

TEST(LeftRotate, CorrectChangePositins) {
  tree_t* tree = TestRightTree(); 
  LeftRotate(tree, tree->root);
  ASSERT_EQ(tree->root->key, 4);
  ASSERT_EQ(tree->root->left->key, 2);
  ASSERT_EQ(tree->root->left->left->key, 1);
  ASSERT_EQ(tree->root->left->right->key, 3);
  ASSERT_EQ(tree->root->right->key, 5);
}

TEST(RightRotate, CorrectChangePositins) {
  tree_t* tree = TestLeftTree();
  RightRotate(tree, tree->root);
  ASSERT_EQ(tree->root->key, 2);
  ASSERT_EQ(tree->root->right->key, 4);
  ASSERT_EQ(tree->root->right->left->key, 1);
  ASSERT_EQ(tree->root->right->right->key, 5);
}
