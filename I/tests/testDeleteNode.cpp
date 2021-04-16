#include <gtest/gtest.h>
#include <vector>

#include "../23Tree.h"

class DeleteNode : public testing::Test {
protected:
    Node_t* root = nullptr;

    DeleteNode() = default;

    ~DeleteNode() override = default; //{freeTree(root);}

    Node_t* insertNodes(const std::vector<int> &vals) {
        for (auto i: vals)
            root = insertNode(root, i);
        return root;
    }
};

// tests for 1-1 case
TEST_F(DeleteNode, 4Nodes_LeftLeft) {
    root = insertNodes({0, 1, 2, 3});
    root = deleteNode(root, 0);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, 2);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 1);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 2);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 2);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteNode, 4Nodes_LeftRight) {
    root = insertNodes({0, 1, 2, 3});
    root = deleteNode(root, 1);

    ASSERT_EQ(root->lval, 0);
    ASSERT_EQ(root->rval, 2);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 0);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 2);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 2);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteNode, 4Nodes_RightLeft) {
    root = insertNodes({0, 1, 2, 3});
    root = deleteNode(root, 2);

    ASSERT_EQ(root->lval, 0);
    ASSERT_EQ(root->rval, 1);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 0);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 1);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 1);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteNode, 4Nodes_RightRight) {
    root = insertNodes({0, 1, 2, 3});
    root = deleteNode(root, 3);

    ASSERT_EQ(root->lval, 0);
    ASSERT_EQ(root->rval, 1);
    ASSERT_EQ(root->max_child, 2);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 0);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 1);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 1);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 2);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 2);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}

// tests for 2-1 case
TEST_F(DeleteNode, 5Nodes_Left2to1) {
    root = insertNodes({1, 2, 3, 4, 0}); // 2-valued node on the left
    root = deleteNode(root, 2); // root->lval should updated

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 4);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 4);

    Node_t* lleft = root->left->left, * lright = root->left->right,
            * rleft = root->right->left, * rright = root->right->right;

    ASSERT_EQ(lleft->lval, 0);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 0);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lright);

    ASSERT_EQ(lright->lval, 1);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 1);
    ASSERT_EQ(lright->lsib, lleft);
    ASSERT_EQ(lright->rsib, rleft);

    ASSERT_EQ(rleft->lval, 3);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 3);
    ASSERT_EQ(rleft->lsib, lright);
    ASSERT_EQ(rleft->rsib, rright);

    ASSERT_EQ(rright->lval, 4);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 4);
    ASSERT_EQ(rright->lsib, rleft);
    ASSERT_EQ(rright->rsib, nullptr);
}

TEST_F(DeleteNode, 5Nodes_Right2to1) {
    root = insertNodes({0, 1, 2, 3, 4}); // 2-valued node on the right
    root = deleteNode(root, 4); // root->max_child should updated

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);

    ASSERT_EQ(root->right->lval, 2);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 3);

    Node_t* lleft = root->left->left, * lright = root->left->right,
            * rleft = root->right->left, * rright = root->right->right;

    ASSERT_EQ(lleft->lval, 0);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 0);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lright);

    ASSERT_EQ(lright->lval, 1);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 1);
    ASSERT_EQ(lright->lsib, lleft);
    ASSERT_EQ(lright->rsib, rleft);

    ASSERT_EQ(rleft->lval, 2);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 2);
    ASSERT_EQ(rleft->lsib, lright);
    ASSERT_EQ(rleft->rsib, rright);

    ASSERT_EQ(rright->lval, 3);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 3);
    ASSERT_EQ(rright->lsib, rleft);
    ASSERT_EQ(rright->rsib, nullptr);
}

// tests for 1-2 case
TEST_F(DeleteNode, 6Nodes_Left1to2) {
    root = insertNodes({0, 1, 2, 3, 4, 5});
    root = deleteNode(root, 1);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 5);
    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, 2);
    ASSERT_EQ(root->left->max_child, 3);
    ASSERT_EQ(root->left->parent, root);

    ASSERT_EQ(root->right->lval, 4);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 5);
    ASSERT_EQ(root->right->parent, root);

    Node_t* a = root->left->left, * b = root->left->middle, * c = root->left->right,
            * d = root->right->left, * e = root->right->right;

    ASSERT_EQ(a->lval, 0);
    ASSERT_EQ(a->rval, EMPTY);
    ASSERT_EQ(a->max_child, 0);
    ASSERT_EQ(a->parent, root->left);
    ASSERT_EQ(a->lsib, nullptr);
    ASSERT_EQ(a->rsib, b);

    ASSERT_EQ(b->lval, 2);
    ASSERT_EQ(b->rval, EMPTY);
    ASSERT_EQ(b->max_child, 2);
    ASSERT_EQ(b->parent, root->left);
    ASSERT_EQ(b->lsib, a);
    ASSERT_EQ(b->rsib, c);

    ASSERT_EQ(c->lval, 3);
    ASSERT_EQ(c->rval, EMPTY);
    ASSERT_EQ(c->max_child, 3);
    ASSERT_EQ(c->parent, root->left);
    ASSERT_EQ(c->lsib, b);
    ASSERT_EQ(c->rsib, d);

    ASSERT_EQ(d->lval, 4);
    ASSERT_EQ(d->rval, EMPTY);
    ASSERT_EQ(d->max_child, 4);
    ASSERT_EQ(d->parent, root->right);
    ASSERT_EQ(d->lsib, c);
    ASSERT_EQ(d->rsib, e);

    ASSERT_EQ(e->lval, 5);
    ASSERT_EQ(e->rval, EMPTY);
    ASSERT_EQ(e->max_child, 5);
    ASSERT_EQ(e->parent, root->right);
    ASSERT_EQ(e->lsib, d);
    ASSERT_EQ(e->rsib, nullptr);
}

TEST_F(DeleteNode, 6Nodes_Middle1to2) {
    root = insertNodes({0, 1, 2, 3, 4, 5});
    root = deleteNode(root, 3);

    ASSERT_EQ(root->lval, 2);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 5);
    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, 1);
    ASSERT_EQ(root->left->max_child, 2);
    ASSERT_EQ(root->left->parent, root);

    ASSERT_EQ(root->right->lval, 4);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 5);
    ASSERT_EQ(root->right->parent, root);

    Node_t* a = root->left->left, * b = root->left->middle, * c = root->left->right,
            * d = root->right->left, * e = root->right->right;

    ASSERT_EQ(a->lval, 0);
    ASSERT_EQ(a->rval, EMPTY);
    ASSERT_EQ(a->max_child, 0);
    ASSERT_EQ(a->parent, root->left);
    ASSERT_EQ(a->lsib, nullptr);
    ASSERT_EQ(a->rsib, b);

    ASSERT_EQ(b->lval, 1);
    ASSERT_EQ(b->rval, EMPTY);
    ASSERT_EQ(b->max_child, 1);
    ASSERT_EQ(b->parent, root->left);
    ASSERT_EQ(b->lsib, a);
    ASSERT_EQ(b->rsib, c);

    ASSERT_EQ(c->lval, 2);
    ASSERT_EQ(c->rval, EMPTY);
    ASSERT_EQ(c->max_child, 2);
    ASSERT_EQ(c->parent, root->left);
    ASSERT_EQ(c->lsib, b);
    ASSERT_EQ(c->rsib, d);

    ASSERT_EQ(d->lval, 4);
    ASSERT_EQ(d->rval, EMPTY);
    ASSERT_EQ(d->max_child, 4);
    ASSERT_EQ(d->parent, root->right);
    ASSERT_EQ(d->lsib, c);
    ASSERT_EQ(d->rsib, e);

    ASSERT_EQ(e->lval, 5);
    ASSERT_EQ(e->rval, EMPTY);
    ASSERT_EQ(e->max_child, 5);
    ASSERT_EQ(e->parent, root->right);
    ASSERT_EQ(e->lsib, d);
    ASSERT_EQ(e->rsib, nullptr);
}

TEST_F(DeleteNode, 6Nodes_Right1to2) {
    root = insertNodes({0, 1, 2, 3, 4, 5});
    root = deleteNode(root, 5);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 4);
    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->parent, root);

    ASSERT_EQ(root->right->lval, 2);
    ASSERT_EQ(root->right->rval, 3);
    ASSERT_EQ(root->right->max_child, 4);
    ASSERT_EQ(root->right->parent, root);

    Node_t* a = root->left->left, * b = root->left->right,
            * c = root->right->left, * d = root->right->middle, * e = root->right->right;

    ASSERT_EQ(a->lval, 0);
    ASSERT_EQ(a->rval, EMPTY);
    ASSERT_EQ(a->max_child, 0);
    ASSERT_EQ(a->parent, root->left);
    ASSERT_EQ(a->lsib, nullptr);
    ASSERT_EQ(a->rsib, b);

    ASSERT_EQ(b->lval, 1);
    ASSERT_EQ(b->rval, EMPTY);
    ASSERT_EQ(b->max_child, 1);
    ASSERT_EQ(b->parent, root->left);
    ASSERT_EQ(b->lsib, a);
    ASSERT_EQ(b->rsib, c);

    ASSERT_EQ(c->lval, 2);
    ASSERT_EQ(c->rval, EMPTY);
    ASSERT_EQ(c->max_child, 2);
    ASSERT_EQ(c->parent, root->right);
    ASSERT_EQ(c->lsib, b);
    ASSERT_EQ(c->rsib, d);

    ASSERT_EQ(d->lval, 3);
    ASSERT_EQ(d->rval, EMPTY);
    ASSERT_EQ(d->max_child, 3);
    ASSERT_EQ(d->parent, root->right);
    ASSERT_EQ(d->lsib, c);
    ASSERT_EQ(d->rsib, e);

    ASSERT_EQ(e->lval, 4);
    ASSERT_EQ(e->rval, EMPTY);
    ASSERT_EQ(e->max_child, 4);
    ASSERT_EQ(e->parent, root->right);
    ASSERT_EQ(e->lsib, d);
    ASSERT_EQ(e->rsib, nullptr);
}

// tests for 2-2 case
TEST_F(DeleteNode, 7Nodes_Left2to2) {
    root = insertNodes({1, 2, 3, 4, 5, 6, 0}); // 2-valued node on the left
    root = deleteNode(root, 2); // root->lval should become 1

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, 4);
    ASSERT_EQ(root->max_child, 6);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->parent, root);

    ASSERT_EQ(root->middle->lval, 3);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 4);
    ASSERT_EQ(root->middle->parent, root);

    ASSERT_EQ(root->right->lval, 5);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 6);
    ASSERT_EQ(root->right->parent, root);

    Node_t* a = root->left->left, *b = root->left->right,
    *c = root->middle->left, *d = root->middle->right,
    *e = root->right->left, *f = root->right->right;

    ASSERT_EQ(a->lval, 0);
    ASSERT_EQ(a->rval, EMPTY);
    ASSERT_EQ(a->max_child, 0);
    ASSERT_EQ(a->parent, root->left);
    ASSERT_EQ(a->lsib, nullptr);
    ASSERT_EQ(a->rsib, b);

    ASSERT_EQ(b->lval, 1);
    ASSERT_EQ(b->rval, EMPTY);
    ASSERT_EQ(b->max_child, 1);
    ASSERT_EQ(b->parent, root->left);
    ASSERT_EQ(b->lsib, a);
    ASSERT_EQ(b->rsib, c);

    ASSERT_EQ(c->lval, 3);
    ASSERT_EQ(c->rval, EMPTY);
    ASSERT_EQ(c->max_child, 3);
    ASSERT_EQ(c->parent, root->middle);
    ASSERT_EQ(c->lsib, b);
    ASSERT_EQ(c->rsib, d);

    ASSERT_EQ(d->lval, 4);
    ASSERT_EQ(d->rval, EMPTY);
    ASSERT_EQ(d->max_child, 4);
    ASSERT_EQ(d->parent, root->middle);
    ASSERT_EQ(d->lsib, c);
    ASSERT_EQ(d->rsib, e);

    ASSERT_EQ(e->lval, 5);
    ASSERT_EQ(e->rval, EMPTY);
    ASSERT_EQ(e->max_child, 5);
    ASSERT_EQ(e->parent, root->right);
    ASSERT_EQ(e->lsib, d);
    ASSERT_EQ(e->rsib, f);

    ASSERT_EQ(f->lval, 6);
    ASSERT_EQ(f->rval, EMPTY);
    ASSERT_EQ(f->max_child, 6);
    ASSERT_EQ(f->parent, root->right);
    ASSERT_EQ(f->lsib, e);
    ASSERT_EQ(f->rsib, nullptr);
}

TEST_F(DeleteNode, 7Nodes_Middle2to2) {
    root = insertNodes({0, 1, 2, 4, 5, 6, 3}); // 2-valued node on the middle
    root = deleteNode(root, 4); // root->rval should become 3

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, 3);
    ASSERT_EQ(root->max_child, 6);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->parent, root);

    ASSERT_EQ(root->middle->lval, 2);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 3);
    ASSERT_EQ(root->middle->parent, root);

    ASSERT_EQ(root->right->lval, 5);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 6);
    ASSERT_EQ(root->right->parent, root);

    Node_t* a = root->left->left, *b = root->left->right,
            *c = root->middle->left, *d = root->middle->right,
            *e = root->right->left, *f = root->right->right;

    ASSERT_EQ(a->lval, 0);
    ASSERT_EQ(a->rval, EMPTY);
    ASSERT_EQ(a->max_child, 0);
    ASSERT_EQ(a->parent, root->left);
    ASSERT_EQ(a->lsib, nullptr);
    ASSERT_EQ(a->rsib, b);

    ASSERT_EQ(b->lval, 1);
    ASSERT_EQ(b->rval, EMPTY);
    ASSERT_EQ(b->max_child, 1);
    ASSERT_EQ(b->parent, root->left);
    ASSERT_EQ(b->lsib, a);
    ASSERT_EQ(b->rsib, c);

    ASSERT_EQ(c->lval, 2);
    ASSERT_EQ(c->rval, EMPTY);
    ASSERT_EQ(c->max_child, 2);
    ASSERT_EQ(c->parent, root->middle);
    ASSERT_EQ(c->lsib, b);
    ASSERT_EQ(c->rsib, d);

    ASSERT_EQ(d->lval, 3);
    ASSERT_EQ(d->rval, EMPTY);
    ASSERT_EQ(d->max_child, 3);
    ASSERT_EQ(d->parent, root->middle);
    ASSERT_EQ(d->lsib, c);
    ASSERT_EQ(d->rsib, e);

    ASSERT_EQ(e->lval, 5);
    ASSERT_EQ(e->rval, EMPTY);
    ASSERT_EQ(e->max_child, 5);
    ASSERT_EQ(e->parent, root->right);
    ASSERT_EQ(e->lsib, d);
    ASSERT_EQ(e->rsib, f);

    ASSERT_EQ(f->lval, 6);
    ASSERT_EQ(f->rval, EMPTY);
    ASSERT_EQ(f->max_child, 6);
    ASSERT_EQ(f->parent, root->right);
    ASSERT_EQ(f->lsib, e);
    ASSERT_EQ(f->rsib, nullptr);
}

TEST_F(DeleteNode, 7Nodes_Right2to2) {
    root = insertNodes({0, 1, 2, 3, 4, 5, 6}); // 2-valued node on the right
    root = deleteNode(root, 6); // root->lval should become 5

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, 3);
    ASSERT_EQ(root->max_child, 5);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->parent, root);

    ASSERT_EQ(root->middle->lval, 2);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 3);
    ASSERT_EQ(root->middle->parent, root);

    ASSERT_EQ(root->right->lval, 4);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 5);
    ASSERT_EQ(root->right->parent, root);

    Node_t* a = root->left->left, *b = root->left->right,
            *c = root->middle->left, *d = root->middle->right,
            *e = root->right->left, *f = root->right->right;

    ASSERT_EQ(a->lval, 0);
    ASSERT_EQ(a->rval, EMPTY);
    ASSERT_EQ(a->max_child, 0);
    ASSERT_EQ(a->parent, root->left);
    ASSERT_EQ(a->lsib, nullptr);
    ASSERT_EQ(a->rsib, b);

    ASSERT_EQ(b->lval, 1);
    ASSERT_EQ(b->rval, EMPTY);
    ASSERT_EQ(b->max_child, 1);
    ASSERT_EQ(b->parent, root->left);
    ASSERT_EQ(b->lsib, a);
    ASSERT_EQ(b->rsib, c);

    ASSERT_EQ(c->lval, 2);
    ASSERT_EQ(c->rval, EMPTY);
    ASSERT_EQ(c->max_child, 2);
    ASSERT_EQ(c->parent, root->middle);
    ASSERT_EQ(c->lsib, b);
    ASSERT_EQ(c->rsib, d);

    ASSERT_EQ(d->lval, 3);
    ASSERT_EQ(d->rval, EMPTY);
    ASSERT_EQ(d->max_child, 3);
    ASSERT_EQ(d->parent, root->middle);
    ASSERT_EQ(d->lsib, c);
    ASSERT_EQ(d->rsib, e);

    ASSERT_EQ(e->lval, 4);
    ASSERT_EQ(e->rval, EMPTY);
    ASSERT_EQ(e->max_child, 4);
    ASSERT_EQ(e->parent, root->right);
    ASSERT_EQ(e->lsib, d);
    ASSERT_EQ(e->rsib, f);

    ASSERT_EQ(f->lval, 5);
    ASSERT_EQ(f->rval, EMPTY);
    ASSERT_EQ(f->max_child, 5);
    ASSERT_EQ(f->parent, root->right);
    ASSERT_EQ(f->lsib, e);
    ASSERT_EQ(f->rsib, nullptr);
}
