#include "pch.h"
#include "../lab-F22/LabF22.c"

TEST(Add, AddToLeft_returnNumbers)
{
	intTree_t* tree = NULL;
	Add(&tree, 5, 10);
	Add(&tree, 4, 11);
	EXPECT_EQ(4, tree->left->l);
	EXPECT_EQ(11, tree->left->r);
	RemoveTree(tree);
}

TEST(Add, AddToRight_returnNumbers)
{
	intTree_t* tree = NULL;
	Add(&tree, 5, 10);
	Add(&tree, 6, 11);
	EXPECT_EQ(6, tree->right->l);
	EXPECT_EQ(11, tree->right->r);
	RemoveTree(tree);
}

TEST(Add, AddToEmptyTree_returnNumbers)
{
	intTree_t* tree = NULL;
	Add(&tree, 1, 2);
	EXPECT_EQ(1, tree->l);
	EXPECT_EQ(2, tree->r);
	RemoveTree(tree);
}

TEST(Find, ValidInterval_returnTRUE)
{
	intTree_t* tree = NULL;
	Add(&tree, 1, 10);
	Add(&tree, 3, 4);
	Add(&tree, 2, 5);
	EXPECT_EQ(TRUE, Find(tree, 2, 5));
	EXPECT_EQ(TRUE, Find(tree, 1, 10));
	RemoveTree(tree);
}

TEST(Find, InvalidInterval_returnFALSE)
{
	intTree_t* tree = NULL;
	Add(&tree, 1, 10);
	Add(&tree, 2, 5);
	EXPECT_EQ(FALSE, Find(tree, 2, 10));
	EXPECT_EQ(FALSE, Find(tree, 1, 7));
	RemoveTree(tree);
}

TEST(Remove, RemovingInterval_returnFALSE)
{
	intTree_t* tree = NULL;
	Add(&tree, 1, 10);
	Add(&tree, 4, 7);
	RemoveInter(&tree, 4, 7);
	EXPECT_EQ(FALSE, Find(tree, 4, 7));
	RemoveTree(tree);
}

TEST(Intersect, NotIntersect_returnFALSE)
{
	interval_t arr[size];
	int lvl = 0;
	intTree_t* tree = NULL;
	Add(&tree, 1, 10);
	Add(&tree, 4, 7);
	Intersect(tree, -3, -1, &arr, &lvl);
	Intersect(tree, 11, 15, &arr, &lvl);
	EXPECT_EQ(FALSE, lvl);
	RemoveTree(tree);
}

TEST(Intersect, ValidIntersect_returnNUMBERS)
{
	interval_t arr[size];
	int lvl = 0;
	intTree_t* tree = NULL;
	Add(&tree, 1, 10);
	Add(&tree, 2, 7);
	Add(&tree, 3, 8);
	Intersect(tree, 3, 7, &arr, &lvl);
	EXPECT_EQ(1, arr[0].l);
	EXPECT_EQ(10, arr[0].r);
	EXPECT_EQ(2, arr[1].l);
	EXPECT_EQ(7, arr[1].r);
	EXPECT_EQ(3, lvl);
	RemoveTree(tree);
}