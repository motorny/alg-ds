#include "pch.h"
#include "../LabA.h/LabA23.c"

TEST(Test, Testgetcount) {
	char* word = "a";
	ASSERT_EQ(getcount(word), 1);
	word = "ab";
	ASSERT_EQ(getcount(word), 2);
	word = "";
	ASSERT_EQ(getcount(word), 0);
}
TEST(Test, TestFindCount) {
	list* fortest = (list*)malloc(sizeof(list));
	list* fortestn = (list*)malloc(sizeof(list));
	list* fortestnn = (list*)malloc(sizeof(list));
	list* head = (list*)malloc(sizeof(list));
	if (fortest && fortestn && fortestnn && head) {
		*fortestnn = { "you", NULL, 3 };
		*fortestn = { "me", fortestnn, 2 };
		*fortest = {"i", fortestn, 1};
		head = fortest;
		ASSERT_EQ(FindCount(&fortest, 0), 0);
		ASSERT_TRUE(fortest == head);
		ASSERT_EQ(FindCount(&fortest, 1), -2);
		ASSERT_TRUE(fortest == head);
		ASSERT_EQ(FindCount(&fortest, 2), -1);
		ASSERT_TRUE(fortest == head);
		ASSERT_EQ(FindCount(&fortest, 3), -1);
		ASSERT_TRUE(fortest == fortestn);
		fortest = head;
		ASSERT_EQ(FindCount(&fortest, 4), 1);
		ASSERT_TRUE(fortest == fortestnn);
	}
}
TEST(Test, TestFindLetter) {
	list* fortest = (list*)malloc(sizeof(list));
	list* fortestn = (list*)malloc(sizeof(list));
	list* fortestnn = (list*)malloc(sizeof(list));
	list* newfortest = (list*)malloc(sizeof(list));
	list* head = (list*)malloc(sizeof(list));
	if (fortest && fortestn && fortestnn && head && newfortest) {
		*fortestnn = { "you", NULL, 3 };
		*fortestn = { "me", fortestnn, 2 };
		*fortest = { "i", fortestn, 1 };
		head = fortest;
		*newfortest = { "a", NULL, 1 };
		ASSERT_EQ(FindLetter(&fortest, newfortest, -2), 0);
		ASSERT_TRUE(fortest == head);
		*newfortest = { "o", NULL, 1 };
		ASSERT_EQ(FindLetter(&fortest, newfortest, -1), 1);
		ASSERT_TRUE(fortest == head);
		*newfortest = { "ab", NULL, 2 };
		ASSERT_EQ(FindLetter(&fortest, newfortest, -1), 1);
		ASSERT_TRUE(fortest == head);
		*newfortest = { "no", NULL, 2 };
		ASSERT_EQ(FindLetter(&fortest, newfortest, -1), 1);
		ASSERT_TRUE(fortest == fortestn);
		fortest = fortestn;
		*newfortest = { "abc", NULL, 3 };
		ASSERT_EQ(FindLetter(&fortest, newfortest, -1), 1);
		ASSERT_TRUE(fortest == fortestn);
		fortest = fortest;
		*newfortest = { "yox", NULL, 3 };
		ASSERT_EQ(FindLetter(&fortest, newfortest, -1), 1);
		ASSERT_TRUE(fortest == fortestnn);
	}
}

TEST(Test, TestAddtoList) {
	list* fortest = (list*)malloc(sizeof(list));
	list* fortestn = (list*)malloc(sizeof(list));
	list* fortestnn = (list*)malloc(sizeof(list));
	list* newfortest = (list*)malloc(sizeof(list));
	list* head = (list*)malloc(sizeof(list));
	if (fortest && fortestn && fortestnn && head && newfortest) {
		*fortestnn = { "you", NULL, 3 };
		*fortestn = { "me", fortestnn, 2 };
		*fortest = { "i", fortestn, 1 };
		head = fortest;
		*newfortest = { "a", NULL, 1 };
		AddtoList(&head, newfortest);
		ASSERT_TRUE(head == newfortest);
		ASSERT_TRUE(head->next == fortest);
		*newfortest = { "o", NULL, 1 };
		AddtoList(&head, newfortest);
		ASSERT_TRUE(head->next->next == newfortest);
	}
}
