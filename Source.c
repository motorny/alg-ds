#include "2-3.h"


int main(void) {
    char* str, * tmpStr, ch = 0;
    int num = 0, i = 0, j = 1, k = 1;
    tree_t* tree = NULL;
    str = ReadStr();
    tmpStr = strtok(str, "\n");
    while (tmpStr != NULL) {
        if (sscanf(tmpStr + i++, "%c", &ch));
        if (sscanf(tmpStr + i, "%i", &num));
        i = 0;
        switch (ch)
        {
        case 'a':
            if (!FindVal(tree, num))
                tree = InsertNode(tree, num);
            break;
        case 'f':
            if (FindVal(tree, num))
                printf("yes\n");
            else
                printf("no\n");
            break;
        case 'r':
            if (FindVal(tree, num))
                tree = DeleteVal(tree, num);
            break;
        }
        tmpStr = strtok(NULL, "\n");
    }
    DestroyTree(tree);
    free(str);
    return 0;
}