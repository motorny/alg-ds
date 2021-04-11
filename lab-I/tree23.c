#include "tree23.h"

int UnTwoNodes(TreeNode** tree, TreeNode* nodeInTree, TreeNode* newNode)
{
    TreeNode* nodeParent = nodeInTree->parent;

    if (nodeParent == NULL)
    {
        TreeNode* newTreeTop = (TreeNode*)malloc(sizeof(TreeNode));
        if (!newTreeTop)
            return FAIL;

        newTreeTop->isLeaf = false;
        newTreeTop->data = 0;
        newTreeTop->rightNum = 0;
        newTreeTop->childsCount = 2;
        newTreeTop->right = newTreeTop->parent = NULL;
        newTreeTop->maxSubtreeData = newNode->maxSubtreeData;
        newTreeTop->leftNum = nodeInTree->maxSubtreeData;
        newTreeTop->left = nodeInTree;
        newTreeTop->middle = newNode;

        newNode->parent = newTreeTop;
        nodeInTree->parent = newTreeTop;

        *tree = newTreeTop;
        return SUCCESS;
    }
    else if (nodeParent->childsCount == 2)
    {
        nodeParent->childsCount = 3;
        newNode->parent = nodeParent;

        if (newNode->maxSubtreeData < nodeParent->left->maxSubtreeData)
        {
            nodeParent->right = nodeParent->middle;
            nodeParent->middle = nodeParent->left;
            nodeParent->left = newNode;
        }
        else if (newNode->maxSubtreeData > nodeParent->left->maxSubtreeData && newNode->maxSubtreeData < nodeParent->middle->maxSubtreeData)
        {
            nodeParent->right = nodeParent->middle;
            nodeParent->middle = newNode;
        }
        else
            nodeParent->right = newNode;

        nodeParent->leftNum = nodeParent->left->maxSubtreeData;
        nodeParent->rightNum = nodeParent->middle->maxSubtreeData;
        nodeParent->maxSubtreeData = nodeParent->right->maxSubtreeData;

        nodeParent = nodeParent->parent;
        while (nodeParent != NULL)
        {
            if (newNode->maxSubtreeData > nodeParent->maxSubtreeData)
                nodeParent->maxSubtreeData = newNode->maxSubtreeData;
            else
                break;

            nodeParent = nodeParent->parent;
        }

        return SUCCESS;
    }
    else
    {
        TreeNode* leaf1;
        TreeNode* leaf2;
        TreeNode* leaf3;
        TreeNode* leaf4;
        TreeNode* newParentElement = (TreeNode*)malloc(sizeof(TreeNode));
        if (!newParentElement)
            return FAIL;

        if (newNode->maxSubtreeData < nodeParent->left->maxSubtreeData)
        {
            leaf1 = newNode;
            leaf2 = nodeParent->left;
            leaf3 = nodeParent->middle;
            leaf4 = nodeParent->right;
        }
        else if (newNode->maxSubtreeData > nodeParent->left->maxSubtreeData && newNode->maxSubtreeData < nodeParent->middle->maxSubtreeData)
        {
            leaf1 = nodeParent->left;
            leaf2 = newNode;
            leaf3 = nodeParent->middle;
            leaf4 = nodeParent->right;
        }
        else if (newNode->maxSubtreeData > nodeParent->middle->maxSubtreeData && newNode->maxSubtreeData < nodeParent->right->maxSubtreeData)
        {
            leaf1 = nodeParent->left;
            leaf2 = nodeParent->middle;
            leaf3 = newNode;
            leaf4 = nodeParent->right;
        }
        else
        {
            leaf1 = nodeParent->left;
            leaf2 = nodeParent->middle;
            leaf3 = nodeParent->right;
            leaf4 = newNode;
        }

        nodeParent->rightNum = 0;
        nodeParent->childsCount = 2;
        nodeParent->leftNum = leaf1->maxSubtreeData;
        nodeParent->left = leaf1;
        nodeParent->middle = leaf2;
        nodeParent->right = NULL;
        nodeParent->maxSubtreeData = leaf2->maxSubtreeData;

        leaf1->parent = nodeParent;
        leaf2->parent = nodeParent;

        newParentElement->isLeaf = false;
        newParentElement->data = 0;
        newParentElement->rightNum = 0;
        newParentElement->childsCount = 2;
        newParentElement->leftNum = leaf3->maxSubtreeData;
        newParentElement->left = leaf3;
        newParentElement->middle = leaf4;
        newParentElement->right = NULL;
        newParentElement->maxSubtreeData = leaf4->maxSubtreeData;

        leaf3->parent = newParentElement;
        leaf4->parent = newParentElement;

        return UnTwoNodes(tree, nodeParent, newParentElement);
    }
}

void CorrectNodePath(TreeNode* node)
{
    TreeNode* tmp = node;
    TreeNode* tmpParent = NULL;

    if (tmp != NULL)
        tmpParent = tmp->parent;

    while (tmp != NULL && tmpParent != NULL)
    {
        if (tmpParent->childsCount == 2)
        {
            if (tmp == tmpParent->left)
                tmpParent->leftNum = tmp->maxSubtreeData;
            else if (tmp == tmpParent->middle)
                tmpParent->maxSubtreeData = tmp->maxSubtreeData;
        }
        else
        {
            if (tmp == tmpParent->left)
                tmpParent->leftNum = tmp->maxSubtreeData;
            else if (tmp == tmpParent->middle)
                tmpParent->rightNum = tmp->maxSubtreeData;
            else if (tmp == tmpParent->right)
                tmpParent->maxSubtreeData = tmp->maxSubtreeData;
        }

        tmp = tmpParent;
        tmpParent = tmpParent->parent;
    }
}

void Correct2ParentsTreesLowChild(TreeNode* nodeToCorrect, TreeNode* nodeToDelete)
{
    TreeNode* nodeToDeleteParent = nodeToDelete->parent;

    if (nodeToCorrect->childsCount == 2 && nodeToCorrect->left->childsCount == 2 && nodeToCorrect->middle->childsCount == 2)
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

            nodeToCorrect->middle->childsCount = 3;
            nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
            nodeToCorrect->middle->rightNum = nodeToCorrect->middle->middle->maxSubtreeData;
        }
        else
        {
            if (nodeToDelete == nodeToDeleteParent->left)
                nodeToCorrect->left->right = nodeToDeleteParent->middle;
            else
                nodeToCorrect->left->right = nodeToDeleteParent->left;

            nodeToCorrect->left->right->parent = nodeToCorrect->left;

            nodeToCorrect->left->childsCount = 3;
            nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxSubtreeData;
            nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->right->maxSubtreeData;

            nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
        }
    }

    CorrectNodePath(nodeToCorrect);
    return;
}

void Correct2ParentsTrees(TreeNode* nodeToCorrect, TreeNode* nodeToDelete)
{
    TreeNode* nodeToDeleteParent = nodeToDelete->parent;

    if (nodeToCorrect->left == nodeToDeleteParent)
    {
        if (nodeToDeleteParent->left == nodeToDelete)
        {
            nodeToDeleteParent->left = nodeToDeleteParent->middle;
            nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
        }
        nodeToDeleteParent->middle = nodeToCorrect->middle->left;
        nodeToDeleteParent->middle->parent = nodeToDeleteParent;
        nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

        nodeToCorrect->middle->left = nodeToCorrect->middle->middle;
        nodeToCorrect->middle->middle = nodeToCorrect->middle->right;
        nodeToCorrect->middle->right = NULL;
        nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
        nodeToCorrect->middle->rightNum = 0;

        nodeToCorrect->middle->childsCount = 2;
        nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
    }
    else
    {
        if (nodeToDeleteParent->middle == nodeToDelete)
            nodeToDeleteParent->middle = nodeToDeleteParent->left;

        nodeToDeleteParent->left = nodeToCorrect->left->right;
        nodeToDeleteParent->left->parent = nodeToDeleteParent;
        nodeToCorrect->leftNum = nodeToDeleteParent->left->maxSubtreeData;
        nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

        nodeToCorrect->left->childsCount = 2;
        nodeToCorrect->left->rightNum = 0;
        nodeToCorrect->left->right = NULL;
        nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->middle->maxSubtreeData;

        nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;

        nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
        nodeToCorrect->maxSubtreeData = nodeToCorrect->middle->maxSubtreeData;
    }

    CorrectNodePath(nodeToCorrect);
    return;
}

void Correct3ParentsTrees(TreeNode* nodeToCorrect, TreeNode* nodeToDelete)
{
    TreeNode* nodeToDeleteParent = nodeToDelete->parent;

    if (nodeToCorrect->left->childsCount + nodeToCorrect->middle->childsCount + nodeToCorrect->right->childsCount == 6)
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

            nodeToCorrect->childsCount = 2;
            nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
            nodeToCorrect->rightNum = 0;
            nodeToCorrect->left->childsCount = 3;
            nodeToCorrect->left->leftNum = nodeToCorrect->left->left->maxSubtreeData;
            nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxSubtreeData;
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

            nodeToCorrect->childsCount = 2;
            nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->right->maxSubtreeData;
            nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
            nodeToCorrect->rightNum = 0;
            nodeToCorrect->left->childsCount = 3;
            nodeToCorrect->left->rightNum = nodeToCorrect->left->middle->maxSubtreeData;
        }
        else if (nodeToCorrect->right == nodeToDeleteParent)
        {
            if (nodeToDeleteParent->left == nodeToDelete)
                nodeToCorrect->middle->right = nodeToDeleteParent->middle;
            else
                nodeToCorrect->middle->right = nodeToDeleteParent->left;

            nodeToCorrect->middle->right->parent = nodeToCorrect->middle;
            nodeToCorrect->right = NULL;

            nodeToCorrect->childsCount = 2;
            nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
            nodeToCorrect->rightNum = 0;
            nodeToCorrect->middle->maxSubtreeData = nodeToCorrect->middle->right->maxSubtreeData;
            nodeToCorrect->maxSubtreeData = nodeToCorrect->middle->maxSubtreeData;
            nodeToCorrect->middle->childsCount = 3;
            nodeToCorrect->middle->rightNum = nodeToCorrect->middle->middle->maxSubtreeData;
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
            nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
            nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

            nodeToCorrect->middle->left = nodeToCorrect->middle->middle;
            if (nodeToCorrect->middle->childsCount == 2)
            {
                nodeToCorrect->middle->middle = nodeToCorrect->right->left;
                nodeToCorrect->middle->middle->parent = nodeToCorrect->middle;

                nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
                nodeToCorrect->middle->maxSubtreeData = nodeToCorrect->middle->middle->maxSubtreeData;

                nodeToCorrect->right->left = nodeToCorrect->right->middle;
                nodeToCorrect->right->middle = nodeToCorrect->right->right;

                nodeToCorrect->right->childsCount = 2;
                nodeToCorrect->right->rightNum = 0;
                nodeToCorrect->right->right = NULL;
                nodeToCorrect->right->leftNum = nodeToCorrect->right->left->maxSubtreeData;
                nodeToCorrect->right->maxSubtreeData = nodeToCorrect->right->middle->maxSubtreeData;
            }
            else
            {
                nodeToCorrect->middle->childsCount = 2;
                nodeToCorrect->middle->middle = nodeToCorrect->middle->right;
                nodeToCorrect->middle->rightNum = 0;
                nodeToCorrect->middle->right = NULL;
                nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
            }

            nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
            nodeToCorrect->rightNum = nodeToCorrect->middle->maxSubtreeData;
            nodeToCorrect->maxSubtreeData = nodeToCorrect->right->maxSubtreeData;
        }
        else if (nodeToCorrect->middle == nodeToDeleteParent)
        {
            if (nodeToCorrect->left->childsCount == 3)
            {
                if (nodeToDeleteParent->middle == nodeToDelete)
                    nodeToDeleteParent->middle = nodeToDeleteParent->left;

                nodeToDeleteParent->left = nodeToCorrect->left->right;
                nodeToDeleteParent->left->parent = nodeToDeleteParent;
                nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
                nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

                nodeToCorrect->left->childsCount = 2;
                nodeToCorrect->left->rightNum = 0;
                nodeToCorrect->left->right = NULL;
                nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->middle->maxSubtreeData;
            }
            else
            {
                if (nodeToDeleteParent->left == nodeToDelete)
                    nodeToDeleteParent->left = nodeToDeleteParent->middle;

                nodeToDeleteParent->middle = nodeToCorrect->right->left;
                nodeToDeleteParent->middle->parent = nodeToDeleteParent;
                nodeToDeleteParent->left->parent = nodeToDeleteParent;
                nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
                nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

                nodeToCorrect->right->left = nodeToCorrect->right->middle;
                nodeToCorrect->right->middle = nodeToCorrect->right->right;
                nodeToCorrect->right->childsCount = 2;
                nodeToCorrect->right->rightNum = 0;
                nodeToCorrect->right->right = NULL;
                nodeToCorrect->right->leftNum = nodeToCorrect->right->left->maxSubtreeData;
                nodeToCorrect->right->maxSubtreeData = nodeToCorrect->right->middle->maxSubtreeData;
            }

            nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
            nodeToCorrect->rightNum = nodeToCorrect->middle->maxSubtreeData;
            nodeToCorrect->maxSubtreeData = nodeToCorrect->right->maxSubtreeData;
        }
        else
        {
            if (nodeToDeleteParent->middle == nodeToDelete)
                nodeToDeleteParent->middle = nodeToDeleteParent->left;

            if (nodeToCorrect->middle->childsCount == 2)
            {
                nodeToDeleteParent->left = nodeToCorrect->middle->middle;
                nodeToDeleteParent->left->parent = nodeToDeleteParent;

                nodeToCorrect->middle->middle = nodeToCorrect->middle->left;

                nodeToCorrect->middle->left = nodeToCorrect->left->right;
                nodeToCorrect->middle->left->parent = nodeToCorrect->middle;

                nodeToCorrect->left->childsCount = 2;
                nodeToCorrect->left->rightNum = 0;
                nodeToCorrect->left->right = NULL;
                nodeToCorrect->left->maxSubtreeData = nodeToCorrect->left->middle->maxSubtreeData;

                nodeToCorrect->middle->leftNum = nodeToCorrect->middle->left->maxSubtreeData;
                nodeToCorrect->middle->maxSubtreeData = nodeToCorrect->middle->middle->maxSubtreeData;
            }
            else
            {
                nodeToDeleteParent->left = nodeToCorrect->middle->right;
                nodeToDeleteParent->left->parent = nodeToDeleteParent;

                nodeToCorrect->middle->childsCount = 2;
                nodeToCorrect->middle->rightNum = 0;
                nodeToCorrect->middle->right = NULL;
                nodeToCorrect->middle->maxSubtreeData = nodeToCorrect->middle->middle->maxSubtreeData;
            }
            nodeToDeleteParent->leftNum = nodeToDeleteParent->left->maxSubtreeData;
            nodeToDeleteParent->maxSubtreeData = nodeToDeleteParent->middle->maxSubtreeData;

            nodeToCorrect->leftNum = nodeToCorrect->left->maxSubtreeData;
            nodeToCorrect->rightNum = nodeToCorrect->middle->maxSubtreeData;
            nodeToCorrect->maxSubtreeData = nodeToCorrect->right->maxSubtreeData;
        }
    }

    CorrectNodePath(nodeToCorrect);
    return;
}

void DeleteNodesFromTree(TreeNode** tree, TreeNode* nodeParent, TreeNode* node)
{
    if (nodeParent->parent == NULL && nodeParent->childsCount == 2)
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
        nodeParent->childsCount = 2;
        if (nodeParent->left == node)
        {
            nodeParent->left = nodeParent->middle;
            nodeParent->middle = nodeParent->right;
        }
        else if (nodeParent->middle == node)
            nodeParent->middle = nodeParent->right;

        nodeParent->right = NULL;
        nodeParent->rightNum = 0;
        nodeParent->maxSubtreeData = nodeParent->middle->maxSubtreeData;
        nodeParent->leftNum = nodeParent->left->maxSubtreeData;
        free(node);
    }
    else
    {
        if (nodeParent->parent->childsCount == 2 && nodeParent->parent->left->childsCount == 2 && nodeParent->parent->middle->childsCount == 2)
        {
            Correct2ParentsTreesLowChild(nodeParent->parent, node);
            DeleteNodesFromTree(tree, nodeParent->parent, nodeParent);
        }
        else if (nodeParent->parent->childsCount == 2)
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

int Insert(TreeNode** tree, int newElement)
{
    TreeNode* tmp = *tree;
    TreeNode* tmpParent = NULL;
    TreeNode* newTtTreeLeaf = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newTtTreeLeaf)
        return FAIL;

    newTtTreeLeaf->isLeaf = true;
    newTtTreeLeaf->data = newTtTreeLeaf->maxSubtreeData = newElement;

    newTtTreeLeaf->childsCount = 0;
    newTtTreeLeaf->leftNum = 0;
    newTtTreeLeaf->rightNum = 0;
    newTtTreeLeaf->left = NULL;
    newTtTreeLeaf->right = NULL;
    newTtTreeLeaf->middle = NULL;

    if (*tree != NULL)
    {
        while (tmp != NULL && tmp->isLeaf == false)
        {
            tmpParent = tmp;

            if (tmp->childsCount == 2)
            {
                if (newElement <= tmp->leftNum)
                    tmp = tmp->left;
                else
                    tmp = tmp->middle;
            }
            else
            {
                if (newElement <= tmp->leftNum)
                    tmp = tmp->left;
                else if (tmp->leftNum < newElement && newElement <= tmp->rightNum)
                    tmp = tmp->middle;
                else if (tmp->rightNum < newElement)
                    tmp = tmp->right;
            }
        }
        if (tmp != NULL && tmp->data == newElement)
        {
            free(newTtTreeLeaf);
            return FAIL;
        }

        if (tmpParent != NULL)
        {
            if (tmpParent->childsCount == 2)
            {
                tmpParent->childsCount = 3;
                newTtTreeLeaf->parent = tmpParent;

                if (newElement < tmpParent->left->data)
                {
                    tmpParent->leftNum = newElement;
                    tmpParent->rightNum = tmpParent->left->data;
                    tmpParent->right = tmpParent->middle;
                    tmpParent->middle = tmpParent->left;
                    tmpParent->left = newTtTreeLeaf;
                }
                else if (newElement < tmpParent->middle->data && newElement > tmpParent->left->data)
                {
                    tmpParent->rightNum = newElement;
                    tmpParent->right = tmpParent->middle;
                    tmpParent->middle = newTtTreeLeaf;
                }
                else
                {
                    tmpParent->rightNum = tmpParent->middle->data;
                    tmpParent->right = newTtTreeLeaf;
                }
                tmpParent->maxSubtreeData = tmpParent->right->data;

                tmpParent = tmpParent->parent;
                while (tmpParent != NULL)
                {
                    if (newElement > tmpParent->maxSubtreeData)
                        tmpParent->maxSubtreeData = newElement;
                    else
                        break;

                    tmpParent = tmpParent->parent;
                }

                return SUCCESS;
            }
            else
            {
                TreeNode* leaf1;
                TreeNode* leaf2;
                TreeNode* leaf3;
                TreeNode* leaf4;
                TreeNode* newParentElement = (TreeNode*)malloc(sizeof(TreeNode));
                if (!newParentElement)
                {
                    free(newTtTreeLeaf);
                    return FAIL;
                }

                if (newElement < tmpParent->left->data)
                {
                    leaf1 = newTtTreeLeaf;
                    leaf2 = tmpParent->left;
                    leaf3 = tmpParent->middle;
                    leaf4 = tmpParent->right;
                }
                else if (newElement > tmpParent->left->data&& newElement < tmpParent->middle->data)
                {
                    leaf1 = tmpParent->left;
                    leaf2 = newTtTreeLeaf;
                    leaf3 = tmpParent->middle;
                    leaf4 = tmpParent->right;
                }
                else if (newElement > tmpParent->middle->data&& newElement < tmpParent->right->data)
                {
                    leaf1 = tmpParent->left;
                    leaf2 = tmpParent->middle;
                    leaf3 = newTtTreeLeaf;
                    leaf4 = tmpParent->right;
                }
                else
                {
                    leaf1 = tmpParent->left;
                    leaf2 = tmpParent->middle;
                    leaf3 = tmpParent->right;
                    leaf4 = newTtTreeLeaf;
                }

                tmpParent->childsCount = 2;
                tmpParent->rightNum = 0;
                tmpParent->leftNum = leaf1->data;
                tmpParent->left = leaf1;
                tmpParent->middle = leaf2;
                tmpParent->right = NULL;
                tmpParent->maxSubtreeData = leaf2->data;

                leaf1->parent = tmpParent;
                leaf2->parent = tmpParent;

                newParentElement->isLeaf = false;
                newParentElement->data = 0;
                newParentElement->rightNum = 0;
                newParentElement->childsCount = 2;
                newParentElement->leftNum = leaf3->data;
                newParentElement->left = leaf3;
                newParentElement->middle = leaf4;
                newParentElement->right = NULL;
                newParentElement->maxSubtreeData = leaf4->data;

                leaf3->parent = newParentElement;
                leaf4->parent = newParentElement;

                return UnTwoNodes(tree, tmpParent, newParentElement);
            }
        }
        else
        {
            TreeNode* newParentElement = (TreeNode*)malloc(sizeof(TreeNode));
            if (!newParentElement)
            {
                free(newTtTreeLeaf);
                return FAIL;
            }
            newTtTreeLeaf->parent = tmp->parent = newParentElement;

            newParentElement->parent = NULL;
            newParentElement->childsCount = 2;
            newParentElement->isLeaf = false;
            newParentElement->data = 0;
            newParentElement->rightNum = 0;
            newParentElement->right = NULL;

            if (tmp->data < newElement)
            {
                newParentElement->left = tmp;
                newParentElement->leftNum = tmp->data;
                newParentElement->middle = newTtTreeLeaf;
            }
            else
            {
                newParentElement->left = newTtTreeLeaf;
                newParentElement->leftNum = newTtTreeLeaf->data;
                newParentElement->middle = tmp;
            }
            newParentElement->maxSubtreeData = newParentElement->middle->data;

            *tree = newParentElement;
            return SUCCESS;
        }
    }
    else
    {
        newTtTreeLeaf->parent = NULL;
        *tree = newTtTreeLeaf;
    }

    return SUCCESS;
}

int Delete(TreeNode** tree, int element)
{
    TreeNode* tmp = *tree;
    TreeNode* tmpParent = NULL;

    if (*tree == NULL)
        return FAIL;

    while (tmp != NULL && tmp->isLeaf == false)
    {
        tmpParent = tmp;

        if (tmp->childsCount == 2)
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
    if (tmp == NULL || (tmp != NULL && tmp->data != element))
        return FAIL;

    if (tmpParent == NULL)
        *tree = NULL;

    else if (tmpParent->parent == NULL)
    {
        if (tmpParent->childsCount == 2)
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
            tmpParent->childsCount = 2;
            if (tmpParent->left == tmp)
            {
                tmpParent->left = tmpParent->middle;
                tmpParent->middle = tmpParent->right;
            }
            else if (tmpParent->middle == tmp)
                tmpParent->middle = tmpParent->right;

            tmpParent->maxSubtreeData = tmpParent->middle->data;
            tmpParent->leftNum = tmpParent->left->data;
            tmpParent->right = NULL;
            tmpParent->rightNum = 0;

            CorrectNodePath(tmpParent);
        }
    }
    else
    {
        if (tmpParent->childsCount == 3)
        {
            tmpParent->childsCount = 2;
            if (tmpParent->left == tmp)
            {
                tmpParent->left = tmpParent->middle;
                tmpParent->middle = tmpParent->right;
            }
            else if (tmpParent->middle == tmp)
                tmpParent->middle = tmpParent->right;

            tmpParent->maxSubtreeData = tmpParent->middle->data;
            tmpParent->leftNum = tmpParent->left->data;
            tmpParent->right = NULL;
            tmpParent->rightNum = 0;

            CorrectNodePath(tmpParent);
        }
        else
        {
            if (tmpParent->parent->childsCount == 2 && tmpParent->parent->left->childsCount == 2 && tmpParent->parent->middle->childsCount == 2)
            {
                Correct2ParentsTreesLowChild(tmpParent->parent, tmp);
                DeleteNodesFromTree(tree, tmpParent->parent, tmpParent);
            }
            else if (tmpParent->parent->childsCount == 2)
                Correct2ParentsTrees(tmpParent->parent, tmp);
            else
                Correct3ParentsTrees(tmpParent->parent, tmp);
        }
    }

    free(tmp);
    return SUCCESS;
}

int Find(TreeNode* tree, int element)
{
    TreeNode* tmp = tree;

    while (tmp != NULL && tmp->isLeaf == false)
    {
        if (tmp->childsCount == 2)
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

    if (tmp == NULL)
        return FAIL;
    else if (tmp->data == element)
        return SUCCESS;
    else
        return FAIL;
}

int Push(treeStackNode** stack, TreeNode* newTree)
{
    treeStackNode* newNode = (treeStackNode*)malloc(sizeof(treeStackNode));
    if (newTree == NULL || newNode == NULL)
        return FAIL;

    newNode->currentTree = newTree;
    newNode->nextTree = *stack;
    *stack = newNode;
    return SUCCESS;
}

int Pop(treeStackNode** stack, TreeNode** treeFromStack)
{
    treeStackNode* nodeToDelete = *stack;
    if (*stack == NULL)
    {
        *treeFromStack = NULL;
        return FAIL;
    }

    *treeFromStack = (*stack)->currentTree;
    *stack = (*stack)->nextTree;
    free(nodeToDelete);
    return SUCCESS;
}

int GetHeight(TreeNode* tree)
{
    int i = 0;
    TreeNode *tmp = tree;

    while (tmp != NULL)
    {
        i++;
        tmp = tmp->left;
    }

    return i;
}

int GetMinElement(TreeNode* tree)
{
    TreeNode* tmp = tree;

    while (tmp != NULL && tmp->isLeaf == false)
        tmp = tmp->left;

    if (tmp == NULL)
        return 0;
    else
        return tmp->data;
}

int UnTwoFromLeft(TreeNode** tree, TreeNode* treeNewInLeft, TreeNode* treeBroOfNew)
{
    TreeNode *broParent = treeBroOfNew->parent;

    if (broParent == 0)
    {
        TreeNode* newParent = (TreeNode*)malloc(sizeof(TreeNode));
        if (newParent == NULL)
            return FAIL;

        newParent->isLeaf = false;
        newParent->data = 0;
        newParent->rightNum = 0;
        newParent->leftNum = treeNewInLeft->maxSubtreeData;
        newParent->maxSubtreeData = treeBroOfNew->maxSubtreeData;
        newParent->childsCount = 2;

        newParent->left = treeNewInLeft;
        newParent->middle = treeBroOfNew;
        newParent->right = newParent->parent = NULL;

        treeNewInLeft->parent = newParent;
        treeBroOfNew->parent = newParent;

        *tree = newParent;
        return SUCCESS;
    }
    if (broParent->childsCount == 2)
    {
        broParent->childsCount = 3;
        broParent->right = broParent->middle;
        broParent->middle = broParent->left;
        broParent->left = treeNewInLeft;
        treeNewInLeft->parent = broParent;

        broParent->rightNum = broParent->middle->maxSubtreeData;
        broParent->leftNum = broParent->left->maxSubtreeData;

        return SUCCESS;
    }
    if (broParent->childsCount == 3)
    {
        TreeNode* newNodeToNewLeft = (TreeNode*)malloc(sizeof(TreeNode));
        if (newNodeToNewLeft == NULL)
            return FAIL;

        newNodeToNewLeft->isLeaf = false;
        newNodeToNewLeft->data = 0;
        newNodeToNewLeft->rightNum = 0;
        newNodeToNewLeft->childsCount = 2;

        newNodeToNewLeft->left = treeNewInLeft;
        newNodeToNewLeft->middle = broParent->left;
        newNodeToNewLeft->right = newNodeToNewLeft->parent = NULL;

        newNodeToNewLeft->leftNum = treeNewInLeft->maxSubtreeData;
        newNodeToNewLeft->maxSubtreeData = newNodeToNewLeft->middle->maxSubtreeData;

        treeNewInLeft->parent = newNodeToNewLeft;
        treeBroOfNew->parent = newNodeToNewLeft;

        broParent->childsCount = 2;
        broParent->left = broParent->middle;
        broParent->middle = broParent->right;
        broParent->right = NULL;
        broParent->rightNum = 0;
        broParent->leftNum = broParent->left->maxSubtreeData;

        return UnTwoFromLeft(tree, newNodeToNewLeft, broParent);
    }
    return SUCCESS;
}

int UnTwoFromRight(TreeNode** tree, TreeNode* treeNewInRight, TreeNode* treeBroOfNew)
{
    TreeNode* broParent = treeBroOfNew->parent;
    TreeNode* tmp;

    if (broParent == 0)
    {
        TreeNode* newParent = (TreeNode*)malloc(sizeof(TreeNode));
        if (newParent == NULL)
            return FAIL;

        newParent->isLeaf = false;
        newParent->data = 0;
        newParent->rightNum = 0;
        newParent->leftNum = treeBroOfNew->maxSubtreeData;
        newParent->maxSubtreeData = treeNewInRight->maxSubtreeData;
        newParent->childsCount = 2;

        newParent->left = treeBroOfNew;
        newParent->middle = treeNewInRight;
        newParent->right = newParent->parent = NULL;

        treeNewInRight->parent = newParent;
        treeBroOfNew->parent = newParent;

        *tree = newParent;
        return SUCCESS;
    }
    if (broParent->childsCount == 2)
    {
        broParent->childsCount = 3;
        broParent->right = treeNewInRight;
        treeNewInRight->parent = broParent;

        broParent->rightNum = broParent->middle->maxSubtreeData;
        broParent->maxSubtreeData = broParent->right->maxSubtreeData;

        broParent = broParent->parent;
        while (broParent != NULL)
        {
            if (treeNewInRight->maxSubtreeData > broParent->maxSubtreeData)
                broParent->maxSubtreeData = treeNewInRight->maxSubtreeData;
            else
                break;

            broParent = broParent->parent;
        }

        return SUCCESS;
    }
    if (broParent->childsCount == 3)
    {
        TreeNode* newNodeToNewRight = (TreeNode*)malloc(sizeof(TreeNode));
        if (newNodeToNewRight == NULL)
            return FAIL;

        newNodeToNewRight->isLeaf = false;
        newNodeToNewRight->data = 0;
        newNodeToNewRight->rightNum = 0;
        newNodeToNewRight->childsCount = 2;

        newNodeToNewRight->left = broParent->right;
        newNodeToNewRight->middle = treeNewInRight;
        newNodeToNewRight->right = newNodeToNewRight->parent = NULL;

        newNodeToNewRight->leftNum = newNodeToNewRight->left->maxSubtreeData;
        newNodeToNewRight->maxSubtreeData = newNodeToNewRight->middle->maxSubtreeData;

        treeNewInRight->parent = newNodeToNewRight;
        treeBroOfNew->parent = newNodeToNewRight;

        broParent->childsCount = 2;
        broParent->right = NULL;
        broParent->rightNum = 0;
        broParent->maxSubtreeData = broParent->middle->maxSubtreeData;

        int prevMax = newNodeToNewRight->left->maxSubtreeData;
        tmp = broParent->parent;
        while (tmp != NULL)
        {
            if (tmp->maxSubtreeData == prevMax)
                if (tmp->childsCount == 2)
                    tmp->maxSubtreeData = tmp->middle->maxSubtreeData;
                else
                    tmp->maxSubtreeData = tmp->right->maxSubtreeData;
            else
                break;

            tmp = tmp->parent;
        }

        return UnTwoFromRight(tree, newNodeToNewRight, broParent);
    }
    return SUCCESS;
}

int Split(TreeNode* tree, TreeNode** tree1, TreeNode** tree2, int elementToSplit)
{
    TreeNode* tmp = tree;
    TreeNode* tmpParent = NULL;
    TreeNode* leftTree = NULL;
    TreeNode* rightTree = NULL;
    TreeNode* nodeToDelete;
    TreeNode* leafNode;
    treeStackNode* stackTreeLeft = NULL;
    treeStackNode* stackTreeRight = NULL;

    *tree1 = NULL;
    *tree2 = NULL;

    if (tree == NULL)
        return FAIL;

    while (tmp != NULL && tmp->isLeaf == false)
    {
        tmpParent = tmp;

        if (tmp->childsCount == 2)
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

    if (tmp == NULL || (tmp != NULL && tmp->data != elementToSplit))
        return FAIL;

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
            if (tmpParent->childsCount == 2 && tmp == tmpParent->left)
            {
                tmpParent->middle->parent = NULL;
                Push(&stackTreeRight, tmpParent->middle);
            }
            else if (tmpParent->childsCount == 2 && tmp == tmpParent->middle)
            {
                tmpParent->left->parent = NULL;
                Push(&stackTreeLeft, tmpParent->left);
            }
            else if (tmpParent->childsCount == 3 && tmp == tmpParent->left)
            {
                tmpParent->middle->parent = tmpParent->right->parent = NULL;
                Push(&stackTreeRight, tmpParent->middle);
                Push(&stackTreeRight, tmpParent->right);
            }
            else if (tmpParent->childsCount == 3 && tmp == tmpParent->middle)
            {
                tmpParent->left->parent = tmpParent->right->parent = NULL;
                Push(&stackTreeLeft, tmpParent->left);
                Push(&stackTreeRight, tmpParent->right);
            }
            else if (tmpParent->childsCount == 3 && tmp == tmpParent->right)
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

    return SUCCESS;
}

int Merge(TreeNode** tree, TreeNode* tree1, TreeNode* tree2)
{
    int firstLength = GetHeight(tree1);
    int secondLength = GetHeight(tree2);
    int tmpLength;

    int firstMin = GetMinElement(tree1);
    int secondMin = GetMinElement(tree2);
    int tmpMin;

    TreeNode* tmp;
    TreeNode* oldTreePtr = *tree;
    TreeNode* tmpParent;

    if (tree1 == NULL && tree2 == NULL)
    {
        *tree = NULL;
        return FAIL;
    }
    else if (tree1 == NULL)
    {
        *tree = tree2;
        return SUCCESS;
    }
    else if (tree2 == NULL)
    {
        *tree = tree1;
        return SUCCESS;
    }

    if (!(secondMin > tree1->maxSubtreeData || firstMin > tree2->maxSubtreeData))
    {
        *tree = NULL;
        return FAIL;
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
        TreeNode *newTreeTop = (TreeNode*)malloc(sizeof(TreeNode));
        if (newTreeTop == NULL)
            return FAIL;

        newTreeTop->isLeaf = false;
        newTreeTop->data = 0;
        newTreeTop->rightNum = 0;
        newTreeTop->childsCount = 2;
        newTreeTop->right = NULL;
        newTreeTop->parent = NULL;

        tree1->parent = newTreeTop;
        tree2->parent = newTreeTop;

        if (secondMin > tree1->maxSubtreeData)
        {
            newTreeTop->left = tree1;
            newTreeTop->middle = tree2;
        }
        else
        {
            newTreeTop->left = tree1;
            newTreeTop->middle = tree2;
        }
        newTreeTop->leftNum = newTreeTop->left->maxSubtreeData;
        newTreeTop->maxSubtreeData = newTreeTop->middle->maxSubtreeData;
        *tree = newTreeTop;
        return SUCCESS;
    }
    else
    {
        tmp = tree1;
        tmpParent = NULL;
        if (firstMin > tree2->maxSubtreeData)
        {
            for (int i = 0; i < firstLength - secondLength; i++)
                tmpParent = tmp, tmp = tmp->left;

            UnTwoFromLeft(tree, tree2, tmp);
            if (*tree == oldTreePtr)
                *tree = tree1;
        }
        else
        {
            for (int i = 0; i < firstLength - secondLength; i++)
            {
                tmpParent = tmp;
                if (tree1->childsCount == 2)
                    tmp = tmp->middle;
                else
                    tmp = tmp->right;
            }

            UnTwoFromRight(tree, tree2, tmp);
            if (*tree == oldTreePtr)
                *tree = tree1;
        }
    }
    return SUCCESS;
}
