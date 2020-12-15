#include "tree.h"

static int get_num_width(int key){
    int width = 0;
    if (key <= 0) {
        width++;
        key = -key;
    }
    while (key != 0)
    {
        key /= 10;
        width++;
    }
    return width;
}

static int get_node_width(node_t* t){
    if (t == NULL)
        return 0;
    if (!t->left && !t->right)
        return t->width = get_num_width(t->key);
    if (!t->left)
        return t->width = get_num_width(t->key) + get_node_width(t->right);
    if (!t->right)
        return t->width = get_num_width(t->key) + get_node_width(t->left);
    return t->width = get_num_width(t->key) + get_node_width(t->left) + get_node_width(t->right);
}

void push_node(node_t** t, int key){
    if (*t == NULL)
    {
        *t = (node_t*)malloc(sizeof(node_t));
        (*t)->key = key;
        (*t)->flag = FREE_FLAG;
        (*t)->parent = NULL;
        (*t)->width = get_num_width(key);
        (*t)->left = (*t)->right = NULL;
    }
    if (key > (*t)->key){
        PUSH_NODE(right);
    }
    if (key < (*t)->key){
        PUSH_NODE(left);
    }
}

void del_node(node_t** t, int key) {
    while ((*t)->key != key)
        if (key > (*t)->key) {
            if ((*t)->right == NULL)
                return;
            else
                (*t) = (*t)->right;
        }
        else if (key < (*t)->key) {
            if ((*t)->left == NULL)
                return;
            else
                (*t) = (*t)->left;
        }
    if ((*t)->parent == NULL) {
        if ((*t)->left == NULL && (*t)->right != NULL) {
            (*t) = (*t)->right;
            free((*t)->parent);
            (*t)->parent = NULL;
        }
        else if ((*t)->right == NULL && (*t)->left != NULL) {
            (*t) = (*t)->left;
            free((*t)->parent);
            (*t)->parent = NULL;
        }
        else if ((*t)->right == NULL && (*t)->left == NULL) {
            free(*t);
            (*t) = NULL;
        }
        else if ((*t)->right != NULL && (*t)->left == NULL) {
            node_t* for_free = NULL;
            (*t) = (*t)->left;
            while ((*t)->right != NULL)
                (*t) = (*t)->right;
            (*t)->right = for_free->right;
            (*t)->left = for_free->left;
            (*t)->parent = for_free->parent;
            (*t)->right->parent = (*t);
            (*t)->left->parent = (*t);
        }
    }
    else if ((*t)->right == NULL && (*t)->left == NULL) {
        (*t) = (*t)->parent;
        if ((*t)->right != NULL) {
            free((*t)->right);
            (*t)->right = NULL;

        }
        else if ((*t)->left != NULL)
            free((*t)->left);
        (*t)->left = NULL;
    }
    else if (((*t)->left == NULL) && ((*t)->right != NULL)) {
        (*t)->right->parent = (*t)->parent;
        (*t) = (*t)->right;
        if ((*t)->parent->left != NULL)
            if ((*t)->parent->left->key == key) {
                free((*t)->parent->left);
                (*t)->parent->left = (*t);
            }
        if ((*t)->parent->right != NULL)
            if ((*t)->parent->right->key == key) {
                free((*t)->parent->right);
                (*t)->parent->right = (*t);
            }
    }
    else if (((*t)->right == NULL) && ((*t)->left != NULL)) {
        (*t)->left->parent = (*t)->parent;
        (*t) = (*t)->left;
        if ((*t)->parent->left != NULL)
            if ((*t)->parent->left->key == key) {
                free((*t)->parent->right);
                (*t)->parent->right = (*t);
            }
        if ((*t)->parent->right != NULL)
            if ((*t)->parent->right->key == key) {
                free((*t)->parent->left);
                (*t)->parent->left = (*t);
            }
    }
    else if (((*t)->left != NULL) && ((*t)->right != NULL)) {
        node_t* for_free = NULL;
        (*t) = (*t)->left;
        if ((*t)->left == NULL && (*t)->right == NULL) {
            (*t) = (*t)->parent;
            (*t)->left->right = (*t)->right;
            (*t)->left->parent = (*t)->parent;
            (*t)->right->parent = (*t)->left;
            (*t) = (*t)->parent;
            if ((*t)->right->key == key) {
                (*t)->right = (*t)->right->left;
            }
            else if ((*t)->left->key == key)
                (*t)->left = (*t)->left->left;
        }
        else if ((*t)->left != NULL && (*t)->right == NULL) {
            (*t) = (*t)->parent;
            (*t)->left->right = (*t)->right;
            (*t)->left->parent = (*t)->parent;
            (*t)->right->parent = (*t)->left;
            (*t) = (*t)->parent;
            if ((*t)->right->key == key) {
                (*t)->right = (*t)->right->left;
            }
            else if ((*t)->left->key == key)
                (*t)->left = (*t)->left->left;
        }
        else if (((*t)->left == NULL && (*t)->right != NULL) || ((*t)->left != NULL && (*t)->right != NULL)) {
            (for_free) = (*t)->parent;
            while ((*t)->right != NULL)
                (*t) = (*t)->right;
            (*t)->right = for_free->right;
            (*t)->left = for_free->left;
            (*t)->parent = for_free->parent;
            (*t)->right->parent = (*t);
            (*t)->left->parent = (*t);
            if ((*t)->parent->right->key == key) {
                (*t)->parent->right = (*t)->right->left;
            }
            else if ((*t)->parent->left->key == key)
                (*t)->parent->left = (*t)->left->left;
        }
    }
    if ((*t) != NULL)
        while ((*t)->parent != NULL)
            (*t) = (*t)->parent;
}

node_t* find_elem(node_t* T, int key){
    node_t* t = T;
    while (GO_ON)
    {
        if (t == NULL)
            return NULL;
        if (key > t->key && t->right != NULL)
        {
            t = t->right;
            continue;
        }
        else if (key < t->key && t->left != NULL)
        {
            t = t->left;
            continue;
        }
        else if (key < t->key && t->left == NULL)
           return NULL;
        else if (key > t->key && t->right == NULL)
           return NULL;

        return t;
    }
}


int find_node(node_t* t, int key) {
    if (t == NULL)
        return 0;
    else if (t->key == key)
        return 1;
    else if (t->key > key) {
        if (find_node(t->left, key))
            return 1;
    }
    else if (t->key < key) {
        if (find_node(t->right, key))
            return 1;
    }

}

static void print_node(node_t* t, int is_width){
    int spaces;

    if (t == NULL)
        return;
    if (t->left != NULL)
        spaces = t->left->width + 1;
    else
        spaces = 0;

    for (int i = 0; i < spaces; i++)
        printf(" ");

    if (is_width)
    {
        printf("%i", t->width);
        spaces = +get_num_width(t->key) - get_num_width(t->width);
    }
    else
    {
        printf("%i", t->key);
        spaces = 0;
    }

    if (t->right)
        spaces += t->right->width;

    for (int i = 0; i < spaces; i++)
        printf(" ");
}

static int print_level(node_t* t, int level, int cur_level, int is_width, node_t* root){
    int offset = 0;
    int left_end = 0;
    int right_end = 0;
    int len = 0;

    if (!t)
        return 1;

    if (level == cur_level){
        print_node(t, is_width);
        return 0;
    }

    if (t->left){
        left_end = print_level(t->left, level, cur_level + 1, is_width, root);
        printf(" ");
    }
    else{
        left_end = 1;
    }

    len = get_num_width(t->key);
    for (int i = 0; i < len; i++)
        printf(" ");

    if (t->right){
        printf(" ");
        right_end = print_level(t->right, level, cur_level + 1, is_width, root);
    }
    else{
        right_end = 1;
    }

    return left_end & right_end;
}

void print_tree(node_t* t){
    int level = 0;
    int is_end = 0;
    node_t* cur = { 0 };

    if (!t)
        return;

    cur = t;

    get_node_width(t);

    while (!is_end)
    {
        is_end = print_level(t, level, 0, 0, t);
        printf("\n");
        print_level(t, level, 0, 1, t);
        printf("\n");
        level++;
    }

}

node_t* find_elem_k_lower(node_t* T, int k) {
    node_t* t = T;
    int unique_flag = k * T->key;
    int counter = 0;
    int new_key = T->key - k;
    t->flag = unique_flag;
    while (new_key != t->key) {
        if (new_key <= t->key && t->left != NULL && t->left->flag != unique_flag) {
            t = t->left;
            t->flag = unique_flag;
        }
        else if (new_key >= t->key && t->right != NULL && t->right->flag != unique_flag) {
            t = t->right;
            t->flag = unique_flag;
        }
        else if (((t->right == NULL && t->left == NULL) || (t->flag = unique_flag)) && t->parent != NULL) {
            t = t->parent;
            t->flag = unique_flag;
        }
    }
    return t;
}

int main() {
    return 0;
}