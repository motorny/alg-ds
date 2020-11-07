#include "pch.h"

extern "C" {
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
	list = DestroyList(list);
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
	int n;
	from = "vnkfvn.";
	to = CopyStr(from);
	n = strcmp(to, from);
	EXPECT_TRUE(n == 0);
}

TEST(TestAddToList, AddToList) {
	list_t* list = CreateList();
	char* arr = (char*)malloc(sizeof(char));
	int n;
	AddToList(list, "cck flk");
	arr = "cck flk";
	n = strcmp(list->head->data, arr);
	EXPECT_TRUE(n == 0);
	EXPECT_TRUE(list->head->next == NULL);
}

TEST(TestAddToListNULL, AddToList) {
	list_t* list = CreateList();
	char* arr = (char*)malloc(sizeof(char));
	int n;
	AddToList(list, "");
	arr = "";
	n = strcmp(arr, list->head->data);
	EXPECT_TRUE(n == 0);
	EXPECT_TRUE(list->head->next == NULL);
}

TEST(TestTwoSortList, SortList) {
	list_t* list = CreateList();
	char* arr1 = (char*)malloc(sizeof(char)), * arr2 = (char*)malloc(sizeof(char));
	int n1, n2;
	AddToList(list, "cck flk");
	AddToList(list, "-4u4");
	arr1 = "cck flk";
	arr2 = "-4u4";
	list = SortList(list);
	n1 = strcmp(list->head->data, arr2);
	n2 = strcmp(list->head->next->data, arr1);
	EXPECT_TRUE(n1 == 0);
	EXPECT_TRUE(n2 == 0);
}

TEST(TestSortedList, SortList) {
	list_t* list = CreateList();
	char* arr1 = (char*)malloc(sizeof(char)), * arr2 = (char*)malloc(sizeof(char));
	int n1, n2;
	AddToList(list, "-4u4");
	AddToList(list, "cck flk");
	arr1 = "cck flk";
	arr2 = "-4u4";
	list = SortList(list);
	n1 = strcmp(list->head->data, arr2);
	n2 = strcmp(list->head->next->data, arr1);
	EXPECT_TRUE(n1 == 0);
	EXPECT_TRUE(n2 == 0);
}
