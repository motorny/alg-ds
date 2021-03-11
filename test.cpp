#include "pch.h"
#include"/Users/Анастасия/source/repos/RandomSearchTree/tree.c"

TEST(DeleteTree, CorrectProcessing) {
    DeleteTree(NULL);
}


 

TEST(Insert, Insert_EmptyTree_ReturnTreeFromOneElement)
{
    tree_t* node = NULL;
    const int num = 1;
    Insert(&node, num);

    EXPECT_NE(node, (tree_t*)NULL);
    EXPECT_EQ(node->left, (tree_t*)NULL);
    EXPECT_EQ(node->right, (tree_t*)NULL);
    EXPECT_EQ(node->key, 1);
    

    DeleteTree(node);

}


TEST(Find, returnNULL)
{
    tree_t* node = NULL;
    Insert(&node, 1);
    EXPECT_TRUE(Find(node, 2) == NULL);
    DeleteTree(node);
}



TEST(Find, returnPointer)
{
  
    tree_t* node = NULL;
    Insert(&node, 1);
    EXPECT_TRUE(Find(node, 1) != NULL);
    DeleteTree(node);
}


