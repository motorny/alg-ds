#include "labE.h"
int main(void) {
    struct tree* tree = NULL;
    char esc;
    char act;
    int value;
    int* output;
    int out = 1;
    output = (int*)malloc(1 * sizeof(int));
    if (!output) {
        return FALSE;
    }
    do {
        act = (char)getchar();
        if (feof(stdin)) {
            break;
        }
        scanf(" %i", &value);
        Input(&tree, act, value, &output);
        scanf("%c", &esc);
    } while (act != EOF);
    for (int i = 0; i < out - 1; i++)
    {
        if (output[i] == TRUE) {
            printf("Yes");
        }
        else {
            printf("No");
        }
    }
    free(output);
    return 0;
}
