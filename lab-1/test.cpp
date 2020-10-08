#include "pch.h"
#include "C:\Users\79523\source\repos\ALG1\ALG1\listfuncs.c"

LIST* InitTestList() {
	LIST* list = (LIST*)malloc(sizeof(LIST));
	list->first = (NODE*)malloc(sizeof(NODE));
	list->first->day = 1;
	list->first->month = 1;
	list->first->year = 2020;
	list->first->temperature = -12;
	list->first->next = (NODE*)malloc(sizeof(NODE));
	list->first->next->day = 2;
	list->first->next->month = 1;
	list->first->next->year = 2020;
	list->first->next->temperature = -10;
	list->first->next->next = NULL;

	return list;
}

TEST(InitList, InitListValid) {
	LIST* list = InitList();
	ASSERT_TRUE(list != NULL);

	FreeList(list);
}

TEST(AddToList, AddNewElement) {
	LIST* list = InitList();
	AddToList(list, 2, 10, 2019, -14);
	EXPECT_EQ(list->first->day, 2);
	EXPECT_EQ(list->first->month, 10);
	EXPECT_EQ(list->first->year, 2019);
	EXPECT_EQ(list->first->temperature, -14);

	FreeList(list);
}

TEST(AddToList, SortAddedElements) {
	LIST* list = InitList();
	AddToList(list, 4, 10, 2019, -14);
	AddToList(list, 5, 10, 2019, -16);
	AddToList(list, 2, 11, 2020, -14);
	AddToList(list, 3, 10, 2020, -14);
	AddToList(list, 3, 11, 2020, -14);

	EXPECT_TRUE(list->first->temperature < list->first->next->temperature);
	EXPECT_TRUE(list->first->next->year < list->first->next->next->year);
	EXPECT_TRUE(list->first->next->next->month < list->first->next->next->next->month);
	EXPECT_TRUE(list->first->next->next->next->day < list->first->next->next->next->next->day);

	FreeList(list);
}

TEST(Search, ElementFound) {
	LIST* list = InitTestList();
	int out;
	out = Search(list, -12);
	EXPECT_EQ(out, 1);

	FreeList(list);
}

TEST(Search, ElementNotFound) {
	LIST* list = InitTestList();
	int out;
	out = Search(list, -11);
	EXPECT_EQ(out, 0);

	FreeList(list);
}
