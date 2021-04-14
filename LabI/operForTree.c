#include "tree23plus.h"

bool Push(stackTree_t** stack, tree_t* newTree)
{
    stackTree_t* newNode = (stackTree_t*)malloc(sizeof(stackTree_t));
    if (newTree == NULL || newNode == NULL)
        return false;

    newNode->curTree = newTree;
    newNode->nextTree = *stack;
    *stack = newNode;
    return true;
}

bool Pop(stackTree_t** stack, tree_t** treeFromStack)
{
    stackTree_t* nodeToDelete = *stack;
    if (*stack == NULL)
    {
        *treeFromStack = NULL;
        return false;
    }

    *treeFromStack = (*stack)->curTree;
    *stack = (*stack)->nextTree;
    free(nodeToDelete);
    return true;
}


int GetHeight(tree_t* tree)
{
    int i = 0;
    tree_t* tmp = tree;

    while (tmp != NULL)
    {
        i++;
        tmp = tmp->left;
    }

    return i;
}

int GetMinElement(tree_t* tree)
{
    tree_t* tmp = tree;

    while (tmp != NULL && tmp->isLeaf == false)
        tmp = tmp->left;

    if (tmp == NULL)
        return 0;
    else
        return tmp->value;
}

int UnitedFromLeft(tree_t** tree, tree_t* treeNewInLeft, tree_t* treeBroOfNew)
{
    tree_t* broParent = treeBroOfNew->parent;

    if (broParent == 0)
    {
        tree_t* newParent = (tree_t*)malloc(sizeof(tree_t));
        if (newParent == NULL)
            return false;

        newParent->isLeaf = false;
        newParent->value = 0;
        newParent->rightNum = 0;
        newParent->leftNum = treeNewInLeft->maxValue;
        newParent->maxValue = treeBroOfNew->maxValue;
        newParent->countChild = 2;

        newParent->left = treeNewInLeft;
        newParent->middle = treeBroOfNew;
        newParent->right = newParent->parent = NULL;

        treeNewInLeft->parent = newParent;
        treeBroOfNew->parent = newParent;

        *tree = newParent;
        return true;
    }
    if (broParent->countChild == 2)
    {
        broParent->countChild = 3;
        broParent->right = broParent->middle;
        broParent->middle = broParent->left;
        broParent->left = treeNewInLeft;
        treeNewInLeft->parent = broParent;

        broParent->rightNum = broParent->middle->maxValue;
        broParent->leftNum = broParent->left->maxValue;

        return true;
    }
    if (broParent->countChild == 3)
    {
        tree_t* newNodeToNewLeft = (tree_t*)malloc(sizeof(tree_t));
        if (newNodeToNewLeft == NULL)
            return false;

        newNodeToNewLeft->isLeaf = false;
        newNodeToNewLeft->value = 0;
        newNodeToNewLeft->rightNum = 0;
        newNodeToNewLeft->countChild = 2;

        newNodeToNewLeft->left = treeNewInLeft;
        newNodeToNewLeft->middle = broParent->left;
        newNodeToNewLeft->right = newNodeToNewLeft->parent = NULL;

        newNodeToNewLeft->leftNum = treeNewInLeft->maxValue;
        newNodeToNewLeft->maxValue = newNodeToNewLeft->middle->maxValue;

        treeNewInLeft->parent = newNodeToNewLeft;
        treeBroOfNew->parent = newNodeToNewLeft;

        broParent->countChild = 2;
        broParent->left = broParent->middle;
        broParent->middle = broParent->right;
        broParent->right = NULL;
        broParent->rightNum = 0;
        broParent->leftNum = broParent->left->maxValue;

        return UnitedFromLeft(tree, newNodeToNewLeft, broParent);
    }
    return true;
}

bool UnitedFromRight(tree_t** tree, tree_t* treeNewInRight, tree_t* treeBroOfNew)
{
    tree_t* broParent = treeBroOfNew->parent;
    tree_t* tmp;

    if (broParent == 0)
    {
        tree_t* newParent = (tree_t*)malloc(sizeof(tree_t));
        if (newParent == NULL)
            return false;

        newParent->isLeaf = false;
        newParent->value = 0;
        newParent->rightNum = 0;
        newParent->leftNum = treeBroOfNew->maxValue;
        newParent->maxValue = treeNewInRight->maxValue;
        newParent->countChild = 2;

        newParent->left = treeBroOfNew;
        newParent->middle = treeNewInRight;
        newParent->right = newParent->parent = NULL;

        treeNewInRight->parent = newParent;
        treeBroOfNew->parent = newParent;

        *tree = newParent;
        return true;
    }
    if (broParent->countChild == 2)
    {
        broParent->countChild = 3;
        broParent->right = treeNewInRight;
        treeNewInRight->parent = broParent;

        broParent->rightNum = broParent->middle->maxValue;
        broParent->maxValue = broParent->right->maxValue;

        broParent = broParent->parent;
        while (broParent != NULL)
        {
            if (treeNewInRight->maxValue > broParent->maxValue)
                broParent->maxValue = treeNewInRight->maxValue;
            else
                break;

            broParent = broParent->parent;
        }

        return true;
    }
    if (broParent->countChild == 3)
    {
        tree_t* newNodeToNewRight = (tree_t*)malloc(sizeof(tree_t));
        if (newNodeToNewRight == NULL)
            return false;

        newNodeToNewRight->isLeaf = false;
        newNodeToNewRight->value = 0;
        newNodeToNewRight->rightNum = 0;
        newNodeToNewRight->countChild = 2;

        newNodeToNewRight->left = broParent->right;
        newNodeToNewRight->middle = treeNewInRight;
        newNodeToNewRight->right = newNodeToNewRight->parent = NULL;

        newNodeToNewRight->leftNum = newNodeToNewRight->left->maxValue;
        newNodeToNewRight->maxValue = newNodeToNewRight->middle->maxValue;

        treeNewInRight->parent = newNodeToNewRight;
        treeBroOfNew->parent = newNodeToNewRight;

        broParent->countChild = 2;
        broParent->right = NULL;
        broParent->rightNum = 0;
        broParent->maxValue = broParent->middle->maxValue;

        int prevMax = newNodeToNewRight->left->maxValue;
        tmp = broParent->parent;
        while (tmp != NULL)
        {
            if (tmp->maxValue == prevMax)
                if (tmp->countChild == 2)
                    tmp->maxValue = tmp->middle->maxValue;
                else
                    tmp->maxValue = tmp->right->maxValue;
            else
                break;

            tmp = tmp->parent;
        }

        return UnitedFromRight(tree, newNodeToNewRight, broParent);
    }
    return true;
}

bool Merge(tree_t** tree, tree_t* tree1, tree_t* tree2)
{
    int firstLength = GetHeight(tree1);
    int secondLength = GetHeight(tree2);
    int tmpLength;

    int firstMin = GetMinElement(tree1);
    int secondMin = GetMinElement(tree2);
    int tmpMin;

    tree_t* tmp;
    tree_t* oldTreePtr = *tree;
    tree_t* tmpParent;

    if (tree1 == NULL && tree2 == NULL)
    {
        *tree = NULL;
        return false;
    }
    else if (tree1 == NULL)
    {
        *tree = tree2;
        return true;
    }
    else if (tree2 == NULL)
    {
        *tree = tree1;
        return true;
    }

    if (!(secondMin > tree1->maxValue || firstMin > tree2->maxValue))
    {
        *tree = NULL;
        return false;
    }

    if (firstLength < secondLength)
    {
        tmp = tree2;
        tree2 = tree1;
        tree1 = tmp;

        tmpLength = firstLength;
        firstLength = secondLength;
        secondLength = tmpLength;
        tmpMin = firstMin;
        firstMin = secondMin;
        secondMin = tmpMin;
    }

    if (firstLength == secondLength)
    {
        tree_t* newTreeTop = (tree_t*)malloc(sizeof(tree_t));
        if (newTreeTop == NULL)
            return false;

        newTreeTop->isLeaf = false;
        newTreeTop->value = 0;
        newTreeTop->rightNum = 0;
        newTreeTop->countChild = 2;
        newTreeTop->right = NULL;
        newTreeTop->parent = NULL;

        tree1->parent = newTreeTop;
        tree2->parent = newTreeTop;

        if (secondMin > tree1->maxValue)
        {
            newTreeTop->left = tree1;
            newTreeTop->middle = tree2;
        }
        else
        {
            newTreeTop->left = tree1;
            newTreeTop->middle = tree2;
        }
        newTreeTop->leftNum = newTreeTop->left->maxValue;
        newTreeTop->maxValue = newTreeTop->middle->maxValue;
        *tree = newTreeTop;
        return true;
    }
    else
    {
        tmp = tree1;
        tmpParent = NULL;
        if (firstMin > tree2->maxValue)
        {
            for (int i = 0; i < firstLength - secondLength; i++)
                tmpParent = tmp, tmp = tmp->left;

            UnitedFromLeft(tree, tree2, tmp);
            if (*tree == oldTreePtr)
                *tree = tree1;
        }
        else
        {
            for (int i = 0; i < firstLength - secondLength; i++)
            {
                tmpParent = tmp;
                if (tree1->countChild == 2)
                    tmp = tmp->middle;
                else
                    tmp = tmp->right;
            }

            UnitedFromRight(tree, tree2, tmp);
            if (*tree == oldTreePtr)
                *tree = tree1;
        }
    }
    return true;
}


bool Split(tree_t* tree, tree_t** tree1, tree_t** tree2, int elementToSplit)
{
    tree_t* tmp = tree;
    tree_t* tmpParent = NULL, * leftTree = NULL, * rightTree = NULL, * nodeToDelete, * leafNode;
    stackTree_t* stackTreeLeft = NULL;
    stackTree_t* stackTreeRight = NULL;

    *tree1 = NULL;
    *tree2 = NULL;

    if (tree == NULL)
        return false;

    while (tmp != NULL && tmp->isLeaf == false)
    {
        tmpParent = tmp;

        if (tmp->countChild == 2)
        {
            if (elementToSplit <= tmp->leftNum)
                tmp = tmp->left;
            else
                tmp = tmp->middle;
        }
        else
        {
            if (elementToSplit <= tmp->leftNum)
                tmp = tmp->left;
            else if (tmp->leftNum < elementToSplit && elementToSplit <= tmp->rightNum)
                tmp = tmp->middle;
            else if (tmp->rightNum < elementToSplit)
                tmp = tmp->right;
        }
    }

    if (tmp == NULL || (tmp != NULL && tmp->value != elementToSplit))
        return false;

    if (tmpParent == NULL)
    {
        *tree1 = tmp;
        *tree2 = NULL;
    }
    else
    {
        Push(&stackTreeLeft, tmp);

        while (tmpParent != NULL)
        {
            if (tmpParent->countChild == 2 && tmp == tmpParent->left)
            {
                tmpParent->middle->parent = NULL;
                Push(&stackTreeRight, tmpParent->middle);
            }
            else if (tmpParent->countChild == 2 && tmp == tmpParent->middle)
            {
                tmpParent->left->parent = NULL;
                Push(&stackTreeLeft, tmpParent->left);
            }
            else if (tmpParent->countChild == 3 && tmp == tmpParent->left)
            {
                tmpParent->middle->parent = tmpParent->right->parent = NULL;
                Push(&stackTreeRight, tmpParent->middle);
                Push(&stackTreeRight, tmpParent->right);
            }
            else if (tmpParent->countChild == 3 && tmp == tmpParent->middle)
            {
                tmpParent->left->parent = tmpParent->right->parent = NULL;
                Push(&stackTreeLeft, tmpParent->left);
                Push(&stackTreeRight, tmpParent->right);
            }
            else if (tmpParent->countChild == 3 && tmp == tmpParent->right)
            {
                tmpParent->middle->parent = tmpParent->left->parent = NULL;
                Push(&stackTreeLeft, tmpParent->left);
                Push(&stackTreeLeft, tmpParent->middle);
            }

            nodeToDelete = tmp;
            tmpParent = tmpParent->parent;
            if (tmp->isLeaf == true)
            {
                leafNode = tmp;
                tmp = tmp->parent;
                leafNode->parent = NULL;
            }
            else
                tmp = tmp->parent;
            if (nodeToDelete->isLeaf == false)
                free(nodeToDelete);
        }

        while (stackTreeLeft != NULL)
        {
            Pop(&stackTreeLeft, &tmp);
            Merge(&leftTree, leftTree, tmp);
        }
        *tree1 = leftTree;

        while (stackTreeRight != NULL)
        {
            Pop(&stackTreeRight, &tmp);
            Merge(&rightTree, rightTree, tmp);
        }
        *tree2 = rightTree;
    }

    return true;
}