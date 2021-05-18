#pragma warning (disable:4996)
#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct tree2_3_t {
    int leftValue;
    int rightValue;
    int maxSon;
    struct tree2_3_t* left;
    struct tree2_3_t* middle;
    struct tree2_3_t* right;
    struct tree2_3_t* left1;
    struct tree2_3_t* right1;
} tree2_3_t;

void Union(tree2_3_t* left, tree2_3_t* middle, tree2_3_t* right) {

    if (left != NULL)
        left->right1 = middle;
    middle->left1 = left;
    middle->right1 = right;
    if (right != NULL)
        right->left1 = middle;
}

void Separate(tree2_3_t* left, tree2_3_t* middle, tree2_3_t* right) {
    if (left != NULL)
        left->right1 = right;
    if (right != NULL)
        right->left1 = left;
}

tree2_3_t* AddNode(int val) {

    tree2_3_t* node = (tree2_3_t*)malloc(sizeof(tree2_3_t));
    if (node != NULL) {
        node->left = NULL;
        node->right = NULL;
        node->middle = NULL;
        node->leftValue = val;
        node->rightValue = -1;
        node->left1 = NULL;
        node->right1 = NULL;
        node->maxSon = val;
    }
    return node;
}

void Delete_Node(tree2_3_t* node) {

    if (node != NULL) {
        node->left1 = NULL;
        node->right1 = NULL;
        node->left = NULL;
        node->middle = NULL;
        node->right = NULL;
        node->leftValue = -1;
        node->rightValue = -1;
        node->maxSon = -1;
        free(node);
    }
}

void Destroy_Tree(tree2_3_t* tree) {

    if (tree != NULL) {
        Destroy_Tree(tree->left);
        Destroy_Tree(tree->middle);
        Destroy_Tree(tree->right);
        Delete_Node(tree);
    }
}

tree2_3_t* Update(tree2_3_t* tree, tree2_3_t* left, tree2_3_t* middle, tree2_3_t* right) {

    if (tree != NULL) {
        tree->left = left;
        tree->leftValue = (tree->left == NULL ? -1 : tree->left->maxSon);
        tree->middle = middle;
        tree->rightValue = (tree->middle == NULL ? -1 : tree->middle->maxSon);
        tree->right = right;
        tree->maxSon = (tree->right == NULL ? tree->middle == NULL ? tree->left->maxSon : -1 : tree->right->maxSon);
    }
    return tree;
}

tree2_3_t* Split(tree2_3_t* A, tree2_3_t* node, tree2_3_t* B, tree2_3_t* del, tree2_3_t* a, tree2_3_t* b, tree2_3_t* c, tree2_3_t* d) {

    A = Update(A == NULL ? AddNode(-1) : A, a, NULL, b);
    B = Update(B == NULL ? AddNode(-1) : B, c, NULL, d);
    node = Update(node == NULL ? AddNode(-1) : node, A, NULL, B);
    Delete_Node(del);
    return node;
}

int Is2Sons(tree2_3_t* node) {

    return node != NULL && node->left != NULL && node->middle == NULL && node->right != NULL;
}

tree2_3_t* Merge(tree2_3_t* tree, tree2_3_t* left, tree2_3_t* middle, tree2_3_t* right, tree2_3_t* del) {

    if (Is2Sons(left) && Is2Sons(middle) && Is2Sons(right)) {
        left = Update(left, left->left, left->right, middle->left);
        right = Update(right, middle->right, right->left, right->right);
        tree = Update(tree, left, NULL, right);
        Delete_Node(middle);
    }
    else
        tree = Update(tree, left, middle, right);
    Delete_Node(del);
    return tree;
}

int Is3Sons(tree2_3_t* node) {

    return node != NULL && node->left != NULL && node->middle != NULL && node->right != NULL;
}

tree2_3_t* Balance(tree2_3_t* tree, tree2_3_t* a, tree2_3_t* b, tree2_3_t* c, tree2_3_t* d, tree2_3_t* toFree) {

    if (Is2Sons(a) && Is2Sons(b) && Is2Sons(c) && tree->right == d) {
        toFree = Merge(toFree, a, b, c, NULL);
        return Merge(tree, toFree->left, toFree->right, d, toFree);
    }
    else if (Is2Sons(b) && Is2Sons(c) && Is2Sons(d)) {
        toFree = Merge(toFree, b, c, d, NULL);
        return Merge(tree, a, toFree->left, toFree->right, toFree);
    }
    else if (Is3Sons(c) && Is2Sons(d)) {
        a = Merge(a, a->left, a->right, b->left, NULL);
        b = Merge(b, b->right, c->left, c->middle, NULL);
        c = Merge(c, c->right, d->left, d->right, d);
        return Merge(tree, a, b, c, toFree);
    }
    else if (Is3Sons(b) && Is2Sons(a)) {
        d = Merge(d, c->right, d->left, d->right, NULL);
        c = Merge(c, b->middle, b->right, c->left, NULL);
        b = Merge(b, a->left, a->right, b->left, a);
        return Merge(tree, b, c, d, toFree);
    }
    return Split(tree->left == a ? NULL : toFree, tree->middle == b || tree->middle == c ? NULL : toFree, tree->right == d ? NULL : toFree, tree, a, b, c, d);
}

int Check2(tree2_3_t* node) {

    return node != NULL && node->leftValue == node->maxSon;
}

tree2_3_t* Insert(tree2_3_t* tree, int val) {

    if (tree == NULL) {
        tree2_3_t* node = AddNode(val);
        tree2_3_t* tmp = AddNode(val);
        node->left = tmp;
        return node;
    }
    tree2_3_t* node = AddNode(val);
    if (val < tree->leftValue) {
        Union(tree->left->left1, node, tree->left);
        return Check2(tree) ? Update(tree, node, NULL, tree->left) :
            Is2Sons(tree) ? Merge(tree, node, tree->left, tree->right, NULL) : Split(NULL, NULL, NULL, tree, node, tree->left, tree->middle, tree->right);
    }
    else if (val > tree->maxSon) {
        if (Check2(tree)) {
            Union(tree->left, node, tree->left->right1);
            return Update(tree, tree->left, NULL, node);
        }
        Union(tree->right, node, tree->right->right1);
        return Is2Sons(tree) ? Merge(tree, tree->left, tree->right, node, NULL) : Split(NULL, NULL, NULL, tree, tree->left, tree->middle, tree->right, node);
    }
    else if (Is2Sons(tree) && val > tree->leftValue && val < tree->maxSon) {
        Union(tree->left, node, tree->right);
        return Merge(tree, tree->left, node, tree->right, NULL);
    }
    else if (Is3Sons(tree)) {
        if (val < tree->rightValue && val > tree->leftValue) {
            Union(tree->left, node, tree->middle);
            return Split(NULL, NULL, NULL, tree, tree->left, node, tree->middle, tree->right);
        }
        else if (val < tree->maxSon && val > tree->rightValue) {
            Union(tree->middle, node, tree->right);
            return Split(NULL, NULL, NULL, tree, tree->left, tree->middle, node, tree->right);
        }
    }
    return tree;
}

int Check1(tree2_3_t* node) {

    return node != NULL && (node->left != NULL && node->left->left == NULL || node->right != NULL && node->right->left == NULL ||
        node->middle != NULL && node->middle->left == NULL) || node == NULL;
}

tree2_3_t* Insert_Node(tree2_3_t* tree, int val) {

    if (Check1(tree))
        return Insert(tree, val);
    tree2_3_t* node;
    if (val < tree->leftValue) {
        node = Insert_Node(tree->left, val);
        if (node != tree->left) {
            if (Is2Sons(tree))
                return Merge(tree, node->left, node->right, tree->right, node);
            return Balance(tree, node->left, node->right, tree->middle, tree->right, node);
        }
    }
    else if (Is3Sons(tree) && val < tree->rightValue && val > tree->leftValue) {
        node = Insert_Node(tree->middle, val);
        if (node != tree->middle)
            return Balance(tree, tree->left, node->left, node->right, tree->right, node);
    }
    else if (val > (Is2Sons(tree) ? tree->leftValue : tree->rightValue)) {
        node = Insert_Node(tree->right, val);
        if (tree->right != node) {
            if (Is2Sons(tree))
                return Merge(tree, tree->left, node->left, node->right, node);
            return Balance(tree, tree->left, tree->middle, node->left, node->right, node);
        }
    }
    return Update(tree, tree->left, tree->middle, tree->right);
}

tree2_3_t* Delete1(tree2_3_t* tree, int val) {

    if (tree == NULL || Check2(tree) && tree->leftValue == val) {
        Destroy_Tree(tree);
        return NULL;
    }
    if (val == tree->leftValue) {
        Separate(tree->left->left1, tree->left, tree->left->right1);
        if (Is2Sons(tree))
            return Merge(tree, tree->right, NULL, NULL, tree->left);
        return Merge(tree, tree->middle, NULL, tree->right, tree->left);
    }
    else if (val == tree->maxSon) {
        Separate(tree->right->left1, tree->right, tree->right->right1);
        return Merge(tree, tree->left, NULL, tree->middle, tree->right);
    }
    else if (Is3Sons(tree) && val == tree->rightValue) {
        Separate(tree->middle->left1, tree->middle, tree->middle->right1);
        return Merge(tree, tree->left, NULL, tree->right, tree->middle);
    }
    return tree;
}

tree2_3_t* Delete2(tree2_3_t* tree, tree2_3_t* left, tree2_3_t* middle, tree2_3_t* right) {

    if (Check2(left)) {
        if (Is2Sons(middle)) {
            left = Merge(left, left->left, middle->left, middle->right, middle);
            return Update(tree, left, NULL, right);
        }
        middle = Split(left, NULL, middle, NULL, left->left, middle->left, middle->middle, middle->right);
        return Merge(tree, middle->left, middle->right, right, middle);
    }
    else if (Check2(middle)) {
        if (Is2Sons(left)) {
            middle = Merge(middle, left->left, left->right, middle->left, left);
            return Update(tree, middle, NULL, right);
        }
        else if (Is2Sons(right)) {
            middle = Merge(middle, middle->left, right->left, right->right, right);
            return Update(tree, left, NULL, middle);
        }
        left = Split(left, NULL, middle, NULL, left->left, left->middle, left->right, middle->left);
        return Merge(tree, left->left, left->right, right, left);
    }
    else if (Check2(right)) {
        if (Is2Sons(middle)) {
            right = Merge(right, middle->left, middle->right, right->left, middle);
            return Update(tree, left, NULL, right);
        }
        middle = Split(middle, NULL, right, NULL, middle->left, middle->middle, middle->right, right->left);
        return Merge(tree, left, middle->left, middle->right, middle);
    }
    return Update(tree, left, middle, right);
}

tree2_3_t* Delete(tree2_3_t* tree, int val) {

    if (Check1(tree))
        return Delete1(tree, val);
    tree2_3_t* node = NULL;
    if (val <= tree->leftValue) {
        node = Delete(tree->left, val);
        if (Check2(node)) {
            if (Is2Sons(tree)) {
                if (Is2Sons(tree->right)) {
                    node->left = Merge(tree, node->left, tree->right->left, tree->right->right, tree->right);
                    return node;
                }
                return Split(node, tree, tree->right, NULL, node->left, tree->right->left, tree->right->middle, tree->right->right);
            }
            return Delete2(tree, node, tree->middle, tree->right);
        }
    }
    else if (Is3Sons(tree) && val <= tree->rightValue && val > tree->leftValue) {
        node = Delete(tree->middle, val);
        if (Check2(node))
            return Delete2(tree, tree->left, node, tree->right);
    }
    else if (val > Is3Sons(tree) ? tree->rightValue : tree->leftValue && val <= tree->maxSon) {
        node = Delete(tree->right, val);
        if (Check2(node)) {
            if (Is2Sons(tree)) {
                if (Is2Sons(tree->left)) {
                    node->left = Merge(tree, tree->left->left, tree->left->right, node->left, tree->left);
                    return node;
                }
                return Split(tree->left, tree, node, NULL, tree->left->left, tree->left->middle, tree->left->right, node->left);
            }
            return Delete2(tree, tree->left, tree->middle, node);
        }
    }
    return Merge(tree, tree->left, tree->middle, tree->right, NULL);
}

tree2_3_t* Delete_Val(tree2_3_t* tree, int val) {

    tree = Delete(tree, val);
    if (Check2(tree) && !Check1(tree)) {
        tree2_3_t* node = tree->left;
        Delete_Node(tree);
        return node;
    }
    return tree;
}

tree2_3_t* Find_Val(tree2_3_t* tree, int val) {

    if (tree != NULL) {
        if (tree->left == NULL && tree->right == NULL && tree->middle == NULL)
            return val == tree->leftValue ? tree : NULL;
        else if (val <= tree->leftValue)
            return Find_Val(tree->left, val);
        else if (tree->middle != NULL && val <= tree->rightValue && val > tree->leftValue)
            return Find_Val(tree->middle, val);
        return Find_Val(tree->right, val);
    }
    return NULL;
}

void Print_Tree(tree2_3_t* tree) {

    if (tree == NULL)
        return;
    while (!Check1(tree))
        tree = tree->left;
    if (tree != NULL) {
        tree = tree->left;
        do {
            printf("%d ", tree->leftValue);
        } while ((tree = tree->right1) != NULL);
    }
}



int main(void) {
    tree2_3_t* tree = NULL;
    int command, key;

    command = getchar();
    while (command != EOF) {
        scanf("%d", &key);
        switch (command) {
        case 'a':
            tree = Insert_Node(tree, key);
            break;
        case 'f':
            if (Find_Val(tree, key))
                printf("yes\n");
            else
                printf("no\n");
            break;
        case 'r':
            tree = Delete_Val(tree, key);
            break;
        default:
            Destroy_Tree(tree);
            return 0;
        }
        command = getchar();
        if (command == '\n')
            command = getchar();
    }
    Destroy_Tree(tree);

 

    return 0;


}