#include "pch.h"
#include "../LabALinkedList/LinkedList.c"

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

TEST(deleteItem, deleteItem_ValidList)
{
	LIST* head = initList();
	head = insertInList(head, 2);
	head = insertInList(head, 3);
	head = insertInList(head, 1);
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
	LIST* head = initList();
	head = insertInList(head, 5);
	head = insertInList(head, 3);
	Bool searchItem = searchItemInList(head, 5);
	ASSERT_EQ(TRUE, searchItem);
	delList(head);
}

TEST(searchItem, searchItemWhichIsNot_ReturnFALSE)
{
	LIST* head = initList();
	head = insertInList(head, 5);
	head = insertInList(head, 3);
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
	LIST* head1 = initList(),
		* head2 = initList(),
		* un;
	head1 = insertInList(head1, 5);
	head1 = insertInList(head1, 3);
	head1 = insertInList(head1, 1);

	head2 = insertInList(head2, 4);
	head2 = insertInList(head2, 2);
	head2 = insertInList(head2, 6);
	head2 = insertInList(head2, 1);

	un = unionOfSets(head1, head2);
	ASSERT_EQ(1, un->data);
	ASSERT_EQ(2, un->next->data);
	ASSERT_EQ(3, un->next->next->data);
	ASSERT_EQ(4, un->next->next->next->data);
	ASSERT_EQ(5, un->next->next->next->next->data);
	ASSERT_EQ(6, un->next->next->next->next->next->data);
	delList(head1);
	delList(head2);
	delList(un);
}

TEST(unionOfSets, UnionOfEmptyAndNonEmptySet_ValidList)
{
	LIST* head1 = initList(),
		* head2 = initList(),
		* un;

	head2 = insertInList(head2, 4);
	head2 = insertInList(head2, 2);
	head2 = insertInList(head2, 3);
	head2 = insertInList(head2, 1);

	un = unionOfSets(head1, head2);
	ASSERT_EQ(1, un->data);
	ASSERT_EQ(2, un->next->data);
	ASSERT_EQ(3, un->next->next->data);
	ASSERT_EQ(4, un->next->next->next->data);
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
	LIST* head1 = initList(),
		* head2 = initList(),
		* inter;
	head1 = insertInList(head1, 7);
	head1 = insertInList(head1, 4);
	head1 = insertInList(head1, 8);

	head2 = insertInList(head2, 2);
	head2 = insertInList(head2, 7);
	head2 = insertInList(head2, 3);
	head2 = insertInList(head2, 4);

	inter = intersection(head1, head2);

	ASSERT_EQ(4, inter->data);
	ASSERT_EQ(7, inter->next->data);

	delList(head1);
	delList(head2);
	delList(inter);
}

TEST(intersectionSets, intersectionOfEmptyAndNonEmptySet_ReturnNULL)
{
	LIST* head1 = initList(),
		* head2 = initList(),
		* inter;
	head1 = insertInList(head1, 7);
	head1 = insertInList(head1, 4);
	head1 = insertInList(head1, 8);

	inter = intersection(head1, head2);
	ASSERT_EQ(NULL, inter);

	delList(head1);
	delList(head2);
	delList(inter);
}