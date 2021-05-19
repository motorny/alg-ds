#include "gtest/gtest.h"
#include "../tree.h"

extern "C" {
  struct node_t {
    int
      size,
      keys[3];
    struct node_t
      *childs[4],
      *parent;
  };
}

TEST(Insert_NullTree_ReturnMinus1) {
  EXPECT_EQ(Insert(NULL, 0), -1);
}

TEST(Insert_AddToRoot_Return1) {
  node_t *tree = NULL;
  EXPECT_EQ(Insert(&tree, 0), 1);
  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Insert_AddToExistedNode_Return1) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 0;
  EXPECT_EQ(Insert(&tree, 1), 1);
  EXPECT_EQ(tree->size, 2);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->keys[1], 1);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Insert_AddWithNewLevel_Return1) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 2;
  tree->keys[0] = 0;
  tree->keys[1] = 1;

  EXPECT_EQ(Insert(&tree, 2), 1);

  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 1);
  EXPECT_EQ(tree->parent, (node_t *)NULL);

  EXPECT_EQ(tree->childs[0]->size, 1);
  EXPECT_EQ(tree->childs[0]->keys[0], 0);
  EXPECT_EQ(tree->childs[0]->parent, tree);
  EXPECT_EQ(tree->childs[0]->childs[0], (node_t *)NULL);

  EXPECT_EQ(tree->childs[1]->size, 1);
  EXPECT_EQ(tree->childs[1]->keys[0], 2);
  EXPECT_EQ(tree->childs[1]->parent, tree);
  EXPECT_EQ(tree->childs[1]->childs[0], (node_t *)NULL);

  free(tree->childs[0]);
  free(tree->childs[1]);
  free(tree);
}

TEST(Insert_AddExisted_Return0) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 0;
  EXPECT_EQ(Insert(&tree, 0), 0);
  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Find_NullTree_Return0) {
  EXPECT_EQ(Find(NULL, 0), 0);
}

TEST(Find_Existed_Return1) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 0;

  EXPECT_EQ(Find(tree, 0), 1);
  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Find_Unexisted_Return0) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 0;

  EXPECT_EQ(Find(tree, 1), 0);
  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Delete_NullTree_ReturnMinus1) {
  EXPECT_EQ(Delete(NULL, 0), -1);
}

TEST(Delete_DeleteUnexisted_Return0) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 0;

  EXPECT_EQ(Delete(&tree, 1), 0);
  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Delete_DeleteRoot_Return1) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 0;

  EXPECT_EQ(Delete(&tree, 0), 1);
  EXPECT_EQ(tree, (node_t *)NULL);
  free(tree);
}

TEST(Delete_DeleteWithoutLeveling_Return1) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 2;
  tree->keys[0] = 0;
  tree->keys[1] = 1;

  EXPECT_EQ(Delete(&tree, 1), 1);
  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Delete_DeleteWithLeveling_Return1) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 1;

  tree->childs[0] = (node_t *)malloc(sizeof(node_t));
  tree->childs[0]->size = 1;
  tree->childs[0]->keys[0] = 0;
  tree->childs[0]->parent = tree;
  tree->childs[0]->childs[0] = tree->childs[0]->childs[1] = tree->childs[0]->childs[2] = tree->childs[0]->childs[3] = NULL;

  tree->childs[1] = (node_t *)malloc(sizeof(node_t));
  tree->childs[1]->size = 1;
  tree->childs[1]->keys[0] = 2;
  tree->childs[1]->parent = tree;
  tree->childs[1]->childs[0] = tree->childs[1]->childs[1] = tree->childs[1]->childs[2] = tree->childs[1]->childs[3] = NULL;

  EXPECT_EQ(Delete(&tree, 2), 1);
  EXPECT_EQ(tree->size, 2);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->keys[1], 1);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Print_EmptyTree_CorrectWork) {
  Print(NULL);
}

TEST(Print_1KeyInNode_CorrectWork) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 0;
  Print(tree);
  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Print_2KeyInNode_CorrectWork) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 2;
  tree->keys[0] = 0;
  tree->keys[1] = 1;
  Print(tree);
  EXPECT_EQ(tree->size, 2);
  EXPECT_EQ(tree->keys[0], 0);
  EXPECT_EQ(tree->keys[1], 1);
  EXPECT_EQ(tree->parent, (node_t *)NULL);
  EXPECT_EQ(tree->childs[0], (node_t *)NULL);
  free(tree);
}

TEST(Print_2Levels_CorrectWork) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 1;

  tree->childs[0] = (node_t *)malloc(sizeof(node_t));
  tree->childs[0]->size = 1;
  tree->childs[0]->keys[0] = 0;
  tree->childs[0]->parent = tree;
  tree->childs[0]->childs[0] = tree->childs[0]->childs[1] = tree->childs[0]->childs[2] = tree->childs[0]->childs[3] = NULL;

  tree->childs[1] = (node_t *)malloc(sizeof(node_t));
  tree->childs[1]->size = 1;
  tree->childs[1]->keys[0] = 2;
  tree->childs[1]->parent = tree;
  tree->childs[1]->childs[0] = tree->childs[1]->childs[1] = tree->childs[1]->childs[2] = tree->childs[1]->childs[3] = NULL;

  Print(tree);
  
  EXPECT_EQ(tree->size, 1);
  EXPECT_EQ(tree->keys[0], 1);
  EXPECT_EQ(tree->parent, (node_t *)NULL);

  EXPECT_EQ(tree->childs[0]->size, 1);
  EXPECT_EQ(tree->childs[0]->keys[0], 0);
  EXPECT_EQ(tree->childs[0]->parent, tree);
  EXPECT_EQ(tree->childs[0]->childs[0], (node_t *)NULL);

  EXPECT_EQ(tree->childs[1]->size, 1);
  EXPECT_EQ(tree->childs[1]->keys[0], 2);
  EXPECT_EQ(tree->childs[1]->parent, tree);
  EXPECT_EQ(tree->childs[1]->childs[0], (node_t *)NULL);

  free(tree->childs[0]);
  free(tree->childs[1]);
  free(tree);
}

TEST(DeleteTree_EmptyTree_CorrectWork) {
  DeleteTree(NULL);
}

TEST(DeleteTree_1Level_CorrectWork) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[0] = tree->childs[1] = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 2;
  tree->keys[0] = 0;
  tree->keys[1] = 1;
  DeleteTree(tree);
}

TEST(DeleteTree_2Levels_CorrectWork) {
  node_t *tree = (node_t *)malloc(sizeof(node_t));
  tree->parent = tree->childs[2] = tree->childs[3] = NULL;
  tree->size = 1;
  tree->keys[0] = 1;

  tree->childs[0] = (node_t *)malloc(sizeof(node_t));
  tree->childs[0]->size = 1;
  tree->childs[0]->keys[0] = 0;
  tree->childs[0]->parent = tree;
  tree->childs[0]->childs[0] = tree->childs[0]->childs[1] = tree->childs[0]->childs[2] = tree->childs[0]->childs[3] = NULL;

  tree->childs[1] = (node_t *)malloc(sizeof(node_t));
  tree->childs[1]->size = 1;
  tree->childs[1]->keys[0] = 2;
  tree->childs[1]->parent = tree;
  tree->childs[1]->childs[0] = tree->childs[1]->childs[1] = tree->childs[1]->childs[2] = tree->childs[1]->childs[3] = NULL;

  DeleteTree(tree);
}
