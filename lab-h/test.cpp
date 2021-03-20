#include "pch.h"
extern "C" {
#include "../H50_KabanovaAnna/AA_tree.h"
}


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Insert, AddOneElem) {
	aatree_t* tree = NULL;
	Insert(&tree, 3);
	ASSERT_EQ(3, tree->data);
	FreeTree(tree);
}

TEST(Insert, InsertTwoElems) {
	aatree_t* tree = NULL;
	Insert(&tree, 3);
	Insert(&tree, 2);
	ASSERT_EQ(3, tree->data);
	ASSERT_EQ(2, tree->left->data);
	FreeTree(tree);
}

TEST(Delete, DeleteNotExisting) {
	aatree_t* tree = NULL;
	Insert(&tree, 3);
	Insert(&tree, 2);
	ASSERT_EQ(3, tree->data);
	ASSERT_EQ(2, tree->left->data);
	DeleteNode(&tree, 1);
	ASSERT_EQ(3, tree->data);
	ASSERT_EQ(2, tree->left->data);
	FreeTree(tree);
}

TEST(Delete, DeleteExisting) {
	aatree_t* tree = NULL;
	Insert(&tree, 3);
	Insert(&tree, 2);
	ASSERT_EQ(3, tree->data);
	ASSERT_EQ(2, tree->left->data);
	DeleteNode(&tree, 2);
	ASSERT_EQ(3, tree->data);
	ASSERT_EQ(NULL, tree->left->data);
	FreeTree(tree);
}

TEST(Find, FindNotExisting) {
	aatree_t* tree = NULL;
	Insert(&tree, 3);
	Insert(&tree, 2);
	ASSERT_EQ(FALSE, FindNode(tree, 1));
	FreeTree(tree);
}

TEST(Find, FindExisting) {
	aatree_t* tree = NULL;
	Insert(&tree, 3);
	Insert(&tree, 2);
	ASSERT_EQ(TRUE, FindNode(tree, 2));
	FreeTree(tree);
}