#include "pch.h"

extern "C" {
#include "..\\LAB_E7\tree.h"
#include "..\\LAB_E7\tree.c"
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(AddToTree, AddToExisting_retTRUE) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));
	tree->key = 2;
	tree->left = (node_t*)NULL;
	tree->right = (node_t*)NULL;
	tree->parent = (node_t*)NULL;

	EXPECT_EQ(AddToTree(&tree, 1), TRUE);
	EXPECT_EQ(tree->left->key, 1);
	EXPECT_EQ(tree->left->left, (node_t*)NULL);
	EXPECT_EQ(tree->left->right, (node_t*)NULL);
	EXPECT_EQ(tree->left->parent, tree);

	free(tree->left);
	free(tree);
}

TEST(AddToTree, AddToEmpty_retTRUE) {
	node_t* tree = (node_t*)NULL;

	EXPECT_EQ(AddToTree(&tree, 1), TRUE);
	EXPECT_EQ(tree->key, 1);
	EXPECT_EQ(tree->left, (node_t*)NULL);
	EXPECT_EQ(tree->right, (node_t*)NULL);
	EXPECT_EQ(tree->parent, (node_t*)NULL);
;
	free(tree);
}

TEST(AddToTree, AddExistingNode_retFALSE) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));
	tree->key = 1;
	tree->left = (node_t*)NULL;
	tree->right = (node_t*)NULL;
	tree->parent = (node_t*)NULL;

	EXPECT_EQ(AddToTree(&tree, 1), FALSE);
	EXPECT_EQ(tree->key, 1);
	EXPECT_EQ(tree->left, (node_t*)NULL);
	EXPECT_EQ(tree->right, (node_t*)NULL);
	EXPECT_EQ(tree->parent, (node_t*)NULL);

	free(tree);
}

TEST(DeleteFromTree, DeleteFromEmpty_retFALSE) {
	node_t* tree = (node_t*)NULL;
	EXPECT_EQ(DeleteFromTree(&tree, 1), FALSE);
}

TEST(DeleteFromTree, DeleteNonExistingNode_retFALSE) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));
	tree->key = 1;
	tree->left = (node_t*)NULL;
	tree->right = (node_t*)NULL;
	tree->parent = (node_t*)NULL;

	EXPECT_EQ(DeleteFromTree(&tree, 2), FALSE);

	free(tree);
}

TEST(DeleteFromTree, DeleteLeaves_retTRUE) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));
	tree->key = 1;
	tree->left = (node_t*)NULL;
	tree->right = (node_t*)NULL;
	tree->parent = (node_t*)NULL;

	EXPECT_EQ(DeleteFromTree(&tree, 1), TRUE);
	EXPECT_EQ(tree, (node_t*)NULL);
}

TEST(DeleteFromTree, DeleteWithDescendants_retTRUE) {
	node_t tree;
	node_t* node1 = (node_t*)malloc(sizeof(node_t));
	node_t* pointerTree = &tree;
	node_t node2;
	// root
	tree.key = 2;
	tree.parent = (node_t*)NULL;
	tree.left = node1;
	tree.right = &node2;
	// left
	node1->key = 1;
	node1->left = (node_t*)NULL;
	node1->right = (node_t*)NULL;
	node1->parent = pointerTree;
	//right
	node2.key = 3;
	node2.left = (node_t*)NULL;
	node2.right = (node_t*)NULL;
	node2.parent = pointerTree;

	EXPECT_EQ(DeleteFromTree(&pointerTree, 2), TRUE);
	EXPECT_EQ(tree.key, 1);
	EXPECT_EQ(tree.right, &node2);
	EXPECT_EQ(tree.left, (node_t*)NULL);
	EXPECT_EQ(tree.parent, (node_t*)NULL);
}

TEST(FindInTree, FindInEmpty_retNULL) {
	node_t* tree = (node_t*)NULL;
	EXPECT_EQ(FindInTree(tree, 1), (node_t*)NULL);
}

TEST(FindInTree, FindUnexisting_retNULL) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));
	tree->key = 1;
	tree->left = (node_t*)NULL;
	tree->right = (node_t*)NULL;
	tree->parent = (node_t*)NULL;

	EXPECT_EQ(FindInTree(tree, 2), (node_t*)NULL);
	free(tree);
}

TEST(FindInTree, FindExisting_retCorrect) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));

	tree->key = 1;
	tree->left = (node_t*)NULL;
	tree->right = (node_t*)NULL;
	tree->parent = (node_t*)NULL;

	EXPECT_EQ(FindInTree(tree, 1), tree);

	free(tree);
}

TEST(DestroyTree, DestroyCorrectly) {
	node_t* tree = (node_t*)malloc(sizeof(node_t));

	tree->key = 1;
	tree->left = (node_t*)NULL;
	tree->right = (node_t*)NULL;
	tree->parent = (node_t*)NULL;

	DestroyTree(&tree);
	EXPECT_EQ(tree, (node_t*)NULL);
}