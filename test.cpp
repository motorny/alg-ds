#include "pch.h"
#include "../LAST PROJECT/bintree.c"

//Create test tree with keys
//         1
//       /   \ 
//      -1     2
tree_t* TestTree(void)
{
  vertex_t* key1, * key2, * keym1;
  tree_t* t;
  t = (tree_t*)malloc(sizeof(tree_t));
  key1 = (vertex_t*)malloc(sizeof(vertex_t));
  keym1 = (vertex_t*)malloc(sizeof(vertex_t));
  key2 = (vertex_t*)malloc(sizeof(vertex_t));
  if (!key1 || !key2 || !keym1 || !t) {
    return NULL;
  }

  key1->key = key1->data = 1;
  key1->width = 6;
  key1->parent = NULL;
  key1->right = key2;
  key1->left = keym1;

  keym1->key = keym1->data = -1;
  keym1->width = 2;
  keym1->parent = key1;
  keym1->left = keym1->right= NULL;

  key2->key = key2->data = 2;
  key2->width = 1;
  key2->parent = key1;
  key2->left = key2->right = NULL;
  t->root = key1;
  return t;
}

TEST(AddVertex, NULLTree_Returns_0) {
  ASSERT_EQ(AddVertex(NULL, 30,1), 0);
}

TEST(AddVertex, SameKey_Returns_0) {
  tree_t* tree = TestTree();
  ASSERT_EQ(AddVertex(tree, tree->root->key, 0), 0);
  TreeFree(tree);
}

TEST(AddVertex, NewKey_Returnes_1) {
  tree_t* tree = TestTree();
  ASSERT_EQ(AddVertex(tree,3,1), 1);
  TreeFree(tree);
}

TEST(DeleteVertex, NULLTree_Returnes_0) {
  ASSERT_EQ(DeleteVertex((vertex_t**)NULL,30), 0);
}

TEST(DeleteVertex, StrangerKey_Returns_0) {
  tree_t* tree = TestTree();
  ASSERT_EQ(DeleteVertex(NULL, 30), 0);
  TreeFree(tree);
}
TEST(DeleteVertex,OurKey_Returns_1) {
  tree_t* tree = TestTree();
  ASSERT_EQ(DeleteVertex(&tree->root, 2), 1);
  TreeFree(tree);
}

TEST(FindVertex, StrangerKey_Returns_0) {
  tree_t* tree = TestTree();
  ASSERT_EQ(FindVertex(*tree, -10),(vertex_t*)NULL);
  TreeFree(tree);
}
TEST(FindVertex, OurKey_Returns_CorrectPtr) {
  tree_t* tree = TestTree();
  ASSERT_EQ(FindVertex(*tree, 1), tree->root);
  TreeFree(tree);
}

TEST(UpdateWidth, Root_CorrectUpdate) {
  tree_t* tree = TestTree();
  int w1 = tree->root->width;
  int w2 = tree->root->left->width;
  int w3 = tree->root->right->width;
  UpdateWidth(tree->root);
  ASSERT_EQ(w1, tree->root->width);
  ASSERT_EQ(w2, tree->root->left->width);
  ASSERT_EQ(w3, tree->root->right->width);
}