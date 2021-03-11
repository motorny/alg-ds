#include <stdio.h>
#include "rbtree.h"
#pragma warning(disable:4996)

int main(void) {
    Node* tree = NIL;
    int value;
    char c = getchar();
    while (c != EOF) {
        scanf("%d", &value);
        if (c == 'a') {
            insert(value, &tree);
        }
        else if (c == 'r') {
            deleteD(value, &tree);
        }
        else if (c == 'f') {
            Node* check = findNode(value, tree);
            if (check != NULL)
                printf("yes\n");
            else
                printf("no\n");
        }

        else {
            continue;
        }
        c = getchar();
        if (c == '\r')
            c = getchar();
        else if (c == '\n')
            c = getchar();
    }
    return 0;
}
