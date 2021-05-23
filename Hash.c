#include"Hash.h"

Hash_t* Create(int size) {
    Hash_t* table;

    table = (Hash_t*)malloc(sizeof(Hash_t) * size);
    if (table == NULL)
        return NULL;

    for (int i = 0; i < size; i++)
        table[i].status = FREE;

    return table;
}

int Hash(char* str, int size) {
    int index = 0;

    for (int i = 0; str[i] != 0; i++)
        index += str[i];

    return index % size;
}

void Insert(Hash_t* table, char* elem, int size) {
    int key = Hash(elem, size);
    int index = key;
    for (int pos = 0; pos < size; pos++) {
        if (table[index].status == FREE || table[index].status == DELETED) {
            table[index].str = (char*)malloc((strlen(elem) + 1) * sizeof(char));
            strcpy(table[index].str, elem);
            table[index].status = NOT_FREE;
            return;
        }
        else
            if (table[index].status == NOT_FREE && strcmp(table[index].str, elem) == 0)
                return;
        index = (index + 2 * pos + 1) % size;
    }
}

int Find(Hash_t* table, char* elem, int size) {
    int key = Hash(elem, size);
    int index = key;
    for (int pos = 0; pos < size; pos++) {
        if (table[index].status == NOT_FREE && strcmp(table[index].str, elem) == 0)
            return SUCCESS;
        else
            if (table[index].status == FREE)
                return FAIL;
        index = (index + 2 * pos + 1) % size;
    }
    return FAIL;
}

void Delete(Hash_t* table, char* elem, int size) {
    int key = Hash(elem, size);
    int index = key;
    for (int pos = 0; pos < size; pos++) {
        if (table[index].status == NOT_FREE && strcmp(table[index].str, elem) == 0) {
            free(table[index].str);
            table[index].status = DELETED;
            return;
        }
        else
            if (table[index].status == FREE)
                return;
        index = (index + 2 * pos + 1) % size;
    }
}

void Free(Hash_t* table, int size) {
    for (int i = 0; i < size; i++)
        if (table[i].status == NOT_FREE)
            free(table[i].str);
    free(table);
}
