#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "LabA.h"

//функция, считывающая слова из файла в список
int ReadList(list* mylist, FILE* F) {

    list* WordBase = (list*)calloc(1, sizeof(list));

    fscanf(F, "%s", &WordBase->string);

    WordBase->previous = mylist->previous;
    mylist->previous = WordBase;

    if (feof(F) != 0 )  
        return 0;
    else
        ReadList(mylist, F);
}
//функция, меняющая 2 слова местами при необходимости и возвращающая указатель на образовавшееся локальное начало
list* SortSubstitution(list* word) {
    //если слова стоят в нужном порядке
    if (strlen(word->string) < strlen(word->previous->string)  || (strlen(word->string) == strlen(word->previous->string) && strcmp(word->string, word->previous->string) <= 0)) {
        if (word->previous->previous != NULL)
            word->previous = SortSubstitution(word->previous);
        return word;
    }
    //если слова нужно поменять местами
    else if (strlen(word->string) > strlen(word->previous->string) || (strlen(word->string) == strlen(word->previous->string) && strcmp(word->string, word->previous->string)>0)) {
        list intermediate;
        list* sortedStart;
        sortedStart = word->previous;
        intermediate.previous = word->previous->previous;
        word->previous->previous = word;
        word->previous = intermediate.previous;
        flagSort++; //подсчет количества подмен
        if (sortedStart->previous->previous != NULL)
            sortedStart->previous = SortSubstitution(sortedStart->previous);
        return sortedStart;
    }
}
//функция, печатающая список
void ListPrint(list* word) {
    printf("%s\n", word->string);
    if (word->previous != NULL)
        ListPrint(word->previous);
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
    if(strlen(word->string) > N)
    printf("%s\n", word->string);
    if (word->previous != NULL)
        ListCountMore(word->previous);
}
//функция, печатающая слова, равные введенной длине
void ListCountSame(list* word, int number) {
    if (strlen(word->string) == number) {
        flagSameLength++;
        if (flagSameLength == 1)//при нахождении первого слова такой длины
            printf("Words of the same length:\n");
        printf("%s\n", word->string);
    }
    if (word->previous != NULL)
        ListCountSame(word->previous, number);
    else  if (flagSameLength == 0)
        printf("No words of the same length.");
}
//функция, сортирующая список целиком
void SortList(list* mylist) {
    flagSort = 0;
    mylist->previous = SortSubstitution(mylist->previous);
    if (flagSort != 0) //если не сделано ни одной подмены, значит, список отсортирован
        SortList(mylist);
}
