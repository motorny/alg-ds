#include <stdio.h>
#include <stdlib.h>

#include "23Tree.h"

int isTerminal(Node_t* node) { // only left is considered, since without it there won't be middle and right
    return node != NULL && (node->left != NULL && node->left->left == NULL ||
                            node->right != NULL && node->right->left == NULL ||
                            node->middle != NULL && node->middle->left == NULL) || node == NULL;
}

int isHole(Node_t* node) {
    return node != NULL && node->lval == node->max_child;
}

int hasTwoChildren(Node_t* node) { // two, no more no less
    return node != NULL && node->left != NULL && node->middle == NULL && node->right != NULL;
}

int hasThreeChildren(Node_t* node) {
    return node != NULL && node->left != NULL && node->middle != NULL && node->right != NULL;
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
    // sibs of the middle should be NULLed by freeNode
    if (right != NULL)
        right->lsib = left;
}

Node_t* newNode(int val) {
    Node_t* node = (Node_t*) malloc(sizeof(Node_t));
    if (node != NULL) {
        node->left = NULL;
        node->right = NULL;
        node->middle = NULL;
        node->lval = val;
        node->rval = EMPTY;
        node->lsib = NULL;
        node->rsib = NULL;
        node->max_child = val;
    }
    return node;
}

void freeNode(Node_t* node) {
    if (node != NULL) {
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
        freeTree(root->middle);
        freeTree(root->right);
        freeNode(root);
    }
}

Node_t* updateNode(Node_t* root, Node_t* left, Node_t* middle, Node_t* right) {
    if (root != NULL) {
        root->left = left;
        root->lval = (root->left == NULL ? EMPTY : root->left->max_child);
        root->middle = middle;
        root->rval = (root->middle == NULL ? EMPTY : root->middle->max_child);
        root->right = right;
        // in case of creating a hole max_child should be equal to its lval
        root->max_child = (root->right == NULL ? root->middle == NULL ? root->left->max_child : EMPTY
                                               : root->right->max_child);
    }
    return root;
}

Node_t* splitNode(Node_t* X, Node_t* node, Node_t* Y, Node_t* toFree, Node_t* a, Node_t* b, Node_t* c, Node_t* d) {
    X = updateNode(X == NULL ? newNode(EMPTY) : X, a, NULL, b);
    Y = updateNode(Y == NULL ? newNode(EMPTY) : Y, c, NULL, d);
    node = updateNode(node == NULL ? newNode(EMPTY) : node, X, NULL, Y);

    freeNode(toFree);
    return node;
}

Node_t* mergeNode(Node_t* root, Node_t* left, Node_t* middle, Node_t* right, Node_t* toFree) {
    if (hasTwoChildren(left) && hasTwoChildren(middle) && hasTwoChildren(right)) {
        left = updateNode(left, left->left, left->right, middle->left);
        right = updateNode(right, middle->right, right->left, right->right);
        root = updateNode(root, left, NULL, right);
        freeNode(middle);
    } else
        root = updateNode(root, left, middle, right);
    freeNode(toFree);
    return root;
}

Node_t* redistributeNode(Node_t* root, Node_t* a, Node_t* b, Node_t* c, Node_t* d, Node_t* toFree) {
    // branch for 224 or 242 is the next one and root->right is equal d only if it is not 4
    if (hasTwoChildren(a) && hasTwoChildren(b) && hasTwoChildren(c) && root->right == d) {
        toFree = mergeNode(toFree, a, b, c, NULL);
        return mergeNode(root, toFree->left, toFree->right, d, toFree);
    } else if (hasTwoChildren(b) && hasTwoChildren(c) && hasTwoChildren(d)) {
        toFree = mergeNode(toFree, b, c, d, NULL);
        return mergeNode(root, a, toFree->left, toFree->right, toFree);
    } else if (hasThreeChildren(c) && hasTwoChildren(d)) {
        a = mergeNode(a, a->left, a->right, b->left, NULL);
        b = mergeNode(b, b->right, c->left, c->middle, NULL);
        c = mergeNode(c, c->right, d->left, d->right, d);
        return mergeNode(root, a, b, c, toFree);
    } else if (hasThreeChildren(b) && hasTwoChildren(a)) {
        d = mergeNode(d, c->right, d->left, d->right, NULL);
        c = mergeNode(c, b->middle, b->right, c->left, NULL);
        b = mergeNode(b, a->left, a->right, b->left, a);
        return mergeNode(root, b, c, d, toFree);
    }
    return splitNode(root->left == a ? NULL : toFree,
                     root->middle == b || root->middle == c ? NULL : toFree,
                     root->right == d ? NULL : toFree, root, a, b, c, d);
}

Node_t* insertTerminate(Node_t* root, int val) {
    if (root == NULL) {
        Node_t* node = newNode(val), * leaf = newNode(val);
        node->left = leaf;
        return node;
    }
    Node_t* node = newNode(val);
    if (val < root->lval) {
        connectSiblings(root->left->lsib, node, root->left);
        return isHole(root) ? updateNode(root, node, NULL, root->left) :
               hasTwoChildren(root) ? mergeNode(root, node, root->left, root->right, NULL)
                                    : splitNode(NULL, NULL, NULL, root, node, root->left, root->middle, root->right);
    } else if (val > root->max_child) {
        if (isHole(root)) {
            connectSiblings(root->left, node, root->left->rsib);
            return updateNode(root, root->left, NULL, node);
        }
        connectSiblings(root->right, node, root->right->rsib);
        return hasTwoChildren(root) ? mergeNode(root, root->left, root->right, node, NULL)
                                    : splitNode(NULL, NULL, NULL, root, root->left, root->middle, root->right, node);
    } else if (hasTwoChildren(root) && val > root->lval && val < root->max_child) {
        connectSiblings(root->left, node, root->right);
        return mergeNode(root, root->left, node, root->right, NULL);
    } else if (hasThreeChildren(root)) {
        if (val < root->rval && val > root->lval) {
            connectSiblings(root->left, node, root->middle);
            return splitNode(NULL, NULL, NULL, root, root->left, node, root->middle, root->right);
        } else if (val < root->max_child && val > root->rval) {
            connectSiblings(root->middle, node, root->right);
            return splitNode(NULL, NULL, NULL, root, root->left, root->middle, node, root->right);
        }
    }
    return root;
}

Node_t* insertNode(Node_t* root, int val) {
    if (isTerminal(root))
        return insertTerminate(root, val);

    Node_t* node;
    if (val < root->lval) { // left
        node = insertNode(root->left, val);
        if (node != root->left) { // node was split during insertion, cannot just update the root
            if (hasTwoChildren(root))
                return mergeNode(root, node->left, node->right, root->right, node);
            return redistributeNode(root, node->left, node->right, root->middle, root->right, node);
        }
    } else if (hasThreeChildren(root) && val < root->rval && val > root->lval) { // middle
        node = insertNode(root->middle, val);
        if (node != root->middle)
            return redistributeNode(root, root->left, node->left, node->right, root->right, node);
    } else if (val > (hasTwoChildren(root) ? root->lval : root->rval)) { // right
        node = insertNode(root->right, val);
        if (root->right != node) { // node was split, hence cannot just update the root
            if (hasTwoChildren(root))
                return mergeNode(root, root->left, node->left, node->right, node);
            return redistributeNode(root, root->left, root->middle, node->left, node->right, node);
        }
    }
    return updateNode(root, root->left, root->middle, root->right);
}

Node_t* deleteTerminal(Node_t* root, int val) {
    if (root == NULL || isHole(root) && root->lval == val) { // null or one leaf
        freeTree(root);
        return NULL;
    }
    if (val == root->lval) {
        disconnectSiblings(root->left->lsib, root->left, root->left->rsib);
        if (hasTwoChildren(root))
            return mergeNode(root, root->right, NULL, NULL, root->left);
        return mergeNode(root, root->middle, NULL, root->right, root->left);
    } else if (val == root->max_child) {
        disconnectSiblings(root->right->lsib, root->right, root->right->rsib);
        // if root has 2 children, middle should be NULL
        return mergeNode(root, root->left, NULL, root->middle, root->right);
    } else if (hasThreeChildren(root) && val == root->rval) {
        disconnectSiblings(root->middle->lsib, root->middle, root->middle->rsib);
        return mergeNode(root, root->left, NULL, root->right, root->middle);
    }
    return root;
}

Node_t* stirNode(Node_t* root, Node_t* left, Node_t* middle, Node_t* right) {
    if (isHole(left)) { // 1xx
        if (hasTwoChildren(middle)) { // 12x
            left = mergeNode(left, left->left, middle->left, middle->right, middle);
            return updateNode(root, left, NULL, right);
        } // 13x
        middle = splitNode(left, NULL, middle, NULL, left->left, middle->left, middle->middle, middle->right);
        return mergeNode(root, middle->left, middle->right, right, middle);
    } else if (isHole(middle)) { // x1x
        if (hasTwoChildren(left)) { // 21x
            middle = mergeNode(middle, left->left, left->right, middle->left, left);
            return updateNode(root, middle, NULL, right);
        } else if (hasTwoChildren(right)) { // 312
            middle = mergeNode(middle, middle->left, right->left, right->right, right);
            return updateNode(root, left, NULL, middle);
        } // 313
        left = splitNode(left, NULL, middle, NULL, left->left, left->middle, left->right, middle->left);
        return mergeNode(root, left->left, left->right, right, left);
    } else if (isHole(right)) { // xx1
        if (hasTwoChildren(middle)) { // x21
            right = mergeNode(right, middle->left, middle->right, right->left, middle);
            return updateNode(root, left, NULL, right);
        } // x31
        middle = splitNode(middle, NULL, right, NULL, middle->left, middle->middle, middle->right, right->left);
        return mergeNode(root, left, middle->left, middle->right, middle);
    }
    return updateNode(root, left, middle, right);
}

Node_t* _deleteNode(Node_t* root, int val) {
    if (isTerminal(root))
        return deleteTerminal(root, val);
    Node_t* node = NULL;
    if (val <= root->lval) {
        node = _deleteNode(root->left, val);
        if (isHole(node)) {
            if (hasTwoChildren(root)) {
                if (hasTwoChildren(root->right)) {
                    node->left = mergeNode(root, node->left, root->right->left, root->right->right, root->right);
                    return node;
                }
                return splitNode(node, root, root->right, NULL, node->left, root->right->left, root->right->middle,
                                 root->right->right);
            }
            return stirNode(root, node, root->middle, root->right);
        }
    } else if (hasThreeChildren(root) && val <= root->rval && val > root->lval) {
        node = _deleteNode(root->middle, val);
        if (isHole(node))
            return stirNode(root, root->left, node, root->right);
    } else if (val > hasThreeChildren(root) ? root->rval : root->lval && val <= root->max_child) {
        node = _deleteNode(root->right, val);
        if (isHole(node)) {
            if (hasTwoChildren(root)) {
                if (hasTwoChildren(root->left)) {
                    node->left = mergeNode(root, root->left->left, root->left->right, node->left, root->left);
                    return node;
                }
                return splitNode(root->left, root, node, NULL, root->left->left, root->left->middle, root->left->right,
                                 node->left);
            }
            return stirNode(root, root->left, root->middle, node);
        }
    }
    return mergeNode(root, root->left, root->middle, root->right, NULL);
}

Node_t* deleteNode(Node_t* root, int val) {
    root = _deleteNode(root, val);
    if (isHole(root) && !isTerminal(root)) {
        Node_t* node = root->left;
        freeNode(root);
        return node;
    }
    return root;
}

Node_t* findNode(Node_t* root, int val) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL && root->middle == NULL)
            return val == root->lval ? root : NULL;
        else if (val <= root->lval)
            return findNode(root->left, val);
        else if (root->middle != NULL && val <= root->rval && val > root->lval)
            return findNode(root->middle, val);
        return findNode(root->right, val);
    }
    return NULL;
}

void printTree(Node_t* root) {
    if (root == NULL)
        return;
    while (!isTerminal(root))
        root = root->left;
    if (root != NULL) {
        root = root->left;
        do {
            printf("%d ", root->lval);
        } while ((root = root->rsib) != NULL);
    }
}