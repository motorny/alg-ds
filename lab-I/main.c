#include "tree23.h"

int main()
{
    TreeNode* tree = NULL;

    char c = getchar();
    int number;
    while (c != EOF)
    {
        scanf("%d", &number);
        switch (c)
        {
        case 'a':
            Insert(&tree, number);
            break;
        case 'r':
            Delete(&tree, number);
            break;
        case 'f':
            if (Find(tree,number))
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

    return 0;
}
