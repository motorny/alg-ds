#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <string.h>

extern "C" {
#include "J20.h"
}

TEST(TestFindElem, EmptyHT_ReturnFalse_IndEq1_ListEqNULL) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;
  int i;

  ASSERT_EQ(0, FindElem(ht, "a", &i, &list));
  ASSERT_EQ(1, i);
  ASSERT_EQ(NULL, list);

  free(ht);
}

TEST(TestFindElem, ElemIsInHT_ReturnTrue_IndEq1_ListEqNULL) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;
  int i;

  ht[1].str = "a";
  ht[1].num = 1;

  ASSERT_EQ(1, FindElem(ht, "a", &i, &list));
  ASSERT_EQ(1, i);
  ASSERT_EQ(NULL, list);

  free(ht);
}

TEST(TestFindElem, ElemIsInHTList_ReturnTrue_IndEq1_ListUneqNULL) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;
  int i;

  ht[1].str = "";
  ht[1].list = (list_t*)malloc(sizeof(list_t));  // dummy
  ht[1].end = (list_t*)malloc(sizeof(list_t));   // elem
  ht[1].num = 2;

  ht[1].list->next = ht[1].end;
  ht[1].end->str = "a";
  ht[1].end->next = NULL;

  ASSERT_EQ(1, FindElem(ht, "a", &i, &list));
  ASSERT_EQ(1, i);
  ASSERT_TRUE(list != NULL);

  free(ht[1].list);
  free(ht[1].end);
  free(ht);
}

TEST(TestAddElem, ToHT_ElemAddedCorrectly) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;

  AddElem(ht, "a");

  ASSERT_TRUE(strcmp("a", ht[1].str) == 0);
  ASSERT_EQ(NULL, ht[1].list);
  ASSERT_EQ(NULL, ht[1].end);
  ASSERT_EQ(1, ht[1].num);

  free(ht);
}

TEST(TestAddElem, ToHTList_ElemAddedCorrectly) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;

  ht[1].str = "";
  ht[1].num = 1;

  AddElem(ht, "a");

  ASSERT_TRUE(strcmp("a", ht[1].end->str) == 0);
  ASSERT_TRUE(ht[1].list != NULL);
  ASSERT_TRUE(ht[1].end != NULL);
  ASSERT_EQ(2, ht[1].num);
  ASSERT_EQ(ht[1].end, ht[1].list->next);
  ASSERT_EQ(NULL, ht[1].end->next);

  free(ht[1].list);
  free(ht[1].end);
  free(ht);
}

TEST(TestAddElem, ElemExists_ElemIsNotAdded) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;

  ht[1].str = "a";
  ht[1].num = 1;

  AddElem(ht, "a");

  ASSERT_TRUE(strcmp("a", ht[1].str) == 0);
  ASSERT_EQ(NULL, ht[1].list);
  ASSERT_EQ(NULL, ht[1].end);
  ASSERT_EQ(1, ht[1].num);

  free(ht);
}

TEST(TestDelElem, FromHT_ElemDeletedCorrectly) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;

  ht[1].str = "a";
  ht[1].num = 1;

  DelElem(ht, "a");

  ASSERT_TRUE(strcmp("", ht[1].str) == 0);
  ASSERT_EQ(NULL, ht[1].list);
  ASSERT_EQ(NULL, ht[1].end);
  ASSERT_EQ(0, ht[1].num);

  free(ht);
}

TEST(TestDelElem, FromHTList_ElemDeletedCorrectly) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;
  char* str = (char*)malloc(2 * sizeof(char));

  ht[1].str = "";
  ht[1].list = (list_t*)malloc(sizeof(list_t));  // dummy
  ht[1].end = (list_t*)malloc(sizeof(list_t));   // elem
  ht[1].num = 2;

  ht[1].list->next = ht[1].end;
  str[0] = 'a';
  str[1] = 0;
  ht[1].end->str = str;
  ht[1].end->next = NULL;

  DelElem(ht, "a");

  ASSERT_TRUE(strcmp("", ht[1].str) == 0);
  ASSERT_EQ(NULL, ht[1].list);
  ASSERT_EQ(NULL, ht[1].end);
  ASSERT_EQ(1, ht[1].num);

  free(ht);
}

TEST(TestDelElem, ElemDoesNotExist_ElemIsNotDeleted) {
  htable_t* ht = (htable_t*)calloc(N, sizeof(htable_t));
  list_t* list = NULL;

  ht[1].str = "a";
  ht[1].num = 1;

  // 'd' = 100; 'a' = 97;
  // 'a' % N = 'b' % N = 1
  DelElem(ht, "d");

  ASSERT_TRUE(strcmp("a", ht[1].str) == 0);
  ASSERT_EQ(NULL, ht[1].list);
  ASSERT_EQ(NULL, ht[1].end);
  ASSERT_EQ(1, ht[1].num);

  free(ht);
}

int main(int argc, char** argv) {

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}