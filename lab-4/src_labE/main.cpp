#include <cstdlib>
#include <cstdio>
#include "cstring"
#include "tree.h"


int main(int argc, char **argv) {
    int lenN, res;
    FILE *file;
//    const char *fName = argv[1];
    const char *fName = "/home/ikuzin/study/algo_and_struct/alg-ds/lab-4/word'stree";
    file = fopen(fName, "r");
    if (file != nullptr) {
        fseek(file, 0, SEEK_END);
        long lSize = ftell(file);
        rewind(file);
        char *buffer = (char *) malloc(sizeof(char) * lSize);
        size_t result = fread(buffer, 1, lSize, file);
        if (result == lSize) {
            treeNode_t *root = (treeNode_t *) malloc(sizeof(treeNode_t));
            addChildren(root, buffer);
            inOrder(root, 0);
            fclose(file);
            free(buffer);
            ClearTree(&root);
            return 0;
        }
        printf("\nОшибка работы с файлом! - ошибка чтения из файла");
    }
    printf("\nОшибка работы с файлом! - файл не найден");
    return 1;
}
