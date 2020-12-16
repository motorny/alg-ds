#include "pch.h"

extern "C" {
#include "../Interval Tree/intervalTree.h"
#include "../Interval Tree/intervalTree.c"
}

TEST(AddByLeftBorder, Create_tree) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);

	EXPECT_NE(tree, (tree_t*)NULL);
	EXPECT_EQ(tree->leftBorder, -1);
	EXPECT_EQ(tree->rightBorder, 1);
	EXPECT_EQ(tree->left, (tree_t*)NULL);
	EXPECT_EQ(tree->right, (tree_t*)NULL);
	EXPECT_EQ(tree->parent, (tree_t*)NULL);

	DestroyTree(tree);
}

TEST(AddByLeftBorder, Sequential_addition) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);
	AddByLeftBorder(&tree, -6, 4);
 
	EXPECT_NE(tree->left, (tree_t*)NULL);
	EXPECT_NE(tree->left->left, (tree_t*)NULL);
	EXPECT_TRUE(tree->left->leftBorder < tree->leftBorder);
	EXPECT_TRUE(tree->left->left->leftBorder < tree->left->leftBorder);

	DestroyTree(tree);
}

TEST(AddByLeftBorder, Node_is_already_exist_return_NOT_FINISHED) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);

	EXPECT_EQ(AddByLeftBorder(&tree, -1, 1), NOT_FINISHED);
	EXPECT_NE(tree, (tree_t*)NULL);
	EXPECT_EQ(tree->leftBorder, -1);
	EXPECT_EQ(tree->rightBorder, 1);
	EXPECT_EQ(tree->left, (tree_t*)NULL);
	EXPECT_EQ(tree->right, (tree_t*)NULL);
	EXPECT_EQ(tree->parent, (tree_t*)NULL);

	DestroyTree(tree);
}

TEST(FindByBorders, Node_is_not_exist_return_NULL) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);

	EXPECT_EQ(FindByBorders(tree, -2, 2), (tree_t*)NULL);

	DestroyTree(tree);
}

TEST(FindByBorders, Node_is_found_return_ptr) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);
	AddByLeftBorder(&tree, -2, 15);

	EXPECT_EQ(FindByBorders(tree, -2, 15), tree->left->right);

	DestroyTree(tree);
}

TEST(DeleteByBorders, Node_is_not_exist_return_ERROR) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);

	EXPECT_EQ(DeleteByBorders(FindByBorders(tree, -2, 2)), ERROR);

	DestroyTree(tree);
}

TEST(DeleteByBorders, Node_without_sons_return_FINISHED) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);

	EXPECT_EQ(DeleteByBorders(FindByBorders(tree, -4, 10)), FINISHED);
	EXPECT_EQ(tree->left, (tree_t*)NULL);

	DestroyTree(tree);

}

TEST(DeleteByBorders, Node_with_the_left_son_return_FINISHED) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);
	AddByLeftBorder(&tree, -6, 4);

	EXPECT_EQ(DeleteByBorders(FindByBorders(tree, -4, 10)), FINISHED);
	EXPECT_EQ(tree->left->leftBorder, -6);
	EXPECT_EQ(tree->left->rightBorder, 4);
	EXPECT_EQ(tree->left->left, (tree_t*)NULL);
	EXPECT_EQ(tree->left->parent, tree);

	DestroyTree(tree);
}

TEST(DeleteByBorders, Node_with_the_right_son_return_FINISHED) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);
	AddByLeftBorder(&tree, -2, 15);

	EXPECT_EQ(DeleteByBorders(FindByBorders(tree, -4, 10)), FINISHED);
	EXPECT_EQ(tree->left->right, (tree_t*)NULL);
	EXPECT_EQ(tree->left->parent, tree);
	EXPECT_EQ(tree->left->leftBorder, -2);
	EXPECT_EQ(tree->left->rightBorder, 15);

	DestroyTree(tree);
}

TEST(DeleteByBorders, Both_sons_return_FINISHED) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);
	AddByLeftBorder(&tree, -6, 4);
	AddByLeftBorder(&tree, -2, 15);

	EXPECT_EQ(DeleteByBorders(FindByBorders(tree, -4, 10)), FINISHED);
	EXPECT_EQ(tree->left->leftBorder, -6);
	EXPECT_EQ(tree->left->rightBorder, 4);
	EXPECT_EQ(tree->left->parent, tree);
	EXPECT_EQ(tree->left->left, (tree_t*)NULL);
	EXPECT_EQ(tree->left->right->leftBorder, -2);
	EXPECT_EQ(tree->left->right->rightBorder, 15);

	DestroyTree(tree);
}

TEST(SearchIntersecting, No_intersecting_segments_return_NOT_FINISHED) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);
	AddByLeftBorder(&tree, -6, 4);
	AddByLeftBorder(&tree, -2, 15);
	answer_t* answer = (answer_t*)malloc(sizeof(answer_t));
	answer->segments = (segment_t*)malloc(sizeof(segment_t));
	answer->count = 0;

	EXPECT_EQ(SearchIntersecting(tree, 16, 20, answer), NOT_FINISHED);
	EXPECT_EQ(answer->count, 0);

	FreeAnswer(answer);
	DestroyTree(tree);
}

TEST(SearchIntersecting, Found_intersecting_segments_return_FINISHED) {
	tree_t* tree = NULL;
	AddByLeftBorder(&tree, -1, 1);
	AddByLeftBorder(&tree, -4, 10);
	AddByLeftBorder(&tree, -6, 4);
	AddByLeftBorder(&tree, -2, 15);
	answer_t* answer = (answer_t*)malloc(sizeof(answer_t));
	answer->segments = (segment_t*)malloc(sizeof(segment_t));
	answer->count = 0;

	EXPECT_EQ(SearchIntersecting(tree, -4, -2, answer), FINISHED);
	EXPECT_EQ(answer->count, 3);

	FreeAnswer(answer);
	DestroyTree(tree);
}