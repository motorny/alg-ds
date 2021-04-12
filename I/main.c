#include <stdlib.h>

#include "23Tree.h"

int main() {

    Node_t* root = newNode(1);

    root = insertTerminate(root, 3);

    free(root);

    return 0;
}