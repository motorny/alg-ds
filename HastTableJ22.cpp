#pragma warning (disable: 4996)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "HashTableJ22.h"

char s = ' ';
typedef char* type;

Hashtable* create_hash(int n) {

    Hashtable* myHash = (Hashtable*)malloc(sizeof(Hashtable));
    if (!myHash)
        return NULL;
    myHash->data = (type*)calloc(n, sizeof(type));
    if (!myHash->data) {
        free(myHash);
        return NULL;
    }
    myHash->n = n;
    return myHash;
}

int insert(Hashtable* table, const type val) {

    int i = 0, j = 0;
    int start = 0;
    int m = table->n;
    while (val[i])
        start += val[i++];
    start = start % m;
    i = start;
    do {
        if (!table->data[i] || table->data[i] == &s) {
            table->data[i] = (type)malloc(sizeof(char) * (strlen(val) + 1));
            if (!table->data[i])
                return 0;
            strcpy(table->data[i], val);
            return 1;
        }
        if (strcmp(table->data[i], val) == 0)
            return 1;
        i = (i + 2 * j + 1) % m;
        j++;
    } while (i != start);
    return 1;
}

int find(const Hashtable* table, const type val) {

    int i = 0, j = 0;
    int start = 0;
    int m = table->n;
    while (val[i])
        start += val[i++];
    start = start % m;
    i = start;
    do {
        if (!table->data[i])
            return 0;
        if (table->data[i] != &s && strcmp(table->data[i], val) == 0)
            return 1;
        i = (i + 2 * j + 1) % m;
        ++j;
    } while (i != start);
    return 0;
}

int Delete(Hashtable* table, const type val) {

    int i = 0;
    int j = 0;
    int start = 0;
    int m = table->n;
    while (val[i])
        start += val[i++];
    start = start % m;
    i = start;
    do {
        if (!table->data[i])
            return 0;
        if (table->data[i] != &s && strcmp(table->data[i], val) == 0) {
            free(table->data[i]);
            table->data[i] = &s;
            return 1;
        }

        i = (i + 2 * j + 1) % m;
        ++j;
    } while (i != start);
    return 0;
}

void free_hash(Hashtable* table) {
    for (int i = 0; i < table->n; ++i) {
        if (table->data[i] && table->data != (type*)&s)
            free(table->data[i]);
    }

    free(table->data);
    free(table);
}

int main() {

    char symbol = 1;
    char val[64];
    Hashtable* Olyasha = create_hash(5);

    while (1) {
        symbol = getchar();
        if (symbol == EOF)
            break;
        scanf("%s", &val);
        getchar();
        switch (symbol) {
        case 'a':
            insert(Olyasha, val);
            break;
        case 'f':
            if (find(Olyasha, val))
                printf("yes\n");
            else
                printf("no\n");
            break;
        case 'r':
            Delete(Olyasha, val);
            break;
        default:
            break;
        }
    }

    free_hash(Olyasha);
    return 0;
}