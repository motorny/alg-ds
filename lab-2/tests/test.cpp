#include "pch.h"
#include "..\alg_laba1\func.c"

#define _CRT_SECURE_NO_WARNINGS
#define WORD_LENGTH 10

char examp[][WORD_LENGTH] = { "this ", "is ", "example" };

node_t* InitNode(char* word) {
	node_t* elem = (node_t*)malloc(sizeof(node_t));
	if (elem == NULL)
		return NULL;

	elem->data = word;
	elem->next = NULL;
	return elem;
}

list_t* Init() {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	node_t* el1 = InitNode(examp[0]);
	node_t* el2 = InitNode(examp[1]);
	node_t* el3 = InitNode(examp[2]);
	list->head = el1;
	el1->next = el2;
	el2->next = el3;

	return list;
}

void DeleteList(list_t* list) {
	node_t* todel = list->head;
		
	while (todel->next != NULL) {
		list->head = todel->next;
		free(todel);
		todel = list->head;
	}
	free(list);
}


TEST(FuncTest, LengthOfListTest) {
	list_t* list = Init();
	ASSERT_TRUE(list != NULL);
	int len = LengthOfList(list);

	EXPECT_EQ(len, 16);

  	EXPECT_TRUE(true);

	DeleteList(list);
}

TEST(FuncTest, LengthOfListTestNULL) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->head = NULL;

	int len = LengthOfList(list);

	EXPECT_EQ(len, 0);

	free(list);
}


TEST(FuncTest, ListToArrayTest) {
	list_t* list = Init();
	ASSERT_TRUE(list != NULL);
	char* arr = ListToArray(list);

	EXPECT_STREQ(arr, "this is example");

	DeleteList(list);
}

TEST(FuncTest, ListToArrayTestNull) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->head = NULL;

	char* arr = ListToArray(list);

	EXPECT_TRUE(arr == NULL);

	free(list);
}
