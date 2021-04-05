#include "pch.h"
#include "gtest/gtest.h"
#include "../LabI/tree.c"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(0, NULL);
  EXPECT_TRUE(true);
}


TEST(AddElem, empty_tree) {
	ASSERT_TRUE(Insert(NULL, 30));
}


TEST(AddElem, add_some_elements) {
	struct Node* p = CreateNode(13);

	//EXPECT_TRUE(Insert(p, 13));
	EXPECT_EQ(p->key[0], 13);
	EXPECT_TRUE(Insert(p, 99));
	EXPECT_EQ(p->key[1], 99);
	EXPECT_TRUE(Insert(p, 12));
	EXPECT_TRUE(Insert(p, 4));
	EXPECT_TRUE(Insert(p, 770));
	EXPECT_TRUE(Insert(p, 2));
	EXPECT_TRUE(Insert(p, 7));

	free(p->first);
	free(p->second);
	free(p->third);
	free(p);
}


TEST(SearchElem, search_in_empty_tree) {
	ASSERT_FALSE(Search(NULL, 13));
}


TEST(SearchElem, search_no_exist_element) {
	struct Node* p = CreateNode(13);
	p = Insert(p, 99);
	p = Insert(p, 1);
	p = Insert(p, 9);
	p = Insert(p, 38);
	p = Insert(p, 7);

	ASSERT_FALSE(Search(p, 0));
	ASSERT_FALSE(Search(p, 8));
	ASSERT_FALSE(Search(p, 76234));

	free(p->first);
	free(p->second);
	free(p->third);
	free(p);
}


TEST(SearchElem, search_exist_elems) {
	struct Node* p = CreateNode(13);
	p = Insert(p, 99);
	p = Insert(p, 1);
	p = Insert(p, 9);
	p = Insert(p, 38);
	p = Insert(p, 7);

	ASSERT_TRUE(Search(p, 13));
	ASSERT_TRUE(Search(p, 7));
	ASSERT_TRUE(Search(p, 1));

	free(p->first);
	free(p->second);
	free(p->third);
	free(p);
}


TEST(RemoveElem, remove_in_empty_tree) {
	ASSERT_FALSE(Remove(NULL, 13));
}


TEST(RemoveElem, remove_no_exist_element) {
	struct Node* p = CreateNode(13);
	p = Insert(p, 99);
	p = Insert(p, 1);
	p = Insert(p, 9);
	p = Insert(p, 38);
	p = Insert(p, 7);

	ASSERT_FALSE(Remove(p, 0));
	ASSERT_FALSE(Remove(p, 8));
	ASSERT_FALSE(Remove(p, 76234));

	free(p->first);
	free(p->second);
	free(p->third);
	free(p);
}


TEST(RemoveElem, remove_exist_elems) {
	struct Node* p = CreateNode(13);
	p = Insert(p, 99);
	p = Insert(p, 1);
	p = Insert(p, 9);
	p = Insert(p, 38);
	p = Insert(p, 7);

	ASSERT_TRUE(Remove(p, 13));
	ASSERT_TRUE(Remove(p, 7));
	ASSERT_TRUE(Remove(p, 1));

	free(p->first);
	free(p->second);
	free(p->third);
	free(p);
}