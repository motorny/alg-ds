#include "pch.h"
#include <stdlib.h>

extern "C" {
#include "..//LAB_E_F//lab_F.c"
}

node_t* CreateTree1() {
	node_t* node1 = (node_t*)malloc(sizeof(node_t));
	if (node1 == NULL)
		return NULL;
	node1->key = 2;
	node1->number = 1;
	node1->left = NULL;
	node1->right = NULL;
	node1->father = NULL;

	return node1;
}
node_t* CreateTree2() {
	node_t* node1 = (node_t*)malloc(sizeof(node_t));
	node_t* node2 = (node_t*)malloc(sizeof(node_t));
	if (node1 == NULL || node2 == NULL)
		return NULL;

	node2->key = 1;
	node2->number = 1;
	node2->left = NULL;
	node2->right = NULL;
	node2->father = node1;

	node1->key = 2;
	node1->number = 2;
	node1->left = node2;
	node1->right = NULL;
	node1->father = NULL;

	return node1;
}
node_t* CreateTree3() {
	node_t* node1 = (node_t*)malloc(sizeof(node_t));
	node_t* node2 = (node_t*)malloc(sizeof(node_t));
	node_t* node3 = (node_t*)malloc(sizeof(node_t));
	if (node1 == NULL || node2 == NULL || node3 == NULL)
		return NULL;

	node3->key = 1;
	node3->number = 1;
	node3->right = NULL;
	node3->left = NULL;
	node3->father = node1;

	node2->key = 3;
	node2->number = 1;
	node2->right = NULL;
	node2->left = NULL;
	node2->father = node1;

	node1->key = 2;
	node1->number = 3;
	node1->left = node3;
	node1->right = node2;
	node1->father = NULL;

	return node1;
}

TEST(EmptyNormalAdd, AddFunction) {
	node_t* tree = NULL;
	int check = Add(&tree, NULL, 2);

	EXPECT_TRUE(check == 1);
	EXPECT_TRUE(tree->key == 2);
	EXPECT_TRUE(tree->left == NULL);
	EXPECT_TRUE(tree->right == NULL);
	EXPECT_TRUE(tree->father == NULL);
	EXPECT_TRUE(tree->number == 1);
}

TEST(NotEmptyNormalAdd, AddFunction) {
	node_t* tree = CreateTree1();
	int check = Add(&tree, tree, 1);

	EXPECT_TRUE(check == 1);
	EXPECT_TRUE(tree->key == 2);
	EXPECT_TRUE(tree->left->key == 1 );
	EXPECT_TRUE(tree->left->father == tree);
	EXPECT_TRUE(tree->right == NULL);

	check = Add(&tree, tree, 3);
	EXPECT_TRUE(check == 1);
	EXPECT_TRUE(tree->key == 2);
	EXPECT_TRUE(tree->left->key == 1);
	EXPECT_TRUE(tree->right->key == 3);
	EXPECT_TRUE(tree->left->father == tree); 
	EXPECT_TRUE(tree->right->father == tree);

	check = Add(&tree, tree, 3);
	EXPECT_TRUE(check == 0);
}

TEST(NormalCase, FindFunction) {
	node_t* tree = CreateTree2();

	node_t* check = Find(tree, 2);
	EXPECT_TRUE(check == tree);

	check = Find(tree, 1);
	EXPECT_TRUE(check == tree->left);
}

TEST(FailCase, FindFunction) {
	node_t* tree = CreateTree2();

	node_t* check = Find(tree, 0);
	EXPECT_TRUE(check == NULL);
}

TEST(NullCase, FindOnKLowerFunction) {
	node_t* tree = CreateTree3();
	node_t* check = FindTreeLowerOnK(tree, 1, 1);
	EXPECT_TRUE(check == NULL);
}

TEST(ZeroKCase, FindOnKLowerFunction) {
	node_t* tree = CreateTree3();
	node_t* check;

	check = FindTreeLowerOnK(tree, 1, 0);
	EXPECT_TRUE(check == tree->left);
	check = FindTreeLowerOnK(tree, 2, 0);
	EXPECT_TRUE(check == tree);
	check = FindTreeLowerOnK(tree, 3, 0);
	EXPECT_TRUE(check == tree->right);
}

TEST(NormalCase, FindOnKLowerFunction) {
	node_t* tree = CreateTree3();
	node_t* check;

	check = FindTreeLowerOnK(tree, 1, 1);
	ASSERT_EQ(check == NULL, 1);
	check = FindTreeLowerOnK(tree, 2, 1);
	ASSERT_EQ(check == tree->left, 1);
	check = FindTreeLowerOnK(tree, 3, 1);
	ASSERT_EQ(check == tree, 1);
}