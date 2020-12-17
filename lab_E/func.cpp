#include "Header.h"
LIST* list;
LIST* add_block(LIST* parent, char data[])
{
    LIST* NEW = (LIST*)malloc(sizeof(LIST));
    if (NEW == NULL)
    {
        return NULL;
    }
    NEW->left = NEW->right = NULL;
    int i = 0;
    for (i; i < strlen(data); i++)
    {
        NEW->data[i] = data[i];
    }
    NEW->data[i] = '\0';
    NEW->parent = parent;
    return NEW;
}

void insert_in_tree(char data[])
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


LIST* find_data(char data[], LIST* current)
{
    while (current != NULL)
    {
        if (strcmp(current->data, data)==0)
        {
            return current;
        }
        else if (strcmp(current->data, data)>0)
        {
            current = current->left;
            continue;
        }
        else if (strcmp(current->data, data)<0)
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
            for (int i=0; i < strlen(tmp->data); i++)
            {
                current->data[i] = tmp->data[i];
            }
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
            for (int i=0; i < strlen(tmp->data); i++)
            {
                current->data[i] = tmp->data[i];
            }
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
        for (int i=0; i < strlen(localMax->data); i++)
        {
            current->data[i] = localMax->data[i];
        }
        delete_block(localMax);
        return;
    }
    free(current);
}

void deleteValue(LIST* root, char value[])
{
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

void file_read(FILE* fp)
{
    char res;
    char next;
    char current;
    char prev;
    char word[100];
    int position_in_array = 0;
    res = getc(fp);
    prev = res;
    while (res != '=')
    {
        res = getc(fp);
    }
    res = getc(fp);
    if (res == ' ')
    {
        return;
    }
    while (res != '(' && res != ')' && res != EOF)
    {
        prev = res;
        word[position_in_array] = res;
        position_in_array++;
        res = getc(fp);
    }
    word[position_in_array] = '\0';
    list = add_block(NULL, word);
    current = res;
    res = getc(fp);
    while (res != EOF)
    {
        position_in_array = 0;
        while (res != '(' && res != ')' && res != EOF)
        {
            word[position_in_array] = res;
            position_in_array++;
            res = getc(fp);
        }
        next = res;
        res = current;
        word[position_in_array] = '\0';
        if (res == '(')
        {
            if (prev != ')')
            {
                list->left = add_block(list, word);
                list = list->left;
            }
            if (prev == ')')
            {
                list->right = add_block(list, word);
                list = list->right;
            }
        }
        if (res == ')')
        {
            list = list->parent;
        }
        prev = res;
        res = next;
        current = res;
        res = getc(fp);
    }
    list = list->parent;
}
