#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

extern "C" {
#include "mergelists.h"
}

TEST(TestCreateList, RunFunc_SublistIsNULL_NextOfDummyIsNULL) {
  list_t* list;
  int err = 0;
  
  list = CreateList(&err);

  ASSERT_EQ(NULL, list->words);
  ASSERT_EQ(NULL, list->next);

  DestroyList(list);
}

TEST(TestFindPlaceForWord, AbIntoSublistOfAaAndAc_ReturnAaPtr) {
  list_t* list;
  subList_t *aa, *ac;
  subList_t* res;
  int err = 0;

  list = (list_t*)malloc(sizeof(list_t));
  list->words = (subList_t*)malloc(sizeof(subList_t));
  aa = (subList_t*)malloc(sizeof(subList_t));
  ac = (subList_t*)malloc(sizeof(subList_t));

  list->words->next = aa;
  aa->next = ac;
  aa->word = "aa";
  ac->next = NULL;
  ac->word = "ac";

  res = FindPlaceForWord("ab", list, &err);
  ASSERT_EQ(aa, res);

  free(aa);
  free(ac);
  free(list->words);
  free(list);
}

TEST(TestFindPlaceForWord, AbIntoSublistOfAa_ReturnAaPtr) {
  list_t* list;
  subList_t *aa;
  subList_t* res;
  int err = 0;

  list = (list_t*)malloc(sizeof(list_t));
  list->words = (subList_t*)malloc(sizeof(subList_t));
  aa = (subList_t*)malloc(sizeof(subList_t));

  list->words->next = aa;
  aa->word = "aa";
  aa->next = NULL;

  res = FindPlaceForWord("ab", list, &err);
  ASSERT_EQ(aa, res);

  free(aa);
  free(list->words);
  free(list);
}

TEST(TestFindPlaceForWord, AbIntoEmptySublist_ReturnDummyPtr) {
  list_t* list;
  subList_t* res;
  int err = 0;

  list = (list_t*)malloc(sizeof(list_t));
  list->words = (subList_t*)malloc(sizeof(subList_t));

  list->words->next = NULL;

  res = FindPlaceForWord("ab", list, &err);
  ASSERT_EQ(list->words, res);

  free(list->words);
  free(list);
}

TEST(TestAddWord, AddAbTntoEmptySublist_NewStructMeetsExpectations) {
  list_t* list;
  subList_t *newSubNode;
  int err = 0;

  list = (list_t*)malloc(sizeof(list_t));
  list->words = (subList_t*)malloc(sizeof(subList_t));

  list->words->next = NULL;

  newSubNode = AddWord("ab", list, &err);
  ASSERT_EQ(newSubNode, list->words->next);
  ASSERT_EQ(0, strcmp(newSubNode->word, "ab"));
  ASSERT_EQ(NULL, newSubNode->next);

  free(list->words);
  free(list);
  free(newSubNode);
}

TEST(TestAddLetter, AddAToEmptyList_NewStructMeetsExpectations) {
  list_t* list, *newNode;
  int err = 0;

  list = (list_t*)malloc(sizeof(list_t));
  list->next = NULL;

  newNode = AddLetter('a', list, &err);
  ASSERT_EQ(newNode, list->next);
  ASSERT_EQ('a', newNode->letter);
  ASSERT_EQ(NULL, newNode->next);
  ASSERT_EQ(NULL, newNode->words->next);

  free(list);
  free(newNode->words);
  free(newNode);
}

TEST(TestFindLetterMatch, BIntoListOfA_ReturnAPtr_FlagZero) {
  list_t *list, *a;
  list_t* res;
  int flag = 0;
  int err = 0;

  list = (list_t*)malloc(sizeof(list_t));
  a = (list_t*)malloc(sizeof(list_t));

  list->next = a;
  a->next = NULL;
  a->letter = 'a';

  res = FindLetterMatch(list, 'b', &flag, &err);
  ASSERT_EQ(a, res);
  ASSERT_EQ(0, flag);

  free(list);
  free(a);
}

TEST(TestFindLetterMatch, BIntoListOfB_ReturnBPtr_FlagUnit) {
  list_t* list, *b;
  list_t* res;
  int flag = 0;
  int err = 0;

  list = (list_t*)malloc(sizeof(list_t));
  b = (list_t*)malloc(sizeof(list_t));

  list->next = b;
  b->next = NULL;
  b->letter = 'b';

  res = FindLetterMatch(list, 'b', &flag, &err);
  ASSERT_EQ(b, res);
  ASSERT_EQ(1, flag);

  free(list);
  free(b);
}

TEST(TestFindLetterMatch, BIntoEmptyList_ReturnDummyPtr_FlagZero) {
  list_t* list;
  list_t* res;
  int flag = 0;
  int err = 0;

  list = (list_t*)malloc(sizeof(list_t));
  list->next = NULL;

  res = FindLetterMatch(list, 'b', &flag, &err);
  ASSERT_EQ(list, res);
  ASSERT_EQ(0, flag);

  free(list);
}

list_t* CreateSimpleList(char letter, char* word) {
  list_t* list, *node;
  subList_t* subNode;

  list = (list_t*)malloc(sizeof(list_t));
  node = (list_t*)malloc(sizeof(list_t));
  list->next = node;
  node->letter = letter;
  node->next = NULL;

  node->words = (subList_t*)malloc(sizeof(subList_t));
  subNode = (subList_t*)malloc(sizeof(subList_t));
  node->words->next = subNode;
  subNode->word = word;
  subNode->next = NULL;

  return list;
}

void DestroySimpleList(list_t* list) {
  list_t* cur = list->next, *next;
  subList_t* subCur, *subNext;

  free(list);
  while (cur != NULL) {
    next = cur->next;
    subCur = cur->words;
    while (subCur != NULL) {
      subNext = subCur->next;
      free(subCur);
      subCur = subNext;
    }
    free(cur);
    cur = next;
  }
}

TEST(TestMergeLists, MergeLetterNeeded__NewListMeetsExpectations) {
  list_t *list1, *list2, *merged;
  int err = 0;

  list1 = CreateSimpleList('a', "aa");
  list2 = CreateSimpleList('a', "ab");

  merged = MergeLists(list1, list2, &err);
  
  ASSERT_EQ('a', merged->next->letter);
  ASSERT_EQ(NULL, merged->next->next);

  ASSERT_EQ(0, strcmp(merged->next->words->next->word, "aa"));
  ASSERT_EQ(0, strcmp(merged->next->words->next->next->word, "ab"));
  ASSERT_EQ(NULL, merged->next->words->next->next->next);

  DestroySimpleList(merged);
}

TEST(TestMergeLists, NoMergeLetterNeeded) {
  list_t* list1, * list2, * merged;
  int err = 0;

  list1 = CreateSimpleList('a', "aa");
  list2 = CreateSimpleList('b', "bb");

  merged = MergeLists(list1, list2, &err);

  ASSERT_EQ('a', merged->next->letter);
  ASSERT_EQ('b', merged->next->next->letter);
  ASSERT_EQ(NULL, merged->next->next->next);

  ASSERT_EQ(0, strcmp(merged->next->words->next->word, "aa"));
  ASSERT_EQ(NULL, merged->next->words->next->next);

  ASSERT_EQ(0, strcmp(merged->next->next->words->next->word, "bb"));
  ASSERT_EQ(NULL, merged->next->next->words->next->next);

  DestroySimpleList(merged);
}

TEST(TestMergeLists, MergeEmptyLists_) {
  list_t* list1, *list2, *merged;
  int err = 0;

  list1 = (list_t*)malloc(sizeof(list_t));
  list2 = (list_t*)malloc(sizeof(list_t));
  list1->next = NULL;
  list2->next = NULL;

  merged = MergeLists(list1, list2, &err);

  ASSERT_EQ(NULL, merged->words);
  ASSERT_EQ(NULL, merged->next);

  DestroyList(merged);
}

int main(int argc, char** argv) {

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}