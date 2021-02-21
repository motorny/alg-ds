#include "pch.h"
extern"C" {
#include"../AVL/AVL.h"
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Insert, InsertingElem) {
    node_t* a = NULL;
    a = Insert(a, 17);
    EXPECT_EQ(17, a->key);
}

TEST(Insert, InsertingElem_CheckingRoot) {
    node_t* a = NULL;
    a = Insert(a, 17);
    a = Insert(a, 5);
    a = Insert(a, 12);
    EXPECT_EQ(12, a->key);
}

TEST(Insert, InseringElems) {
    node_t* a = NULL;                  //                4   
    a = Insert(a, 1);                  //              /   \ 
    a = Insert(a, 2);                  //             2     6  
    a = Insert(a, 3);                  //            / \   / \ 
    a = Insert(a, 4);                  //           1   3 5   8 
    a = Insert(a, 5);                  //                    / \ 
    a = Insert(a, 6);                  //                   7   9
    a = Insert(a, 7);
    a = Insert(a, 8);
    a = Insert(a, 9);
    EXPECT_EQ(4, a->key);
    EXPECT_EQ(2, a->left->key);
    EXPECT_EQ(1, a->left->left->key);
    EXPECT_EQ(9, a->right->right->right->key);
}

TEST(RemoveNode, RemovingRoot) {
    node_t* l = (node_t*)malloc(sizeof(node_t));
    l->key = 5;
    l->left = l->right = 0;
    l->height = 1;
    node_t* r = (node_t*)malloc(sizeof(node_t));
    r->key = 17;
    r->left = r->right = 0;
    r->height = 1;
    node_t * a = (node_t*)malloc(sizeof(node_t));
    a->key = 12;
    a->left = l;
    a->right = r;
    a->height = 1;
    a = RemoveNode(a, 12);
    EXPECT_EQ(17, a->key);
}

TEST(FindNodeByKey, CheckingReturningValues) {
    node_t* a, * b, * c, * d, * e, * f;
    node_t* root, *node;
    f = (node_t*)malloc(sizeof(node_t));
    f->height = 0;
    f->key = 6;
    f->left = f->right = NULL;

    e = (node_t*)malloc(sizeof(node_t));
    e->height = 0;
    e->key = 1;
    e->left = e->right = NULL;

    d = (node_t*)malloc(sizeof(node_t));
    d->height = 0;
    d->key = 3;
    d->left = e->right = NULL;

    c = (node_t*)malloc(sizeof(node_t));
    c->height = -1;
    c->key = 5;
    c->left = NULL;
    c->right = f;

    b = (node_t*)malloc(sizeof(node_t));
    b->height = 1;                               //         4
    b->key = 2;                                  //        / \ 
    b->left = e;                                 //       2   5 
    b->right = d;                                //      / \   \
                                                 //     1   3   6
    a = (node_t*)malloc(sizeof(node_t));         
    a->height = -1;
    a->key = 4;
    a->left = b;
    a->right = c;
    root = a;
   
    EXPECT_EQ(root, FindNodeByKey(root, 4));
    EXPECT_EQ(root->right, FindNodeByKey(root, 5));
    EXPECT_EQ(root->right->right, FindNodeByKey(root, 6));
    
}
