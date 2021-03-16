#include "pch.h"

extern "C" {
#include "../treap/treap.h"
}

TEST(MergeTrees, EmptyTrees_ReturnNullPtr) {
	node_t* firstTree = NULL;
	node_t* secondTree = NULL;

	EXPECT_EQ(MergeTrees(firstTree, secondTree), nullptr);
}

TEST(MergeTrees, ValidTrees_ReturnValidTree) {
	node_t* firstTree = (node_t*)malloc(sizeof(node_t));
	node_t* secondTree = (node_t*)malloc(sizeof(node_t));
	node_t* newTree;

	EXPECT_NE(firstTree, nullptr);
	EXPECT_NE(secondTree, nullptr);

	firstTree->key = 2;
	firstTree->priority = 15;

	firstTree->left = (node_t*)malloc(sizeof(node_t));
	EXPECT_NE(firstTree->left, nullptr);

	firstTree->left->key = 1;
	firstTree->left->priority = 12;
	firstTree->left->left = NULL;
	firstTree->left->right = NULL;

	firstTree->right = (node_t*)malloc(sizeof(node_t));
	EXPECT_NE(firstTree->right, nullptr);

	firstTree->right->key = 3;
	firstTree->right->priority = 6;
	firstTree->right->left = NULL;
	firstTree->right->right = NULL;
	
	secondTree->key = 5;
	secondTree->priority = 11;
	secondTree->right = NULL;

	secondTree->left = (node_t*)malloc(sizeof(node_t));
	EXPECT_NE(secondTree->left, nullptr);

	secondTree->left->key = 4;
	secondTree->left->priority = 3;
	secondTree->left->left = NULL;
	secondTree->left->right = NULL;

	newTree = MergeTrees(firstTree, secondTree);
	EXPECT_NE(newTree, nullptr);
	EXPECT_EQ(newTree->key, 2);
	EXPECT_NE(newTree->left, nullptr);
	EXPECT_EQ(newTree->left->key, 1);
	EXPECT_NE(newTree->right, nullptr);
	EXPECT_EQ(newTree->right->key, 5);
	EXPECT_EQ(newTree->right->right, nullptr);
	EXPECT_NE(newTree->right->left, nullptr);
	EXPECT_EQ(newTree->right->left->key, 3);
	EXPECT_EQ(newTree->right->left->left, nullptr);
	EXPECT_NE(newTree->right->left->right, nullptr);
	EXPECT_EQ(newTree->right->left->right->key, 4);

	free(newTree->right->left->right);
	free(newTree->right->left);
	free(newTree->right);
	free(newTree->left);
	free(newTree->right);
}


TEST(SplitTree, EmptyTree_ReturnNullPtrs) {
	node_t* tree = NULL;
	node_t* leftTree = NULL;
	node_t* rightTree = NULL;

	SplitTree(tree, 2, &leftTree, &rightTree);

	EXPECT_EQ(leftTree, nullptr);
	EXPECT_EQ(rightTree, nullptr);
}

TEST(SplitTree, ValidTree_ReturnValidTrees) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));
	node_t* leftTree, * rightTree;
	EXPECT_NE(tree, nullptr);

	tree->key = 2;
	tree->priority = 15;

	tree->left = (node_t*)malloc(sizeof(node_t));
	EXPECT_NE(tree->left, nullptr);

	tree->left->key = 1;
	tree->left->priority = 12;
	tree->left->left = NULL;
	tree->left->right = NULL;

	tree->right = (node_t*)malloc(sizeof(node_t));
	EXPECT_NE(tree->right, nullptr);

	tree->right->key = 3;
	tree->right->priority = 6;
	tree->right->left = NULL;

	tree->right->right = (node_t*)malloc(sizeof(node_t));
	EXPECT_NE(tree->right->right, nullptr);

	tree->right->right->key = 5;
	tree->right->right->priority = 4;
	tree->right->right->right = NULL;
	tree->right->right->left = NULL;

	SplitTree(tree, 3, &leftTree, &rightTree);

	EXPECT_NE(rightTree, nullptr);
	EXPECT_EQ(rightTree->key, 5);

	EXPECT_NE(leftTree, nullptr);
	EXPECT_EQ(leftTree->key, 2);
	EXPECT_NE(leftTree->left, nullptr);
	EXPECT_EQ(leftTree->left->key, 1);
	EXPECT_EQ(leftTree->left->right, nullptr);
	EXPECT_NE(leftTree->left->left, nullptr);
	EXPECT_NE(leftTree->right, nullptr);
	EXPECT_EQ(leftTree->right->key, 3);
	EXPECT_EQ(leftTree->right->right, nullptr);
	EXPECT_NE(leftTree->right->left, nullptr);

	free(leftTree->right);
	free(leftTree->left);
	free(leftTree);
	free(rightTree);
}

TEST(AddNode, EmptyTree_ReturnValidTree) {
	node_t* tree = NULL;

	EXPECT_EQ(AddNode(&tree, 1), TRUE);
	EXPECT_NE(tree, nullptr);
	EXPECT_EQ(tree->left, nullptr);
	EXPECT_EQ(tree->right, nullptr);
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
	EXPECT_NE(tree->right, nullptr);
	EXPECT_EQ(tree->key, 2);

	EXPECT_NE(tree->left, nullptr);
	EXPECT_NE(tree->left->left, nullptr);
	EXPECT_NE(tree->left->right, nullptr);
	EXPECT_EQ(tree->left->key, 1);


	EXPECT_NE(tree->right, nullptr);
	EXPECT_NE(tree->right->left, nullptr);
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
	EXPECT_EQ(tree->key, 1);

	free(tree);
}


TEST(FindNode, NodeDoesntExist_ReturnNullPtr) {
	node_t* tree = NULL;
	AddNode(&tree, 1);
	AddNode(&tree, 2);

	EXPECT_EQ(FindNode(tree, 5), FALSE);

	free(tree->right);
	free(tree);

}

TEST(FindNode, SearchInTree_ReturnValidPtr) {
	node_t* tree = NULL;
	AddNode(&tree, 1);
	AddNode(&tree, 3);
	AddNode(&tree, 4);
	AddNode(&tree, 2);

	EXPECT_NE(FindNode(tree, 2), FALSE);

	free(tree->right->right);
	free(tree->right->left);
	free(tree->right);
	free(tree);

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
	EXPECT_EQ(tree->right, nullptr);
	EXPECT_EQ(tree->key, 2);
	EXPECT_NE(tree->left, nullptr);
	EXPECT_EQ(tree->left->left, nullptr);
	EXPECT_EQ(tree->left->right, nullptr);
	EXPECT_EQ(tree->left->key, 1);

	free(tree->left);
	free(tree);
}