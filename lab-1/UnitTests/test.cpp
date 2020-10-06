#include "gtest/gtest.h"
extern "C" {
#include "../skip_list.h"
#include "../list.h"
}

/* Tests for 'skip_list_t' */

TEST(SkipListInsert_InsertKeyNotAdded_return1) {
  skip_list_t sl;

  SkipListIni(&sl);
  EXPECT_EQ(1, SkipListInsert(&sl, 1));
  ASSERT_FALSE(sl.start == NULL);
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0]->key, 1);
  ASSERT_EQ(sl.start->next[0]->next[0], sl.start);

  SkipListClose(&sl);
}

TEST(SkipListInsert_InsertKeyAdded_returnMinus2) {
  skip_list_t sl;
  skip_list_node_t sln = {};

  SkipListIni(&sl);
  sln.key = 1;
  sln.next[0] = sl.start;
  sl.start->next[0] = &sln;

  EXPECT_EQ(-2, SkipListInsert(&sl, 1));
  ASSERT_FALSE(sl.start == NULL);
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0]->key, 1);
  ASSERT_EQ(sl.start->next[0]->next[0], sl.start);

  sl.start->next[0] = sl.start;
  SkipListClose(&sl);
}

TEST(SkipListInsert_InsertNILKey_returnMinus2) {
  skip_list_t sl;

  SkipListIni(&sl);
  EXPECT_EQ(-2, SkipListInsert(&sl, INT_MAX));
  ASSERT_FALSE(sl.start == NULL);
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0]->key, INT_MAX);

  SkipListClose(&sl);
}

TEST(SkipListFind_FindKeyNotAdded_return0) {
  skip_list_t sl;

  SkipListIni(&sl);
  EXPECT_EQ(0, SkipListFind(&sl, 1));
  ASSERT_FALSE(sl.start == NULL);
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0], sl.start);

  SkipListClose(&sl);
}

TEST(SkipListFind_FindKeyAdded_return1) {
  skip_list_t sl;
  skip_list_node_t sln = {};

  SkipListIni(&sl);
  sln.key = 1;
  sln.next[0] = sl.start;
  sl.start->next[0] = &sln;

  EXPECT_EQ(1, SkipListFind(&sl, 1));
  ASSERT_FALSE(sl.start == NULL);
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0]->key, 1);
  ASSERT_EQ(sl.start->next[0]->next[0], sl.start);

  sl.start->next[0] = sl.start;
  SkipListClose(&sl);
}

TEST(SkipListFind_FindNILKey_return1) {
  skip_list_t sl;

  SkipListIni(&sl);

  EXPECT_EQ(1, SkipListFind(&sl, INT_MAX));
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0]->key, INT_MAX);

  SkipListClose(&sl);
}

TEST(SkipListExtract_ExtractNotAdded_return0) {
  skip_list_t sl;

  SkipListIni(&sl);
  EXPECT_EQ(0, SkipListExtract(&sl, 1));
  ASSERT_FALSE(sl.start == NULL);
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0], sl.start);

  SkipListClose(&sl);
}

TEST(SkipListFind_ExtractKeyAdded_return1) {
  skip_list_t sl;
  skip_list_node_t *sln = (skip_list_node_t*)malloc(sizeof(skip_list_node_t));

  SkipListIni(&sl);
  sln->key = 1;
  sln->next[0] = sl.start;
  sl.start->next[0] = sln;

  EXPECT_EQ(1, SkipListExtract(&sl, 1));
  ASSERT_FALSE(sl.start == NULL);
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0], sl.start);

  SkipListClose(&sl);
}

TEST(SkipListFind_ExtractNILKey_returnMinus1) {
  skip_list_t sl;

  SkipListIni(&sl);
  EXPECT_EQ(-1, SkipListExtract(&sl, INT_MAX));
  ASSERT_FALSE(sl.start == NULL);
  ASSERT_EQ(sl.start->key, INT_MAX);
  ASSERT_EQ(sl.start->next[0], sl.start);

  SkipListClose(&sl);
}

/* Tests for 'list_t' */
TEST(ListInsert_InsertKeyNotAdded_return1) {
  list_t l;

  ListIni(&l);
  EXPECT_EQ(1, ListInsert(&l, 1));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, 1);
  ASSERT_EQ(l.start->next->key, INT_MAX);
  ASSERT_EQ(l.start->next->next, (list_node_t*)NULL);

  ListClose(&l);
}

TEST(ListInsert_InsertKeyAdded_returnMinus2) {
  list_t l;
  list_node_t ln = {};

  ListIni(&l);
  ln.key = 1;
  ln.next = l.start;
  l.start = &ln;

  EXPECT_EQ(-2, ListInsert(&l, 1));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, 1);
  ASSERT_EQ(l.start->next->key, INT_MAX);
  ASSERT_EQ(l.start->next->next, (list_node_t*)NULL);

  l.start = l.start->next;
  ListClose(&l);
}

TEST(ListInsert_InsertNILKey_returnMinus2) {
  list_t l;

  ListIni(&l);
  EXPECT_EQ(-2, ListInsert(&l, INT_MAX));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, INT_MAX);
  ASSERT_EQ(l.start->next, (list_node_t *)NULL);

  ListClose(&l);
}

TEST(ListFind_FindKeyNotAdded_return0) {
  list_t l;

  ListIni(&l);
  EXPECT_EQ(0, ListFind(&l, 1));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, INT_MAX);
  ASSERT_EQ(l.start->next, (list_node_t*)NULL);
  ListClose(&l);
}

TEST(ListFind_FindKeyAdded_return1) {
  list_t l;
  list_node_t ln = {};

  ListIni(&l);
  ln.key = 1;
  ln.next = l.start;
  l.start = &ln;

  EXPECT_EQ(1, ListFind(&l, 1));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, 1);
  ASSERT_EQ(l.start->next->key, INT_MAX);
  ASSERT_EQ(l.start->next->next, (list_node_t*)NULL);

  l.start = l.start->next;

  ListClose(&l);
}

TEST(ListFind_FindNILKey_returnMinus1) {
  list_t l;

  ListIni(&l);
  EXPECT_EQ(1, ListFind(&l, INT_MAX));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, INT_MAX);
  ASSERT_EQ(l.start->next, (list_node_t*)NULL);

  ListClose(&l);
}

TEST(ListExtract_ExtractNotAdded_return0) {
  list_t l;

  ListIni(&l);
  EXPECT_EQ(0, ListExtract(&l, 1));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, INT_MAX);
  ASSERT_EQ(l.start->next, (list_node_t*)NULL);

  ListClose(&l);
}

TEST(ListFind_ExtractKeyAdded_return1) {
  list_t l;
  list_node_t *ln = (list_node_t*)malloc(sizeof(list_node_t));

  ListIni(&l);
  ln->key = 1;
  ln->next = l.start;
  l.start = ln;

  EXPECT_EQ(1, ListExtract(&l, 1));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, INT_MAX);
  ASSERT_EQ(l.start->next, (list_node_t*)NULL);

  ListClose(&l);
}

TEST(ListFind_ExtractNILKey_returnMinus1) {
  list_t l;

  ListIni(&l);
  EXPECT_EQ(-1, ListExtract(&l, INT_MAX));
  ASSERT_FALSE(l.start == NULL);
  ASSERT_EQ(l.start->key, INT_MAX);
  ASSERT_EQ(l.start->next, (list_node_t*)NULL);

  ListClose(&l);
}