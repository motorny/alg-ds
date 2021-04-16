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
        // terminal and value among leaves
    } else if (isTerminal(root) && (val == root->lval || val == root->rval || val == root->max_child)) {
        int isOneValued = root->rval == EMPTY && root->rval <= root->lval;
        // leaves, which order is determined in the branches
        Node_t* a = root->left, * b = isOneValued ? NULL : root->middle; // right case
        // sibling, node to delete, sibling
        // right case
        Node_t* lsib = isOneValued ? root->left : root->middle, * node = root->right, * rsib = root->right->rsib;

        if (val == root->lval) {
            a = isOneValued ? root->right : root->middle, b = isOneValued ? NULL : root->right;
            lsib = root->left->lsib, node = root->left, rsib = isOneValued ? root->right : root->middle;
        } else if (!isOneValued && val == root->rval) {
            a = root->left, b = root->right;
            lsib = root->left, node = root->middle, rsib = root->right;
        }
        disconnectSiblings(lsib, node, rsib);
        freeNode(node);
        root->left = a, root->right = b, root->middle = NULL;
        root->lval = a->lval, root->max_child = (b == NULL ? a->max_child : b->max_child), root->rval = EMPTY;
    } // no value among the leaves or node is not terminal
    return root;
}

Node_t* deleteNode(Node_t* root, int val) {
    if (isTerminal(root))
        return deleteTerminal(root, val);
    else {
        Node_t* node;
        if (root->rval == EMPTY && root->rval <= root->lval) { // 1-valued root
            if (val <= root->lval) {
                node = deleteNode(root->left, val);
                if (node->right == NULL) { // one leaf
                    Node_t* toDelete = root->right;
                    root = mergeNode(root, node->left, root->right->left, root->right->right);
                    freeNode(node);
                    freeNode(toDelete);
                    return root;
                } else { // two leaves
                    root->lval = root->left->max_child;
                    return root;
                }
            } else {
                node = deleteNode(root->right, val);
                if (node->right == NULL) { // one leaf
                    Node_t* toDelete = root->left;
                    root = mergeNode(root, root->left->left, root->left->right, node->left);
                    freeNode(node);
                    freeNode(toDelete);
                    return root;
                } else { // two leaves
                    root->max_child = root->right->max_child;
                    return root;
                }
            }
        } else { // 2-valued root
            if (val <= root->lval) {
                node = deleteNode(root->left, val);
                if (node->right == NULL) { // one leaf
                    Node_t* toDelete = root->middle;
                    node = mergeNode(node, node->left, root->middle->left, root->middle->right);
                    freeNode(toDelete);
                    root->left = node;
                    node->parent = root;
                    root->middle = NULL;
                    root->rval = EMPTY;
                    root->lval = node->max_child;
                    return root;
                } else { // two leaves
                    root->lval = node->max_child;
                    return root;
                }
            } else if (val <= root->rval && val > root->lval) {
                node = deleteNode(root->middle, val);
                if (node->right == NULL) {
                    Node_t* toDelete = root->left;
                    node = mergeNode(node, root->left->left, root->left->right, node->left);
                    freeNode(toDelete);
                    root->left = node;
                    node->parent = root;
                    root->middle = NULL;
                    root->rval = EMPTY;
                    root->lval = node->max_child;
                    return root;
                } else { // two leaves
                    root->rval = node->max_child;
                    return root;
                }
            } else {
                node = deleteNode(root->right, val);
                if (node->right == NULL) {
                    Node_t* toDelete = root->middle;
                    node = mergeNode(node, root->middle->left, root->middle->right, node->left);
                    freeNode(toDelete);
                    root->right = node;
                    node->parent = root;
                    root->middle = NULL;
                    root->rval = EMPTY;
                    root->max_child = node->max_child;
                    return root;
                } else { // two leaves
                    root->max_child = node->max_child;
                    return root;
                }
            }
        }
    }
    return root;
}