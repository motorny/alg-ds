#include "pch.h"
#include "C:\Users\79523\source\repos\ALG4\ALG4\tree.c"

SPLAYTREE* TestTree() {
	SPLAYTREE* tree = (SPLAYTREE*)malloc(sizeof(SPLAYTREE));
	tree->number = 2;
	tree->left = (SPLAYTREE*)malloc(sizeof(SPLAYTREE));
	tree->right = (SPLAYTREE*)malloc(sizeof(SPLAYTREE));
	tree->parent = NULL;
	tree->left->number = 0;
	tree->right->number = 3;
	tree->left->left = NULL;
	tree->left->right = (SPLAYTREE*)malloc(sizeof(SPLAYTREE));
	tree->left->parent = tree;
	tree->right->left = NULL;
	tree->right->right = NULL;
	tree->right->parent = tree;
	tree->left->right->number = 1;
	tree->left->right->left = NULL;
	tree->left->right->right = NULL;
	tree->left->right->parent = tree->left;

	return tree;
}

TEST(Insert, EmptyTree_ValidInsert) {
	SPLAYTREE* tree = NULL;
	Insert(&tree, 5);
	EXPECT_EQ(tree->number, 5);
	EXPECT_EQ(tree->left, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->right, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->parent, (SPLAYTREE*)NULL);

	free(tree);
}

TEST(Insert, RegularTree_ValidInsert) {
	SPLAYTREE* tree = (SPLAYTREE*)malloc(sizeof(SPLAYTREE));
	tree->number = 2;
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;
	Insert(&tree, 1);
	Insert(&tree, 3);
	EXPECT_EQ(tree->number, 2);
	EXPECT_TRUE(tree->left != (SPLAYTREE*)NULL);
	EXPECT_TRUE(tree->right != (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->parent, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->left->number, 1);
	EXPECT_EQ(tree->right->number, 3);
	EXPECT_EQ(tree->left->left, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->left->right, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->left->parent->number, 2);
	EXPECT_EQ(tree->right->left, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->right->right, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->right->parent->number, 2);
	Clear(tree);
}

TEST(Search, CorrectSearching) {
	SPLAYTREE* tree = TestTree();
	SPLAYTREE* searched1 = Search(tree, 2);
	SPLAYTREE* searched2 = Search(tree, 10);
	EXPECT_TRUE(searched1 != NULL);
	EXPECT_TRUE(searched2 == NULL);

	Clear(tree);
}

TEST(MinValueNode, CorrectWork) {
	SPLAYTREE* tree = TestTree();
	tree = MinValueNode(tree);
	EXPECT_EQ(tree->number, 0);
	EXPECT_TRUE(tree->left == (SPLAYTREE*)NULL);

	Clear(tree);
}

TEST(Delete, DeleteAllCorrect) {
	SPLAYTREE* tree = TestTree();
	Delete(&tree, 0);
	Delete(&tree, 1);
	Delete(&tree, 2);
	Delete(&tree, 3);
	Delete(&tree, 4);
	EXPECT_EQ(tree, (SPLAYTREE*)NULL);

	Clear(tree);
}

TEST(Delete, DeleteOneNodeCorrect) {
	SPLAYTREE* tree = TestTree();
	Delete(&tree, 0);
	EXPECT_EQ(tree->left->number, 1);
	EXPECT_EQ(tree->left->right, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->left->parent->number, 2);
	Clear(tree);
}

TEST(Splay, CorrectWorkOfSplay) {
	SPLAYTREE* tree = TestTree();
	tree = Splay(tree->left->right);
	EXPECT_EQ(tree->number, 1);
	EXPECT_EQ(tree->parent, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->left->number, 0);
	EXPECT_EQ(tree->left->left, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->left->right, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->left->parent->number, 1);
	EXPECT_EQ(tree->right->number, 2);
	EXPECT_EQ(tree->right->left, (SPLAYTREE*)NULL);
	EXPECT_EQ(tree->right->right->number, 3);
	EXPECT_EQ(tree->right->parent->number, 1);
	EXPECT_EQ(tree->right->right->parent->number, 2);
	Clear(tree);
}