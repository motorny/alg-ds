//
// Created by ikuzin on 18.02.2021.
//
#include <malloc.h>
#include "Node.h"

int ReadAction(FILE *fp, int *key) {
    char c, n;
    int check;
    check = fscanf(fp, "%c", &c);
    if (check == -1)
        return 0;

    fscanf(fp, " %d", key);
    fscanf(fp, "%c", &n);

    switch (c) {
        case 'a':
            return 1;
        case 'r':
            return 2;
        case 'f':
            return 3;
        default:
            return 0;
    }
}

int main() {
    int mode = 0, num = 0;
    Node_t *tree = NULL;

    mode = ReadAction(stdin, &num);
    if (mode == 0)
        return -1;

    do {
        switch (mode) {
            case 1:
                tree = Add(tree, num);
                break;
            case 2:
                Del(&tree, num);
                break;
            case 3: {
                Node_t *tmp = Find(tree, num);
                if (tmp != NULL) {
                    printf("yes\n");
                    tree = Splay(tree);
                } else
                    printf("no\n");
                break;
            }
            default:
                break;
        }
        mode = ReadAction(stdin, &num);

    } while (mode != 0);

    return 0;
}

