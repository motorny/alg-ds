//
// Created by ikuzin on 02.03.2021.
//

#include "gtest/gtest.h"
#include "Node.h"

TEST(addNode, addRootNode) {
    Node_t *tr = NULL;
    tr = Add(tr, 10);
    ASSERT_EQ(10, tr->key);
    ASSERT_EQ(NULL, tr->parent);
    ASSERT_EQ(NULL, tr->left);
    ASSERT_EQ(NULL, tr->right);
}

TEST(addNode, addChildren4Root) {
    Node_t *tr = NULL;
    tr = Add(tr, 10);
    tr = Add(tr, 15);
    tr = Add(tr, 5);
    ASSERT_EQ(tr->right->parent, tr->left->parent);
    ASSERT_EQ(5, tr->left->key);
    ASSERT_EQ(15, tr->right->key);
}

TEST(delNode, delRoot) {
    Node_t *tr = NULL;
    tr = Add(tr, 10);
    tr = Add(tr, 15);
    tr = Add(tr, 5);
    Del(tr, 10);
    ASSERT_EQ(15, tr->key);
    ASSERT_EQ(NULL, tr->right);
    ASSERT_EQ(tr->key, tr->left->parent->key);
}

TEST(delNode, delChildren4Root) {
    Node_t *tr = NULL;
    tr = Add(tr, 10);
    tr = Add(tr, 15);
    tr = Add(tr, 5);
    Del(tr, 15);
    Del(tr, 5);
    ASSERT_EQ(NULL, tr->left);
    ASSERT_EQ(tr->right, tr->left);
}

TEST(delNode, delParent4Children) {
    Node_t *tr = NULL;
    tr = Add(tr, 15);
    tr = Add(tr, 10);
    tr = Add(tr, 25);
    tr = Add(tr, 20);
    tr = Add(tr, 30);
    Del(tr, 25);
    ASSERT_EQ(30, tr->right->key);
    ASSERT_EQ(20, tr->right->left->key);
}

TEST(findNode, findRoot) {
    Node_t *tr = NULL;
    tr = Add(tr, 15);
    Node_t *tmp = Find(tr, tr->key);
    ASSERT_EQ(tr->key, tmp->key);
}

TEST(findNode, NotFindNode) {
    Node_t *tr = NULL;
    tr = Add(tr, 15);
    tr = Add(tr, 10);
    tr = Add(tr, 25);
    tr = Add(tr, 20);
    tr = Add(tr, 30);
    Node_t *tmp = Find(tr, 14);
    ASSERT_EQ(NULL, tmp);
}

TEST(findNodeWithSplay, SplayNode) {
    Node_t *tr = NULL;
    tr = Add(tr, 15);
    tr = Add(tr, 10);
    tr = Add(tr, 25);
    tr = Add(tr, 20);
    tr = Add(tr, 30);
    Node_t *tmp = Find(tr, 25);
    tr = Splay(tmp);
    ASSERT_EQ(25, tr->key);
    ASSERT_EQ(15, tr->left->key);
    ASSERT_EQ(30, tr->right->key);
    ASSERT_EQ(20, tr->left->right->key);
}
