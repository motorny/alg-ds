#include "pch.h"

tree_t createTestTree(void) {
    node_t* a, * b, * c, * d;
    tree_t tree;
    tree.t = SIZE;
    a = createNode(tree.t);
    b = createNode(tree.t);
    c = createNode(tree.t);
    d = createNode(tree.t);

    b->size = 1;
    b->values[0] = 1;
    b->child[0] = NULL;
    b->child[1] = NULL;
    b->child[2] = NULL;

    c->size = 1;
    c->values[0] = 3;
    c->child[0] = NULL;
    c->child[1] = NULL;
    c->child[2] = NULL;

    d->size = 1;
    d->values[0] = 6;
    d->child[0] = NULL;
    d->child[1] = NULL;
    a->child[2] = NULL;

    a->size = 2;
    a->values[0] = 2;
    a->values[1] = 5;
    a->child[0] = b;
    a->child[1] = c;
    a->child[2] = d;

    tree.root = a;
    return tree;
}

void deleteNode(node_t* node) {
    if (!node)
        return;
    for (int i = 0; i < node->size; i++)
        deleteNode(node->child[i]);
    free(node);
}

void deleteTree(tree_t* tree) {
    deleteNode(tree->root);
    tree->root = NULL;
}
TEST(searchElem, EmptyTree_returnFalse) {
    tree_t tree = { 0 };
    tree.t = SIZE;
    ASSERT_EQ(searchElem(tree, 1), FALSE);
}
TEST(searchElem, fillTreeElemDoesntExist_returnFalse) {
    tree_t tree = createTestTree();
    ASSERT_EQ(searchElem(tree, 4), FALSE);
    deleteTree(&tree);
}
TEST(searchElem, fillTreeElemExist_returnTrue) {
    tree_t tree = createTestTree();
    ASSERT_EQ(searchElem(tree, 1), TRUE);
    deleteTree(&tree);
}
TEST(deleteElem, EmptyTree_returnFalse) {
    tree_t tree = { 0 };
    tree.t = SIZE;
    ASSERT_EQ(deleteElem(&tree, 1), FALSE);
}
TEST(deleteElem, fillTreeElemDoesntExist_returnFalse) {
    tree_t tree = createTestTree();
    ASSERT_EQ(deleteElem(&tree, 4), FALSE);
    deleteTree(&tree);
}
TEST(deleteElem, fillTreeElemExist_returnTrue) {
    tree_t tree = createTestTree();
    ASSERT_EQ(deleteElem(&tree, 1), TRUE);
    deleteTree(&tree);
}
TEST(addElem, treeDoesntExist_returnFalse) {
    ASSERT_EQ(addElem(NULL, 1), FALSE);
}
TEST(addElem, EmptyTree_returnTrueInEmpty) {
    tree_t tree = { 0 };
    tree.t = SIZE;
    ASSERT_EQ(addElem(&tree, 1), -1);
    ASSERT_EQ(tree.root->values[0], 1);
}
TEST(addElem, fillTreeElemExist_returnFalse) {
    tree_t tree = createTestTree();
    ASSERT_EQ(addElem(&tree, 1), FALSE);
    deleteTree(&tree);
}
TEST(addElem, fillTreeElemDoesntExist_returnTRUE) {
    tree_t tree = createTestTree();
    ASSERT_EQ(addElem(&tree, 4), TRUE);
    deleteTree(&tree);
}