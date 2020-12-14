#include "pch.h"

extern "C" {
#include "../Binary search tree/tree.h"
#include "../Binary search tree/tree.c"
}

TEST(AddNodeByKey, Create_tree) {
	tree_t* tree = NULL;
	int key = 2;
	AddNodeByKey(&tree, key);

	EXPECT_NE(tree, (tree_t*)NULL);
	EXPECT_EQ(tree->key, key);
	EXPECT_EQ(tree->left, (tree_t*)NULL);
	EXPECT_EQ(tree->right, (tree_t*)NULL);
	EXPECT_EQ(tree->height, 0);
	EXPECT_EQ(tree->differense, 0);

	DestroyTree(tree);
}

TEST(AddNodeByKey, Sequential_addition) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 10);
	AddNodeByKey(&tree, 8);

	EXPECT_EQ(tree->height, 2);
	EXPECT_EQ(tree->differense, 1);
	EXPECT_NE(tree->right, (tree_t*)NULL);
	EXPECT_EQ(tree->right->key, 10);
	EXPECT_EQ(tree->right->differense, 0);
	EXPECT_EQ(tree->right->height, 1);
	EXPECT_NE(tree->right->left, (tree_t*)NULL);
	EXPECT_EQ(tree->right->left->key, 8);
	EXPECT_EQ(tree->right->left->differense, 0);
	EXPECT_EQ(tree->right->left->height, 0);

	DestroyTree(tree);
}

TEST(AddNodeByKey, Node_is_already_exist_return_NOT_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);

	EXPECT_EQ(AddNodeByKey(&tree, 2), NOT_FINISHED);
	EXPECT_NE(tree, (tree_t*)NULL);
	EXPECT_EQ(tree->key, 2);
	EXPECT_EQ(tree->left, (tree_t*)NULL);
	EXPECT_EQ(tree->right, (tree_t*)NULL);
	EXPECT_EQ(tree->height, 0);
	EXPECT_EQ(tree->differense, 0);

	DestroyTree(tree);
}

TEST(FindByKey, Node_is_not_exist_return_NOT_FOUND) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 10);

	EXPECT_EQ(FindByKey(tree, 8), (tree_t*)NULL);

	DestroyTree(tree);
}

TEST(FindByKey, Node_is_found_return_ptr) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 10);
	AddNodeByKey(&tree, 8);

	EXPECT_EQ(FindByKey(tree, 8), tree->right->left);

	DestroyTree(tree);
}

TEST(DeleteByKey, Node_is_not_exist_return_NOT_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 10);

	EXPECT_EQ(DeleteByKey(&tree, 8), NOT_FINISHED);

	DestroyTree(tree);
}

TEST(DeleteByKey, Node_without_sons_return_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 10);

	EXPECT_EQ(DeleteByKey(&tree, 10), FINISHED);
	EXPECT_EQ(tree->right, (tree_t*)NULL);

	DestroyTree(tree);

}

TEST(DeleteByKey, Node_with_the_left_son_return_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 10);
	AddNodeByKey(&tree, 8);

	EXPECT_EQ(DeleteByKey(&tree, 10), FINISHED);
	EXPECT_EQ(tree->height, 1);
	EXPECT_EQ(tree->differense, 0);
	EXPECT_EQ(tree->right->key, 8);
	EXPECT_EQ(tree->right->differense, 0);
	EXPECT_EQ(tree->right->height, 0);
	EXPECT_EQ(tree->right->left, (tree_t*)NULL);
	EXPECT_EQ(tree->right->right, (tree_t*)NULL);

	DestroyTree(tree);
}

TEST(DeleteByKey, Node_with_the_right_son_return_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 8);
	AddNodeByKey(&tree, 10);

	EXPECT_EQ(DeleteByKey(&tree, 8), FINISHED);
	EXPECT_EQ(tree->height, 1);
	EXPECT_EQ(tree->differense, 0);
	EXPECT_EQ(tree->right->key, 10);
	EXPECT_EQ(tree->right->differense, 0);
	EXPECT_EQ(tree->right->height, 0);
	EXPECT_EQ(tree->right->left, (tree_t*)NULL);
	EXPECT_EQ(tree->right->right, (tree_t*)NULL);

	DestroyTree(tree);
}

TEST(DeleteByKey, Both_sons_return_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 1);
	AddNodeByKey(&tree, 8);

	EXPECT_EQ(DeleteByKey(&tree, 2), FINISHED);
	EXPECT_EQ(tree->key, 1);
	EXPECT_EQ(tree->left, (tree_t*)NULL);
	EXPECT_EQ(tree->height, 1);
	EXPECT_EQ(tree->differense, 0);

	DestroyTree(tree);
}