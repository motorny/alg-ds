#include <stdio.h>

#include "AvlList.h"

int main() 
{

    Node_t* root = NULL;
    int c = getchar(), number;

    while (c != EOF) 
    {
        scanf("%d", &number);
        switch (c) 
        {
        case 'a':
            root = insertNode(root, number);
            break;
        case 'f':
            printf(findNode(root, number) == NULL ? "no\n" : "yes\n");
            break;
        case 'r':
            root = deleteNode(root, number);
            break;
        default:
            freeTree(root);
            return 0;
        }

        if ((c = getchar()) == '\n')
            c = getchar();
    }
    freeTree(root);

    return 0;
}