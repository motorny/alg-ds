#include "pch.h"
extern "C" {
	#include "./ULL.c"
	#include "ULL.h"
}

ull_t* CreateHeadTest() {
	ull_t* head;
	head = (ull_t*)malloc(sizeof(ull_t));
	if (head) {
		head->arrSize = 0;
		head->nextBlock = NULL;
		return head;
	}
	else {
		return NULL;
	}
}

TEST(GetCurrentNodeTest, TestOne) {
	ull_t* head = CreateHeadTest();
	ASSERT_EQ(head, GetCurrentNode(head));
}
TEST(GetCurrentNodeTest, TestSecond) {
	ull_t* head = CreateHeadTest();
	int i;
	for (i = 0; i < SIZE + 1; i++) {
		AddElement(head, i);
	}
	ASSERT_EQ(head->nextBlock, GetCurrentNode(head));
}
TEST(AddElementTest, TestOne) {
	ull_t* head = CreateHeadTest();
	AddElement(head, 2);
	ASSERT_EQ(2, head->arr[0]);
}
TEST(AddElementTest, TestSecond) {
	ull_t* head = CreateHeadTest();
	int i;
	for (i = 1; i <= SIZE + 1; i++) {
		AddElement(head, i);
	}
	ASSERT_EQ(5, head->nextBlock->arr[0]);
}
TEST(GetElementNumTest, TestOne) {
	ull_t* head = CreateHeadTest();
	AddElement(head, 2);
	ASSERT_EQ(2, GetElementNum(head, 1));
}
TEST(GetElementNumTest, TestSecond) {
	ull_t* head = CreateHeadTest();
	AddElement(head, 2);
	ASSERT_EQ(ERROR, GetElementNum(head, 2));
}
TEST(GetNumKeyTest, TestOne) {
	ull_t* head = CreateHeadTest();
	AddElement(head, 2);
	ASSERT_EQ(1, GetNumKey(head, 2));
}
TEST(GetNumKeyTest, TestSecond) {
	ull_t* head = CreateHeadTest();
	AddElement(head, 1);
	ASSERT_EQ(ERROR, GetNumKey(head, 2));
}
TEST(GetNextElementKeyTest, TestOne) {
	ull_t* head = CreateHeadTest();
	int i;
	for (i = 1; i < 3; i++) {
		AddElement(head, i);
	}
	ASSERT_EQ(2, GetNextElementKey(head, 1));
}
TEST(GetNextElementKeyTest, TestSecond) {
	ull_t* head = CreateHeadTest();
	int i;
	for (i = 1; i < 3; i++) {
		AddElement(head, i);
	}
	ASSERT_EQ(ERROR, GetNextElementKey(head, 3));
}
TEST(GetNextElementKeyTest, TestThird) {
	ull_t* head = CreateHeadTest();
	int i;
	for (i = 1; i < 3; i++) {
		AddElement(head, i);
	}
	ASSERT_EQ(ERROR, GetNextElementKey(head, 10));
}
TEST(GetCountElementTest, TestOne) {
	ull_t* head = CreateHeadTest();
	AddElement(head, 2);
	ASSERT_EQ(1, GetCountElements(head));
}
TEST(GetCountElementTest, TestSecond) {
	ull_t* head = CreateHeadTest();
	int i;
	for (i = 0; i < 2 * SIZE + 1; i++) {
		AddElement(head, i);
	}
	ASSERT_EQ(i, GetCountElements(head));
}
TEST(DeleteElementTest, TestOne) {
	ull_t* head = CreateHeadTest();
	AddElement(head, 2);
	DeleteElement(head, 1);
	ASSERT_EQ(0, head->arrSize);
}
TEST(DeleteElementTest, TestSecond) {
	ull_t* head = CreateHeadTest();
	AddElement(head, 2);
	DeleteElement(head, 1);
	ASSERT_EQ(ERROR, GetElementNum(head, 1));
}
TEST(DeleteElementTest, TestThird) {
	ull_t* head = CreateHeadTest();
	int i;
	for (i = 0; i < SIZE + 1; i++) {
		AddElement(head, i + 1);
	}
	DeleteElement(head, i - 1);
	ASSERT_EQ(i, GetNextElementKey(head, i - 2));
}