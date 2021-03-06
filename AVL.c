#include <stdlib.h>

#include "AVL.h"

int height(Node_t* node) { return node == NULL ? 0 : node->height; }

int max(int a, int b) { return a > b ? a : b; }

Node_t* newNode(int val) {
    Node_t* node = (Node_t*) malloc(sizeof(Node_t));
    if (node) {
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        node->value = val;
        return node;
    }
    return NULL;
}

Node_t* rightRotate(Node_t* y) {
    Node_t* x = y->left;
    Node_t* beta = x->right;

    x->right = y;
    y->left = beta;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node_t* leftRotate(Node_t* y) {
    Node_t* x = y->right;
    Node_t* beta = x->left;

    x->left = y;
    y->right = beta;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node_t* findNode(Node_t* node, int val) {
    if (node != NULL) {
        if (node->value < val)
            return findNode(node->right, val);
        else if (node->value > val)
            return findNode(node->left, val);
        return node;
    }
    return NULL;
}

int getBalance(Node_t* node) { return (node == NULL) ? 0 : height(node->left) - height(node->right); }

Node_t* insertNode(Node_t* node, int val) {
    if (node == NULL)
        return newNode(val);

    if (val < node->value)
        node->left = insertNode(node->left, val);
    else if (val > node->value)
        node->right = insertNode(node->right, val);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && val < node->left->value)
        return rightRotate(node);
    if (balance < -1 && val > node->right->value)
        return leftRotate(node);
    if (balance > 1 && val > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && val < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node_t* minNodeValue(Node_t* node) {
    Node_t* curr = node;
    while (curr->left != NULL)
        curr = curr->left;
    return curr;
}

Node_t* deleteNode(Node_t* root, int val) {
    if (root == NULL)
        return root;

    if (val < root->value)
        root->left = deleteNode(root->left, val);
    else if (val > root->value)
        root->right = deleteNode(root->right, val);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node_t* tmp = root->left ? root->left : root->right;
            if (tmp == NULL) {
                tmp = root;
                root = NULL;
            } else
                *root = *tmp;
            free(tmp);
        } else {
            root->value = minNodeValue(root->right)->value;
            root->right = deleteNode(root->right, root->value);
        }
    }

    if (root == NULL)
        return NULL;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->left) <= 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void printPreOrder(Node_t* root) {
    if (root != NULL) {
        printPreOrder(root->left);
        printf("%d ", root->value);
        printPreOrder(root->right);
    }
    printf("\n");
}

void freeTree(Node_t* node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}
