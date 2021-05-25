
////////////////////////////
// B-Tree.h
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define TRUE 1
#define FALSE 0
//b-tree param, >=2
#define T 3

typedef struct node_t {
    int size;
    int values[T - 1];
    struct node_t* child[T];
}node_t;

typedef struct {
    int t;
    node_t* root;
} tree_t;

////////////////////////////
// B-Tree.cpp
node_t* CreateNode(int value);
int InsertNode(tree_t* tree, int value);
int RemoveNode(tree_t* tree, int value);
int FindNode(tree_t* tree, int value);
void PrintTree(node_t* root, int level);
void TreeMain(tree_t tree);

node_t* CreateNode(int value) {
    node_t* tmp = (node_t*)malloc(sizeof(node_t));
    if (!tmp) {
        exit(-1);
    }
    else {
        tmp->size = 0;
    }
    return tmp;
}

static int returnPosition(int value, int* values, int size) {
    int position = 0;
    while (position < size && value > values[position])
        position++;
    return position;
}

static int addInNode(node_t* node, int value, int* sValue, node_t** sNode, int t) {
    node_t* newNode, * endNode;

    int position, sPosition, newValue, result, endValue;

    if (node == NULL) {
        *sNode = NULL;
        *sValue = value;
        return -1;
    }

    position = returnPosition(value, node->values, node->size);

    if (position < node->size && value == node->values[position])
        return FALSE;

    result = addInNode(node->child[position], value, &newValue, &newNode, t);

    if (result != -1)
        return result;

    if (node->size < t - 1) {
        position = returnPosition(newValue, node->values, node->size);
        for (int i = node->size; i > position; i--) {
            node->values[i] = node->values[i - 1];
            node->child[i + 1] = node->child[i];
        }

        node->values[position] = newValue;
        node->child[position + 1] = newNode;
        node->size++;
        return TRUE;
    }

    if (position == t - 1) {
        endValue = newValue;
        endNode = newNode;
    }
    else {
        endValue = node->values[t - 2];
        endNode = node->child[t - 1];
        for (int i = t - 2; i > position; i--) {
            node->values[i] = node->values[i - 1];
            node->child[i + 1] = node->child[i];
        }

        node->values[position] = newValue;
        node->child[position + 1] = newNode;
    }
    sPosition = (t - 1) / 2;
    (*sValue) = node->values[sPosition];

    (*sNode) = CreateNode(t);

    node->size = sPosition;

    (*sNode)->size = t - 1 - sPosition;

    for (int i = 0; i < (*sNode)->size; i++)
    {
        (*sNode)->child[i] = node->child[i + sPosition + 1];
        (*sNode)->values[i] = i < (*sNode)->size - 1 ? node->values[i + sPosition + 1] : endValue;
    }
    (*sNode)->child[(*sNode)->size] = endNode;
    return -1;
}

int  InsertNode(tree_t* tree, int value) {
    node_t* tmp;
    int tmpValue;
    if (!tree)
        return FALSE;
    int result = addInNode(tree->root, value, &tmpValue, &tmp, tree->t);

    if (result == -1) {
        node_t* tmpRoot = tree->root;
        tree->root = CreateNode(tree->t);
        tree->root->size = 1;
        tree->root->values[0] = tmpValue;
        tree->root->child[0] = tmpRoot;
        tree->root->child[1] = tmp;
    }
    return result;
}

static int deleteInNode(node_t* node, int value, int t, int IsRoot) {
    int position, rotate, min, tmpValue;

    node_t* leftNode, * rightNode;

    if (node == NULL)
        return 0;
    min = (t - 1) / 2;
    if (IsRoot)
        min = 1;
    position = returnPosition(value, node->values, node->size);

    if (node->child[0] == NULL) {
        if (position == node->size || value < node->values[position])
            return 0;

        for (int i = position + 1; i < node->size; i++) {
            node->values[i - 1] = node->values[i];
            node->child[i] = node->child[i + 1];
        }
        if (--node->size >= min)
            return 1;
        else
            return -1;
    }

    if (position < node->size && value == node->values[position]) {
        node_t* tmp = node->child[position], * tmp1;
        int nvalue;
        while (TRUE) {
            nvalue = tmp->size;
            tmp1 = tmp->child[nvalue];
            if (tmp1 == NULL)
                break;
            tmp = tmp1;
        }
        node->values[position] = tmp->values[nvalue - 1];
        tmp->values[nvalue - 1] = value;
    }

    tmpValue = deleteInNode(node->child[position], value, t, FALSE);
    if (tmpValue != -1)
        return tmpValue;

    if (position > 0 && node->child[position - 1]->size > min) {
        rotate = position - 1;

        leftNode = node->child[rotate];
        rightNode = node->child[position];
        rightNode->child[rightNode->size + 1] = rightNode->child[rightNode->size];

        for (int i = rightNode->size; i > 0; i--) {
            rightNode->values[i] = rightNode->values[i - 1];
            rightNode->child[i] = rightNode->child[i - 1];
        }

        rightNode->size++;
        rightNode->values[0] = node->values[rotate];
        rightNode->child[0] = leftNode->child[leftNode->size];
        node->values[rotate] = leftNode->values[--leftNode->size];

        return 1;
    }

    if (position < node->size && node->child[position + 1]->size > min) {
        rotate = position;

        leftNode = node->child[rotate];
        rightNode = node->child[rotate + 1];

        leftNode->values[leftNode->size] = node->values[rotate];
        leftNode->child[leftNode->size + 1] = rightNode->child[0];

        node->values[rotate] = rightNode->values[0];

        leftNode->size++;
        rightNode->size--;

        for (int i = 0; i < rightNode->size; i++) {
            rightNode->values[i] = rightNode->values[i + 1];
            rightNode->child[i] = rightNode->child[i + 1];
        }

        rightNode->child[rightNode->size] = rightNode->child[rightNode->size + 1];
        return 1;
    }

    if (position == node->size)
        rotate = position - 1;
    else
        rotate = position;

    leftNode = node->child[rotate];
    rightNode = node->child[rotate + 1];
    leftNode->values[leftNode->size] = node->values[rotate];
    leftNode->child[leftNode->size + 1] = rightNode->child[0];
    for (int i = 0; i < rightNode->size; i++) {
        leftNode->values[leftNode->size + 1 + i] = rightNode->values[i];
        leftNode->child[leftNode->size + 2 + i] = rightNode->child[i + 1];
    }
    leftNode->size += rightNode->size + 1;

    free(rightNode);

    for (int i = position + 1; i < node->size; i++) {
        node->values[i - 1] = node->values[i];
        node->child[i] = node->child[i + 1];
    }
    if (--node->size >= min)
        return 1;
    else
        return -1;
}

int RemoveNode(tree_t* tree, int value) {
    node_t* tmp;
    int result = deleteInNode(tree->root, value, tree->t, TRUE);
    if (result == -1) {
        tmp = tree->root;
        tree->root = tree->root->child[0];
        free(tmp);
        result = 1;
    }
    return result;
}

int FindNode(tree_t* tree, int value) {
    int index, size;
    node_t* root = tree->root;
    node_t* tmp = root;
    while (tmp) {
        size = tmp->size;
        index = returnPosition(value, tmp->values, size);
        if (index < size && value == tmp->values[index])
            return TRUE;
        tmp = tmp->child[index];
    }
    return FALSE;
}


void PrintTree(node_t* root, int level) {
    if (!root)
        return;
    int i;
    for (i = 0; i <= root->size - 1; i++) {
        PrintTree(root->child[i], level + 1);
        for (int j = 0; j <= level; j++)
            printf(" ");
        printf("%d\n", root->values[i]);
    }
    PrintTree(root->child[i], level + 1);
}


void TreeMain(tree_t tree) {
    char func;
    int value, strFuncElem;

    while (TRUE) {
        func = getchar();
        if (func == EOF)
            break;
        while (func == '\0' || func == '\n')
            strFuncElem = getchar();
        strFuncElem = scanf("%i", &value);
        switch (func) {
        case('a'):
            InsertNode(&tree, value);
            break;
        case('r'):
            RemoveNode(&tree, value);
            break;
        case('f'):
            if (FindNode(&tree, value) == 1)
                printf("yes\n");
            else
                printf("no\n");
            break;
        case ('d'):
            PrintTree(tree.root, 0);
            break;
        default:
            break;
        }
        strFuncElem = getchar();
    }
}
////////////////////////////
int main(void) {
    tree_t tree;
    tree.t = T;
    TreeMain(tree);
}