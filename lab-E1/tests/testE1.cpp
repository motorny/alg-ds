#include "pch.h"
#include "../lab_e/bintree.h"
#include "../lab_e/bintree.c"

#define _CRT_SECURE_NO_WARNINGS

TEST(TestInsert, Simple) {
  btree_t* tree = NULL;
  int key = 1;

  tree = BtreeInsertMod(tree, key);

  EXPECT_EQ(tree->key, key);
  BtreeFree(&tree);
}

TEST(TestInsert, Normal) {
  btree_t* tree = NULL;
  int key1 = 1;
  int key2 = 2;

  tree = BtreeInsertMod(tree, key1);
  tree = BtreeInsertMod(tree, key2);

  EXPECT_EQ(tree->key, key1);
  EXPECT_EQ(tree->right->key, key2);
  BtreeFree(&tree);
}

TEST(TestInsert, Hard) {
  btree_t* tree = NULL;
  int key1 = 1;
  int key2 = 2;
  int key3 = 3;
  int key4 = 4;

  tree = BtreeInsertMod(tree, key2);
  tree = BtreeInsertMod(tree, key1);
  tree = BtreeInsertMod(tree, key3);
  tree = BtreeInsertMod(tree, key4);

  EXPECT_EQ(tree->key, key2);
  EXPECT_EQ(tree->left->key, key1);
  EXPECT_EQ(tree->right->key, key3);
  EXPECT_EQ(tree->right->right->key, key4);
  BtreeFree(&tree);
}

TEST(TestDelete, Simple) {
  btree_t* tree = NULL;
  int key1 = 1;

  tree = BtreeInsertMod(tree, key1);
  tree = BtreeDelete(tree, key1);

  EXPECT_EQ(tree, (btree_t*)NULL);
  BtreeFree(&tree);
}

TEST(TestDelete, Normal) {
  btree_t* tree = NULL;
  int key1 = 1;
  int key2 = 2;
  
  tree = BtreeInsertMod(tree, key1);
  tree = BtreeInsertMod(tree, key2);
  tree = BtreeDelete(tree, key1);

  EXPECT_EQ(tree->key, key2);
  EXPECT_EQ(tree->right, (btree_t*)NULL);
  EXPECT_EQ(tree->left, (btree_t*)NULL);
  BtreeFree(&tree);
}

TEST(TestDelete, Hard) {
  btree_t* tree = NULL;
  int key1 = 1;
  int key2 = 2;
  int key5 = 5;
  int key4 = 4;
  int key6 = 6;

  tree = BtreeInsertMod(tree, key2);
  tree = BtreeInsertMod(tree, key1);
  tree = BtreeInsertMod(tree, key5);
  tree = BtreeInsertMod(tree, key4);
  tree = BtreeInsertMod(tree, key6);

  tree = BtreeDelete(tree, key5);
  EXPECT_EQ(tree->key, key2);
  EXPECT_EQ(tree->left->key, key1);
  EXPECT_EQ(tree->right->key, key6);
  EXPECT_EQ(tree->right->left->key, key4);

  tree = BtreeDelete(tree, key2);
  EXPECT_EQ(tree->key, key4);
  EXPECT_EQ(tree->left->key, key1);
  EXPECT_EQ(tree->right->key, key6);
  BtreeFree(&tree);
}

TEST(TestSearch, Simple) {
  btree_t* tree = NULL;
  int key = 1;
  int keySmoke = 2;

  tree = BtreeInsertMod(tree, key);
  
  EXPECT_EQ(BtreeSearchMod(tree, key), OK);
  EXPECT_EQ(BtreeSearchMod(tree, keySmoke), ERROR);
  BtreeFree(&tree);
}

TEST(TestSearch, Normal) {
  btree_t* tree = NULL;
  int key1 = 1;
  int key2 = 2;
  int keySmoke = 3;

  tree = BtreeInsertMod(tree, key1);
  tree = BtreeInsertMod(tree, key2);
  tree = BtreeDelete(tree, key1);

  EXPECT_EQ(BtreeSearchMod(tree, key1), ERROR);
  EXPECT_EQ(BtreeSearchMod(tree, key2), OK);
  EXPECT_EQ(BtreeSearchMod(tree, keySmoke), ERROR);
  BtreeFree(&tree);
}

TEST(TestHeight, Simple) {
  btree_t* tree = NULL;

  tree = BtreeInsertMod(tree, 1);
  tree = BtreeInsertMod(tree, 2);
  tree = BtreeInsertMod(tree, 3);
  tree = BtreeInsertMod(tree, 4);

  EXPECT_EQ(BtreeHeight(tree), 3);
  BtreeFree(&tree);
}

TEST(TestHeight, Normal) {
  btree_t* tree = NULL;

  tree = BtreeInsertMod(tree, 4);
  tree = BtreeInsertMod(tree, 1);
  tree = BtreeInsertMod(tree, 6);
  tree = BtreeInsertMod(tree, 5);
  tree = BtreeInsertMod(tree, 9);
  tree = BtreeInsertMod(tree, 7);
  tree = BtreeInsertMod(tree, 10);
  tree = BtreeInsertMod(tree, 8);

  EXPECT_EQ(BtreeHeight(tree), 4);
  BtreeFree(&tree);
}

TEST(TestSubDifHeight, Normal) {
  btree_t* tree = NULL;

  tree = BtreeInsertMod(tree, 2);
  tree = BtreeInsertMod(tree, 1);
  tree = BtreeInsertMod(tree, 4);
  tree = BtreeInsertMod(tree, 3);
  tree = BtreeInsertMod(tree, 5);
  tree = BtreeSubHeightDif(tree);

  EXPECT_EQ(tree->difNods, 1);
  EXPECT_EQ(tree->left->difNods, 0);
  EXPECT_EQ(tree->right->difNods, 0);
  EXPECT_EQ(tree->right->left->difNods, 0);
  EXPECT_EQ(tree->right->right->difNods, 0);
  BtreeFree(&tree);
}

