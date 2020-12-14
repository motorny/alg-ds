#include "pch.h"
#include "../../LabE/LabE/LabE.c"

TEST(AddingTree, AddFirst) {

	tree_t* tree = NULL;
	Add(&tree, 1);
	ASSERT_EQ(1, tree->key);
	ClearTree(tree);

}

TEST(AddingTree, AddLeft) {

	tree_t* tree = NULL;
	Add(&tree, 3);
	Add(&tree, 2);
	ASSERT_EQ(2, tree->left->key);
	ClearTree(tree);

}

TEST(AddingTree, AddRight) {

	tree_t* tree = NULL;
	Add(&tree, 1);
	Add(&tree, 3);
	ASSERT_EQ(3, tree->right->key);
	ClearTree(tree);

}

TEST(FindInTree, Find) {

	tree_t* tree = NULL;
	Add(&tree, 1);
	Add(&tree, 3);
	Add(&tree, 2);
	ASSERT_EQ(1, FindInTree(tree, 3));
	ClearTree(tree);

}

TEST(FindInTree, NotFind) {

	tree_t* tree = NULL;
	Add(&tree, 1);
	Add(&tree, 3);
	Add(&tree, 2);
	ASSERT_EQ(0, FindInTree(tree, 4));
	ClearTree(tree);

}

TEST(DelInTree, Del) {

	tree_t* tree = NULL;
	Add(&tree, 1);
	Add(&tree, 3);
	Add(&tree, 2);
	Delete(&tree, 3);
	ASSERT_EQ(0, FindInTree(tree, 3));
	ClearTree(tree);

}

TEST(CountLeafTree, Count) {

	tree_t* tree = NULL;

	Add(&tree, 3);
	Add(&tree, 2);
	Add(&tree, 4);
	Add(&tree, 6);
	Add(&tree, 1);
	CountLeaf(&tree);
	ASSERT_EQ(2, tree->leaf);

	ClearTree(tree);

}