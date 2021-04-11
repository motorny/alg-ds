#include "pch.h"
#include "../tree23v2/tree23.cpp"

TEST(insert, AddElemInTree)
{
	node* tree = NULL;
	insert(&tree, 9);
	ASSERT_EQ(9, tree->key[0]);
	treeFree(tree);
}

TEST(insert, AddElements)
{
	node* tree = NULL;
	insert(&tree, 5);
	insert(&tree, 4);
	insert(&tree, 8);
	ASSERT_EQ(5, tree->key[0]);
	ASSERT_EQ(4, tree->son[0]->key[0]);
	ASSERT_EQ(8, tree->son[1]->key[0]);
	treeFree(tree);
}

void createTree(node** tree)
{
	node* root, * left, * right;

	left = (node*)malloc(sizeof(node));
	left->key[0] = 4;
	left->son[0] = NULL;
	left->son[1] = NULL;

	right = (node*)malloc(sizeof(node));
	right->key[0] = 6;
	right->son[0] = NULL;
	right->son[1] = NULL;

	root = (node*)malloc(sizeof(node));
	root->key[0] = 5;
	root->son[0] = left;
	root->son[1] = right;

	(*tree) = root;
}

TEST(removenode, delNotExistElement)
{
	node* tree;
	createTree(&tree);
	tree = delKey(tree, 8);
	ASSERT_EQ(5, tree->key[0]);
	ASSERT_EQ(4, tree->son[0]->key[0]);
	ASSERT_EQ(6, tree->son[1]->key[0]);
	treeFree(tree);
}

TEST(removenode, delExistElement)
{
	node* tree;
	createTree(&tree);
	tree = delKey(tree, 5);
	ASSERT_EQ(4, tree->key[0]);
	ASSERT_EQ(6, tree->key[1]);
	ASSERT_EQ(NULL, tree->son[0]);
	ASSERT_EQ(NULL, tree->son[1]);
	ASSERT_EQ(NULL, tree->son[2]);
	treeFree(tree);
}

TEST(findnode, findNotExistElem)
{
	node* tree;
	createTree(&tree);
	ASSERT_EQ(FALSE, find(tree, 9));
	treeFree(tree);
}

TEST(findnode, findExistElem)
{
	node* tree;
	createTree(&tree);
	ASSERT_EQ(TRUE, find(tree, 6));
	treeFree(tree);
}