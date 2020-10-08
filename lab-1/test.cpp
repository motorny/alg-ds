#include "pch.h"
#include "C:\Users\79523\source\repos\ALG1\ALG1\listfuncs.c"

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

TEST(Search, NumberOfFoundedElements) {
	LIST* list = InitList();
	AddToList(list, 1, 10, 2020, -10);
	AddToList(list, 2, 10, 2020, -8);
	AddToList(list, 3, 10, 2020, -8);

	int out1, out2, out3;

	out1 = Search(list, -12);
	out2 = Search(list, -10);
	out3 = Search(list, -8);

	EXPECT_EQ(out1, 0);
	EXPECT_EQ(out2, 1);
	EXPECT_EQ(out3, 2);

	FreeList(list);
}