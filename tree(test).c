#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

#define TRUE 1



struct tree {
    int num;
    struct tree* left;
    struct tree* parent;
    struct tree* right;
};




void Add(struct tree** tree, int num) {
    struct tree* temp = (*tree), * newnode, * ptr = (*tree);

    newnode = (struct tree*)malloc(sizeof(struct tree));
    if (!newnode)
        return;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    newnode->num = num;

    if (!(*tree)) {
        (*tree) = newnode;
        return;
    }

    while (ptr) {
        if (num < ptr->num) {
            if (ptr->left)
                ptr = ptr->left;
            else
                break;
        }

        else if (num > ptr->num) {
            if (ptr->right)
                ptr = ptr->right;
            else
                break;
        }

        else {

            free(newnode);
            return;
        }
    }



    if (num < ptr->num)
        ptr->left = newnode;
    else
        ptr->right = newnode;

    newnode->parent = ptr;
}

struct tree* NodeFind(struct tree* tree, int num) {

    while (tree) {

        if (num < tree->num)
            tree = tree->left;

        else if (num > tree->num)
            tree = tree->right;

        else
            return tree;
    }
    return NULL;
}


struct tree* getMax(struct tree* tree)
{
    while (tree->right != NULL)
    {
        tree = tree->right;
    }
    return tree;
}


void NodeRemove(struct tree** tree, int num) {
    if (tree == NULL) {
        return;
    }
    if ((*tree) == NULL)
    {
        return;
    }
    if (num < (*tree)->num)
    {
        NodeRemove(&((*tree)->left), num);
    }
    else if (num > (*tree)->num)
    {
        NodeRemove(&((*tree)->right), num);
    }
    else if ((*tree)->left == NULL && (*tree)->right == NULL)
    {
        (*tree) = NULL;
    }
    else if ((*tree)->left != NULL && (*tree)->right == NULL)
    {
        (*tree) = (*tree)->left;
    }
    else
    {
        if ((*tree)->left == NULL && (*tree)->right != NULL)
        {
            (*tree) = (*tree)->right;
        }
        else
        {
            struct tree* max = getMax((*tree)->left);
            (*tree)->num = max->num;
            NodeRemove(&((*tree)->left), max->num);
        }
    }
        
   
}

void DestroyTree(struct tree* tree) {
    if (tree) {
        DestroyTree(tree->left);
        DestroyTree(tree->right);
        free(tree);
    }
}



int main(void) {
    char comand;
    int num = 0;
    struct tree* tree = NULL;

    while (TRUE) {
        comand = fgetc(stdin);

        if (comand == EOF || comand == '\n')
            break;

        scanf("%i", &num);

        //comands
        if (comand == 'a') //append
            Add(&tree, num);

        //adress as bool type. Is adress not NULL -> TRUE. Otherwise, FALSE
        else if (comand == 'f') { //find
            if (NodeFind(tree, num))
                printf("yes\n");
            else
                printf("no\n");
        }

        else if (comand == 'r')//remove
            NodeRemove(&tree,num);

        num = 0;
        comand = fgetc(stdin); //get '\n' from stdin
    }
    //PrintTree(tree, 1);
    DestroyTree(tree);

    return 0;
}