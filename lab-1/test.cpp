#pragma warning(disable:4996)

#include "pch.h"
extern "C"
{
#include "LabA.h"
}

TEST(TestAddList, TestAddList) {
  list_t testStart;
  list_t testNEW = { "a", NULL };
  AddList(&testStart, &testNEW);
  ASSERT_STREQ(testStart.prev->str, testNEW.str);
}

TEST(TestSortTwo, TestSortTwoMovingElements) {
  list_t test;
  test.prev = NULL;
  list_t* test1 = (list_t*)calloc(1, sizeof(list_t));
  list_t* test2 = (list_t*)calloc(1, sizeof(list_t));
  if (test1 != NULL && test2 != NULL) {
    strcpy_s(test1->str, "b");
    strcpy_s(test2->str, "a");
    test1->prev = test.prev;
    test.prev = test1;
    test2->prev = test.prev;
    test.prev = test2;
    list_t* firstTest = &test;
    SortTwo(firstTest->prev);
    ASSERT_STREQ(firstTest->prev->str, "a");
    ASSERT_STREQ(firstTest->prev->prev->str, "b");
    ASSERT_TRUE(firstTest->prev->prev->prev == NULL);
    free(test1);
    free(test2);
  }
}

TEST(TestSortTwo, TestSortTwoNoMovingElements) {
  list_t test;
  test.prev = NULL;
  list_t* test1 = (list_t*)calloc(1, sizeof(list_t));
  list_t* test2 = (list_t*)calloc(1, sizeof(list_t));
  if (test1 != NULL && test2 != NULL) {
    strcpy_s(test1->str, "a");
    strcpy_s(test2->str, "b");
    test1->prev = test.prev;
    test.prev = test1;
    test2->prev = test.prev;
    test.prev = test2;
    list_t* firstTest = &test;
    SortTwo(firstTest->prev);
    ASSERT_STREQ(firstTest->prev->str, "b");
    ASSERT_TRUE(firstTest->prev->prev == NULL);
    free(test1);
    free(test2);
  }
}

TEST(TestSortList, TestSortListSorted) {
  list_t test;
  test.prev = NULL;
  list_t* test1 = (list_t*)calloc(1, sizeof(list_t));
  list_t* test2 = (list_t*)calloc(1, sizeof(list_t));
  list_t* test3 = (list_t*)calloc(1, sizeof(list_t));
  list_t* test4 = (list_t*)calloc(1, sizeof(list_t));
  if (test1 != NULL && test2 != NULL && test3 != NULL && test4 != NULL) {
    strcpy_s(test1->str, "c");
    strcpy_s(test2->str, "d");
    strcpy_s(test3->str, "a");
    strcpy_s(test4->str, "b");
    test1->prev = test.prev;
    test.prev = test1;
    test2->prev = test.prev;
    test.prev = test2;
    test3->prev = test.prev;
    test.prev = test3;
    test4->prev = test.prev;
    test.prev = test4;
    list_t* first = &test;
    SortList(first);
    ASSERT_STREQ(first->prev->str, "a");
    ASSERT_STREQ(first->prev->prev->str, "b");
    ASSERT_STREQ(first->prev->prev->prev->str, "c");
    ASSERT_STREQ(first->prev->prev->prev->prev->str, "d");
    ASSERT_TRUE(first->prev->prev->prev->prev->prev == NULL);
    free(test1);
    free(test2);
    free(test3);
    free(test4);
  }
}

int main(void) {
  return RUN_ALL_TESTS();
}