#include "gtest/gtest.h"
#include "Parser.h"
#include "Structure.h"
#include "Interface.h"

// Template
/*
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
*/

TEST(StringParcing, AllElems)
{
	strPtr strArray;
	int ElemCount = 5;
	char str[] = "1-2-3-4-5";
	char separator[] = "-";
	strArray = ParseString(str, "-", ElemCount);
	EXPECT_STREQ("1", strArray[0]);
	EXPECT_STREQ("2", strArray[1]);
	EXPECT_STREQ("3", strArray[2]);
	EXPECT_STREQ("4", strArray[3]);
	EXPECT_STREQ("5", strArray[4]);
	EXPECT_EQ(NULL, strArray[5]);
}

TEST(StringParcing, 4ElemsOutOf5)
{
	strPtr strArray;
	int ElemCount = 4;
	char str[] = "2-3-4-5-6";
	char separator[] = "-";
	strArray = ParseString(str, "-", ElemCount);
	EXPECT_STREQ("2", strArray[0]);
	EXPECT_STREQ("3", strArray[1]);
	EXPECT_STREQ("4", strArray[2]);
	EXPECT_STREQ("5", strArray[3]);
	EXPECT_EQ(NULL, strArray[4]); // check if this is the end
}


TEST(ListTests, Init)
{
	ListNode* ptr;
	ptr = InitList();
	EXPECT_EQ(0, ptr->date);
	EXPECT_STREQ("Head", ptr->name);
	EXPECT_EQ(INT_MAX, ptr->next->date);
	EXPECT_STREQ("Tail", ptr->next->name);
	EXPECT_EQ(NULL, ptr->next->next);
}

TEST(ListTests, PushNode)
{
	ListNode* head, * tail, * newNode;
	newNode = InitListNode("New Node", 20201016);
	head = InitList();
	tail = head->next;
	PushNode(head, newNode);
	EXPECT_EQ(newNode, head->next);
	EXPECT_EQ(tail, newNode->next);
}

TEST(ListTests, FindPlaceToPush)
{
	//init some list with 5 nodes (+2 fict)
	ListNode* head, *tail;
	ListNode* newNode[5];
	char* name[5] = { "1","2","3","4","5" };
	int date[5] = { 20181016,20191016,20191018,20191018,20191211 };
	head = InitList();
	tail = head->next;
	for (int i = 0;i < 5;i++)
	{
		newNode[i] = InitListNode(name[i], date[i]);
		if (i!=0) newNode[i-1]->next = newNode[i];
	}
	head->next = newNode[0];
	newNode[4]->next = tail;

	EXPECT_EQ(head, FindPlaceToPush(head, 20170101)); // 2017 01 01 must be after head
	EXPECT_EQ(newNode[0], FindPlaceToPush(head, 20181030)); // 2018 10 30 must be after first Node
	EXPECT_EQ(newNode[1], FindPlaceToPush(head, 20191016)); // ...
	EXPECT_EQ(newNode[1], FindPlaceToPush(head, 20191017));
	EXPECT_EQ(newNode[3], FindPlaceToPush(head, 20191018));
	EXPECT_EQ(newNode[4], FindPlaceToPush(head, 20200101)); // 2020 01 01 must be after 2019 12 11
}

TEST(ListTests, FindByDate)
{
	//init some list with 5 nodes (+2 fict)
	ListNode* head, * tail;
	ListNode* newNode[5];
	char* name[5] = { "1","2","3","4","5" };
	int date[5] = { 20181016,20191016,20191018,20191018,20191211 };
	head = InitList();
	tail = head->next;
	for (int i = 0;i < 5;i++)
	{
		newNode[i] = InitListNode(name[i], date[i]);
		if (i != 0) newNode[i - 1]->next = newNode[i];
	}
	head->next = newNode[0];
	newNode[4]->next = tail;

	int count = 0;

	ListNodePtrArray Array = FindByDate(head, 20191018, &count);

	EXPECT_EQ(newNode[2], Array[0]);
	EXPECT_EQ(newNode[3], Array[1]);
	EXPECT_EQ(2, count);
}

TEST(ListTests, IsListSorted)
{
	int flag = 1;
	int count = 0;
	ListNode* head = InitList();
	ReadData(head); //read from Data.txt
	while (head->next->next != NULL && flag==1)
	{
		if (head->date > head->next->date) flag = 0;
		head = head->next;
	}
	EXPECT_EQ(1, flag);
}

int main(int argc, char** argv)
{
	//code for gtest
	//::testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS(); 
	
	ShowMenu();
	return 0;
}