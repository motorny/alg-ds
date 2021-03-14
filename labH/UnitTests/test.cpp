#include "gtest/gtest.h"

extern "C" {
#include "..\randSearchTreap\randSearchTreap.h"
}

#define NULL_ (void*)0

struct _Treap_t
{
  int key;
  int priority;
  int val;
  struct _Treap_t* L;
  struct _Treap_t* R;
};

TEST(TreapAdd, AddToEmptyTreap)
{
	Treap_t* treap = TreapGet();
	EXPECT_EQ(TreapAdd(&treap, 1, 2, 3), 1);
  EXPECT_EQ(treap->key, 1);
  EXPECT_EQ(treap->priority, 2);
  EXPECT_EQ(treap->val, 3);
  EXPECT_EQ(treap->L, NULL_);
  EXPECT_EQ(treap->R, NULL_);
  TreapFree(treap);
}

TEST(TreapAdd, AddAsLeft)
{
  Treap_t* treap = TreapGet();
  Treap_t* item;
  EXPECT_EQ(TreapAdd(&treap, 1, 2, 3), 1);
  EXPECT_EQ(TreapAdd(&treap, -1, -2, -3), 1);
  EXPECT_EQ(treap->key, 1);
  EXPECT_EQ(treap->priority, 2);
  EXPECT_EQ(treap->val, 3);
  EXPECT_NE(treap->L, NULL_);
  EXPECT_EQ(treap->R, NULL_);
  item = treap->L;
  EXPECT_EQ(item->key, -1);
  EXPECT_EQ(item->priority, -2);
  EXPECT_EQ(item->val, -3);
  EXPECT_EQ(item->L, NULL_);
  EXPECT_EQ(item->R, NULL_);
  TreapFree(treap);
}

TEST(TreapAdd, AddAsRight)
{
  Treap_t* treap = TreapGet();
  Treap_t* item;
  EXPECT_EQ(TreapAdd(&treap, 1, 2, 3), 1);
  EXPECT_EQ(TreapAdd(&treap, 2, -2, -3), 1);
  EXPECT_EQ(treap->key, 1);
  EXPECT_EQ(treap->priority, 2);
  EXPECT_EQ(treap->val, 3);
  EXPECT_EQ(treap->L, NULL_);
  EXPECT_NE(treap->R, NULL_);
  item = treap->R;
  EXPECT_EQ(item->key, 2);
  EXPECT_EQ(item->priority, -2);
  EXPECT_EQ(item->val, -3);
  EXPECT_EQ(item->L, NULL_);
  EXPECT_EQ(item->R, NULL_);
  TreapFree(treap);
}

TEST(TreapAdd, AddAsRoot)
{
  Treap_t* treap = TreapGet();
  Treap_t* item;
  EXPECT_EQ(TreapAdd(&treap, 1, 2, 3), 1);
  EXPECT_EQ(TreapAdd(&treap, -1, 3, -3), 1);
  EXPECT_EQ(treap->key, -1);
  EXPECT_EQ(treap->priority, 3);
  EXPECT_EQ(treap->val, -3);
  EXPECT_EQ(treap->L, NULL_);
  EXPECT_NE(treap->R, NULL_);
  item = treap->R;
  EXPECT_EQ(item->key, 1);
  EXPECT_EQ(item->priority, 2);
  EXPECT_EQ(item->val, 3);
  EXPECT_EQ(item->L, NULL_);
  EXPECT_EQ(item->R, NULL_);
  TreapFree(treap);
}

Treap_t* CreateTreap()
{
  Treap_t* treap = TreapGet();
  TreapAdd(&treap, 5, 12, 5);
  TreapAdd(&treap, 6, 10, 6);
  TreapAdd(&treap, 4, 8, 4);
  TreapAdd(&treap, 2, 6, 2);
  TreapAdd(&treap, 1, 4, 1);
  TreapAdd(&treap, 10, 2, 10);
  return treap;
}

TEST(TreeFind, ItemInTree)
{
  Treap_t* treap = CreateTreap();
  int item = 0;
  EXPECT_EQ(TreapFind(&treap, 2, &item), 1);
  EXPECT_EQ(item, 2);
  TreapFree(treap);
}

TEST(TreeFind, ItemNotInTree)
{
  Treap_t* treap = CreateTreap();
  int item = 0;
  EXPECT_EQ(TreapFind(&treap, 3, &item), -1);
  EXPECT_EQ(item, 0);
  TreapFree(treap);
}

TEST(TreeRemove, ItemInTree)
{
  Treap_t* treap = CreateTreap();
  int item = 0;
  EXPECT_EQ(TreapRemove(&treap, 2, &item), 1);
  EXPECT_EQ(item, 2);
  TreapFree(treap);
}

TEST(TreeRemove, ItemNotInTree)
{
  Treap_t* treap = CreateTreap();
  int item = 0;
  EXPECT_EQ(TreapRemove(&treap, 3, &item), -1);
  EXPECT_EQ(item, 0);
  TreapFree(treap);
}