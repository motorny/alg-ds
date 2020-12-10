#include "tree.h"

int mainn()
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

int main()
{
    Node *tree = NULL;
    insert(&tree, 10);
    insert(&tree, 5);
    insert(&tree, 15);
    insert(&tree, 7);
    insert(&tree, 3);
    insert(&tree, 12);
    insert(&tree, 17);
    insert(&tree, 1);
    insert(&tree, 20);
    insert(&tree, 4);
    insert(&tree, 16);
    destroyTree(tree);
    Node* tmp = getNodeByValue(tree, 12);

    //getNumOfLeavesBelow(tree);
    //printf("%d ", tree->numOfLeavesBelow);
}
