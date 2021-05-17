#include "pch.h"
#include "../LAB_I/LAB_I.c"

TEST(Insert, AddElemement)
{
	node* tree = NULL;
	Insert(&tree, 9);
	ASSERT_EQ(9, tree->key[0]);
	FreeTree(tree);
}

TEST(Insert, AddThreeElements)
{
	node* tree = NULL;
	Insert(&tree, 10);
	Insert(&tree, 5);
	Insert(&tree, 15);
	ASSERT_EQ(10, tree->key[0]);
	ASSERT_EQ(5, tree->son[0]->key[0]);
	ASSERT_EQ(15, tree->son[1]->key[0]);
	FreeTree(tree);
}

void createTree(node** tree)
{
	node* root, * left, * right;
	left = (node*)malloc(sizeof(node));
	left->key[0] = 5;
	left->son[0] = NULL;
	left->son[1] = NULL;
	right = (node*)malloc(sizeof(node));
	right->key[0] = 15;
	right->son[0] = NULL;
	right->son[1] = NULL;
	root = (node*)malloc(sizeof(node));
	root->key[0] = 10;
	root->son[0] = left;
	root->son[1] = right;
	(*tree) = root;
}

TEST(DelKey, DelNotExistElement)
{
	node* tree;
	createTree(&tree);
	tree = DelKey(tree, 3);
	ASSERT_EQ(15, tree->key[0]);
	ASSERT_EQ(5, tree->son[0]->key[0]);
	ASSERT_EQ(10, tree->son[1]->key[0]);
	FreeTree(tree);
}

TEST(DelKey, DelExistElement)
{
	node* tree;
	createTree(&tree);
	tree = DelKey(tree, 10);
	ASSERT_EQ(5, tree->key[0]);
	ASSERT_EQ(15, tree->key[1]);
	ASSERT_EQ(NULL, tree->son[0]);
	ASSERT_EQ(NULL, tree->son[1]);
	ASSERT_EQ(NULL, tree->son[2]);
	FreeTree(tree);
}

TEST(findnode, findNotExistElem)
{
	node* tree;
	createTree(&tree);
	ASSERT_EQ(FALSE, IsItFind(tree, 9));
	FreeTree(tree);
}

TEST(IsItFind, FindElem)
{
	node* tree;
	createTree(&tree);
	ASSERT_EQ(TRUE, IsItFind(tree, 6));
	FreeTree(tree);
}