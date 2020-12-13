#include "pch.h"
#include<stdbool.h>
#include "..\SectionTree\SectionTree.h"
#include "..\SectionTree\SectionTree.c"
TEST(AddSegm, AddingToEmptyTree)
{
	NODE* root = NULL;
	InsertInTree(&root, 10, 15);
	ASSERT_EQ(10, root->leftBorder);
	ASSERT_EQ(15, root->rightBorder);
	ASSERT_EQ(NULL, root->left);
	ASSERT_EQ(NULL, root->right);
	DestroyTree(&root);
}

TEST(Add, AddingToLeftNode)
{
	NODE* root = NULL;
	InsertInTree(&root, 5, 10);
	InsertInTree(&root, 4, 11);
	ASSERT_EQ(4, root->left->leftBorder);
	ASSERT_EQ(11, root->left->rightBorder);
	DestroyTree(&root);
}

TEST(Add, AddingToRightNode)
{
	NODE* root = NULL;
	InsertInTree(&root, 5, 10);
	InsertInTree(&root, 6, 11);
	ASSERT_EQ(6, root->right->leftBorder);
	ASSERT_EQ(11, root->right->rightBorder);
	DestroyTree(&root);
}

NODE* createTree()
{
	NODE* root = NULL;
	InsertInTree(&root, 5, 9);
	InsertInTree(&root, 6, 8);
	InsertInTree(&root, 4, 11);
	InsertInTree(&root, 2, 5);
	InsertInTree(&root, 1, 3);
	InsertInTree(&root, 10, 15);

	return root;
}

TEST(FindTest, FindInterSegmTestDiff) {
	int counter = 0;
	NODE* root = NULL;
	NODE** interMass = NULL;

	InsertInTree(&root, 1, 4);
	InsertInTree(&root, 2, 7);
	InsertInTree(&root, -5, 3);
	InsertInTree(&root, 8, 10);

	interMass = FindInterSegm(root, 2, 3);
	for (counter; interMass[counter] != NULL; counter++) {
		EXPECT_TRUE(CheckForCrossing(2, 3, interMass[counter]->leftBorder, interMass[counter]->rightBorder));
	}
	EXPECT_TRUE(counter == 3);


	counter = 0;
	interMass = FindInterSegm(root, -2, 1);
	for (counter; interMass[counter] != NULL; counter++) {
		EXPECT_TRUE(CheckForCrossing(-2, 1, interMass[counter]->leftBorder, interMass[counter]->rightBorder));
	}
	EXPECT_TRUE(counter == 2);


	DestroyTree(&root);
	counter = 0;
	InsertInTree(&root, -8, -4);
	InsertInTree(&root, 8, 10);
	InsertInTree(&root, 5, 11);
	InsertInTree(&root, 2, 7);
	InsertInTree(&root, -3, 10);
	InsertInTree(&root, -11, -6);
	InsertInTree(&root, 6, 7);
	interMass = FindInterSegm(root, 0, 1);
	for (counter; interMass[counter] != NULL; counter++) {
		EXPECT_TRUE(CheckForCrossing(0, 1, interMass[counter]->leftBorder, interMass[counter]->rightBorder));
	}
	EXPECT_TRUE(counter == 1);

	DestroyTree(&root);
	free(interMass);
}