#include "pch.h"
extern "C" {
	#include "labH.h"
}


TEST(CreateTree, returnTree) {
	node_t* tree;
	int error = NO_ERRORS;
	tree = CreateTree(5, 4, NULL, NULL, &error);

	EXPECT_EQ(5, tree->key);
	EXPECT_EQ(4, tree->priority);
	EXPECT_EQ(tree->left || tree->right, NULL);
	EXPECT_EQ(error, NO_ERRORS);

	DeleteTree(tree);
}

TEST(Merge, returnValidVal) {
	node_t* tree1, *tree2, *tree;
	int error = NO_ERRORS;
	tree1 = CreateTree(5, 4, NULL, NULL, &error);
	tree2 = CreateTree(7, 14, NULL, NULL, &error);

	tree = Merge(tree1, tree2, &error);

	EXPECT_EQ(7, tree->key);
	EXPECT_EQ(5, tree->left->key);
	EXPECT_EQ(tree->left->left || tree->left->right || tree->right, NULL);
	EXPECT_EQ(error, NO_ERRORS);

	DeleteTree(tree);
}

TEST(Split, returnValidVal) {
	node_t* tree1, * tree2, * tree;
	int error = NO_ERRORS;
	tree1 = CreateTree(5, 4, NULL, NULL, &error);
	tree2 = CreateTree(8, 7, NULL, NULL, &error);

	tree = CreateTree(7, 10, tree1, tree2, &error);
	Split(6, tree, &tree1, &tree2, &error);

	EXPECT_EQ(5, tree1->key);
	EXPECT_EQ(7, tree2->key);
	EXPECT_EQ(error, NO_ERRORS);

	DeleteTree(tree);
}

TEST(Add, NullTreeReturnValidVal) {
	node_t* tree = NULL;
	int error = NO_ERRORS;

	Add(4, &tree, &error);
	EXPECT_EQ(tree->key, 4);
	EXPECT_EQ(error, NO_ERRORS);

	DeleteTree(tree);
}

TEST(Add, FilledTreeReturnValidVal) {
	node_t* tree;
	int error = NO_ERRORS;

	tree = CreateTree(3, -2, NULL, NULL, &error);
	Add(4, &tree, &error);

	EXPECT_EQ(tree->key, 4);
	EXPECT_EQ(error, NO_ERRORS);

	DeleteTree(tree);
}

TEST(Delete, NullTreeReturnError) {
	node_t* tree = NULL;
	int error = NO_ERRORS;

	Delete(4, &tree, &error);

	EXPECT_EQ(error, NO_ELEMENTS);

	DeleteTree(tree);
}

TEST(Delete, FilledTreeReturnValidVal) {
	node_t* tree;
	int error = NO_ERRORS;

	tree = CreateTree(4, rand(), NULL, NULL, &error);
	Delete(4, &tree, &error);

	EXPECT_EQ(error, NO_ERRORS);
	EXPECT_TRUE(!tree);

	DeleteTree(tree);
}

TEST(Search, NullTreeReturnError) {
	node_t* tree = NULL;
	int error = NO_ERRORS, result;

	result = Search(4, tree, &error);

	EXPECT_EQ(error, NO_ERRORS);
	EXPECT_EQ(result, 0);

	DeleteTree(tree);
}


TEST(Search, FilledTreeReturnValidVal) {
	int error = NO_ERRORS, result;
	node_t* tree = CreateTree(4, rand(), NULL, NULL, &error);

	result = Search(4, tree, &error);

	EXPECT_EQ(error, NO_ERRORS);
	EXPECT_EQ(result, 1);

	DeleteTree(tree);
}
