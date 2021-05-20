#include "Header.h"
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996)

hash_t* HashCreate(int size) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (!hash)
        return NULL;
    hash->data = calloc(size, sizeof(table));
    if (!hash->data) {
        free(hash);
        return NULL;
    }
    hash->size = size;
    return hash;
}

int Hash(table key, int m) {
    int hash = 0, i = 0;
    while (key[i])
        hash += key[i++];
    return hash % m;
}

int HashInsert(hash_t* t, const table key) {
    int i = 0, j = 0, start;
    int m = t->size;
    start = Hash(key, m);
    i = start;
    do {
        if (t->data[i] == NULL || t->data[i] == ' ') {
            t->data[i] = malloc(sizeof(char) * (strlen(key) + 1));
            if (!t->data[i])
                return FAIL;
            strcpy(t->data[i], key);
            return SUCCESS;
        }
        if (strcmp(t->data[i], key) == 0)
            return FAIL;
        i = (i + 2 * j + 1) % m;
        ++j;
    } while (i != start);
    return SUCCESS;
}

int HashSearch(const hash_t* t, const table key) {
    int i = 0, j = 0, start;
    int m = t->size;
    start = Hash(key, m);
    i = start;
    do {
        if (t->data[i] == NULL)
            return FAIL;
        if (t->data[i] != ' ' && strcmp(t->data[i], key) == 0)
            return SUCCESS;
        i = (i + 2 * j + 1) % m;
        ++j;
    } while (i != start);
    return FAIL;
}

int HashDelete(hash_t* t, const table key) {
    int i = 0, j = 0, start;
    int m = t->size;
    start = Hash(key, m);
    i = start;
    do {
        if (t->data[i] == NULL)
            return FAIL;
        if (t->data[i] != ' ' && strcmp(t->data[i], key) == 0) {
            free(t->data[i]);
            t->data[i] = ' ';
            return SUCCESS;
        }
        i = (i + 2 * j + 1) % m;
        ++j;
    } while (i != start);
    return FAIL;
}

void HashFree(hash_t* t) {
    int i;
    for (i = 0; i < t->size; ++i) {
        if (t->data[i] && t->data != ' ')
            free(t->data[i]);
    }
    free(t->data);
    free(t);
}