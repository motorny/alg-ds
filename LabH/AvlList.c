#include <stdlib.h>

#include "AvlList.h"

int height(Node_t* node) 
{ 
    return node == NULL ? 0 : node->height; 
}

int max(int a, int b) 
{ 
    return a > b ? a : b; 
}

int fixHeight(Node_t* node) 
{ 
    return 1 + max(height(node->left), height(node->right));
}

Node_t* newNode(int val) 
{
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    if (node) 
    {
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        node->value = val;
        return node;
    }
    return NULL;
}

Node_t* rightRotate(Node_t* y) 
{
    Node_t* x = y->left;
    Node_t* beta = x->right;

    x->right = y;
    y->left = beta;

    y->height = fixHeight(y);
    x->height = fixHeight(x);

    return x;
}

Node_t* leftRotate(Node_t* y)
{
    Node_t* x = y->right;
    Node_t* beta = x->left;

    x->left = y;
    y->right = beta;

    y->height = fixHeight(y);
    x->height = fixHeight(x);

    return x;
}

Node_t* findNode(Node_t* node, int val)
{
    if (node != NULL)
    {
        if (node->value < val)
            return findNode(node->right, val);
        else if (node->value > val)
            return findNode(node->left, val);
        return node;
    }
    return NULL;
}

int getBalance(Node_t* node) 
{ 
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

Node_t* balance(Node_t* node)
{
    node->height = fixHeight(node);
    int balance = getBalance(node);

    if (balance > 1)
    {
        if (getBalance(node->left) < 0)
            node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1)
    {
        if (getBalance(node->right) > 0)
            node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node_t* insertNode(Node_t* node, int val)
{
    if (node == NULL)
        return newNode(val);

    if (val < node->value)
        node->left = insertNode(node->left, val);
    else if (val > node->value)
        node->right = insertNode(node->right, val);
    else
        return node;
    return balance(node);
}

Node_t* minNodeValue(Node_t* node) 
{
    Node_t* curr = node;
    while (curr->left != NULL)
        curr = curr->left;
    return curr;
}

Node_t* deleteNode(Node_t* node, int val) 
{
    if (node == NULL)
        return node;

    if (val < node->value)
        node->left = deleteNode(node->left, val);
    else if (val > node->value)
        node->right = deleteNode(node->right, val);
    else
    {
        if ((node->left == NULL) || (node->right == NULL))
        {
            Node_t* tmp = node->left ? node->left : node->right;
            if (tmp == NULL)
            {
                tmp = node;
                node = NULL;
            }
            else
                *node = *tmp;
            free(tmp);
        }
        else
        {
            node->value = minNodeValue(node->right)->value;
            node->right = deleteNode(node->right, node->value);
        }
    }
    if (node == NULL)
        return NULL;

    return balance(node);
}

void printPreOrder(Node_t* node) 
{
    if (node != NULL) 
    {
        printPreOrder(node->left);
        printf("%d ", node->value);
        printPreOrder(node->right);
    }
    printf("\n");
}

void freeTree(Node_t* node) 
{
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}