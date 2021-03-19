#pragma warning(disable:4996)

#include "pch.h"
extern "C" {
#include "Dekart.h"
}

node_t* TreeTest() {

	node_t* treeTest1 = Insert(10);
	node_t* treeTest2 = Insert(20);
	node_t* treeTest3 = Insert(30);
	node_t* treeTest4 = Insert(40);

	treeTest1->prior = treeTest1->val;
	treeTest1->left = treeTest2;
	treeTest1->right = treeTest4;
	treeTest1->size = 4;

	treeTest2->prior = treeTest2->val;
	treeTest2->left = NULL;
	treeTest2->right = treeTest3;
	treeTest2->size = 2;

	treeTest3->prior = treeTest3->val;
	treeTest3->left = NULL;
	treeTest3->right = NULL;
	treeTest3->size = 1;

	treeTest4->prior = treeTest4->val;
	treeTest4->left = NULL;
	treeTest4->right = NULL;
	treeTest4->size = 1;

	return treeTest1;
}

TEST(TestGetSize, Empty) {

	node_t* treeTest = NULL;
	EXPECT_EQ(GetSize(treeTest), 0);
}

TEST(TestGetSize, NotEmpty) {

	node_t* treeTest = Insert(10);
	treeTest->size = 10;
	EXPECT_EQ(GetSize(treeTest), 10);
	DestroyTree(treeTest);
}

TEST(TestUpdateSize, NoSons) {

	node_t* treeTest = TreeTest()->right;
	treeTest->size = 0;
	UpdateSize(treeTest);
	int testSize2 = treeTest->size;
	EXPECT_EQ(testSize2, 1);
	DestroyTree(treeTest);
}

TEST(TestUpdateSize, TwoSons) {

	node_t* treeTest = TreeTest();
	treeTest->size = 0;
	int testSize1 = treeTest->left->size + treeTest->right->size + 1;
	UpdateSize(treeTest);
	int testSize2 = treeTest->size;
	EXPECT_EQ(testSize2, testSize1);
	DestroyTree(treeTest);
}

TEST(TestMerge, EmptyTree) {

	node_t* treeTest1, * treeTest2;
	treeTest1 = NULL;
	treeTest2 = TreeTest();
	node_t* treeTest = Merge(treeTest1, treeTest2);
	EXPECT_EQ(treeTest, treeTest2);
	DestroyTree(treeTest);
}

TEST(TestMerge, TwoEmptyTrees) {

	node_t* treeTest1, * treeTest2;
	treeTest1 = treeTest2 = NULL;
	node_t* treeTest = Merge(treeTest1, treeTest2);
	EXPECT_TRUE(!treeTest);
	DestroyTree(treeTest);
	DestroyTree(treeTest2);
	DestroyTree(treeTest1);
}

TEST(TestMerge, NotEmptyTrees) {

	node_t* treeTest1, * treeTest2;
	treeTest1 = Insert(10);
	treeTest2 = TreeTest();
	node_t* treeTest = Merge(treeTest1, treeTest2);
	EXPECT_TRUE(treeTest == treeTest1);
	EXPECT_EQ(treeTest->size, treeTest1->size);
	DestroyTree(treeTest);
}

TEST(TestSplit, EmptyTree) {

	node_t* treeTest = NULL;
	node_t* treeTest1, * treeTest2;
	Split(1, treeTest, &treeTest1, &treeTest2, 0);
	EXPECT_TRUE(!treeTest1);
	EXPECT_TRUE(!treeTest2);
	DestroyTree(treeTest);
}

TEST(TestSplit, OneEmptyTree) {

	node_t* treeTest = TreeTest();
	node_t* treeTest1, * treeTest2;
	Split(0, treeTest, &treeTest1, &treeTest2, 0);
	EXPECT_TRUE(!treeTest1);
	EXPECT_TRUE(treeTest2 == treeTest);
	DestroyTree(treeTest);
}

TEST(TestSplit, TwoTree) {

	node_t* treeTest = TreeTest();
	node_t* treeTest1, * treeTest2;
	int TestSize = treeTest->size;
	Split(1, treeTest, &treeTest1, &treeTest2, 0);
	EXPECT_TRUE(treeTest1);
	EXPECT_TRUE(treeTest2);
	EXPECT_EQ(treeTest2->size, TestSize - 1);
	EXPECT_EQ(treeTest1->size, 1);
	DestroyTree(treeTest1);
	DestroyTree(treeTest2);
}

TEST(TestSplit, BigSize) {

	node_t* treeTest = TreeTest();
	node_t* treeTest1, * treeTest2;
	Split(treeTest->size + 1, treeTest, &treeTest1, &treeTest2, 0);
	EXPECT_TRUE(!treeTest2);
	EXPECT_TRUE(treeTest1 == treeTest);
	DestroyTree(treeTest1);
}

TEST(TestAddNode, EmptyTree) {

	node_t* treeTest = NULL;
	AddNode(&treeTest, 0, 10);
	EXPECT_TRUE(treeTest);
	EXPECT_TRUE(treeTest->size == 1);
	EXPECT_EQ(10, treeTest->val);
	DestroyTree(treeTest);
}

TEST(TestAddNode, NegN) {

	node_t* treeTest = TreeTest();
	AddNode(&treeTest, -10, 10);
	EXPECT_TRUE(treeTest->size == 4);
	DestroyTree(treeTest);
}

TEST(TestAddNode, PosN) {

	node_t* treeTest = TreeTest();
	AddNode(&treeTest, 1, 10);
	EXPECT_TRUE(treeTest->size == 5);
	EXPECT_EQ(10, treeTest->val);
	DestroyTree(treeTest);
}

TEST(TestIsFind, NotFind) {

	node_t* treeTest = NULL;
	int find = 0;
	AddNode(&treeTest, 0, 10);
	IsFind(treeTest, 1, &find);
	EXPECT_TRUE(!find);
	DestroyTree(treeTest);
}

TEST(TestIsFind, Find) {

	node_t* treeTest = NULL;
	int indicator = 0;
	AddNode(&treeTest, 0, 10);
	IsFind(treeTest, 10, &indicator);
	EXPECT_TRUE(indicator);
	DestroyTree(treeTest);
}

int main(void) {

	return RUN_ALL_TESTS();
}