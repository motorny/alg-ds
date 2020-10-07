#include "pch.h"
#include"../Skip_List/Skip_List.c"
#include"../Skip_List/Skip_List.h"

TEST(CreateTest, Test—omparison)
{
    Node* node = Create(1, 7, 4);
    ASSERT_TRUE(node != NULL);
    EXPECT_EQ(7, node->key);
    EXPECT_EQ(4, node->value);
}

TEST(SearchTest, Test—omparison)
{
    SkipList* sl = CreateSkipList();
    ASSERT_EQ(Search(sl, 4), Search(sl, 4));
    ASSERT_NE(Search(sl, 6), Search(sl, 4));
}

TEST(InsertTest, Test—omparison) 
{
    SkipList* sl = CreateSkipList();
    Insert(sl, 9, 8);
    EXPECT_EQ(8, Search(sl, 9));
}

TEST(DeleteTest, Test—omparison)
{
    SkipList* sl = CreateSkipList();
    Delete(sl, 6);
    EXPECT_EQ(0, Search(sl, 6));
}


TEST(DeleteTest, deleteSingleItem_ReturnNULL)
{
    SkipList* sl = CreateSkipList();
    Insert(sl, 1, NULL);
    Delete(sl, 1);
    ASSERT_EQ(NULL, sl);
}