#include"BplsTree.h"

tree_t* CreateTree(void) {
    tree_t* tree = (tree_t*)(malloc(sizeof(tree_t)));
    if (!tree)
        return NULL;

    int i = 0;
    tree->isLeaf = LEAF;
    tree->keysNum = 0;
    tree->parent = NULL;
    tree->left = NULL;
    tree->right = NULL;
    for (i = 0; i < 2 * T + 1; i++)
        tree->childs[i] = NULL;

    return tree;
}

int DestroyTree(tree_t* tree) {
    if (!tree)
        return NOT_FINISHED;

    int i = 0;
    if (tree->isLeaf == NOTLEAF) {
        for (int i = 0; i <= tree->keysNum; i++)
            DestroyTree(tree->childs[i]);
    }

    free(tree);
    return FINISHED;
}

tree_t* FindNodeByKey(tree_t* tree, int key) {
    if (!tree)
        return NOT_FOUND;

    int i = 0;
    tree_t* curNode = tree;
    while (curNode->isLeaf == NOTLEAF)
        for (i = 0; i <= curNode->keysNum; i++) {
            if (i == curNode->keysNum || key < curNode->keys[i]) {
                curNode = curNode->childs[i];
                break;
            }
        }

    return curNode;
}

int FindByKey(tree_t* tree, int key) {
    tree_t* node = FindNodeByKey(tree, key);
    if (node) {
        int i = 0;
        for (i = 0; i < node->keysNum; i++) {
            if (node->keys[i] == key)
                return FINISHED;
        }
    }

    return NOT_FINISHED;
}

void NodeSplit(tree_t** root, tree_t* node) {
    int i = 0, key = 0, position = 0;

    tree_t* newNode = CreateTree();
    newNode->isLeaf = NOTLEAF;


    if (node->right != NULL) {
        newNode->right = node->right;
        node->right->left = newNode;
        node->right = newNode;
        newNode->left = node;
    }
    else {
        newNode->right = node->right;
        node->right = newNode;
        newNode->left = node;
    }

    key = node->keys[T];
    newNode->keysNum = T - 1;
    node->keysNum = T;
    for (i = 0; i < newNode->keysNum; i++) {
        newNode->keys[i] = node->keys[i + T + 1];
        newNode->childs[i] = node->childs[i + T + 1];
        node->childs[i + T + 1] = NULL;
    }
    newNode->childs[newNode->keysNum] = node->childs[2 * T];
    node->childs[2 * T] = NULL;

    if (node->isLeaf == LEAF) {
        newNode->keysNum++;
        newNode->isLeaf = LEAF;
        for (i = newNode->keysNum - 1; i >= 1; i--)
            newNode->keys[i] = newNode->keys[i - 1];
        newNode->keys[0] = node->keys[T];
    }

    if (node == *(root)) {
        (*root) = (tree_t*)malloc(sizeof(tree_t));
        if (!(*root))
            return;

        (*root)->keys[0] = key;
        (*root)->childs[0] = node;
        (*root)->childs[1] = newNode;
        for (i = 0; i < 2 * T + 1; i++) {
            if (newNode->childs[i] != NULL)
                newNode->childs[i]->parent = newNode;
            if (node->childs[i] != NULL)
                node->childs[i]->parent = node;
        }
        (*root)->isLeaf = NOTLEAF;
        (*root)->parent = NULL;
        (*root)->left = NULL;
        (*root)->right = NULL;
        for (i = 2; i < 2 * T + 1; i++)
            (*root)->childs[i] = NULL;
        (*root)->keysNum = 1;
        node->parent = (*root);
        newNode->parent = (*root);
    }
    else {
        newNode->parent = node->parent;
        while (position < node->parent->keysNum && node->parent->keys[position] < key)
            position++;

        for (i = node->parent->keysNum; i >= position; i--)
            node->parent->keys[i] = node->parent->keys[i - 1];
        for (i = node->parent->keysNum + 1; i >= position + 2; i--)
            node->parent->childs[i] = node->parent->childs[i - 1];
        for (i = 0; i < 2 * T; i++)
            if (newNode->childs[i] != NULL)
                newNode->childs[i]->parent = newNode;
        node->parent->keys[position] = key;
        node->parent->childs[position + 1] = newNode;
        node->parent->keysNum++;

        if (node->parent->keysNum == 2 * T)
            NodeSplit(root, node->parent);
    }

    return;
}

int FindMin(tree_t* tree) {
    int i = 0;
    for (i = 0; i < 2 * T; i++)
        if (tree->childs[i])
            return FindMin(tree->childs[i]);

    return tree->keys[0];
}

void UpdateKeys(tree_t* node, int key) {
    tree_t* updated = node->parent;
    int i = 0;

    while (updated) {
        while (i < updated->keysNum && updated->keys[i] < key)
            i++;
        if (i < updated->keysNum)
            if (updated->keys[i] != FindMin(updated->childs[i + 1]))
                updated->keys[i] = FindMin(updated->childs[i + 1]);
        updated = updated->parent;
    }

    return;
}

void MergeNodes(tree_t* tree, tree_t* node, int key) {
    tree_t* parent = node->parent;
    tree_t* right = node->right;
    tree_t* left = node->left;
    tree_t* tmp = NULL;
    int i = 0;

    if (right != NULL && right->parent == node->parent) {
        for (i = 0; i < right->keysNum; i++) {
            node->keys[node->keysNum] = right->keys[i];
            node->childs[node->keysNum + 1] = right->childs[i];
            if (right->childs[i] != NULL)
                right->childs[i]->parent = node;
            node->keysNum++;
        }
        node->childs[node->keysNum + 1] = right->childs[right->keysNum];
        if (right->childs[right->keysNum])
            right->childs[right->keysNum]->parent = node;
        if (right->right)
            right->right->left = node;

        node->right = right->right;

        DeleteByKeyFromNode(tree, node->parent, FindMin(right));
        UpdateKeys(node, key);
    }
    else {
        for (i = 0; i < node->keysNum; i++) {
            left->keys[left->keysNum] = node->keys[i];
            left->childs[left->keysNum + 1] = node->childs[i];
            if (node->childs[i] != NULL)
                node->childs[i]->parent = left;
            left->keysNum++;
        }
        left->childs[left->keysNum + 1] = node->childs[node->keysNum];
        if (node->childs[node->keysNum])
            node->childs[node->keysNum]->parent = left;
        left->right = node->right;
        if (node->right != NULL)
            node->right->left = left;

        DeleteByKeyFromNode(tree, left->parent, FindMin(node));
        UpdateKeys(left, key);
    }
    return;
}

int InsertKey(tree_t** root, int key) {
    tree_t* leaf = FindNodeByKey((*root), key);
    if (!leaf)
        return NOT_FINISHED;

    int i = 0, position = 0;;
    for (i = 0; i < leaf->keysNum; i++) {
        if (leaf->keys[i] == key)
            return NOT_FINISHED;
    }

    while (position < leaf->keysNum && leaf->keys[position] < key)
        ++position;

    for (int i = leaf->keysNum; i >= position + 1; i--)
        leaf->keys[i] = leaf->keys[i - 1];

    leaf->keys[position] = key;
    leaf->keysNum++;
    if (leaf->keysNum == 2 * T)
        NodeSplit(root, leaf);

    return FINISHED;
}

void DeleteByKeyFromNode(tree_t* tree, tree_t* node, int key) {
    int i = 0, position = 0;
    while (position < node->keysNum && node->keys[position] < key)
        position++;
    for (int i = position; i < node->keysNum; i++)
        node->keys[i] = node->keys[i + 1];
    for (int i = position + 1; i <= node->keysNum; i++)
        node->childs[i] = node->childs[i + 1];
    for (int i = node->keysNum + 1; i < 2 * T + 1; i++)
        *(node->childs + i) = NULL;
    node->keysNum--;
    if (node == tree) {
        for (int i = 0; i < 2 * T + 1; i++)
            if (node->childs[i] != NULL)
                if (node->childs[i]->keysNum == 0)
                    node->childs[i] = NULL;
        if (tree->keysNum == 0 && tree->childs[0] != NULL)
            tree = tree->childs[0];
        return;
    }

    if (node->keysNum >= 1)
        UpdateKeys(node, key);
    else
        if (node->keysNum < T - 1) {
            tree_t* right = node->right;
            tree_t* left = node->left;
            if (left != NULL && left->keysNum > (T - 1) && left->parent == node->parent) {
                left->keysNum--;
                node->keysNum++;
                for (int i = 1; i < node->keysNum; i++) {
                    node->keys[i] = node->keys[i - 1];
                    node->childs[i] = node->childs[i - 1];
                }
                node->childs[node->keysNum] = node->childs[node->keysNum - 1];
                node->keys[0] = left->keys[left->keysNum];
                node->childs[0] = left->childs[left->keysNum + 1];
                left->childs[left->keysNum + 1] = NULL;
                if (node->childs[0] != NULL)
                    node->childs[0]->parent = node;
                UpdateKeys(node, key);
            }
            else
                if (right != NULL && right->keysNum > (T - 1) && right->parent == node->parent) {
                    node->keysNum++;
                    node->keys[node->keysNum - 1] = right->keys[0];
                    node->childs[node->keysNum] = right->childs[0];
                    if (node->childs[node->keysNum] != NULL)
                        node->childs[node->keysNum]->parent = node;
                    for (int i = 0; i < right->keysNum; i++) {
                        right->keys[i] = right->keys[i + 1];
                        right->childs[i] = right->childs[i + 1];
                    }
                    for (int i = 0; i < 2 * T; i++)
                        if (right->childs[i] == right->childs[i + 1] && right->childs[i] != NULL) {
                            right->childs[i + 1] = NULL;
                            break;
                        }
                    right->keysNum--;
                    UpdateKeys(node, key);
                }
                else
                    MergeNodes(tree, node, key);
        }
    return;
}

int DeleteByKey(tree_t* tree, int key) {
    if (!tree)
        return NOT_FINISHED;

    if (!FindByKey(tree, key))
        return NOT_FINISHED;

    tree_t* leaf = FindNodeByKey(tree, key);
    DeleteByKeyFromNode(tree, leaf, key);
    return FINISHED;
}

void PrintTree(tree_t* tree, int index, int child) {
    if (tree != NULL) {
        for (int i = 0; i < tree->keysNum; i++)
            printf("lvl %i child %i key %i\n", index, child, tree->keys[i]);
        for (int i = 0; i < 2 * T; i++) {
            if (tree->childs[i])
                PrintTree(tree->childs[i], index + 1, i);
        }
    }
    return;
}