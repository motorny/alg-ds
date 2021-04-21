#include "pch.h"

extern "C"
{
#include "ht.h"
}

TEST(HTInit, HTInit_NotPossitiveSize_False) {
  htCell_t *table = NULL;

  EXPECT_FALSE(HtInit(&table, -3) == 1);
  EXPECT_TRUE(table == NULL);
}

TEST(HTInit, HTInit_PossitiveSize_True) {
  htCell_t *table;
  
  EXPECT_TRUE(HtInit(&table, 3) == 1);
  EXPECT_TRUE(table != NULL);
  
  EXPECT_TRUE(table[0].isFree == 1);
  EXPECT_TRUE(table[0].str == NULL);

  EXPECT_TRUE(table[1].isFree == 1);
  EXPECT_TRUE(table[1].str == NULL);

  EXPECT_TRUE(table[2].isFree == 1);
  EXPECT_TRUE(table[2].str == NULL);
}

TEST(HTInsert, HTInsert_EmptyTable_True) {
  htCell_t table[3];
  table[0].isFree = 1;
  table[0].str = NULL;
  table[1].isFree = 1;
  table[1].str = NULL;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_TRUE(HtInsert(table, 3, "first element") == 1);
  EXPECT_TRUE(table[0].isFree == 0 || table[1].isFree == 0 || table[2].isFree == 0);
}

TEST(HTInsert, HTInsert_NotEmptyTable_True) {
  htCell_t table[3];
  table[0].isFree = 0;
  table[0].str = "first";
  table[1].isFree = 0;
  table[1].str = "second";
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_TRUE(HtInsert(table, 3, "third") == 1);
  EXPECT_TRUE(table[2].isFree == 0);
}

TEST(HTInsert, HTInsert_FullTable_False) {
  htCell_t table[3];
  table[0].isFree = 0;
  table[0].str = "first";
  table[1].isFree = 0;
  table[1].str = "second";
  table[2].isFree = 0;
  table[2].str = "third";

  EXPECT_FALSE(HtInsert(table, 3, "chetvertyi") == 1);
}

TEST(HTInsert, HTInsert_WithCollision_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "d", str3[2] = "g";
  table[0].isFree = 1;
  table[0].str = NULL;
  table[1].isFree = 1;
  table[1].str = NULL;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_TRUE(HtInsert(table, 3, str1) == 1);
  EXPECT_TRUE(HtInsert(table, 3, str2) == 1);
  EXPECT_TRUE(HtInsert(table, 3, str3) == 1);
  EXPECT_TRUE(table[0].isFree == 0);
  EXPECT_TRUE(table[1].isFree == 0);
  EXPECT_TRUE(table[2].isFree == 0);
}

TEST(HTInsert, HTInsert_WithoutCollision_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].isFree = 1;
  table[0].str = NULL;
  table[1].isFree = 1;
  table[1].str = NULL;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_TRUE(HtInsert(table, 3, str1) == 1);
  EXPECT_TRUE(HtInsert(table, 3, str2) == 1);
  EXPECT_TRUE(HtInsert(table, 3, str3) == 1);
  EXPECT_TRUE(table[0].isFree == 0);
  EXPECT_TRUE(table[1].isFree == 0);
  EXPECT_TRUE(table[2].isFree == 0);
}

TEST(HTFind, HTFind_EmptyTable_False) {
  htCell_t table[3];
  char str1[2] = "a";
  table[0].isFree = 1;
  table[0].str = NULL;
  table[1].isFree = 1;
  table[1].str = NULL;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_FALSE(HtFind(table, 3, str1) >= 0);
}

TEST(HTFind, HTFind_NotEmptyTableAndElementExist_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].isFree = 0;
  table[0].str = str1;
  table[1].isFree = 0;
  table[1].str = str2;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_TRUE(HtFind(table, 3, str1) >= 0);
}

TEST(HTFind, HTFind_NotEmptyTableAndElementDontExist_False) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].isFree = 0;
  table[0].str = str1;
  table[1].isFree = 0;
  table[1].str = str2;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_FALSE(HtFind(table, 3, str3) >= 0);
}

TEST(HTFind, HTFind_WithCollision_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "d", str3[2] = "g";
  table[0].isFree = 0;
  table[0].str = str1;
  table[1].isFree = 0;
  table[1].str = str2;
  table[2].isFree = 0;
  table[2].str = str3;

  EXPECT_TRUE(HtFind(table, 3, str1) >= 0);
  EXPECT_TRUE(HtFind(table, 3, str2) >= 0);
  EXPECT_TRUE(HtFind(table, 3, str3) >= 0);
}

TEST(HTFind, HTInsert_WithoutCollision_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].isFree = 0;
  table[0].str = str3;
  table[1].isFree = 0;
  table[1].str = str1;
  table[2].isFree = 0;
  table[2].str = str2;

  EXPECT_TRUE(HtFind(table, 3, str3) >= 0);
  EXPECT_TRUE(HtFind(table, 3, str1) >= 0);
  EXPECT_TRUE(HtFind(table, 3, str2) >= 0);
}

TEST(HTDelete, HTDelete_EmptyTable_False) {
  htCell_t table[3];
  table[0].isFree = 1;
  table[0].str = NULL;
  table[1].isFree = 1;
  table[1].str = NULL;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_FALSE(HtDelete(table, 3, "smth") == 1);
}

TEST(HTDelete, HTDelete_NotEmptyTableAndElementExists_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].isFree = 0;
  table[0].str = str3;
  table[1].isFree = 0;
  table[1].str = str1;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_TRUE(HtDelete(table, 3, str1) == 1);
  EXPECT_TRUE(table[1].isFree == 1);
  EXPECT_TRUE(table[1].str == NULL);
}

TEST(HTDelete, HTDelete_NotEmptyTableAndElementDontExist_False) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].isFree = 0;
  table[0].str = str3;
  table[1].isFree = 0;
  table[1].str = str1;
  table[2].isFree = 1;
  table[2].str = NULL;

  EXPECT_FALSE(HtDelete(table, 3, str2) == 1);
  EXPECT_TRUE(table[2].isFree == 1);
  EXPECT_TRUE(table[2].str == NULL);
}

TEST(HTDelete, HTInsert_WithCollisionAndElementExists_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "d", str3[2] = "g";
  table[0].isFree = 0;
  table[0].str = str1;
  table[1].isFree = 0;
  table[1].str = str2;
  table[2].isFree = 0;
  table[2].str = str3;

  EXPECT_TRUE(HtDelete(table, 3, str1) == 1);
  EXPECT_TRUE(table[0].isFree == 1);
  EXPECT_TRUE(table[0].str == NULL);

  table[0].isFree = 0;
  table[0].str = str1;
  EXPECT_TRUE(HtDelete(table, 3, str2) == 1);
  EXPECT_TRUE(table[1].isFree == 1);
  EXPECT_TRUE(table[1].str == NULL);

  table[1].isFree = 0;
  table[1].str = str2;
  EXPECT_TRUE(HtDelete(table, 3, str3) == 1);
  EXPECT_TRUE(table[2].isFree == 1);
  EXPECT_TRUE(table[2].str == NULL);
}

TEST(HTDelete, HTInsert_WithCollisionAndElementDoesntExist_False) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "d", str3[2] = "g", str4[2] = "j";
  table[0].isFree = 0;
  table[0].str = str1;
  table[1].isFree = 0;
  table[1].str = str2;
  table[2].isFree = 0;
  table[2].str = str3;

  EXPECT_FALSE(HtDelete(table, 3, str4) == 1);
  EXPECT_TRUE(table[0].isFree == 0 && table[1].isFree == 0 && table[2].isFree == 0);
}

TEST(HTDelete, HTInsert_WithoutCollisionAndElementExist_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].isFree = 0;
  table[0].str = str3;
  table[1].isFree = 0;
  table[1].str = str1;
  table[2].isFree = 0;
  table[2].str = str2;

  EXPECT_TRUE(HtDelete(table, 3, str1) == 1);
  EXPECT_TRUE(table[1].isFree == 1);
  EXPECT_TRUE(table[1].str == NULL);

  table[1].isFree = 0;
  table[1].str = str1;
  EXPECT_TRUE(HtDelete(table, 3, str2) == 1);
  EXPECT_TRUE(table[2].isFree == 1);
  EXPECT_TRUE(table[2].str == NULL);

  table[2].isFree = 0;
  table[2].str = str1;
  EXPECT_TRUE(HtDelete(table, 3, str3) == 1);
  EXPECT_TRUE(table[0].isFree == 1);
  EXPECT_TRUE(table[0].str == NULL);
}

TEST(HTInsert, HTInsert_WithoutCollisionAndElementDoesntExist_False) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c", str4[2] = "3";
  table[0].isFree = 0;
  table[0].str = str3;
  table[1].isFree = 0;
  table[1].str = str1;
  table[2].isFree = 0;
  table[2].str = str2;

  EXPECT_FALSE(HtDelete(table, 3, str4) == 1);
  EXPECT_TRUE(table[0].isFree == 0 && table[1].isFree == 0 && table[2].isFree == 0);
}

TEST(HTClear, HTClear_True) {
  htCell_t* table = (htCell_t*)malloc(sizeof(htCell_t) * 3);
  char str1[2] = "a", str2[2] = "b", str3[2] = "c", str4[2] = "3";
  table[0].isFree = 0;
  table[0].str = str3;
  table[1].isFree = 0;
  table[1].str = str1;
  table[2].isFree = 0;
  table[2].str = str2;

  EXPECT_TRUE(HtClear(&table, 3) == 1);
  EXPECT_TRUE(table == NULL);
}
