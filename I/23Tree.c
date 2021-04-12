#include <stdio.h>
#include <stdlib.h>
#include "23Tree.h"

int isTerminal(Node_t* node) {
    return node != NULL && node->left == NULL && node->right == NULL && node->middle == NULL || node == NULL;
}

//Node_t* updateVals(Node_t* node) {
//
//}

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
            Node_t* v = newNode(root_val), *X = newNode(left_val), *Y = newNode(right_val);
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