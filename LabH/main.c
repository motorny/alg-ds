#pragma warning(disable:4996)
#include <../../rbst.h>

int main()
{
    struct node* root = NULL;
    int key = 0;

    char c = getchar();
    while (c != EOF)
    {
        scanf("%d", &key);
        switch (c)
        {
        case 'a':
            root = insertnode(root, key);
            break;
        case 'r':
            root = remove_node(root, key);
            break;
        case 'f':
            if (node_find(root, key))
                printf("yes\n");
            else
                printf("no\n");
            break;
        default:
            printf("wrong command");
            return 0;
        }

        c = getchar();
        if (c == '\r')
            c = getchar();
        if (c == '\n')
            c = getchar();
    }

    return 0;
}