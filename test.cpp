#include "pch.h"
#include "/Users/79676/Desktop/Algh&Struct/Project1/Project1/tree.h"

TEST(test_push_case, push_one) {
    node_t* t = { 0 };
    push_node(&t, 1);
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(t->key, 1);
    EXPECT_EQ(t->parent, nullptr);
    EXPECT_EQ(t->right, nullptr);
    EXPECT_EQ(t->left, nullptr);
}

TEST(test_push_case, push_big_son) {
    node_t* t = { 0 };
    push_node(&t, 1);
    push_node(&t, 100);
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(t->key, 1);
    EXPECT_EQ(t->parent, nullptr);
    EXPECT_NE(t->right, nullptr);
    EXPECT_EQ(t->right->key, 100);
    EXPECT_EQ(t->left, nullptr);
}

TEST(test_push_case, push_lil_son) {
    node_t* t = { 0 };
    push_node(&t, 1);
    push_node(&t, 0);
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(t->key, 1);
    EXPECT_EQ(t->parent, nullptr);
    EXPECT_NE(t->left, nullptr);
    EXPECT_EQ(t->left->key, 0);
    EXPECT_EQ(t->right, nullptr);
}

TEST(test_push_case, push_all_children) {
    node_t* t = { 0 };
    push_node(&t, 1);
    push_node(&t, 0);
    push_node(&t, 100);
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(t->key, 1);
    EXPECT_EQ(t->parent, nullptr);
    EXPECT_NE(t->left, nullptr);
    EXPECT_EQ(t->left->key, 0);
    EXPECT_NE(t->right, nullptr);
    EXPECT_EQ(t->right->key, 100);
}

TEST(test_delete_case, you_killed_my_father) {
    node_t* t = { 0 };
    push_node(&t, 1);
    push_node(&t, 100);
    del_node(&t, 1);
    EXPECT_EQ(t->key, 100);
    EXPECT_EQ(t->parent, nullptr);
}

TEST(test_delete_case, no_i_am_your_father){
    node_t* t = { 0 };
    push_node(&t, 0);
    push_node(&t, 1);
    push_node(&t, 100);
    del_node(&t, 1);
    EXPECT_EQ(t->right->parent->key, 0);
}

TEST(test_delete_case, delete_hard) {
    node_t* t = { 0 };
    push_node(&t, 1);
    push_node(&t, 6);
    push_node(&t, 8);
    push_node(&t, 2);
    push_node(&t, 3);
    push_node(&t, 4);
    del_node(&t, 6);
    EXPECT_EQ(t->right->key, 3);
}

TEST(test_delete_case, delete_hard2) {
    node_t* t = { 0 };
    push_node(&t, 1);
    push_node(&t, 6);
    push_node(&t, 8);
    push_node(&t, 3);
    push_node(&t, 2);
    push_node(&t, 4);
    del_node(&t, 6);
    EXPECT_EQ(t->right->key, 4);
}

TEST(test_find_case, find_nothing) {
    node_t* t = { 0 };
    push_node(&t, 1);
    push_node(&t, 6);
    push_node(&t, 8);
    push_node(&t, 3);
    push_node(&t, 2);
    push_node(&t, 4);
    EXPECT_EQ(find_node(t, 5),0);
}

TEST(test_find_case, find_node_please) {
    node_t* t = { 0 };
    push_node(&t, 1);
    push_node(&t, 6);
    push_node(&t, 8);
    push_node(&t, 3);
    push_node(&t, 5);
    push_node(&t, 2);
    push_node(&t, 4);
    EXPECT_EQ(find_node(t, 5), 1);
}

TEST(test_4_F_lab, get_elem) {
    node_t* t = { 0 };
    node_t* f = { 0 };
    node_t* n = { 0 };
    push_node(&t, 1);
    push_node(&t, 6);
    push_node(&t, 8);
    push_node(&t, 3);
    push_node(&t, 5);
    push_node(&t, 2);
    push_node(&t, 4);
    f = find_elem(t, 8);
    n = find_elem_k_lower(f, 6);
    EXPECT_EQ(n->parent->key, 3);
    EXPECT_EQ(n->left, nullptr);
    EXPECT_EQ(n->right, nullptr);
    EXPECT_EQ(n->key, 8 - 6);
}