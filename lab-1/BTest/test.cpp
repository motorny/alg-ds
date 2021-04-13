#include "pch.h"

extern "C" {
#include "..//B_tree/Header.h"
}

TEST(Add_key, RightExpressions) {
	node_t* root = NULL;
	root = Insert(root, 2);
	ASSERT_EQ(root->n, 1);
	ASSERT_EQ(root->Isleaf, TRUE);
	ASSERT_EQ(root->key[0], 2);
}

TEST(SplitAfterInsert, Rightsplit) {
	node_t* root = NULL;
	root = Insert(root, 1);
	root = Insert(root, 2);
	root = Insert(root, 3);
	root = Insert(root, 4);
	root = Insert(root, 5);

	ASSERT_EQ(root->n, 1);
	ASSERT_EQ(root->Isleaf, FALSE);
	ASSERT_EQ(root->key[0], 2);

	ASSERT_EQ(root->kids[0]->n, 1);
	ASSERT_EQ(root->kids[0]->Isleaf, TRUE);
	ASSERT_EQ(root->kids[0]->key[0], 1);
	ASSERT_EQ(root->kids[0]->key[1], 2);

	ASSERT_EQ(root->kids[1]->n, 3);
	ASSERT_EQ(root->kids[1]->Isleaf, TRUE);
	ASSERT_EQ(root->kids[1]->key[0], 3);
	ASSERT_EQ(root->kids[1]->key[1], 4);
	ASSERT_EQ(root->kids[1]->key[2], 5);
}

TEST(Find, RightExpressions) {
	node_t* root = NULL;
	root = Insert(root, 5);
	
	EXPECT_EQ(FindKey(root, 5), TRUE);
	ASSERT_EQ(FindKey(root, 1), FALSE);

}

TEST(Keydelete, Keynotfound) {
	node_t* root = NULL;
	root = Insert(root, 1);
	root = Insert(root, 3);
	Remove(root, 1);

	ASSERT_EQ(root->n, 1);
	ASSERT_EQ(root->Isleaf, TRUE);
	ASSERT_EQ(FindKey(root, 1), FALSE);
}