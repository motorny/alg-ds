#include "Treap.h"

#include <stdio.h>

int main()
{
    Treap* root = NULL;

    char c = getchar();
    int number;
    while (c != EOF)
    {
        scanf_s("%d", &number);
        switch (c)
        {
        case 'a':
            Insert(&root, number);
            break;
        case 'r':
            Remove(&root, number);
            break;
        case 'f':
            if (Find(root, number))
                printf("yes\n");
            else
                printf("no\n");
            break;
        default:
            printf("Incorrect input");
            return 0;
        }

        c = getchar();
        if(c == '\r')
            c = getchar();
        if(c == '\n')
            c = getchar();
    }

    DestroyTreap(root);

    return 0;
}
