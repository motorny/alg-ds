#include "pch.h"
#include"..//Tree/Tree.c"


TEST(TestCaseName, TestName)
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(Add, Add_EmptyTree_ReturnTreeFromOneElement) 
{
    struct tree* tree = NULL;
    const int num = 1;
    Add(&tree, num);

    EXPECT_NE(tree, (struct tree*)NULL);
    EXPECT_EQ(tree->left, (struct tree*)NULL);
    EXPECT_EQ(tree->parent, (struct tree*)NULL);
    EXPECT_EQ(tree->right, (struct tree*)NULL);
    EXPECT_EQ(tree->num, num);
    EXPECT_EQ(tree->ord, 1);

    DestroyTree(tree);

}


TEST(FindNode_ElemNotfound, returnNULL)
{
    struct tree* tree = NULL;
    Add(&tree, 1);
    EXPECT_TRUE(FindNode(tree, 2) == NULL);
    DestroyTree(tree);
}



TEST(FindNode_Elemfound, returnPointer)
{
    struct tree* tree = NULL;
    Add(&tree, 1);
    EXPECT_TRUE(FindNode(tree, 1) != NULL);
    DestroyTree(tree);
}


TEST(KNodeFind_, returnNULL)
{
    struct tree* tree = NULL;
    Add(&tree, 1);
    EXPECT_TRUE(KNodeFind(tree, 3) == NULL);
    DestroyTree(tree);
}



TEST(KNodeFind_, returnPointer)
{
    struct tree* tree = NULL;
    Add(&tree, 1);
    EXPECT_TRUE(KNodeFind(tree, 1) != NULL);
    DestroyTree(tree);
}