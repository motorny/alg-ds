#include "pch.h"
extern "C"
{
#include"tree.h"
}

TEST(CheckInsert, CorrectInsert)
{
	Node *tree = NULL
	insert(&tree, 5);
	EXPECT_TRUE(!tree->right);
	EXPECT_TRUE(!tree->left);
	EXPECT_EQ(tree->data, 5);
	EXPECT_EQ(tree->parent, root);

	destroyTree(tree);
}

TEST(CheckFound, ViolationMemory)
{
	Node *tree = NULL, *tmp = NULL;
	EXPECT_TRUE(!getNodeByValue(tree, 5));
	insert(&tree, 5);
	tmp = getNodeByValue(tree, 5);
	EXPECT_TRUE(tmp);
	EXPECT_EQ(tmp->data, 5);
	deleteValue(root, 5);
	EXPECT_TRUE(!getNodeByValue(tree, 5));

	destroyTree(tree);
}

TEST(CheckOrderliness, OneElement)
{
	Node *tree = NULL;
	insert(&tree, 10);

   	int number = 1;
    	setOrder(tree, &number);
	EXPECT_EQ(tree->orderAscending, 1)

	treeDestroy(tree);
}

TEST(CheckOrderliness, GroupOfElements)
{
	Node *tree = NULL, *tmp = NULL;
	insert(&tree, 10);
	insert(&tree, 5);
	insert(&tree, 15);
	insert(&tree, 7);
	insert(&tree, 3);
	insert(&tree, 12);
	insert(&tree, 17);
	insert(&tree, 1);
	insert(&tree, 20);
	insert(&tree, 4);
	insert(&tree, 16);

	tmp = getNodeByValue(tree, 12);

   	int number = 1;
    	setOrder(tree, &number);
	EXPECT_EQ(tmp->orderAscending, 7);
	EXPECT_EQ(tree->orderAscending, 6);

	treeDestroy(tree);
}

TEST(CheckGetNumOfLeavesBelow, OneElement)
{
	Node *tree = NULL;
	insert(&tree, 10);

    	getNumOfLeavesBelow(tree);

	EXPECT_EQ(tree->numOfLeavesBelow, 0);

	treeDestroy(tree);
}

TEST(CheckGetNumOfLeavesBelow, GroupOfElements)
{
	Node *tree = NULL, *tmp = NULL;
	insert(&tree, 10);
	insert(&tree, 5);
	insert(&tree, 15);
	insert(&tree, 7);
	insert(&tree, 3);
	insert(&tree, 12);
	insert(&tree, 17);
	insert(&tree, 1);
	insert(&tree, 20);
	insert(&tree, 4);
	insert(&tree, 16);

    	getNumOfLeavesBelow(tree);

	tmp = getNodeByValue(tree, 12);

	EXPECT_EQ(tree->numOfLeavesBelow, 6);
	EXPECT_EQ(tmp->numOfLeavesBelow, 0);

	treeDestroy(tree);
}