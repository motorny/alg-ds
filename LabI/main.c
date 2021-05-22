#include "2-3tree.h"
#pragma warning (disable:4996)
#include <stdio.h>

void print(Tree* root) {
    if (root == NULL) {
        return;
    }
    while (!isT(root)) {
        root = root->left;
    }
    if (root != NULL) {
        root = root->left;
        do {
            printf("%d ", root->left_value);
        } while ((root = root->right1) != NULL);
    }
}
int main(void) {
    Tree* root = NULL;
    int c = getchar();
    int number;
  
scanf("%d", &number);
    root = AddN(root, number);
    printf(Search(root, number) == NULL ? "no\n" : "yes\n");
    root = deleteN(root, number);
    freeTr(root);
    return 0;
}