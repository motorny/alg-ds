#include "pch.h"
extern"C" {
#include "avl.h"
}

TEST(AddNote, OneNode) {
    node_t* a = NULL;
    a = AddNode(a, 1);
    EXPECT_EQ(1, a->val);
}

TEST(AddNote, CheckRoot) {
    node_t* a = NULL;
    a = AddNode(a, 1);
    a = AddNode(a, 2);
    a = AddNode(a, 3);
    EXPECT_EQ(2, a->val);
}

TEST(AddNote, CheckElems) {
    node_t* a = NULL;                 
    a = AddNode(a, 1);                
    a = AddNode(a, 2);                 
    a = AddNode(a, 3);               
    a = AddNode(a, 4);                 
    a = AddNode(a, 5);                 
    a = AddNode(a, 6);                 
    a = AddNode(a, 7);
    a = AddNode(a, 8);
    a = AddNode(a, 9);
    EXPECT_EQ(4, a->val);
    EXPECT_EQ(2, a->left->val);
    EXPECT_EQ(6, a->right->val);
    EXPECT_EQ(1, a->left->left->val);
    EXPECT_EQ(3, a->left->right->val);
    EXPECT_EQ(5, a->right->left->val);
    EXPECT_EQ(8, a->right->right->val);
    EXPECT_EQ(7, a->right->right->left->val);
    EXPECT_EQ(9, a->right->right->right->val);
}

TEST(RemoveNode, OneNode) {
    node_t* a = (node_t*)malloc(sizeof(node_t));
    a->val = 1;
    a->left = a->right = 0;
    a->height = 1;
    RemoveNode(a, 1);

    ASSERT_NE(a->val, 1);
}

TEST(RemoveNode, RemovingRoot) {
    node_t* a = (node_t*)malloc(sizeof(node_t));
    node_t* l = (node_t*)malloc(sizeof(node_t));
    node_t* r = (node_t*)malloc(sizeof(node_t));

    l->val = 1;
    l->left = l->right = 0;
    l->height = 1;

    r->val = 3;
    r->left = r->right = 0;
    r->height = 1;

    a->val = 2;
    a->left = l;
    a->right = r;
    a->height = 1;

    a = RemoveNode(a, 2);
    EXPECT_EQ(3, a->val);
    EXPECT_EQ(1, a->left->val);
}

TEST(FindNode, EmptyTree) {
    node_t* tree = NULL;
    ASSERT_EQ(0, FindNode(tree, 0));
}

TEST(FindNode, OneNode) {
    node_t* a = (node_t*)malloc(sizeof(node_t));
    a->val = 1;
    a->left = a->right = 0;
    a->height = 1;
    ASSERT_NE(FindNode(a, 1), 0);
    EXPECT_EQ(1, FindNode(a, 1));
}

TEST(FindNode, CheckElems) {
    node_t* a = (node_t*)malloc(sizeof(node_t)), *b = (node_t*)malloc(sizeof(node_t)), *c = (node_t*)malloc(sizeof(node_t)),
        *d = (node_t*)malloc(sizeof(node_t)), *e = (node_t*)malloc(sizeof(node_t)), *f = (node_t*)malloc(sizeof(node_t));
    node_t* root;
    f->height = 0;
    f->val = 6;
    f->left = f->right = NULL;

    e->height = 0;
    e->val = 1;
    e->left = e->right = NULL;

    d->height = 0;
    d->val = 3;
    d->left = e->right = NULL;

    c->height = 1;
    c->val = 5;
    c->left = NULL;
    c->right = f;

    b->height = 1;                             
    b->val = 2;                                
    b->left = e;                                 
    b->right = d;                             

    a->height = 2;
    a->val = 4;
    a->left = b;
    a->right = c;
    root = a;

    EXPECT_EQ(1, FindNode(root, 4));
    EXPECT_EQ(1, FindNode(root, 2));
    EXPECT_EQ(1, FindNode(root, 5));
    EXPECT_EQ(1, FindNode(root, 1));
    EXPECT_EQ(1, FindNode(root, 3));
    EXPECT_EQ(1, FindNode(root, 6));

}
