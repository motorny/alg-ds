#include "pch.h"
extern "C" {
#include "tree.h"
}

TEST(TestInit, TestValidInitialization) {
	node_t* a = InitNode(12);
	EXPECT_EQ(a->key[0], 12);
	free(a);
}

TEST(TestInsert, TestInsertNodeNoSplit) {
	node_t* a = InitNode(12);
	a = AddElem(a, 32);

	EXPECT_EQ(a->key[0], 12);
	EXPECT_EQ(a->key[1], 32);

	free(a);
}


TEST(TestInsert, TestInsertNodeSplit) {
	node_t* a = InitNode(12);
	a = AddElem(a, 32);
	a = AddElem(a, 77);

	EXPECT_EQ(a->key[0], 32);
	EXPECT_EQ(a->first->key[0], 12);
	EXPECT_EQ(a->second->key[0], 77);

	free(a->first);
	free(a->second);
	free(a);
}


TEST(TestInsert, TestInsertLeftSubTree) {
	node_t* a = InitNode(12);
	a = AddElem(a, 32);
	a = AddElem(a, 77);
	a = AddElem(a, 20);

	EXPECT_EQ(a->first->key[0], 12);
	EXPECT_EQ(a->first->key[1], 20);

	free(a->first);
	free(a->second);
	free(a);
}

TEST(TestInsert, TestInsertRightSubTree) {
	node_t* a = InitNode(12);
	a = AddElem(a, 32);
	a = AddElem(a, 77);
	a = AddElem(a, 60);

	EXPECT_EQ(a->second->key[0], 60);
	EXPECT_EQ(a->second->key[1], 77);

	free(a->first);
	free(a->second);
	free(a);
}


TEST(TestSearch, TestEmptyTreeReturnFalse) {
	node_t* a = FindElem(NULL, 12);
	EXPECT_FALSE(a);
}

TEST(TestSearch, TestOneNodeTreeReturnValidVal) {
	node_t* a = NULL;
	a = AddElem(a, 12);
	EXPECT_TRUE(FindElem(a, 12));
	free(a);
}

TEST(TestSearch, TestSearchLeftTreeReturnValidVal) {
	node_t* a = NULL;
	a = AddElem(a, 12);
	a = AddElem(a, 22);
	a = AddElem(a, 72);

	EXPECT_TRUE(FindElem(a, 12));
	free(a->first);
	free(a->second);
	free(a);


}

TEST(TestSearch, TestSearchRightTreeReturnTrue) {
	node_t* a = NULL;
	a = AddElem(a, 12);
	a = AddElem(a, 22);
	a = AddElem(a, 72);

	EXPECT_TRUE(FindElem(a, 72));
	free(a->first);
	free(a->second);
	free(a);


}

TEST(TestRemove, TestEmptyTreeReturnNull) {
	node_t* a = NULL;

	EXPECT_FALSE(RemoveElem(a, 33));
}

TEST(TestRemove, TestRemoveNonExistingElemReturnNull) {
	node_t* a = NULL;
	a = AddElem(a, 12);
	a = AddElem(a, 72);
	a = AddElem(a, 13);


	EXPECT_FALSE(RemoveElem(a, 33));
	free(a->first);
	free(a->second);
	free(a);

}


TEST(TestRemove, TestRemoveFromRootReturnNull) {
	node_t* a = NULL;
	a = AddElem(a, 12);
	a = AddElem(a, 72);
	a = AddElem(a, 13);

	a = RemoveElem(a, 13);
	EXPECT_EQ(a->key[0], 12);
	EXPECT_EQ(a->key[1], 72);


	free(a);
}


TEST(TestRemove, TestRemoveFromLeftTreeReturnTrue) {
	node_t* a = NULL;
	a = AddElem(a, 12);
	a = AddElem(a, 72);
	a = AddElem(a, 13);
	a = RemoveElem(a, 12);
	EXPECT_TRUE(a != NULL);
	EXPECT_EQ(a->key[0], 13);
	EXPECT_EQ(a->key[1], 72);


	free(a);
}

TEST(TestRemove, TestRemoveFromRightTreeReturnTrue) {
	node_t* a = NULL;
	a = AddElem(a, 12);
	a = AddElem(a, 72);
	a = AddElem(a, 13);
	a = RemoveElem(a, 72);
	EXPECT_TRUE(a != NULL);
	EXPECT_EQ(a->key[0], 12);
	EXPECT_EQ(a->key[1], 13);


	free(a);
}