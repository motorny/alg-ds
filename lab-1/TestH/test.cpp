#include "pch.h"

extern "C" {
#include "../Lab_H/DekartTree.h"
#include "../LAB_H/LAB_H.c"
}

TEST(TestGetSize, Empty) {
	node_t* tree = NULL;
	EXPECT_EQ(GetSize(tree), 0);
}

TEST(TestGetSize, NotEmpty) {
	node_t* tree = Insert(10);
	tree->size = 10;
	EXPECT_EQ(GetSize(tree), 10);
	DestroyTree(tree);
}

TEST(TestChangeSize, TwoTree) {
	node_t* tree = Tree();
	tree->size = 0;
	int Size1 = tree->left->size + tree->right->size + 1;
	ChangeSize(tree);
	int Size2 = tree->size;
	EXPECT_EQ(Size2, Size1);
	DestroyTree(tree);
}

TEST(TestMerge, EmptyTree) {
	node_t* treeA, * treeB;
	treeA = NULL;
	treeB = Tree();
	node_t* tree = Merge(treeA, treeB);
	EXPECT_EQ(tree, treeB);
	DestroyTree(tree);
}

TEST(TestMerge, TwoEmptyTrees) {
	node_t* treeA, * treeB;
	treeA = treeB = NULL;
	node_t* tree = Merge(treeA, treeB);
	EXPECT_TRUE(!tree);
	DestroyTree(tree);
	DestroyTree(treeB);
	DestroyTree(treeA);
}

TEST(TestMerge, NotEmptyTrees) {
	node_t* treeA, * treeB;
	treeA = Insert(10);
	treeB = Tree();
	node_t* tree = Merge(treeA, treeB);
	EXPECT_TRUE(tree == treeA);
	EXPECT_EQ(tree->size, treeA->size);
	DestroyTree(tree);
}

TEST(TestSplit, TwoEmptyTree) {
	node_t* tree = NULL;
	node_t* treeA, * treeB;
	Split(0, 1, tree, &treeA, &treeB);
	EXPECT_TRUE(!treeA);
	EXPECT_TRUE(!treeB);
	DestroyTree(tree);
}

TEST(TestSplit, OneEmptyTree) {
	node_t* tree = Tree();
	node_t* treeA, * treeB;
	Split(0, 0, tree, &treeA, &treeB);
	EXPECT_TRUE(!treeA);
	EXPECT_TRUE(treeB == tree);
	DestroyTree(tree);
}

TEST(TestSplit, TwoTree) {
	node_t* tree = Tree();
	node_t* treeA, * treeB;
	int Size = tree->size;
	Split(0, 1, tree, &treeA, &treeB);
	EXPECT_TRUE(treeA);
	EXPECT_TRUE(treeB);
	EXPECT_EQ(treeA->size, 1);
	EXPECT_EQ(treeB->size, Size - 1);
	DestroyTree(treeA);
	DestroyTree(treeB);
}

TEST(TestIsItFind, FindNo) {
	node_t* tree = NULL;
	int find = 0;
	AddNode(0, 10, &tree);
	IsItFind(tree, 1, &find);
	EXPECT_TRUE(!find);
	DestroyTree(tree);
}

TEST(TestIsFind, FindYes) {
	node_t* tree = NULL;
	int find = 0;
	AddNode(0, 10, &tree);
	IsItFind(tree, 10, &find);
	EXPECT_TRUE(find);
	DestroyTree(tree);
}

int main(void) {
	return RUN_ALL_TESTS();
}