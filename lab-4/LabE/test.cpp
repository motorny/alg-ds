#include "pch.h"
#include <string.h>

extern "C"
{
#include "tree.h"
}

#define TRUE 1
#define FALSE 0

TEST(ReadTreeFromFile_EmptyFile_returnNULLandFALSE) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "emptyFile.txt");
  
  EXPECT_EQ(res, FALSE);
  EXPECT_EQ(tree == NULL, 1);
}

 TEST(ReadTreeFromFile_1NodeTree_returnTRUEandTree) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "1node.txt");

  EXPECT_EQ(res, TRUE);
  EXPECT_EQ(strcmp(tree->keyStr, "cat"), 0);
  EXPECT_EQ(tree->right == NULL, 1);
  EXPECT_EQ(tree->left == NULL, 1);
}

TEST(ReadTreeFromFile_2NodeLeftTree_returnTRUEandTree) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "2nodeLeft.txt");

  EXPECT_EQ(res, TRUE);
  EXPECT_EQ(strcmp(tree->keyStr, "cat"), 0);
  EXPECT_EQ(tree->right == NULL, 1);

  EXPECT_EQ(strcmp(tree->left->keyStr, "kitten"), 0);
  EXPECT_EQ(tree->left->left == NULL, 1);
  EXPECT_EQ(tree->left->right == NULL, 1);
}

TEST(ReadTreeFromFile_2NodeRightTree_returnTRUEandTree) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "2nodeRight.txt");

  EXPECT_EQ(res, TRUE);
  EXPECT_EQ(strcmp(tree->keyStr, "cat"), 0);
  EXPECT_EQ(tree->left == NULL, 1);

  EXPECT_EQ(strcmp(tree->right->keyStr, "kitten"), 0);
  EXPECT_EQ(tree->right->left == NULL, 1);
  EXPECT_EQ(tree->right->right == NULL, 1);
}

TEST(ReadTreeFromFile_3NodeTree_returnTRUEandTree) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "3node.txt");

  EXPECT_EQ(res, TRUE);
  EXPECT_EQ(strcmp(tree->keyStr, "cat"), 0);

  EXPECT_EQ(strcmp(tree->left->keyStr, "kitten"), 0);
  EXPECT_EQ(tree->left->left == NULL, 1);
  EXPECT_EQ(tree->left->right == NULL, 1);

  EXPECT_EQ(strcmp(tree->right->keyStr, "kitten"), 0);
  EXPECT_EQ(tree->right->left == NULL, 1);
  EXPECT_EQ(tree->right->right == NULL, 1);
}

TEST(ReadTreeFromFile_EmptyStr_returnFALSEandNULL) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "emptyStr.txt");

  EXPECT_EQ(res, FALSE);
  EXPECT_EQ(tree == NULL, 1);
}

TEST(ReadTreeFromFile_BadStrTooManyChilds_returnFALSEandNULL) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "badStrTooManyChilds.txt");

  EXPECT_EQ(res, FALSE);
  EXPECT_EQ(tree == NULL, 1);
}

TEST(ReadTreeFromFile_BadStrUncorrectCntOfOpenedBrackets_returnFALSEandNULL) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "badStrTooMany(.txt");

  EXPECT_EQ(res, FALSE);
  EXPECT_EQ(tree == NULL, 1);
}

TEST(ReadTreeFromFile_BadStrUncorrectCntOfClosedBrackets_returnFALSEandNULL) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "badStrTooMany).txt");

  EXPECT_EQ(res, FALSE);
  EXPECT_EQ(tree == NULL, 1);
}

TEST(ReadTreeFromFile_BadStrUnexpectedWord_returnFALSEandNULL) {
  node_t* tree;
  int res = ReadTreeFromFile(&tree, "badStrUnexpectedWord.txt");

  EXPECT_EQ(res, FALSE);
  EXPECT_EQ(tree == NULL, 1);
}