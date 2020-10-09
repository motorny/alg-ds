#include "pch.h"

extern "C" {
#include "../unrolledlinkedlist/unrolledlinkedlist.h"
}

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(CreateList, Create_ReturnValidValue) {
	ullist_t* list = CreateList();
	ASSERT_NE(list, nullptr);
	ASSERT_NE(list->head, nullptr);
	ASSERT_EQ(list->head->numElem, 0);
	free(list->head);
	free(list);
} 

TEST(DeleteList, Delete_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 3, { 1, 20, 2 }, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL) {
		*(list->head->next) = { 2, { 10, 20 }, NULL };
		list->head->next->next = (node_t*)malloc(sizeof(node_t));
		if (list->head->next->next != NULL)
			*(list->head->next->next) = { 1, { 15 }, NULL };
	}

	ASSERT_EQ(DeleteList(list), TRUE);
}
TEST(DeleteList, DeleteEmptyList_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 0, { }, NULL };

	ASSERT_EQ(DeleteList(list), TRUE);
}


TEST(AddElemToList, AddToEmptyList_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 0, { }, NULL };
	ASSERT_EQ(AddElemToList(list, 0, 1), TRUE);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->numElem, 1);
	DeleteList(list);
}
TEST(AddElemToList, AddToEmptyEnoughNode_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 3, { 1, 2, 4 }, NULL };

	ASSERT_EQ(AddElemToList(list, 2, 3), TRUE);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 2);
	ASSERT_EQ(list->head->arr[2], 3);
	ASSERT_EQ(list->head->arr[3], 4);
	ASSERT_EQ(list->head->numElem, 4);

	DeleteList(list);
}
TEST(AddElemToList, AddToFullNodeElemGetsIntoOldNode_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 4, 5, 6 }, NULL };

	ASSERT_EQ(AddElemToList(list, 2, 3), TRUE);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 2);
	ASSERT_EQ(list->head->arr[2], 3);
	ASSERT_EQ(list->head->arr[3], 4);
	ASSERT_NE(list->head->next, nullptr);
	ASSERT_EQ(list->head->next->arr[0], 5);
	ASSERT_EQ(list->head->next->arr[1], 6);
	ASSERT_EQ(list->head->numElem, 4);
	ASSERT_EQ(list->head->next->numElem, 2);

	DeleteList(list);
}
TEST(AddElemToList, AddToFullNodeElemGetsIntoNewNode_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 6 }, NULL };

	ASSERT_EQ(AddElemToList(list, 4, 5), TRUE);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 2);
	ASSERT_EQ(list->head->arr[2], 3);
	ASSERT_NE(list->head->next, nullptr);
	ASSERT_EQ(list->head->next->arr[0], 4);
	ASSERT_EQ(list->head->next->arr[1], 5);
	ASSERT_EQ(list->head->next->arr[2], 6);
	ASSERT_EQ(list->head->numElem, 3);
	ASSERT_EQ(list->head->next->numElem, 3);

	DeleteList(list);
}
TEST(AddElemToList, ElemToInsertAfterIsNotInList_ReturnINVALID_INPUT_DATA) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5 }, NULL };

	ASSERT_EQ(AddElemToList(list, 7, 6), INVALID_INPUT_DATA);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 2);
	ASSERT_EQ(list->head->arr[2], 3);
	ASSERT_EQ(list->head->arr[3], 4);
	ASSERT_EQ(list->head->arr[4], 5);
	ASSERT_EQ(list->head->numElem, 5);
	ASSERT_EQ(list->head->next, nullptr);

	DeleteList(list);
}

TEST(FindNumOfElemInListByKey, ElemIsInList_ReturnValidValue) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5}, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL) 
		*(list->head->next) = { 4, { 10, 20, 30, 4 }, NULL };

	ASSERT_EQ(FindNumOfElemInListByKey(list, 30), 8);

	DeleteList(list);
}
TEST(FindNumOfElemInListByKey, ElemIsNotInList_ReturnELEM_IS_NOT_IN_THE_LIST) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5}, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL) 
		*(list->head->next) = { 4, { 6, 7, 8, 9 }, NULL };

	ASSERT_EQ(FindNumOfElemInListByKey(list, 10), ELEM_IS_NOT_IN_THE_LIST);

	DeleteList(list);
}
TEST(FindNumOfElemInListByKey, FindInEmptyList_ReturnELEM_IS_NOT_IN_THE_LIST) {
	ullist_t* list = CreateList();
	*(list->head) = { 0, { }, NULL };

	ASSERT_EQ(FindNumOfElemInListByKey(list, 30), ELEM_IS_NOT_IN_THE_LIST);

	DeleteList(list);
}


TEST(FindElemInListByNum, NumIsInList_ReturnValidValue) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5}, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL)
		*(list->head->next) = { 4, { 10, 20, 30, 40 }, NULL };

	int* elem = FindElemInListByNum(list, 7);
	ASSERT_NE(elem, nullptr);
    ASSERT_EQ(*elem, 20);

	DeleteList(list);
}
TEST(FindElemInListByNum, NumIsNotInList_ReturnNULL) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5}, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL) 
		*(list->head->next) = { 4, { 10, 20, 30, 40 }, NULL };

	ASSERT_EQ(FindElemInListByNum(list, 12), nullptr);

	DeleteList(list);
}
TEST(FindElemInListByNum, EmptyList_ReturnNULL) {
	ullist_t* list = CreateList();
	*(list->head) = { 0, { }, NULL };

	ASSERT_EQ(FindElemInListByNum(list, 3), nullptr);

	DeleteList(list);
}

TEST(DeleteElemFromListByNum, InvalidNum_ReturnINVALID_INPUT_DATA) {
	ullist_t* list = CreateList();
	*(list->head) = { 2, { 1, 2 }, NULL };

	ASSERT_EQ(DeleteElemFromListByNum(list, 4), INVALID_INPUT_DATA);
	ASSERT_EQ(list->head->numElem, 2);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 2);

	DeleteList(list);
}
TEST(DeleteElemFromListByNum, EmptyList_ReturnLIST_IS_EMPTY) {
	ullist_t* list = CreateList();
	*(list->head) = { 0, { }, NULL };

	ASSERT_EQ(DeleteElemFromListByNum(list, 1), LIST_IS_EMPTY);

	DeleteList(list);
}
TEST(DeleteElemFromListByNum, FirstAndOnly_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 1, { 1 }, NULL };

	ASSERT_EQ(DeleteElemFromListByNum(list, 1), TRUE);
	ASSERT_EQ(list->head->numElem, 0);
	ASSERT_EQ(list->head->next, nullptr);

	DeleteList(list);
}
TEST(DeleteElemFromListByNum, FullEnoughNode_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 4, { 1, 2, 20, 3}, NULL };

	ASSERT_EQ(DeleteElemFromListByNum(list, 3), TRUE);
	ASSERT_EQ(list->head->numElem, 3);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 2);
	ASSERT_EQ(list->head->arr[2], 3);
	ASSERT_EQ(list->head->next, nullptr);

	DeleteList(list);
}
TEST(DeleteElemFromListByNum, HalfEmptyNodeNextFullEnough_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 3, { 1, 20, 2 }, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL)
		*(list->head->next) = { 4, { 10, 20, 30, 40 }, NULL };

	ASSERT_EQ(DeleteElemFromListByNum(list, 2), TRUE);
	ASSERT_EQ(list->head->numElem, 3);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 2);
	ASSERT_EQ(list->head->arr[2], 10);
	ASSERT_EQ(list->head->next->numElem, 3);
	ASSERT_EQ(list->head->next->arr[0], 20);
	ASSERT_EQ(list->head->next->arr[1], 30);
	ASSERT_EQ(list->head->next->arr[2], 40);
	ASSERT_EQ(list->head->next->next, nullptr);

	DeleteList(list);
}
TEST(DeleteElemFromListByNum, HalfEmptyNodeNextHalfEmpty_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 3, { 1, 20, 2 }, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL) {
		*(list->head->next) = { 2, { 10, 20 }, NULL };
		list->head->next->next = (node_t*)malloc(sizeof(node_t));
		if (list->head->next->next != NULL)
			*(list->head->next->next) = { 1, { 15 }, NULL };
	}

	ASSERT_EQ(DeleteElemFromListByNum(list, 2), TRUE);
	ASSERT_EQ(list->head->numElem, 4);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 2);
	ASSERT_EQ(list->head->arr[2], 10);
	ASSERT_EQ(list->head->arr[3], 20);
	ASSERT_EQ(list->head->next->numElem, 1);
	ASSERT_NE(list->head->next, nullptr);
	ASSERT_EQ(list->head->next->arr[0], 15);
	ASSERT_EQ(list->head->next->next, nullptr);

	DeleteList(list);
}
TEST(DeleteElemFromListByNum, HalfEmptyLastNode_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 2, { 1, 2 }, NULL };

	ASSERT_EQ(DeleteElemFromListByNum(list, 2), TRUE);
	ASSERT_EQ(list->head->numElem, 1);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->next, nullptr);

	DeleteList(list);
}
TEST(DeleteElemFromListByNum, LastElemInLastNode_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 3, { 1, 20, 2 }, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL) {
		*(list->head->next) = { 2, { 10, 20 }, NULL };
		list->head->next->next = (node_t*)malloc(sizeof(node_t));
		if (list->head->next->next != NULL) 
			*(list->head->next->next) = { 1, { 15 }, NULL };
	}

	ASSERT_EQ(DeleteElemFromListByNum(list, 6), TRUE);
	ASSERT_EQ(list->head->numElem, 3);
	ASSERT_EQ(list->head->arr[0], 1);
	ASSERT_EQ(list->head->arr[1], 20);
	ASSERT_EQ(list->head->arr[2], 2);
	ASSERT_EQ(list->head->next->numElem, 2);
	ASSERT_EQ(list->head->next->arr[0], 10);
	ASSERT_EQ(list->head->next->arr[1], 20);
	ASSERT_EQ(list->head->next->next, nullptr);

	DeleteList(list);
}

TEST(CountNumOfElements, EmptyList_ReturnZero) {
	ullist_t* list = CreateList();
	*(list->head) = { 0, { }, NULL };

	ASSERT_EQ(CountNumOfElements(list), 0);

	DeleteList(list);
}
TEST(CountNumOfElements, Count_ReturnPositiveNumber) {
	ullist_t* list = CreateList();
	*(list->head) = { 3, { 1, 20, 2 }, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL) {
		*(list->head->next) = { 2, { 10, 20 }, NULL };
		list->head->next->next = (node_t*)malloc(sizeof(node_t));
		if (list->head->next->next != NULL)
			*(list->head->next->next) = { 1, { 15 }, NULL };
	}

	ASSERT_EQ(CountNumOfElements(list), 6);

	DeleteList(list);
}


TEST(CreateIterator, CreateIter_ReturnValidPointer) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5 }, NULL };
	ullIter_t* iter = CreateIterator(list);

	ASSERT_NE(iter, nullptr);
	ASSERT_EQ(iter->list, list);
	ASSERT_EQ(iter->node, list->head);
	ASSERT_EQ(iter->numOfCurElemInNode, 0);
	ASSERT_EQ(iter->ptrOnCurElem, &(list->head->arr[0]));

	DeleteList(list);
}

TEST(GetFromIterator, GetFromIterFirstInList_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5 }, NULL };
	ullIter_t* iter = CreateIterator(list);
	int elem;

	ASSERT_EQ(GetFromIterator(iter, &elem), TRUE);
	ASSERT_EQ(elem, 1);

	DeleteList(list);
}
TEST(GetFromIterator, GetFromIter_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5 }, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL)
		*(list->head->next) = { 3, { 10, 20, 30 }, NULL };
	ullIter_t* iter = CreateIterator(list);
	int elem;
	iter->node = list->head->next;
	iter->numOfCurElemInNode = 1;
	if (list->head->next != NULL)
		iter->ptrOnCurElem = &(list->head->next->arr[1]);

	ASSERT_EQ(GetFromIterator(iter, &elem), TRUE);
	ASSERT_EQ(elem, 20);

	DeleteList(list);
}

TEST(NextInIterator, NextInIterInsideNode_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5 }, NULL };
	ullIter_t* iter = CreateIterator(list);

	iter->numOfCurElemInNode = 2;
	iter->ptrOnCurElem = &(list->head->arr[2]);

	ASSERT_EQ(NextInIterator(iter), TRUE);
	ASSERT_EQ(*(iter->ptrOnCurElem), 4);

	DeleteList(list);
}

TEST(NextInIterator, NextInIterOutOfNode_ReturnTrue) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5 }, NULL };
	list->head->next = (node_t*)malloc(sizeof(node_t));
	if (list->head->next != NULL)
		*(list->head->next) = { 3, { 10, 20, 30 }, NULL };
	ullIter_t* iter = CreateIterator(list);

	iter->numOfCurElemInNode = 4;
	iter->ptrOnCurElem = &(list->head->arr[4]);

	ASSERT_EQ(NextInIterator(iter), TRUE);
	ASSERT_EQ(iter->node, list->head->next);
	ASSERT_EQ(iter->numOfCurElemInNode, 0);
	ASSERT_EQ(*(iter->ptrOnCurElem), 10);

	DeleteList(list);
}
TEST(NextInIterator, EndOfList_ReturnEND_OF_THE_LIST) {
	ullist_t* list = CreateList();
	*(list->head) = { 5, { 1, 2, 3, 4, 5 }, NULL };
	ullIter_t* iter = CreateIterator(list);

	iter->numOfCurElemInNode = 4;
	iter->ptrOnCurElem = &(list->head->arr[4]);

	ASSERT_EQ(NextInIterator(iter), END_OF_THE_LIST);

	DeleteList(list);
}