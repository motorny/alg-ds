#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAIL 0
#define TRUE 1

#pragma warning (disable: 4996)

typedef char* T;
char del = ' ';

typedef struct {
	int size;
    T* data;
} hash_t;


hash_t* Hash_Create(int size) {
    hash_t* tableNew = malloc(sizeof(hash_t));
    if (!tableNew)
        return NULL;

    tableNew->data = calloc(size, sizeof(T));
    if (!tableNew->data) {
        free(tableNew);
        return NULL;
    }

    tableNew->size = size;
    return tableNew;
}

int Hash(T key, int m) {
    int hash = 0;
    int i = 0;
    while (key[i])
        hash += key[i++];

    return hash % m;
}

int Hash_Insert(hash_t* table, const T key) {
    int i = 0;
    int j = 0;
    int start;
    int m = table->size;

    start = Hash(key, m);
    i = start;
    do {
        if (table->data[i] == NULL || table->data[i] == &del) {
            table->data[i] = malloc(sizeof(char) * (strlen(key) + 1));
            if (!table->data[i])
                return FAIL;
            strcpy(table->data[i], key);
            return SUCCESS;
        }

        if (strcmp(table->data[i], key) == 0)
            return FAIL;

        i = (i + 2 * j + 1) % m;
        ++j;
    } while (i != start);

    return SUCCESS;
}

int Hash_Find(const hash_t* table, const T key) {
    int i = 0;
    int j = 0;
    int start;
    int m = table->size;

    start = Hash(key, m);
    i = start;
    do {
        if (table->data[i] == NULL)
            return FAIL;

        if (table->data[i] != &del && strcmp(table->data[i], key) == 0)
            return SUCCESS;

        i = (i + 2 * j + 1) % m;
        ++j;
    } while (i != start);

    return FAIL;
}

int Hash_Delete(hash_t* table, const T key) {
    int i = 0;
    int j = 0;
    int start;
    int m = table->size;

    start = Hash(key, m);
    i = start;
    do {
        if (table->data[i] == NULL)
            return FAIL;

        if (table->data[i] != &del && strcmp(table->data[i], key) == 0) {
            free(table->data[i]);
            table->data[i] = &del;
            return SUCCESS;
        }

        i = (i + 2 * j + 1) % m;
        ++j;
    } while (i != start);

    return FAIL;
}


/*
void Hash_Destroy(hash_t* table) {
    int i = 0;
    for (i = 0; i < table->size; ++i) {
        if (table->data[i] && table->data != &del)
            free(table->data[i]);
    }
    free(table->data);
    free(table);
}
*/
int main() {

    char command = 1;
    char key[64];
    hash_t* table = Hash_Create(5);

    command = getchar();
    while (command != EOF) {
        scanf("%s", &key);
        switch (command) {
        case 'a':
            Hash_Insert(table, key);
            break;
        case 'f':
            if (Hash_Find(table, key))
                printf("yes\n");
            else
                printf("no\n");
            break;
        case 'r':
            Hash_Delete(table, key);
            break;
        default:
            return 0;
        }
        command = getchar();
        if (command == '\n')
            command = getchar();
    }
  //  Hash_Destroy(table);

    return 0;
}