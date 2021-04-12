#include "pch.h"

extern "C" {
#include "../AVL tree/avlTree.h"
#include "../AVL tree/avlTree.c"
}

TEST(AddNodeByKey, Left_adding_to_taller_Lsubtree_returnFINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 3);
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 1);

	EXPECT_NE(tree, (tree_t*)NULL);
	EXPECT_EQ(tree->key, 2);
	EXPECT_EQ(tree->left->key, 1);
	EXPECT_EQ(tree->right->key, 3);

	DestroyTree(tree);
}

TEST(AddNodeByKey, Right_adding_to_taller_Lsubtree_returnFINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 3);
	AddNodeByKey(&tree, 1);
	AddNodeByKey(&tree, 2);

	EXPECT_NE(tree, (tree_t*)NULL);
	EXPECT_EQ(tree->key, 2);
	EXPECT_EQ(tree->left->key, 1);
	EXPECT_EQ(tree->right->key, 3);

	DestroyTree(tree);
}

TEST(AddNodeByKey, Adding_to_balanced_Lsubtree_returnFINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 5);
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 6);
	AddNodeByKey(&tree, 1);
	AddNodeByKey(&tree, 4);
	AddNodeByKey(&tree, 3);

	EXPECT_NE(tree, (tree_t*)NULL);
	EXPECT_EQ(tree->key, 4);
	EXPECT_EQ(tree->left->key, 2);
	EXPECT_EQ(tree->left->balance, 0);
	EXPECT_EQ(tree->left->left->key, 1);
	EXPECT_EQ(tree->right->key, 5);
	EXPECT_EQ(tree->right->balance, 1);
	EXPECT_EQ(tree->right->left->key, 3);
	EXPECT_EQ(tree->right->right->key, 6);

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

	EXPECT_EQ(FindByKey(tree, 8), tree);

	DestroyTree(tree);
}

TEST(DeleteByKey, Deletion_from_shorter_Lsubtree_one_rotation_return_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 1);
	AddNodeByKey(&tree, 4);
	AddNodeByKey(&tree, 3);
	AddNodeByKey(&tree, 5);

	EXPECT_EQ(DeleteByKey(&tree, 1), FINISHED);
	EXPECT_EQ(tree->key, 4);
	EXPECT_EQ(tree->balance, -1);
	EXPECT_EQ(tree->right->key, 5);
	EXPECT_EQ(tree->left->left->key, 2);
	EXPECT_EQ(tree->left->balance, 1);
	EXPECT_EQ(tree->left->right->key, 3);

	DestroyTree(tree);
}

TEST(DeleteByKey, Deletion_from_shorter_Lsubtree_two_rotations_return_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 1);
	AddNodeByKey(&tree, 4);
	AddNodeByKey(&tree, 3);

	EXPECT_EQ(DeleteByKey(&tree, 1), FINISHED);
	EXPECT_EQ(tree->key, 3);
	EXPECT_EQ(tree->balance, 0);
	EXPECT_EQ(tree->right->key, 4);
	EXPECT_EQ(tree->left->key, 2);

	DestroyTree(tree);
}

TEST(DeleteByKey, Deletion_from_balanced_tree_return_FINISHED) {
	tree_t* tree = NULL;
	AddNodeByKey(&tree, 2);
	AddNodeByKey(&tree, 1);
	AddNodeByKey(&tree, 4);

	EXPECT_EQ(DeleteByKey(&tree, 4), FINISHED);
	EXPECT_EQ(tree->key, 2);
	EXPECT_EQ(tree->balance, -1);
	EXPECT_EQ(tree->left->key, 1);

	DestroyTree(tree);
}