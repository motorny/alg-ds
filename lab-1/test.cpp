#include "pch.h"
#include "../LabALinkedList/LinkedList.c"

LIST* initFirstList()
{
	LIST* head = (LIST*)malloc(sizeof(LIST));
	head->data = 1;
	head->next = (LIST*)malloc(sizeof(LIST));
	head->next->data = 2;
	head->next->next = (LIST*)malloc(sizeof(LIST));
	head->next->next->data = 3;
	head->next->next->next = NULL;
	return head;
}

LIST* initSecondList()
{
	LIST* head = (LIST*)malloc(sizeof(LIST));
	head->data = 1;
	head->next = (LIST*)malloc(sizeof(LIST));
	head->next->data = 2;
	head->next->next = (LIST*)malloc(sizeof(LIST));
	head->next->next->data = 4;
	head->next->next->next = (LIST*)malloc(sizeof(LIST));
	head->next->next->next->data = 6;
	head->next->next->next->next = NULL;
	return head;
}

TEST(insertItemInList, insertItem_ValidList)
{
	LIST* head = initList();
	head = insertInList(head, 2);
	head = insertInList(head, 3);
	head = insertInList(head, 1);
	ASSERT_EQ(1, head->data);
	ASSERT_EQ(2, head->next->data);
	ASSERT_EQ(3, head->next->next->data);
	delList(head);
}

TEST(insertItemInList, insertNULL)
{
	LIST* head = initList();
	head = insertInList(head, NULL);
	ASSERT_EQ(NULL, head->data);
	delList(head);
}

TEST(insertItemInList, insertOrderedItems_ValidList)
{
	LIST* head = initList();
	head = insertInList(head, 1);
	head = insertInList(head, 2);
	head = insertInList(head, 3);
	ASSERT_EQ(1, head->data);
	ASSERT_EQ(2, head->next->data);
	ASSERT_EQ(3, head->next->next->data);
	delList(head);
}

TEST(deleteItem, deleteItem_ValidList)
{
	LIST* head = initFirstList();
	head = deleteItem(head, 2);
	ASSERT_EQ(1, head->data);
	ASSERT_EQ(3, head->next->data);
	delList(head);
}
TEST(deleteItem, deleteSingleItem_ReturnNULL)
{
	LIST* head = initList();
	head = insertInList(head, 1);
	head = deleteItem(head, 1);
	ASSERT_EQ(NULL, head);
}

TEST(searchItem, searchItemInEmptyLIST_ReturnFALSE)
{
	LIST* head = initList();
	Bool searchItem = searchItemInList(head, 5);
	ASSERT_EQ(FALSE, searchItem);
}

TEST(searchItem, searchItemWhichIs_ReturnTRUE)
{
	LIST* head = initFirstList();
	Bool searchItem = searchItemInList(head, 3);
	ASSERT_EQ(TRUE, searchItem);
	delList(head);
}

TEST(searchItem, searchItemWhichIsNot_ReturnFALSE)
{
	LIST* head = initFirstList();
	Bool searchItem = searchItemInList(head, 4);
	ASSERT_EQ(FALSE, searchItem);
	delList(head);
}

TEST(unionOfSets, unionOfEmptySets_ReturnNULL)
{
	LIST* head1 = initList(),
		* head2 = initList(),
		* un = unionOfSets(head1, head2);
	ASSERT_EQ(NULL, un);
}

TEST(unionOfSets, UnionOfSets_ValidList)
{
	LIST* head1 = initFirstList(),
		* head2 = initSecondList(),
		* un;

	un = unionOfSets(head1, head2);
	ASSERT_EQ(1, un->data);
	ASSERT_EQ(2, un->next->data);
	ASSERT_EQ(3, un->next->next->data);
	ASSERT_EQ(4, un->next->next->next->data);
	ASSERT_EQ(6, un->next->next->next->next->data);
	delList(head1);
	delList(head2);
	delList(un);
}

TEST(unionOfSets, UnionOfEmptyAndNonEmptySet_ValidList)
{
	LIST* head1 = initList(),
		* head2 = initFirstList(),
		* un;

	un = unionOfSets(head1, head2);
	ASSERT_EQ(1, un->data);
	ASSERT_EQ(2, un->next->data);
	ASSERT_EQ(3, un->next->next->data);
	delList(head1);
	delList(head2);
	delList(un);
}

TEST(intersectionSets, intersectionEmptySets_ReturnNULL)
{
	LIST* head1 = initList(),
		* head2 = initList(),
		* inter = intersection(head1, head2);
	ASSERT_EQ(NULL, inter);
}

TEST(intersectionSets, intersectionSets_ValidList)
{
	LIST* head1 = initFirstList(),
		* head2 = initSecondList(),
		* inter;

	inter = intersection(head1, head2);

	ASSERT_EQ(1, inter->data);
	ASSERT_EQ(2, inter->next->data);

	delList(head1);
	delList(head2);
	delList(inter);
}

TEST(intersectionSets, intersectionOfEmptyAndNonEmptySet_ReturnNULL)
{
	LIST* head1 = initList(),
		* head2 = initFirstList(),
		* inter;

	inter = intersection(head1, head2);
	ASSERT_EQ(NULL, inter);

	delList(head1);
	delList(head2);
	delList(inter);
}