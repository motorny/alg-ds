#include "2-3.h"

tree_t* Update(tree_t* tree, tree_t* left, tree_t* mid, tree_t* right) {

    if (tree) {
        tree->left = left;
        tree->left_val = (tree->left == NULL ? -1 : tree->left->max_son);
        tree->mid = mid;
        tree->right_val = (tree->mid == NULL ? -1 : tree->mid->max_son);
        tree->right = right;
        tree->max_son = (tree->right == NULL ? tree->mid == NULL ? tree->left->max_son : -1 : tree->right->max_son);
    }
    else
        return tree;
}

tree_t* Split(tree_t* A, tree_t* node, tree_t* B, tree_t* del, tree_t* a, tree_t* b, tree_t* c, tree_t* d) {

    A = Update(A == NULL ? AddVal(-1) : A, a, NULL, b);
    B = Update(B == NULL ? AddVal(-1) : B, c, NULL, d);
    node = Update(node == NULL ? AddVal(-1) : node, A, NULL, B);
    DeleteNode(del);
    return node;
}

int IsTwoSons(tree_t* node) {

    return node != NULL && node->left != NULL && node->mid == NULL && node->right != NULL;
}

tree_t* Merge(tree_t* tree, tree_t* left, tree_t* mid, tree_t* right, tree_t* del) {

    if (IsTwoSons(left) && IsTwoSons(mid) && IsTwoSons(right)) {
        left = Update(left, left->left, left->right, mid->left);
        right = Update(right, mid->right, right->left, right->right);
        tree = Update(tree, left, NULL, right);
        DeleteNode(mid);
    }
    else
        tree = Update(tree, left, mid, right);
    DeleteNode(del);
    return tree;
}

int IsTreeSons(tree_t* node) {

    return node != NULL && node->left != NULL && node->mid != NULL && node->right != NULL;
}

tree_t* Balance(tree_t* tree, tree_t* a, tree_t* b, tree_t* c, tree_t* d, tree_t* toFree) {

    if (IsTwoSons(a) && IsTwoSons(b) && IsTwoSons(c) && tree->right == d) {
        toFree = Merge(toFree, a, b, c, NULL);
        return Merge(tree, toFree->left, toFree->right, d, toFree);
    }
    else if (IsTwoSons(b) && IsTwoSons(c) && IsTwoSons(d)) {
        toFree = Merge(toFree, b, c, d, NULL);
        return Merge(tree, a, toFree->left, toFree->right, toFree);
    }
    else if (IsTreeSons(c) && IsTwoSons(d)) {
        a = Merge(a, a->left, a->right, b->left, NULL);
        b = Merge(b, b->right, c->left, c->mid, NULL);
        c = Merge(c, c->right, d->left, d->right, d);
        return Merge(tree, a, b, c, toFree);
    }
    else if (IsTreeSons(b) && IsTwoSons(a)) {
        d = Merge(d, c->right, d->left, d->right, NULL);
        c = Merge(c, b->mid, b->right, c->left, NULL);
        b = Merge(b, a->left, a->right, b->left, a);
        return Merge(tree, b, c, d, toFree);
    }
    return Split(tree->left == a ? NULL : toFree, tree->mid == b || tree->mid == c ? NULL : toFree, tree->right == d ? NULL : toFree, tree, a, b, c, d);
}

tree_t* AddVal(int val) {

    tree_t* node = (tree_t*)malloc(sizeof(tree_t));
    if (node) {
        node->left = NULL;
        node->left_val = val;
        node->right = NULL;
        node->right_val = -1;
        node->mid = NULL;
        node->max_son = val;
        node->left1 = NULL;
        node->right1 = NULL;
    }
    return node;
}

int Check1(tree_t* node) {

    return node != NULL && node->left_val == node->max_son;
}

void Unite(tree_t* left, tree_t* mid, tree_t* right) {

    if (left)
        left->right1 = mid;
    mid->left1 = left;
    mid->right1 = right;
    if (right)
        right->left1 = mid;
}

tree_t* Insert(tree_t* tree, int val) {

    if (!tree) {
        tree_t* node = AddVal(val);
        tree_t* tmp = AddVal(val);
        node->left = tmp;
        return node;
    }
    tree_t* node = AddVal(val);
    if (val < tree->left_val) {
        Unite(tree->left->left1, node, tree->left);
        return Check1(tree) ? Update(tree, node, NULL, tree->left) :
            IsTwoSons(tree) ? Merge(tree, node, tree->left, tree->right, NULL) : Split(NULL, NULL, NULL, tree, node, tree->left, tree->mid, tree->right);
    }
    else if (val > tree->max_son) {
        if (Check1(tree)) {
            Unite(tree->left, node, tree->left->right1);
            return Update(tree, tree->left, NULL, node);
        }
        Unite(tree->right, node, tree->right->right1);
        return IsTwoSons(tree) ? Merge(tree, tree->left, tree->right, node, NULL) : Split(NULL, NULL, NULL, tree, tree->left, tree->mid, tree->right, node);
    }
    else if (IsTwoSons(tree) && val > tree->left_val && val < tree->max_son) {
        Unite(tree->left, node, tree->right);
        return Merge(tree, tree->left, node, tree->right, NULL);
    }
    else if (IsTreeSons(tree)) {
        if (val < tree->right_val && val > tree->left_val) {
            Unite(tree->left, node, tree->mid);
            return Split(NULL, NULL, NULL, tree, tree->left, node, tree->mid, tree->right);
        }
        else if (val < tree->max_son && val > tree->right_val) {
            Unite(tree->mid, node, tree->right);
            return Split(NULL, NULL, NULL, tree, tree->left, tree->mid, node, tree->right);
        }
    }
    return tree;
}

int Check2(tree_t* node) {

    return node != NULL && (node->left != NULL && node->left->left == NULL || node->right != NULL && node->right->left == NULL ||
        node->mid != NULL && node->mid->left == NULL) || node == NULL;
}

tree_t* InsertNode(tree_t* tree, int val) {

    tree_t* node = NULL;
    if (Check2(tree))
        return Insert(tree, val);
    if (val < tree->left_val) {
        node = InsertNode(tree->left, val);
        if (node != tree->left) {
            if (IsTwoSons(tree))
                return Merge(tree, node->left, node->right, tree->right, node);
            return Balance(tree, node->left, node->right, tree->mid, tree->right, node);
        }
    }
    else if (IsTreeSons(tree) && val < tree->right_val && val > tree->left_val) {
        node = InsertNode(tree->mid, val);
        if (node != tree->mid)
            return Balance(tree, tree->left, node->left, node->right, tree->right, node);
    }
    else if (val > (IsTwoSons(tree) ? tree->left_val : tree->right_val)) {
        node = InsertNode(tree->right, val);
        if (tree->right != node) {
            if (IsTwoSons(tree))
                return Merge(tree, tree->left, node->left, node->right, node);
            return Balance(tree, tree->left, tree->mid, node->left, node->right, node);
        }
    }
    return Update(tree, tree->left, tree->mid, tree->right);
}

void Separate(tree_t* left, tree_t* mid, tree_t* right) {

    if (left)
        left->right1 = right;
    if (right)
        right->left1 = left;
}

tree_t* Delete1(tree_t* tree, int val) {

    if (!tree || Check1(tree) && tree->left_val == val) {
        DestroyTree(tree);
        return NULL;
    }
    if (val == tree->left_val) {
        Separate(tree->left->left1, tree->left, tree->left->right1);
        if (IsTwoSons(tree))
            return Merge(tree, tree->right, NULL, NULL, tree->left);
        return Merge(tree, tree->mid, NULL, tree->right, tree->left);
    }
    else if (val == tree->max_son) {
        Separate(tree->right->left1, tree->right, tree->right->right1);
        return Merge(tree, tree->left, NULL, tree->mid, tree->right);
    }
    else if (IsTreeSons(tree) && val == tree->right_val) {
        Separate(tree->mid->left1, tree->mid, tree->mid->right1);
        return Merge(tree, tree->left, NULL, tree->right, tree->mid);
    }
    return tree;
}

tree_t* Delete2(tree_t* tree, tree_t* left, tree_t* mid, tree_t* right) {

    if (Check1(left)) {
        if (IsTwoSons(mid)) {
            left = Merge(left, left->left, mid->left, mid->right, mid);
            return Update(tree, left, NULL, right);
        }
        mid = Split(left, NULL, mid, NULL, left->left, mid->left, mid->mid, mid->right);
        return Merge(tree, mid->left, mid->right, right, mid);
    }
    else if (Check1(mid)) {
        if (IsTwoSons(left)) {
            mid = Merge(mid, left->left, left->right, mid->left, left);
            return Update(tree, mid, NULL, right);
        }
        else if (IsTwoSons(right)) {
            mid = Merge(mid, mid->left, right->left, right->right, right);
            return Update(tree, left, NULL, mid);
        }
        left = Split(left, NULL, mid, NULL, left->left, left->mid, left->right, mid->left);
        return Merge(tree, left->left, left->right, right, left);
    }
    else if (Check1(right)) {
        if (IsTwoSons(mid)) {
            right = Merge(right, mid->left, mid->right, right->left, mid);
            return Update(tree, left, NULL, right);
        }
        mid = Split(mid, NULL, right, NULL, mid->left, mid->mid, mid->right, right->left);
        return Merge(tree, left, mid->left, mid->right, mid);
    }
    return Update(tree, left, mid, right);
}

tree_t* Delete(tree_t* tree, int val) {

    tree_t* node = NULL;
    if (Check2(tree))
        return Delete1(tree, val);
    if (val <= tree->left_val) {
        node = Delete(tree->left, val);
        if (Check1(node)) {
            if (IsTwoSons(tree)) {
                if (IsTwoSons(tree->right)) {
                    node->left = Merge(tree, node->left, tree->right->left, tree->right->right, tree->right);
                    return node;
                }
                return Split(node, tree, tree->right, NULL, node->left, tree->right->left, tree->right->mid, tree->right->right);
            }
            return Delete2(tree, node, tree->mid, tree->right);
        }
    }
    else if (IsTreeSons(tree) && val <= tree->right_val && val > tree->left_val) {
        node = Delete(tree->mid, val);
        if (Check1(node))
            return Delete2(tree, tree->left, node, tree->right);
    }
    else if (val > IsTreeSons(tree) ? tree->right_val : tree->left_val && val <= tree->max_son) {
        node = Delete(tree->right, val);
        if (Check1(node)) {
            if (IsTwoSons(tree)) {
                if (IsTwoSons(tree->left)) {
                    node->left = Merge(tree, tree->left->left, tree->left->right, node->left, tree->left);
                    return node;
                }
                return Split(tree->left, tree, node, NULL, tree->left->left, tree->left->mid, tree->left->right, node->left);
            }
            return Delete2(tree, tree->left, tree->mid, node);
        }
    }
    return Merge(tree, tree->left, tree->mid, tree->right, NULL);
}

tree_t* DeleteVal(tree_t* tree, int val) {

    tree = Delete(tree, val);
    if (Check1(tree) && !Check2(tree)) {
        tree_t* node = tree->left;
        DeleteNode(tree);
        return node;
    }
    else
        return tree;
}

tree_t* FindVal(tree_t* tree, int val) {

    if (tree) {
        if (tree->left == NULL && tree->right == NULL && tree->mid == NULL)
            return val == tree->left_val ? tree : NULL;
        else if (val <= tree->left_val)
            return FindVal(tree->left, val);
        else if (tree->mid != NULL && val <= tree->right_val && val > tree->left_val)
            return FindVal(tree->mid, val);
        return FindVal(tree->right, val);
    }
    else
        return NULL;
}

void PrintTree(tree_t* tree) {

    if (tree) {
        while (!Check2(tree))
            tree = tree->left;
        if (tree) {
            tree = tree->left;
            while (tree) {
                printf("%d ", tree->left_val);
                tree = tree->right1;
            }
        }
    }
}

void DeleteNode(tree_t* node) {

    if (node) {
        node->left = NULL;
        node->left_val = -1;
        node->right = NULL;
        node->right_val = -1;
        node->mid = NULL;
        node->max_son = -1;
        node->left1 = NULL;
        node->right1 = NULL;
        free(node);
    }
}

void DestroyTree(tree_t* tree) {

    if (tree) {
        DestroyTree(tree->left);
        DestroyTree(tree->mid);
        DestroyTree(tree->right);
        DeleteNode(tree);
    }
}

char* ReadStr(void) {
    int i = 0, size = 2;
    int block = 8;
    char* str = (char*)malloc(sizeof(char) * size), * tmp = NULL;
    if (str == NULL)
        return NULL;
    while ((str[i++] = fgetc(stdin)) != EOF) {
        if (i >= size) {
            size += block;
            tmp = realloc(str, (size) * sizeof(char));
            if (tmp)
                str = tmp;
            else
                return NULL;
        }
    }
    str[i - 1] = 0;
    return str;
}