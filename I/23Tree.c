#include <stdio.h>
#include <stdlib.h>
#include "23Tree.h"

int isTerminal(Node_t* node) { // only left is considered, since without it there won't be middle and right
    return node != NULL && (node->left != NULL && node->left->left == NULL ||
                            node->right != NULL && node->right->left == NULL ||
                            node->middle != NULL && node->middle->left == NULL) || node == NULL;
}

void connectSiblings(Node_t* left, Node_t* middle, Node_t* right) {
    if (left != NULL)
        left->rsib = middle;
    middle->lsib = left;
    middle->rsib = right;
    if (right != NULL)
        right->lsib = middle;
}

Node_t* newNode(int val) {
    Node_t* node = (Node_t*) malloc(sizeof(Node_t));
    if (node != NULL) {
        node->left = NULL;
        node->right = NULL;
        node->middle = NULL;
        node->parent = NULL;
        node->lval = val;
        node->rval = EMPTY;
        node->lsib = NULL;
        node->rsib = NULL;
        node->max_child = val;
    }
    return node;
}

Node_t* insertTerminate(Node_t* root, int val) {
    if (root == NULL) {
        Node_t* node = newNode(val), * leaf = newNode(val);
        node->left = leaf;
        leaf->parent = node;
        return node;
    } else if (isTerminal(root)) {
        if (root->rval == EMPTY && root->rval <= root->lval) { // one value
            if (root->right == NULL) { // one value, one leaf
                Node_t* node = newNode(val);
                node->parent = root;
                if (val <= root->lval) {
                    connectSiblings(root->left->lsib, node, root->left);

                    root->right = root->left;
                    root->left = node;
                    root->lval = node->lval;
                    root->max_child = root->right->max_child;
                } else {
                    connectSiblings(root->left, node, root->left->rsib);

                    root->right = node;
                    root->max_child = root->right->max_child;
                }
                return root;
            } else { // one value, two leaves
                Node_t* node = newNode(val);
                node->parent = root;
                if (val <= root->left->lval) {
                    connectSiblings(root->left->lsib, node, root->left);
                    root->middle = root->left;
                    root->left = node;
                    root->max_child = root->right->max_child;
                    root->lval = node->lval;
                    root->rval = root->middle->max_child;
                } else if (val <= root->right->lval && val > root->left->lval) {
                    connectSiblings(root->left, node, root->right);
                    root->middle = node;
                    root->lval = root->left->lval;
                    root->rval = node->max_child;
                    root->max_child = root->right->max_child;
                } else {
                    connectSiblings(root->right, node, root->right->rsib);
                    root->middle = root->right;
                    root->right = node;
                    root->rval = root->middle->max_child;
                    root->max_child = root->right->max_child;
                }
                return root;
            }
        } else { // two values, three leaves
            Node_t* node = newNode(val);
            Node_t* L, * M, * R;
            if (val <= root->lval) {
                L = newNode(val);
                R = newNode(root->rval);
                connectSiblings(root->left->lsib, node, root->left);
                L->left = node;
                L->right = root->left;
                node->parent = L;
                root->left->parent = L;
                L->max_child = L->right->max_child;

                R->left = root->middle;
                R->right = root->right;
                root->middle->parent = R;
                root->right->parent = R;
                R->max_child = R->right->max_child;

                M = newNode(L->max_child);
                M->max_child = R->max_child;
                L->parent = M;
                R->parent = M;
                M->left = L;
                M->right = R;
                free(root);
                return M;
            } else if (val <= root->rval && val > root->lval) {
                L = newNode(root->lval);
                R = newNode(root->rval);
                connectSiblings(root->left, node, root->middle);
                L->left = root->left;
                L->right = node;
                node->parent = L;
                root->left->parent = L;
                L->max_child = L->right->max_child;

                R->left = root->middle;
                R->right = root->right;
                root->middle->parent = R;
                root->right->parent = R;
                R->max_child = R->right->max_child;

                M = newNode(L->max_child);
                M->max_child = R->max_child;
                L->parent = M;
                R->parent = M;
                M->left = L;
                M->right = R;
                free(root);
                return M;
            } else if (val <= root->right->lval && val > root->rval) {
                L = newNode(root->lval);
                R = newNode(val);
                connectSiblings(root->middle, node, root->right);
                L->left = root->left;
                L->right = root->middle;
                root->middle->parent = L;
                root->left->parent = L;
                L->max_child = L->right->max_child;

                R->left = node;
                R->right = root->right;
                node->parent = R;
                root->right->parent = R;
                R->max_child = R->right->max_child;

                M = newNode(L->max_child);
                M->max_child = R->max_child;
                L->parent = M;
                R->parent = M;
                M->left = L;
                M->right = R;
                free(root);
                return M;
            } else {
                L = newNode(root->lval);
                R = newNode(root->max_child);
                connectSiblings(root->right, node, root->right->rsib);
                L->left = root->left;
                L->right = root->middle;
                root->middle->parent = L;
                root->left->parent = L;
                L->max_child = L->right->max_child;

                R->left = root->right;
                R->right = node;
                node->parent = R;
                root->right->parent = R;
                R->max_child = R->right->max_child;

                M = newNode(L->max_child);
                M->max_child = R->max_child;
                L->parent = M;
                R->parent = M;
                M->left = L;
                M->right = R;
                free(root);
                return M;
            }
        }
    } else
        return root;
}

Node_t* splitNode(Node_t* X, Node_t* node, Node_t* Y, Node_t* root, Node_t* a, Node_t* b, Node_t* c, Node_t* d) {
    node->parent = root->parent;
    node->lval = b->max_child;
    node->max_child = d->max_child;

    node->left = X;
    node->right = Y;
    X->parent = node;
    Y->parent = node;

    X->left = a;
    X->right = b;
    X->lval = a->max_child;
    X->max_child = b->max_child;
    a->parent = X;
    b->parent = X;

    Y->left = c;
    Y->right = d;
    Y->lval = c->max_child;
    Y->max_child = d->max_child;
    c->parent = Y;
    d->parent = Y;

    free(root);
    return node;
}

Node_t* insertNode(Node_t* root, int val) {
    if (isTerminal(root))
        return insertTerminate(root, val);
    else {
        Node_t* node, * X = newNode(root->lval), * Y = newNode(root->rval);
        if (val <= root->lval) { // left regardless node being one or two valued
            node = insertNode(root->left, val);
            if (node->rval == EMPTY && root->rval == EMPTY) { // 1 in 1
                root->left = node->left;
                root->middle = node->right;
                node->left->parent = root;
                node->right->parent = root;
                root->lval = root->left->max_child;
                root->rval = root->middle->max_child;
                free(node); // it was merged into two valued node
                return root;
            } else if (node->rval == EMPTY && root->rval != EMPTY) { // 1 in 2
                return splitNode(node, X, Y, root, node->left, node->right, root->middle, root->right);
            } else { // 2 in 2 or 1
                root->lval = node->max_child;
                return root;
            }
        } else if (root->rval != EMPTY && val <= root->rval && val > root->lval) { // middle
            node = insertNode(root->middle, val);
            if (node->rval != EMPTY) { // 2 in 2
                root->rval = node->max_child;
                return root;
            } else { // 1 in 2
                return splitNode(X, node, Y, root, root->left, node->left, node->right, root->right);
            }
        } else { // right regardless node being one or two valued
            node = insertNode(root->right, val);
            if (node->rval == EMPTY && root->rval == EMPTY) { // 1 in 1
                root->middle = node->left;
                root->right = node->right;
                root->rval = node->left->max_child;
                root->max_child = node->max_child;
                node->left->parent = root;
                node->right->parent = root;
                free(node); // merged into 2 valued node
                return root;
            } else if (node->rval == EMPTY && root->rval != EMPTY) { // 1 in 2
                return splitNode(X, Y, node, root, root->left, root->middle, node->left, node->right);
            } else { // 2 in 2 or 1
                root->max_child = node->max_child;
                return root;
            }
        }
    }
}