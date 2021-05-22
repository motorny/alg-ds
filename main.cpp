#include <stdio.h>


////////////////////////////
// RB-Tree.h
#include <stdlib.h>

typedef enum {
    BLACK,
    RED
} color_t;

typedef struct node_t_ {
    int key;
    color_t color;
    struct node_t_* parent;
    struct node_t_* left;
    struct node_t_* right;
}node_t;

static node_t leaf = { 0, BLACK, NULL, &leaf, &leaf };

typedef struct tree_t {
    node_t* root;
}tree_t;

node_t* InsertNode(tree_t* tree, int key);
void FixUpInsertion(tree_t* tree, node_t* node);
void RemoveNode(tree_t* tree, int key);
void FixUpRemoving(tree_t* tree, node_t* node);
node_t* FindNode(tree_t* tree, int key);

void LeftRotate(tree_t* tree, node_t* x);
void RightRotate(tree_t* tree, node_t* x);

////////////////////////////
// RB-Tree.cpp

void LeftRotate(tree_t* tree, node_t* x) {
    node_t* y = x->right;
    x->right = y->left;

    if (y->left != &leaf)
        y->left->parent = x;

    if (y != &leaf)
        y->parent = x->parent;

    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    else {
        tree->root = y;
    }

    y->left = x;

    if (x != &leaf)
        x->parent = y;
}

void RightRotate(tree_t* tree, node_t* x) {
    node_t* y = x->left;
    x->left = y->right;

    if (y->right != &leaf)
        y->right->parent = x;

    if (y != &leaf)
        y->parent = x->parent;

    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    else {
        tree->root = y;
    }

    y->right = x;

    if (x != &leaf)
        x->parent = y;
}


node_t* InsertNode(tree_t* tree, int key) {
    node_t* current;
    node_t* parent;
    node_t* x;

    current = tree->root;
    parent = NULL;

    while (current != &leaf) {
        if (key == current->key)
            return current;
        parent = current;

        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    x = (node_t*)malloc(sizeof(node_t));
    if (x == NULL) {
        return NULL;
    }

    x->key = key;
    x->parent = parent;
    x->left = &leaf;
    x->right = &leaf;
    x->color = RED;

    if (parent) {
        if (key < parent->key)
            parent->left = x;
        else
            parent->right = x;
    }
    else {
        tree->root = x;
    }

    FixUpInsertion(tree,x);
    return x;
}

void FixUpInsertion(tree_t* tree, node_t* x) {
    while (x != tree->root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            node_t* y = x->parent->parent->right;
            
            if (y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->right) {
                    x = x->parent;
                    LeftRotate(tree,x);
                }
                
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                RightRotate(tree,x->parent->parent);
            }
        }
        else {
            node_t* y = x->parent->parent->left;
            if (y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->left) {
                    x = x->parent;
                    RightRotate(tree,x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                LeftRotate(tree, x->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

node_t* FindNode(tree_t* tree, int key) {
    node_t* x = tree->root;
    while (x != &leaf) {
        if (x->key == key)
            return x;
        else {
            if (x->key < key)
                x = x->right;
            else
                x = x->left;
        }
    }
    return NULL;
}

void RemoveNode(tree_t* tree, int key) {
    node_t* x;
    node_t* y;
    node_t* z;

    z = FindNode(tree, key);
    if (z == NULL) return;

    if (z->left == &leaf || z->right == &leaf) {
        y = z;
    }
    else {
        y = z->right;
        while (y->left != &leaf) {
            y = y->left;
        }
    }

    if (y->left != &leaf)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if (y->parent!=NULL) {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    else {
        tree->root = x;
    }

    if (y != z)
        z->key = y->key;
    if (y->color == BLACK)
        FixUpRemoving(tree, x);
    
    free(y);
}

void FixUpRemoving(tree_t* tree, node_t* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            node_t* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(tree, x->parent);
                x = tree->root;
            }
        }
        else {
            node_t* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}
////////////////////////////
#pragma warning(disable:4996) 
int main(void) {
    tree_t tree;
    int key;

    tree.root = &leaf;

    char c = getchar();
    while (c != EOF) {
        scanf("%d", &key);
        if (c == 'a') {
            InsertNode(&tree, key);
        }
        else if (c == 'r') {
            RemoveNode(&tree, key);
        }
        else if (c == 'f') {
            if (FindNode(&tree,key) != NULL)
                printf("yes\n");
            else
                printf("no\n");
        }
        else {
            continue;
        }
        c = getchar();
        if (c == '\r')
            c = getchar();
        else if (c == '\n')
            c = getchar();
    }
    return 0;
}