#include "pch.h"
#include "2_3_tree.h"



TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestInit, TestValidInitialization) {
	node* a = InitNode(12);
	EXPECT_EQ(a->key[0], 12);
	free(a);
}

TEST(TestInsert, TestInsertNodeNoSplit) {
	node* a = InitNode(12);
	a = Insert(a, 32);
	
	EXPECT_EQ(a->key[0], 12);
	EXPECT_EQ(a->key[1], 32);


	free(a);
}


TEST(TestInsert, TestInsertNodeSplit) {
	node* a = InitNode(12);
	a = Insert(a, 32);
	a = Insert(a, 77);

	EXPECT_EQ(a->key[0], 32);
	EXPECT_EQ(a->first->key[0], 12);
	EXPECT_EQ(a->second->key[0], 77);

	free(a->first);
	free(a->second);
	free(a);
}


TEST(TestInsert, TestInsertLeftSubTree) {
	node* a = InitNode(12);
	a = Insert(a, 32);
	a = Insert(a, 77);
	a = Insert(a, 20);

	EXPECT_EQ(a->first->key[0], 12);
	EXPECT_EQ(a->first->key[1], 20);

	free(a->first);
	free(a->second);
	free(a);
}

TEST(TestInsert, TestInsertRightSubTree) {
	node* a = InitNode(12);
	a = Insert(a, 32);
	a = Insert(a, 77);
	a = Insert(a, 60);

	EXPECT_EQ(a->second->key[0], 60);
	EXPECT_EQ(a->second->key[1], 77);

	free(a->first);
	free(a->second);
	free(a);
}


TEST(TestSearch, TestEmptyTreeReturnFalse) {
	node* a = Search(NULL, 12);
	EXPECT_FALSE(a);
}

TEST(TestSearch, TestOneNodeTreeReturnValidVal) {
	node* a = NULL;
	a = Insert(a, 12);
	EXPECT_TRUE(Search(a,12));
	free(a);
}

TEST(TestSearch, TestSearchLeftTreeReturnValidVal) {
	node* a = NULL;
	a = Insert(a, 12);
	a = Insert(a, 22);
	a = Insert(a, 72);

	EXPECT_TRUE(Search(a, 12));
	free(a->first);
	free(a->second);
	free(a);


}

TEST(TestSearch, TestSearchRightTreeReturnTrue) {
	node* a = NULL;
	a = Insert(a, 12);
	a = Insert(a, 22);
	a = Insert(a, 72);

	EXPECT_TRUE(Search(a, 72));
	free(a->first);
	free(a->second);
	free(a);


}

TEST(TestRemove, TestEmptyTreeReturnNull) {
	node* a = NULL;

	EXPECT_FALSE(Remove(a,33));
}

TEST(TestRemove, TestRemoveNonExistingElemReturnNull) {
	node* a = NULL;
	a = Insert(a, 12);
	a = Insert(a, 72);
	a = Insert(a, 13);


	EXPECT_FALSE(Remove(a, 33));
	free(a->first);
	free(a->second);
	free(a);

}


TEST(TestRemove, TestRemoveFromRootReturnNull) {
	node* a = NULL;
	a = Insert(a, 12);
	a = Insert(a, 72);
	a = Insert(a, 13);

	a = Remove(a, 13);
	EXPECT_EQ(a->key[0], 12);
	EXPECT_EQ(a->key[1], 72);


	free(a);
}


TEST(TestRemove, TestRemoveFromLeftTreeReturnTrue) {
	node* a = NULL;
	a = Insert(a, 12);
	a = Insert(a, 72);
	a = Insert(a, 13);
	a = Remove(a, 12);
	EXPECT_TRUE(a!=NULL);
	EXPECT_EQ(a->key[0],13);
	EXPECT_EQ(a->key[1], 72);

	
	free(a);
}

TEST(TestRemove, TestRemoveFromRightTreeReturnTrue) {
	node* a = NULL;
	a = Insert(a, 12);
	a = Insert(a, 72);
	a = Insert(a, 13);
	a = Remove(a, 72);
	EXPECT_TRUE(a != NULL);
	EXPECT_EQ(a->key[0], 12);
	EXPECT_EQ(a->key[1], 13);


	free(a);
}



