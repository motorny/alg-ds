#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#pragma warning(disable:4996)
#define SIZE 10000
#define TRUE 1
#define FALSE 0

typedef enum status {
    FREE,
    DELETED,
    FULL
}status_t;

typedef struct hashTable {
    char* str;
    status_t status;
} hashTable_t;

hashTable_t* Table = NULL;

hashTable_t* Create() {
    int i;
    hashTable_t* hashTable = (hashTable_t*)malloc(sizeof(hashTable_t) * SIZE);
    if (hashTable == NULL)
        return NULL;
    for (i = 0; i < SIZE; i++)
        hashTable[i].status = DELETED;
    return hashTable;
}

static int Hash(char* str) {
    int index = 0, i;
    for (i = 0; str[i] != 0; i++)
        index += str[i];
    return index % SIZE;
}

int Add(char* str) {
    if (!Table) {
        Table = Create();
        if (!Table) {
            return FALSE;
        }
    }
    int p0 = Hash(str);
    int cp = p0, resp = -1, i = 0;
    do {
        if (Table[cp].status == FULL && strcmp(Table[cp].str, str) == 0)
            return FALSE;

        if (Table[cp].status == FREE || Table[cp].status == DELETED) {
            resp = cp;
            break;
        }
        i++;
        cp = (p0 + i * 1) % SIZE;
    } while (cp != p0);
    if (resp != -1) {
        Table[resp].str = malloc((strlen(str) + 1) * sizeof(char));
        if (!Table[resp].str)
            return FALSE;
        strcpy(Table[resp].str, str);
        Table[resp].status = FULL;
        return TRUE;
    }
    return FALSE;
}

int Search(char* str) {
    if (!Table) {
        return FALSE;
    }
    int p0 = Hash(str), cp = p0, i = 0;
    do {
        if (Table[cp].status == FREE) {
           return FALSE;
        }
        if (Table[cp].status == FULL && strcmp(Table[cp].str, str) == 0)
            return TRUE;
        i++;
        cp = (p0 + i * 1) % SIZE;
    } while (cp != p0);
    return FALSE;
}

int Delete(char* str) {
    if (!Table) {
        return TRUE;
    }
    int p0 = Hash(str), cp = p0, i = 0;
    do {
        if (Table[cp].status == FREE) {
            return FALSE;
        }
        if (Table[cp].status == FULL && strcmp(Table[cp].str, str) == 0) {
            free(Table[cp].str);
            Table[cp].status = DELETED;
            return TRUE;
        }
        i++;
        cp = (p0 + i * 1) % SIZE;
    } while (cp != p0);
    return FALSE;
}

void DestroyTable() {
    if (!Table)
        return;
    int i;
    for (i = 0; i < SIZE; i++)
        if (Table[i].str && Table[i].status == FULL)
            free(Table[i].str);
    free(Table);
}

int main() {
    char str[100];
    char c, command;
    int number;
    while (1) {
        command = getchar();
        if (command != EOF) {
            while (command == '\0' || command == '\n' || isspace(command) != 0)
                c = getchar();
            scanf("%s", &str);
            switch (command) {
            case('a'):
                Add(str);
                break;
            case('r'):
                Delete(str);
                break;
            case('f'):
                if (Search(str) == TRUE)
                    printf("yes\n");
                else
                    printf("no\n");
                break;
            default:
                break;
            }
            c = getchar();
        }
        else
            break;
    }
    DestroyTable();
    return 0;
}