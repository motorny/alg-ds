#include "tree23plus.h"
#pragma warning(disable:4996)


int main(void) {
    tree_t* tree = NULL;
    int value;
    char c = getchar();
    while (c != EOF) {
        scanf("%i", &value);
        if (c == 'a') {
            Insert(&tree, value);
        }
        else if (c == 'r') {
            Delete(&tree, value);
        }
        else if (c == 'f') {
            if (Find(tree, value))
                printf("yes\n");
            else
                printf("no\n");
        }

        else {
            continue;
        }
        c = getchar();
        if (c == '\r' || c == '\n')
            c = getchar();
    }
    return 0;
}