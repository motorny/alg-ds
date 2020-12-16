#include "pch.h"
#include "../Alg_Lab_E/tree.c"


TEST(AddInTreeTest, AddInEmptyTree) {
	node_t* tree = NULL;
	AddInTree(&tree, 1);
	EXPECT_EQ(tree->num, 1);
	EXPECT_EQ(tree->right, (node_t*)NULL);
	EXPECT_EQ(tree->left, (node_t*)NULL);
	free(tree);
}

TEST(AddInTreeTest, AddInStartedTree) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));
	tree->num = 4;
	tree->left = NULL;
	tree->right = NULL;
	AddInTree(&tree, 2);
	AddInTree(&tree, 7);
	EXPECT_TRUE(tree->left != (node_t*)NULL);
	EXPECT_TRUE(tree->right != (node_t*)NULL);
	EXPECT_EQ(tree->left->num, 2);
	EXPECT_EQ(tree->right->num, 7);
	EXPECT_EQ(tree->left->left, (node_t*)NULL);
	EXPECT_EQ(tree->left->right, (node_t*)NULL);
	EXPECT_EQ(tree->right->left, (node_t*)NULL);
	EXPECT_EQ(tree->right->right, (node_t*)NULL);
	DestroyTree(tree);
}

TEST(SearchInTreeTest, FoundedElement) {
	node_t* tree = NULL;
	AddInTree(&tree, 1);
	AddInTree(&tree, 2);
	AddInTree(&tree, 7);
	EXPECT_EQ(SearchInTree(tree, 2), FOUND);
	DestroyTree(tree);
}

TEST(SearchInTreeTest, NotFoundedElement) {
	node_t* tree = NULL;
	AddInTree(&tree, 1);
	AddInTree(&tree, 2);
	AddInTree(&tree, 7);
	EXPECT_EQ(SearchInTree(tree, 3), NOT_FOUND);
	DestroyTree(tree);
}

TEST(RemoveFromTreeTest, RemoveOneElement) {
	node_t* tree = NULL;
	AddInTree(&tree, 1);
	AddInTree(&tree, 2);
	AddInTree(&tree, 7);
	RemoveFromTree(&tree, 7);
	EXPECT_EQ(tree->right->num, 2);
	EXPECT_EQ(tree->left, (node_t*)NULL);
	DestroyTree(tree);
}