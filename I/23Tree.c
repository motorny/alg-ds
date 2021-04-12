#include <stdio.h>
#include <stdlib.h>
#include "23Tree.h"

int isTerminal(Node_t* node) {
    return node != NULL && node->left == NULL && node->right == NULL && node->middle == NULL || node == NULL;
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
    if (root == NULL)
        return newNode(val);
    else if (isTerminal(root)) {
        if (root->rval == EMPTY && root->rval <= root->lval) { // one value in node
            root->rval = val > root->lval ? val : root->lval;
            root->lval = val > root->lval ? root->lval : val;
            root->max_child = root->rval;
            return root;
        } else { // two values in node
            int root_val = val, left_val = root->lval, right_val = root->rval; // X v Y
            if (val < root->lval) { // v X Y
                root_val = root->lval;
                left_val = val;
            } else if (val > root->rval) { // X Y v
                root_val = root->rval;
                right_val = val;
            }
            Node_t* v = newNode(root_val), * X = newNode(left_val), * Y = newNode(right_val);
            v->parent = root->parent;
            v->left = X;
            v->right = Y;
            v->max_child = Y->lval;

            Y->parent = v;
            X->parent = v;

            X->rsib = Y;
            Y->lsib = X;

            free(root);
            return v;
        }
    } else // apparently, not terminal node
        return root;
}

Node_t* insertNode(Node_t* root, int val) {
    if (isTerminal(root))
        return insertTerminate(root, val);
    else if (root->rval == EMPTY && root->rval <= root->lval) { // one value node
        if (val <= root->lval) {
            Node_t* node = insertNode(val <= root->lval ? root->left : root->right, val);
            root->rval = root->lval;
            root->lval = node->lval;
            root->max_child = node->max_child;

            root->left = node->left;
            root->middle = node->right;

            node->parent = root;
        } else {
            Node_t* node = insertNode(val <= root->lval ? root->left : root->right, val);
            root->rval = node->lval;

            root->middle = node->left;
            root->right = node->right;

            node->parent = root;
        }
    } else { // two values node
        Node_t* X = newNode(root->lval), * Y = newNode(root->rval);
        if (val < root->lval) {
            Node_t* node = insertNode(root->left, val);
            X->parent = root->parent;
            X->left = node;
            X->right = Y;
            Y->parent = X;
            node->parent = X;
            Y->left = root->middle;
            Y->right = root->right;
            X->max_child = node->max_child;
            Y->max_child = Y->left->max_child;
            free(root);
            return X;
        } else if (val <= root->rval && val > root->lval) {
            Node_t* node = insertNode(root->middle, val);
            node->parent = root->parent;
            X->right = node->left;
            X->left = root->left;
            X->max_child = X->left->max_child;
            Y->left = node->right;
            Y->right = root->right;
            Y->max_child = Y->left->max_child;
            node->left = X;
            node->right = Y;
            X->parent = node;
            Y->parent = node;
            node->max_child = X->max_child;
            free(root);
            return node;
        } else {
            Node_t* node = insertNode(root->right, val);
            Y->parent = root->parent;
            X->left = root->left;
            X->right = root->middle;
            X->max_child = X->left->max_child;
            Y->left = X;
            X->parent = Y;
            Y->max_child = Y->left->max_child;
            Y->right = node;
            node->parent = Y;
            free(root);
            return Y;
        }
    }

}