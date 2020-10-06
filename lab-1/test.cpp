#include "pch.h"
#include "list.c"
#include "sort.c"
#include "list.h"
#include "sort.h"

TEST(addNodeTest, addingFirstNode) {
	List* pList = createList();

	addNode(pList, "a", 1);

	EXPECT_STREQ(pList->head->cont, "a");

	destroyList(pList);
}

TEST(addNodeTest, addingSecondNode) {
	List* pList = createList();

	addNode(pList, "a", 1);
	addNode(pList, "b", 1);

	EXPECT_STREQ(pList->head->next->cont, "b");
	EXPECT_STREQ(pList->tail->cont, "b");
	EXPECT_STREQ(pList->tail->prev->cont, "a");

	destroyList(pList);
}

TEST(addNodeTest, addingThirdNode) {
	List* pList = createList();

	addNode(pList, "a", 1);
	addNode(pList, "b", 1);
	addNode(pList, "c", 1);

	EXPECT_STREQ(pList->head->next->next->cont, "c");
	EXPECT_STREQ(pList->tail->cont, "c");
	EXPECT_STREQ(pList->tail->prev->cont, "b");

	destroyList(pList);
}

TEST(sortInsertTest, emptyList) {
	List* pList = createList();

	sortInsert(pList);

	EXPECT_TRUE(pList->head == NULL);
	EXPECT_TRUE(pList->tail == NULL);

	destroyList(pList);
}

TEST(sortInsertTest, sortedList) {
	List* pList = createList();

	addNode(pList, "a", 1);
	addNode(pList, "b", 1);
	addNode(pList, "c", 1);

	sortInsert(pList);

	EXPECT_STREQ(pList->head->cont, "a");
	EXPECT_STREQ(pList->head->next->cont, "b");
	EXPECT_STREQ(pList->tail->cont, "c");

	destroyList(pList);
}

TEST(sortInsertTest, randomList) {
	List* pList = createList();

	addNode(pList, "a", 1);
	addNode(pList, "c", 1);
	addNode(pList, "b", 1);

	sortInsert(pList);

	EXPECT_STREQ(pList->head->cont, "a");
	EXPECT_STREQ(pList->head->next->cont, "b");
	EXPECT_STREQ(pList->tail->cont, "c");

	destroyList(pList);
}
TEST(sortMergeTest, emptyListMerge) {
	List* pList = createList();

	sortMerge(pList);

	EXPECT_TRUE(pList->head == NULL);
	EXPECT_TRUE(pList->tail == NULL);

	destroyList(pList);
}

TEST(sortMergeTest, sortedListMerge) {
	List* pList = createList();

	addNode(pList, "a", 1);
	addNode(pList, "b", 1);
	addNode(pList, "c", 1);

	sortMerge(pList);

	EXPECT_STREQ(pList->head->cont, "a");
	EXPECT_STREQ(pList->head->next->cont, "b");
	EXPECT_STREQ(pList->tail->cont, "c");

	destroyList(pList);
}

TEST(sortMergeTest, randomListMerge) {
	List* pList = createList();

	addNode(pList, "a", 1);
	addNode(pList, "c", 1);
	addNode(pList, "b", 1);

	sortMerge(pList);

	EXPECT_STREQ(pList->head->cont, "a");
	EXPECT_STREQ(pList->head->next->cont, "b");
	EXPECT_STREQ(pList->tail->cont, "c");

	destroyList(pList);
}