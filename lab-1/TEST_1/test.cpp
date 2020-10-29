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
	list=DestroyList(list);
	EXPECT_TRUE(list == NULL);
}

TEST(CheckLength, Length) {
	char* str = (char*)malloc(sizeof(char));
	str = "vnkfvn.";
	int len = 0;
	len = Length(str);
	EXPECT_TRUE(len == 8);
}

TEST(TestCopyStr, CopyStr) {
	char* from = (char*)malloc(sizeof(char));
	char* to = (char*)malloc(sizeof(char));
	int a;
	from = "vnkfvn.";
	to = CopyStr(from);
	a = strcmp(to, from);
	EXPECT_TRUE(a==0);
}

TEST(TestAddToList, AddToList) {
	list_t* list = CreateList();
	char* str = "cck flk";
	int a;
	AddToList(list, "cck flk");
	a = strcmp(str, list->head->data);
	EXPECT_TRUE(a == 0);
	EXPECT_TRUE(list->head->next == NULL);
}

TEST(TestAddToListNULL, AddToList) {
	list_t* list = CreateList();
	char* str = "";
	int a;
	AddToList(list, "");
	a = strcmp(str, list->head->data);
	EXPECT_TRUE(a == 0);
	EXPECT_TRUE(list->head->next == NULL);
}

TEST(TestTwoSortList, SortList) {
	list_t* list = CreateList();
	char* str1 = "cck flk";
	char* str2 = "-4u4";
	AddToList(list, "cck flk");
	AddToList(list, "-4u4");
	int a, b;
	list = SortList(list);
	a= strcmp(str2, list->head->data);
	b= strcmp(str1, list->head->next->data);
	EXPECT_TRUE(a == 0);
	EXPECT_TRUE(b == 0);
}

TEST(TestSortedList, SortList) {
	list_t* list = CreateList();
	AddToList(list, "-4u4");
	AddToList(list, "cck flk");
	char* str1 = "cck flk";
	char* str2 = "-4u4";
	int a, b;
	list = SortList(list);
	a = strcmp(str2, list->head->data);
	b = strcmp(str1, list->head->next->data);
	EXPECT_TRUE(a == 0);
	EXPECT_TRUE(b == 0);
}
