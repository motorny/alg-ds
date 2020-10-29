#include "pch.h"

extern "C"{ 
#include "../Lab_1/Header.h"
}

TEST(TestDestroyElements, DestroyList) {
	list_t* list = CreateList();
	AddToList(list, "cck flk");
	AddToList(list, "-4u4");
	AddToList(list, "42kf ngp0");
	AddToList(list, "42kf deffn gp0");
	AddToList(list, "&3298 328u31/fwef12./,");
	AddToList(list, "u *%");
	AddToList(list, "-_-");
	DestroyList(list);
	EXPECT_TRUE(list == NULL);
}

TEST(CheckLength, Length) {
	char* str = (char*)malloc(sizeof(char));
	str = "vnkfvn.";
	int len = 0;
	len = Length(str);
	EXPECT_TRUE(len == 7);
}

TEST(TestCopyStr, CopyStr) {
	char* from = (char*)malloc(sizeof(char));
	char* to = (char*)malloc(sizeof(char));
	from = "vnkfvn.";
	to = CopyStr(from);
	EXPECT_TRUE(to == from);
}

TEST(TestAddToList, AddToList) {
	list_t* list = CreateList();
	AddToList(list, "cck flk");
	EXPECT_TRUE(list->head->data == "cck flk");
	EXPECT_TRUE(list->head->next == NULL);
}

TEST(TestAddToListNULL, AddToList) {
	list_t* list = CreateList();
	AddToList(list, "");
	EXPECT_TRUE(list->head->data == NULL);
	EXPECT_TRUE(list->head->next == NULL);
}

TEST(TestTwoSortList, SortList) {
	list_t* list = CreateList();
	AddToList(list, "cck flk");
	AddToList(list, "-4u4");
	list = SortList(list);
	EXPECT_TRUE(list->head->data == "-4u4");
	EXPECT_TRUE(list->head->next->data == "cck flk");
}

TEST(TestSortedList, SortList) {
	list_t* list = CreateList();
	AddToList(list, "-4u4");
	AddToList(list, "cck flk");
	list = SortList(list);
	EXPECT_TRUE(list->head->data == "-4u4");
	EXPECT_TRUE(list->head->next->data == "cck flk");
}
