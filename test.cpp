#include "pch.h"
#include "..\LabEF\LabE.c"

TEST(add, addingToEmptyTree)
{
	TREE* node = NULL;
	add(&node, 10);
	ASSERT_EQ(10, node->key);
	ASSERT_EQ(NULL, node->left);
	ASSERT_EQ(NULL, node->right);
	destroyTree(node);
}

TEST(add, addingToLeftNode)
{
	TREE* node = NULL;
	add(&node, 5);
	add(&node, 4);
	ASSERT_EQ(5, node->key);
	ASSERT_EQ(4, node->left->key);
	ASSERT_EQ(NULL, node->right);
	destroyTree(node);
}

TEST(add, addingToRightNode)
{
	TREE* node = NULL;
	add(&node, 5);
	add(&node, 6);
	ASSERT_EQ(5, node->key);
	ASSERT_EQ(6, node->right->key);
	ASSERT_EQ(NULL, node->left);
	destroyTree(node);
}

TREE* createTree()
{
	TREE* node = NULL;
	add(&node, 5);
	add(&node, 6);
	add(&node, 4);
	add(&node, 2);
	add(&node, 1);
	add(&node, 10);

	return node;
}

TEST(find, elemIsInTheTree)
{
	TREE* node = createTree();
	ASSERT_EQ(1, findByValue(node, 4));
	ASSERT_EQ(1, findByValue(node, 10));
	destroyTree(node);
}

TEST(find, elemIsNotInTheTree)
{
	TREE* node = createTree();
	ASSERT_EQ(0, findByValue(node, 9));
	ASSERT_EQ(0, findByValue(node, 11));
	destroyTree(node);
}

TEST(del, delElemIsInTheTree)
{
	TREE* node = createTree();
	del(&node, 4);
	ASSERT_EQ(0, findByValue(node, 4));
	destroyTree(node);
}

TEST(countLeaf, subTreeCountLeaf)
{
	TREE* tree = createTree();
	countLeaf(&tree);
	ASSERT_EQ(tree->leaf, 5);
	ASSERT_EQ(tree->left->leaf, 2);
	ASSERT_EQ(tree->right->leaf, 1);
	ASSERT_EQ(tree->left->left->leaf, 1);
	destroyTree(tree);
}