#include "pch.h"
#include "..\SearchTree\LabF22.c"

TEST(addSegm, addingToEmptyTree)
{
	TREESEGM* tree = NULL;
	addSegment(&tree, 10, 15);
	ASSERT_EQ(10, tree->leftBorder);
	ASSERT_EQ(15, tree->rightBorder);
	ASSERT_EQ(NULL, tree->left);
	ASSERT_EQ(NULL, tree->right);
	destroyTreeSegm(tree);
}

TEST(add, addingToLeftNode)
{
	TREESEGM* tree = NULL;
	addSegment(&tree, 5, 10);
	addSegment(&tree, 4, 11);
	ASSERT_EQ(4, tree->left->leftBorder);
	ASSERT_EQ(11, tree->left->rightBorder);
	destroyTreeSegm(tree);
}

TEST(add, addingToRightNode)
{
	TREESEGM* tree = NULL;
	addSegment(&tree, 5, 10);
	addSegment(&tree, 6, 11);
	ASSERT_EQ(6, tree->right->leftBorder);
	ASSERT_EQ(11, tree->right->rightBorder);
	destroyTreeSegm(tree);
}

TREESEGM* createTree()
{
	TREESEGM* tree = NULL;
	addSegment(&tree, 5, 9);
	addSegment(&tree, 6, 8);
	addSegment(&tree, 4, 11);
	addSegment(&tree, 2, 5);
	addSegment(&tree, 1, 3);
	addSegment(&tree, 10, 15);

	return tree;
}

TEST(find, elemIsInTheTree)
{
	TREESEGM* tree = createTree();
	ASSERT_EQ(1, findSegmention(tree, 4, 11));
	ASSERT_EQ(1, findSegmention(tree, 10, 15));
	destroyTreeSegm(tree);
}

TEST(find, elemIsNotInTheTree)
{
	TREESEGM* tree = createTree();
	ASSERT_EQ(0, findSegmention(tree, 9, 12));
	ASSERT_EQ(0, findSegmention(tree, 11, 18));
	destroyTreeSegm(tree);
}

TEST(del, delElemIsInTheTree)
{
	TREESEGM* tree = createTree();
	delSegment(&tree, 4, 11);
	ASSERT_EQ(0, findSegmention(tree, 4, 11));
	destroyTreeSegm(tree);
}

TEST(interSegm, intersectionNotExists)
{
	TREESEGM* tree = createTree();
	interSegm(tree, -4, 0);
	ASSERT_EQ(0, index);
	destroyTreeSegm(tree);
}

TEST(interSegm, intersectionExists)
{
	TREESEGM* tree = createTree();
	interSegm(tree, 4, 8);
	ASSERT_EQ(5, answer[0].lBorder);
	ASSERT_EQ(9, answer[0].rBorder);
	ASSERT_EQ(4, answer[1].lBorder);
	ASSERT_EQ(11, answer[1].rBorder);
	ASSERT_EQ(4, index);
	destroyTreeSegm(tree);
}