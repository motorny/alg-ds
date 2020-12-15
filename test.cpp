#include "pch.h"
#include "..\LabEF\Labf.c"

TEST(addSegm, addingToEmptyTree)
{
	TREE* node = NULL;
	add(&node, 10, 15);
	ASSERT_EQ(10, node->leftBorder);
	ASSERT_EQ(15, node->rightBorder);
	ASSERT_EQ(NULL, node->left);
	ASSERT_EQ(NULL, node->right);
	destroyTree(node);
}

TEST(add, addingToLeftNode)
{
	TREE* node = NULL;
	add(&node, 5, 10);
	add(&node, 4, 11);
	ASSERT_EQ(4, node->left->leftBorder);
	ASSERT_EQ(11, node->left->rightBorder);
	destroyTree(node);
}

TEST(add, addingToRightNode)
{
	TREE* node = NULL;
	add(&node, 5, 10);
	add(&node, 6, 11);
	ASSERT_EQ(6, node->right->leftBorder);
	ASSERT_EQ(11, node->right->rightBorder);
	destroyTree(node);
}

TREE* createTree()
{
	TREE* node = NULL;
	add(&node, 5, 9);
	add(&node, 6, 8);
	add(&node, 4, 11);
	add(&node, 2, 5);
	add(&node, 1, 3);
	add(&node, 10, 15);

	return node;
}

TEST(find, elemIsInTheTree)
{
	TREE* node = createTree();
	ASSERT_EQ(1, findByValue(node, 4, 11));
	ASSERT_EQ(1, findByValue(node, 10, 15));
	destroyTree(node);
}

TEST(find, elemIsNotInTheTree)
{
	TREE* node = createTree();
	ASSERT_EQ(0, findByValue(node, 9, 12));
	ASSERT_EQ(0, findByValue(node, 11, 18));
	destroyTree(node);
}

TEST(del, delElemIsInTheTree)
{
	TREE* node = createTree();
	del(&node, 4, 11);
	ASSERT_EQ(0, findByValue(node, 4, 11));
	destroyTree(node);
}

TEST(intersectionSegm, intersectionNotExists)
{
	TREE* node = createTree();
	interSegm(node, -4, 0);
	ASSERT_EQ(0, index);
	destroyTree(node);
}

TEST(intersectionSegm, intersectionExists)
{
	TREE* node = createTree();
	interSegm(node, 4, 8);
	ASSERT_EQ(5, answer[0].lBorder);
	ASSERT_EQ(9, answer[0].rBorder);
	ASSERT_EQ(4, answer[1].lBorder);
	ASSERT_EQ(11, answer[1].rBorder);
	ASSERT_EQ(4, index);
	destroyTree(node);
}