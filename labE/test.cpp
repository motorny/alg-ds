#include "pch.h"
#include "C:\Users\79523\source\repos\ALG4\ALG4\tree.c"

TREE_NODE* TestTree() {
	TREE_NODE* tree = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	tree->number = 2;
	tree->left = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	tree->right = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	tree->left->number = 0;
	tree->right->number = 3;
	tree->left->left = NULL;
	tree->left->right = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	tree->right->left = NULL;
	tree->right->right = NULL;
	tree->left->right->number = 1;
	tree->left->right->left = NULL;
	tree->left->right->right = NULL;

	return tree;
}

TEST(Insert, EmptyTree_ValidInsert) {
	TREE_NODE* tree = NULL;
	Insert(&tree, 5);
	EXPECT_EQ(tree->number, 5);
	EXPECT_EQ(tree->left, (TREE_NODE*)NULL);
	EXPECT_EQ(tree->right, (TREE_NODE*)NULL);

	free(tree);
}

TEST(Insert, RegularTree_ValidInsert) {
	TREE_NODE* tree = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	tree->number = 2;
	tree->left = NULL;
	tree->right = NULL;
	Insert(&tree, 1);
	Insert(&tree, 3);
	EXPECT_EQ(tree->number, 2);
	EXPECT_TRUE(tree->left != (TREE_NODE*)NULL);
	EXPECT_TRUE(tree->right != (TREE_NODE*)NULL);
	EXPECT_EQ(tree->left->number, 1);
	EXPECT_EQ(tree->right->number, 3);
	EXPECT_EQ(tree->left->left, (TREE_NODE*)NULL);
	EXPECT_EQ(tree->left->right, (TREE_NODE*)NULL);
	EXPECT_EQ(tree->right->left, (TREE_NODE*)NULL);
	EXPECT_EQ(tree->right->right, (TREE_NODE*)NULL);

	Clear(tree);
}

TEST(Search, CorrectSearching) {
	TREE_NODE* tree = TestTree();
	EXPECT_EQ(Search(tree, 2), FOUND_ELEMENT);
	EXPECT_EQ(Search(tree, 10), NO_ELEMENT);

	Clear(tree);
}

TEST(MinValueNode, CorrectWork) {
	TREE_NODE* tree = TestTree();
	tree = MinValueNode(tree);
	EXPECT_EQ(tree->number, 0);
	EXPECT_TRUE(tree->left == (TREE_NODE*)NULL);

	Clear(tree);
}

TEST(Delete, DeleteAllCorrect) {
	TREE_NODE* tree = TestTree();
	Delete(&tree, 0);
	Delete(&tree, 1);
	Delete(&tree, 2);
	Delete(&tree, 3);
	Delete(&tree, 4);
	EXPECT_EQ(tree, (TREE_NODE*)NULL);

	Clear(tree);
}

TEST(Delete, DeleteOneNodeCorrect) {
	TREE_NODE* tree = TestTree();
	Delete(&tree, 0);
	EXPECT_EQ(tree->left->number, 1);
	EXPECT_EQ(tree->left->right, (TREE_NODE*)NULL);
	Clear(tree);
}