#include "pch.h"
#include"../Skip_List/Skip_List.c"
#include"../Skip_List/Skip_List.h"

TEST(CreateTest, TestСomparison)
{
    Node* node = Create(1, 7, 4);
    ASSERT_TRUE(node != NULL);
    EXPECT_EQ(7, node->key);
    EXPECT_EQ(4, node->value);
}


void Init(SkipList* sl, int key, int value, int lvl) {
    Node* update[2];
    Node* p, * q;
    p = sl->header;

if (lvl > sl->level) {
    for (int i = sl->level + 1; i <= lvl; i++)
        update[i] = sl->header;
    sl->level = lvl;
}

q = Create(lvl, key, value);
for (int i = 0; i <= lvl; i++) {
    q->forward[i] = update[i]->forward[i];
    update[i]->forward[i] = q;
}

}

SkipList* Get(){
    SkipList* sl = (SkipList*)malloc(sizeof(SkipList));
    int k = 0;
    sl->level = 0;
    sl->header = Create(2, 0, 0);
    sl->tail = Create(0, 3, 0);
    for (int i = 0; i <= 2; i++) {
        sl->header->forward[i] = sl->tail;
    }
    for (int i = 1 ; i <= 3 ; i++ ,k++) {
        Init(sl, i, i, k);
    }
    return sl;
    /*      
              (3:3)
         (2:2)(3:3)  
    (1:1)(2:2)(3:3)
    */
}


TEST(SearchTest, TestСomparison)
{
    SkipList* sl = Get();
    ASSERT_EQ(1, Search(sl, 1));
    ASSERT_EQ(2, Search(sl, 2));
    ASSERT_EQ(3, Search(sl, 3));

}

TEST(DeleteTest, TestСomparison)
{
    SkipList* sl = Get();
    Delete(sl, 1);
    ASSERT_NE(1, sl->header->forward[1]->key);
    EXPECT_EQ(2, sl->header->forward[1]->key);
}

TEST(DeleteTest, deleteSingleItem_ReturnNULL)
{
    SkipList* sl = Get();
    Delete(sl, 1);
    Delete(sl, 2);
    Delete(sl, 3);
    ASSERT_EQ(NULL, sl);
}

TEST(InsertTest, TestСomparison) 
{
    SkipList* sl =Get();
    Insert(sl, 4, 4);
    ASSERT_NE(NULL, sl->header->forward[4]->key);
    EXPECT_EQ(4, sl->header->forward[4]->key);
    EXPECT_EQ(4, sl->header->forward[4]->value);
}





    
