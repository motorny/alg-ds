#include "pch.h"

TEST(Find_ElemNotfound, returnNULL) {
	tree* tree = NULL;
	Add(&tree, 1);
	EXPECT_TRUE(Find(tree, 2) == NULL);
	freeTree(tree);
}



TEST(Find_Elemfound, returnPointer) {
	tree* tree = NULL;
	Add(&tree, 1);
	EXPECT_TRUE(Find(tree, 1) != NULL);
	freeTree(tree);
}



TEST(Add_addElem, return1) {
	tree* tree = NULL;
	EXPECT_EQ(Add(&tree, 1), 1);
	freeTree(tree);
}



TEST(Add_addSameElem, return0) {
	tree* tree = NULL;
	Add(&tree, 1);
	EXPECT_EQ(Add(&tree, 1), 0);
	freeTree(tree);
}