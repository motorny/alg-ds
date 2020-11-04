#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "LabA.h"

//функция, ищущая место для слова
void PutWord(list* old, list* newWord) {
    list* tmp = old;;
    int flag = 1;
    while (flag == 1) {
        if (strlen(newWord->string) < strlen(tmp->previous->string) || (strlen(newWord->string) == strlen(tmp->previous->string) && strcmp(newWord->string, tmp->previous->string) <= 0)) {
            newWord->previous = tmp->previous;
            tmp->previous = newWord;
            flag = 0;
        }
        else {
            if (tmp->previous->previous != NULL) {
                tmp = tmp->previous;
            }
            else {
                newWord->previous = NULL;
                tmp->previous->previous = newWord;
                break;
            }
        }
    }
}

//функция, формирующая список
void MakeList(list* mylist, FILE* F) {
    while (feof(F) == 0) {
        list* new = (list*)calloc(1, sizeof(list));
        if (new != NULL) {
            fscanf(F, "%s", &new->string);
            WordToList(mylist, new);
        }
        else printf("Error: no memory");
    }
}

//функция, записывающее слово в нужное место
void WordToList(list* mylist, list* newWord) {
    if (mylist->previous == NULL) {
        newWord->previous = NULL;
        mylist->previous = newWord;
    }
    else {
        if (mylist->previous->previous == NULL) {
            if (strlen(newWord->string) < strlen(mylist->previous->string) || (strlen(newWord->string) == strlen(mylist->previous->string) && strcmp(newWord->string, mylist->previous->string) <= 0)) {
                newWord->previous = mylist->previous;
                mylist->previous = newWord;
            }
            else {
                newWord->previous = NULL;
                mylist->previous->previous = newWord;
            }
        }
        else {
            PutWord(mylist, newWord);
        }
    }
}

//функция, печатающая список
void ListPrint(list* word) {
    while (word != NULL) {
        printf("%s\n", word->string);
        word = word->previous;
    }
}

//функция, запрашиващая длину слова
int NumberOfLetters(void) {
    int number;
    printf("Enter the number of letters:\n");
    scanf("%d", &number);
    flagSameLength = 0;
    return number;
}

//функция, печатающая слова, длиннее заданного N
void ListCountMore(list* word) {
    int flagMoreLength = 0;
    while (word != NULL) {
        if (strlen(word->string) > N) {
            flagMoreLength++;
            if (flagMoreLength == 1)// при нахождении первого такого слова
                printf("Words which are longer than N:\n");
            printf("%s\n", word->string);
        }
        word = word->previous;
    }
    if (flagMoreLength == 0)
        printf("No words of such length.");
}

//функция, печатающая слова, равные введенной длине
void ListCountSame(list* word, int number) {
    while (word != NULL) {
        if (strlen(word->string) == number) {
            flagSameLength++;
            if (flagSameLength == 1)// при нахождении первого слова такой длины
                printf("Words of the same length:\n");
            printf("%s\n", word->string);
        }
        word = word->previous;
    }
    if (flagSameLength == 0)
        printf("No words of the same length.");
}

