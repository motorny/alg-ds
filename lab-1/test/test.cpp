#include "pch.h"
#include "../Alg_Lab_A/list_functions.c"

TEST(list_functionsTest, InitListTest) {
	list_p* list = InitList("tword");
	ASSERT_TRUE(list != NULL);
	EXPECT_STREQ("tword", list->word);
	DeleteList(list);
}

TEST(list_functionsTest, EnterWordTest) {
	list_p* list = InitList("");
	EnterWord(list, "tword");
	EXPECT_STREQ("tword", list->word);
	DeleteList(list);
}

TEST(list_functionsTest, FindPlaceForWordTestThatIsHigher) {
	list_p* list = InitList("tword");

	list_p* pWord = NULL;
	list_p* nWord = NULL;
	char word2compare[20];

	strcpy(word2compare, "mind");

	FindPlaceForWord(&list, word2compare, &pWord, &nWord);
	EXPECT_TRUE(pWord == NULL);
	EXPECT_TRUE(nWord == list);

	DeleteList(list);
}

TEST(list_functionsTest, FindPlaceForWordTestThatIsLower) {
	list_p* list = InitList("tword");

	list_p* pWord = NULL;
	list_p* nWord = NULL;
	char word2compare[20];

	strcpy(word2compare, "zoo");

	FindPlaceForWord(&list, word2compare, &pWord, &nWord);
	EXPECT_TRUE(pWord == list);
	EXPECT_TRUE(nWord == NULL);

	DeleteList(list);
}

TEST(list_functionsTest, FindPlaceForWordTestThatIsBetween) {
	list_p* list = InitList("tword");
	list_p* list2 = InitList("zoo");
	list->next = list2;

	list_p* pWord = NULL;
	list_p* nWord = NULL;
	char word2compare[20];

	strcpy(word2compare, "you");

	FindPlaceForWord(&list, word2compare, &pWord, &nWord);
	EXPECT_TRUE(pWord == list);
	EXPECT_TRUE(nWord == list->next);

	DeleteList(list);
}

TEST(list_functionsTest, AddWordTestThatIsHigher) {
	list_p* list = InitList("tword");

	list_p* newWord = NULL;
	list_p* pWord = NULL, * nWord = NULL;

	char word2compare[20];

	strcpy(word2compare, "mind");

	FindPlaceForWord(&list, word2compare, &pWord, &nWord);
	newWord = AddWord(nWord, pWord, word2compare);

	ASSERT_TRUE(newWord != NULL);
	EXPECT_TRUE(pWord == NULL);
	EXPECT_TRUE(newWord->next == nWord);

	DeleteList(list);
}

TEST(list_functionsTest, AddWordTestThatIsLower) {
	list_p* list = InitList("tword");

	list_p* newWord = NULL;
	list_p* pWord = NULL, * nWord = NULL;

	char word2compare[20];

	strcpy(word2compare, "zoo");

	FindPlaceForWord(&list, word2compare, &pWord, &nWord);
	newWord = AddWord(nWord, pWord, word2compare);

	ASSERT_TRUE(newWord != NULL);
	EXPECT_TRUE(pWord->next == newWord);
	EXPECT_TRUE(newWord->next == NULL);

	DeleteList(list);
}

TEST(list_functionsTest, AddWordTestThatIsBetween) {
	list_p* list = InitList("tword");
	list_p* list2 = InitList("zoo");
	list->next = list2;

	list_p* newWord = NULL;
	list_p* pWord = NULL, * nWord = NULL;

	char word2compare[20];

	strcpy(word2compare, "you");

	FindPlaceForWord(&list, word2compare, &pWord, &nWord);
	newWord = AddWord(nWord, pWord, word2compare);

	ASSERT_TRUE(newWord != NULL);
	EXPECT_TRUE(pWord->next == newWord);
	EXPECT_TRUE(newWord->next == nWord);

	DeleteList(list);
}

TEST(list_functionsTest, Add2ListTestWithNoChangeOrder) {
	list_p* list = NULL;
	list_p* word1 = NULL;
	char word[20];

	strcpy(word, "russia");
	list = InitList(word);
	word1= list;

	strcpy(word, "usa");
	Add2List(&list, word);

	ASSERT_TRUE(word1 != NULL);
	EXPECT_TRUE(word1 == list);
	EXPECT_TRUE(word1->next != NULL);

	DeleteList(list);
}

TEST(list_functionsTest, Add2ListTestWithChangeOrder) {
	list_p* list = NULL;
	list_p* word1 = NULL;
	char word[20];

	strcpy(word, "usa");
	list = InitList(word);
	word1 = list;

	strcpy(word, "russia");
	Add2List(&list, word);

	ASSERT_TRUE(word1 != NULL);
	EXPECT_TRUE(word1 != list);
	EXPECT_TRUE(word1->next == NULL);

	DeleteList(list);
}