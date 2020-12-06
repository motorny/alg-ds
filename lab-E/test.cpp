#include "pch.h"
#include "pch.h"
#include "..\Tree\Tree.c"


TEST(Add, AddingToEmptyTree)
{
	NODE* root = NULL;
	InsertInTree(&root, 1);
	ASSERT_EQ(1, root->data);
	ASSERT_EQ(NULL, root->left);
	ASSERT_EQ(NULL, root->right);
	RemoveNodeByPtr(root);
}

TEST(Add, AddingToLeftNode)
{
	NODE* root = NULL;
	InsertInTree(&root, 5);
	InsertInTree(&root, 4);
	ASSERT_EQ(5, root->data);
	ASSERT_EQ(4, root->left->data);
	ASSERT_EQ(NULL, root->right);
	DestroyTree(&root);
	ASSERT_EQ(NULL, root);
}

TEST(Add, AddingToRightNode)
{
	NODE* root = NULL;
	InsertInTree(&root, 5);
	InsertInTree(&root, 6);
	ASSERT_EQ(5, root->data);
	ASSERT_EQ(6, root->right->data);
	ASSERT_EQ(NULL, root->left);
	DestroyTree(&root);
	ASSERT_EQ(NULL, root);
}

NODE* createTree()
{
	NODE* root= NULL;
	InsertInTree(&root, 5);
	InsertInTree(&root, 6);
	InsertInTree(&root, 4);
	InsertInTree(&root, 2);
	InsertInTree(&root, 1);
	InsertInTree(&root, 10);

	return root;
}

TEST(Find, ElemIsInTheTree)
{
	NODE* root = createTree();
	ASSERT_TRUE(SearchNodeByData(root, 4)!=NULL);
	ASSERT_TRUE(SearchNodeByData(root, 10)!=NULL);
	DestroyTree(&root);
}

TEST(Find, ElemIsNotInTheTree)
{
	NODE* root = createTree();
	ASSERT_EQ(NULL, SearchNodeByData(root, 9));
	ASSERT_EQ(NULL, SearchNodeByData(root, 11));
	DestroyTree(&root);
}

TEST(Del, DelElemIsInTheTree)
{
	NODE* root = createTree();
	RemoveNodeByData(root, 4);
	ASSERT_EQ(NULL, SearchNodeByData(root, 4));
	DestroyTree(&root);
}

TEST(Data, WriteInDataMinLeavesHeight)
{
	NODE* root = createTree();
	WriteInDataMinLeavesHeight(root);
	ASSERT_EQ(root->data, 2);
	ASSERT_EQ(root->left->data, 2);
	ASSERT_EQ(root->right->data, 1);
	ASSERT_EQ(root->left->left->data, 1);
	DestroyTree(&root);
}