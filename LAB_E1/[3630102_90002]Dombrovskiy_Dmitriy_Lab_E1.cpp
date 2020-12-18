#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct LIST {
    int data;
    struct LIST* left;
    struct LIST* right;
    struct LIST* parent;
} LIST;

LIST* list;


LIST* add_block(LIST* parent, int data)
{
    LIST* NEW = (LIST*)malloc(sizeof(LIST));
    if(NEW == NULL)
    {
        return NULL;
    }
    NEW->left = NEW->right = NULL;
    NEW->data = data;
    NEW->parent = parent;
    return NEW;
}


void insert_in_tree(int data)
{
    if (list == NULL)
    {
        list = add_block(NULL, data);
        return;
    }
    LIST* current;
    current = list;
    while (current != NULL)
    {
        if (current->data > data)
        {
            if (current->left != NULL)
            {
                current = current->left;
                continue;
            }
            else if (current->left == NULL)
            {
                current->left = add_block(current, data);
                return;
            }
        }
        if (current->data < data)
        {
            if (current->right != NULL)
            {
                current = current->right;
                continue;
            }
            else if (current->right == NULL)
            {
                current->right = add_block(current, data);
                return;
            }
        }
        return;
    }
}

LIST* find_min(LIST* current)
{
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

LIST* find_max(LIST* current)
{
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

int length(LIST* root, int len) {
    if (root) {
        int a = length(root->left, len + 1);
        int b = length(root->right, len + 1);
        return (a > b) ? a : b;

    }
    else
        return len;
}
LIST* fillTree(LIST* root) {
    if (root) {
        int a = length(root->left, 0);
        int b = length(root->right, 0);
        root->data = (a > b) ? a - b : b - a;
        fillTree(root->left);
        fillTree(root->right);
        return root;
    }
    return NULL;
}

LIST* find_data(int data, LIST* current)
{
    while (current != NULL)
    {
        if (current->data == data)
        {
            return current;
        }
        else if (current->data > data)
        {
            current = current->left;
            continue;
        }
        else if (current->data < data)
        {
            current = current->right;
            continue;
        }
    }
    return NULL;
}


void delete_block(LIST* current)
{
    if (current == NULL)
    {
        return;
    }
    if (current->right == NULL && current->left == NULL)
    {
        if (current->parent == NULL)
        {
            list = NULL;
            return;
        }
        if (current->parent->left == current)
        {
            current->parent->left = NULL;
        }
        else if (current->parent->right == current)
        {
            current->parent->right = NULL;
        }
    }
    else if (current->left != NULL && current->right == NULL)
    {
        if (current->parent == NULL)
        {
            LIST* tmp = current->left;
            current->data = tmp->data;
            current->left = tmp->left;
            current->right = tmp->right;
            current = tmp;
        }
        else if (current->parent->left == current)
        {
            current->parent->left = current->left;
            current->left->parent = current->parent;
        }
        else if (current->parent->right == current)
        {
            current->parent->right = current->left;
            current->left->parent = current->parent;
        }
    }
    else if (current->left == NULL && current->right != NULL)
    {
        if (current->parent == NULL)
        {
            LIST* tmp = current->right;
            current->data = tmp->data;
            current->left = tmp->left;
            current->right = tmp->right;
            current = tmp;
        }
        else if (current->parent->left == current)
        {
            current->parent->left = current->right;
            current->right->parent = current->parent;
        }
        else if (current->parent->right == current)
        {
            current->parent->right = current->right;
            current->right->parent = current->parent;
        }
    }
    else if (current->left != NULL && current->right != NULL)
    {
        LIST* localMax = find_max(current->left);
        current->data = localMax->data;
        delete_block(localMax);
        return;
    }
    free(current);
}

void deleteValue(LIST* root, int value) {
    LIST* target = find_data(value, root);
    delete_block(target);
}
void printTree(LIST* root, const char* dir, int level)
{
    if (root)
    {
        printf("lvl %d %s = %s\n", level, dir, root->data);
        printTree(root->left, "left", level + 1);
        printTree(root->right, "right", level + 1);
    }
}
int main()
{
    char res;
    int data;
    int count = 0;
    LIST* power;
    res = getchar();
    getchar();
    scanf("%d", &data);
    insert_in_tree(data);
    while (res != EOF)
    {
        if (res == 'a')
        {
            power = find_data(data, list);
            if (power == NULL)
            {
                insert_in_tree(data);
            }
            count++;
        }
        if (res == 'r')
        {
            power = find_data(data, list);
            if (power != NULL)
            {
                delete_block(power);
            }
        }
        if (res == 'f')
        {
            power = find_data(data, list);
            if (power == NULL)
            {
                printf("no\n");
            }
            else
            {
                printf("yes\n");
            }
        }
        if (res == '\r')
        {
            getchar();
        }
        if (res == '\n')
        {
            getchar();
        }
        getchar();
        res = getchar();
        scanf("%d", &data);
    }
    LIST* node = fillTree(list);
    printTree(node, "root", count);
    return 0;
}
