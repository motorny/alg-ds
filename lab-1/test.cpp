#include "pch.h"
extern"C" {
#include"List.h"
}

TEST(ListCreate_InitializeListPointer, returnPointer) {
	UnrolledList* list = ListCreate();
	ASSERT_TRUE(list != NULL);
	ListDestroy(list);
}

TEST(AddElem_NULLList, returnFAILED_0) {
	UnrolledList* list = NULL;
	ASSERT_EQ(FAILED, AddElem(list, 1));
}

TEST(AddElem_ValidList, returnSUCCESS_1) {
	UnrolledList* list = ListCreate();
	ASSERT_EQ(SUCCESS, AddElem(list, 2));
	ListDestroy(list);
}

TEST(FindElem_IncorrectIndex, returnNULL) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	AddElem(list, 2);
	ASSERT_EQ(NULL, FindElem(list, 5));
	ListDestroy(list);
}

TEST(FindElem_correctIndex, returnPointer) {
	UnrolledList* list = ListCreate();
	int* p = NULL;
	AddElem(list, 1);
	AddElem(list, 2);
	p = FindElem(list, 1);
	ASSERT_TRUE(p != NULL);
	ListDestroy(list);
}

TEST(DeleteElem_IncorrectIndex, returnFAILED_0) {
	UnrolledList* list = ListCreate();
	ASSERT_EQ(FAILED, DeleteElem(list, 9));
	ListDestroy(list);
}

TEST(DeleteElem_correctIndex, returnSUCCES_1) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	AddElem(list, 2);
	AddElem(list, 3);
	ASSERT_EQ(SUCCESS, DeleteElem(list, 1));
	ListDestroy(list);
}
/*
░░░░░░░█▐▓▓░████▄▄▄█▀▄▓▓▓▌█
░░░░░▄█▌▀▄▓▓▄▄▄▄▀▀▀▄▓▓▓▓▓▌█
░░░▄█▀▀▄▓█▓▓▓▓▓▓▓▓▓▓▓▓▀░▓▌█
░░█▀▄▓▓▓███▓▓▓███▓▓▓▄░░▄▓▐█
░█▌▓▓▓▀▀▓▓▓▓███▓▓▓▓▓▓▓▄▀▓▓▐█
▐█▐██▐░▄▓▓▓▓▓▀▄░▀▓▓▓▓▓▓▓▓▓▌█▌
█▌███▓▓▓▓▓▓▓▓▐░░▄▓▓███▓▓▓▄▀▐█
█▐█▓▀░░▀▓▓▓▓▓▓▓▓▓██████▓▓▓▓▐█
▌▓▄▌▀░▀░▐▀█▄▓▓██████████▓▓▓▌█▌
▌▓▓▓▄▄▀▀▓▓▓▀▓▓▓▓▓▓▓▓█▓█▓█▓▓▌█
█▐▓▓▓▓▓▓▄▄▄▓▓▓▓▓▓█▓█▓█▓█▓▓▓▐█
*/

TEST(FindSize_NULLpointer, return0) {
	UnrolledList* list = NULL;
	ASSERT_EQ(0, FindSize(list));
}

TEST(FindSize_StartingList, return1) {
	UnrolledList* list = ListCreate();
	ASSERT_EQ(1, FindSize(list));
	ListDestroy(list);
}

TEST(FindSize_Non_EmptyList, returnPositive) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	AddElem(list, 2);
	AddElem(list, 3);
	ASSERT_EQ(3, FindSize(list));
	ListDestroy(list);
}

TEST(FindNextELem_NULLList, returnNULL) {
	UnrolledList* list = NULL;
	ASSERT_EQ(NULL, FindNextElem(list, 77));
}

TEST(FindNextElem_EmptyList, returnNULL) {
	UnrolledList* list = ListCreate();
	ASSERT_EQ(NULL, FindNextElem(list, 1234));
	ListDestroy(list);
}

TEST(FindNextElem_OneElem, returnNULL) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	ASSERT_EQ(NULL, FindNextElem(list, 2));
	ListDestroy(list);
}

TEST(FindNextElem_ElemNotFound, returnNULL) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	AddElem(list, 2);
	AddElem(list, 3);
	ASSERT_EQ(NULL, FindNextElem(list, 17));
	ListDestroy(list);
}

TEST(FindNextElem_BeginOfList, returnGoodPointer) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	AddElem(list, 2);
	ASSERT_TRUE(FindNextElem(list, 1) != NULL);
	ListDestroy(list);
}

TEST(FindNextElem_MiddleOfList, returnGoodPointer) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	AddElem(list, 2);
	AddElem(list, 3);
	AddElem(list, 4);
	AddElem(list, 5);
	ASSERT_TRUE(FindNextElem(list, 4) != NULL);
	ListDestroy(list);
}

TEST(FindNextElem_EndOfList, returnNULL) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	AddElem(list, 2);
	AddElem(list, 3);
	ASSERT_TRUE(FindNextElem(list, 3) == NULL);
	ListDestroy(list);
}

TEST(FindByKey_NULLLIst, return_minus1) {
	UnrolledList* list = NULL;
	ASSERT_EQ(-1, FindByKey(list, 3));
}

TEST(FindByKey_NumbNotFound, return_minus1) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	ASSERT_EQ(-1, FindByKey(list, 70));
	ListDestroy(list);
}

TEST(FindByKey_NumbFound, returnGoodIndex) {
	UnrolledList* list = ListCreate();
	AddElem(list, 1);
	AddElem(list, 2);
	AddElem(list, 3);
	ASSERT_EQ(1, FindByKey(list, 2));
	ListDestroy(list);
}

TEST(FindByKey_EqualNumbers, returnGoodIndex) {
	UnrolledList* list = ListCreate();
	AddElem(list, 9);
	AddElem(list, 9);
	AddElem(list, 9);
	ASSERT_EQ(0, FindByKey(list, 9));
	ListDestroy(list);
}
