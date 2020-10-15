#include <cstdio>
#include <cstring>

#include "WordsList.h"

#define moreThanN 7

int main() {
    WordsListNode *listHead = nullptr;
    int lenN;
    FILE *file;
    const char *fName =  "/home/ikuzin/study/algo_and_struct/alg-ds/lab-1/src/words.txt";
    file = fopen(fName, "r");
    if (file != nullptr) {
        fseek(file, 0, SEEK_END);
        long lSize = ftell(file);
        rewind(file);
        char *buffer = (char *) malloc(sizeof(char) * lSize);
        size_t result = fread(buffer, 1, lSize, file);
        if (result == lSize) {
            char *word = strtok(buffer, " ,.-");
            while (word != nullptr) {
                unsigned int len = getCountOfLetters(word);
                add2List(word, listHead, len);
                word = strtok(nullptr, " ,.-\n");
            }
            fclose(file);
            printWordsMoreNLen(listHead, moreThanN);
            printf("\n Давайте узнаем сколько слов с длинной...: ");
            scanf("%d", &lenN);
            printWordsLenN(listHead, lenN);
            return 0;
        }
        printf("\nОшибка работы с файлом! - ошибка чтения из файла");
    }
    printf("\nОшибка работы с файлом! - файл не найден");
    return 1;
}
