#include "pch.h"
#include "../AAtree/tree.cpp"

TEST(insert, AddElemInTree)
{
	Node* tree = NULL;
	insert(&tree, 9);
	ASSERT_EQ(9, tree->data);
	treeFree(tree);
}

TEST(insert, AddElements)
{
	Node* tree = NULL;
	insert(&tree, 5);
	insert(&tree, 4);
	insert(&tree, 8);
	ASSERT_EQ(5, tree->data);
	ASSERT_EQ(4, tree->left->data);
	ASSERT_EQ(8, tree->right->data);
	treeFree(tree);
}

void createTree(Node** tree)
{
	Node* root, * left, * right;

	left = (Node*)malloc(sizeof(Node));
	left->data = 4;
	left->left = NULL;
	left->right = NULL;

	right = (Node*)malloc(sizeof(Node));
	right->data = 6;
	right->left = NULL;
	right->right = NULL;

	root = (Node*)malloc(sizeof(Node));
	root->data = 5;
	root->left = left;
	root->right = right;

	(*tree) = root;
}

TEST(removeNode, delNotExistElement)
{
	Node* tree;
	createTree(&tree);
	removeNode(&tree, 8);
	ASSERT_EQ(5, tree->data);
	ASSERT_EQ(4, tree->left->data);
	ASSERT_EQ(6, tree->right->data);
	treeFree(tree);
}

TEST(removeNode, delExistElement)
{
	Node* tree;
	createTree(&tree);
	removeNode(&tree, 5);
	ASSERT_EQ(4, tree->data);
	ASSERT_EQ(6, tree->right->data);
	ASSERT_EQ(NULL, tree->left);
	treeFree(tree);
}

TEST(findNode, findNotExistElem)
{
	Node* tree;
	createTree(&tree);
	ASSERT_EQ(False, findNode(tree, 9));
	treeFree(tree);
}

TEST(findNode, findExistElem)
{
	Node* tree;
	createTree(&tree);
	ASSERT_EQ(True, findNode(tree, 6));
	treeFree(tree);
}