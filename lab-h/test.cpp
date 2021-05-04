#include <gtest/gtest.h>
#define GTEST
#include "LAB-H.c"

TEST(SimpleTestFromExample, One){
    treap *t = NULL, *k;

    k = creatNode(1);
    EXPECT_TRUE(k != NULL);

    t = insertKey(t, k);
    EXPECT_TRUE(t != NULL);

    EXPECT_TRUE(search(t, 1));
    EXPECT_FALSE(search(t, 3));
}

TEST(SimpleTestFromExample, Two){
    treap *t = NULL, *k;

    k = creatNode(1);
    EXPECT_TRUE(k != NULL);
    t = insertKey(t, k);
    EXPECT_TRUE(t != NULL);
    k = creatNode(2);
    EXPECT_TRUE(k != NULL);
    t = insertKey(t, k);
    EXPECT_TRUE(t != NULL);

    t = removeKey(t, 1);

    EXPECT_FALSE(search(t, 1));
    EXPECT_TRUE(search(t, 2));
    EXPECT_FALSE(search(t, 3));
}

TEST(InsertKeyTest, TwoKey){
    treap *t = NULL;
    t = insertKey(t,creatNode(5));
    t = insertKey(t,creatNode(6));

    EXPECT_EQ(6,t->x);
    EXPECT_EQ(5,t->left->x);
}

TEST(InsertKeyTest, FourKey){
    treap *t = NULL;
    t = insertKey(t,creatNode(5));
    t = insertKey(t,creatNode(6));
    t = insertKey(t,creatNode(3));
    t = insertKey(t,creatNode(2));

    EXPECT_EQ(2,t->x);
    EXPECT_EQ(3,t->right->x);
    EXPECT_EQ(6,t->right->right->x);
    EXPECT_EQ(5,t->right->right->left->x);
}

TEST(InsertKeyTest, SixKey){

    treap *t = NULL;
    t = insertKey(t,creatNode(5));
    t = insertKey(t,creatNode(6));
    t = insertKey(t,creatNode(3));
    t = insertKey(t,creatNode(2));
    t = insertKey(t,creatNode(14));
    t = insertKey(t,creatNode(4));

    EXPECT_EQ(4,t->x);
    EXPECT_EQ(2,t->left->x);
    EXPECT_EQ(3,t->left->right->x);
    EXPECT_EQ(14,t->right->x);
    EXPECT_EQ(6,t->right->left->x);
    EXPECT_EQ(5,t->right->left->left->x);
}

TEST(InsertKeyTest, NullOneArg){
    treap *t;
    treap k;
    k.left = NULL;
    k.right = NULL;
    k.x = 1;
    k.y = 0;

    t = insertKey(NULL, &k);
    EXPECT_EQ(t, &k);
}

TEST(InsertKeyTest, NullTwoArg){
    treap *t = NULL;
    treap k;
    k.left = NULL;
    k.right = NULL;
    k.x = 1;
    k.y = 0;
    t = insertKey(t, &k);

    t = insertKey(t, NULL);

    EXPECT_TRUE(t);
    EXPECT_EQ(t, &k);
    EXPECT_FALSE(t->left);
    EXPECT_FALSE(t->right);
}

TEST(RemoveKeyTest, DelExistElem){
    treap *t1 = NULL, *t2 = NULL, *t3 = NULL;
    
    t1 = insertKey(t1,creatNode(5));
    t1 = insertKey(t1,creatNode(6));

    EXPECT_TRUE(search(t1,6));
    EXPECT_TRUE(search(t1,5));

    t1 = removeKey(t1, 5);
    EXPECT_TRUE(search(t1,6));
    EXPECT_FALSE(search(t1,5));
    t1 = removeKey(t1, 6);
    EXPECT_FALSE(search(t1,6));
    EXPECT_FALSE(search(t1,5));


    t2 = insertKey(t2,creatNode(5));
    t2 = insertKey(t2,creatNode(6));
    t2 = insertKey(t2,creatNode(3));
    t2 = insertKey(t2,creatNode(2));

    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));

    t2 = removeKey(t2, 3);
    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_FALSE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
    t2 = removeKey(t2, 6);
    EXPECT_TRUE(search(t2,5));
    EXPECT_FALSE(search(t2,6));
    EXPECT_FALSE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
    t2 = removeKey(t2, 5);
    EXPECT_FALSE(search(t2,5));
    EXPECT_FALSE(search(t2,6));
    EXPECT_FALSE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
}

TEST(RemoveKeyTest, DelNoExistElem){
    treap *t1 = NULL, *t2 = NULL, *t3 = NULL;
    
    t1 = insertKey(t1,creatNode(5));
    t1 = insertKey(t1,creatNode(6));

    EXPECT_TRUE(search(t1,6));
    EXPECT_TRUE(search(t1,5));

    t1 = removeKey(t1, 8);
    EXPECT_TRUE(search(t1,6));
    EXPECT_TRUE(search(t1,5));
    t1 = removeKey(t1, 3);
    EXPECT_TRUE(search(t1,6));
    EXPECT_TRUE(search(t1,5));


    t2 = insertKey(t2,creatNode(5));
    t2 = insertKey(t2,creatNode(6));
    t2 = insertKey(t2,creatNode(3));
    t2 = insertKey(t2,creatNode(2));

    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));

    t2 = removeKey(t2, 1);
    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
    t2 = removeKey(t2, 10);
    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
    t2 = removeKey(t2, 4);
    EXPECT_TRUE(search(t2,5));
    EXPECT_TRUE(search(t2,6));
    EXPECT_TRUE(search(t2,3));
    EXPECT_TRUE(search(t2,2));
}

TEST(RemoveKeyTest, NullOneArg){
    treap *t;   

    t = removeKey(NULL, 5);
    EXPECT_FALSE(t);
}

TEST(SearchTest, SearchExistElem){
    treap *t = NULL;
    t = insertKey(t,creatNode(5));
    t = insertKey(t,creatNode(6));
    t = insertKey(t,creatNode(3));
    t = insertKey(t,creatNode(2));

    EXPECT_EQ(2,t->x);
    EXPECT_EQ(3,t->right->x);
    EXPECT_EQ(6,t->right->right->x);
    EXPECT_EQ(5,t->right->right->left->x);


    EXPECT_EQ(search(t, 2), t);
    EXPECT_EQ(search(t, 3), t->right);
    EXPECT_EQ(search(t, 6), t->right->right);
    EXPECT_EQ(search(t, 5), t->right->right->left);
}

TEST(SearchTest, SearchNoExistElem){
    treap *t = NULL;
    t = insertKey(t,creatNode(5));
    t = insertKey(t,creatNode(6));
    t = insertKey(t,creatNode(3));
    t = insertKey(t,creatNode(2));

    EXPECT_EQ(2,t->x);
    EXPECT_EQ(3,t->right->x);
    EXPECT_EQ(6,t->right->right->x);
    EXPECT_EQ(5,t->right->right->left->x);


    EXPECT_FALSE(search(t, 1));
    EXPECT_FALSE(search(t, 10));
    EXPECT_FALSE(search(t, 4));
    EXPECT_FALSE(search(t, 0));
}

TEST(SearchTest, NullOneArg){
    treap *t;   

    t = search(NULL, 5);
    EXPECT_FALSE(t);
}
