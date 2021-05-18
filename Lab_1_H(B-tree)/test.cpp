#include "gtest/gtest.h"
#include "pch.h"

extern "C"
{
#include "Header.h"
}


TEST(KeyInsert, KeyInsert_EmptyTree_RemoveSuccess) {
	B_Node* tempTree = NULL;
	KeyInsert(1, &tempTree);
	ASSERT_EQ(tempTree->n, 1);
	ASSERT_EQ(tempTree->leaf, TRUE);
	ASSERT_EQ(tempTree->keys[0], 1);
}

TEST(KeyInsert, KeyInsert_) {
	B_Node* tempTree = NULL;
	KeyInsert(1, &tempTree);
	KeyInsert(2, &tempTree);
	KeyInsert(3, &tempTree);
	KeyInsert(4, &tempTree);
	KeyInsert(5, &tempTree);
	KeyInsert(6, &tempTree);

	ASSERT_EQ(tempTree->n, 1);
	ASSERT_EQ(tempTree->leaf, FALSE);
	ASSERT_EQ(tempTree->keys[0], 3);

	ASSERT_EQ(tempTree->c[0]->n, 2);
	ASSERT_EQ(tempTree->c[0]->leaf, TRUE);
	ASSERT_EQ(tempTree->c[0]->keys[0], 1);
	ASSERT_EQ(tempTree->c[0]->keys[1], 2);

	ASSERT_EQ(tempTree->c[1]->n, 3);
	ASSERT_EQ(tempTree->c[1]->leaf, TRUE);
	ASSERT_EQ(tempTree->c[1]->keys[0], 4);
	ASSERT_EQ(tempTree->c[1]->keys[1], 5);
	ASSERT_EQ(tempTree->c[1]->keys[2], 6);

	free(tempTree->c[0]);
	free(tempTree->c[1]);
	free(tempTree);
}

TEST(KeyFind, KeyFind_KeyExists_ReturnsTrue) {
	B_Node* tempTree = NULL;
	KeyInsert(1, &tempTree);

	ASSERT_EQ(KeyFind(tempTree, 1), TRUE);

	free(tempTree);
}

TEST(KeyFind, KeyFind_KeyDoesNotExist_ReturnFalse) {
	B_Node* tempTree = NULL;
	KeyInsert(1, &tempTree);

	ASSERT_EQ(KeyFind(tempTree, 2), FALSE);

	free(tempTree);
}

TEST(KeyRemove, KeyRemove_KeyExists_RemoveSuccessfully) {
	KeyInsert(1, &tree); 
	KeyInsert(2, &tree);

	KeyRemove(2);

	ASSERT_EQ(tree->n, 1);
	ASSERT_EQ(tree->leaf, TRUE);
	ASSERT_EQ(tree->keys[0], 1);

	free(tree);
}