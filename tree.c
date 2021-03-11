#include <stdio.h>
#include <stdlib.h>

typedef struct tree_t
{
    int key;
    int previous;
    struct tree_t* left;
    struct tree_t* right;
} tree_t;


tree_t* Node(int key)
{
    tree_t* node = (tree_t*)malloc(sizeof(tree_t));
    if (node != NULL)
    {
        node->key = key;
        node->previous = rand();
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

tree_t* Merge(tree_t* L, tree_t* R)
{
    if (L == NULL)
        return R;
    if (R == NULL)
        return L;

    if (L->previous > R->previous)
    {
        L->right = Merge(L->right, R);
        return L;
    }
    else
    {
        R->left = Merge(L, R->left);
        return R;
    }
}

void LR(tree_t* node, int key, tree_t** L, tree_t** R)
{
    if (node == NULL)
    {
        (*L) = NULL;
        (*R) = NULL;
        return;
    }

    if (key < node->key)//
    {
        LR(node->left, key, L, &(node->left));
        (*R) = node;
    }
    else
    {
    
        LR(node->right, key, &(node->right), R);
        (*L) = node;
    }
}

void Insert(tree_t** root, int key)
{
    if ((*root) == NULL)
    {
        (*root) = Node(key);
        return;
    }

    tree_t* L = NULL;
    tree_t* R = NULL;
    LR(*root, key, &L, &R);
    tree_t* m = Node(key);

    (*root) = Merge(Merge(L, m), R);
}

void Delete(tree_t** root, int key)
{
    tree_t* L = NULL;
    tree_t* R = NULL;
    tree_t* m = NULL;

    LR(*root, key - 1, &L, &R);
    LR(R, key, &m, &R);

    free(m);

    (*root) = Merge(L, R);
}

tree_t* Find(tree_t* node, int key)
{
    if (node == NULL)
        return NULL;

    if (node->key == key)
        return node;

    if (key < node->key )
        return Find(node->left, key);
    else
        return Find(node->right, key);
}

void DeleteTree(tree_t* node)
{
    if (node != NULL)
    {
        DeleteTree(node->left);
        DeleteTree(node->right);
        free(node);
    }
}

int main()
{
    tree_t* root = NULL;

    char c = getchar();
    int number;
    while (c != EOF)
    {
        scanf("%d", &number);
        switch (c)
        {
        case 'a':
            Insert(&root, number);
            break;
        case 'r':
            Delete(&root, number);
            break;
        case 'f':
            if (Find(root, number))
                printf("yes\n");
            else
                printf("no\n");
            break;
        default:
            printf("no\n");
            return 0;
        }

        c = getchar();
        if (c == '\r')
            c = getchar();
        if (c == '\n')
            c = getchar();
    }

    DeleteTree(root);

    return 0;
}