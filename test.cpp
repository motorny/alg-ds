#include "pch.h"

extern "C" {
#include "../treeofintervals/treeofintervals.h"
}

TEST(AddNode, EmptyTree_ReturnValidTree) {
	node_t* tree = NULL;

	EXPECT_EQ(AddNode(&tree, 1, 2), TRUE);
	EXPECT_NE(tree, nullptr);
	EXPECT_EQ(tree->left, nullptr);
	EXPECT_EQ(tree->right, nullptr);
	EXPECT_EQ(tree->parent, nullptr);
	EXPECT_EQ(tree->leftBorder, 1);
	EXPECT_EQ(tree->rightBorder, 2);

	free(tree);
}

TEST(AddNode, AddIntoTree_ReturnValidTree) {
	node_t* tree = NULL;
	AddNode(&tree, 2, 3);
	AddNode(&tree, 1, 2);
	AddNode(&tree, 3, 4);

	EXPECT_NE(tree, nullptr);
	EXPECT_NE(tree->left, nullptr);
	EXPECT_EQ(tree->parent, nullptr);
	EXPECT_NE(tree->right, nullptr);
	EXPECT_EQ(tree->leftBorder, 2);
	EXPECT_EQ(tree->rightBorder, 3);

	EXPECT_NE(tree->left, nullptr);
	EXPECT_EQ(tree->left->parent, tree);
	EXPECT_EQ(tree->left->left, nullptr);
	EXPECT_EQ(tree->left->right, nullptr);
	EXPECT_EQ(tree->left->leftBorder, 1);
	EXPECT_EQ(tree->left->rightBorder, 2);

	EXPECT_NE(tree->right, nullptr);
	EXPECT_EQ(tree->right->parent, tree);
	EXPECT_EQ(tree->right->left, nullptr);
	EXPECT_EQ(tree->right->right, nullptr);
	EXPECT_EQ(tree->right->leftBorder, 3);
	EXPECT_EQ(tree->right->rightBorder, 4);

	free(tree->left);
	free(tree->right);
	free(tree);
}

TEST(FindNode, NodeDoesntExist_ReturnNullPtr) {
	node_t* tree = NULL;
	AddNode(&tree, 1, 2);
	AddNode(&tree, 3, 4);

	EXPECT_EQ(FindNode(tree, 1, 4), nullptr);

	free(tree->right);
	free(tree);

}

TEST(FindNode, SearchInTree_ReturnValidPtr) {
	node_t* tree = NULL, * foundNode;
	AddNode(&tree, 2, 3);
	AddNode(&tree, 4, 5);
	AddNode(&tree, 3, 6);
	AddNode(&tree, 1, 2);

	foundNode = FindNode(tree, 3, 6);
	EXPECT_NE(foundNode, nullptr);
	EXPECT_EQ(foundNode->leftBorder, 3);
	EXPECT_EQ(foundNode->rightBorder, 6);
}

TEST(RemoveNode, NodeDoesntExist_ReturnFalse) {
	node_t* tree = NULL;
	AddNode(&tree, 1, 2);
	AddNode(&tree, 3, 4);

	EXPECT_EQ(RemoveNode(&tree, 1, 4), FALSE);
	EXPECT_EQ(tree->leftBorder, 1);
	EXPECT_EQ(tree->rightBorder, 2);
	EXPECT_NE(tree->right, nullptr);
	EXPECT_EQ(tree->right->leftBorder, 3);
	EXPECT_EQ(tree->right->rightBorder, 4);

	free(tree->right);
	free(tree);
}

TEST(RemoveNode, NodeExists_ReturnTrue) {
	node_t* tree = NULL;
	AddNode(&tree, 2, 3);
	AddNode(&tree, 3, 4);
	AddNode(&tree, 1, 3);

	EXPECT_EQ(RemoveNode(&tree, 2, 3), TRUE);

	EXPECT_NE(tree, nullptr);
	EXPECT_EQ(tree->left, nullptr);
	EXPECT_EQ(tree->parent, nullptr);
	EXPECT_NE(tree->right, nullptr);
	EXPECT_EQ(tree->leftBorder, 1);
	EXPECT_EQ(tree->rightBorder, 3);

	EXPECT_NE(tree->right, nullptr);
	EXPECT_EQ(tree->right->left, nullptr);
	EXPECT_EQ(tree->right->parent, tree);
	EXPECT_EQ(tree->right->right, nullptr);
	EXPECT_EQ(tree->right->leftBorder, 3);
	EXPECT_EQ(tree->right->rightBorder, 4);

	free(tree->right);
	free(tree);
}

TEST(FindIntersections, NoIntersections_ReturnNULL) {
	node_t* tree = NULL;
	AddNode(&tree, 2, 3);
	AddNode(&tree, 3, 4);
	AddNode(&tree, 1, 3);
	AddNode(&tree, 5, 6);

	EXPECT_EQ(FindIntersections(tree, 7, 8), nullptr);

	free(tree->right->right);
	free(tree->right);
	free(tree->left);
	free(tree);
}

TEST(FindIntersections, IntersectionsFound_ReturnValidPtr) {
	node_t* tree = NULL;
	node_t** intersections;
	AddNode(&tree, 2, 3);
	AddNode(&tree, 3, 4);
	AddNode(&tree, 1, 3);
	AddNode(&tree, 5, 6);

	intersections = FindIntersections(tree, 1, 2);
	EXPECT_NE(intersections, nullptr);
	EXPECT_EQ(intersections[0]->leftBorder, 2);
	EXPECT_EQ(intersections[0]->rightBorder, 3);
	EXPECT_EQ(intersections[1]->leftBorder, 1);
	EXPECT_EQ(intersections[1]->rightBorder, 3);
	EXPECT_EQ(intersections[2], nullptr);

	free(intersections);
	free(tree->right->right);
	free(tree->right);
	free(tree->left);
	free(tree);
}