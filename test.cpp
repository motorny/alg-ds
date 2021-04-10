#include <gtest/gtest.h>
#define GTEST
#include "LAB-I.c" 

TEST(SimpleTestFromExample, One){
    node *t = NULL;

    t = addElem(t, 1);
    EXPECT_TRUE(t != NULL);

    EXPECT_TRUE(search(t, 1));
    EXPECT_FALSE(search(t, 3));
}

TEST(SimpleTestFromExample, Two){
    node *t = NULL;

    t = addElem(t, 1);
    EXPECT_TRUE(t != NULL);
    t = addElem(t, 2);
    EXPECT_TRUE(t != NULL);

    t = removElem(t, 1);

    EXPECT_FALSE(search(t, 1));
    EXPECT_TRUE(search(t, 2));
    EXPECT_FALSE(search(t, 3));
}

TEST(addElem, TwoKey){
    node *t = NULL;
    t = addElem(t,5);
    t = addElem(t,6);

    EXPECT_EQ(2,t->size);
    EXPECT_EQ(5,t->key[0]);
    EXPECT_EQ(6,t->key[1]);
    EXPECT_FALSE(t->child[0]);
    EXPECT_FALSE(t->child[1]);
    EXPECT_FALSE(t->child[2]);
}

TEST(addElem, FourKey){
    node *t = NULL;
    t = addElem(t,5);
    t = addElem(t,6);
    t = addElem(t,3);
    t = addElem(t,2);

    EXPECT_EQ(1,t->size);
    EXPECT_EQ(5,t->key[0]);
    EXPECT_TRUE(t->child[0]);
    EXPECT_TRUE(t->child[1]);
    EXPECT_FALSE(t->child[2]);

    EXPECT_EQ(2,t->child[0]->size);
    EXPECT_EQ(2,t->child[0]->key[0]);
    EXPECT_EQ(3,t->child[0]->key[1]);
    EXPECT_FALSE(t->child[0]->child[0]);
    EXPECT_FALSE(t->child[0]->child[1]);
    EXPECT_FALSE(t->child[0]->child[2]);

    EXPECT_EQ(1,t->child[1]->size);
    EXPECT_EQ(6,t->child[1]->key[0]);
    EXPECT_FALSE(t->child[1]->child[0]);
    EXPECT_FALSE(t->child[1]->child[1]);
    EXPECT_FALSE(t->child[1]->child[2]);
}

TEST(addElem, SixKey){
    node *t = NULL;
    t = addElem(t,5);
    t = addElem(t,6);
    t = addElem(t,3);
    t = addElem(t,2);
    t = addElem(t,14);
    t = addElem(t,4);

    EXPECT_EQ(2,t->size);
    EXPECT_EQ(3,t->key[0]);
    EXPECT_EQ(5,t->key[1]);
    EXPECT_TRUE(t->child[0]);
    EXPECT_TRUE(t->child[1]);
    EXPECT_TRUE(t->child[2]);

    EXPECT_EQ(1,t->child[0]->size);
    EXPECT_EQ(2,t->child[0]->key[0]);
    EXPECT_FALSE(t->child[0]->child[0]);
    EXPECT_FALSE(t->child[0]->child[1]);
    EXPECT_FALSE(t->child[0]->child[2]);

    EXPECT_EQ(1,t->child[1]->size);
    EXPECT_EQ(4,t->child[1]->key[0]);
    EXPECT_FALSE(t->child[1]->child[0]);
    EXPECT_FALSE(t->child[1]->child[1]);
    EXPECT_FALSE(t->child[1]->child[2]);

    EXPECT_EQ(2,t->child[2]->size);
    EXPECT_EQ(6,t->child[2]->key[0]);
    EXPECT_EQ(14,t->child[2]->key[1]);
    EXPECT_FALSE(t->child[2]->child[0]);
    EXPECT_FALSE(t->child[2]->child[1]);
    EXPECT_FALSE(t->child[2]->child[2]);
}

TEST(addElem, NullOneArg){
    node *t;
    
    t = addElem(NULL, 5);
    EXPECT_TRUE(t);
    EXPECT_EQ(1,t->size);
    EXPECT_EQ(5,t->key[0]);
}

TEST(removElem, DelExistElem){
    node *t1 = NULL, *t2 = NULL, *t3 = NULL;

    t1 = addElem(t1,5);
    t1 = addElem(t1,6);

    EXPECT_TRUE(search(t1,6));
    EXPECT_TRUE(search(t1,5));

    t1 = removElem(t1, 5);
    EXPECT_TRUE(search(t1,6));
    EXPECT_FALSE(search(t1,5));
    t1 = removElem(t1, 6);
    EXPECT_FALSE(search(t1,6));
    EXPECT_FALSE(search(t1,5));


    t2 = addElem(t2,5);
    t2 = addElem(t2,6);
    t2 = addElem(t2,3);
    t2 = addElem(t2,2);

    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));

    t2 = removElem(t2, 3);
    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_FALSE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
    t2 = removElem(t2, 6);
    EXPECT_TRUE(search(t2,5));
    EXPECT_FALSE(search(t2,6));
    EXPECT_FALSE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
    t2 = removElem(t2, 5);
    EXPECT_FALSE(search(t2,5));
    EXPECT_FALSE(search(t2,6));
    EXPECT_FALSE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
}

TEST(removElem, DelNoExistElem){
    node *t1 = NULL, *t2 = NULL, *t3 = NULL;

    t1 = addElem(t1,5);
    t1 = addElem(t1,6);

    EXPECT_TRUE(search(t1,6));
    EXPECT_TRUE(search(t1,5));

    t1 = removElem(t1, 8);
    EXPECT_TRUE(search(t1,6));
    EXPECT_TRUE(search(t1,5));
    t1 = removElem(t1, 3);
    EXPECT_TRUE(search(t1,6));
    EXPECT_TRUE(search(t1,5));


    t2 = addElem(t2,5);
    t2 = addElem(t2,6);
    t2 = addElem(t2,3);
    t2 = addElem(t2,2);

    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));

    t2 = removElem(t2, 1);
    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
    t2 = removElem(t2, 10);
    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
    t2 = removElem(t2, 4);
    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
}

TEST(removElem, NullOneArg){
    node *t;   

    t = removElem(NULL, 5);
    EXPECT_FALSE(t);
}

TEST(search, SearchExistElem){
    node *t = NULL;
    t = addElem(t,5);
    t = addElem(t,6);
    t = addElem(t,3);
    t = addElem(t,2);

    EXPECT_EQ(5,t->key[0]);
    EXPECT_EQ(2,t->child[0]->key[0]);
    EXPECT_EQ(3,t->child[0]->key[1]);
    EXPECT_EQ(6,t->child[1]->key[0]);

    EXPECT_EQ(search(t, 5), t);
    EXPECT_EQ(search(t, 2), t->child[0]);
    EXPECT_EQ(search(t, 3), t->child[0]);
    EXPECT_EQ(search(t, 6), t->child[1]);
}

TEST(search, SearchNoExistElem){
    node *t = NULL;
    t = addElem(t,5);
    t = addElem(t,6);
    t = addElem(t,3);
    t = addElem(t,2);

    EXPECT_EQ(5,t->key[0]);
    EXPECT_EQ(2,t->child[0]->key[0]);
    EXPECT_EQ(3,t->child[0]->key[1]);
    EXPECT_EQ(6,t->child[1]->key[0]);

    EXPECT_FALSE(search(t, 1));
    EXPECT_FALSE(search(t, 10));
    EXPECT_FALSE(search(t, 4));
    EXPECT_FALSE(search(t, 0));
}

TEST(search, NullOneArg){
    node *t;   

    t = search(NULL, 5);
    EXPECT_FALSE(t);
}
