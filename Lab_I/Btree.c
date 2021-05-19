//B tree
#include "BTree.h"

node_t* createNode(int value) {
    node_t* tmp = (node_t*)malloc(sizeof(node_t));
    tmp->size = 0;
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

    (*sNode) = createNode(t);

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

int  addElem(tree_t* root, int value) {
    node_t* tmp;
    int tmpValue;
    if (!root)
        return FALSE;
    int result = addInNode(root->root, value, &tmpValue, &tmp, root->t);

    if (result == -1) {
        node_t* tmpRoot = root->root;
        root->root = createNode(root->t);
        root->root->size = 1;
        root->root->values[0] = tmpValue;
        root->root->child[0] = tmpRoot;
        root->root->child[1] = tmp;
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

int deleteElem(tree_t* Tree, int value) {
    node_t* tmp;
    int result = deleteInNode(Tree->root, value, Tree->t, TRUE);
    if (result == -1) {
        tmp = Tree->root;
        Tree->root = Tree->root->child[0];
        free(tmp);
        result = 1;
    }
    return result;
}

int searchElem(tree_t root, int value) {
    int index, size;
    node_t* tmp = root.root;
    while (tmp) {
        size = tmp->size;
        index = returnPosition(value, tmp->values, size);
        if (index < size && value == tmp->values[index])
            return TRUE;
        tmp = tmp->child[index];
    }
    return FALSE;
}


void printTree(node_t* tree, int lvl) {
    if (!tree)
        return;
    int i;
    for (i = 0; i <= tree->size - 1; i++) {
        printTree(tree->child[i], lvl + 1);
        for (int j = 0; j <= lvl; j++)
            printf(" ");
        printf("%d\n", tree->values[i]);
    }
    printTree(tree->child[i], lvl + 1);
}


void funcTree(tree_t tree) {
    char func;
    int value, strFuncElem;

    while (TRUE) {
        func = getchar();
        if (func == EOF)
            break;
        while (func == '\0' || func == '\n' || isspace(func) != 0)
            strFuncElem = getchar();
        strFuncElem = scanf("%i", &value);
        switch (func) {
        case('a'):
            addElem(&tree, value);
            break;
        case('r'):
            deleteElem(&tree, value);
            break;
        case('f'):
            if (searchElem(tree, value) == 1)
                printf("yes\n");
            else
                printf("no\n");
            break;
        case ('d'):
            printTree(tree.root, 0);
            break;
        default:
            break;
        }
        strFuncElem = getchar();
    }
}