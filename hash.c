#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable: 4996)

typedef enum {
    FREE,
    NOT_FREE,
} status_t;

typedef struct {
    char* str;
    int status;
} hash_table_t;

hash_table_t* Create(int size) {
    hash_table_t* table;

    table = (hash_table_t*)malloc(sizeof(hash_table_t) * size);
    if (table == NULL)
        return NULL;

    for (int i = 0; i < size; i++)
        table[i].status = FREE;

    return table;
}

static int HashFunc(char* str, int size) {
    int index = 0;

    for (int i = 0; str[i] != 0; i++)
        index += str[i];

    return index % size;
}

void Add(hash_table_t* table, char* elem, int size) {
    int key = HashFunc(elem, size);
    int index = key;
    for (int pos = 0; pos < size; pos++) {
        if (table[index].status == FREE) {
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

int Find(hash_table_t* table, char* elem, int size) {
    int key = HashFunc(elem, size);
    int index = key;
    for (int pos = 0; pos < size; pos++) {
        if (table[index].status == NOT_FREE && strcmp(table[index].str, elem) == 0)
            return 1;
        else
            if (table[index].status == FREE)
                return 0;
        index = (index + 2 * pos + 1) % size;
    }
    return 0;
}

void Remove(hash_table_t* table, char* elem, int size) {
    int key = HashFunc(elem, size);
    int index = key;
    for (int pos = 0; pos < size; pos++) {
        if (table[index].status == NOT_FREE && strcmp(table[index].str, elem) == 0) {
            free(table[index].str);
            table[index].status = FREE;
            return;
        }
        else
            if (table[index].status == FREE)
                return;
        index = (index + 2 * pos + 1) % size;
    }
}

void Destroy(hash_table_t* table, int size) {
    for (int i = 0; i < size; i++)
        if (table[i].status == NOT_FREE)
            free(table[i].str);
    free(table);
}

int main(void) {
    hash_table_t* table;
    int size = 500;
    table = Create(size);
    char key[100];
    char cmd;
    char sym;

    while ((cmd = getchar()) != EOF) {
        while (cmd == '\0' || cmd == '\n' || isspace(cmd) != 0)
            sym = getchar();
        scanf("%s", &key);
        switch (cmd) {
        case('a'):
            Add(table, key, size);
            break;
        case('r'):
            Remove(table, key, size);
            break;
        case('f'):
            if (Find(table, key, size))
                puts("yes");
            else
                puts("no");
            break;
        default:
            break;
        }
        sym = getchar();
    }


    Destroy(table, size);
    return 0;
}