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

void disconnectSiblings(Node_t* left, Node_t* middle, Node_t* right) {
    if (left != NULL)
        left->rsib = right;
    middle->lsib = NULL; // TODO redundant
    middle->rsib = NULL; // TODO redundant
    if (right != NULL)
        right->lsib = left;
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

Node_t* mergeNode(Node_t* root, Node_t* left, Node_t* middle, Node_t* right) {
    root->left = left;
    root->middle = middle;
    root->right = right;
    left->parent = root;
    middle->parent = root;
    right->parent = root;
    root->lval = left->max_child;
    root->rval = middle->max_child;
    root->max_child = right->max_child;

    return root;
}

Node_t* insertTerminate(Node_t* root, int val) {
    if (root == NULL) {
        Node_t* node = newNode(val), * leaf = newNode(val);
        node->left = leaf;
        leaf->parent = node;
        return node;
    } else if (isTerminal(root)) {
        Node_t* node = newNode(val);
        if (root->rval == EMPTY && root->rval <= root->lval) { // one value
            if (root->right == NULL) { // one value, one leaf
                // leaves, which order is determined in the branches
                Node_t* a = root->left, * b = node; // last branch case (else)
                // siblings
                Node_t* lsib = root->left, * rsib = root->left->rsib; // last branch case (else)

                if (val <= root->lval) {
                    a = node, b = root->left;
                    lsib = root->left->lsib, rsib = root->left;
                }
                connectSiblings(lsib, node, rsib);
                root->left = a, root->right = b;
                root->lval = a->lval, root->max_child = b->max_child;
                a->parent = root, b->parent = root;
                return root;
            } else { // one value, two leaves
                // leaves, which order is determined in the branches
                Node_t* a = root->left, * b = root->right, * c = node; // last branch case (else)
                // siblings
                Node_t* lsib = root->right, * rsib = root->right->rsib; // last branch case (else)
                if (val <= root->lval) {
                    lsib = root->left->lsib, rsib = root->left;
                    a = node, b = root->left, c = root->right;
                } else if (val <= root->max_child && val > root->lval) {
                    lsib = root->left, rsib = root->right;
                    a = root->left, b = node, c = root->right;
                }
                connectSiblings(lsib, node, rsib);
                return mergeNode(root, a, b, c);
            }
        } else { // two values, three leaves
            // three nodes after splitting 2-valued, from left to right
            Node_t* X = newNode(EMPTY), * w = newNode(EMPTY), * Y = newNode(EMPTY);
            // leaves, which order is determined in the branches
            Node_t* a = root->left, * b = root->middle, * c = root->right, * d = node; // last branch case (else)
            // siblings
            Node_t* lsib = root->right, * rsib = root->right->rsib; // last branch case (else)
            if (val <= root->lval) {
                lsib = root->left->lsib, rsib = root->left;
                a = node, b = root->left, c = root->middle, d = root->right;
            } else if (val <= root->rval && val > root->lval) {
                lsib = root->left, rsib = root->middle;
                a = root->left, b = node, c = root->middle, d = root->right;
            } else if (val <= root->right->lval && val > root->rval) {
                lsib = root->middle, rsib = root->right;
                a = root->left, b = root->middle, c = node, d = root->right;
            }
            connectSiblings(lsib, node, rsib);
            return splitNode(X, w, Y, root, a, b, c, d);
        }
    } else // the node is not terminal
        return root;
}

Node_t* insertNode(Node_t* root, int val) {
    if (isTerminal(root))
        return insertTerminate(root, val);
    else {
        Node_t* node, * X = newNode(root->lval), * Y = newNode(root->rval);
        if (val <= root->lval) { // left regardless node being one or two valued
            node = insertNode(root->left, val);
            if (node->rval == EMPTY && root->rval == EMPTY) { // 1 in 1
                root = mergeNode(root, node->left, node->right, root->right);
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
                root = mergeNode(root, root->left, node->left, node->right);
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

void freeNode(Node_t* node) {
    if (node != NULL) {
        node->parent = NULL;
        node->lsib = NULL;
        node->rsib = NULL;
        node->left = NULL;
        node->middle = NULL;
        node->right = NULL;
        node->lval = EMPTY;
        node->rval = EMPTY;
        node->max_child = EMPTY;
        free(node);
    }
}

void freeTree(Node_t* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        freeNode(root);
    }
}

Node_t* deleteTerminal(Node_t* root, int val) {
    if (root == NULL || root->right == NULL && root->lval == val) { // null or one leaf
        freeTree(root);
        return NULL;
    } else if (isTerminal(root)) {
        if (root->rval == EMPTY && root->rval <= root->lval) { // 1-valued node
            if (val == root->lval) { // left leaf
                disconnectSiblings(root->left->lsib, root->left, root->right);
                freeNode(root->left);
                root->left = root->right;
                root->right = NULL;
                root->lval = root->left->lval;
                root->max_child = root->left->max_child;
            } else if (val == root->max_child) { // right leaf
                disconnectSiblings(root->left, root->right, root->right->rsib);
                freeNode(root->right);
                root->right = NULL;
                root->max_child = root->left->max_child;
            } // else unmodified root is returned
        } else { // 2-valued node
            if (val == root->lval || val == root->rval || val == root->max_child) {
                // leaves, which order is determined in the branches
                Node_t* a = root->left, * b = root->right; // middle node case
                // sibling, node to delete, sibling
                Node_t* lsib = root->left, * node = root->middle, * rsib = root->right; // middle node case
                if (val == root->lval) { // left
                    lsib = root->left->lsib, node = root->left, rsib = root->middle;
                    a = root->middle, b = root->right;
                } else if (val == root->max_child) { // right
                    lsib = root->middle, node = root->right, rsib = root->right->rsib;
                    a = root->left, b = root->middle;
                } // middle is default
                disconnectSiblings(lsib, node, rsib);
                freeNode(node);
                root->left = a, root->right = b, root->middle = NULL;
                root->lval = a->lval, root->max_child = b->max_child, root->rval = EMPTY;
            } // else unmodified root is returned
        }
    } // no value among the leaves or node is not terminal
    return root;
}

Node_t* deleteNode(Node_t* root, int val) {
    return root;
}