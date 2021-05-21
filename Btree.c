#include "Btree.h"

static int removeNode(node_t* node, int key);

void BTreeInit(btree_t* tree) {
    tree->root = NULL;
}

static int bTreeSplitChild(node_t* node, int index) {
    if (index > 2 * T - 1)
        return ERROR_IND;
    else if (node == NULL)
        return MFAIL;
    else {
        node_t* newNode = (node_t*)malloc(sizeof(node_t));
        node_t* childNode = node->children[index];

        if (newNode == NULL)
            return ERROR_MEM;

        newNode->leaf = childNode->leaf;
        newNode->count = T - 1;
        memcpy(&newNode->key[0], &childNode->key[T], (T - 1) * sizeof(int));

        if (childNode->leaf == FALSE)
            memcpy(&newNode->children[0], &childNode->children[T], (T) * sizeof(node_t*));
        childNode->count = T - 1;

        if (node->count > index)
            memmove(&node->children[index + 2], &node->children[index + 1], (node->count - index) * sizeof(node_t*));
        node->children[index + 1] = newNode;

        if (node->count > index)
            memmove(&node->key[index + 1], &node->key[index], (node->count - index) * sizeof(int));
        node->key[index] = childNode->key[T - 1];
        node->count++;

        return SUCCESS;
    }
}


int BTreeInsert(btree_t* tree, int key) {
    int index = 0;
    node_t* node;

    if (tree == NULL)
        return MFAIL;

    if (tree->root == NULL) {
        node_t* newRoot = (node_t*)malloc(sizeof(node_t));

        if (newRoot == NULL)
            return ERROR_MEM;

        newRoot->count = 0;
        newRoot->leaf = TRUE;

        tree->root = newRoot;
    }
    else if (tree->root->count == 2 * T - 1) {
        node_t* newRoot = (node_t*)malloc(sizeof(node_t));

        if (newRoot == NULL)
            return ERROR_MEM;

        newRoot->children[0] = tree->root;
        newRoot->leaf = FALSE;
        newRoot->count = 0;

        tree->root = newRoot;
    }
    else if (tree->root->count > 0) {
        index = binarySearch(tree->root->key, tree->root->count, key);
        if (index < tree->root->count && tree->root->key[index] == key)
            return SUCCESS;
    }

    node = tree->root;
    while (node->leaf == FALSE) {
        if (node->children[index]->count == 2 * T - 1) {
            if (bTreeSplitChild(node, index) != SUCCESS)
                return MFAIL;

            if (key > node->key[index])
                index++;
        }
        if (index < node->count && node->key[index] == key)
            return SUCCESS;
        node = node->children[index];
        index = binarySearch(node->key, node->count, key);
        if (index < node->count && node->key[index] == key)
            return SUCCESS;
    }

    if (node->count > index)
        memmove(&node->key[index + 1], &node->key[index], (node->count - index) * sizeof(int));
    node->key[index] = key;
    node->count++;

    return SUCCESS;
}

static int binarySearch(int arr[], int length, int key) {
    int first = 0;
    int last = length;

    if (length == 0)
        return 0;
    if (key < arr[first])
        return 0;
    if (key > arr[last - 1])
        return last;

    while (first < last)
        if (key <= arr[first + (last - first) / 2])
            last = first + (last - first) / 2;
        else
            first = first + (last - first) / 2 + 1;

    return last;
}

node_t* BTreeFind(btree_t* tree, int key) {
    int index = 0;
    node_t* node;

    if (tree == NULL)
        return NULL;

    node = tree->root;
    if (node == NULL)
        return NULL;

    while (node->leaf == FALSE) {
        index = binarySearch(node->key, node->count, key);

        if (index < node->count && node->key[index] == key)
            return node;

        node = node->children[index];
    }
    index = binarySearch(node->key, node->count, key);

    if (index < node->count && node->key[index] == key)
        return node;
    else
        return NULL;
}

static void clear(node_t* node) {

    int counter;

    if (node->leaf == FALSE) {
        for (counter = 0; counter <= node->count; counter++) {
            clear(node->children[counter]);
            free(node->children[counter]);
        }
    }
    else
        return;
}

void BTreeClear(btree_t* tree) {

    if (tree->root != NULL) {
        clear(tree->root);
        free(tree->root);
        tree->root = NULL;
    }

}

static void print(node_t* node, int level) {
    int i;

    if (node != NULL && level >= 0) {
        for (i = 0; i < level; i++)
            printf("    ");
        for (i = 0; i < node->count; i++) {
            printf("%i", node->key[i]);
            if (i != node->count - 1)
                printf(", ");
        }
        printf("\n");
        if (node->leaf == TRUE)
            return;
        for (i = 0; i <= node->count; i++)
            print(node->children[i], level + 1);
    }
}

void BTreePrint(btree_t* tree) {

    if (tree != NULL && tree->root != NULL)
        print(tree->root, 0);

}

static int getPred(node_t* node, int index) {
    node_t* cur = node->children[index];

    while (cur->leaf == FALSE)
        cur = cur->children[cur->count];

    return cur->key[cur->count - 1];
}

static int getSucc(node_t* node, int index) {

    node_t* cur = node->children[index + 1];

    while (cur->leaf == FALSE)
        cur = cur->children[0];

    return cur->key[0];
}

static void merge(node_t* node, int index) {

    node_t* child = node->children[index];
    node_t* sibling = node->children[index + 1];

    child->key[T - 1] = node->key[index];

    memcpy(&child->key[T], &sibling->key[0], sibling->count * sizeof(int));

    if (child->leaf == FALSE)
        memcpy(&child->children[T], &sibling->children[0], (sibling->count + 1) * sizeof(node_t*));

    if (node->count > index + 1)
        memmove(&node->key[index], &node->key[index + 1], (node->count - index - 1) * sizeof(int));

    if (node->count > index + 1)
        memmove(&node->children[index + 1], &node->children[index + 2], (node->count - index - 1) * sizeof(node_t*));

    child->count += sibling->count + 1;
    node->count--;

    free(sibling);

}

static void removeFromNonLeaf(node_t* node, int index) {

    int k = node->key[index];

    if (node->children[index]->count >= T) {
        int pred = getPred(node, index);

        node->key[index] = pred;
        removeNode(node->children[index], pred);
    }

    else if (node->children[index + 1]->count >= T) {
        int succ = getSucc(node, index);

        node->key[index] = succ;
        removeNode(node->children[index + 1], succ);
    }

    else {
        merge(node, index);
        removeNode(node->children[index], k);
    }

}

static void removeFromLeaf(node_t* node, int index) {

    if (node->count > index + 1)
        memmove(&node->key[index], &node->key[index + 1], (node->count - index - 1) * sizeof(int));

    node->count--;

    return;

}

static void borrowFromNext(node_t* node, int index) {

    node_t* child = node->children[index];
    node_t* sibling = node->children[index + 1];

    child->key[child->count] = node->key[index];

    if (child->leaf == FALSE)
        child->children[child->count + 1] = sibling->children[0];

    node->key[index] = sibling->key[0];

    memmove(&sibling->key[0], &sibling->key[1], (sibling->count - 1) * sizeof(int));

    if (sibling->leaf == FALSE)
        memmove(&sibling->children[0], &sibling->children[1], sibling->count * sizeof(node_t*));

    child->count++;
    sibling->count--;

}

static void borrowFromPrev(node_t* node, int index) {

    node_t* child = node->children[index];
    node_t* sibling = node->children[index - 1];

    memmove(&child->key[1], &child->key[0], child->count * sizeof(int));

    if (child->leaf == FALSE)
        memmove(&child->children[1], &child->children[0], (child->count + 1) * sizeof(node_t*));

    child->key[0] = node->key[index - 1];

    if (child->leaf == FALSE)
        child->children[0] = sibling->children[sibling->count];

    node->key[index - 1] = sibling->key[sibling->count - 1];
    child->count++;
    sibling->count--;

}


static void fill(node_t* node, int index) {

    if (index != 0 && node->children[index - 1]->count >= T)
        borrowFromPrev(node, index);
    else if (index != node->count && node->children[index + 1]->count >= T)
        borrowFromNext(node, index);
    else {
        if (index != node->count)
            merge(node, index);
        else
            merge(node, index - 1);
    }

}

static int removeNode(node_t* node, int key) {

    int index;

    if (node == NULL)
        return MFAIL;

    index = binarySearch(node->key, node->count, key);
    if (index < node->count && node->key[index] == key) {
        if (node->leaf == TRUE)
            removeFromLeaf(node, index);
        else
            removeFromNonLeaf(node, index);
    }
    else {
        int flag = (index == node->count) ? 1 : 0;

        if (node->leaf == TRUE)
            return MFAIL;

        if (node->children[index]->count < T)
            fill(node, index);

        if (flag && index > node->count) {
            if (!removeNode(node->children[index - 1], key))
                return MFAIL;
        }
        else
            if (!removeNode(node->children[index], key))
                return MFAIL;
    }

    return SUCCESS;

}

int BTreeRemove(btree_t* tree, int key) {

    int flag;
    if (tree == NULL)
        return MFAIL;

    flag = removeNode(tree->root, key);

    if (tree->root != NULL) {
        if (tree->root->count == 0) {
            node_t* tmp = tree->root;

            if (tree->root->leaf == TRUE)
                tree->root = NULL;
            else
                tree->root = tree->root->children[0];

            free(tmp);
        }
    }

    if (!flag)
        return MFAIL;

    return SUCCESS;

}