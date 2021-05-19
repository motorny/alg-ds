#include "pch.h"

#include"../H12/main.cpp"


TEST(Add, EmptyTree_ReturnTRUE) {
  node_t* tree = NULL;
  ASSERT_EQ(AddKey(&tree,1), TRUE);
  ASSERT_EQ(tree->num, 1);
  ASSERT_EQ(tree->isLeaf, TRUE);
  ASSERT_EQ(tree->keys[0], 1);
}

TEST(Add, AddingNode_CorrectTree) {
  node_t* tree = NULL;
  AddKey(&tree, 1);
  AddKey(&tree, 2);
  AddKey(&tree, 3);
  AddKey(&tree, 4);
  AddKey(&tree, 5);

  ASSERT_EQ(AddKey(&tree, 6), TRUE);

  ASSERT_EQ(tree->num, 1);
  ASSERT_EQ(tree->isLeaf, FALSE);
  ASSERT_EQ(tree->keys[0], 3);

  ASSERT_EQ(tree->children[0]->num, 2);
  ASSERT_EQ(tree->children[0]->isLeaf, TRUE);
  ASSERT_EQ(tree->children[0]->keys[0], 1);
  ASSERT_EQ(tree->children[0]->keys[1], 2);

  ASSERT_EQ(tree->children[1]->num, 3);
  ASSERT_EQ(tree->children[1]->isLeaf, TRUE);
  ASSERT_EQ(tree->children[1]->keys[0], 4);
  ASSERT_EQ(tree->children[1]->keys[1], 5);
  ASSERT_EQ(tree->children[1]->keys[2], 6);

  free(tree->children[0]);
  free(tree->children[1]);
  free(tree);
}

TEST(Find, ExistKey_ReturnPtr) {
  node_t* tree = NULL;
  AddKey(&tree, 1);

  ASSERT_NE(FindKey(tree, 1), nullptr);

  free(tree);
}

TEST(Find, StrangerKey_ReturnNull) {
  node_t* tree = NULL;
  AddKey(&tree, 1);

  ASSERT_EQ(FindKey(tree, 2), nullptr);

  free(tree);
}

TEST(Remove, FillingTree_ReturnTRUE) {
  node_t* tree = NULL;
  AddKey(&tree, 1);
  AddKey(&tree, 2);

  ASSERT_EQ(RemoveKey(tree, 2), TRUE);

  ASSERT_EQ(tree->num, 1);
  ASSERT_EQ(tree->isLeaf, TRUE);
  ASSERT_EQ(tree->keys[0], 1);

  free(tree);
}

TEST(Destroy, NotEmptyTree_ReturnSuccess) {
  node_t* tree = NULL;
  AddKey(&tree, 1);
  AddKey(&tree, 2);
  AddKey(&tree, 3);

  EXPECT_EQ(DestroyTree(tree), TRUE);
}