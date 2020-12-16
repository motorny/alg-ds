#include "pch.h"
extern "C" {
#include "..\BST_Lib\BST_Lib.h"
}

#define NULL_ (void*)0

TEST(TreeAdd, AddToEmptyTree)
{
	Tree* tree_p = TreeGet();
	TreeItem* item_p = TreeAdd(tree_p, 10, 0);
	EXPECT_EQ(item_p, tree_p->root_p);
	EXPECT_EQ(10, item_p->key);
	EXPECT_EQ(0, item_p->value);
	EXPECT_EQ(NULL_, item_p->childL_p);
	EXPECT_EQ(NULL_, item_p->childR_p);
	TreeFree(tree_p);
}

TEST(TreeAdd, AddAsLeft)
{
	Tree* tree_p = TreeGet();
	TreeItem* item1_p = TreeAdd(tree_p, 5, 1);
	TreeItem* item2_p = TreeAdd(tree_p, 4, 2);
	EXPECT_EQ(5, item1_p->key);
	EXPECT_EQ(1, item1_p->value);
	EXPECT_EQ(4, item2_p->key);
	EXPECT_EQ(2, item2_p->value);
	EXPECT_EQ(item1_p, tree_p->root_p);
	EXPECT_EQ(item2_p, item1_p->childL_p);
	EXPECT_EQ(NULL_, item1_p->childR_p);
	EXPECT_EQ(NULL_, item2_p->childL_p);
	EXPECT_EQ(NULL_, item2_p->childR_p);
	TreeFree(tree_p);
}

TEST(TreeAdd, AddAsRight)
{
	Tree* tree_p = TreeGet();
	TreeItem* item1_p = TreeAdd(tree_p, 5, 1);
	TreeItem* item2_p = TreeAdd(tree_p, 6, 2);
	EXPECT_EQ(5, item1_p->key);
	EXPECT_EQ(1, item1_p->value);
	EXPECT_EQ(6, item2_p->key);
	EXPECT_EQ(2, item2_p->value);
	EXPECT_EQ(item1_p, tree_p->root_p);
	EXPECT_EQ(NULL_, item1_p->childL_p);
	EXPECT_EQ(item2_p, item1_p->childR_p);
	EXPECT_EQ(NULL_, item2_p->childL_p);
	EXPECT_EQ(NULL_, item2_p->childR_p);
	TreeFree(tree_p);
}

Tree* CreateTree()
{
	Tree* tree_p = TreeGet();
	TreeAdd(tree_p, 5, 5);
	TreeAdd(tree_p, 6, 6);
	TreeAdd(tree_p, 4, 4);
	TreeAdd(tree_p, 2, 2);
	TreeAdd(tree_p, 1, 1);
	TreeAdd(tree_p, 10, 10);
	return tree_p;
}

TEST(TreeFind, ItemInTree)
{
	Tree* tree_p = CreateTree();
	TreeItem* item1_p = TreeFind(tree_p, 4);
	TreeItem* item2_p = TreeFind(tree_p, 10);
	EXPECT_NE(NULL_, item1_p);
	EXPECT_NE(NULL_, item2_p);
	EXPECT_EQ(4, item1_p->key);
	EXPECT_EQ(10, item2_p->key);
	TreeFree(tree_p);
}

TEST(TreeFind, ItemNotInTree)
{
	Tree* tree_p = CreateTree();
	TreeItem* item1_p = TreeFind(tree_p, 9);
	TreeItem* item2_p = TreeFind(tree_p, 11);
	EXPECT_EQ(NULL_, item1_p);
	EXPECT_EQ(NULL_, item2_p);
	TreeFree(tree_p);
}

TEST(TreeRemove, ItemInTree)
{
	Tree* tree_p = CreateTree();
	TreeItem* item_p;
	TreeRemove(tree_p, 4);
	item_p = TreeFind(tree_p, 4);
	EXPECT_EQ(NULL_, item_p);
	TreeFree(tree_p);
}

TEST(TreeHightDifToValue, CorrectDif)
{
	Tree* tree_p = CreateTree();
	TreeHightDifToValue(tree_p);
	EXPECT_EQ(tree_p->root_p->value, -1);
	EXPECT_EQ(tree_p->root_p->childL_p->value, -2);
	EXPECT_EQ(tree_p->root_p->childR_p->value, 1);
	EXPECT_EQ(tree_p->root_p->childL_p->childL_p->value, -1);
	TreeFree(tree_p);
}