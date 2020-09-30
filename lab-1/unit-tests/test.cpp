#include "pch.h"
#include "..\skipList.h"

TEST(SkipListFree, ZeroItems_NoMemLeaks) {
  _CrtMemState s1, s2, s3;

  skipList* list;

  _CrtMemCheckpoint(&s1);

  list = skipList_Get();
  skipList_Free(list);

  _CrtMemCheckpoint(&s2);

  EXPECT_FALSE(_CrtMemDifference(&s3, &s1, &s2) && (_CrtMemDumpStatistics(&s3), true));
}

TEST(SkipListFree, OneItems_NoMemLeaks) {
  _CrtMemState s1, s2, s3;

  skipList* list;
  void* value = NULL;
  int key = 0;
  char level = 1;

  _CrtMemCheckpoint(&s1);

  list = skipList_Get();
  skipList_Add(list, value, key, level);
  skipList_Free(list);

  _CrtMemCheckpoint(&s2);

  EXPECT_FALSE(_CrtMemDifference(&s3, &s1, &s2) && (_CrtMemDumpStatistics(&s3), true));
}

TEST(SkipListAdd, TwoItemsSecondSmaller_NoMemLeaks) {
  _CrtMemState s1, s2, s3;

  skipList* list;
  void* value = NULL;
  int key1 = 1, key2 = 0;
  char level1 = 1, level2 = 2;

  _CrtMemCheckpoint(&s1);

  list = skipList_Get();
  skipList_Add(list, value, key1, level1);
  skipList_Add(list, value, key2, level2);
  skipList_Free(list);

  _CrtMemCheckpoint(&s2);

  EXPECT_FALSE(_CrtMemDifference(&s3, &s1, &s2) && (_CrtMemDumpStatistics(&s3), true));
}

TEST(SkipListAdd, TwoItemsSecondBigger_NoMemLeaks) {
  _CrtMemState s1, s2, s3;

  skipList* list;
  void* value = NULL;
  int key1 = 1, key2 = 2;
  char level1 = 1, level2 = 2;

  _CrtMemCheckpoint(&s1);

  list = skipList_Get();
  skipList_Add(list, value, key1, level1);
  skipList_Add(list, value, key2, level2);
  skipList_Free(list);

  _CrtMemCheckpoint(&s2);

  EXPECT_FALSE(_CrtMemDifference(&s3, &s1, &s2) && (_CrtMemDumpStatistics(&s3), true));
}

TEST(SkipListAdd, TreeItems_NoMemLeaks) {
  _CrtMemState s1, s2, s3;

  skipList* list;
  void* value = NULL;
  int key1 = 1, key2 = 2, key3 = 3;
  char level1 = 1, level2 = 2, level3 = 3;

  _CrtMemCheckpoint(&s1);

  list = skipList_Get();
  skipList_Add(list, value, key1, level1);
  skipList_Add(list, value, key2, level2);
  skipList_Add(list, value, key3, level3);
  skipList_Free(list);

  _CrtMemCheckpoint(&s2);

  EXPECT_FALSE(_CrtMemDifference(&s3, &s1, &s2) && (_CrtMemDumpStatistics(&s3), true));
}