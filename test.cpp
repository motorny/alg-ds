#include "pch.h"
#include "C:\\Users\Lenovo\source\repos\lib_2020\lib_2020.c"

LIST_T* InitSplittedListFirstHalf() {
	LIST_T * List, *go, *tmp;
	List = (LIST_T*)malloc(sizeof(LIST_T));
	go = List;
	go->prev = NULL;
	go->str = "First test message";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "Second test message";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "Third test message";
	go->next = NULL;
	return List;
}
LIST_T* InitSplittedListSecondHalf() {
	LIST_T * List, *go, *tmp;
	List = (LIST_T*)malloc(sizeof(LIST_T));
	go = List;
	go->prev = NULL;
	go->str = "k";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "Afdio";
	go->next = NULL;
	return List;
}
LIST_T* InitSplittedListSecondHalfSorted() {
	LIST_T * List, *go, *tmp;
	List = (LIST_T*)malloc(sizeof(LIST_T));
	go = List;
	go->prev = NULL;
	go->str = "Afdio";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "k";
	go->next = NULL;
	return List;
}
LIST_T* InitSortedList()
{
	LIST_T * List, *go, *tmp;
	List = (LIST_T*)malloc(sizeof(LIST_T));
	go = List;
	go->prev = NULL;
	go->str = "Afdio";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "First test message";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "Second test message";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "Third test message";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "k";
	go->next = NULL;
	return List;
}
LIST_T* InitNotSortedList()
{
	LIST_T * List, *go, *tmp;
	List = (LIST_T*)malloc(sizeof(LIST_T));
	go = List;
	go->prev = NULL;
	go->str = "First test message";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "Second test message";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "Third test message";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "k";
	go->next = (LIST_T*)malloc(sizeof(LIST_T));
	tmp = go;
	go = go->next;
	go->prev = tmp;
	go->str = "Afdio";
	go->next = NULL;
	return List;
}
TEST(Merge_BothNULLLists_ReturnNULL)
{
	LIST_T *ListToMerge, *ListToCheck, *List1, *List2;
	ListToCheck = NULL;
	List1 = NULL;
	List2 = NULL;
	ListToMerge = Merge(List1, List2);
	EXPECT_EQ(ListToMerge, ListToCheck);
}
TEST(Merge_NULLAndNotNULLLists_ReturnValList)
{
	LIST_T *ListToMerge, *List1, *List2;
	List1 = InitSplittedListFirstHalf();
	List2 = NULL;
	ListToMerge = Merge(List1, List2);
	EXPECT_EQ(ListToMerge, List1);
}
TEST(Merge_NotNULLLists_ReturnValList) 
{
	LIST_T *ListToMerge, *ListToCheck, *List1, *List2;
	int ListLength = 5;
	ListToCheck = InitSortedList();
	List1 = InitSplittedListFirstHalf();
	List2 = InitSplittedListSecondHalfSorted();
	ListToMerge=Merge(List1,List2);
	for (int i=0;i<ListLength-1;i++) 
	{
		EXPECT_EQ(0, strcmp((*ListToMerge).str, (*ListToCheck).str));
		ListToMerge->next->prev = ListToMerge;
		ListToMerge = ListToMerge->next;
		ListToCheck->next->prev = ListToCheck;
		ListToCheck = ListToCheck->next;
	}
	EXPECT_EQ(0, strcmp((*ListToMerge).str, (*ListToCheck).str));
}
TEST(Split_NULLList_ReturnNULLs) 
{
	LIST_T *ListToSplit, *List1, *List2;
	ListToSplit = NULL;
	Split(ListToSplit, &List1, &List2);
	EXPECT_EQ(ListToSplit,List1);
	EXPECT_EQ(ListToSplit, List1);
}
TEST(Split_NotNULLList_ReturnValValue)
{
	LIST_T *ListToSplit,*List1ToCheck, *List2ToCheck, *List1, *List2;
	int List1Length = 3, List2Length = 2;
	ListToSplit = InitNotSortedList();
	List1ToCheck = InitSplittedListFirstHalf();
	List2ToCheck = InitSplittedListSecondHalf();
	Split(ListToSplit, &List1, &List2);
	for (int i = 0; i < List1Length - 1; i++)
	{
		EXPECT_EQ(0, strcmp((*List1).str, (*List1ToCheck).str));
		List1->next->prev = List1;
		List1 = List1->next;
		List1ToCheck->next->prev = List1ToCheck;
		List1ToCheck = List1ToCheck->next;
	}
	EXPECT_EQ(0, strcmp((*List1).str, (*List1ToCheck).str));
	for (int i = 0; i < List2Length - 1; i++)
	{
		EXPECT_EQ(0, strcmp((*List2).str, (*List2ToCheck).str));
		List2->next->prev = List2;
		List2 = List2->next;
		List2ToCheck->next->prev = List2ToCheck;
		List2ToCheck = List2ToCheck->next;
	}
	EXPECT_EQ(0, strcmp((*List2).str, (*List2ToCheck).str));
}
TEST(Sort_SortedList_ListRemainSorted)
{
	LIST_T *List1, *List2;
	int ListLength = 5;
	List1 = InitSortedList();
	List2 = InitSortedList();
	Sort(&List1);
	for (int i = 0; i < ListLength - 1; i++)
	{
		EXPECT_EQ(0, strcmp((*List1).str, (*List2).str));
		List1->next->prev = List1;
		List1 = List1->next;
		List2->next->prev = List2;
		List2 = List2->next;
	}
	EXPECT_EQ(0, strcmp((*List1).str, (*List2).str));
}
TEST(Sort_NotSortedList_ListBecameSorted)
{
	LIST_T *List1,*List2;
	int ListLength = 5;
	List1 = InitNotSortedList(); 
	List2 = InitSortedList();
	Sort(&List1);
	for (int i = 0; i < ListLength-1; i++)
	{
		EXPECT_EQ(0,strcmp((*List1).str,(*List2).str));
		List1->next->prev = List1;
		List1 = List1->next;
		List2->next->prev = List2;
		List2 = List2->next;
	}
	EXPECT_EQ(0, strcmp((*List1).str, (*List2).str));
}
TEST(Sort_NULLList_ListRemainNULL)
{
	LIST_T *List=NULL;
	Sort(&List);
	EXPECT_EQ(NULL,List);
}

