#include <gtest/gtest.h>
#include "node.h"

TEST(SimpleTestFromExample, One) {
    node *root = NULL;

    insert(1);
    EXPECT_TRUE(root != NULL);
}

TEST(SimpleTestFromExample, Two) {
    node *root = NULL;

    insert(1);
    EXPECT_TRUE(root != NULL);
}

TEST(InsertKeyTest, TwoKey) {
    treap *t = NULL;
    t = insert(5);
    t = insert(6);

    EXPECT_EQ(6, t->x);
    EXPECT_EQ(5, t->left->x);
}

TEST(InsertKeyTest, FourKey) {
    node *root = NULL;
    insert(5);
    insert(6);
    insert(3);
    insert(2);

    EXPECT_EQ(2, t->x);
    EXPECT_EQ(3, t->right->x);
    EXPECT_EQ(6, t->right->right->x);
    EXPECT_EQ(5, t->right->right->left->x);
}

TEST(InsertKeyTest, SixKey) {

    node *root = NULL;
    insert(5);
    insert(6);
    insert(3);
    insert(2);
    insert(1);
    insert(4);

    EXPECT_EQ(4, root->keys[1]);
    EXPECT_EQ(2, root->p[0]->x);
    EXPECT_EQ(14, root->right->x);
    EXPECT_EQ(6, root->right->left->x);
    EXPECT_EQ(5, root->right->left->left->x);
}


TEST(RemoveKeyTest, DelExistElem) {
    node *t1 = NULL, *t2 = NULL, *t3 = NULL;

    insert(5);
    insert(6);

    EXPECT_TRUE(search(6));
    EXPECT_TRUE(search(5));

    del(5);
    EXPECT_TRUE(search(6));
    EXPECT_FALSE(search(5));
    del(6);
    EXPECT_FALSE(search(6));
    EXPECT_FALSE(search(5));


    insert(5);
    insert(6);
    insert(3);
    insert(2);

    EXPECT_TRUE(search(5));
    EXPECT_TRUE(search(6));
    EXPECT_TRUE(search(3));
    EXPECT_TRUE(search(2));

    del(3);
    EXPECT_TRUE(search(5));
    EXPECT_TRUE(search(6));
    EXPECT_FALSE(search(3));
    EXPECT_TRUE(search(2));
    del(6);
    EXPECT_TRUE(search(5));
    EXPECT_FALSE(search(6));
    EXPECT_FALSE(search(3));
    EXPECT_TRUE(search(2));
    del(5);
    EXPECT_FALSE(search(5));
    EXPECT_FALSE(search(6));
    EXPECT_FALSE(search(3));
    EXPECT_TRUE(search(2));
}
