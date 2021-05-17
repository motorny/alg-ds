#include "pch.h"
#include "gtest/gtest.h"
#include "../Lab-H/lab-h.c"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(Insert, AddElem) {
	Node* tree;
	Insert(2);
	Insert(5);
	tree = Insert(1);

	EXPECT_EQ(2, tree->key);
	EXPECT_EQ(1, tree->left->key);
	EXPECT_EQ(5, tree->right->key);
	EXPECT_EQ(NIL, tree->right->left);
	EXPECT_EQ(NIL, tree->right->right);

	Delete(2);
	Delete(5);
	Delete(1);

	//free(tree);
}


TEST(Insert, CheckColorElements) {
	
	Node* a;
	Insert(3);
	Insert(8);
	Insert(12);
	a = Insert(9);
	EXPECT_EQ(1, a->color);
	EXPECT_EQ(1, a->left->color);
	EXPECT_EQ(0, a->right->left->color);

	Delete(3);
	Delete(8);
	Delete(12);
	Delete(9);
}


TEST(Find, FindExistElements) {

	Node* tree;
	Insert(3);
	Insert(8);
	tree = Insert(12);

	EXPECT_EQ(tree, FindNode(8));
	EXPECT_EQ(tree->left, FindNode(3));
	EXPECT_EQ(tree->right, FindNode(12));

	Delete(3);
	Delete(8);
	Delete(12);
}


TEST(Find, FindNoExistElements) {

	Node* tree;
	Insert(3);
	Insert(8);
	tree = Insert(12);

	EXPECT_EQ(tree, FindNode(8));
	EXPECT_EQ(NULL, FindNode(5));
	EXPECT_EQ(NULL, FindNode(12724));

	Delete(3);
	Delete(8);
	Delete(12);
}


TEST(Delete, DeleteExistElement) {

	Node* tree;
	Insert(3);
	Insert(8);
	tree = Insert(12);

	EXPECT_EQ(tree, FindNode(8));
	EXPECT_EQ(tree->left, FindNode(3));
	EXPECT_EQ(tree->right, FindNode(12));

	Delete(3);
	Delete(8);
	Delete(12);

	EXPECT_EQ(NULL, FindNode(8));
	EXPECT_EQ(NULL, FindNode(3));
	EXPECT_EQ(NULL, FindNode(12));
}


TEST(Delete, DeleteNoExistElement) {

	Node* tree;
	Insert(3);
	Insert(8);
	tree = Insert(12);

	EXPECT_EQ(tree, FindNode(8));
	EXPECT_EQ(tree->left, FindNode(3));
	EXPECT_EQ(tree->right, FindNode(12));

	Delete(4);
	Delete(2);
	Delete(782);

	EXPECT_EQ(tree, FindNode(8));
	EXPECT_EQ(tree->left, FindNode(3));
	EXPECT_EQ(tree->right, FindNode(12));
}