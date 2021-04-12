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
            Node_t* v = newNode(val), *X = newNode(root->lval), *Y = newNode(root->rval);
            if (val <= root->lval) { // v <= X
                X->left = v;
                X->right = Y;

                X->max_child = Y->lval;

                v->parent = X;
                Y->parent = X;

                v->rsib = Y;
                Y->lsib = v;

                free(root);
                return X;
            } else if (val > root->lval && val <= root->rval) { // X < v <= Y
                v->left = X;
                v->right = Y;

                v->max_child = Y->lval;

                Y->parent = v;
                X->parent = v;

                X->rsib = Y;
                Y->lsib = X;
                free(root);
                return v;
            } else {
                Y->left = X;
                Y->right = v;

                Y->max_child = v->lval;

                v->parent = Y;
                X->parent = Y;

                X->rsib = v;
                v->lsib = X;
                free(root);
                return Y;
            }
        }
    }
    else
        return root;
}