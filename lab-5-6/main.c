#include "tree.h"

int main()
{
    Node* root = NULL;

    char c = getchar();
    int number;
    while (c != EOF)
    {
        scanf_s("%d", &number);
        switch (c)
        {
        case 'a':
            insert(&root, number);
            break;
        case 'r':
            deleteValue(root, number);
            break;
        case 'f':
            if (getNodeByValue(root, number))
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

    printTree(root, "root", 0);
    getNumOfLeavesBelow(root);

    printf("\nNum of leaves in root: %d\n", root->numOfLeavesBelow);
    printKsmall(root, 6);

    destroyTree(root);
    return 0;
}
