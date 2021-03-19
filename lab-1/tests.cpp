#include "pch.h"
#include <stdlib.h>

extern "C" {
#include "..//LAB_H//AA-tree.c"
}

tree_t* CreateTree() {
	tree_t* node1 = (tree_t*)malloc(sizeof(tree_t));
	tree_t* node2 = (tree_t*)malloc(sizeof(tree_t));
	tree_t* node3 = (tree_t*)malloc(sizeof(tree_t));
	if (node1 == NULL || node2 == NULL || node3 == NULL)
		return NULL;

	node3->key = 1;
	node3->level = 1;
	node3->right = NULL;
	node3->left = NULL;

	node2->key = 3;
	node2->level = 1;
	node2->right = NULL;
	node2->left = NULL;

	node1->key = 2;
	node1->level = 2;
	node1->left = node3;
	node1->right = node2;

	return node1;
}

TEST(OneNormalAdd, AddFunction) {
	tree_t* t = NULL;
	t = Add(t, 1);

	ASSERT_TRUE(t != NULL);
	EXPECT_TRUE(t->key == 1);
	EXPECT_TRUE(t->level == 1);
	EXPECT_TRUE(t->left == NULL);
	EXPECT_TRUE(t->right == NULL);
}

TEST(TwoNormalAdd, AddFunction) {
	tree_t* t = NULL;
	t = Add(t, 1);
	t = Add(t, 2);

	ASSERT_TRUE(t != NULL);
	EXPECT_TRUE(t->key == 1);
	EXPECT_TRUE(t->level == 1);
	EXPECT_TRUE(t->left == NULL);

	ASSERT_TRUE(t->right != NULL);
	EXPECT_TRUE(t->right->key == 2);
	EXPECT_TRUE(t->right->level == 1);
	EXPECT_TRUE(t->right->left == NULL);
	EXPECT_TRUE(t->right->right == NULL);
}

TEST(ThreeNormalAddWihtBalance, AddFunction) {
	tree_t* t = NULL;
	t = Add(t, 1);
	t = Add(t, 2);
	t = Add(t, 3);

	ASSERT_TRUE(t != NULL);
	EXPECT_TRUE(t->key == 2);
	EXPECT_TRUE(t->level == 2);

	ASSERT_TRUE(t->right != NULL);
	EXPECT_TRUE(t->right->key == 3);
	EXPECT_TRUE(t->right->level == 1);
	EXPECT_TRUE(t->right->left == NULL);
	EXPECT_TRUE(t->right->right == NULL);

	ASSERT_TRUE(t->left != NULL);
	EXPECT_TRUE(t->left->key == 1);
	EXPECT_TRUE(t->left->level == 1);
	EXPECT_TRUE(t->left->left == NULL);
	EXPECT_TRUE(t->left->right == NULL);
}

TEST(NormalCase, FindFunction) {
	tree_t* t = CreateTree();

	tree_t* check = Find(t, 2);
	EXPECT_TRUE(check == t);

	check = Find(t, 1);
	EXPECT_TRUE(check == t->left);
}

TEST(FailCase, FindFunction) {
	tree_t* t = CreateTree();

	tree_t* check = Find(t, 0);
	EXPECT_TRUE(check == NULL);
}

TEST(LeafCase, DelFunction) {
	tree_t* t = CreateTree();

	EXPECT_TRUE(t->left != NULL);
	Del(&t, 1);
	EXPECT_TRUE(t->left == NULL);

	EXPECT_TRUE(t->right != NULL);
	Del(&t, 3);
	EXPECT_TRUE(t->right == NULL);
}

TEST(NodeCase, DelFunction) {
	tree_t* t = CreateTree();

	Del(&t, 2);
	EXPECT_TRUE(t->key == 1);
	EXPECT_TRUE(t->right->key == 3);
}

