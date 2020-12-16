#include "pch.h"

extern "C"{
#include "../binarytree/binarytree.h"
}

TEST(AddNode, EmptyTree_ReturnValidTree) {
	node_t* tree = NULL;

	EXPECT_EQ(AddNode(&tree, 1), TRUE);
	EXPECT_NE(tree, nullptr);
	EXPECT_EQ(tree->left, nullptr);
	EXPECT_EQ(tree->right, nullptr);
	EXPECT_EQ(tree->parent, nullptr);
	EXPECT_EQ(tree->key, 1);

	free(tree);
}

TEST(AddNode, AddIntoTree_ReturnValidTree) {
	node_t* tree = NULL;
	AddNode(&tree, 2);
	AddNode(&tree, 3);
	AddNode(&tree, 1);

	EXPECT_NE(tree, nullptr);
	EXPECT_NE(tree->left, nullptr);
	EXPECT_EQ(tree->parent, nullptr);
	EXPECT_NE(tree->right, nullptr);
	EXPECT_EQ(tree->key, 2);

	EXPECT_NE(tree->left, nullptr);
	EXPECT_NE(tree->left->left, nullptr);
	EXPECT_EQ(tree->left->parent, nullptr);
	EXPECT_NE(tree->left->right, nullptr);
	EXPECT_EQ(tree->left->key, 1);


	EXPECT_NE(tree->right, nullptr);
	EXPECT_NE(tree->right->left, nullptr);
	EXPECT_EQ(tree->right->parent, nullptr);
	EXPECT_NE(tree->right->right, nullptr);
	EXPECT_EQ(tree->right->key, 3);

	free(tree->left);
	free(tree->right);
	free(tree);
}

TEST(AddNode, NodeAlreadyExist_ReturnFalse) {
	node_t* tree = NULL;

	AddNode(&tree, 1);

	EXPECT_EQ(AddNode(&tree, 1), FALSE);
	EXPECT_NE(tree, nullptr);
	EXPECT_EQ(tree->left, nullptr);
	EXPECT_EQ(tree->right, nullptr);
	EXPECT_EQ(tree->parent, nullptr);
	EXPECT_EQ(tree->key, 1);

	free(tree);
}


TEST(FindNode, NodeDoesntExist_ReturnNullPtr) {
	node_t* tree = NULL;
	AddNode(&tree, 1);
	AddNode(&tree, 2);

	EXPECT_EQ(FindNode(tree, 5), nullptr);

	free(tree->right);
	free(tree);

}

TEST(FindNode, SearchInTree_ReturnValidPtr) {
	node_t* tree = NULL,* foundNode;
	AddNode(&tree, 1);
	AddNode(&tree, 3);
	AddNode(&tree, 2);
	AddNode(&tree, 4);

	foundNode = FindNode(tree, 2);
	EXPECT_NE(foundNode, nullptr);
	EXPECT_EQ(foundNode->key, 2);
}

TEST(RemoveNode, NodeDoesntExist_ReturnFalse) {
	node_t* tree = NULL;
	AddNode(&tree, 1);
	AddNode(&tree, 3);

	EXPECT_EQ(RemoveNode(&tree, 2), FALSE);
	EXPECT_EQ(tree->key, 1);
	EXPECT_NE(tree->right, nullptr);
	EXPECT_EQ(tree->right->key, 3);

	free(tree->right);
	free(tree);
}

TEST(RemoveNode, NodeExists_ReturnTrue) {
	node_t* tree = NULL;
	AddNode(&tree, 2);
	AddNode(&tree, 3);
	AddNode(&tree, 1);

	EXPECT_EQ(RemoveNode(&tree, 3), TRUE);


	EXPECT_NE(tree, nullptr);
	EXPECT_NE(tree->left, nullptr);
	EXPECT_EQ(tree->parent, nullptr);
	EXPECT_EQ(tree->right, nullptr);
	EXPECT_EQ(tree->key, 2);

	EXPECT_NE(tree->left, nullptr);
	EXPECT_EQ(tree->left->left, nullptr);
	EXPECT_EQ(tree->left->parent, tree);
	EXPECT_EQ(tree->left->right, nullptr);
	EXPECT_EQ(tree->left->key, 1);

	free(tree->left);
	free(tree);
}

TEST(MinSubtreeHeigh, ValidTree_PutRightValues) {
	node_t* tree;

	AddNode(&tree, 4);
	AddNode(&tree, 3);
	AddNode(&tree, 6);
	AddNode(&tree, 5);
	AddNode(&tree, 7);

	MinSubtreeHeigh(tree);

	EXPECT_EQ(tree->data, 2);
	EXPECT_EQ(tree->left->data, 0);
	EXPECT_EQ(tree->right->data, 1);
	EXPECT_EQ(tree->right->left->data, 0);
	EXPECT_EQ(tree->right->right->data, 0);

	free(tree->right->right);
	free(tree->right->left);
	free(tree->right);
	free(tree->left);
	free(tree);
}