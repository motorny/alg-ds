#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C"
{
#include "C:/Users/Lenovo/source/repos/AlgE6/E6.c"
#include "C:/Users/Lenovo/source/repos/AlgE6/E6.h"
}

#define TRUE 1
#define FALSE 0

TEST(ReadFile_NULLFile_returnNULLandFALSE) {
	node* tree;
	int res = ReadFile(&tree, "C:/Users/Lenovo/source/repos/E6test/NotExist.txt");

	EXPECT_EQ(res, FALSE);
	EXPECT_EQ(tree == NULL, 1);
}

TEST(ReadFile_1NodeTree_returnTRUEandTree) {
	//this
	node* tree;
	int res = ReadFile(&tree, "C:/Users/Lenovo/source/repos/E6test/this.txt");

	EXPECT_EQ(res, TRUE);
	EXPECT_EQ(strcmp(tree->key, "this"), 0);
	EXPECT_EQ(tree->right == NULL, 1);
	EXPECT_EQ(tree->left == NULL, 1);
}

TEST(ReadFile_2NodeTree_returnTRUEandTree) {
	//this(is)()
	node* tree;
	int res = ReadFile(&tree, "C:/Users/Lenovo/source/repos/E6test/thisis.txt");

	EXPECT_EQ(res, TRUE);
	EXPECT_EQ(strcmp(tree->key, "this"), 0);
	EXPECT_EQ(tree->right == NULL, 1);

	EXPECT_EQ(strcmp(tree->left->key, "is"), 0);
	EXPECT_EQ(tree->left->left == NULL, 1);
	EXPECT_EQ(tree->left->right == NULL, 1);
}


TEST(ReadFile_3NodeTree_returnTRUEandTree) {
	//this(is)(okay)
	node* tree;
	int res = ReadFile(&tree, "C:/Users/Lenovo/source/repos/E6test/thisisokay.txt");

	EXPECT_EQ(res, TRUE);
	EXPECT_EQ(strcmp(tree->key, "this"), 0);

	EXPECT_EQ(strcmp(tree->left->key, "is"), 0);
	EXPECT_EQ(tree->left->left == NULL, 1);
	EXPECT_EQ(tree->left->right == NULL, 1);

	EXPECT_EQ(strcmp(tree->right->key, "okay"), 0);
	EXPECT_EQ(tree->right->left == NULL, 1);
	EXPECT_EQ(tree->right->right == NULL, 1);
}

TEST(ReadFile_EmptyStr_returnFALSEandNULL) {
	node* tree;
	int res = ReadFile(&tree, "C:/Users/Lenovo/source/repos/E6test/nowords.txt");

	EXPECT_EQ(res, FALSE);
	EXPECT_EQ(tree == NULL, 1);
}

