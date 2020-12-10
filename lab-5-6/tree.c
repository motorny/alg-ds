#include "tree.h"

Node* getMinNode(Node *root)
{
    while (root->left)
        root = root->left;
    return root;
}

Node* getMaxNode(Node *root)
{
    while (root->right)
        root = root->right;
    return root;
}

Node* getFreeNode(int value, Node *parent)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = parent;
    tmp->data = value;
    tmp->numOfLeavesBelow = 0;
    tmp->orderAscending = 0;
    return tmp;
}


Node *getNodeByValue(Node *root, int value)
{
    while (root)
    {
        if (root->data > value)
        {
            root = root->left;
            continue;
        }
        else if (root->data < value)
        {
            root = root->right;
            continue;
        }
        return root;
    }
    return NULL;
}


void insert(Node **head, int value)
{
    Node *tmp = NULL;
    if (*head == NULL)
    {
        *head = getFreeNode(value, NULL);
        return;
    }

    tmp = *head;
    while (tmp)
    {
        if (value > tmp->data)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        }
        else if (value < tmp->data)
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        }
        return;
    }
}


void removeNodeByPtr(Node *target)
{
    if (!target)
        return;

    if (target->left && target->right)
    {
        Node *localMax = getMaxNode(target->left);
        target->data = localMax->data;
        removeNodeByPtr(localMax);
        return;
    }
    else if (target->left)
    {
        if (target->parent == NULL)
        {
            Node* tmp = target->left;
            target->data = tmp->data;
            target->left = tmp->left;
            target->right = tmp->right;
            target->numOfLeavesBelow = tmp->numOfLeavesBelow;
            target->orderAscending = tmp->orderAscending;
            target = tmp;
        }
        else if (target == target->parent->left)
        {
            target->parent->left = target->left;
            target->left->parent = target->parent;
        }
        else
        {
            target->parent->right = target->left;
            target->left->parent = target->parent;
        }
    }
    else if (target->right)
    {
        if (target->parent == NULL)
        {
            Node* tmp = target->right;
            target->data = tmp->data;
            target->left = tmp->left;
            target->right = tmp->right;
            target->numOfLeavesBelow = tmp->numOfLeavesBelow;
            target->orderAscending = tmp->orderAscending;
            target = tmp;
        }
        else if (target == target->parent->right)
        {
            target->parent->right = target->right;
            target->right->parent = target->parent;
        }
        else
        {
            target->parent->left = target->right;
            target->right->parent = target->parent;
        }
    }
    else
    {
        if (target == target->parent->left)
        {
            target->parent->left = NULL;
        }
        else
        {
            target->parent->right = NULL;
        }
    }
    free(target);
}


void deleteValue(Node *root, int value)
{
    Node *target = getNodeByValue(root, value);
    removeNodeByPtr(target);
}


void destroyTree(Node *root)
{
    if (root)
    {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}


void printTree(Node *root, const char *dir, int level)
{
    if (root)
    {
        printf("lvl %d %s = %d\n", level, dir, root->data);
        printTree(root->left, "left", level + 1);
        printTree(root->right, "right", level + 1);
    }
}

void printTreeLow(Node *root, const char *dir, int level, int k)
{
    if (root)
    {
        printTreeLow(root->left, "left", level + 1, k);
        if (root->orderAscending < k)
            printf("lvl %d %s = %d  order = %i\n", level, dir, root->data, root->orderAscending);
        printTreeLow(root->right, "right", level + 1, k);
    }
}


int getNumOfLeavesBelow(Node *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
    {
        root->numOfLeavesBelow = 0;
        return 1;
    }
    root->numOfLeavesBelow = getNumOfLeavesBelow(root->left) + getNumOfLeavesBelow(root->right);
    return root->numOfLeavesBelow;
}


void setOrder(Node *node, int *number)
{
    if (node)
    {
        setOrder(node->left, number);
        node->orderAscending = (*number);
        (*number)++;
        setOrder(node->right, number);
    }
}


Node* findK(Node *root, int k)
{
    Node* tmp = NULL;
    if (root)
    {
        tmp = findK(root->right, k);
        if (tmp)
            return tmp;
        if (root->orderAscending == k)
            return root;
        tmp = findK(root->left, k);
        if (tmp)
            return tmp;
    }
    return NULL;
}


void printKsmall(Node *root, int k)
{
    int number = 1;
    setOrder(root, &number);
    Node* trgt = findK(root, k);
    if (trgt)
    {
        printf("\nK: %i  VALUE: %i\n", trgt->orderAscending, trgt->data);
        if (trgt->data % 2 == 0)
            printTreeLow(root, "root", 0, k);
    }
    else
        printf("\nNOT FOUND\n");
}
