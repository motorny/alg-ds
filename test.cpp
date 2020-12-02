#include "pch.h"
extern "C" {
#include"tree.h"
}

TEST(findNode_ElemNotfound, returnNULL) {
	node_t* tree = NULL;
	nodeAdd(&tree, 1);
    EXPECT_TRUE(findNode(tree, 2) == NULL);
    treeDestroy(tree);
}

TEST(findNode_Elemfound, returnPointer) {
	node_t* tree = NULL;
	nodeAdd(&tree, 1);
	EXPECT_TRUE(findNode(tree, 1) != NULL);
	treeDestroy(tree);
}

TEST(nodeAdd_addElem, return1) {
	node_t* tree = NULL;
	EXPECT_EQ(nodeAdd(&tree, 1), 1);
	treeDestroy(tree);
}

TEST(nodeAdd_addSameElem, return0) {
	node_t* tree = NULL;
	nodeAdd(&tree, 1);
	EXPECT_EQ(nodeAdd(&tree, 1), 0);
	treeDestroy(tree);
}

TEST(findK_Kmorethannodes, returnNULL) {
	node_t* tree = NULL;
	nodeAdd(&tree, 1);
	EXPECT_TRUE(findK(tree, 3) == NULL);
	treeDestroy(tree);
}

TEST(findK_Klessthannodes, returnPointer) {
	node_t* tree = NULL;
	nodeAdd(&tree, 1);
	EXPECT_TRUE(findK(tree, 1) != NULL);
	treeDestroy(tree);
}

TEST(findK_negativeK, returnNULL) {
	node_t* tree = NULL;
	nodeAdd(&tree, 1);
	EXPECT_TRUE(findK(tree, -2) == NULL);
	treeDestroy(tree);
}

