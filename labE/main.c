#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#pragma warning (disable:4996)


void InputProcessing(tree_t** tree, char action, int value, int** output, int *sizeOfout) {
    int* tmp;
    tree_t* buffer;
    switch (action)
    {
    case 'a':
        Insert(tree, value);
        break;
    case 'r':
        RemoveByValue(tree, value);
        break;
    case 'f':
        (*output)[(*sizeOfout) - 1] = FindByValue(*tree, value, &buffer);
        tmp = (int*)realloc((*output), (++(*sizeOfout)) * sizeof(int));
        if (tmp == NULL) {
            free(*output);
            return;
        }
        *output = tmp;
        break;
    default:
        break;
    }
}

void LeavesInSubtree(tree_t** tree, int** count, int* lvl) { 
    if (tree != NULL) {
        if ((*tree)->left == NULL && (*tree)->right == NULL) {
            (*tree)->value = 1;
            return;
        }
        else if ((*tree)->left == NULL) {
            LeavesInSubtree(&(*tree)->right, count, lvl);
            (*tree)->value = (*tree)->right->value;
        }
        else if ((*tree)->right == NULL) {
            LeavesInSubtree(&(*tree)->left, count, lvl);
            (*tree)->value = (*tree)->left->value;
        }
        else {
            LeavesInSubtree(&(*tree)->left, count, lvl);
            LeavesInSubtree(&(*tree)->right, count, lvl);
            (*tree)->value = (*tree)->right->value + (*tree)->left->value;
        }
    }
}




int main(void) {
    tree_t* tree = NULL;
    char escape, action;
    int value, *output, sizeOfout = 1;
    output = (int*)malloc(1* sizeof(int));
    if (!output)
        return FALSE;

    do {
        action = (char)getchar();
        if (feof(stdin))
            break;
        scanf(" %i", &value);
        InputProcessing(&tree, action, value, &output, &sizeOfout);
        scanf("%c", &escape);
    } while (action != EOF);

    for (int i = 0; i < sizeOfout - 1; i++)
    {
        if (output[i] == TRUE)
            printf("yes\n");
        else
            printf("no\n");
    }
    free(output);
	return 0;
}