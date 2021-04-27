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
  
  EXPECT_TRUE(table[0].status == 0);
  EXPECT_TRUE(table[1].status == 0);
  EXPECT_TRUE(table[2].status == 0);
}

TEST(HTInsert, HTInsert_EmptyTable_True) {
  htCell_t table[3];
  table[0].status = 0;
  table[1].status = 0;
  table[2].status = 0;

  EXPECT_TRUE(HtInsert(table, 3, "first element") == LABJ_TRUE);
  EXPECT_TRUE(table[0].status == 1 || table[1].status == 1 || table[2].status == 1);
}

TEST(HTInsert, HTInsert_NotEmptyTable_True) {
  htCell_t table[3];
  table[0].status = 1;
  strcpy(table[0].str, "first");
  table[1].status = 1;
  strcpy(table[1].str, "second");
  table[2].status = 0;

  EXPECT_TRUE(HtInsert(table, 3, "third") == LABJ_TRUE);
  EXPECT_TRUE(table[2].status == 1);
}

TEST(HTInsert, HTInsert_FullTable_False) {
  htCell_t table[3];
  table[0].status = 1;
  strcpy(table[0].str, "first");
  table[1].status = 1;
  strcpy(table[1].str, "second");
  table[2].status = 1;
  strcpy(table[2].str, "third");

  EXPECT_FALSE(HtInsert(table, 3, "chetvertyi") == LABJ_TRUE);
}

TEST(HTInsert, HTInsert_WithCollision_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "d", str3[2] = "g";
  table[0].status = 0;
  table[1].status = 0;
  table[2].status = 0;

  EXPECT_TRUE(HtInsert(table, 3, str1) == 1);
  EXPECT_TRUE(HtInsert(table, 3, str2) == 1);
  EXPECT_TRUE(HtInsert(table, 3, str3) == 1);
  EXPECT_TRUE(table[0].status == 1);
  EXPECT_TRUE(table[1].status == 1);
  EXPECT_TRUE(table[2].status == 1);
}

TEST(HTInsert, HTInsert_WithoutCollision_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].status = 0;
  table[1].status = 0;
  table[2].status = 0;

  EXPECT_TRUE(HtInsert(table, 3, str1) == 1);
  EXPECT_TRUE(HtInsert(table, 3, str2) == 1);
  EXPECT_TRUE(HtInsert(table, 3, str3) == 1);
  EXPECT_TRUE(table[0].status == 1);
  EXPECT_TRUE(table[1].status == 1);
  EXPECT_TRUE(table[2].status == 1);
}

TEST(HTFind, HTFind_EmptyTable_False) {
  htCell_t table[3];
  char str1[2] = "a";
  table[0].status = 0;
  table[1].status = 0;
  table[2].status = 0;

  EXPECT_FALSE(HtFind(table, 3, str1) == LABJ_TRUE);
}

TEST(HTFind, HTFind_NotEmptyTableAndElementExist_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].status = 1;
  strcpy(table[0].str, str1);
  table[1].status = 1;
  strcpy(table[1].str, str2);
  table[2].status = 0;

  EXPECT_TRUE(HtFind(table, 3, str1) >= 0);
}

TEST(HTFind, HTFind_NotEmptyTableAndElementDontExist_False) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].status = 1;
  strcpy(table[0].str, str1);
  table[1].status = 1;
  strcpy(table[1].str, str2);
  table[2].status = 0;

  EXPECT_FALSE(HtFind(table, 3, str3) == LABJ_TRUE);
}

TEST(HTFind, HTFind_WithCollision_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "d", str3[2] = "g";
  table[0].status = 1;
  strcpy(table[0].str, str1);
  table[1].status = 1;
  strcpy(table[1].str, str2);
  table[2].status = 1;
  strcpy(table[2].str, str3);

  EXPECT_TRUE(HtFind(table, 3, str1) == LABJ_TRUE);
  EXPECT_TRUE(HtFind(table, 3, str2) == LABJ_TRUE);
  EXPECT_TRUE(HtFind(table, 3, str3) == LABJ_TRUE);
}

TEST(HTFind, HTInsert_WithoutCollision_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].status = 1;
  strcpy(table[0].str, str3);
  table[1].status = 1;
  strcpy(table[1].str, str1);
  table[2].status = 1;
  strcpy(table[2].str, str2);

  EXPECT_TRUE(HtFind(table, 3, str3) == LABJ_TRUE);
  EXPECT_TRUE(HtFind(table, 3, str1) == LABJ_TRUE);
  EXPECT_TRUE(HtFind(table, 3, str2) == LABJ_TRUE);
}

TEST(HTDelete, HTDelete_EmptyTable_False) {
  htCell_t table[3];
  table[0].status = 0;
  table[1].status = 0;
  table[2].status = 0;

  EXPECT_FALSE(HtDelete(table, 3, "smth") == LABJ_TRUE);
}

TEST(HTDelete, HTDelete_NotEmptyTableAndElementExists_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].status = 1;
  strcpy(table[0].str, str3);
  table[1].status = 1;
  strcpy(table[1].str, str1);
  table[2].status = 0;

  EXPECT_TRUE(HtDelete(table, 3, str1) == LABJ_TRUE);
  EXPECT_TRUE(table[1].status == 2);
}

TEST(HTDelete, HTDelete_NotEmptyTableAndElementDontExist_False) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].status = 1;
  strcpy(table[0].str, str3);
  table[1].status = 1;
  strcpy(table[1].str, str1);
  table[2].status = 0;

  EXPECT_FALSE(HtDelete(table, 3, str2) == LABJ_TRUE);
  EXPECT_TRUE(table[0].status == 1 && table[1].status == 1 && table[2].status == 0);
}

TEST(HTDelete, HTInsert_WithCollisionAndElementExists_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "d", str3[2] = "g";
  table[0].status = 1;
  strcpy(table[0].str, str3);
  table[1].status = 1;
  strcpy(table[1].str, str1);
  table[2].status = 1;
  strcpy(table[2].str, str2);

  EXPECT_TRUE(HtDelete(table, 3, str3) == LABJ_TRUE);
  EXPECT_TRUE(table[0].status == 2);

  table[0].status = 1;
  strcpy(table[0].str, str3);
  EXPECT_TRUE(HtDelete(table, 3, str1) == LABJ_TRUE);
  EXPECT_TRUE(table[1].status == 2);

  table[1].status = 1;
  strcpy(table[1].str, str1);
  EXPECT_TRUE(HtDelete(table, 3, str2) == LABJ_TRUE);
  EXPECT_TRUE(table[2].status == 2);
}

TEST(HTDelete, HTInsert_WithCollisionAndElementDoesntExist_False) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "d", str3[2] = "g", str4[2] = "j";
  table[0].status = 1;
  strcpy(table[0].str, str3);
  table[1].status = 1;
  strcpy(table[1].str, str1);
  table[2].status = 1;
  strcpy(table[2].str, str2);

  EXPECT_FALSE(HtDelete(table, 3, str4) == LABJ_TRUE);
  EXPECT_TRUE(table[0].status == 1 && table[1].status == 1 && table[2].status == 1);
}

TEST(HTDelete, HTInsert_WithoutCollisionAndElementExist_True) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c";
  table[0].status = 1;
  strcpy(table[0].str, str3);
  table[1].status = 1;
  strcpy(table[1].str, str1);
  table[2].status = 1;
  strcpy(table[2].str, str2);

  EXPECT_TRUE(HtDelete(table, 3, str1) == LABJ_TRUE);
  EXPECT_TRUE(table[1].status == 2);

  table[1].status = 1;
  strcpy(table[1].str, str1);
  EXPECT_TRUE(HtDelete(table, 3, str2) == LABJ_TRUE);
  EXPECT_TRUE(table[2].status == 2);

  table[2].status = 1;
  strcpy(table[2].str, str2);
  EXPECT_TRUE(HtDelete(table, 3, str3) == 1);
  EXPECT_TRUE(table[0].status == 2);
}

TEST(HTInsert, HTInsert_WithoutCollisionAndElementDoesntExist_False) {
  htCell_t table[3];
  char str1[2] = "a", str2[2] = "b", str3[2] = "c", str4[2] = "3";
  table[0].status = 1;
  strcpy(table[0].str, str3);
  table[1].status = 1;
  strcpy(table[1].str, str1);
  table[2].status = 1;
  strcpy(table[2].str, str2);

  EXPECT_FALSE(HtDelete(table, 3, str4) == LABJ_TRUE);
  EXPECT_TRUE(table[0].status == 1 && table[1].status == 1 && table[2].status == 1);
}

TEST(HTClear, HTClear_True) {
  htCell_t* table = (htCell_t*)malloc(sizeof(htCell_t) * 3);
  char str1[2] = "a", str2[2] = "b", str3[2] = "c", str4[2] = "3";
  table[0].status = 1;
  strcpy(table[0].str, str3);
  table[1].status = 1;
  strcpy(table[1].str, str1);
  table[2].status = 1;
  strcpy(table[2].str, str2);

  EXPECT_TRUE(HtClear(&table, 3) == LABJ_TRUE);
  EXPECT_TRUE(table == NULL);
}
