#include "gtest/gtest.h"

extern "C" {
#include "..\BTree\BTree.h"
}

#define NULL_ (void*)0

typedef struct _BTNode_t BTNode_t;

typedef struct _keyItem_t
{
  int key;
  int value;
  BTNode_t* L;
}keyItem_t;

struct _BTNode_t
{
  int count;
  keyItem_t* keyItems;
};

struct _BTree_t
{
  int t;
  int count;
  BTNode_t* root;
};

#define IsLeaf(node) (node->keyItems[0].L == NULL_)

TEST(BTreeAdd, AddToEmptyTree)
{
  BTree_t* tree = BTreeGet(2);
  EXPECT_EQ(1, BTreeAdd(tree, 2, 3));
  EXPECT_EQ(2, tree->t);
  EXPECT_EQ(1, tree->count);
  EXPECT_NE(NULL_, tree->root);
  EXPECT_EQ(1, tree->root->count);
  EXPECT_EQ(2, tree->root->keyItems[0].key);
  EXPECT_EQ(3, tree->root->keyItems[0].value);
  EXPECT_EQ(NULL_, tree->root->keyItems[0].L);
  EXPECT_EQ(NULL_, tree->root->keyItems[1].L);
  BTreeFree(tree);
}

TEST(BTreeAdd, AddAsLeft)
{
  BTree_t* tree = BTreeGet(2);
  EXPECT_EQ(1, BTreeAdd(tree, 2, 3));
  EXPECT_EQ(1, BTreeAdd(tree, 0, 1));
  EXPECT_EQ(2, tree->t);
  EXPECT_EQ(2, tree->count);
  EXPECT_NE(NULL_, tree->root);
  EXPECT_EQ(2, tree->root->count);
  EXPECT_EQ(0, tree->root->keyItems[0].key);
  EXPECT_EQ(1, tree->root->keyItems[0].value);
  EXPECT_EQ(2, tree->root->keyItems[1].key);
  EXPECT_EQ(3, tree->root->keyItems[1].value);
  EXPECT_EQ(NULL_, tree->root->keyItems[0].L);
  EXPECT_EQ(NULL_, tree->root->keyItems[1].L);
  EXPECT_EQ(NULL_, tree->root->keyItems[2].L);
  BTreeFree(tree);
}

TEST(BTreeAdd, AddAsRight)
{
  BTree_t* tree = BTreeGet(2);
  EXPECT_EQ(1, BTreeAdd(tree, 2, 3));
  EXPECT_EQ(1, BTreeAdd(tree, 4, 5));
  EXPECT_EQ(2, tree->t);
  EXPECT_EQ(2, tree->count);
  EXPECT_NE(NULL_, tree->root);
  EXPECT_EQ(2, tree->root->count);
  EXPECT_EQ(2, tree->root->keyItems[0].key);
  EXPECT_EQ(3, tree->root->keyItems[0].value);
  EXPECT_EQ(4, tree->root->keyItems[1].key);
  EXPECT_EQ(5, tree->root->keyItems[1].value);
  EXPECT_EQ(NULL_, tree->root->keyItems[0].L);
  EXPECT_EQ(NULL_, tree->root->keyItems[1].L);
  EXPECT_EQ(NULL_, tree->root->keyItems[2].L);
  BTreeFree(tree);
}

TEST(BTreeAdd, AddToFullRoot)
{
  BTree_t* tree = BTreeGet(2);
  BTNode_t* L;
  BTNode_t* R;
  EXPECT_EQ(1, BTreeAdd(tree, 0, 1));
  EXPECT_EQ(1, BTreeAdd(tree, 2, 3));
  EXPECT_EQ(1, BTreeAdd(tree, 4, 5));
  EXPECT_EQ(1, BTreeAdd(tree, 6, 7));
  EXPECT_EQ(2, tree->t);
  EXPECT_EQ(4, tree->count);
  EXPECT_NE(NULL_, tree->root);
  EXPECT_EQ(1, tree->root->count);
  EXPECT_EQ(2, tree->root->keyItems[0].key);
  EXPECT_EQ(3, tree->root->keyItems[0].value);
  L = tree->root->keyItems[0].L;
  R = tree->root->keyItems[1].L;
  EXPECT_NE(NULL_, L);
  EXPECT_NE(NULL_, R);
  EXPECT_EQ(1, L->count);
  EXPECT_EQ(0, L->keyItems[0].key);
  EXPECT_EQ(1, L->keyItems[0].value);
  EXPECT_EQ(NULL_, L->keyItems[0].L);
  EXPECT_EQ(NULL_, L->keyItems[1].L);
  EXPECT_EQ(2, R->count);
  EXPECT_EQ(4, R->keyItems[0].key);
  EXPECT_EQ(5, R->keyItems[0].value);
  EXPECT_EQ(6, R->keyItems[1].key);
  EXPECT_EQ(7, R->keyItems[1].value);
  EXPECT_EQ(NULL_, R->keyItems[0].L);
  EXPECT_EQ(NULL_, R->keyItems[1].L);
  EXPECT_EQ(NULL_, R->keyItems[2].L);
  BTreeFree(tree);
}

BTree_t* CreateBTree()
{
  BTree_t* tree = BTreeGet(2);
  BTreeAdd(tree, 5, 12);
  BTreeAdd(tree, 6, 10);
  BTreeAdd(tree, 4, 8);
  BTreeAdd(tree, 2, 6);
  BTreeAdd(tree, 1, 4);
  BTreeAdd(tree, 10, 2);
  //      5
  //1 2 4   6 10
  return tree;
}

TEST(BTreeFind, ItemInTree)
{
  BTree_t* tree = CreateBTree();
  int item = 0;
  EXPECT_EQ(BTreeFind(tree, 2, &item), 1);
  EXPECT_EQ(item, 6);
  BTreeFree(tree);
}

TEST(BTreeFind, ItemNotInTree)
{
  BTree_t* tree = CreateBTree();
  int item = 0;
  EXPECT_EQ(BTreeFind(tree, 3, &item), -1);
  EXPECT_EQ(item, 0);
  BTreeFree(tree);
}

TEST(BTreeRemove, ItemInTree)
{
  BTree_t* tree = CreateBTree();
  int item = 0;
  EXPECT_EQ(BTreeRemove(tree, 2, &item), 1);
  EXPECT_EQ(item, 6);
  BTreeFree(tree);
}

TEST(TreeRemove, ItemNotInTree)
{
  BTree_t* tree = CreateBTree();
  int item = 0;
  EXPECT_EQ(BTreeRemove(tree, 3, &item), -1);
  EXPECT_EQ(item, 0);
  BTreeFree(tree);
}