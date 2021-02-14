#include "pch.h"

extern "C"
{
#include "tree.h"
}

treap_t * Create1NodeTreap() {
  treap_t* node1 = (treap_t*)malloc(sizeof(treap_t));
  node1->data = 2;
  node1->prior = 0.1;
  node1->parent = NULL;
  node1->right = NULL;
  node1->left = NULL;

  return node1;
}

treap_t* Create2NodeLeftTreap() {
  treap_t* node1 = (treap_t*)malloc(sizeof(treap_t));
  treap_t* node2 = (treap_t*)malloc(sizeof(treap_t));

  node2->data = 1;
  node1->prior = 0.2;
  node2->parent = node1;
  node2->right = NULL;
  node2->left = NULL;

  node1->data = 2;
  node1->prior = 0.1;
  node1->parent = NULL;
  node1->right = NULL;
  node1->left = node2;

  return node1;
}

treap_t* Create2NodeRightTreap() {
  treap_t* node1 = (treap_t*)malloc(sizeof(treap_t));
  treap_t* node2 = (treap_t*)malloc(sizeof(treap_t));

  node2->data = 3;
  node1->prior = 0.2;
  node2->parent = node1;
  node2->right = NULL;
  node2->left = NULL;

  node1->data = 2;
  node1->prior = 0.1;
  node1->parent = NULL;
  node1->left = NULL;
  node1->right = node2;

  return node1;
}

treap_t* Create3NodeTreap() {
  treap_t* node1 = (treap_t*)malloc(sizeof(treap_t));
  treap_t* node2 = (treap_t*)malloc(sizeof(treap_t));
  treap_t* node3 = (treap_t*)malloc(sizeof(treap_t));

  node3->data = 1;
  node1->prior = 0.3;
  node3->parent = node1;
  node3->right = NULL;
  node3->left = NULL;

  node2->data = 3;
  node1->prior = 0.2;
  node2->parent = node1;
  node2->right = NULL;
  node2->left = NULL;

  node1->data = 2;
  node1->prior = 0.1;
  node1->parent = NULL;
  node1->left = node3;
  node1->right = node2;

  return node1;
}


TEST(AddToTreap_AddToEmptyTreap_notCrush) {
  treap_t* tree = NULL;
  int res = TreapAdd(&tree, 2);

  ASSERT_EQ(res == LABH_TRUE, 1);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->left == NULL, 1);
  ASSERT_EQ(tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);
}

TEST(AddToTreap_AddNotToEmptyTreap_notCrush) {
  treap_t* tree = Create1NodeTreap();
  // добавляем уже существующий и проверим что res=false;
  int res = TreapAdd(&tree, 2);
  ASSERT_EQ(res == LABH_FALSE, 1);

  res = TreapAdd(&tree, 3);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->left == NULL && tree->right == NULL, 0);
  ASSERT_EQ(tree->parent == NULL, 1);

  res = TreapAdd(&tree, 1);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->left == NULL && tree->right == NULL, 0);
  ASSERT_EQ(tree->parent == NULL, 1);
}

TEST(DeleteFromTreap_AddToEmptyTreap_returnFALSE) {
  treap_t* tree = NULL;
  int res = TreapRemove(&tree, 2);
  ASSERT_EQ(res == LABH_FALSE, 1);
}

TEST(DeleteFromTreap_AddNotToEmptyTreap_notCrush) {
  treap_t* tree = Create3NodeTreap();
  // удаляем несуществующий и проверим что res=false;
  int res = TreapRemove(&tree, 100);
  ASSERT_EQ(res == LABH_FALSE, 1);

  res = TreapRemove(&tree, 3);
  ASSERT_EQ(res == LABH_TRUE, 1);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->left == NULL && tree->right == NULL, 0);
  ASSERT_EQ(tree->parent == NULL, 1);

  res = TreapRemove(&tree, 1);
  ASSERT_EQ(tree->data == 2, 1);
  ASSERT_EQ(tree->left == NULL && tree->right == NULL, 1);
  ASSERT_EQ(tree->parent == NULL, 1);

  res = TreapRemove(&tree, 2);
  ASSERT_EQ(tree == NULL, 1);
}

TEST(FindInTreap_notCrush) {
  // пустое дерево
  treap_t* tree = NULL;
  int res = TreapFind(tree, 100);
  ASSERT_EQ(res == LABH_FALSE, 1);

  // 1 элемент в дереве
  tree = Create1NodeTreap();
  // поиск несуществующего элемента
  res = TreapFind(tree, 100);
  ASSERT_EQ(res == LABH_FALSE, 1);
  // поиск существующего элемента
  res = TreapFind(tree, 2);
  ASSERT_EQ(res == LABH_FALSE, 0);

  // 2 элемента в дереве
  tree = Create2NodeLeftTreap();
  // поиск несуществующего элемента
  res = TreapFind(tree, 100);
  ASSERT_EQ(res == LABH_FALSE, 1);
  // поиск существующего элемента
  res = TreapFind(tree, 2);
  ASSERT_EQ(res == LABH_FALSE, 0);
  res = TreapFind(tree, 1);
  ASSERT_EQ(res == LABH_FALSE, 0);

  // 3 элемента в дереве
  tree = Create3NodeTreap();
  // поиск несуществующего элемента
  res = TreapFind(tree, 100);
  ASSERT_EQ(res == LABH_FALSE, 1);
  // поиск существующего элемента
  res = TreapFind(tree, 2);
  ASSERT_EQ(res == LABH_FALSE, 0);
  res = TreapFind(tree, 1);
  ASSERT_EQ(res == LABH_FALSE, 0);
  res = TreapFind(tree, 3);
  ASSERT_EQ(res == LABH_FALSE, 0);
}
