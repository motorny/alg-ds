#include "2-3tree.h"

int isT(Tree* node) {

    return node != NULL && (node->left != NULL && node->left->left == NULL || node->right != NULL && node->right->left == NULL ||
        node->middle != NULL && node->middle->left == NULL) || node == NULL;
}
int isEmpty(Tree* node) {

    return node != NULL && node->left_value == node->max_child;
}
int Children2(Tree* node) {

    return node != NULL && node->left != NULL && node->middle == NULL && node->right != NULL;
}
int Children3(Tree* node) {

    return node != NULL && node->left != NULL && node->middle != NULL && node->right != NULL;
}
void Join(Tree* left, Tree* middle, Tree* right) {
    if (left != NULL) {
        left->right1 = middle;
    }
    middle->left1 = left;
    middle->right1 = right;
    if (right != NULL) {
        right->left1 = middle;
    }
}
void Divide(Tree* left, Tree* middle, Tree* right) {
    if (left != NULL) {
        left->right1 = right;
    }
    if (right != NULL) {
        right->left1 = left;
    }
}
Tree* newN(int value) {
    Tree* node = (Tree*)malloc(sizeof(Tree));
    if (node != NULL) {
        node->left = NULL;
        node->right = NULL;
        node->middle = NULL;
        node->left_value = value;
        node->right_value = EMP;
        node->left1 = NULL;
        node->right1 = NULL;
        node->max_child = value;
    }
    return node;
}
void freeN(Tree* node) {
    if (node != NULL) {
        node->left1 = NULL;
        node->right1 = NULL;
        node->left = NULL;
        node->middle = NULL;
        node->right = NULL;
        node->left_value = EMP;
        node->right_value = EMP;
        node->max_child = EMP;
        free(node);
    }
}
void freeTr(Tree* root) {
    if (root != NULL) {
        freeTr(root->left);
        freeTr(root->middle);
        freeTr(root->right);
        freeN(root);
    }
}
Tree* updateNode(Tree* root, Tree* left, Tree* middle, Tree* right) {
    if (root != NULL) {
        root->left = left;
        root->left_value = (root->left == NULL ? EMP : root->left->max_child);
        root->middle = middle;
        root->right_value = (root->middle == NULL ? EMP : root->middle->max_child);
        root->right = right;
        root->max_child = (root->right == NULL ? root->middle == NULL ? root->left->max_child : EMP : root->right->max_child);
    }
    return root;
}
Tree* splitNode(Tree* A, Tree* node, Tree* B, Tree* toFree, Tree* a, Tree* b, Tree* c, Tree* d) {
    A = updateNode(A == NULL ? newN(EMP) : A, a, NULL, b);
    B = updateNode(B == NULL ? newN(EMP) : B, c, NULL, d);
    node = updateNode(node == NULL ? newN(EMP) : node, A, NULL, B);
    freeN(toFree);
    return node;
}
Tree* mergeNode(Tree* root, Tree* left, Tree* middle, Tree* right, Tree* toFree) {
    if (Children2(left) && Children2(middle) && Children2(right)) {
        left = updateNode(left, left->left, left->right, middle->left);
        right = updateNode(right, middle->right, right->left, right->right);
        root = updateNode(root, left, NULL, right);
        freeN(middle);
    }
    else {
        root = updateNode(root, left, middle, right);
    }
    freeN(toFree);
    return root;
}
Tree* redistributeNode(Tree* root, Tree* a, Tree* b, Tree* c, Tree* d, Tree* toFree) {
    if (Children2(a) && Children2(b) && Children2(c) && root->right == d) {
        toFree = mergeNode(toFree, a, b, c, NULL);
        return mergeNode(root, toFree->left, toFree->right, d, toFree);
    }
    else if (Children2(b) && Children2(c) && Children2(d)) {
        toFree = mergeNode(toFree, b, c, d, NULL);
        return mergeNode(root, a, toFree->left, toFree->right, toFree);
    }
    else if (Children3(c) && Children2(d)) {
        a = mergeNode(a, a->left, a->right, b->left, NULL);
        b = mergeNode(b, b->right, c->left, c->middle, NULL);
        c = mergeNode(c, c->right, d->left, d->right, d);
        return mergeNode(root, a, b, c, toFree);
    }
    else if (Children3(b) && Children2(a)) {
        d = mergeNode(d, c->right, d->left, d->right, NULL);
        c = mergeNode(c, b->middle, b->right, c->left, NULL);
        b = mergeNode(b, a->left, a->right, b->left, a);
        return mergeNode(root, b, c, d, toFree);
    }
    return splitNode(root->left == a ? NULL : toFree, root->middle == b || root->middle == c ? NULL : toFree, root->right == d ? NULL : toFree, root, a, b, c, d);
}
Tree* Add(Tree* root, int value) {
    if (root == NULL) {
        Tree* node = newN(value), * leaf = newN(value);
        node->left = leaf;
        return node;
    }
    Tree* node = newN(value);
    if (value < root->left_value) {
        Join(root->left->left1, node, root->left);
        return isEmpty(root) ? updateNode(root, node, NULL, root->left) :
            Children2(root) ? mergeNode(root, node, root->left, root->right, NULL) : splitNode(NULL, NULL, NULL, root, node, root->left, root->middle, root->right);
    }
    else if (value > root->max_child) {
        if (isEmpty(root)) {
            Join(root->left, node, root->left->right1);
            return updateNode(root, root->left, NULL, node);
        }
        Join(root->right, node, root->right->right1);
        return Children2(root) ? mergeNode(root, root->left, root->right, node, NULL) : splitNode(NULL, NULL, NULL, root, root->left, root->middle, root->right, node);
    }
    else if (Children2(root) && value > root->left_value && value < root->max_child) {
        Join(root->left, node, root->right);
        return mergeNode(root, root->left, node, root->right, NULL);
    }
    else if (Children3(root)) {
        if (value < root->right_value && value > root->left_value) {
            Join(root->left, node, root->middle);
            return splitNode(NULL, NULL, NULL, root, root->left, node, root->middle, root->right);
        }
        else if (value < root->max_child && value > root->right_value) {
            Join(root->middle, node, root->right);
            return splitNode(NULL, NULL, NULL, root, root->left, root->middle, node, root->right);
        }
    }
    return root;
}
Tree* AddN(Tree* root, int value) {
    if (isT(root)) {
        return Add(root, value);
    }
    Tree* node;
    if (value < root->left_value) {
        node = AddN(root->left, value);
        if (node != root->left) {
            if (Children2(root)) {
                return mergeNode(root, node->left, node->right, root->right, node);
            }
            return redistributeNode(root, node->left, node->right, root->middle, root->right, node);
        }
    }
    else if (Children3(root) && value < root->right_value && value > root->left_value) {
        node = AddN(root->middle, value);
        if (node != root->middle) {
            return redistributeNode(root, root->left, node->left, node->right, root->right, node);
        }
    }
    else if (value > (Children2(root) ? root->left_value : root->right_value)) {
        node = AddN(root->right, value);
        if (root->right != node) {
            if (Children2(root)) {
                return mergeNode(root, root->left, node->left, node->right, node);
            }
            return redistributeNode(root, root->left, root->middle, node->left, node->right, node);
        }
    }
    return updateNode(root, root->left, root->middle, root->right);
}
Tree* deleteT(Tree* root, int value) {
    if (root == NULL || isEmpty(root) && root->left_value == value) {
        freeTr(root);
        return NULL;
    }
    if (value == root->left_value) {
        Divide(root->left->left1, root->left, root->left->right1);
        if (Children2(root)) {
            return mergeNode(root, root->right, NULL, NULL, root->left);
        }
        return mergeNode(root, root->middle, NULL, root->right, root->left);
    }
    else if (value == root->max_child) {
        Divide(root->right->left1, root->right, root->right->right1);
        return mergeNode(root, root->left, NULL, root->middle, root->right);
    }
    else if (Children3(root) && value == root->right_value) {
        Divide(root->middle->left1, root->middle, root->middle->right1);
        return mergeNode(root, root->left, NULL, root->right, root->middle);
    }
    return root;
}
Tree* stirNode(Tree* root, Tree* left, Tree* middle, Tree* right) {
    if (isEmpty(left)) {
        if (Children2(middle)) {
            left = mergeNode(left, left->left, middle->left, middle->right, middle);
            return updateNode(root, left, NULL, right);
        }
        middle = splitNode(left, NULL, middle, NULL, left->left, middle->left, middle->middle, middle->right);
        return mergeNode(root, middle->left, middle->right, right, middle);
    }
    else if (isEmpty(middle)) {
        if (Children2(left)) {
            middle = mergeNode(middle, left->left, left->right, middle->left, left);
            return updateNode(root, middle, NULL, right);
        }
        else if (Children2(right)) {
            middle = mergeNode(middle, middle->left, right->left, right->right, right);
            return updateNode(root, left, NULL, middle);
        }
        left = splitNode(left, NULL, middle, NULL, left->left, left->middle, left->right, middle->left);
        return mergeNode(root, left->left, left->right, right, left);
    }
    else if (isEmpty(right)) {
        if (Children2(middle)) {
            right = mergeNode(right, middle->left, middle->right, right->left, middle);
            return updateNode(root, left, NULL, right);
        }
        middle = splitNode(middle, NULL, right, NULL, middle->left, middle->middle, middle->right, right->left);
        return mergeNode(root, left, middle->left, middle->right, middle);
    }
    return updateNode(root, left, middle, right);
}
Tree* deleteN1(Tree* root, int value) {
    if (isT(root)) {
        return deleteT(root, value);
    }
    Tree* node = NULL;
    if (value <= root->left_value) {
        node = deleteN1(root->left, value);
        if (isEmpty(node)) {
            if (Children2(root)) {
                if (Children2(root->right)) {
                    node->left = mergeNode(root, node->left, root->right->left, root->right->right, root->right);
                    return node;
                }
                return splitNode(node, root, root->right, NULL, node->left, root->right->left, root->right->middle, root->right->right);
            }
            return stirNode(root, node, root->middle, root->right);
        }
    }
    else if (Children3(root) && value <= root->right_value && value > root->left_value) {
        node = deleteN1(root->middle, value);
        if (isEmpty(node)) {
            return stirNode(root, root->left, node, root->right);
        }
    }
    else if (value > Children3(root) ? root->right_value : root->left_value && value <= root->max_child) {
        node = deleteN1(root->right, value);
        if (isEmpty(node)) {
            if (Children2(root)) {
                if (Children2(root->left)) {
                    node->left = mergeNode(root, root->left->left, root->left->right, node->left, root->left);
                    return node;
                }
                return splitNode(root->left, root, node, NULL, root->left->left, root->left->middle, root->left->right, node->left);
            }
            return stirNode(root, root->left, root->middle, node);
        }
    }
    return mergeNode(root, root->left, root->middle, root->right, NULL);
}
Tree* deleteN(Tree* root, int value) {
    root = deleteN1(root, value);
    if (isEmpty(root) && !isT(root)) {
        Tree* node = root->left;
        freeN(root);
        return node;
    }
    return root;
}
Tree* Search(Tree* root, int value) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL && root->middle == NULL) {
            return value == root->left_value ? root : NULL;
        }
        else if (value <= root->left_value) {
            return Search(root->left, value);
        }
        else if (root->middle != NULL && value <= root->right_value && value > root->left_value) {
            return Search(root->middle, value);
        }
        return Search(root->right, value);
    }
    return NULL;
}
