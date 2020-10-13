#include <iostream>
#include <cstdio>
#include <cstring>

#include "WordsList.h"

#define moreThanN 10
#define lenN 6

int main() {
    WordsListNode *listHead = nullptr;
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
            std::cout<<std::endl;
            printWordsLenN(listHead, lenN);
            return 0;
        }
        std::cout << "Ошибка работы с файлом! - ошибка чтения из файла" << std::endl;
    }
    std::cout << "Ошибка работы с файлом! - файл не найден" << std::endl;
    return 1;
}
