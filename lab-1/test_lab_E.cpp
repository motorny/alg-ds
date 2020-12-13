#include "pch.h"
#include <stdio.h>

extern "C" {
#include "..//LAB_E_F//lab_E.c"
}

int CheckStr(char* str1, char* str2) {
	int i = 0;
	while (str1[i] != 0 || str2[i] != 0) {
		if (str1[i] != str2[i])
			return -1;
		i++;
	}
	return 1;
}


TEST(NULLFile, ReadFunction) {
	node_t* tree = ReadTree(NULL);
	EXPECT_TRUE(tree == NULL);
}

TEST(NormalCase, ReadFunction) {
	//hello (well (fire)(okey))(cool (perfect)(exiting))

	FILE* fp = fopen("tree.txt", "r");
	node_t* tree = ReadTree(fp);

	EXPECT_TRUE(CheckStr(tree->keyWord, "hello") == 1);

	EXPECT_TRUE(CheckStr(tree->left->keyWord, "well") == 1);
	EXPECT_TRUE(CheckStr(tree->left->left->keyWord, "fire") == 1);
	EXPECT_TRUE(CheckStr(tree->left->right->keyWord, "okey") == 1);

	EXPECT_TRUE(CheckStr(tree->right->keyWord, "cool") == 1);
	EXPECT_TRUE(CheckStr(tree->right->left->keyWord, "perfect") == 1);
	EXPECT_TRUE(CheckStr(tree->right->right->keyWord, "exiting") == 1);

	fclose(fp);
}

TEST(OneChildCase, ReadFunction) {
	//hello (well (fire)(okey))

	FILE* fp = fopen("treeOneChild.txt", "r");
	node_t* tree = ReadTree(fp);

	EXPECT_TRUE(CheckStr(tree->keyWord, "hello") == 1);

	EXPECT_TRUE(CheckStr(tree->left->keyWord, "well") == 1);
	EXPECT_TRUE(CheckStr(tree->left->left->keyWord, "fire") == 1);
	EXPECT_TRUE(CheckStr(tree->left->right->keyWord, "okey") == 1);

	EXPECT_TRUE(tree->right == NULL);

	fclose(fp);
}

TEST(NoChildrenCase, ReadFunction) {
	//hello 

	FILE* fp = fopen("treeNoChild.txt", "r");
	node_t* tree = ReadTree(fp);

	EXPECT_TRUE(CheckStr(tree->keyWord, "hello") == 1);

	EXPECT_TRUE(tree->left == NULL);

	EXPECT_TRUE(tree->right == NULL);

	fclose(fp);
}

TEST(EmptyKeyWord, ReadFunction) {
	//  (well (fire)(okey))(cool (perfect)(exiting))

	FILE* fp = fopen("EmptyKeyWord.txt", "r");
	node_t* tree = ReadTree(fp);

	EXPECT_TRUE(CheckStr(tree->keyWord, "") == 1);

	EXPECT_TRUE(CheckStr(tree->left->keyWord, "well") == 1);
	EXPECT_TRUE(CheckStr(tree->left->left->keyWord, "fire") == 1);
	EXPECT_TRUE(CheckStr(tree->left->right->keyWord, "okey") == 1);

	EXPECT_TRUE(CheckStr(tree->right->keyWord, "cool") == 1);
	EXPECT_TRUE(CheckStr(tree->right->left->keyWord, "perfect") == 1);
	EXPECT_TRUE(CheckStr(tree->right->right->keyWord, "exiting") == 1);

	fclose(fp);
}

