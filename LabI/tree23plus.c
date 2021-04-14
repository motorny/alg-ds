#include "tree23plus.h"
#pragma warning(disable:28182)


bool Find(tree_t* tree, int element) {
    tree_t* tmp = tree;

    while (tmp != NULL && tmp->isLeaf == 0) {
        if (tmp->countChild == 2) {
            if (element <= tmp->leftNum)
                tmp = tmp->left;
            else
                tmp = tmp->middle;
        }
        else {
            if (tmp->leftNum >= element)
                tmp = tmp->left;
            else if (tmp->leftNum < element && element <= tmp->rightNum)
                tmp = tmp->middle;
            else if (tmp->rightNum < element)
                tmp = tmp->right;
        }
    }
    if (tmp == NULL)
        return false;
    else if (tmp->value == element)
        return true;
    else
        return false;
}

bool United2Nodes(tree_t** tree, tree_t* node, tree_t* newNode) {
    tree_t* nodeParent = node->parent;

    if (nodeParent == NULL) {
        tree_t* newTree = (tree_t*)malloc(sizeof(tree_t));
        if (!newTree)
            return false;

        newTree->isLeaf = 0;
        newTree->value = 0;
        newTree->rightNum = 0;
        newTree->countChild = 2;
        newTree->right = newTree->parent = NULL;
        newTree->maxValue = newNode->maxValue;
        newTree->leftNum = node->maxValue;
        newTree->left = node;
        newTree->middle = newNode;
        newNode->parent = node->parent = newTree;

        *tree = newTree;
        return true;
    }
    else if (nodeParent->countChild == 2) {
        nodeParent->countChild = 3;
        newNode->parent = nodeParent;

        if (newNode->maxValue < nodeParent->left->maxValue) {
            nodeParent->right = nodeParent->middle;
            nodeParent->middle = nodeParent->left;
            nodeParent->left = newNode;
        }
        else if (newNode->maxValue > nodeParent->left->maxValue && newNode->maxValue < nodeParent->middle->maxValue) {
            nodeParent->right = nodeParent->middle;
            nodeParent->middle = newNode;
        }
        else
            nodeParent->right = newNode;

        nodeParent->leftNum = nodeParent->left->maxValue;
        nodeParent->rightNum = nodeParent->middle->maxValue;
        nodeParent->maxValue = nodeParent->right->maxValue;
        nodeParent = nodeParent->parent;
        while (nodeParent != NULL) {
            if (newNode->maxValue > nodeParent->maxValue)
                nodeParent->maxValue = newNode->maxValue;
            else
                break;

            nodeParent = nodeParent->parent;
        }

        return true;
    }
    else {
        tree_t* newParentElement = (tree_t*)malloc(sizeof(tree_t));
        tree_t* l1, * l2, * l3, * l4;
        if (!newParentElement)
            return false;

        if (newNode->maxValue < nodeParent->left->maxValue) {
            l1 = newNode;
            l2 = nodeParent->left;
            l3 = nodeParent->middle;
            l4 = nodeParent->right;
        }
        else if (newNode->maxValue > nodeParent->left->maxValue && newNode->maxValue < nodeParent->middle->maxValue) {
            l1 = nodeParent->left;
            l2 = newNode;
            l3 = nodeParent->middle;
            l4 = nodeParent->right;
        }
        else if (newNode->maxValue > nodeParent->middle->maxValue && newNode->maxValue < nodeParent->right->maxValue) {
            l1 = nodeParent->left;
            l2 = nodeParent->middle;
            l3 = newNode;
            l4 = nodeParent->right;
        }
        else {
            l1 = nodeParent->left;
            l2 = nodeParent->middle;
            l3 = nodeParent->right;
            l4 = newNode;
        }

        nodeParent->rightNum = 0;
        nodeParent->countChild = 2;
        nodeParent->leftNum = l1->maxValue;
        nodeParent->left = l1;
        nodeParent->middle = l2;
        nodeParent->right = NULL;
        nodeParent->maxValue = l2->maxValue;
        l1->parent = l2->parent = nodeParent;

        newParentElement->isLeaf = 0;
        newParentElement->value = 0;
        newParentElement->rightNum = 0;
        newParentElement->countChild = 2;
        newParentElement->leftNum = l3->maxValue;
        newParentElement->left = l3;
        newParentElement->middle = l4;
        newParentElement->right = NULL;
        newParentElement->maxValue = l4->maxValue;
        l3->parent = l4->parent = newParentElement;

        return United2Nodes(tree, nodeParent, newParentElement);
    }
}

bool Insert(tree_t** tree, int newEl) {
    tree_t* newLeaf = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tmp = *tree, * tmpParent = NULL;
    if (!newLeaf)
        return false;
    newLeaf->isLeaf = 1;
    newLeaf->value = newLeaf->maxValue = newEl;

    newLeaf->countChild = 0;
    newLeaf->leftNum = newLeaf->rightNum = 0;
    newLeaf->left = NULL;
    newLeaf->right = NULL;
    newLeaf->middle = NULL;

    if (*tree != NULL) {
        while (tmp != NULL && tmp->isLeaf == 0) {
            tmpParent = tmp;

            if (tmp->countChild == 2) {
                if (newEl <= tmp->leftNum)
                    tmp = tmp->left;
                else
                    tmp = tmp->middle;
            }
            else {
                if (newEl <= tmp->leftNum)
                    tmp = tmp->left;
                else if (tmp->leftNum < newEl && newEl <= tmp->rightNum)
                    tmp = tmp->middle;
                else if (tmp->rightNum < newEl)
                    tmp = tmp->right;
            }
        }
        if (tmp != NULL && tmp->value == newEl) {
            free(newLeaf);
            return false;
        }

        if (tmpParent != NULL) {
            if (tmpParent->countChild == 2) {
                tmpParent->countChild = 3;
                newLeaf->parent = tmpParent;

                if (newEl < tmpParent->left->value) {
                    tmpParent->leftNum = newEl;
                    tmpParent->rightNum = tmpParent->left->value;
                    tmpParent->right = tmpParent->middle;
                    tmpParent->middle = tmpParent->left;
                    tmpParent->left = newLeaf;
                }
                else if (newEl  < tmpParent->middle->value && newEl  > tmpParent->left->value) {
                    tmpParent->rightNum = newEl;
                    tmpParent->right = tmpParent->middle;
                    tmpParent->middle = newLeaf;
                }
                else {
                    tmpParent->rightNum = tmpParent->middle->value;
                    tmpParent->right = newLeaf;
                }
                tmpParent->maxValue = tmpParent->right->value;

                tmpParent = tmpParent->parent;
                while (tmpParent != NULL) {
                    if (newEl > tmpParent->maxValue)
                        tmpParent->maxValue = newEl;
                    else
                        break;

                    tmpParent = tmpParent->parent;
                }

                return true;
            }
            else {
                tree_t* newParent = (tree_t*)malloc(sizeof(tree_t));
                tree_t* leaf1, * leaf2, * leaf3, * leaf4;
                if (!newParent) {
                    free(newLeaf);
                    return false;
                }
                if (newEl < tmpParent->left->value) {
                    leaf1 = newLeaf;
                    leaf2 = tmpParent->left;
                    leaf3 = tmpParent->middle;
                    leaf4 = tmpParent->right;
                }
                else if (newEl > tmpParent->left->value && newEl < tmpParent->middle->value) {
                    leaf1 = tmpParent->left;
                    leaf2 = newLeaf;
                    leaf3 = tmpParent->middle;
                    leaf4 = tmpParent->right;
                }
                else if (newEl > tmpParent->middle->value && newEl < tmpParent->right->value) {
                    leaf1 = tmpParent->left;
                    leaf2 = tmpParent->middle;
                    leaf3 = newLeaf;
                    leaf4 = tmpParent->right;
                }
                else {
                    leaf1 = tmpParent->left;
                    leaf2 = tmpParent->middle;
                    leaf3 = tmpParent->right;
                    leaf4 = newLeaf;
                }

                tmpParent->countChild = 2;
                tmpParent->rightNum = 0;
                tmpParent->leftNum = leaf1->value;
                tmpParent->left = leaf1;
                tmpParent->middle = leaf2;
                tmpParent->right = NULL;
                tmpParent->maxValue = leaf2->value;
                leaf1->parent = leaf2->parent = tmpParent;

                newParent->isLeaf = 0;
                newParent->value = 0;
                newParent->rightNum = 0;
                newParent->countChild = 2;
                newParent->leftNum = leaf3->value;
                newParent->left = leaf3;
                newParent->middle = leaf4;
                newParent->right = NULL;
                newParent->maxValue = leaf4->value;
                leaf3->parent = leaf4->parent = newParent;

                return United2Nodes(tree, tmpParent, newParent);
            }
        }
        else {
            tree_t* newParent = (tree_t*)malloc(sizeof(tree_t));
            if (!newParent) {
                free(newLeaf);
                return false;
            }
            newLeaf->parent = tmp->parent = newParent;

            newParent->parent = NULL;
            newParent->countChild = 2;
            newParent->isLeaf = 0;
            newParent->value = 0;
            newParent->rightNum = 0;
            newParent->right = NULL;

            if (tmp->value < newEl) {
                newParent->left = tmp;
                newParent->leftNum = tmp->value;
                newParent->middle = newLeaf;
            }
            else {
                newParent->left = newLeaf;
                newParent->leftNum = newLeaf->value;
                newParent->middle = tmp;
            }
            newParent->maxValue = newParent->middle->value;

            *tree = newParent;
            return true;
        }
    }
    else {
        newLeaf->parent = NULL;
        *tree = newLeaf;
    }

    return true;
}

void CorrectNodePath(tree_t* node)
{
    tree_t* tmp = node;
    tree_t* tmpParent = NULL;

    if (tmp != NULL)
        tmpParent = tmp->parent;

    while (tmp != NULL && tmpParent != NULL)
    {
        if (tmpParent->countChild == 2)
        {
            if (tmp == tmpParent->left)
                tmpParent->leftNum = tmp->maxValue;
            else if (tmp == tmpParent->middle)
                tmpParent->maxValue = tmp->maxValue;
        }
        else
        {
            if (tmp == tmpParent->left)
                tmpParent->leftNum = tmp->maxValue;
            else if (tmp == tmpParent->middle)
                tmpParent->rightNum = tmp->maxValue;
            else if (tmp == tmpParent->right)
                tmpParent->maxValue = tmp->maxValue;
        }

        tmp = tmpParent;
        tmpParent = tmpParent->parent;
    }
}

void Correct2ParentsTreesLowChild(tree_t* nodeToCorrect, tree_t* nodeToDelete)
{
    tree_t* nodeToDeleteParent = nodeToDelete->parent;

    if (nodeToCorrect->countChild == 2 && nodeToCorrect->left->countChild == 2 && nodeToCorrect->middle->countChild == 2)
    {
        if (nodeToDeleteParent == nodeToCorrect->left)
        {
            nodeToCorrect->middle->right = nodeToCorrect->middle->middle;
            nodeToCorrect->middle->middle = nodeToCorrect->middle->left;

            if (nodeToDelete == nodeToDeleteParent->left)
                nodeToCorrect->middle->left = nodeToDeleteParent->middle;
            else
                nodeToCorrect->middle->left = nodeToDeleteParent->left;

            nodeToCorrect->middle->left->parent = nodeToCorrect->middle;

            nodeToCorrect->middle->countChild = 3;
            nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxValue;
            nodeToCorrect->middle->rightNum = nodeToCorrect->middle->middle->maxValue;
        }
        else
        {
            if (nodeToDelete == nodeToDeleteParent->left)
                nodeToCorrect->left->right = nodeToDeleteParent->middle;
            else
                nodeToCorrect->left->right = nodeToDeleteParent->left;

            nodeToCorrect->left->right->parent = nodeToCorrect->left;

            nodeToCorrect->left->countChild = 3;
            nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxValue;
            nodeToCorrect->left->maxValue = nodeToCorrect->left->right->maxValue;

            nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
        }
    }

    CorrectNodePath(nodeToCorrect);
    return;
}

void Correct2ParentsTrees(tree_t* nodeToCorrect, tree_t* nodeToDelete)
{
    tree_t* nodeToDeleteParent = nodeToDelete->parent;

    if (nodeToCorrect->left == nodeToDeleteParent)
    {
        if (nodeToDeleteParent->left == nodeToDelete)
        {
            nodeToDeleteParent->left = nodeToDeleteParent->middle;
            nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxValue;
        }
        nodeToDeleteParent->middle = nodeToCorrect->middle->left;
        nodeToDeleteParent->middle->parent = nodeToDeleteParent;
        nodeToDeleteParent->maxValue = nodeToDeleteParent->middle->maxValue;

        nodeToCorrect->middle->left = nodeToCorrect->middle->middle;
        nodeToCorrect->middle->middle = nodeToCorrect->middle->right;
        nodeToCorrect->middle->right = NULL;
        nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxValue;
        nodeToCorrect->middle->rightNum = 0;

        nodeToCorrect->middle->countChild = 2;
        nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
    }
    else
    {
        if (nodeToDeleteParent->middle == nodeToDelete)
            nodeToDeleteParent->middle = nodeToDeleteParent->left;

        nodeToDeleteParent->left = nodeToCorrect->left->right;
        nodeToDeleteParent->left->parent = nodeToDeleteParent;
        nodeToCorrect->leftNum = nodeToDeleteParent->left->maxValue;
        nodeToDeleteParent->maxValue = nodeToDeleteParent->middle->maxValue;

        nodeToCorrect->left->countChild = 2;
        nodeToCorrect->left->rightNum = 0;
        nodeToCorrect->left->right = NULL;
        nodeToCorrect->left->maxValue = nodeToCorrect->left->middle->maxValue;

        nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxValue;

        nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
        nodeToCorrect->maxValue = nodeToCorrect->middle->maxValue;
    }

    CorrectNodePath(nodeToCorrect);
    return;
}

void Correct3ParentsTrees(tree_t* nodeToCorrect, tree_t* nodeToDelete)
{
    tree_t* nodeToDeleteParent = nodeToDelete->parent;

    if (nodeToCorrect->left->countChild + nodeToCorrect->middle->countChild + nodeToCorrect->right->countChild == 6)
    {
        if (nodeToCorrect->left == nodeToDeleteParent)
        {
            nodeToCorrect->middle->right = nodeToCorrect->middle->middle;
            nodeToCorrect->middle->middle = nodeToCorrect->middle->left;

            if (nodeToDeleteParent->left == nodeToDelete)
                nodeToCorrect->middle->left = nodeToDeleteParent->middle;
            else
                nodeToCorrect->middle->left = nodeToDeleteParent->left;

            nodeToCorrect->middle->left->parent = nodeToCorrect->middle;

            nodeToCorrect->left = nodeToCorrect->middle;
            nodeToCorrect->middle = nodeToCorrect->right;
            nodeToCorrect->right = NULL;

            nodeToCorrect->countChild = 2;
            nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
            nodeToCorrect->rightNum = 0;
            nodeToCorrect->left->countChild = 3;
            nodeToCorrect->left->leftNum = nodeToCorrect->left->left->maxValue;
            nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxValue;
        }
        else if (nodeToCorrect->middle == nodeToDeleteParent)
        {
            if (nodeToDeleteParent->left == nodeToDelete)
                nodeToCorrect->left->right = nodeToDeleteParent->middle;
            else
                nodeToCorrect->left->right = nodeToDeleteParent->left;

            nodeToCorrect->left->right->parent = nodeToCorrect->left;

            nodeToCorrect->middle = nodeToCorrect->right;
            nodeToCorrect->right = NULL;

            nodeToCorrect->countChild = 2;
            nodeToCorrect->left->maxValue = nodeToCorrect->left->right->maxValue;
            nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
            nodeToCorrect->rightNum = 0;
            nodeToCorrect->left->countChild = 3;
            nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxValue;
        }
        else if (nodeToCorrect->right == nodeToDeleteParent)
        {
            if (nodeToDeleteParent->left == nodeToDelete)
                nodeToCorrect->middle->right = nodeToDeleteParent->middle;
            else
                nodeToCorrect->middle->right = nodeToDeleteParent->left;

            nodeToCorrect->middle->right->parent = nodeToCorrect->middle;
            nodeToCorrect->right = NULL;

            nodeToCorrect->countChild = 2;
            nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
            nodeToCorrect->rightNum = 0;
            nodeToCorrect->middle->maxValue = nodeToCorrect->middle->right->maxValue;
            nodeToCorrect->maxValue = nodeToCorrect->middle->maxValue;
            nodeToCorrect->middle->countChild = 3;
            nodeToCorrect->middle->rightNum = nodeToCorrect->middle->middle->maxValue;
        }

        free(nodeToDeleteParent);
    }
    else
    {
        if (nodeToCorrect->left == nodeToDeleteParent)
        {
            if (nodeToDeleteParent->left == nodeToDelete)
                nodeToDeleteParent->left = nodeToDeleteParent->middle;

            nodeToDeleteParent->middle = nodeToCorrect->middle->left;
            nodeToDeleteParent->middle->parent = nodeToDeleteParent;
            nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxValue;
            nodeToDeleteParent->maxValue = nodeToDeleteParent->middle->maxValue;

            nodeToCorrect->middle->left = nodeToCorrect->middle->middle;
            if (nodeToCorrect->middle->countChild == 2)
            {
                nodeToCorrect->middle->middle = nodeToCorrect->right->left;
                nodeToCorrect->middle->middle->parent = nodeToCorrect->middle;

                nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxValue;
                nodeToCorrect->middle->maxValue = nodeToCorrect->middle->middle->maxValue;

                nodeToCorrect->right->left = nodeToCorrect->right->middle;
                nodeToCorrect->right->middle = nodeToCorrect->right->right;

                nodeToCorrect->right->countChild = 2;
                nodeToCorrect->right->rightNum = 0;
                nodeToCorrect->right->right = NULL;
                nodeToCorrect->right->leftNum = nodeToCorrect->right->left->maxValue;
                nodeToCorrect->right->maxValue = nodeToCorrect->right->middle->maxValue;
            }
            else
            {
                nodeToCorrect->middle->countChild = 2;
                nodeToCorrect->middle->middle = nodeToCorrect->middle->right;
                nodeToCorrect->middle->rightNum = 0;
                nodeToCorrect->middle->right = NULL;
                nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxValue;
            }

            nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
            nodeToCorrect->rightNum = nodeToCorrect->middle->maxValue;
            nodeToCorrect->maxValue = nodeToCorrect->right->maxValue;
        }
        else if (nodeToCorrect->middle == nodeToDeleteParent)
        {
            if (nodeToCorrect->left->countChild == 3)
            {
                if (nodeToDeleteParent->middle == nodeToDelete)
                    nodeToDeleteParent->middle = nodeToDeleteParent->left;

                nodeToDeleteParent->left = nodeToCorrect->left->right;
                nodeToDeleteParent->left->parent = nodeToDeleteParent;
                nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxValue;
                nodeToDeleteParent->maxValue = nodeToDeleteParent->middle->maxValue;

                nodeToCorrect->left->countChild = 2;
                nodeToCorrect->left->rightNum = 0;
                nodeToCorrect->left->right = NULL;
                nodeToCorrect->left->maxValue = nodeToCorrect->left->middle->maxValue;
            }
            else
            {
                if (nodeToDeleteParent->left == nodeToDelete)
                    nodeToDeleteParent->left = nodeToDeleteParent->middle;

                nodeToDeleteParent->middle = nodeToCorrect->right->left;
                nodeToDeleteParent->middle->parent = nodeToDeleteParent;
                nodeToDeleteParent->left->parent = nodeToDeleteParent;
                nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxValue;
                nodeToDeleteParent->maxValue = nodeToDeleteParent->middle->maxValue;

                nodeToCorrect->right->left = nodeToCorrect->right->middle;
                nodeToCorrect->right->middle = nodeToCorrect->right->right;
                nodeToCorrect->right->countChild = 2;
                nodeToCorrect->right->rightNum = 0;
                nodeToCorrect->right->right = NULL;
                nodeToCorrect->right->leftNum = nodeToCorrect->right->left->maxValue;
                nodeToCorrect->right->maxValue = nodeToCorrect->right->middle->maxValue;
            }

            nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
            nodeToCorrect->rightNum = nodeToCorrect->middle->maxValue;
            nodeToCorrect->maxValue = nodeToCorrect->right->maxValue;
        }
        else
        {
            if (nodeToDeleteParent->middle == nodeToDelete)
                nodeToDeleteParent->middle = nodeToDeleteParent->left;

            if (nodeToCorrect->middle->countChild == 2)
            {
                nodeToDeleteParent->left = nodeToCorrect->middle->middle;
                nodeToDeleteParent->left->parent = nodeToDeleteParent;

                nodeToCorrect->middle->middle = nodeToCorrect->middle->left;

                nodeToCorrect->middle->left = nodeToCorrect->left->right;
                nodeToCorrect->middle->left->parent = nodeToCorrect->middle;

                nodeToCorrect->left->countChild = 2;
                nodeToCorrect->left->rightNum = 0;
                nodeToCorrect->left->right = NULL;
                nodeToCorrect->left->maxValue = nodeToCorrect->left->middle->maxValue;

                nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxValue;
                nodeToCorrect->middle->maxValue = nodeToCorrect->middle->middle->maxValue;
            }
            else
            {
                nodeToDeleteParent->left = nodeToCorrect->middle->right;
                nodeToDeleteParent->left->parent = nodeToDeleteParent;

                nodeToCorrect->middle->countChild = 2;
                nodeToCorrect->middle->rightNum = 0;
                nodeToCorrect->middle->right = NULL;
                nodeToCorrect->middle->maxValue = nodeToCorrect->middle->middle->maxValue;
            }
            nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxValue;
            nodeToDeleteParent->maxValue = nodeToDeleteParent->middle->maxValue;

            nodeToCorrect->leftNum = nodeToCorrect->left->maxValue;
            nodeToCorrect->rightNum = nodeToCorrect->middle->maxValue;
            nodeToCorrect->maxValue = nodeToCorrect->right->maxValue;
        }
    }

    CorrectNodePath(nodeToCorrect);
    return;
}

void DeleteNodesFromTree(tree_t** tree, tree_t* nodeParent, tree_t* node)
{
    if (nodeParent->parent == NULL && nodeParent->countChild == 2)
    {
        if (nodeParent->left == node)
            *tree = nodeParent->middle;
        else
            *tree = nodeParent->left;
        (*tree)->parent = NULL;

        free(nodeParent);
        free(node);
    }
    else if (nodeParent->parent == NULL)
    {
        nodeParent->countChild = 2;
        if (nodeParent->left == node)
        {
            nodeParent->left = nodeParent->middle;
            nodeParent->middle = nodeParent->right;
        }
        else if (nodeParent->middle == node)
            nodeParent->middle = nodeParent->right;

        nodeParent->right = NULL;
        nodeParent->rightNum = 0;
        nodeParent->maxValue = nodeParent->middle->maxValue;
        nodeParent->leftNum = nodeParent->left->maxValue;
        free(node);
    }
    else
    {
        if (nodeParent->parent->countChild == 2 && nodeParent->parent->left->countChild == 2 && nodeParent->parent->middle->countChild == 2)
        {
            Correct2ParentsTreesLowChild(nodeParent->parent, node);
            DeleteNodesFromTree(tree, nodeParent->parent, nodeParent);
        }
        else if (nodeParent->parent->countChild == 2)
        {
            Correct2ParentsTrees(nodeParent->parent, node);
            free(node);
        }
        else
        {
            Correct3ParentsTrees(nodeParent->parent, node);
            free(node);
        }
    }
}


bool Delete(tree_t** tree, int element)
{
    tree_t* tmp = *tree;
    tree_t* tmpParent = NULL;

    if (*tree == NULL)
        return false;

    while (tmp != NULL && tmp->isLeaf == false)
    {
        tmpParent = tmp;

        if (tmp->countChild == 2)
        {
            if (element <= tmp->leftNum)
                tmp = tmp->left;
            else
                tmp = tmp->middle;
        }
        else
        {
            if (element <= tmp->leftNum)
                tmp = tmp->left;
            else if (tmp->leftNum < element && element <= tmp->rightNum)
                tmp = tmp->middle;
            else if (tmp->rightNum < element)
                tmp = tmp->right;
        }
    }
    if (tmp == NULL || (tmp != NULL && tmp->value != element))
        return false;

    if (tmpParent == NULL)
        *tree = NULL;

    else if (tmpParent->parent == NULL)
    {
        if (tmpParent->countChild == 2)
        {
            if (tmp == tmpParent->left)
                *tree = tmpParent->middle;
            else
                *tree = tmpParent->left;

            (*tree)->parent = NULL;
            free(tmpParent);
        }
        else
        {
            tmpParent->countChild = 2;
            if (tmpParent->left == tmp)
            {
                tmpParent->left = tmpParent->middle;
                tmpParent->middle = tmpParent->right;
            }
            else if (tmpParent->middle == tmp)
                tmpParent->middle = tmpParent->right;

            tmpParent->maxValue = tmpParent->middle->value;
            tmpParent->leftNum = tmpParent->left->value;
            tmpParent->right = NULL;
            tmpParent->rightNum = 0;

            CorrectNodePath(tmpParent);
        }
    }
    else
    {
        if (tmpParent->countChild == 3)
        {
            tmpParent->countChild = 2;
            if (tmpParent->left == tmp)
            {
                tmpParent->left = tmpParent->middle;
                tmpParent->middle = tmpParent->right;
            }
            else if (tmpParent->middle == tmp)
                tmpParent->middle = tmpParent->right;

            tmpParent->maxValue = tmpParent->middle->value;
            tmpParent->leftNum = tmpParent->left->value;
            tmpParent->right = NULL;
            tmpParent->rightNum = 0;

            CorrectNodePath(tmpParent);
        }
        else
        {
            if (tmpParent->parent->countChild == 2 && tmpParent->parent->left->countChild == 2 && tmpParent->parent->middle->countChild == 2)
            {
                Correct2ParentsTreesLowChild(tmpParent->parent, tmp);
                DeleteNodesFromTree(tree, tmpParent->parent, tmpParent);
            }
            else if (tmpParent->parent->countChild == 2)
                Correct2ParentsTrees(tmpParent->parent, tmp);
            else
                Correct3ParentsTrees(tmpParent->parent, tmp);
        }
    }

    free(tmp);
    return true;
}


